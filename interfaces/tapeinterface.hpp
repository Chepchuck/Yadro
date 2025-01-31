#ifndef ITAPE_HPP
#define ITAPE_HPP

#include <cstdint>
#include <memory>

class ITape{
protected:
    virtual ~ITape() = default;
public:
    virtual int32_t read() = 0;
    virtual void write(int32_t data) = 0;
    virtual void moveForward() = 0;
    virtual void moveBackward() = 0;
    virtual void rewindToStart() = 0;
    virtual bool isEnd() const = 0;
    virtual size_t get_size() = 0;
    ITape& operator=(const ITape&) = delete;
};

#endif