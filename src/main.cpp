#include <iostream>
#include <optional>

#include "FileTape.hpp"
#include "algorithms/TapeSorter.hpp"
#include "TapeConfig.hpp"

int main(int argc, char* argv[]){
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " input_filename output_filename\n";
        return -1;
    }
    auto config = TapeConfig::loadFromFile("config/delay.ini");
    FileTape::delays = {config.read, config.write, config.shift, config.rewind};

    // Открываем исходный файл, если его нет - выбрасывается исключение.
    FileTape input(argv[1]);

    /* Пробуем открыть конечный файл, если его нет, то уже не так страшно, можно и создать. */
    optional<FileTape> output;
    try {
        output.emplace(argv[2]);
    } catch (const exception& e) {
        cerr << e.what() << "\n";
        fstream file;
        file.open(argv[2], ios::out);
        file.close();
        output.emplace(argv[2]);
    }

    algorithms::TapeSorter<FileTape, FileTape> sorter(input.get_size(), input, output.value());
    sorter.sort();

    return 0;
}