#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/FileTapeDevice.h"
#include "../src/Sorter.h"

TEST_CASE("OpenFile that does`t exist for read", "[TapeDevice]") {
    FileTapeDevice tape("../tmp/aslkdjklkjasklfj.txt", 0, 0, 0, 0);
    REQUIRE(!tape.open("r+"));
}

TEST_CASE("OpenFile or create new one", "[TapeDevice]") {
    FileTapeDevice tape("../tmp/aslkdjklkjasklfj.txt", 0, 0, 0, 0);
    REQUIRE(tape.open("w+"));
}

TEST_CASE("WriteRead", "[TapeDevice]") {
    FileTapeDevice tape("../tmp/test_tape.txt", 0, 0, 0, 0);
    tape.open("w+");
    tape.write(42);
    tape.rewind();
    REQUIRE(42 == tape.read());
}

TEST_CASE("RewindShift", "[TapeDevice]") {
    FileTapeDevice tape("../tmp/test_tape.txt", 0, 0, 0, 0);
    tape.open("w+");
    tape.write(42);
    tape.shiftRight();
    tape.write(43);
    tape.rewind();
    REQUIRE(42 == tape.read());
    tape.shiftRight();
    REQUIRE(43 == tape.read());
}

TEST_CASE("Sort", "[TapeDevice, Sorter]") {
    FileTapeDevice inputTape("../tmp/input_test_tape.txt", 0, 0, 0, 0);
    FileTapeDevice outputTape("../tmp/output_test_tape.txt", 0, 0, 0, 0);
    Sorter sorter(inputTape, outputTape, 1024);
    inputTape.open("w+");
    outputTape.open("w+");
    inputTape.write(3);
    inputTape.shiftRight();
    inputTape.write(-1);
    inputTape.shiftRight();
    inputTape.write(0);
    inputTape.shiftRight();
    inputTape.rewind();

    sorter.sort();

    outputTape.rewind();
    REQUIRE(-1 == outputTape.read());
    outputTape.shiftRight();
    REQUIRE(0 == outputTape.read());
    outputTape.shiftRight();
    REQUIRE(3 == outputTape.read());
}