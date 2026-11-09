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


-- FileLoading.cpp:

-- Handles reading data from the four input files using ifstream
and getline(). Each record is stored with its original line number
using the InputLine structure.

-- Skips empty lines and comments, removes leading and trailing
whitespace, and reports an error if a file cannot be opened.

-- main.cpp:

-- Serves as the starting point of the program and connects
the different modules together.

-- Handles loading data, validating building and connection records,
displaying load summaries, and running the main menu.

-- The menu allows users to display campus connections, view graph
statistics, and find reachable buildings using BFS. Other features...

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

How to run it:
Input Files:

-- buildings.txt   : Contains the names of campus buildings.
-- connections.txt : Contains pairs of connected buildings separated by |.
-- facilities.txt  : Contains facility IDs, names, buildings, and categories.
-- departments.txt : Contains department names and their parent departments.

-- The files are loaded from the data/ directory in the following order:
buildings.txt, connections.txt, facilities.txt, departments.txt.

Compiling and Running the Program:

-- Open a terminal in the Project2 directory.
g++ -std=c++17 -Iinclude src/main.cpp src/FileLoading.cpp src/CampusGraph.cpp src/FacilityDatabase.cpp src/HashTable.cpp src/DepartmentTree.cpp -o campus.exe
Then:
 .\campus.exe 

Optional Data Directory:
-- By default, the program reads data from the data/ folder.
-- A different data directory can be provided through a
command-line argument for testing purposes.

-- Example:
.\campus.exe testdata/case1

-- This allows the program to run using another set of input
files without changing the source code.


Github Repository Link: https://github.com/Emman03-tech/Project2.git
