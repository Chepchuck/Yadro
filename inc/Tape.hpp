#ifndef TAPE_HPP
#define TAPE_HPP

#include "tapeinterface.hpp"
#include <fstream>
#include <thread>
#include <iostream>
#include <filesystem>


using namespace std;

class Tape : public ITape{
    fstream file;
    string filename;
    size_t position = 0;
    size_t size;
    
    static void applyDelay(const uint32_t ms) {
        this_thread::sleep_for(chrono::microseconds(ms));
    }
public:
    static struct Delays
    {
        uint32_t read;
        uint32_t write;
        uint32_t shift;
        uint32_t rewind;
    } delays;

    explicit Tape(const std::string& filename);
    ~Tape() override;

    size_t get_size() const;
    string get_filename() const;

    int32_t read() override;
    void write(int32_t data) override;
    void moveForward() override;
    void moveBackward() override;
    void rewindToStart() override;
    bool isEnd() const override;
};

#endif