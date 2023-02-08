cmake_minimum_required(VERSION 3.24)
project (yadro_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(yadro_test src/main.cpp src/TapeDevice.h src/FileTapeDevice.h src/Sorter.h src/Config.h src/Config.h)
