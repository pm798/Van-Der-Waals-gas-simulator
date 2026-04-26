#include "VanDerWaalsGas.h"

// Структура, в которой хранятся табличные данные.
namespace GasData {
    const std::map<std::string, GasConstants> LOOKUP = {
        {"He", {0.00345, 0.0000237, 3}},
        {"H2",  {0.0247,  0.0000266, 5}},
        {"N2",  {0.137,   0.0000385, 5}},
        {"O2",  {0.138,   0.0000318, 5}},
        {"H2O", {0.553,   0.0000305, 6}}
    };
}



// Проверка того, что состояние возможно.
bool VanDerWaalsGas::is_state_valid(double v, double t, double n) const {
    double min_volume = n * b;
    if (v <= min_volume) {
        return false;
    }
    if (t <= 0) {
        return false;
    }
    if (n <= 0) {
        return false;
    }
    return true;
}
// Вспомогательный расчет (a*nu^2 / V^2). Нужен для некоторых других вычислений.
double VanDerWaalsGas::get_cohesion_pressure() const {
    return (a * moles * moles) / (volume * volume);
}

// Расчет давления, зная остальные параметры.
void VanDerWaalsGas::update_pressure() {
    double effective_v = volume - moles * b;
    pressure = (moles * R * temperature) / effective_v - get_cohesion_pressure();
}

// Расчет внутренней энергии, Cp, Cv и gamma.
void VanDerWaalsGas::update_thermodynamics() {
    internal_energy = (Cv * temperature) - get_cohesion_pressure() * volume;

    double v_nb = volume - moles * b;
    double correction = (2.0 * a * moles * v_nb * v_nb) / (R * temperature * std::pow(volume, 3));
    
    Cp = Cv + (moles * R) / (1.0 - correction);
    gamma = Cp / Cv;
}



// Конструктор, в котором задается название газа из таблицы, его объем, температура и количество.
VanDerWaalsGas::VanDerWaalsGas(std::string name, double v, double t, double n) 
: VanDerWaalsGas(name, GasData::LOOKUP.at(name).a, GasData::LOOKUP.at(name).b, GasData::LOOKUP.at(name).degrees_of_freedom, v, t, n)
{
    if (!is_state_valid(v, t, n)) {
    throw std::runtime_error(" ATTEMPT TO CREATE AN OBJECT IN INVALID PHYSICAL STATE :" + name);
    }  
    update_pressure();
    update_thermodynamics();
}
// Конструктор, в котором создается новый газ не из таблицы со своими коэффициентами a, b, кол-во степеней свободы. Остальные параметры задаются так же, как в прошлом конструкторе.
VanDerWaalsGas::VanDerWaalsGas(std::string name, double custom_a, double custom_b, int df, double v, double t, double n)
    : gas_name(name), a(custom_a), b(custom_b), degrees_of_freedom(df), volume(v), temperature(t), moles(n), Cv((df / 2.0) * n * R)
{
    if (!is_state_valid(v, t, n)) {
    throw std::runtime_error(" ATTEMPT TO CREATE AN OBJECT IN INVALID PHYSICAL STATE: " + name);
    }
    else{
        update_pressure();
        update_thermodynamics();
    }
}

// Изохорный нагрев на заданное количество градусов.
void VanDerWaalsGas::isochoricHeating(double delta_T) {
    temperature += delta_T;
    update_pressure();
    update_thermodynamics();
}

// Изобарное расширение на заданное кол-во м^3.
void VanDerWaalsGas::isobaricExpansion(double delta_V) {
    double next_v = volume + delta_V;
    double next_t = (pressure + (a * moles * moles) / (next_v * next_v)) * (next_v - moles * b) / (moles * R);
    
    if (is_state_valid(next_v, next_t, moles)) {
        volume = next_v;
        temperature = next_t;
        update_thermodynamics();
    }
    else{
            throw std::runtime_error(" INVALID ATTEMPT TO CHANGE AN OBJECT :" + gas_name);
        }
}

// Изотермическое сжатие на заданное кол-во м^3.
void VanDerWaalsGas::isothermalCompression(double delta_V) {
    if (is_state_valid(volume + delta_V, temperature, moles)){
        volume += delta_V;
        update_pressure();
        update_thermodynamics();
    }
    else{
        throw std::runtime_error(" INVALID ATTEMPT TO CHANGE AN OBJECT :" + gas_name);
    }
}

// Адиабатиеское расширение на заданное кол-во м^3.
void VanDerWaalsGas::adiabaticProcess(double delta_V) {
    double next_v = volume + delta_V;
    double exponent = (moles * R) / Cv;
    double next_t = temperature * std::pow((volume - moles * b) / (next_v - moles * b), exponent);

    if (is_state_valid(next_v, next_t, moles)) {
        volume = next_v;
        temperature = next_t;
        update_pressure();
        update_thermodynamics();
    }
    else{
        throw std::runtime_error(" INVALID ATTEMPT TO CHANGE AN OBJECT :" + gas_name);
    }
}

