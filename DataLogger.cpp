#include "DataLogger.h"
#include <fstream>
#include <iostream>
#include <ctime>

DataLogger::DataLogger(std::string filename) : log_filename(filename) {}

void DataLogger::logCurrentState(const GasStorage& storage) {
    std::ofstream file(log_filename, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open log file." << std::endl;
        return;
    }

    std::time_t now = std::time(0);
    
    file << "--- Log Entry: " << std::ctime(&now);
    file << "Storage Name: " << storage.getName() << std::endl;
    file << "Status: Operational" << std::endl;
    file << "------------------------------------------" << std::endl;
    
    file.close();
    std::cout << "Data for '" << storage.getName() << " logged." << std::endl;
}