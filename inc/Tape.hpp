#ifndef TAPE_HPP
#define TAPE_HPP

#include "tapeinterface.hpp"
#include <fstream>
#include <thread>
#include <iostream>
#include <filesystem>


using namespace std;

// Класс, имитирующий работу ленты
class Tape : public ITape{
    fstream file;           // Файл входной последовательности 4-байтовых элементов
    string filename;        // Название файла
    size_t position = 0;    // Текущая позиция магнитной головки относительно начала ленты
    size_t size;            // Размер ленты (в элементах)
    
    // Статический метод класса для применения задержек перед каждой операцией
    static void applyDelay(const uint32_t ms) {
        this_thread::sleep_for(chrono::microseconds(ms));
    }
public:
    // Структура для хранения задержек разных видов действий
    static struct Delays
    {
        uint32_t read;
        uint32_t write;
        uint32_t shift;
        uint32_t rewind;
    } delays;

    // Конструктор. Принимает на вход название файла ленты.
    explicit Tape(const std::string& filename);
    // Деструктор
    ~Tape() override;

    // Получение данных о размере ленты.
    size_t get_size() const;
    // Получение данных о названии файла.
    string get_filename() const;

    // Чтение элемента с текущей позиции ленты.
    int32_t read() override;
    // Запись элемента в текущую позицию ленты.
    void write(int32_t data) override;
    // Сдвиг ленты на 1 элемент вперед
    void moveForward() override;
    // Сдвиг ленты на 1 элемент назад.
    void moveBackward() override;
    // Возврат ленты в начальное положение. (position = 0)
    void rewindToStart() override;
    // Флаг окончания ленты. (position == size)
    bool isEnd() const override;
};

#endif