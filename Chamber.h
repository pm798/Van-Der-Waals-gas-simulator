#ifndef CHAMBER_H
#define CHAMBER_H

#include "VanDerWaalsGas.h"
// Класс камеры с газом. Связь - композиция.
class Chamber {
private:
    double volume;
    double max_pressure;
    VanDerWaalsGas contents;

public:
    Chamber(std::string gas_name, double v, double t, double n, double p_limit);
    
    void heat(double delta_T);
    void info() const;
    bool is_safe() const;
};

#endif