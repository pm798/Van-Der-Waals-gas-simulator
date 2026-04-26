#ifndef VANDERWAALSGAS_H
#define VANDERWAALSGAS_H

#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <iomanip>
#include <stdexcept>

namespace GasData {
    struct GasConstants {
        double a;
        double b;
        int degrees_of_freedom;
    };
    extern const std::map<std::string, GasConstants> LOOKUP;
}

class VanDerWaalsGas {
private:
    std::string gas_name;
    const double R = 8.31;
    double a, b, Cv, Cp, gamma, moles, pressure, volume, temperature, internal_energy, degrees_of_freedom;

    bool is_state_valid(double v, double t, double n) const;
    double get_cohesion_pressure() const;
    void update_pressure();
    void update_thermodynamics();

public:
    VanDerWaalsGas(std::string name, double v, double t, double n);
    VanDerWaalsGas(std::string name, double custom_a, double custom_b, int df, double v, double t, double n);
    ~VanDerWaalsGas();

    void isochoricHeating(double delta_T);
    void isobaricExpansion(double delta_V);
    void isothermalCompression(double delta_V);
    void adiabaticProcess(double delta_V);
    void addSubstance(double extra_moles);
    void show_gas_info() const;

    friend std::ostream& operator<<(std::ostream& os, const VanDerWaalsGas& gas);
    VanDerWaalsGas& operator++();
    VanDerWaalsGas& operator--();
    VanDerWaalsGas operator++(int);
    VanDerWaalsGas operator--(int);
    double operator()(double v, double t) const;
    bool operator==(const VanDerWaalsGas& other) const;
    bool operator!=(const VanDerWaalsGas& other) const;
    VanDerWaalsGas& operator*=(double factor);
    VanDerWaalsGas& operator/=(double factor);
};

#endif