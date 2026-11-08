// DepartmentTree.cpp
// Purpose: General tree for the academic department hierarchy
// Author: Boluwatife Elijah Okusanya

#include "../include/DepartmentTree.hpp"
#include <cctype>
#include <string>

// Converts a string to lowercase
static std::string toLowerCopy(const std::string& text)
{
    // Creates a copy of the input string
    std::string result = text;

    // Converts each character to lowercase
    for (char& ch : result)
    {
        // Converts the character to lowercase
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    // Returns the lowercase copy of the input string
    return result;
}
