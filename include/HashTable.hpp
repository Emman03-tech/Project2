#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
#include <vector>
#include <cstddef>

// Create custom hash table for easy facility ID lookup
// using seperating chaining to handle collisions

class HashTable
{
    private:
    struct Entry
    {
        std:: string id;
        std:: size_t facilityIndex;
    };

    static const std:: size_t DEFAULT_CAPACITY = 17;

    std::vector<std::vector<Entry>> table;
    std::size_t entryCount;
    std::size_t collisionCount;

    // Calculate the bucket for normal facility ID
    std::size_t hashFunction(const std::string& id) const;

    public:
    // creates hash table with the specified capacity
    explicit HashTable
    (
        std::size_t capacity = DEFAULT_CAPACITY
    );

    // Inserts an ID and its index in the facility database
    // Returns false if ID already exists
    bool insert(const std::string& id, std::size_t facilityIndex);

    //Returns the number of buckets
    std::size_t getCapacity() const;

    //Returns the number of store IDs
    std::size_t getEntryCount() const;

    //Returns collisions from successful insertions
    std::size_t getCollisionCount() const;
};

#endif