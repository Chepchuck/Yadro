#include <iostream>
#include "Tape.hpp"
#include "TapeSorter.hpp"
#include "TapeConfig.hpp"

int main(int argc, char* argv[]){
    // Проверяем аргументы командной строки
    if (argc < 3){
        cerr << "Usage: " << argv[0] << " input_filename output_filename\n";
        return -1;
    }

    // Считываем конфиг
    auto config = TapeConfig::loadFromFile("config/delay.ini");
    // Записываем данные о задержках в параметры ленты
    Tape::delays = {config.read, config.write, config.shift, config.rewind};
    // Открываем исходный файл
    Tape input(argv[1]);
    // Открываем конечный файл
    Tape output(argv[2]);
    // Создаем объект сортировщика
    TapeSorter sorter(input.get_size(), input, output, "tmp");
    // Сортируем
    sorter.sort();
    // Готово)
    return 0;
}