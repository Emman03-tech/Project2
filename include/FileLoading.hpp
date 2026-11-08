//Semere

#pragma once

#include <string>
#include <vector>

// Stores a record and its original line number
struct InputLine {
    int lineNumber; //linenum
    std::string text; //Text in the line
};

// Removes whitespace around text.
std::string trim(const std::string& text);

// Reads records from a file.
std::vector<InputLine> readRecords(const std::string& filePath);
