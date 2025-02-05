#ifndef ITAPE_HPP
#define ITAPE_HPP

#include <cstdint>
#include <memory>

// Интерфейсный класс для устройств типа лента
class ITape{
protected:
    virtual ~ITape() = default;
public:
    // Чтение элемента с текущей позиции ленты
    virtual int32_t read() = 0;
    // Запись элемента на текущей позиции ленты
    virtual void write(int32_t data) = 0;
    // Сдвиг ленты на 1 элемент вперед
    virtual void moveForward() = 0;
    // Сдвиг ленты на 1 элемент назад
    virtual void moveBackward() = 0;
    // Сдвиг ленты в начало
    virtual void rewindToStart() = 0;
    // Флаг конца ленты
    virtual bool isEnd() const = 0;
};

#endif