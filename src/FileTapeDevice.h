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
        fclose(tape);
    }

    // EOF check
    bool endOfFile() override {
        int temp;
        fseek(tape, position, SEEK_SET);
        if (fscanf(tape, "%d ", &temp) == -1) return true;
        return false;
    }

    // Open file for read or write
    bool open(std::string param) override {
        tape = fopen(filename, param.c_str());
        if (!tape) {
            std::cerr << "Error: Unable to open " << filename << std::endl;
            return false;
        }
        return true;
    }

    // Read integer at current position
    int read() override {
        int value;
        fseek(tape, position, SEEK_SET);
        fscanf(tape, "%d", &value);
        // Add the read delay
        std::this_thread::sleep_for(std::chrono::milliseconds(readDelay));
        return value;
    }

    // Write integer to current position
    void write(int item) override {
        fseek(tape, position, SEEK_SET);
        fprintf(tape, "%d ", item);
        prev_pos = position;
        // Add the write delay
        std::this_thread::sleep_for(std::chrono::milliseconds(writeDelay));
    }

    // Shifting the tape to the left
    void shiftLeft() override {
        position = prev_pos;
        fseek(tape, position, SEEK_SET);
        // Add the shift delay
        std::this_thread::sleep_for(std::chrono::milliseconds(shiftDelay));
    }

    // Shifting the tape to the left
    void shiftRight() override {
        prev_pos = position;
        int value;
        fseek(tape, position, SEEK_SET);
        fscanf(tape, "%d ", &value);
        position += value >= 0 ? 1 : 2;
        for (;;) {
            position++;
            if ((value /= 10) == 0) break;
        };
        // Add the shift delay
        std::this_thread::sleep_for(std::chrono::milliseconds(shiftDelay));
    }

    // Shifting the tape to the beginning
    void rewind() override {
        position = 0;
        prev_pos = 0;
        fseek(tape, position, SEEK_SET);
        // Add the rewind delay
        std::this_thread::sleep_for(std::chrono::milliseconds(rewindDelay));
    }

private:
    FILE *tape{};
    const char *filename;
    int position = 0;
    int prev_pos = 0;
    int readDelay;
    int writeDelay;
    int rewindDelay;
    int shiftDelay;
};

#endif //YADRO_TEST_FILETAPEDEVICE_H
