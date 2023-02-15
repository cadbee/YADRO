/*
 * Interface to work with the tape device
 */

#ifndef YADRO_TEST_TAPEDEVICE_H
#define YADRO_TEST_TAPEDEVICE_H

class TapeDevice {
public:
    virtual bool open(std::string param) = 0;

    virtual bool endOfFile() = 0;

    virtual int read() = 0;

    virtual void write(int item) = 0;

    virtual void shiftLeft() = 0;

    virtual void shiftRight() = 0;

    virtual void rewind() = 0;

    virtual void offsetInsert(int item) = 0;
};

#endif //YADRO_TEST_TAPEDEVICE_H
