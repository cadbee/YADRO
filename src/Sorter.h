/*
 * Class that implements the sorting algorithm using merge sorting
 */

#ifndef YADRO_TEST_SORTER_H
#define YADRO_TEST_SORTER_H

#include <vector>
#include <algorithm>
#include <regex>
#include "TapeDevice.h"
#include "Config.h"

class Sorter {
public:
    Sorter(TapeDevice &inputTape, TapeDevice &outputTape, unsigned long long memorySize)
            : inputTape(inputTape), outputTape(outputTape), maxIntsInMemory(memorySize/sizeof(int)) {
    }

    void sort() {
        int currentInt;
        int partitionCount = 0;
        if(maxIntsInMemory < 1) return;
        // Read the input tape and divide it into partitions
        while (!inputTape.endOfFile()) {
            currentInt = inputTape.read();
            inputTape.shiftRight();
            partition.push_back(currentInt);
            if (partition.size() == maxIntsInMemory) {
                // Sort and write the current partition to a temporary tape
                if(!sortAndWritePartition(partitionCount)) return;
                partitionCount++;
                partition.clear();
            }
        }
        if(!partition.empty() && partition.size() < maxIntsInMemory){
            if(!sortAndWritePartition(partitionCount)) return;
            partitionCount++;
            partition.clear();
        }
        // Combine all the tapes
        mergePartitions();
    }

private:
    TapeDevice &inputTape;
    TapeDevice &outputTape;
    unsigned long long maxIntsInMemory;
    std::vector<int> partition;
    std::vector<TapeDevice *> tempTapes;

    bool sortAndWritePartition(int partitionCount) {
        std::sort(partition.begin(), partition.end());
        // Create a new temporary tape for the current partition
        std::string tempFilename = "../tmp/temp_%d.txt";
        tempFilename = std::regex_replace(tempFilename, std::regex(R"(%d)"), std::to_string(partitionCount));
        TapeDevice *tempTape = new FileTapeDevice(tempFilename.c_str(), READ_DELAY, WRITE_DELAY, REWIND_DELAY, SHIFT_DELAY);
        if(!tempTape->open("w+")) return false;
        // Write the sorted partition to the temporary tape
        for (int i: partition) {
            tempTape->write(i);
            tempTape->shiftRight();
        }
        tempTape->rewind();
        tempTapes.push_back(tempTape);
        return true;
    }

    void mergePartitions() {
        int partitionIndex = 0;
        // Go through all temporary tapes
        while (!tempTapes.empty()) {
            while (!tempTapes[partitionIndex]->endOfFile() && !outputTape.endOfFile()) {
                // Compare the values on the temporary and output tape
                int a = tempTapes[partitionIndex]->read();
                int b = outputTape.read();
                if (a < b) {
                    outputTape.offsetInsert(a);
                    tempTapes[partitionIndex]->shiftRight();
                } else {
                    outputTape.shiftRight();
                }
            }
            // Write the remanining values from the temporary tape
            while (!tempTapes[partitionIndex]->endOfFile()) {
                int a = tempTapes[partitionIndex]->read();
                tempTapes[partitionIndex]->shiftRight();
                outputTape.write(a);
                outputTape.shiftRight();
            }
            outputTape.rewind();
            tempTapes.erase(tempTapes.begin(), tempTapes.begin()+1);
        }
    }
};

#endif //YADRO_TEST_SORTER_H
