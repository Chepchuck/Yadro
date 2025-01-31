<<<<<<< HEAD
#include "inc/TapeSorter.hpp"
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

        string tempName = tmpDir + "/temp_" + to_string(tempFiles.size()) + "_" + to_string(i);

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
    merge(tempFiles, "output_merged");

    for (const auto& name : tempFiles){
        filesystem::remove(name);
    }
=======
#include "inc/TapeSorter.hpp"
#include <algorithm>
#include <queue>

TapeSorter::TapeSorter(size_t length, FileTape& in, FileTape& out, const string& tmp)
  : maxTmpLength(length),
    input(in),
    output(out),
    tmpDir(move(tmp))
{}


void TapeSorter::splitAndSort(vector<string>& tempFiles) {
    const size_t chunkElements = maxTmpLength / sizeof(int32_t);
    vector<int32_t> buffer;

    input.rewindToStart();
    while(!input.isEnd()){
        buffer.clear();
        for (size_t i = 0; i < chunkElements && !input.isEnd(); i++){
            buffer.push_back(input.read());
            input.moveForward();
        }

        std::sort(buffer.begin(), buffer.end());

        string tempName = tmpDir + "/temp_" + to_string(tempFiles.size());

        tempFiles.push_back(tempName);

        FileTape tempTape(tempName, input.delays);
        for (int32_t num : buffer){
            tempTape.write(num);
            tempTape.moveForward();
        }
    }
}

struct MergeNode{
    int32_t value;
    FileTape* tape;

    bool operator>(const MergeNode& other) const{
        return value > other.value;
    }
};

void TapeSorter::merge(const vector<string>& files, const string& out){
    priority_queue<MergeNode, vector<MergeNode>, greater<>> pq;
    vector<unique_ptr<FileTape>> tapes;

    for (const auto& name : files) {
        auto tape = make_unique<FileTape>(name, input.delays);
        tape->rewindToStart();
        if (!tape->isEnd()){
            pq.push({tape->read(), tape.get()});
            tapes.emplace_back(move(tape));
        }
    }
    
    FileTape outTape(out, input.delays);
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
    merge(tempFiles, "output_merged");

    for (const auto& name : tempFiles){
        filesystem::remove(name);
    }
>>>>>>> 7c37bcd5dbeab3a44a59019d8425f5bfbb5943ae
}