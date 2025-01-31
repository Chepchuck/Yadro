#include <iostream>
#include "Tape.hpp"
#include "TapeSorter.hpp"
#include "TapeDelaysConfig.hpp"

int main(int argc, char* argv[]){
    if (argc < 3){
        cerr << "Usage: " << argv[0] << " input output";
        return -1;
    }

    auto config = TapeConfig::loadFromFile("config/delay.ini");
    Tape::delays = {config.read, config.write, config.shift, config.rewind};
    Tape input(argv[1]);
    Tape output(argv[2]);
    TapeSorter sorter(input.get_size(), input, output, "tmp");
    sorter.sort();

    return 0;
}