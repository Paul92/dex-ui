#include "outOfRange.h"
#include <sstream>

OutOfRange::OutOfRange(int value, int lineNumber, std::string varName) {
    this->value = value;
    this->lineNumber = lineNumber;
    this->varName = varName;
}

std::string OutOfRange::getErrorMessage() {
    std::ostringstream outStream;
    outStream << "[OutOfRange] While setting " << varName;
    outStream << " to " << value << " at " << lineNumber << ".";
    return outStream.str();
}
