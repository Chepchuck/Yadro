#include "Tape.hpp"
#include "TapeConfig.hpp"

/* Реализация методов класса Tape */

// Выделение памяти для хранения данных о задержках
Tape::Delays Tape::delays;          

Tape::Tape(const string& filename){
    printf("Open file: %s.\n ", filename.c_str());
    
    // Открываем файл на чтение и запись в бинарном режиме
    file.open(filename, ios::in | ios::out | ios::binary | ios::ate);

    // Если файл не был открыт, создаем и открывем заново с теми же привилегиями и режимом
    if (!file){
        printf("File not found! Create: %s.\n", filename.c_str());
        // Создаем
        file.open(filename, ios::out);      
        file.close();                                                           
        // Снова открываем только что созданный файл
        file.open(filename, ios::in | ios::out | ios::binary | ios::ate);  
    }
    // Сохраняем название
    this->filename = filename;

    // Вычисляем размер
    size = filesystem::file_size(filename) / sizeof(int32_t);   
    printf("%s size %llu \n", filename.c_str(), size);
    
    // Устанавливаем курсор в начало файла
    file.seekg(0);      
}

Tape::~Tape() {
    // Если файл открыт, закрываем
    if (file.is_open()) file.close();   
}

size_t Tape::get_size() const{
    return size;
}

string Tape::get_filename() const{
    return filename;
}

int32_t Tape::read() {
    // Применяем задержку на чтение в мс
    applyDelay(delays.read);        
    // Переменная для хранения данных с текущей позиции
    int32_t value;                  
    // Устанавливаем курсор на текущую позицию
    file.seekg(position * sizeof(int32_t));     
    // Считываем данные с ленты в переменную value
    file.read(reinterpret_cast<char*>(&value), sizeof(value));  
    // Возвращаем считанные данные
    return value;
}

void Tape::write(int32_t data){
    // Применяем задержку на запись в мс
    applyDelay(delays.write);
    // Устанавливаем курсор на текущую позицию
    file.seekp(position * sizeof(int32_t));
    // Записываем переданные данные на ленту (в файл)
    file.write(reinterpret_cast<const char*>(&data), sizeof(data));
    // Если текущая позиция больше размера, увеличиваем размер
    if (position >= size) size++;
}

void Tape::moveBackward(){
    if (position > 0) {
        // Применяем задержку на сдвиг
        applyDelay(delays.shift);
        // Уменьшаем текущую позицию, если она не начальная
        position--;
    }
}

void Tape::moveForward(){
    if (position < size){
        // Применяем задержку на сдвиг
        applyDelay(delays.shift);
        // Увеличиваем текущую позицию, если она меньше размера
        position++;
    }
}

void Tape::rewindToStart() {
    // Вычисляем задержку на возврат в начальное положение с учетом текущей позиции и применяем ее
    applyDelay(static_cast<uint32_t>(delays.rewind * (position / size)));
    // Устанавливаем начальную позицию
    position = 0;
}

bool Tape::isEnd() const{
    return position >= size;
}