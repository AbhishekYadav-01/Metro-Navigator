#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string>
#include <stdexcept>
using namespace std;

// Forward declarations
class MetroStation;
class MetroLine;
class AVLNode;
class Trip;
// MetroStation class
class MetroStation {
private:
    std::string stationName;
    MetroStation *nextStation;
    MetroStation *previousStation;
    MetroLine *line;
    int ticketFare;

public:
    // Constructor
    MetroStation(const std::string &name, MetroLine *metroLine, int fare)
        : stationName(name), nextStation(nullptr), previousStation(nullptr), line(metroLine), ticketFare(fare) {}

    // Getters
    std::string getstationName() const {
        return stationName;
    }

    MetroStation *getnextStation() const {
        return nextStation;
    }

    MetroStation *getpreviousStation() const {
        return previousStation;
    }

    MetroLine *getLine() const {
        return line;
    }

    int getticketFare() const {
        return ticketFare;
    }

    // Setters
    void setnextStation(MetroStation *next) {
        nextStation = next;
    }

    void setpreviousStation(MetroStation *prev) {
        previousStation = prev;
    }
};




int string_to_int(const std::string &str) {
    int result = 0;
    for (char c : str) {
        if (c < '0' || c > '9') {
            throw std::invalid_argument("Invalid input string");
        }
        result = result * 10 + (c - '0');
    }
    return result;
}


class MetroLine {
private:
    std::string lineName;
    MetroStation* headStation;

public:
    // Constructor
    MetroLine(const std::string& name) {
        lineName = name;
        headStation = nullptr;
    }

    // Getter
    std::string getLineName() const {
        return lineName;
    }

    MetroStation* getHeadStation() const {
        return headStation;
    }

    int getTotalStations() const {
        int count = 0;
        MetroStation* current = headStation;
        while (current != nullptr) {
            count++;
            current = current->getnextStation();
        }
        return count;
    }

    // Populate line from file
    void populateLine(const std::string& filePath) {
        std::ifstream file(filePath);
        std::string line;
        MetroStation* previous = nullptr;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::istringstream stream(line);
            std::vector<std::string> row;
            std::string word;

            while (std::getline(stream, word, ' ')) {
                row.push_back(word);
            }

            std::string stationName = line.substr(0, line.find_last_not_of("0123456789,") + 1);
            stationName.erase(stationName.find_last_not_of(' ') + 1);

            std::string fareStr = row.back();
            fareStr.erase(std::remove(fareStr.begin(), fareStr.end(), ','), fareStr.end());

            int ticketFare = string_to_int(fareStr);
            MetroStation* station = new MetroStation(stationName, this, ticketFare);

            if (previous != nullptr) {
                previous->setnextStation(station);
                station->setpreviousStation(previous);
            } else {
                headStation = station;
            }

            previous = station;
        }
    }

    // Setter
    void setHeadStation(MetroStation* station) {
        headStation = station;
    }

    // Print the line stations
    void printLine() const {
        MetroStation* current = headStation;
        while (current != nullptr) {
            std::cout << current->getstationName() << std::endl;
            current = current->getnextStation();
        }
    }
};
class AVLNode {
private:
    std::string stationName;
    std::vector<MetroStation *> stops;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

public:
    // Constructor
    explicit AVLNode(std::string name) 
        : stationName(std::move(name)), left(nullptr), right(nullptr), parent(nullptr) {}

    // Getter methods
    std::string getstationName() const { return stationName; }
    const std::vector<MetroStation *> &getStops() const { return stops; }
    AVLNode *getLeft() const { return left; }
    AVLNode *getRight() const { return right; }
    AVLNode *getParent() const { return parent; }

    // Setter methods
    void addMetroStation(MetroStation *station) { stops.push_back(station); }
    void setLeft(AVLNode *leftNode) { left = leftNode; }
    void setRight(AVLNode *rightNode) { right = rightNode; }
    void setParent(AVLNode *parentNode) { parent = parentNode; }
};


// AVLTree class
class AVLTree
{
private:
    AVLNode *root;

public:
    // constructor
    AVLTree()
    {
        root = 0;
    }
    AVLNode *getRoot() const
    {
        return root;
    }

