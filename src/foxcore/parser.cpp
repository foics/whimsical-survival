#include "foxcore/parser.hpp"

std::string getValue(std::string file, std::string valName) {
    std::string data = readFile(file);
    int subIndex = data.find(valName);
    std::string line = data.substr(subIndex);
    char *linePtr = &line[0];

    char tmpBuf[20] = {0};
    char *bufPtr = &tmpBuf[0];

    while (*linePtr != '=') {
        linePtr++;
    }
    linePtr++;
    while (*linePtr == ' ') {
        linePtr++;
    }
    while (*linePtr != '\n' && *linePtr != 0) {
        *bufPtr++ = *linePtr++;
    }

    *bufPtr = 0;

    return tmpBuf;
}
