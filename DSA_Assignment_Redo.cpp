#include "Graph.h"
#include "File.h"
#include <iostream>
using namespace std;

// Variables
File* Fares, Interchanges, Routes, Stations;

// Functions
bool initFiles();
void displayMenu();


int main()
{
    Graph* graph = new Graph();

    while (true)
    {
        displayMenu();

        int option;
        cout << "Option: ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case 0:
            cout << "Exiting..." << endl;
            return 0;

        case 1:
            continue;

        default:
            cout << "Unknown option..." << endl;
            continue;
        }
    }
}

bool initFiles()
{
    

    return false;
}

void displayMenu()
{
    cout << endl;
    cout << "MENU" << endl;
    cout << "=============================" << endl;
    cout << "1. Display stations on line" << endl;
    cout << "2. Display station information" << endl;
    cout << "3. Add new station" << endl;
    cout << "4. Add new line" << endl;
    cout << "5. Find shortest route" << endl;
    cout << endl;
    cout << "0. Quit" << endl;
    cout << "=============================" << endl;
}