    void setRoot(AVLNode *root)
    {
        this->root = root;
    }

int height(AVLNode *headStation) {
    if (headStation == nullptr) {
        return 0;
    }
    int leftHeight = height(headStation->getLeft());
    int rightHeight = height(headStation->getRight());
    return std::max(leftHeight, rightHeight) + 1;
}


int balanceFactor(AVLNode *headStation) {
    if (headStation == nullptr) {
        return 0;
    }
    int leftHeight = height(headStation->getLeft());
    int rightHeight = height(headStation->getRight());
    return leftHeight - rightHeight;
}


AVLNode *rotateLeft(AVLNode *x) {
    AVLNode *y = x->getRight();
    AVLNode *T2 = y->getLeft();
    AVLNode *x_parent = x->getParent();

    // Perform rotation
    x->setParent(y);
    if (T2 != nullptr) {
        T2->setParent(x);
    }
    y->setLeft(x);
    x->setRight(T2);

    return y;
}


AVLNode *rotateRight(AVLNode *y) {
    AVLNode *x = y->getLeft();
    AVLNode *T2 = x->getRight();
    AVLNode *y_parent = y->getParent();

    // Perform rotation
    y->setParent(x);
    if (T2 != nullptr) {
        T2->setParent(y);
    }
    x->setRight(y);
    y->setLeft(T2);

    return x;
}


int stringCompare(const std::string& s1, const std::string& s2) {
    if (s1 == s2) {
        return 0;
    } else if (s1 < s2) {
        return -1;
    } else {
        return 1;
    }
}


    // inorder traversal
void inOrderTraversal(AVLNode *root) {
    if (root == nullptr) {
        return;
    }
    inOrderTraversal(root->getLeft());
    cout << root->getstationName() << endl;
    inOrderTraversal(root->getRight());
}


    // calculaing lexicographical value
int lex_order(string s1, string s2) {

    int i = 0;
    
    while (i < s1.length() && i < s2.length()) {
        if (int(s1[i]) == int(s2[i])) {
            i++;
            continue;
        } else if (int(s1[i]) < int(s2[i])) {
            return 1;
        } else {
            return 0;
        }
    }
    
    if (s1.length() == s2.length()) {
        return -1;
    } else if (s1.length() < s2.length()) {
        return 1;
    } else {
        return 0;
    }
}


AVLNode* addnode(string &to_add, AVLNode *root, MetroStation *ptr) {
    if (root == nullptr) {
        AVLNode *newNode = new AVLNode(to_add);
        newNode->addMetroStation(ptr);
        return newNode;
    }

    string currentStationName = root->getstationName();

    if (lex_order(to_add, currentStationName) == -1) {
        root->addMetroStation(ptr);
        return root;
    }

    if (lex_order(to_add, currentStationName)) {
        root->setLeft(addnode(to_add, root->getLeft(), ptr));
        root->getLeft()->setParent(root);
    } else {
        root->setRight(addnode(to_add, root->getRight(), ptr));
        root->getRight()->setParent(root);
    }

    int balance = balanceFactor(root);

    if (balance == 2) {
        string leftChildName = root->getLeft()->getstationName();
        if (lex_order(to_add, leftChildName)) {
            return rotateRight(root);
        } else if (!lex_order(to_add, leftChildName)) {
            root->setLeft(rotateLeft(root->getLeft()));
            return rotateRight(root);
        }
    }

    if (balance == -2) {
        string rightChildName = root->getRight()->getstationName();
        if (lex_order(rightChildName, to_add)) {
            return rotateLeft(root);
        } else if (!lex_order(rightChildName, to_add)) {
            root->setRight(rotateRight(root->getRight()));
            return rotateLeft(root);
        }
    }

    return root;
}


void insert(AVLNode *root, MetroStation *MetroStation) {
    string to_add = MetroStation->getstationName();
    AVLNode *newRoot = addnode(to_add, root, MetroStation);
    this->setRoot(newRoot);
}


void populateTree(MetroLine *metroLine) {
    MetroStation *currentStation = metroLine->getHeadStation();
    AVLNode *treeRoot = this->getRoot();
    
    if (treeRoot != nullptr) {
        if (treeRoot->getLeft() == nullptr && treeRoot->getRight() == nullptr) {
            currentStation = currentStation->getnextStation();
        }
    }
    
    if (treeRoot == nullptr) {
        AVLNode *newNode = new AVLNode(currentStation->getstationName());
        newNode->addMetroStation(currentStation);
        this->setRoot(newNode);
        currentStation = currentStation->getnextStation();
    }
    
    while (currentStation != nullptr) {
        insert(this->getRoot(), currentStation);
        currentStation = currentStation->getnextStation();
    }
}


int getTotalNodes(AVLNode *headStation) {
    if (headStation == nullptr) {
        return 0;
    }
    int leftCount = getTotalNodes(headStation->getLeft());
    int rightCount = getTotalNodes(headStation->getRight());
    return leftCount + rightCount + 1;
}


AVLNode *search(AVLNode *headStation, string &stationName) {
    if (headStation == nullptr) {
        return nullptr;
    }

    if (headStation->getstationName() == stationName) {
        return headStation;
    }

    AVLNode *foundNode = search(headStation->getLeft(), stationName);
    if (foundNode != nullptr) {
        return foundNode;
    }

    return search(headStation->getRight(), stationName);
}


