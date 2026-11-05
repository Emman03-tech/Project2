#include "../include/HashTable.hpp"
#include <cctype>
#include <stdexcept>

using namespace std:

// Implementing custom facility ID hashing
// Insertion, lookup, and collision statistics


//Removes outer whitespace and converts ID to uppercase
static string normalizeID(const string& id)
{
    size_t start = 0;
    size_t end = id.size();

    while(start < end && isspace(static_cast<unsigned char>(id[start])))
    {
        start++;
    }
    while (end > start && isspace(static_cast<unsigned char>(id[end - 1])))
    {
        end--;
    }
string result = id.substr(start, end - start);

    for (char& ch : result)
    {
        ch = static_cast<char>
        (
            toupper(static_cast<unsigned char>(ch))
        );
    }

    return result;
}

// Checks the required format: F###
static bool validID(const string & id)
{
    if (id.length() != 4 || id[0] != 'F')
    {
        return false;
    }

    for (size_t i = 1; i < 4; i++)
    {
        if (id[i] < '0' || id[i] > '9')
        {
            return false;
        }
    }
    return true;
}

// Initializing the table and statistics
HashTable::HashTable(size_t capacity)
    : table(capacity), entryCount(0), collisionCount(0)
    {
        if (capacity == 0)
        {
            throw invalid_argument
            (
                "Hash tbale capacity must be greater than zero"
            );
        }
    }

// Custom Polynomial string hash function
size_t HashTable::hashFunction(const string& id) const
{
    size_t hash = 0;

    for (unsigned char ch : id)
    {
        hash = (hash * 31 + ch) % table.size();
    }
    return hash;
}

// Insert an ID into the resulted bucket
// A duplicate ID is rejected without counting a collision
bool HashTable::insert(const string& id, size_t facilityIndex)
{
    string key = normalizeID(id);

    if(!validID(key))
    {
        return false;
    }
    
    size_t bucket = hashFunction(key);

    for (const Entry& entry : table[bucket])
    {
        if (entry.if == key)
        {
            return false;
        }
    }

    if (!table[bucket].empty())
    {
        collisionCount++;
    }

    table[bucket].push_back({key, facilityIndex});
    entryCount++;

    return true;
}

// Searches only the bucket associates with the ID
bool HashTable::search(const string& id, size_t& facilityIndex) const
{
    string key = normalizeID(id);

    if (validID(key))
    {
        return false;
    }

    size_t bucket = hashFunction(key);

    for (const Entry& entry : table[bucket])
    {
        if (entry.id == key)
        {
            facilityIndex = entry.facilityIndex;
            return true;
        }
    }
    return false;
}

//Returns the total number of buckets
size_t HashTable::getCapacity() const
{
    return table.size();
}

// Returns the number of accepted entries
size_t HashTable::getEntryCount() const
{
    return entryCount;
}

// Returns the number of insertion collisions
size_t HashTable:: getCollisionCount() const
{
    return collisionCount;
}