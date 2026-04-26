#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <vector>
#include "GasStorage.h"
// Класс оператора. Ассоциация с хранилищем.
class Operator {
private:
    std::string name;
    std::string employee_id;

public:
    Operator(std::string n, std::string id);

    void performMaintenance(GasStorage& storage);
    void emergencyCooling(GasStorage& storage, double temp_drop);
    
    void createStatusReport(const GasStorage& storage) const;
    
    std::string getName() const { return name; }
};

#endif