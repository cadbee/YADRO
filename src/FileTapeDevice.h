/*
 * Class that implements the TapeDevice interface and emulates working with the tape through a file
 */

#ifndef YADRO_TEST_FILETAPEDEVICE_H
#define YADRO_TEST_FILETAPEDEVICE_H

#include <fstream>
#include <iostream>
#include <thread>
#include "TapeDevice.h"


class FileTapeDevice : public TapeDevice {
public:
    FileTapeDevice(const char *filename, int readDelay, int writeDelay, int rewindDelay, int shiftDelay)
            : filename(filename), readDelay(readDelay), writeDelay(writeDelay), rewindDelay(rewindDelay),
              shiftDelay(shiftDelay) {
    }

    ~FileTapeDevice() {
        tape.close();
    }

    // EOF check
    bool endOfFile() override {
        int temp;
        tape.clear();
        tape.seekg(position, std::ios::beg);
        if (tape >> temp) return false;
        return true;
    }

    // Open file for read or write
    bool open(std::string param) override {
        if (param == "w+") tape.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
        // Need to create a file if it doesn`t exist
        else tape.open(filename, std::ios::in | std::ios::out);
        if (!tape) {
            std::cerr << "Error: Unable to open " << filename << std::endl;
            return false;
        }
        return true;
    }

    // Read integer at current position
    int read() override {
        int value;
        tape.clear();
        tape.seekg(position, std::ios::beg);
        tape >> value;
        // Add the read delay
        std::this_thread::sleep_for(std::chrono::milliseconds(readDelay));
        return value;
    }

    // Write integer to current position
    void write(int item) override {
        tape.clear();
        tape.seekg(position, std::ios::beg);
        tape << item << ' ';
        prev_pos = position;
        // Add the write delay
        std::this_thread::sleep_for(std::chrono::milliseconds(writeDelay));
    }

    // Shifting the tape to the left
    void shiftLeft() override {
        position = prev_pos;
        tape.clear();
        tape.seekg(position, std::ios::beg);
        // Add the shift delay
        std::this_thread::sleep_for(std::chrono::milliseconds(shiftDelay));
    }

    // Shifting the tape to the left
    void shiftRight() override {
        prev_pos = position;
        int value;
        tape.clear();
        tape.seekg(position, std::ios::beg);
        tape >> value;
        position += (int)std::to_string(value).length() + 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(shiftDelay));
    }

    // Shifting the tape to the beginning
    void rewind() override {
        position = 0;
        prev_pos = 0;
        tape.clear();
        tape.seekg(position, std::ios::beg);
        // Add the rewind delay
        std::this_thread::sleep_for(std::chrono::milliseconds(rewindDelay));
    }

    // Inserts a value at the current position, shifting all others to the right
    void offsetInsert(int item) override {
        tape.clear();
        tape.seekg(position, std::ios::beg);
        std::string temp;
        getline(tape, temp);
        this ->write(item);
        tape << temp;
    }

private:
    std::fstream tape{};
    const char *filename;
    int position = 0;
    int prev_pos = 0;
    int readDelay;
    int writeDelay;
    int rewindDelay;
    int shiftDelay;
};

#endif //YADRO_TEST_FILETAPEDEVICE_H