// добавление газа при той же температуре в ту же емкость.
void VanDerWaalsGas::addSubstance(double extra_moles) {
    if (is_state_valid(volume, temperature, moles + extra_moles)) {
        moles += extra_moles;
        Cv = (degrees_of_freedom / 2.0) * moles * R;
        update_pressure();
        update_thermodynamics();
    }
    else{
        throw std::runtime_error(" INVALID ATTEMPT TO CHANGE AN OBJECT :" + gas_name);
    }
}

// Посмотреть текущее состояние газа.
void VanDerWaalsGas::show_gas_info() const {
    std::cout << "\n--- Gas name: " << gas_name << " ---" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Amount of substance = " << moles << " moles" << std::endl;
    std::cout << "Temperature = " << temperature << " K" << std::endl;
    std::cout << "Volume = " << volume << " m^3" << std::endl;
    std::cout << "Pressure = " << pressure << " Pa" << std::endl;
    std::cout << "Internal energy = " << internal_energy << " J" << std::endl;
    std::cout << "Heat capacity Cv = " << Cv << " J/K" << std::endl;
    std::cout << "Heat capacity Cp = " << Cp << " J/K" << std::endl;
    std::cout << "Gamma = " << gamma << std::endl;
    std::cout << "------------------------------------\n" << std::endl;
}

// Деструкотр (Тут в программе везде используются только стандартные типы данных. new не используется, так что delete не нужен).
VanDerWaalsGas::~VanDerWaalsGas() {
std::cout << "Object <<" << gas_name << ">> has been deleted." << std::endl;
}




// Оператор, нагревающий на 1 градус.
VanDerWaalsGas& VanDerWaalsGas::operator++() {
this->temperature += 1.0; 
this->update_pressure();
this->update_thermodynamics();
return *this;
}

// Оператор, охлаждающий на 1 градус.
VanDerWaalsGas& VanDerWaalsGas::operator--() {
    if (this->temperature > 1.0) {
        this->temperature -= 1.0;
        this->update_pressure();
        this->update_thermodynamics();
    }
    return *this;
}

// Постфиксный инкремент.
VanDerWaalsGas VanDerWaalsGas::operator++(int) {
    VanDerWaalsGas temp = *this;
    this->temperature += 1.0;
    this->update_pressure();
    this->update_thermodynamics();
    return temp;
}

// Постфиксный декремент.
VanDerWaalsGas VanDerWaalsGas::operator--(int) {
    VanDerWaalsGas temp = *this;
    if (this->temperature > 1.0) {
        this->temperature -= 1.0;
        this->update_pressure();
        this->update_thermodynamics();
    }
    return temp;
}


// Оператор (), выдающий давление при заданных объеме и температуре.
double VanDerWaalsGas::operator()(double v, double t) const {
if (!is_state_valid(v, t, this->moles)) {
    throw std::runtime_error("INVALID PARAMETERS FOR PRESSURE CALCULATION");
}
else{
    double effective_v = v - moles * b;
    return (moles * R * t) / effective_v - (a * moles * moles) / (v * v);
}
}



// Операторы сравнения.
bool VanDerWaalsGas::operator==(const VanDerWaalsGas& other) const {
    const double error = 0.00001;

    if (this->gas_name != other.gas_name) return false;
    if (std::abs(volume - other.volume) / volume > error) return false;
    if (std::abs(temperature - other.temperature) / temperature > error) return false;
    if (std::abs(moles - other.moles) / moles > error) return false;
    return true;
}

bool VanDerWaalsGas::operator!=(const VanDerWaalsGas& other) const {
    return !(*this == other);
}


// Оператор скалирования. Увеличивает объем и количество молей в заданное число раз, но не меняет состояние (T и P).
VanDerWaalsGas& VanDerWaalsGas::operator*=(double factor) {
    if (factor <= 0) {
        throw std::runtime_error("Scaling factor must be positive");
    }
    this->moles *= factor;
    this->volume *= factor;
    this->Cv = (this->degrees_of_freedom / 2.0) * this->moles * this->R;
    this->update_pressure();
    this->update_thermodynamics();
    return *this;
}

// Деление.
VanDerWaalsGas& VanDerWaalsGas::operator/=(double factor) {
    return (*this) *= (1.0 / factor);
}

std::ostream& operator<<(std::ostream& os, const VanDerWaalsGas& gas) {
    os << "\n--- Gas name: " << gas.gas_name << " ---" << std::endl
    << std::fixed << std::setprecision(4)
    << "Amount of substance = " << gas.moles << " moles" << std::endl
    << "Temperature = " << gas.temperature << " K" << std::endl
    << "Volume = " << gas.volume << " m^3" << std::endl
    << "Pressure = " << gas.pressure << " Pa" << std::endl
    << "Internal energy = " << gas.internal_energy << " J" << std::endl
    << "Heat capacity Cv = " << gas.Cv << " J/K" << std::endl
    << "Heat capacity Cp = " << gas.Cp << " J/K" << std::endl
    << "Gamma = " << gas.gamma << std::endl
    << "------------------------------------\n" << std::endl;
    return os; // Возвращаем поток для цепочки вызовов
}