#include <iostream>
#include "list/Node.cpp"
using namespace std;

int main()
{

    int n, value, t = 0;
    bool flag = false;

    // Node node;

    while (!flag)
    {
        cout << "Enter 1 to insert.  2 to search.  3 to delete.  4 to display.  5 to exit the program.";
        cin >> t;

        if (t == 1)
        {
            cout << "Enter Number of Values you want:";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter Values:";
                cin >> value;
                insert(value);
            }
            // display();
        }
        else if (t == 2)
        {
            int val;
            cout<<"Enter what to search ";
            cin>>val;
            search(val);
        }
        else if (t == 3)
        {
            int val;
            cout<<"Enter what to delete ";
            cin>>val;            
            del(val);
        }
        else if (t == 4)
        {
            display();
        }
        else if (t == 5)
        {
            ///to exit program
            // flag = true;
            exit(flag);
        }
        else{
            cout<<"enter a valid choice from available options.";
        }
    }
}