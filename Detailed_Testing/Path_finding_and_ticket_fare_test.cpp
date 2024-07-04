#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Metro_Station_Management_System.cpp"

using namespace std;

vector<string> getFileNames()
{
    return {"blue.txt", "green.txt", "magenta.txt", "orange.txt", "red.txt", "violet.txt", "yellow.txt"};
}

void testPopulateLine()
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

void testPopulateTree()
{
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
}

vector<string> testFindPath(const string &from, const string &to, int &ticketFare)
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

    cout << "Enter starting station: ";
    getline(cin, from);
    cout << "Enter ending station: ";
    getline(cin, to);

    testPopulateLine();
    testPopulateTree();

    int ticketFare = 0;
    vector<string> path = testFindPath(from, to, ticketFare);

    if (path.empty())
    {
        cout << "No routes found !" << endl;
    }
    else
    {
        cout << "Total ticket fare for this journey: " << ticketFare << endl;
        cout << "This is the path with minimum ticket fare: " << endl;

        // Reverse the path before printing
        reverse(path.begin(), path.end());

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

    return 0;
}
