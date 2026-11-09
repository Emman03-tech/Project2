 #include <iostream>
 #include <vector>
 #include <string>
#include "FileLoading.hpp"
using namespace std;   

int main(int argc, char* argv[]) {
    // Default data directory
    std::string dataDir = "data";

    // If a command-line argument is provided, use it as the data directory for testing purposes
    if (argc > 1) {
        dataDir = argv[1];
    }
    
    // Read records from the specified files and stores them in a vector
    vector<InputLine> buildings = readRecords(dataDir + "/buildings.txt");
    vector<InputLine> connections = readRecords(dataDir + "/connections.txt");
    vector<InputLine> facilities = readRecords(dataDir + "/facilities.txt");
    vector<InputLine> departments = readRecords(dataDir + "/departments.txt");


    // Display the number of records read from each file
    cout << "\nRecords read (not validated yet):\n";
    cout << "Buildings: " << buildings.size() << '\n';
    cout << "Connections: " << connections.size() << '\n';
    cout << "Facilities: " << facilities.size() << '\n';
    cout << "Departments: " << departments.size() << '\n';

    //Display each building name and its line number
    cout << "\nBuildings:\n";
    for(const InputLine& building : buildings) {
        cout << "Line " << building.lineNumber << ": " << building.text << '\n';
    }

    return 0;
}
