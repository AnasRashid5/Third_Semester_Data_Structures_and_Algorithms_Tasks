#include <iostream>
#include "StaticQueue.cpp"
using namespace std;
int main()
{
    // cout<<"inside main";
    StaticQueue queue;
    bool flag = false;

    cout << "Enter what to do 1 for enqueue.2 for dequeue.3 to display" << endl;

    while (!flag)
    {
        int choice = 0;
        cout << "1 for enqueue. 2 for dequeue. 3 to display. 4 to exit ";
        cin >> choice;

        if (choice == 1)
        {
            int value;
            cout << "Enter value to enter ";
            cin >> value;
            queue.enqueue(value);
        }
        else if (choice==2)
        {
            cout<<queue.dequeue()<<endl;
        }
        else if (choice == 3)
        {
            // cout << "value removed: " << queue.dequeue() << endl;
            queue.display();
        }
        else if (choice == 4)
        {
            flag = true;
        }

        else
        {
            cout << "invalid choice " << endl;
            bool flag=true;
            cout<<flag;
        }
    }
}