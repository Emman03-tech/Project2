#ifndef FACILITYDATABASE_HPP
#define FACILITYDATABASE_HPP

#include <string>
#include <vector>
#include "HashTable.hpp"

// Stores, loads, displays, and searches campus facilities

struct Facility 
{
    std::string id;
    std::string name;
    std::string building;
    std::string category;
};

class FacilityDatabase
{
    private:
    stf::vector<Facility> facilities;
    HashTable hashTable;

    int acceptedCount;
    int rejectedCount;

    // Removes whitespace from both ends of string
    static std::string trim(const std::string& value);

    // Converts text to uppercase for comparisons
    static std::string toUpper(std::string value);

    // checks whether an ID is F followed by three digits
    static bool isValidID(const std::string& id);

    public:
    FacilityDatabase();

    // Loads facilities and validates their building references
    void loadFromFile
    (
        const std::string& filename,
        const std::vector<std::string>& validBuildings
    );

    // Displays all accepted facilities in file order
    void displayAll() const;

    // Searches for a facility using the custom hash table
    void searchByID(const std::string& id) const;

    // prints the file loading and hash table statistics
    void displayLoadSummary(const std::string& filename) const;
};

#endif