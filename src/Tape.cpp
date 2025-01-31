#include "inc/Tape.hpp"
#include "inc/TapeDelaysConfig.hpp"
#include <iostream>
#include <filesystem>

using namespace std;

Tape::Tape(const string& filename){
    file.open(filename, ios::in | ios::out | ios::binary | ios::ate);
    if (!file){
        file.open(filename, ios::out);
        file.close();
        file.open(filename, ios::in | ios::out | ios::binary | ios::ate);
    }
    size = filesystem::file_size(filename) / sizeof(int32_t);
    file.seekg(0);
}

Tape::~Tape() {
    if (file.is_open()) file.close();
}

size_t Tape::get_size(){
    return size;
}

int32_t Tape::read() {
    applyDelay(delays.read);
    int32_t value;
    file.seekg(position * sizeof(int32_t));
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

void Tape::write(int32_t data){
    applyDelay(delays.write);
    file.seekp(position * sizeof(int32_t));
    file.write(reinterpret_cast<const char*>(&data), sizeof(data));
    if (position >= size) size++;
}

void Tape::moveBackward(){
    if (position > 0) {
        applyDelay(delays.shift);
        position--;
    }
}

void Tape::moveForward(){
    if (position < size){
        applyDelay(delays.shift);
        position++;
    }
}

void Tape::rewindToStart() {
    applyDelay(delays.rewind);
    position = 0;
}

bool Tape::isEnd() const{
    return position >= size;
}