#ifndef TAPESORTER_HPP
#define TAPESORTER_HPP

#include "Tape.hpp"
#include "TapeDelaysConfig.hpp"
#include <vector>
#include <string>
#include <filesystem>

using namespace std;

class TapeSorter {
    size_t memoryLimit;
    Tape& input;
    Tape& output;
    string tmpDir;

    void splitAndSort(vector<string>& tempFiles) const;
    static void merge(const vector<string>& files, const string& out);

public:
    TapeSorter(size_t memoryLimit, Tape& in, Tape& out, string  tmp);
    void sort() const;
};

#endif