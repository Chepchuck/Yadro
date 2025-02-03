#include "TapeSorter.hpp"

TapeSorter::TapeSorter(const size_t memoryLimit, Tape& in, Tape& out, string  tmp)
  : memoryLimit(memoryLimit),
    input(in),
    output(out),
    tmpDir(move(tmp))
{}

void TapeSorter::splitAndSort(vector<string>& tempFiles) const {
    // Отвечает за максимальное количество элементов на временной ленте
    const size_t chunkElements = memoryLimit / sizeof(int32_t);
    // Буффер для временного хранения элементов с ленты
    vector<int32_t> buffer;

    // Проматываем исходную ленту в начало
    input.rewindToStart();
    /* В цикле последовательно проходимся по элементам исходной ленты и записываем их в буфер,
    как только достигается максимальное количество (==chunkElements), записываем данные из 
    буфера в файл временной ленты. Очищаем буффер. Повторяем, пока не закончится исходная лента.*/
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
    }
}

// Структура для удобного сравнения в приоритетной очереди
struct MergeNode{
    int32_t value;
    Tape* tape;

    bool operator>(const MergeNode& other) const{
        return value > other.value;
    }
};

void TapeSorter::merge(const vector<string>& files, const string& out){
    // Приоритетная очередь, первый вытаскивается объект с минимальным значением
    priority_queue<MergeNode, vector<MergeNode>, greater<>> pq;
    // Вспомогательный вектор для хранения ссылок
    vector<unique_ptr<Tape>> tapes;

    /* В цикле поочереди открываем и создаем указатели на временные файлы лент. 
    Первые значения каждой ленты (они же наименьшие) добавляем в приоритетную очередь
    вместе с указателем на ленту. */
    for (const auto& name : files) {
        auto tape = make_unique<Tape>(name);
        tape->rewindToStart();
        if (!tape->isEnd()){
            pq.push({tape->read(), tape.get()});
            // Указатели на ленты добавляем в вектор, чтобы они не уничтожались после итерации цикла
            tapes.emplace_back(move(tape));
        }
    }
    
    // Открываем файл конечной ленты
    Tape outTape(out);
    /* В цикле достаем из очереди верхний элемент и записываем его на конечную ленту.
    Ленту, на которой был элемент, сдвигаем вперед и добавляем значение с текущей позиции 
    в очередь. Повторяем, пока очередь не закончится. */
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

    /* Можно убрать комменты, чтобы временные файлы удалялись после сортировки */
    // for (const auto& name : tempFiles){
    //     filesystem::remove(name);
    // }
}
