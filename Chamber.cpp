#include "Chamber.h"
#include <iostream>


// Конструктор, который заправляет баллон конкретным газом.
Chamber::Chamber(std::string gas_name, double v, double t, double n, double p_limit)
    : volume(v), max_pressure(p_limit), 
      contents(gas_name, v, t, n)
{}

// Проверка того, что давление не превышает максимально допустимое.
bool Chamber::is_safe() const {
    return contents.getPressure() < max_pressure;
}

// Изохорное нагревание камеры с газом.
void Chamber::heat(double delta_T) {
    std::cout << "Heating chamber by " << delta_T << " K..." << std::endl;
    contents.isochoricHeating(delta_T);
    
    if (!is_safe()) {
        std::cout << "PRESSURE (" << contents.getPressure() << " Pa) EXCEEDED LIMIT!" << std::endl;
    }
}
// Выдает информацию.
void Chamber::info() const {
    std::cout << "CHAMBER STATUS:" << std::endl;
    std::cout << "Volume = " << volume << " m^3" << std::endl;
    std::cout << "Max Pressure = " << max_pressure << " Pa" << std::endl;
    std::cout << "Safety Status = " << (is_safe() ? "OK" : "CRITICAL") << std::endl;
    std::cout << contents;
    std::cout << std::endl;
}