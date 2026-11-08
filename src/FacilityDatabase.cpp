#include "../include/FacilityDatabase.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

// Purpose is to implement facility loading, validation, display, and hash table based ID search

FacilityDatabase::FacilityDatabase(): acceptedCount(0), rejectedCount(0)
{}

// removes spaces, tabs, and carriage returns at the ends
string FacilityDatabase::trim(const string& value)
{
    size_t start = value.find_first_not_of(" \t\r\n");

    if (start == string::npos)
    {
        return "";
    }

    size_t end = value.find_last_not_of(" \t\r\n");
    return value.substr(start, end - start +1);
}

// converts a string to uppercase
string FacilityDatabase::toUpper(string value)
{
    for (char& ch : value)
    {
        ch = static_cast<char>
        (
            toupper(static_cast<unsigned char>(ch))
        );
    }

    return value;
}

// Validates the format F folloed by the 3 digits
bool FacilityDatabase::isValidID(const string& id)
{
    if (id.length() != 4 || id[0] != 'F')
    {
        return false;
    }

    for (size_t i = 1; i < 4; i++)
    {
        if(id[i] < '0' || id[i] > '9')
        {
            return false;
        }
    }

    return true;
}

// Loads and validates facilities from the text files
void FacilityDatabase::loadFromFile
(
    const string& filename, const vector<string>& validBuildings
)
{
    ifstream input(filename);

    if(!input.is_open())
    {
        cerr << "Error: Cannot open " << filename << endl;
        displayLoadSummary(filename);
        return;
    }

    string line;
    int lineNumber = 0;

    while(getline(input, line))
    {
        lineNumber++;
        line = trim(line);

        if(line.empty() || line[0] == '#')
        {
            continue;
        }

        vector<string> fields;
        string field;
        stringstream ss(line);

        while(getline(ss, field, '|'))
        {
            fields.push_back(trim(field));
        }

        // preserve a trailing empty field
        if (!line.empty() && line.back() == '|')
        {
            fields.push_back("");
        }

        string reason;

        if (fields.size() !=4)
        {
            reason = "Incorrect number of fields";
        }else
        {
            string id = toUpper(fields[0]);
            string name = fields[1];
            string building = fields[2];
            string category = fields[3];

            if (id.empty() || name.empty() || building.empty() || category.empty())
            {
                reason = "Empty required field";
            } else if (!isValidID(id))
            {
                reason = "Invalid ID format (F plus 3 digits)";
            }else
            {
                string matchedBuilding;
                bool buildingFound = false;

                for (const string& valid : validBuildings)
                {
                    if (toUpper(trim(valid)) == toUpper(building))
                    {
                        matchedBuilding = valid;
                        buildingFound = true;
                        break;
                    }
                }

                if (!buildingFound)
                {
                    reason = "Unknown building: " + building;
                }else
                {
                    size_t existingIndex = 0;

                    if (hashTable.search(id, existingIndex))
                    {
                        reason = "Duplicate facility ID: " + id;
                    }else
                    {
                        Facility facility =
                        {
                            id, name, matchedBuilding, category
                        };

                        size_t newIndex = facilities.size();

                        if (hashTable.insert(id, newIndex))
                        {
                            facilities.push_back(facility);
                            acceptedCount++;
                        }else
                        {
                            reason = "Unable to insert facility ID";
                        }
                    }
                }
            }
        }

        if (!reason.empty())
        {
            rejectedCount++;

            cerr << "Warning: " << filename
                 << ", line " << lineNumber
                 << ": " << reason << endl;
        }
    }

    displayLoadSummary(filename);
}

// Displays every accepted facility in the database
void FacilityDatabase::displayAll() const
{
    if (facilities.empty())
    {
        cout << "No facilities are available" << endl;
        cout << "Total facilities: 0" << endl;
        return;
    }

    cout << "\n=== All Facilities ===\n";

    for (const Facility& facility : facilities)
    {
        cout << facility.id << " | "
             << facility.name << " | "
             << facility.building << " | "
             << facility.category << endl;
    }

    cout << "Total facilities: " << facilities.size() << endl;
}

// Searches by ID using the custom hash table
void FacilityDatabase::searchByID(const string& id) const
{
    string normalizedID = toUpper(trim(id));

    if(!isValidID(normalizedID))
    {
        cout << "Invalid ID format."
             << "Use F followed by exactly 3 digits"
             << endl;
        return;
    }

    // search for the facility using the hash table
    size_t index = 0;

    if(!hashTable.search(normalizedID, index))
    {
        cout << "Facility not found: "
             << normalizedID 
             << endl;
        return;
    }

    const Facility& facility = facilities[index];

    cout << "Found:\n"
         << "ID: " << facility.id << '\n'
         << "Name: " << facility.name << '\n'
         << "Building: " << facility.building << '\n'
         << "Category: " << facility.category << endl;
}

// Displays the required loading statistics
void FacilityDatabase::displayLoadSummary
(
    const string& filename
)const
{
    cout << filename << ": "
         << acceptedCount << " accepted, "
         << rejectedCount << " rejected"
         << " (hash capacity " 
         << hashTable.getCapacity()
         << ", entries "
         << hashTable.getEntryCount()
         << ", collisions "
         << hashTable.getCollisionCount()
         << ")" << endl;
}