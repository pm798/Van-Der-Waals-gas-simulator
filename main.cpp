#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <stdexcept>
#include "Chamber.h"
#include "VanDerWaalsGas.h"
#include "GasStorage.h"
#include "Operator.h"
#include "DataLogger.h"

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



    Chamber oxygen_tank("O2", 0.01, 300.0, 0.4, 1000000.0);

    oxygen_tank.info();
    
    // Нагреваем, пока не станет опасно
    oxygen_tank.heat(200.0); 
    oxygen_tank.info();


    GasStorage myLab("LFI Physics Lab");


    // Создаем разные камеры.
    Chamber tankA("N2", 0.05, 300.0, 2.0, 1500000.0);
    Chamber tankB("He", 0.02, 290.0, 1.5, 2000000.0);

    // Добавляем их в хранилище с именами.
    myLab.addChamber("Main Nitrogen", tankA);
    myLab.addChamber("High Pressure Helium", tankB);

    // Нагрев всех камер.
    myLab.heatAll(150.0);

    // Отчет о безопасности.
    myLab.safetyAudit();

    // Полный отчетю.
    myLab.fullInventoryReport();




    // Создаем лабораторию.
    GasStorage mfti_lab("Thermodynamics Lab");
    Operator chief("Ivan Ivanov", "MFTI-777");

    // Наполняем склад баллонами.
    Chamber tank1("H2", 0.1, 273.15, 5.0, 5000000.0);
    Chamber tank2("O2", 0.05, 290.0, 10.0, 8000000.0);
    
    mfti_lab.addChamber("Hydrogen_Primary", tank1);
    mfti_lab.addChamber("Oxygen_Support", tank2);

    // Оператор выполняет работу.
    chief.performMaintenance(mfti_lab);
    
    // Имитация внештатной ситуации.
    mfti_lab.heatAll(500.0);
    chief.createStatusReport(mfti_lab); 



    Operator scientist("Petr", "001");
    DataLogger logger("lab_results.txt");

    Chamber tank("N2", 0.02, 300.0, 1.0, 1000000.0);
    mfti_lab.addChamber("Tank_1", tank);

    logger.logCurrentState(mfti_lab); 

    scientist.performMaintenance(mfti_lab);

    return 0;
}