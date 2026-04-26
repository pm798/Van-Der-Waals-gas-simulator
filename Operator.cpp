#include "Operator.h"
#include <iostream>
#include <ctime>

Operator::Operator(std::string n, std::string id) : name(n), employee_id(id) {}

// Управление хранилищем.
void Operator::performMaintenance(GasStorage& storage) {
    std::cout << "Operator " << name << " (ID: " << employee_id << ") starting maintenance." << std::endl;
    
    storage.safetyAudit();
    
    std::cout << "Calibrating sensors..." << std::endl;
    storage.heatAll(5.0);
    
    std::cout << "Maintenance complete." << std::endl;
}

// Охладить хранилище.
void Operator::emergencyCooling(GasStorage& storage, double temp_drop) {
    std::cout << "!!! EMERGENCY COOLING INITIATED BY OPERATOR " << name << " !!!" << std::endl;
    storage.heatAll(-temp_drop);
}

// Написать отчет.
void Operator::createStatusReport(const GasStorage& storage) const {
    std::time_t now = std::time(0);
    char* dt = std::ctime(&now);

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "OFFICIAL LABORATORY REPORT" << std::endl;
    std::cout << "Responsible Operator: " << name << std::endl;
    std::cout << "Timestamp: " << dt;
    
    storage.fullInventoryReport();
    std::cout << "------------------------------------------" << std::endl;
}