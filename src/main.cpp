#include <iostream>
#include <vector>
#include <string>
#include "FileLoading.hpp"
#include "FacilityDatabase.hpp"
#include "CampusGraph.hpp"
#include "DepartmentTree.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    // Default data directory
    std::string dataDir = "data";

    // If a command-line argument is provided, use it as the data directory for testing purposes
    if (argc > 1)
    {
        dataDir = argv[1];
    }

    // Create a campus graph object
    CampusGraph Graph;
    FacilityDatabase facilityDB;
    vector<string> validBuildings;

    // Read all buildings rocords from the file
    vector<InputLine> buildings = readRecords(dataDir + "/buildings.txt");

    int accepted = 0;
    int rejected = 0;

    // Loop through each buildings record
    for (const InputLine &record : buildings)
    {

        // Reject records containing extra fields
        if (record.text.find('|') != string::npos)
        {
            rejected++;
            cout << "Warning: buildings.txt line " << record.lineNumber << " - Invalid number of fields" << endl;
            continue;
        }

        // Try to add the building to the graph. If it fails, it's either a duplicate or invalid name
        if (Graph.addBuilding(record.text))
        {
            accepted++;
            validBuildings.push_back(record.text);
        }
        else
        {
            rejected++;
            cout << "Warning: buildings.txt line " << record.lineNumber << " - Duplicate or invalid building: " << record.text << endl;
        }
    }

    // Display the results
    cout << "buildings.txt: " << accepted << " accepted, " << rejected << " rejected" << endl;

    // Read the connections file
    vector<InputLine> connections = readRecords(dataDir + "/connections.txt");

    int connectionsAccepted = 0;
    int connectionsRejected = 0;

    // Loop through each connection record
    for (const InputLine &record : connections)
    {

        // Find the separator between the two building names
        size_t separator = record.text.find('|');

        // Reject records with missing or extra separators
        if (separator == string::npos || record.text.find('|', separator + 1) != string::npos)
        {
            connectionsRejected++;
            cout << "Warning: connections.txt line " << record.lineNumber << " - Invalid number of fields" << endl;
            continue;
        }

        // Separate the two building names
        string building1 = trim(record.text.substr(0, separator));
        string building2 = trim(record.text.substr(separator + 1));

        // Reject records with empty building names
        if (building1.empty() || building2.empty())
        {
            connectionsRejected++;
            cout << "Warning: connections.txt line " << record.lineNumber << " - Empty building name" << endl;
            continue;
        }

        // Check if the first building exists
        if (!Graph.buildingExists(building1))
        {
            connectionsRejected++;
            cout << "Warning: connections.txt line " << record.lineNumber << " - Unknown building: " << building1 << endl;
            continue;
        }

        // Check if the second building exists
        if (!Graph.buildingExists(building2))
        {
            connectionsRejected++;
            cout << "Warning: connections.txt line " << record.lineNumber << " - Unknown building: " << building2 << endl;
            continue;
        }

        // Reject connections from a building to itself
        if (Graph.getBuildingName(building1) == Graph.getBuildingName(building2))
        {
            connectionsRejected++;
            cout << "Warning: connections.txt line " << record.lineNumber << " - Self-connection" << endl;
            continue;
        }

        // Try to add the connection to the graph
        if (Graph.addConnection(building1, building2))
        {
            connectionsAccepted++;
        }
        else
        {
            connectionsRejected++;
            cout << "Warning: connections.txt line " << record.lineNumber << " - Duplicate connection" << endl;
        }
    }

    // Display the results
    cout << "connections.txt: " << connectionsAccepted << " accepted, " << connectionsRejected << " rejected" << endl;

    // Read the remaining files (validation will be added later)

    // Load and validate the facility records
    facilityDB.loadFromFile(dataDir + "/facilities.txt", validBuildings);
    facilityDB.displayLoadSummary("facilities.txt");


    // Create a department tree object
    DepartmentTree departmentTree;

    // Read all department records from the file
    vector<InputLine> departments = readRecords(dataDir + "/departments.txt");

    int departmentsAccepted = 0;
    int departmentsRejected = 0;

    // Loop through each department record
    for (const InputLine& record : departments) {

        // Find the separator between the department and parent name
        size_t separator = record.text.find('|');

        // Reject records with missing or extra separators
        if (separator == string::npos ||
            record.text.find('|', separator + 1) != string::npos) {
            departmentsRejected++;
            cout << "Warning: departments.txt line " << record.lineNumber
                << " - Invalid number of fields" << endl;
            continue;
        }

        // Separate the department name and parent name
        string departmentName = trim(record.text.substr(0, separator));
        string parentName = trim(record.text.substr(separator + 1));

        // Reject records with empty fields
        if (departmentName.empty() || parentName.empty()) {
            departmentsRejected++;
            cout << "Warning: departments.txt line " << record.lineNumber
                << " - Empty department or parent name" << endl;
            continue;
        }

        // The first accepted department must be the root with parent NONE
        if (departmentTree.getRoot() == nullptr && parentName != "NONE") {
            departmentsRejected++;
            cout << "Warning: departments.txt line " << record.lineNumber
                << " - Root department must have parent NONE" << endl;
            continue;
        }

        string errorMessage;

        // Try to insert the department into the tree
        if (departmentTree.insert(departmentName, parentName, errorMessage)) {
            departmentsAccepted++;
        }
        else {
            departmentsRejected++;
            cout << "Warning: departments.txt line " << record.lineNumber
                << " - " << errorMessage << endl;
        }
    }

    // Display the department load summary
    cout << "departments.txt: " << departmentsAccepted
        << " accepted, " << departmentsRejected << " rejected" << endl;


    // Display the total accepted buildings in our graph
    cout << "Buildings in graph: " << Graph.getBuildingCount() << endl;

    // Repeat the menu until the user chooses to exit
    while (true)
    {

        // Display the Milestone 1 menu
        cout << "\n========== CAMPUS NAVIGATION SYSTEM ==========" << endl;
        cout << "1. View all facilities" << endl;
        cout << "2. Search facility by ID" << endl;
        cout << "3. View campus graph" << endl;
        cout << "4. Display graph counts and degrees" << endl;
        cout << "5. Find reachable buildings (BFS)" << endl;
        cout << "6. Add department" << endl;
        cout << "7. Search department" << endl;
        cout << "8. Display department hierarchy" << endl;
        cout << "9. Run preorder traversal" << endl;
        cout << "10. Exit" << endl;

        string choice;

        // Get the user's menu selection
        cout << "\nEnter your choice: ";
        if (!getline(cin, choice))
        {
            cout << "Input ended. Exiting program." << endl;
            break;
        }

        // Exit the program
        if (choice == "10" || choice == "0")
        {
            cout << "Exiting program..." << endl;
            break;
        }

        // Display the campus graph and its connections
        else if (choice == "3")
        {
            cout << "\nCampus Graph:" << endl;
            Graph.displayGraph();
        }

        // Display the graph statistics
        else if (choice == "4")
        {
            cout << "\nCampus Graph Statistics:" << endl;
            Graph.displayGraphStats();
        }

        // Find reachable buildings using BFS
        else if (choice == "5")
        {
            string startBuilding;

            // Ask the user for a starting building
            cout << "\nEnter a starting building for BFS: ";
            if (!getline(cin, startBuilding))
            {
                break;
            }

            // Reject blank names
            if (trim(startBuilding).empty())
            {
                cout << "Error: Building name cannot be empty." << endl;
            }
            else
            {
                // Display all reachable buildings using BFS
                Graph.displayReachableBuildings(startBuilding);
            }
        }
        else if (choice == "1")
        {
            facilityDB.displayAll();
        }
        else if (choice == "2")
        {
            string facilityID;

            cout << "Enter a facility ID: ";
            if (!getline(cin, facilityID))
            {
                cout << "Input ended. Exiting Program." << endl;
                break;
            }

            facilityDB.searchByID(facilityID);
        }



        
// Add a new department
else if (choice == "6") {
    string departmentName;
    string parentName = "NONE";
    string errorMessage;

    // Ask the user for the department name
    cout << "Enter department name: ";
    if (!getline(cin, departmentName)) {
        break;
    }

    departmentName = trim(departmentName);

    // Reject empty department names
    if (departmentName.empty()) {
        cout << "Error: Department name cannot be empty." << endl;
        continue;
    }

    // Only ask for a parent if the tree already has a root
    if (departmentTree.getRoot() != nullptr) {
        cout << "Enter parent department: ";
        if (!getline(cin, parentName)) {
            break;
        }

        parentName = trim(parentName);

        // Reject empty parent names
        if (parentName.empty()) {
            cout << "Error: Parent name cannot be empty." << endl;
            continue;
        }
    }

    // Try adding the department to the tree
    if (departmentTree.insert(departmentName, parentName, errorMessage)) {
        cout << "Department added successfully: " << departmentName << endl;
    }
    else {
        cout << "Error: " << errorMessage << endl;
    }
}



    // Search for a department
    else if (choice == "7") {
        string departmentName;

        cout << "Enter department name: ";
        if (!getline(cin, departmentName)) {
            break;
        }

        departmentName = trim(departmentName);

        // Reject empty department names
        if (departmentName.empty()) {
            cout << "Error: Department name cannot be empty." << endl;
        }
        else {
            // Display the department information
            departmentTree.printDepartmentInfo(departmentName);
        }
    }

    // Display the department hierarchy
    else if (choice == "8") {
        cout << "\nDepartment Hierarchy:" << endl;
        departmentTree.printHierarchy();
    }

    // Display departments in preorder traversal
    else if (choice == "9") {
        cout << "\nPreorder Traversal:" << endl;
        departmentTree.printPreorder();
    }


        // Handle invalid menu input
        else
        {
            cout << "Error: Invalid menu choice." << endl;
        }
    }

    return 0;
}