    AVLNode *searchStop(string stationName)
    {
        return search(this->getRoot(), stationName);
    }
};

// Exploration class
class Exploration {
private:
    std::queue<Trip *> trips;

public:
    // Constructor
    Exploration() = default;

    // Getter
    std::queue<Trip *> getTrips() const {
        return trips;
    }

    // Functions
    void enqueue(Trip *trip) {
        trips.push(trip);
    }

    Trip *dequeue() {
        if (trips.empty()) {
            return nullptr;
        }
        Trip *trip = trips.front();
        trips.pop();
        return trip;
    }

    bool isEmpty() const {
        return trips.empty();
    }
};


// Trip class
class Trip
{
private:
    MetroStation *headStation;
    Trip *prev;

public:
    // Constructor
    Trip(MetroStation *MetroStation, Trip *previousTrip = nullptr)
        : headStation(MetroStation), prev(previousTrip)
    {
    }

    // Getter for headStation
    MetroStation *getHeadStation() const
    {
        return headStation;
    }

    // Getter for prev
    Trip *getPrev() const
    {
        return prev;
    }

    // Setter for prev
    void setPrev(Trip *previousTrip)
    {
        prev = previousTrip;
    }
};


class Path
{
private:
    std::vector<MetroStation *> stops;
    int totalticketFare;

public:
    // Constructor
    Path() : totalticketFare(0)
    {
    }

    // Getter for stops
    std::vector<MetroStation *> getStops() const
    {
        return stops;
    }

    // Getter for totalticketFare
    int getTotalticketFare() const
    {
        return totalticketFare;
    }

    // Add a stop to the path
    void addStop(MetroStation *stop)
    {
        stops.push_back(stop);
    }

    // Set the total ticket fare
    void setTotalticketFare(int ticketFare)
    {
        totalticketFare = ticketFare;
    }

    // Get the names of the stations in the path
    std::vector<std::string> getPath() const
    {
        std::vector<std::string> ans;
        for (const auto& stop : stops)
        {
            ans.push_back(stop->getstationName());
        }
        return ans;
    }
};


class PathFinder
{
private:
    AVLTree *tree;
    std::vector<MetroLine *> lines;

public:
    std::string starting_location;

    // Constructor
    PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines)
        : tree(avlTree), lines(metroLines)
    {
    }

    // Getter for AVL tree
    AVLTree *getTree() const
    {
        return tree;
    }

    // Getter for metro lines
    const std::vector<MetroLine *> &getLines() const
    {
        return lines;
    }

    // Populate the AVL tree with metro lines
    void createAVLTree()
    {
        for (auto &metroline : lines)
        {
            tree->populateTree(metroline);
        }
    }

