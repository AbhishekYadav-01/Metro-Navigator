#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Metro_Station_Management_System.cpp"

using namespace std;

// For adding new .txt file we can add file here.
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

void testPopulateLine(const vector<string>& filenames)
{
    for (int i = 0; i < filenames.size(); i++)
    {
        string lineName = filenames[i].substr(0, filenames[i].length() - 4);
        MetroLine *metroLine = new MetroLine(lineName);
        metroLine->populateLine(filenames[i]);
        lines.push_back(metroLine);
    }
}

void printTree(AVLNode* root, string indent = "", bool isLeft = true)
{
    if (root != nullptr)
    {
        cout << indent;
        if (isLeft)
        {
            cout << "L----";
            indent += "|    ";
        }
        else
        {
            cout << "R----";
            indent += "     ";
        }
        cout << root->getstationName() << endl;
        printTree(root->getLeft(), indent, true);
        printTree(root->getRight(), indent, false);
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
    cout << "Height of tree: " << tree->height(tree->getRoot()) << endl;
    cout << "Total nodes in tree: " << tree->getTotalNodes(tree->getRoot()) << endl;

    cout << "Tree structure:\n";
    printTree(tree->getRoot());
}

int main()
{
    vector<string> filenames = getFileNames();
    testPopulateLine(filenames);
    testPopulateTree();

    return 0;
}
