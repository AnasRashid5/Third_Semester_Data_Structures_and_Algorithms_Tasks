#include <iostream>
#include "Seperate_Chaining.cpp"
using namespace std;

/*
SEPARATE CHAINING - HASH TABLE

Idea:
Separate chaining is a technique to handle collisions in a hash table.
When two or more elements hash to the same index:
- Each index stores a linked list (or another dynamic structure)
- All elements that hash to the same index are stored in that list
- Lookup, insertion, and deletion operate within the list at that index
*/

int main()
{
    int choice;
    bool exitProgram = false;

    while (!exitProgram)
    {
        cout << "\n===== Hash Table Menu (Separate Chaining) =====" << endl;
        cout << "1. Insert a value" << endl;
        cout << "2. Display hash table" << endl;
        cout << "3. Search for a value" << endl;
        cout << "4. Exit program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Insert
        {
            int val;
            cout << "Enter value to insert into hash table: ";
            cin >> val;
            insert(val);
            break;
        }

        case 2: // Display
            cout << "Hash table contents:" << endl;
            display();
            break;

        case 3: // Search
        {
            int val;
            cout << "Enter value to search in hash table: ";
            cin >> val;
            search(val);
            break;
        }

        case 4: // Exit
            exitProgram = true;
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid input! Please enter a number between 1 and 4." << endl;
            break;
        }
    }

    return 0;
}