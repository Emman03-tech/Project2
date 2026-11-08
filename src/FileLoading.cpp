//Semere

#include "FileLoading.hpp" // For InputLine and readRecords
#include <fstream> // For file I/O
#include <iostream> // For error messages

std::string trim(const std::string& text) {
    size_t first = text.find_first_not_of(" \t\r");
    // If the string is all whitespace, return an empty string
    if (first == std::string::npos) {
        return ""; // All whitespace
    }
    // Find the last non-whitespace character
    size_t last = text.find_last_not_of(" \t\r");
    // Return the substring that excludes leading and trailing whitespace
    return text.substr(first, last - first + 1); 
}

std::vector<InputLine> readRecords(const std::string& filePath) {
    // Vector to store the records read from the file
    std::vector<InputLine> records;
    std::ifstream file(filePath); // Open the file for reading
    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return records; // Return empty vector on error
    }

    std::string line;
    int lineNumber = 0;
    // Read each line from the file
    while (std::getline(file, line)) {
        lineNumber++;
        // Store the line number and the trimmed text in the records vector
        line = trim(line);

        //Skip empty lines and comment lines
        if (line.empty() || line[0] == '#') {
            continue; // Skip this line
        }
        records.push_back({lineNumber, line}); // Add the record to the vector
    }

    file.close();
    return records;
}