#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <string>
#include "GasStorage.h"
// Класс, создающй лог хранилища. Тип связи - зависимость.
class DataLogger {
private:
    std::string log_filename;

public:
    explicit DataLogger(std::string filename);

    void logCurrentState(const GasStorage& storage);
};

#endif