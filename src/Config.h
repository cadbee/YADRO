//
// Read config from config.txt file
//

#ifndef YADRO_TEST_CONFIG_H
#define YADRO_TEST_CONFIG_H

#include <iostream>
#include <fstream>
#include <vector>

std::string CONFIG_FILE_NAME = "../config/config.txt";
int READ_DELAY = 0;
int WRITE_DELAY = 0;
int REWIND_DELAY = 0;
int SHIFT_DELAY = 0;

bool setConfig() {
    std::ifstream configFile(CONFIG_FILE_NAME);
    if (!configFile.is_open()) {
        std::cerr << "Error: Unable to open config.txt file" << std::endl;
        return false;
    }
    std::vector<int> configData;
    std::string line;
    while (std::getline(configFile, line)) {
        configData.push_back(std::stoi(line));
    }
    if (configData.size() < 4) {
        std::cerr << "Error: config.txt wrong data" << std::endl;
        return false;
    }
    READ_DELAY = configData[0];
    WRITE_DELAY = configData[1];
    REWIND_DELAY = configData[2];
    SHIFT_DELAY = configData[3];
    configFile.close();
    return true;
}

#endif //YADRO_TEST_CONFIG_H
