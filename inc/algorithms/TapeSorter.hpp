#ifndef TAPESORTER_HPP
#define TAPESORTER_HPP

#include "tapeinterface.hpp"
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

namespace algorithms {
    // Класс для сортировки элементов с ленты
    template <typename T, typename U>
    class TapeSorter {
        size_t memoryLimit;     // Ограничение памяти для вспомогательных лент
        T& input;
        U& output;
        vector<unique_ptr<T>> tapesPtrs;

        // Разделение на временные ленты и их сортировка
        void splitAndSort();

        // Объединение временных лент в итоговую
        void merge();
    public:
        // Конструктор
        TapeSorter(size_t memoryLimit, T& in, U& out);
        // Комплексная сортировка
        void sort();
    };

    template <typename T, typename U>
    TapeSorter<T, U>::TapeSorter(const size_t memoryLimit, T& in, U& out)
        : memoryLimit(memoryLimit), input(in), output(out) {
        static_assert(is_base_of_v<ITape, T>, "Class T must be inherit from ITape!");
        static_assert(is_base_of_v<ITape, U>, "Class U must be inherit from ITape!");
    }

    template <typename T, typename U>
    void TapeSorter<T, U>::splitAndSort() {
        // Отвечает за максимальное количество элементов на временной ленте
        const size_t chunkElements = memoryLimit / sizeof(int32_t);
        // Буфер для временного хранения элементов с ленты
        vector<int32_t> buffer;

        // Проматываем исходную ленту в начало
        input.rewindToStart();
        /* В цикле последовательно проходимся по элементам исходной ленты и записываем их в буфер,
        как только достигается максимальное количество (==chunkElements), записываем данные из
        буфера в файл временной ленты. Очищаем буфер. Повторяем, пока не закончится исходная лента.*/
        while(!input.isEnd()){
            buffer.clear();
            for (size_t size = 0; size < chunkElements && !input.isEnd(); size++){
                buffer.push_back(input.read());
                input.moveForward();
            }

            std::sort(buffer.begin(), buffer.end());

            /* Я предполагаю, что у каждой реальной ленты должен быть хотя бы идентификатор */
            auto tempTape = make_unique<T>();
            // Сохраняем указатель на ленту для дальнейшего взаимодействия с ней
            for (const int32_t num : buffer){
                tempTape->write(num);
                tempTape->moveForward();
            }
            tapesPtrs.emplace_back(move(tempTape));
        }
    }

    template <typename T>
    struct MergeNode{
        int32_t value;
        T* tape;

        bool operator>(const MergeNode& other) const{
            return value > other.value;
        }
    };

    template <typename T, typename U>
    void TapeSorter<T, U>::merge(){
        // Приоритетная очередь, первый вытаскивается объект с минимальным значением
        priority_queue<MergeNode<T>, vector<MergeNode<T>>, greater<>> pq;

        /* В цикле поочереди открываем и создаем указатели на временные файлы лент.
        Первые значения каждой ленты (они же наименьшие) добавляем в приоритетную очередь
        вместе с указателем на ленту. */
        for (const auto &tape : tapesPtrs) {
            tape->rewindToStart();
            if (!tape->isEnd()){
                pq.push({tape->read(), tape.get()});
            }
        }

        /* В цикле достаем из очереди верхний элемент и записываем его на конечную ленту.
        Ленту, на которой был элемент, сдвигаем вперед и добавляем значение с текущей позиции
        в очередь. Повторяем, пока очередь не закончится. */
        while (!pq.empty()){
            auto [value, tape] = pq.top();
            pq.pop();

            output.write(value);
            output.moveForward();

            tape->moveForward();
            if (!tape->isEnd()){
                pq.push({tape->read(), tape});
            }
        }
    }

    template <typename T, typename U>
    void TapeSorter<T, U>::sort() {
        splitAndSort();
        merge();
        printf("Tape was sorted!\n");
    }
}

#endif
