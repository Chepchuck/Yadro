#include "FileTape.hpp"
#include "TapeConfig.hpp"

/* Реализация методов класса Tape */

// Выделение памяти для хранения данных
FileTape::Delays FileTape::delays;
string FileTape::tmpDir;

string getDateTime() {
    time_t rawTime;
    char buffer[80];

    time (&rawTime);
    struct tm *timeInfo = localtime(&rawTime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y_%H-%M-%S",timeInfo);
    return buffer;
}

FileTape::FileTape(){
    // Задаем директорию для хранения файлов временных лент
    if (tmpDir.empty()) {
        tmpDir = "tmp/" + getDateTime() + "/";
        filesystem::create_directory(tmpDir) ? true : throw runtime_error("Error creating directory " + tmpDir);
    }
    string filename;
    for (unsigned short i = 0; i < 4; i++) {
        filename = tmpDir + "temp_" + to_string(i) + ".bin";
        if (!filesystem::exists(filename)) break;
    }
    // Создаем
    file.open(filename, ios::out);
    file.close();
    file.open(filename, ios::in | ios::out | ios::binary | ios::ate);
    this->filename = filename;
    size = 0;
}

FileTape::FileTape(const string& filename){
    printf("Open file: %s.\n ", filename.c_str());
    
    // Открываем файл на чтение и запись в бинарном режиме
    file.open(filename, ios::in | ios::out | ios::binary | ios::ate);

    // Если файл не был открыт, выкидываем исключение
    if (!file){
        throw runtime_error("File " + filename +" not found!");
    }
    // Сохраняем название
    this->filename = filename;

    // Вычисляем размер
    size = filesystem::file_size(filename) / sizeof(int32_t);   
    printf("%s size %llu \n", filename.c_str(), size);
    
    // Устанавливаем курсор в начало файла
    file.seekg(0);      
}

FileTape::~FileTape() {
    // Если файл открыт, закрываем
    if (file.is_open()) file.close();   
}

size_t FileTape::get_size() const{
    return size;
}

int32_t FileTape::read() {
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

void FileTape::write(int32_t data){
    // Применяем задержку на запись в мс
    applyDelay(delays.write);
    // Устанавливаем курсор на текущую позицию
    file.seekp(position * sizeof(int32_t));
    // Записываем переданные данные на ленту (в файл)
    file.write(reinterpret_cast<const char*>(&data), sizeof(data));
    // Если текущая позиция больше размера, увеличиваем размер
    if (position >= size) size++;
}

void FileTape::moveBackward(){
    if (position > 0) {
        // Применяем задержку на сдвиг
        applyDelay(delays.shift);
        // Уменьшаем текущую позицию, если она не начальная
        position--;
    }
}

void FileTape::moveForward(){
    if (position < size){
        // Применяем задержку на сдвиг
        applyDelay(delays.shift);
        // Увеличиваем текущую позицию, если она меньше размера
        position++;
    }
}

void FileTape::rewindToStart() {
    // Вычисляем задержку на возврат в начальное положение с учетом текущей позиции и применяем ее
    applyDelay(static_cast<uint32_t>(delays.rewind * (position / size)));
    // Устанавливаем начальную позицию
    position = 0;
}

bool FileTape::isEnd() const{
    return position >= size;
}