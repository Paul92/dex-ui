#include "data-utils.h"

#include <vector>
#include <algorithm>

std::vector<std::string> splitString(const std::string &string,
                                     const std::string &delimiter) {
    std::vector<std::string> strings;

    std::string::size_type current = 0;
    std::string::size_type previous = 0;
    while ((current = string.find(delimiter, previous)) != std::string::npos) {
        strings.push_back(string.substr(previous, current - previous));
        previous = current + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(string.substr(previous));

    return strings;
}


std::string reverseLines(std::string input) {

    std::vector<std::string> lines = splitString(input, "\n");

    // Reverse all lines
    for (size_t lineIndex = 0; lineIndex != lines.size(); lineIndex++)
        std::reverse(lines[lineIndex].begin(), lines[lineIndex].end());

    // Join the lines to form the output
    std::string output = "";
    for (size_t lineIndex = 0; lineIndex != lines.size(); lineIndex++)
        output += lines[lineIndex] + "\n";

    return output;
}
