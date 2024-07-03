#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Metro_Station_Management_System.cpp"
using namespace std;

vector<string> getFileNames() {
    return {"blue.txt", "green.txt", "magenta.txt", "orange.txt", "red.txt", "violet.txt", "yellow.txt"};
}

void testPopulateLine()
{
   // cout << "Testing populateLine()" << endl;
    vector<string> filenames = getFileNames();
    int expectedTotalStops[] = {44, 21, 25, 6, 29, 38, 62};
    for (int i = 0; i < filenames.size(); i++)
    {
        string lineName = filenames[i].substr(0, filenames[i].length() - 4);
        MetroLine *metroLine = new MetroLine(lineName);
        metroLine->populateLine(filenames[i]);
        lines.push_back(metroLine);
        // cout << "Line name: " << metroLine->getLineName() << endl;
        // cout << "Total stops: " << metroLine->getTotalStations() << endl;
        //cout << endl;
        assert(metroLine->getTotalStations() == expectedTotalStops[i]);
        // metroLine->printLine();
    }
   // cout << "populateLine() tests passed!" << endl;
}

void testPopulateTree()
{
    //cout << "Testing populateTree()" << endl;
    vector<string> filenames = getFileNames();
    AVLTree *tree = new AVLTree();
    tree->setRoot(nullptr);
    for (auto line : lines)
    {
        if (tree->getRoot() == nullptr)
        {
            tree->setRoot(new AVLNode(line->getHeadStation()->getstationName()));
        }
        tree->populateTree(line);
    }
    // cout << "Height of tree: " << tree->height(tree->getRoot()) << endl;
    // cout << "Total nodes in tree: " << tree->getTotalNodes(tree->getRoot()) << endl;
    // assert(tree->height(tree->getRoot()) == 9);
    assert(tree->getTotalNodes(tree->getRoot()) == 211);
   // cout << "populateTree() tests passed!" << endl;
}

vector<string> getExpectedPath() {
    return {"Pul Bangash", "Pratap Nagar", "Shastri Nagar", "Inder Lok", "Kanhaiya Nagar", "Keshav Puram", "Netaji Subhash Place", "Kohat Enclave", "Pitampura"};
}


vector<string> testFindPath(string from, string to, int &fare)
{
    PathFinder *pathFinder = new PathFinder(new AVLTree(), lines);
    pathFinder->createAVLTree();
    Path *path = pathFinder->findPath(from, to);
    assert(path != nullptr);
    fare = path->getTotalticketFare();
    vector<string> resultPath = path->getPath();
    vector<string> expectedPath = getExpectedPath();
    
    // Reverse the expected path to match the actual path
    reverse(expectedPath.begin(), expectedPath.end());

    // Debugging: Print actual and expected paths
    // cout << "Actual Path: ";
    // for (const auto &stop : resultPath)
    // {
    //     cout << stop << " ";
    // }
    // cout << endl;

    // cout << "Expected Path: ";
    // for (const auto &stop : expectedPath)
    // {
    //     cout << stop << " ";
    // }
    // cout << endl;

    for (int i = 0; i < expectedPath.size(); i++)
    {
        if (path->getStops()[i]->getstationName() != expectedPath[i])
        {
            cout << "Mismatch at position " << i << ": expected " << expectedPath[i]
                 << " but got " << path->getStops()[i]->getstationName() << endl;
        }
        assert(path->getStops()[i]->getstationName() == expectedPath[i]);
    }
 //   cout << "findPath() tests passed!" << endl;
    return resultPath;
}

int main()
{
    try
    {
        testPopulateLine();
        testPopulateTree();
        int fare = 0;
        vector<string> path;
        string from = "Pul Bangash";
        string to = "Pitampura";
        path = testFindPath(from, to, fare);
       // cout << "Fare: " << fare << endl;
        // for (auto i : path)
        // {
        //     cout << i << endl;
        // }
        cout << "All test cases passed!" << endl;
    }
    catch (const exception &e)
    {
        cerr << "A test case failed: " << e.what() << endl;
    }
    return 0;
}
