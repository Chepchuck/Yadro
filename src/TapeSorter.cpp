#include "TapeSorter.hpp"
#include <algorithm>
#include <queue>

TapeSorter::TapeSorter(size_t length, Tape& in, Tape& out, const string& tmp)
  : memoryLimit(length),
    input(in),
    output(out),
    tmpDir(move(tmp))
{}

void TapeSorter::splitAndSort(vector<string>& tempFiles) {
    const size_t chunkElements = memoryLimit / sizeof(int32_t);
    vector<int32_t> buffer;

    input.rewindToStart();
    int i = 0;
    while(!input.isEnd()){
        buffer.clear();
        for (size_t i = 0; i < chunkElements && !input.isEnd(); i++){
            buffer.push_back(input.read());
            input.moveForward();
        }

        std::sort(buffer.begin(), buffer.end());

        string tempName = tmpDir + "/temp_" + to_string(tempFiles.size()) + ".bin";

        tempFiles.push_back(tempName);

        Tape tempTape(tempName);
        for (int32_t num : buffer){
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
    priority_queue<MergeNode, vector<MergeNode>, greater<MergeNode>> pq;
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
        auto node = pq.top();
        pq.pop();

        outTape.write(node.value);
        outTape.moveForward();

        node.tape->moveForward();
        if (!node.tape->isEnd()){
            pq.push({node.tape->read(), node.tape});
        }
    }
}

void TapeSorter::sort(){
    vector<string> tempFiles;
    splitAndSort(tempFiles);
    merge(tempFiles, output.get_filename());
    printf("Tape was sorted! Result of sort contains in output.bin.\n");
    // for (const auto& name : tempFiles){
    //     filesystem::remove(name);
    // }
}