//Semere
#include <iostream>
#include "CampusGraph.hpp"
#include "FileLoading.hpp" // For our trim() function
#include <cctype> // For tolower()
#include <queue> // For BFS traversal
using namespace std;

// Convert a building name to lowercase for comparison
static string normalizeName(const string& name) {
    string result = trim(name);

    // Convert each character to lowercase
    for (char& c : result) {
        //Makes it safe for tolower() then converts it back to char
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    return result;
}

// Find a building by name and return its index
int CampusGraph::findBuildingIndex(const string& name) const {
    string target = normalizeName(name); // Normalize the input name for comparison

    // Search through all buildings
    for (size_t i = 0; i < buildings.size(); i++) {
        if (normalizeName(buildings[i].name) == target) {
            return static_cast<int>(i);
        }
    }

    return -1; // Building not found
}

// Adds a new building to the graph
bool CampusGraph::addBuilding(const string& name) {
    string cleanedName = trim(name);

    // Reject empty names or duplicate buildings
    if (cleanedName.empty() || findBuildingIndex(cleanedName) != -1) {
        return false;
    }

    // Add the building with an empty neighbors list
    buildings.push_back({cleanedName, {}});

    return true; // Building successfully added
}

// Check if a building already exists
bool CampusGraph::buildingExists(const string& name) const {
    // if the building index is not -1, then it exists
    return findBuildingIndex(name) != -1;
}

//Get the original spelling of a building name
string CampusGraph::getBuildingName(const string& name) const {
    int index = findBuildingIndex(name);
    //return an empty string if the building does not exist
    if (index == -1) {return "";}

    return buildings[index].name;
    
}
// Return the total number of buildings in the graph
int CampusGraph::getBuildingCount() const {
    return static_cast<int>(buildings.size());
}


// Add an undirected connection between two buildings
bool CampusGraph::addConnection(const string& building1, const string& building2) {

    // Find the indexes of both buildings
    int index1 = findBuildingIndex(building1);
    int index2 = findBuildingIndex(building2);

    // Reject if either building do not exist
    if (index1 == -1 || index2 == -1) {
        return false;
    }

    // Reject a building connecting to itself
    if (index1 == index2) {
        return false;
    }

    // Check if this connection exists
    for (int neighbor : buildings[index1].neighbors) {
        if (neighbor == index2) {
            return false;
        }
    }

    // Add the connection in both directions
    buildings[index1].neighbors.push_back(index2);
    buildings[index2].neighbors.push_back(index1);

    return true; // Connection successfully added
}


// Display all buildings and their connected neighbors
void CampusGraph::displayGraph() const {

    // Check if there are no buildings in the graph
    if (buildings.empty()) { cout << "No buildings available." << endl; return;}

    // Loop through each building in the graph
    for (const Building& building : buildings) 
    {
        cout << building.name << " -> ";

        // Check if the building has no connections
        if (building.neighbors.empty()) {cout << "(no connections)";}
        else
        {
            // Loop through the neighboring building indexes
            for (size_t i = 0; i < building.neighbors.size(); i++) 
            {
                int neighborIndex = building.neighbors[i];

                // Display the name of the connected building
                cout << buildings[neighborIndex].name;

                // Add a comma between neighbors, except the last one
                if (i + 1 < building.neighbors.size()) {cout << ", ";}
            }
        }

        cout << endl;
    }
}


// Display graph statistics including buildings, connections, and degrees
void CampusGraph::displayGraphStats() const {
    int totalDegrees = 0;

    // Check if the graph is empty
    if (buildings.empty()) {
        cout << "No buildings available." << endl;
        cout << "Total buildings: 0" << endl;
        cout << "Total connections: 0" << endl;
        return;
    }

    // Display the degree of each building
    cout << "BUILDING DEGREES:" << endl;

    for (const Building& building : buildings) {
        int degree = static_cast<int>(building.neighbors.size()); 

        cout << building.name << ": " << degree << endl;

        // Add the degree to the total
        totalDegrees += degree;
    }

    // Each connection is stored twice in an undirected graph
    int totalConnections = totalDegrees / 2;

    // Display the graph totals
    cout << "Total buildings: " << buildings.size() << endl;
    cout << "Total connections: " << totalConnections << endl;
}


// Display all buildings reachable from a starting building using BFS
void CampusGraph::displayReachableBuildings(const string& startName) const {

    // Find the starting building's index
    int startIndex = findBuildingIndex(startName);

    // Reject an unknown building
    if (startIndex == -1) {
        cout << "Error: Unknown building: " << startName << endl;
        return;
    }

    // A queue to store buildings waiting to be explored
    queue<int> q;

    // Track visited buildings and their distances
    vector<bool> visited(buildings.size(), false); 
    vector<int> distance(buildings.size(), -1);

    // Mark the starting building as visited and add it to the queue
    visited[startIndex] = true;
    distance[startIndex] = 0;
    q.push(startIndex); // Add it

    int reachableCount = 0; 

    cout << "Reachable buildings from " << buildings[startIndex].name << ":" << endl;

    // Continue exploring while the queue is not empty
    while (!q.empty()) {

        // Get the first building from the queue
        int current = q.front(); 
        q.pop(); // Remove it from the queue

        // Display the building and its distance
        cout << buildings[current].name << " (distance " << distance[current] << ")" << endl;

        reachableCount++;

        // Loop through the current building's neighbors
        for (int neighbor : buildings[current].neighbors) {

            // Only visit buildings that have not been discovered
            if (!visited[neighbor]) {
                visited[neighbor] = true;

                // Neighbor is one connection farther than current
                distance[neighbor] = distance[current] + 1;

                // Add the neighbor to the queue
                q.push(neighbor);
            }
        }
    }

    // Display the total number of reachable buildings
    cout << "Reachable: " << reachableCount << " of " << buildings.size() << " buildings" << endl;
}
