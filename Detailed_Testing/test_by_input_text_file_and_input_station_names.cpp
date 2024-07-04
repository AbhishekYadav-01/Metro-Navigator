#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Metro_Station_Management_System.cpp"  // Ensure this file contains the definitions for MetroLine, AVLTree, PathFinder, etc.

using namespace std;

vector<string> getFileNames()
{
    vector<string> fileNames;
    string fileName;
    int numberOfFiles;

    cout << "Enter the number of files: ";
    cin >> numberOfFiles;
    cin.ignore(); // Ignore the newline character left in the buffer

    for (int i = 0; i < numberOfFiles; ++i)
    {
        cout << "Enter the name of file " << i + 1 << ": ";
        getline(cin, fileName);
        fileNames.push_back(fileName);
    }

    return fileNames;
}

void testPopulateLine(vector<MetroLine*>& lines)
{
    vector<string> filenames = getFileNames();
    for (int i = 0; i < filenames.size(); i++)
    {
        string lineName = filenames[i].substr(0, filenames[i].length() - 4);
        MetroLine *metroLine = new MetroLine(lineName);
        metroLine->populateLine(filenames[i]);
        lines.push_back(metroLine);
    }
}

void testPopulateTree(AVLTree* tree, const vector<MetroLine*>& lines)
{
    tree->setRoot(nullptr);
    for (auto line : lines)
    {
        if (tree->getRoot() == nullptr)
        {
            tree->setRoot(new AVLNode(line->getHeadStation()->getstationName()));
        }
        tree->populateTree(line);
    }
}

vector<string> testFindPath(const string &from, const string &to, int &ticketFare, const vector<MetroLine*>& lines)
{
    PathFinder *pathFinder = new PathFinder(new AVLTree(), lines);
    pathFinder->createAVLTree();
    Path *path = pathFinder->findPath(from, to);
    ticketFare = path->getTotalticketFare();
    vector<string> pathResult = path->getPath();
    return pathResult;
}

int main()
{
    string from, to;
    vector<MetroLine*> lines;

    testPopulateLine(lines);
    AVLTree* tree = new AVLTree();
    testPopulateTree(tree, lines);
    cout << "Enter starting station: ";
    getline(cin, from);
    cout << "Enter ending station: ";
    getline(cin, to);
    int ticketFare = 0;
    vector<string> path = testFindPath(from, to, ticketFare, lines);

    if (path.empty())
    {
        cout << "No routes found!" << endl;
    }
    else
    {
        cout << "Total ticket fare for this journey: " << ticketFare << endl;
        cout << "This is the path with minimum ticket fare: " << endl;

        for (const auto &stop : path)
        {
            if (&stop != &path.back())
            {
                cout << stop << " -----> ";
            }
            else
            {
                cout << stop << endl;
            }
        }
        cout << "Yahoo! You have reached your destination with the minimum ticket fare." << endl;
    }

    // Clean up dynamic allocations
    delete tree;
    for (auto line : lines)
    {
        delete line;
    }

    return 0;
}
