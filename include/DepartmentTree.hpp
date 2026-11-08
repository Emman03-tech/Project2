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
    // Find a department by its name
    DepartmentNode* findHelper(const std::string& name, DepartmentNode* node) const;
    // Pointer to the root department
    DepartmentNode* root = nullptr;
public:
    // Find a department by its name
    DepartmentNode* find(const std::string& name) const { return findHelper(name, root); }
    
    // Constructor
    DepartmentTree() = default;

    // Destructor
    ~DepartmentTree();

    // Get the root department
    DepartmentNode* getRoot() const { return root; }
};

#endif // DEPARTMENTTREE_HPP