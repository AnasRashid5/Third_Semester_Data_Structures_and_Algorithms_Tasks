#include <iostream>
#include "Closed_Hashing.cpp"
using namespace std;

/*
CLOSED HASHING (OPEN ADDRESSING)

Idea:
Closed hashing (open addressing) handles collisions differently from separate chaining:
- All elements are stored directly in the hash table array.
- When a collision occurs, a probe sequence is followed to find the next available slot.
- Common probing strategies: linear probing, quadratic probing, double hashing.
- Lookup, insertion, and deletion operate by following the probe sequence.
*/

int main()
{
    int choice;
    bool exitProgram = false;
    int probeType; // 1 = Linear, 2 = Quadratic

    // HERE WE ARE ADDING FALSE IN A SECOND ARRAY TO TRACK INDEXES ARE FILLED OR NOT.
    // FALSE DETERMINES INDEX IS NOT OCCUPIED WHILE TRUE DETERMINES INDEX IS OCCUPIED.
    // SO AT THE VERY FIRST PROGRAM RUNS I HAD FILLED THE ARRAY WITH FALSE SO INITIALLY ARRAY IS EMPTY.

    int j = 0;
    while (j < 10)
    {
        state[j] = 0;
        j++;
    }

    // Ask user for probing method once at the start
    cout << "Choose probing method for this session:\n1. Linear Probing\n2. Quadratic Probing\nEnter choice: ";
    cin >> probeType;

    cout << "\n===== Hash Table Menu (Closed Hashing) =====" << endl;
    cout << "1. Insert a value" << endl;
    cout << "2. Display hash table" << endl;
    cout << "3. Search for a value" << endl;
    cout << "4. Delete a value" << endl;
    cout << "5. Exit program" << endl;

    while (!exitProgram)
    {
        cout << endl
             << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Insert
        {
            int val;
            cout << "Enter value to insert into hash table: ";
            cin >> val;

            if (probeType == 1)
                insert(val); // Linear
            else
                insertQuadratic(val); // Quadratic (you need to define this)

            break;
        }

        case 2: // Display
            cout << "Hash table contents:" << endl;
            display(arr, 0);
            break;

        case 3: // Search
        {
            int val;
            cout << "Enter value to search in hash table: ";
            cin >> val;

            if (probeType == 1)
            {
                if (!search(val, 0)) // Linear
                {
                    cout << "Value not found" << endl;
                    return 0;
                }

                cout << "Value found" << endl;
            }

            else
            {
                if (!searchQuadratic(val, 0)) // Quadratric
                {
                    cout << "Value not found" << endl;
                    return 0;
                }

                cout << "Value found" << endl;
            }

            break;
        }

        case 4: // Delete
        {
            int val;
            cout << "Enter value to delete from hash table: ";
            cin >> val;

            if (probeType == 1)
                remove(val, 0); // Linear
            else
                removeQuadratic(val, 0); // Quadratic

            break;
        }

        case 5: // Exit
            exitProgram = true;
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid input! Please enter a number between 1 and 5." << endl;
            break;
        }
    }

    return 0;
}