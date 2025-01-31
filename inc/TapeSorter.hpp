<<<<<<< HEAD
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
    string tmpDir;

    void splitAndSort(vector<string>& tempFiles);
    void merge(const vector<string>& files, const string& out);

public:
    TapeSorter(size_t memoryLimit, Tape& in, Tape& out, const string& tmp);
    void sort();
};

=======
#ifndef TAPESORTER_HPP
#define TAPESORTER_HPP

#include "FileTape.hpp"
#include "TapeDelaysConfig.hpp"
#include <vector>
#include <string>
#include <filesystem>

class TapeSorter {
    size_t maxTmpLength;
    FileTape& input;
    FileTape& output;
    string tmpDir;

    void splitAndSort(vector<string>& tempFiles);
    void merge(const vector<string>& files, const string& out);

public:
    TapeSorter(size_t memory, FileTape& in, FileTape& out, const string& tmp);
    void sort();
};

>>>>>>> 7c37bcd5dbeab3a44a59019d8425f5bfbb5943ae
#endif