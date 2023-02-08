/*
 * Main function of the console application
 */

#include "FileTapeDevice.h"
#include "Sorter.h"

unsigned long long MAX_MEMORY = 13;


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " input_file_path output_file_path" << std::endl;
        return 1;
    }
    if(!setConfig()) return 1;
    const char *inputFile = argv[1];
    const char *outputFile = argv[2];
    FileTapeDevice inputTape(inputFile, READ_DELAY, WRITE_DELAY, REWIND_DELAY, SHIFT_DELAY);
    FileTapeDevice outputTape(outputFile, READ_DELAY, WRITE_DELAY, REWIND_DELAY, SHIFT_DELAY);
    if(!inputTape.open("r+")) return 1;
    if(!outputTape.open("w+")) return 1;
    Sorter sorter(inputTape, outputTape, MAX_MEMORY);
    sorter.sort();
    return 0;
}