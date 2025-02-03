#include "TapeConfig.hpp"

/* Реализация методов класса TapeConfig */

TapeConfig TapeConfig::loadFromFile(const string& path){
    TapeConfig config{};            
    ifstream file(path);            // Создаем input file stream для чтения конфига
    unordered_map<string, uint32_t> params;     // Хэш мапа для хранения параметров

    if (!file) throw runtime_error("Config file not found");

    string line;
    /*Читаем построчно файл и разделяем по символу '=', если находим, 
    левое значение используем как ключ, правое - значение
     и записываем в ранее созданныю мапу, иначе переходим к следующей строчке*/ 
    while (getline(file, line)){
        size_t delim = line.find('=');
        if (delim == string::npos) continue;

        string key = line.substr(0, delim);
        uint32_t value = stoul(line.substr(delim+1));
        params[key] = value;
    }
    
    config.read = params.count("read_delay") ? params["read_delay"] : 0;
    config.read = params.count("write_delay") ? params["write_delay"] : 0;
    config.read = params.count("shift_delay") ? params["shift_delay"] : 0;
    config.read = params.count("rewind_delay") ? params["rewind_delay"] : 0;

    return config;
}