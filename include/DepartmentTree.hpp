// DepartmentTree.hpp
// Purpose: General tree for the academic department hierarchy
// Author: Boluwatife Elijah Okusanya

#ifndef DEPARTMENTTREE_HPP
#define DEPARTMENTTREE_HPP

#include <string>
#include <vector>

// Represents a node in the academic department hierarchy
struct DepartmentNode {
   
    // Name of the department
    std::string name;
    
    // Pointer to the parent department
    DepartmentNode* parent = nullptr;
    
    // Pointer to the child departments
    std::vector<DepartmentNode*> children;
    
    // Depth of the department in the hierarchy
    int depth = 0;
};

// The class for managing the academic department hierarchy
class DepartmentTree {
private:
    // Recursively searches the tree for a department by name
    DepartmentNode* findHelper(const std::string& name, DepartmentNode* node) const;
    
    // Deletes a department node and all of its children
    void destroyHelper(DepartmentNode* node);

    // Recursively prints the department hierarchy
    void printHierarchyHelper(DepartmentNode* node) const;

    // Prints a department node and its children in preorder
    void printPreorderHelper(DepartmentNode* node) const;
    
    // Pointer to the root department
    DepartmentNode* root = nullptr;
public:
    // Find a department by its name
    DepartmentNode* find(const std::string& name) const { return findHelper(name, root); }

    // Inserts a new department into the tree
    bool insert(const std::string& name, const std::string& parentName, std::string& errorMessage);

    // Prints the department hierarchy
    void printHierarchy() const;

    // Prints the department hierarchy in preorder order
    void printPreorder() const;

    // Prints information about a department by its name
    void printDepartmentInfo(const std::string& name) const;

    // Constructor
    DepartmentTree() = default;

    // Destructor
    ~DepartmentTree();

    // Get the root department
    DepartmentNode* getRoot() const { return root; }
};

#endif // DEPARTMENTTREE_HPP