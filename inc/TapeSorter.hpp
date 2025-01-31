#ifndef TAPESORTER_HPP
#define TAPESORTER_HPP

#include "Tape.hpp"
#include "TapeDelaysConfig.hpp"
#include <vector>
#include <string>
#include <filesystem>

class TapeSorter {
    size_t memoryLimit;
    Tape& input;
    Tape& output;
    std::string tmpDir;

    void splitAndSort(std::vector<std::string>& tempFiles);
    void merge(const std::vector<std::string>& files, const std::string& out);

public:
    TapeSorter(size_t memoryLimit, Tape& in, Tape& out, const std::string& tmp);
    void sort();
};

#endif