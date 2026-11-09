// Author: Semere
// Represents the campus buildings and their connections.
#pragma once

#include <string>
#include <vector>

class CampusGraph {
private: // Stores a building and its neighboring buildings
    struct Building {
        std::string name;
        std::vector<int> neighbors;
    };

    // Vector to store all the buildings in the graph
    std::vector<Building> buildings;

    // Find a building by name and return its index
    int findBuildingIndex(const std::string& name) const;

public:
    // Add a new building to the graph if it doesn't already exist. returns true if successful, false if the building already exists
    bool addBuilding(const std::string& name);

    // Check if a building already exists. returns true if it exists, false otherwise
    bool buildingExists(const std::string& name) const;

    // Return the name of a building 
    std::string getBuildingName(const std::string& name) const;

    // Return the total number of buildings
    int getBuildingCount() const;

    // Add a connection between two buildings
    // Returns true if successful, false if either building does not exist or the connection already exists 
    // or a building is being connected to itself
    bool addConnection(const std::string& building1, const std::string& building2);

    // Display all buildings and their connected neighbors
    void displayGraph() const;

    // Display the total buildings, connections, and degree of each building
    void displayGraphStats() const;

    // Use BFS to display reachable buildings and their distances
    void displayReachableBuildings(const std::string& startName) const;


};
