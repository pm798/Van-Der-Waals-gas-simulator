#include "GasStorage.h"
#include <iostream>

GasStorage::GasStorage(std::string name) : storage_name(name) {}

// Добавляет новую камеру в хранилище.
void GasStorage::addChamber(std::string label, const Chamber& chamber) {
    inventory.insert({label, chamber});
    std::cout << "Added chamber '" << label << "' to storage '" << storage_name << "'." << std::endl;
}
// Удаление камеру.
void GasStorage::removeChamber(const std::string& label) {
    if (inventory.erase(label)) {
        std::cout << "Chamber '" << label << "' removed." << std::endl;
    } else {
        std::cout << "Chamber '" << label << "' not found." << std::endl;
    }
}
// Нагревает все камеры в хранилище.
void GasStorage::heatAll(double delta_T) {
    std::cout << "\n--- Mass heating in " << storage_name << " by " << delta_T << " K ---" << std::endl;
    for (auto& [label, chamber] : inventory) {
        std::cout << "Processing [" << label << "]:" << std::endl;
        chamber.heat(delta_T);
    }
}

// Проверяет все баллоны на критическое давление.
void GasStorage::safetyAudit() const {
    std::cout << "Checking" << storage_name << std::endl;
    bool all_safe = true;
    for (const auto& [label, chamber] : inventory) {
        if (!chamber.is_safe()) {
            std::cout << "Chamber '" << label << "' is at risk!" << std::endl;
            all_safe = false;
        }
    }
    if (all_safe) std::cout << "All chambers are safe." << std::endl;
}
// Получение информации.
void GasStorage::fullInventoryReport() const {
    std::cout << "REPORT: " << storage_name << std::endl;
    for (const auto& [label, chamber] : inventory) {
        std::cout << "Label: " << label;
        chamber.info();
    }
    std::cout << std::endl;
}

Chamber& GasStorage::getChamber(const std::string& label) {
    return inventory.at(label);
}