#include <iostream>
#include "Binary_Tree.cpp"
using namespace std;

int main()
{

    Binary_Tree tree;
    Binary_Tree *root = nullptr;
    int n, value, t = 0;
    bool flag = false;

    // Node node;

    cout << "Enter 1 to insert" << endl;
    cout << "Enter 2 to search" << endl;
    cout << "Enter 3 to delete" << endl;
    cout << "Enter 4 to display" << endl;
    cout << "Enter 5 to exit " << endl
         << endl;
    while (!flag)
    {
        cout << "Enter Choice :";
        cin >> t;

        if (t == 1)
        {

            for (int i = 0; i < 5; i++)
            {
                cout << "Enter Value:";
                cin >> value;
                cout << endl;
                root = tree.insert(root, value);
                /* code */
            }

            // display();
        }
        else if (t == 2)
        {
            int val;
            cout << "Enter what to search ";
            cin >> val;

            if (!tree.search(root, val))
            {
                cout << "Tree is empty or no such value found" << endl;
            }
            else
            {

                cout << "Value Found" << endl;
            }
        }
        else if (t == 3)
        {
            int val;
            cout << "Enter what to delete ";
            cin >> val;
            tree.del(root, val);
        }
        else if (t == 4)
        {
            // tree.display();
            int choice = 0;
            cout << "Enter which traversal to use ";
            cout << "1 for PREORDER , 2 for POSTORDER , 3 for INORDER ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                tree.preorder(root);
                break;
            case 2:
                tree.postorder(root);
                break;

            case 3:

                tree.inorder(root);
                break;

            default:
                cout << "Invalid input!";
                break;
            }
        }
        else if (t == 5)
        {
            /// to exit program
            // flag = true;
            exit(flag);
        }
        else
        {
            cout << "enter a valid choice from available options." << endl;
        }
    }
}