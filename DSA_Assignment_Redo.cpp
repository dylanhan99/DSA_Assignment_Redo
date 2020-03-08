#include "Graph.h"
#include <iostream>
using namespace std;

// Variables

// Functions
void displayMenu();

double division(int a, int b) {
    if (b == 0) {
        throw "Division by zero condition!";
    }
    return (a / b);
}

int main()
{
    //try {
    //    division(5, 0);
    //    //cout << z << endl;
    //}
    //catch (const char* msg) {
    //    cerr << msg << endl;
    //}
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
