<<<<<<< HEAD:inc/Tape.hpp
#ifndef TAPE_HPP
#define TAPE_HPP

#include "interfaces/tapeinterface.hpp"
#include "TapeSorter.hpp"
#include <fstream>
#include <thread>

using namespace std;

class Tape : public TapeInterface{
    static struct Delays
    {
        uint32_t read;
        uint32_t write;
        uint32_t shift;
        uint32_t rewind;
    } delays;

    fstream file;
    size_t position = 0;
    size_t size;
    
    void applyDelay(uint32_t ms) const{
        this_thread::sleep_for(chrono::microseconds(ms));
    }
public:
    Tape(const std::string& filename);
    Tape();

    static void set_delays(const Delays config_delays){ delays = config_delays; };
    size_t get_size() override;
    int32_t read() override;
    void write(int32_t data) override;
    void moveForward() override;
    void moveBackward() override;
    void rewindToStart() override;
    bool isEnd() const override;
};

=======
#ifndef FILETAPE_HPP
#define FILETAPE_HPP

#include "interfaces/tapeinterface.hpp"
#include "TapeSorter.hpp"
#include <fstream>
#include <thread>

using namespace std;

class FileTape : public TapeInterface{
    friend TapeSorter;
    fstream file;
    size_t position = 0;
    size_t size;
    struct Delays
    {
        uint32_t read;
        uint32_t write;
        uint32_t shift;
        uint32_t rewind;
    } delays;
    
    void applyDelay(uint32_t ms) const{
        this_thread::sleep_for(chrono::microseconds(ms));
    }
public:
    FileTape(const std::string& filename, const Delays& delays);
    ~FileTape();

    size_t get_size() override;
    int32_t read() override;
    void write(int32_t data) override;
    void moveForward() override;
    void moveBackward() override;
    void rewindToStart() override;
    bool isEnd() const override;
};

>>>>>>> 7c37bcd5dbeab3a44a59019d8425f5bfbb5943ae:inc/FileTape.hpp
#endif