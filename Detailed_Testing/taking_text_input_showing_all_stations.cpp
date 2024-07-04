#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Metro_Station_Management_System.cpp"

using namespace std;

vector<string> getFileNames()
{
    vector<string> fileNames;
    string fileName;
    int numberOfFiles;

    cout << "Enter the number of files: ";
    cin >> numberOfFiles;
    cin.ignore();

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
        cout << endl;
        cout << "Line name: " << metroLine->getLineName() << endl;
        cout << "Total stops: " << metroLine->getTotalStations() << endl;
        cout << endl;
        metroLine->printLine();

    }
}


int main()
{
    vector<string> filenames = getFileNames();
    testPopulateLine(filenames);

    return 0;
}
