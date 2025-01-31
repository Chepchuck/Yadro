<<<<<<< HEAD
#ifndef TAPEINTERFACE_HPP
#define TAPEINTERFACE_HPP

#include <cstdint>
#include <memory>

class TapeInterface{
public:
    virtual ~TapeInterface();
    virtual int32_t read();
    virtual void write(int32_t data);
    virtual void moveForward();
    virtual void moveBackward();
    virtual void rewindToStart();
    virtual bool isEnd() const;
    virtual size_t get_size();
};

=======
#ifndef TAPEINTERFACE_HPP
#define TAPEINTERFACE_HPP

#include <cstdint>
#include <memory>

class TapeInterface{
public:
    virtual ~TapeInterface();
    virtual int32_t read();
    virtual void write(int32_t data);
    virtual void moveForward();
    virtual void moveBackward();
    virtual void rewindToStart();
    virtual bool isEnd() const;
    virtual size_t get_size();
};

>>>>>>> 7c37bcd5dbeab3a44a59019d8425f5bfbb5943ae
#endif