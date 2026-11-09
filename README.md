# Project-2-Smart-Campus-Navigation-and-Facility-Analytics-System

# Overview 
The Smart Campus Navigation and Facility Analytics System is
a C++ application designed to manage campus facilities, building
connections, and academic departments

3 main data structures used:
- Custom Hash Table for storing and searching facility ID's
- Undirected graph for representing campus buildings and connections
- General tree for organizing academic departments

Menu-driven interface program that reads information from the text facilities
and allows users to interact with the data


# Structure
-- 'Include/' : header files (.hpp)
-- src/     : Implementation files (.cpp)
-- data/    : input files 
-- testdata/ : adiitional test cases
-- README.text
-- CONTRIBUTIONS.txt : Team member contribution to project summary
-- Design_document.txt : Data structures, algorithms and design decisions
-- test_results.txt    : Test Scenarios
-- .gitignore          : excludes compiled executables and object files 


-- FacilityDatabase.cpp : Stores facility records containing an ID, facility name, building name,
and category. Responsible for validating facility records, displaying facilities and searching by 
facility ID.

-- HashTable.cpp : Uses facility ID as keys and facility positions as values. Uses custom hash strings
function and seperate chaining with buckets to handle collisions. 

-- CampusGraph.cpp : Campus Graph represents buildings as vertices and direct walkways as 
undirected edges. Displays building connectiosn, calculating graph counts and degrees, and
using Breadth First Search (BFS).

-- DepartmentTree.cpp : The tree represents the academic department hierarchy using a General
tree. Includes adding departments, searching for departments, displaying the hierarchy and performing
preorder traversal.


Github Repository Link: https://github.com/Emman03-tech/Project2.git
