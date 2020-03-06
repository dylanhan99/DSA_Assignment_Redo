#include <iostream>
using namespace std;

void DisplayMenu();


int main()
{
    while (true)
    {
        DisplayMenu();

        int option;
        cout << "Option: ";
        cin >> option;
        cout << endl;
    }
}

void DisplayMenu()
{
    cout << "=============================" << endl;
    cout << "1. Display stations on line" << endl;
    cout << "2. Display station information" << endl;
    cout << "3. Add new station" << endl;
    cout << "4. Add new line" << endl;
    cout << "5. Find shortest route" << endl;
    cout << "=============================" << endl;
}
