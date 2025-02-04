#ifndef TAPESORTER_HPP
#define TAPESORTER_HPP

#include "tapeinterface.hpp"
#include "TapeConfig.hpp"
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

// Класс для сортировки эдементов с ленты
template <typename T>
class TapeSorter {
    size_t memoryLimit;     // Ограничение памяти для вспомогательных лент
    T& input;            // Ссылка на исходную ленту
    T& output;           // Ссылка на итоговую ленту (с отсортированными элементами) 
    vector<unique_ptr<T>> tapesPtrs;
    // string tmpDir;          // Путь для хранения файлов временных лент

    // Разделение и сортировка временных файлов
    void splitAndSort() const;
    // Объединение временных лент в итоговую
    void merge();
public:
    // Конструктор 
    TapeSorter(const size_t memoryLimit, T& in, T& out);
    vector<unique_ptr<T>>& getTapesPointers() const;
    // Комплексная сортировка 
    void sort() const;
};

template <typename T>
TapeSorter<T>::TapeSorter(const size_t memoryLimit, T& in, T& out)
  : memoryLimit(memoryLimit)
{
    static_assert(is_base_of<ITape, T>::value, "Variable of T class must inherit from ITape!");
    input(in);
    output(out);
}

#endif