#include <iostream>
#include "DynamicQueue.cpp"

using namespace std;

int main()
{
    DynamicQueue queue;
    bool flag = false;

    cout << "Enter what to do 1 for enqueue.2 for dequeue." << endl;

    while (!flag)
    {
        int choice = 0;
        cout << "1 for enqueue. 2 for dequeue. 3 to exit ";
        cin >> choice;

        if (choice == 1)
        {
            int value;
            cout << "Enter value to enter ";
            cin >> value;
            queue.enqueue(value);
        }
        else if (choice == 2)
        {
            cout << "value removed: " << queue.dequeue() << endl;
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