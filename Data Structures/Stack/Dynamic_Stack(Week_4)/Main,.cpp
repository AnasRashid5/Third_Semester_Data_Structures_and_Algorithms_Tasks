#include <bits/stdc++.h>
#include "Stack.cpp"
using namespace std;

// DYNAMIC STACK->MEMORY NOT LIMITED
int main()
{
    // STACK HAS ONE ACCESS POINT CALLED TOP, FROM WHERE VALUES ARE BOTH PUSHED AND POPPED.
    // WE CAN TAKE THE EXAMPLE OF A REAL-LIFE STACK LIKE A PILE OF PLATES OR BOOKS. YOU PLACE A NEW PLATE ON TOP AND REMOVE THE TOP PLATE FIRST.
    // BASICALLY, STACK OPERATES ON LIFO(LAST IN FIRST OUT) PRINCIPLE.

    bool flag = false;

    cout << "Enter what to do push or pop." << endl;
    while (!flag)
    {
        int choice = 0;
        cout << "1 for push. 2 for pop. 3 to exit ";
        cin >> choice;

        if (choice == 1)
        {
            int value;
            cout << "Enter value to push ";
            cin >> value;
            push(value);
        }
        else if (choice == 2)
        {
            cout << "value popped: " << pop() << endl;
        }
        else if (choice == 3)
        {
            flag = true;
        }

        else
        {
            cout << "invalid choice " << endl;
        }
    }
}