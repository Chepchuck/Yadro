#ifndef TAPEDELAYSCONFIG_HPP
#define TAPEDELAYSCONFIG_HPP

#include <string>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

// Класс для конфигурации задержек
class TapeConfig{
public:
    uint32_t read;
    uint32_t write;
    uint32_t shift;
    uint32_t rewind;

    // Чтение данных из файла конфигурации
    static TapeConfig loadFromFile(const std::string& path);
};

#endif