#include "TapeSorter.hpp"
#include <algorithm>
#include <queue>
#include <utility>

TapeSorter::TapeSorter(const size_t memoryLimit, Tape& in, Tape& out, string  tmp)
  : memoryLimit(memoryLimit),
    input(in),
    output(out),
    tmpDir(std::move(tmp))
{}

void TapeSorter::splitAndSort(vector<string>& tempFiles) const {
    const size_t chunkElements = memoryLimit / sizeof(int32_t);
    vector<int32_t> buffer;

    input.rewindToStart();
    int i = 0;
    while(!input.isEnd()){
        buffer.clear();
        for (size_t size = 0; size < chunkElements && !input.isEnd(); size++){
            buffer.push_back(input.read());
            input.moveForward();
        }

        std::sort(buffer.begin(), buffer.end());

        string tempName = tmpDir + "/temp_" + to_string(tempFiles.size()) + ".bin";

        tempFiles.push_back(tempName);

        Tape tempTape(tempName);
        for (const int32_t num : buffer){
            tempTape.write(num);
            tempTape.moveForward();
        }
        i++;
    }
}

struct MergeNode{
    int32_t value;
    Tape* tape;

    bool operator>(const MergeNode& other) const{
        return value > other.value;
    }
};

void TapeSorter::merge(const vector<string>& files, const string& out){
    priority_queue<MergeNode, vector<MergeNode>, greater<>> pq;
    vector<unique_ptr<Tape>> tapes;

    for (const auto& name : files) {
        auto tape = make_unique<Tape>(name);
        tape->rewindToStart();
        if (!tape->isEnd()){
            pq.push({tape->read(), tape.get()});
            tapes.emplace_back(move(tape));
        }
    }
    
    Tape outTape(out);
    while (!pq.empty()){
        auto [value, tape] = pq.top();
        pq.pop();

        outTape.write(value);
        outTape.moveForward();

        tape->moveForward();
        if (!tape->isEnd()){
            pq.push({tape->read(), tape});
        }
    }
}

void TapeSorter::sort() const {
    vector<string> tempFiles;
    splitAndSort(tempFiles);
    merge(tempFiles, output.get_filename());
    printf("Tape was sorted! Result of sort contains in output.bin.\n");
    // for (const auto& name : tempFiles){
    //     filesystem::remove(name);
    // }
}
