// DepartmentTree.cpp
// Purpose: General tree for the academic department hierarchy
// Author: Boluwatife Elijah Okusanya

#include "../include/DepartmentTree.hpp"
#include <cctype>
#include <string>
#include <iostream>


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

// Inserts a new department into the tree
bool DepartmentTree::insert(const std::string& name, const std::string& parentName, std::string& errorMessage)
{
    // Creates the root department if the tree is empty
    if (root == nullptr)
    {
        root = new DepartmentNode;
        root->name = name;
        return true;
    }

    // Checks if the department name already exists
    if (find(name) != nullptr)
    {
        errorMessage = "Duplicate department: " + name;
        return false;
    }

    // Finds the parent department
    DepartmentNode* parent = find(parentName);
    if (parent == nullptr)
    {
        errorMessage = "Unknown parent: " + parentName;
        return false;
    }

    // Creates the new department node
    DepartmentNode* node = new DepartmentNode;
    node->name = name;
    node->parent = parent;
    node->depth = parent->depth + 1;

    // Adds the new department to its parent
    parent->children.push_back(node);
    return true;
}

// Recursively prints the department hierarchy
void DepartmentTree::printHierarchyHelper(DepartmentNode* node) const
{
    // Returns if the current node is null
    if (node == nullptr)
    {
        return;
    }

    // Prints the current department
    std::cout << std::string(node->depth * 4, ' ') << node->name << '\n';

    // Recursively prints each child department
    for (DepartmentNode* child : node->children)
    {
        printHierarchyHelper(child);
    }
}

// Prints the department hierarchy
void DepartmentTree::printHierarchy() const
{
    // Returns if the tree is empty
    if (root == nullptr)
    {
        std::cout << "No departments are loaded.\n";
        return;
    }

    printHierarchyHelper(root);
}

// Recursively prints a department node and its children in preorder
void DepartmentTree::printPreorderHelper(DepartmentNode* node) const
{
    // Returns if the current node is null
    if (node == nullptr)
    {
        return;
    }

    // Prints the current department
    std::cout << node->name << '\n';

    // Recursively prints each child department
    for (DepartmentNode* child : node->children)
    {
        printPreorderHelper(child);
    }
}

// Prints the department hierarchy in preorder
void DepartmentTree::printPreorder() const
{
    // Returns if the tree is empty
    if (root == nullptr)
    {
        std::cout << "No departments are loaded.\n";
        return;
    }

    printPreorderHelper(root);

}

// Prints information about a department by its name
void DepartmentTree::printDepartmentInfo(const std::string& name) const
{
    DepartmentNode* node = find(name);
    if (node == nullptr)
    {
        std::cout << "Department not found: " << name << '\n';
        return;
    }

    std::cout << "Name: " << node->name << '\n';
    if (node->parent != nullptr)
    {
        std::cout << "Parent: " << node->parent->name << '\n';
    }
    else
    {
        std::cout << "Parent: None\n";
    }
    std::cout << "Children: " << node->children.size() << '\n';
    std::cout << "Depth: " << node->depth << '\n';
}