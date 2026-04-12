#include <iostream>
#include "list/Node.cpp"
using namespace std;

int main()
{
    int n, value, choice;
    bool exitProgram = false;

    while (!exitProgram)
    {
        cout << "\n===== Singly/Doubly Linked List Menu =====" << endl;
        cout << "1. Insert values" << endl;
        cout << "2. Search for a value" << endl;
        cout << "3. Delete a value" << endl;
        cout << "4. Select Sorting Method" << endl;
        cout << "5. Display forward" << endl;
        cout << "6. Display backward" << endl;
        cout << "7. Exit program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Insert
            cout << "How many values do you want to insert? ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter value " << i + 1 << ": ";
                cin >> value;
                insert(value);
            }
            cout << "Values inserted successfully." << endl;
            break;

        case 2: // Search
        {
            int val;
            cout << "Enter value to search: ";
            cin >> val;
            search(val);
            break;
        }

        case 3: // Delete
        {
            int val;
            cout << "Enter value to delete: ";
            cin >> val;
            del(val);
            break;
        }
        case 4:
        {
            int c = 0;
            cout << "Enter 1,2,3 for selection,insertion,bubble "<<endl;
            cin >> c;
            if (c == 1)
            {
                selectionSort();
            }
            break;
        }

        case 5: // Display forward
            cout << "List (forward): ";
            display();
            cout << endl;
            break;

        case 6: // Display backward
            cout << "List (backward): ";
            displayBackward(list);
            cout << endl;
            break;

        case 7: // Exit
            exitProgram = true;
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            break;
        }
    }

    return 0;
}