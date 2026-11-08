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

// Recursively searches the tree for a department by name
DepartmentNode* DepartmentTree::findHelper(const std::string& name, DepartmentNode* node) const
{
    // Returns null if the current node is null
    if (node == nullptr)
    {
        return nullptr;
    }

    // Checks if the current node matches the department name
    if (toLowerCopy(node->name) == toLowerCopy(name))
    {
        return node;
    }

    // Searches each child node for the department
    for (DepartmentNode* child : node->children)
    {
        // Recursively searches the child node
        DepartmentNode* found = findHelper(name, child);
        if (found != nullptr)
        {
            return found;
        }
    }

    // Returns null if the department is not found
    return nullptr;
}

// Deletes a department node and all of its children
void DepartmentTree::destroyHelper(DepartmentNode* node)
{
    // Returns if the current node is null
    if (node == nullptr)
    {
        return;
    }

    // Deletes each child node
    for (DepartmentNode* child : node->children)
    {
        destroyHelper(child);
    }

    // Deletes the current node
    delete node;
}

// Destructor
DepartmentTree::~DepartmentTree()
{
    destroyHelper(root);
    root = nullptr;
}