// Search path going left
Trip *searchpath_left(std::string start, std::string end, std::vector<std::string> junctions, std::vector<Path *> &paths, Trip *previous_tail)
{
    Trip *tail = nullptr;
    auto stops = tree->searchStop(start)->getStops();
    auto it = stops.begin();
    
    while (it != stops.end())
    {
        auto current = *it;
        tail = nullptr;
        int firstTime = 0;

        for (;;)
        {
            if (!current)
            {
                break;
            }
            Trip *trip = new Trip(current, tail);
            if (firstTime == 0)
            {
                trip->setPrev(previous_tail);
                firstTime = 1;
            }
            tail = trip;
            if (current->getstationName() == end)
            {
                Trip *trip = tail;
                Path *path = new Path();
                while (trip)
                {
                    path->addStop(trip->getHeadStation());
                    trip = trip->getPrev();
                }
                paths.push_back(path);
                return nullptr;
            }
            if (std::find(junctions.begin(), junctions.end(), current->getstationName()) != junctions.end())
            {
                return nullptr;
            }
            auto nextStops = tree->searchStop(current->getstationName())->getStops();
            if (nextStops.size() != 1)
            {
                junctions.push_back(current->getstationName());
                for (auto &nextStop : nextStops)
                {
                    if (nextStop->getnextStation())
                    {
                        searchpath_right(nextStop->getnextStation()->getstationName(), end, junctions, paths, tail);
                    }
                    if (nextStop->getpreviousStation())
                    {
                        searchpath_left(nextStop->getpreviousStation()->getstationName(), end, junctions, paths, tail);
                    }
                }
                return nullptr;
            }
            current = current->getpreviousStation();
        }
        ++it;
    }
    return nullptr;
}


    // Search path going right
   Trip *searchpath_right(std::string start, std::string end, std::vector<std::string> junctions, std::vector<Path *> &paths, Trip *previous_tail)
{
    Trip *tail = nullptr;
    auto stops = tree->searchStop(start)->getStops();
    
    for (auto &current : stops)
    {
        tail = nullptr;
        int firstTime = 0;
        
        while (true)
        {
            if (!current)
            {
                break;
            }
            Trip *trip = new Trip(current, tail);
            if (firstTime == 0)
            {
                trip->setPrev(previous_tail);
                firstTime = 1;
            }
            tail = trip;
            if (current->getstationName() == end)
            {
                Trip *trip = tail;
                Path *path = new Path();
                while (trip)
                {
                    path->addStop(trip->getHeadStation());
                    trip = trip->getPrev();
                }
                paths.push_back(path);
                return nullptr;
            }
            if (std::find(junctions.begin(), junctions.end(), current->getstationName()) != junctions.end())
            {
                return nullptr;
            }
            auto nextStops = tree->searchStop(current->getstationName())->getStops();
            if (nextStops.size() != 1)
            {
                junctions.push_back(current->getstationName());
                for (auto &nextStop : nextStops)
                {
                    if (nextStop->getnextStation())
                    {
                        searchpath_right(nextStop->getnextStation()->getstationName(), end, junctions, paths, tail);
                    }
                    if (nextStop->getpreviousStation())
                    {
                        searchpath_left(nextStop->getpreviousStation()->getstationName(), end, junctions, paths, tail);
                    }
                }
                return nullptr;
            }
            current = current->getnextStation();
        }
    }
    return nullptr;
}


    // Find the shortest path
    Path *findPath(std::string origin, std::string destination)
    {
        std::vector<std::string> junction_v;
        std::vector<std::string> junction_v_2;
        junction_v.push_back(origin);
        starting_location = origin;
        Path *ans = nullptr;
        int ticketFare = 0;
        auto curr = tree->searchStop(origin)->getStops().front();
        std::vector<Path *> possible_path;
        Trip *tail_right = new Trip(curr, nullptr);
        Trip *tail_left = new Trip(curr, nullptr);
        if (curr->getnextStation())
        {
            searchpath_right(curr->getnextStation()->getstationName(), destination, junction_v, possible_path, tail_right);
        }
        if (curr->getpreviousStation())
        {
            searchpath_left(curr->getpreviousStation()->getstationName(), destination, junction_v_2, possible_path, tail_left);
        }
        if (possible_path.empty())
        {
            return new Path();
        }
        int min = INT_MAX;
        for (auto &path : possible_path)
        {
            if (path->getStops().size() < min)
            {
                ans = path;
                min = path->getStops().size();
            }
        }
        auto stops = ans->getStops();
        for (size_t i = 0; i < stops.size() - 1; ++i)
        {
            if (stops[i + 1]->getLine()->getLineName() != stops[i]->getLine()->getLineName())
            {
                auto v1 = tree->searchStop(stops[i]->getstationName())->getStops();
                auto v2 = tree->searchStop(stops[i + 1]->getstationName())->getStops();
                bool found = false;
                for (auto &s1 : v1)
                {
                    if (found)
                    {
                        break;
                    }
                    for (auto &s2 : v2)
                    {
                        if (s1->getLine()->getLineName() == s2->getLine()->getLineName())
                        {
                            if (s1->getnextStation() && s1->getnextStation()->getstationName() == s2->getstationName())
                            {
                                ticketFare += abs(s2->getticketFare() - s1->getticketFare());
                                found = true;
                                break;
                            }
                            if (s1->getpreviousStation() && s1->getpreviousStation()->getstationName() == s2->getstationName())
                            {
                                ticketFare += abs(s2->getticketFare() - s1->getticketFare());
                                found = true;
                                break;
                            }
                        }
                    }
                }
                continue;
            }
            ticketFare += abs(stops[i]->getticketFare() - stops[i + 1]->getticketFare());
        }
        ans->setTotalticketFare(ticketFare);
        return ans;
    }
};

vector<MetroLine *> lines;

