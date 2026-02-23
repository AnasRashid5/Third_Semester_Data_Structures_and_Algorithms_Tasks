#include <iostream>
#include "circular_linked_list/Circular_LL.cpp"
using namespace std;

int main()
{
    int n, value, choice;
    bool exitProgram = false;

    while (!exitProgram)
    {
        cout << "\n===== Circular Linked List Menu =====" << endl;
        cout << "1. Insert values" << endl;
        cout << "2. Search for a value" << endl;
        cout << "3. Delete a value" << endl;
        cout << "4. Display list" << endl;
        cout << "5. Exit program" << endl;
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

        case 4: // Display
            cout << "Circular list: ";
            display();
            cout << endl;
            break;

        case 5: // Exit
            exitProgram = true;
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Please select a number between 1 and 5." << endl;
            break;
        }
    }

    return 0;
}