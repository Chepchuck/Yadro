#include "TapeDelaysConfig.hpp"
#include <fstream>
#include <stdexcept>
#include <string>

TapeConfig TapeConfig::loadFromFile(const std::string& path){
    TapeConfig config{};
    std::ifstream file(path);
    std::unordered_map<std::string, uint32_t> params;

    if (!file) throw std::runtime_error("Config file not found");

    std::string line;
    while (std::getline(file, line)){
        size_t delim = line.find('=');
        if (delim == std::string::npos) continue;

        std::string key = line.substr(0, delim);
        uint32_t value = std::stoul(line.substr(delim+1));
        params[key] = value;
    }
    
    config.read = params.count("read_delay") ? params["read_delay"] : 0;
    config.read = params.count("write_delay") ? params["write_delay"] : 0;
    config.read = params.count("shift_delay") ? params["shift_delay"] : 0;
    config.read = params.count("rewind_delay") ? params["rewind_delay"] : 0;

    return config;
}