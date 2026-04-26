#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <stdexcept>

#include "VanDerWaalsGas.h"




int main() {
    // Пример: 1 моль азота в объеме 0.025 м^3 при температуре 300К.

    VanDerWaalsGas gas_1("N2", 0.025, 300.0, 1.0);
    
    std::cout << "Initial state:";
    gas_1.show_gas_info();

    std::cout << "Heating by 50 degrees in the same capacity..." << std::endl << std::endl;
    gas_1.isochoricHeating(50.0);

    std::cout << "Current state:";
    gas_1.show_gas_info();

    std::cout << "Compressing by 0.005 m^3 while contacting a thermostate..." << std::endl << std::endl;
    gas_1.isothermalCompression(-0.005);

    std::cout << "Current state:";
    gas_1.show_gas_info();

    std::cout << std::endl << std::endl << std::endl;
    std::cout << "------------------------------------------------------------------------\n" << std::endl;


    // Пример 2: Углекислого газа нет в таблице. Задаем коэффициенты a = 0.364, b = 0.00004267, 6 степеней свободы.
    std::cout << "Another gas" << std::endl;

    VanDerWaalsGas gas_2("CO2", 0.364, 0.00004267, 6, 0.05, 293.15, 10.0);

    std::cout << "Initial state:";
    gas_2.show_gas_info();

    std::cout << "Expanding the gas by 0.01 m^3 in a shell with heat isolation..." << std::endl;
    gas_2.adiabaticProcess(0.01);

    gas_2.show_gas_info();

    // Примеры работы операторов.
    std::cout << "Adding 1K to the temperature..." << std::endl;
    ++gas_2;
    std::cout << "Show information about it again using operator:" << std::endl;
    std::cout << gas_2;
    
    double P = gas_2(0.05, 275);
    std::cout << "Calculated P = " << P << " Pa" << std::endl;



    // Создаем и сравниваем газы.
    VanDerWaalsGas O2_1("O2", 0.02, 300.0, 1.0);
    VanDerWaalsGas O2_2("O2", 0.02, 300.0, 1.0);
    VanDerWaalsGas O2_3("O2", 0.04, 300.0, 1.0);

    if (O2_1 == O2_2) {
        std::cout << "Identical." << std::endl;
    }
    else
    {
        std::cout << "Not identical." << std::endl;
    }

    if (O2_1 == O2_3) {
        std::cout << "Identical." << std::endl;
    }
    else
    {
        std::cout << "Not identical." << std::endl;
    }

    VanDerWaalsGas helium_1("He", 0.025, 300.0, 1.0);


    helium_1.show_gas_info();
    helium_1 *= 2;
    helium_1.show_gas_info();
    return 0;
}