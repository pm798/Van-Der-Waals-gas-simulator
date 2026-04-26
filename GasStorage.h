#ifndef GASSTORAGE_H
#define GASSTORAGE_H

#include <map>
#include <string>
#include "Chamber.h"
// Класс хранилища камер с газом. Тип связи - агрегация по отношению к камерам.
class GasStorage {
private:
    std::string storage_name;
    std::map<std::string, Chamber> inventory;

public:
    explicit GasStorage(std::string name);
    
    
    void addChamber(std::string label, const Chamber& chamber);

    
    void removeChamber(const std::string& label);

    void heatAll(double delta_T);
    void safetyAudit() const;

    
    void fullInventoryReport() const;
    
    Chamber& getChamber(const std::string& label);
    std::string getName() const { return storage_name; }
};

#endif