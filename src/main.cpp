<<<<<<< HEAD
#include <iostream>
#include "inc/TapeSorter.hpp"
#include "inc/Tape.hpp"
#include "inc/TapeDelaysConfig.hpp"

int main(int argc, char* argv[]){
    if (argc < 3){
        cerr << "Usage: " << argv[0] << " input output";
        return -1;
    }

    auto config = TapeConfig::loadFromFile("config/delay.ini");
    Tape::set_delays({config.read, config.write, config.shift, config.rewind});
    Tape input(argv[1]);
    Tape output(argv[2]);
    TapeSorter sorter(input.get_size(), input, output, "tmp");
    sorter.sort();

    return 0;
=======
#include <iostream>
#include "inc/TapeSorter.hpp"
#include "inc/FileTape.hpp"
#include "inc/TapeDelaysConfig.hpp"

int main(int argc, char* argv[]){
    if (argc < 3){
        cerr << "Usage: " << argv[0] << " input output";
        return -1;
    }

    auto config = TapeConfig::loadFromFile("config/delay.ini");
    FileTape input(argv[1], {config.read, config.write, config.shift, config.rewind});
    FileTape output(argv[2], {config.read, config.write, config.shift, config.rewind});

    TapeSorter sorter(input.get_size(), input, output, "tmp");
    sorter.sort();

    return 0;
>>>>>>> 7c37bcd5dbeab3a44a59019d8425f5bfbb5943ae
}