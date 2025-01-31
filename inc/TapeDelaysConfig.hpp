#ifndef TAPEDELAYSCONFIG_HPP
#define TAPEDELAYSCONFIG_HPP

#include <string>
#include <unordered_map>
#include <cstdint>

class TapeConfig{
public:
    uint32_t read;
    uint32_t write;
    uint32_t shift;
    uint32_t rewind;

    static TapeConfig loadFromFile(const std::string& path);
};

#endif