# Metro Station Management System

This project implements a Metro Station Management System using advanced data structures in C++. The system efficiently manages metro lines and stations, supports real-time route planning, and calculates optimal ticket fares using pathfinding algorithms. Designed to handle large datasets, the system ensures rapid data retrieval and minimal computational overhead.

## Features

- **Efficient Management**: Handles metro lines and stations with ease.
- **Real-time Route Planning**: Supports dynamic and efficient route planning.
- **Optimal Fare Calculation**: Utilizes pathfinding algorithms for accurate and optimal fare calculations.
- **Scalability**: Capable of managing large datasets with rapid data retrieval.

## Programming Language

- **C++**: Developed entirely in C++, ensuring high performance, reliability, and extensive use of Object-Oriented Programming (OOP) principles.

## System Design

The system is designed to handle large datasets efficiently, ensuring rapid data retrieval and minimal computational overhead. The architecture includes:

- **Data Layer**: Manages all data-related operations using efficient data structures.
- **Logic Layer**: Contains business logic for route planning and fare calculation.
- **Presentation Layer**: Provides a simple and user-friendly interface for interaction.

## Implementation Details

- **Data Structures**: Utilizes data structures to ensure efficient data handling and retrieval.
- **Pathfinding Algorithms**: Implements algorithms to compute the shortest routes and fare calculations, enhancing user experience and operational efficiency.
- **C++**: Developed entirely in C++, ensuring high performance and reliability.

## Class and Source File Details

### AVLNode (AVLNode.cpp)

- **Attributes**: `stationName`, `left`, `right`, `height`.
- **Methods**: `getStationName()`, `getLeft()`, `getRight()`, `getHeight()`, `setLeft()`, `setRight()`, `setHeight()`.
- **Description**: Represents a node in the AVL tree, storing the station name and pointers to its left and right children, along with the height of the node for balancing purposes.

### AVLTree (AVLTree.cpp)

- **Attributes**: `root`.
- **Methods**: `setRoot()`, `getRoot()`, `populateTree()`, `height()`, `getTotalNodes()`, `insert()`, `balanceTree()`, `leftRotate()`, `rightRotate()`.
- **Description**: Provides methods for inserting nodes, balancing the tree, performing rotations (left and right), and calculating the height of the tree and the total number of nodes.

### Exploration (Exploration.cpp)

- **Description**: Handles various exploration and traversal tasks within the metro system, including depth-first search (DFS), breadth-first search (BFS), and other exploration algorithms to analyze the metro network.

### MetroLine (MetroLine.cpp)

- **Attributes**: `lineName`, `headStation`, `stations`.
- **Methods**: `populateLine()`, `getLineName()`, `getHeadStation()`, `getTotalStations()`.
- **Description**: Manages a specific metro line, including populating the line with stations, adding new stations, and retrieving information about the line such as its name and total number of stations.

### MetroStation (MetroStation.cpp)

- **Attributes**: `stationName`, `nextStation`, `connections`.
- **Methods**: `getStationName()`, `addConnection()`, `getNextStation()`.
- **Description**: Represents individual metro stations, including methods for managing connections between stations, retrieving station information, and handling the station's position within a line.

### Path (Path.cpp)

- **Attributes**: `stations`, `totalFare`.
- **Methods**: `addStation()`, `getPath()`, `getTotalFare()`.
- **Description**: Represents a path through the metro system, including methods for adding stations to the path, retrieving the entire path, and calculating the total fare for the path.

### PathFinder (PathFinder.cpp)

- **Attributes**: `avlTree`, `lines`.
- **Methods**: `createAVLTree()`, `findPath()`.
- **Description**: Responsible for finding the optimal path between two stations, using pathfinding algorithms to compute the shortest route and calculate the corresponding fare.

## Detailed Testing

These files allow you to test the system:

- **Path_finding_and_ticket_fare_test.cpp**: Test pathfinding and ticket fare calculation.
- **see_created_avl_tree_of_stations_without_giving_any_input.cpp**: View the created AVL tree of stations without providing any input.
- **see_created_avl_tree_of_stations_by_giving_input_text_file.cpp**: View the created AVL tree of stations by providing an input text file.
- **taking_text_input_showing_all_stations.cpp**: Take text input and display all stations.
- **test_by_input_text_file_and_input_station_names.cpp**: Test the system by providing an input text file and station names.

**Steps :**

Collect all dataset file in same folder then , add `Metro_Station_Management_System.cpp` file in same folder then test whatever you want from the above list, by adding that testing file in same folder.
