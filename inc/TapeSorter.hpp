#ifndef TAPESORTER_HPP
#define TAPESORTER_HPP

#include "Tape.hpp"
#include "TapeConfig.hpp"
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

// Класс для сортировки эдементов с ленты
class TapeSorter {
    size_t memoryLimit;     // Ограничение памяти для вспомогательных лент
    Tape& input;            // Ссылка на исходную ленту
    Tape& output;           // Ссылка на итоговую ленту (с отсортированными элементами) 
    string tmpDir;          // Путь для хранения файлов временных лент

    // Разделение и сортировка временных файлов
    void splitAndSort(vector<string>& tempFiles) const;
    // Объединение временных лент в итоговую
    static void merge(const vector<string>& files, const string& out);

public:
    // Конструктор 
    TapeSorter(size_t memoryLimit, Tape& in, Tape& out, string  tmp);
    // Комплексная сортировка 
    void sort() const;
};

#endif