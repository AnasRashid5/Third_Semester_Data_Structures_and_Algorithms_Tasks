#include <iostream>
using namespace std;

class Avl_own
{
    int data;
    Avl_own *leftChild;
    Avl_own *rightChild;
    int height;

public:
    int heightCalculator(Avl_own *current)
    {
        if (current->leftChild == nullptr && current->rightChild == nullptr)
        {
            return 0;
        }
        if (current->rightChild == nullptr)
        {
            return current->leftChild->height + 1;
        }
        if (current->leftChild == nullptr)
        {
            return current->rightChild->height + 1;
        }
        return max(current->leftChild->height, current->rightChild->height) + 1;
    }

    int balanceFactor(Avl_own *current)
    {
        if (current->rightChild == nullptr && current->leftChild == nullptr)
        {
            return 0;
        }
        if (current->rightChild == nullptr)
        {
            return current->leftChild->height + 1;
        }
        if (current->leftChild == nullptr)
        {
            return (current->rightChild->height + 1) * (-1);
        }
        return current->leftChild->height - current->rightChild->height;
    }

    Avl_own *rotateRight(Avl_own *curr)
    {
        Avl_own *temp = curr;
        curr = curr->leftChild;

        Avl_own *temp2 = curr->rightChild;
        curr->rightChild = temp;
        temp->leftChild = temp2;

        temp->height = heightCalculator(temp);
        curr->height = heightCalculator(curr);
        return curr;
    }

    Avl_own *rotateLeft(Avl_own *curr)
    {
        Avl_own *temp = curr;
        curr = curr->rightChild;

        Avl_own *temp2 = curr->leftChild;
        curr->leftChild = temp;
        temp->rightChild = temp2;

        temp->height = heightCalculator(temp);
        curr->height = heightCalculator(curr);
        return curr;
    }
    Avl_own *rotateLeftRight(Avl_own *curr)
    {
        curr->leftChild = rotateLeft((curr->leftChild));
        curr = rotateRight(curr);
        return curr;
    }
    Avl_own *rotateRightLeft(Avl_own *curr)
    {
        curr->rightChild = rotateRight(curr->rightChild);
        curr = rotateLeft(curr);
        return curr;
    }

    Avl_own *insert(Avl_own *curr, int val)
    {
        if (curr == nullptr)
        {
            Avl_own *temp = new Avl_own;
            temp->data = val;
            temp->leftChild = nullptr;
            temp->rightChild = nullptr;
            temp->height = 0;
            return temp;
        }
        if (val < curr->data)
        {
            curr->leftChild = insert(curr->leftChild, val);

            if (balanceFactor(curr) == 2)
            {
                if (val < curr->leftChild->data)
                {
                    curr = rotateRight(curr);
                }
                else
                {
                    curr = rotateLeftRight(curr);
                }
            }
        }
        else
        {
            curr->rightChild = insert(curr->rightChild, val);

            if (balanceFactor(curr) == -2)
            {
                if (val > curr->rightChild->data)
                {
                    curr = rotateLeft(curr);
                }
                else
                {
                    curr = rotateRightLeft(curr);
                }
            }
        }
        curr->height = heightCalculator(curr);
        return curr;
    }

    Avl_own *del(Avl_own *curr, int val)
    {

        if (curr == nullptr)
        {
            cout << "Nothing inside avl to delete." << endl;
            return NULL;
        }
        if (curr->data == val)
        {
            // FOR Zero Child::
            if (curr->rightChild == nullptr && curr->leftChild == nullptr)
            {
                // curr->height = 0;
                delete (curr);
                curr = nullptr;
                return curr;
            }

            // FOR One Child::
            if (curr->leftChild == nullptr)
            {
                Avl_own *temp = curr->rightChild;
                delete (curr);

                return temp;
            }
            // FOR One Child::
            if (curr->rightChild == nullptr)
            {
                Avl_own *temp = curr->leftChild;
                delete (curr);
                return temp;
            }
            // if both childs available:we use inorder successor means go right node then go to most left of right node we will find the smallest number of that subtree copy to head and delete that original copied node  :

            Avl_own *temp = curr->rightChild;

            while (temp->leftChild != nullptr)
            {
                temp = temp->leftChild;
            }
            curr->data = temp->data;
            curr->rightChild = del(curr->rightChild, temp->data);
            curr->height = heightCalculator(curr);
        }
        else
        {
            if (val > curr->data)
            {
                curr->rightChild = del(curr->rightChild, val);
                curr->height = heightCalculator(curr);
            }
            else
            {
                curr->leftChild = del(curr->leftChild, val);
                curr->height = heightCalculator(curr);
            }
        }
        if (balanceFactor(curr) == 2)
        {
            if (balanceFactor(curr->leftChild) >= 0)
            {
                curr = rotateRight(curr);
            }
            else
            {
                curr = rotateLeftRight(curr);
            }
        }
        if (balanceFactor(curr) == -2)
        {
            if (balanceFactor(curr->rightChild) <= 0)
            {
                curr = rotateLeft(curr);
            }
            else
            {
                curr = rotateRightLeft(curr);
            }
        }
        return curr;
    }
    Avl_own *search(Avl_own *curr, int val)
    {
        if (curr == nullptr)
            return nullptr;

        if (curr->data == val)
            return curr;

        if (val < curr->data)
            return search(curr->leftChild, val);

        return search(curr->rightChild, val);
    }
    void PreOrder_Traversal(Avl_own *curr)
    {
        if (curr != NULL)
        {
            cout << " --> " << curr->data;
            PreOrder_Traversal(curr->leftChild);
            PreOrder_Traversal(curr->rightChild);
        }
    }
    void InOrder_Traversal(Avl_own *curr)
    {
        if (curr != NULL)
        {
            InOrder_Traversal(curr->leftChild);
            cout << " --> " << curr->data;
            InOrder_Traversal(curr->rightChild);
        }
    }
    void PostOrder_Traversal(Avl_own *curr)
    {
        if (curr != NULL)
        {
            PostOrder_Traversal(curr->leftChild);
            PostOrder_Traversal(curr->rightChild);
            cout << " --> " << curr->data;
        }
    }
    void printTree(Avl_own *curr, int space = 0, int indent = 5)
    {
        if (curr == nullptr)
            return;

        space += indent;
        printTree(curr->rightChild, space);
        cout << endl;
        for (int i = indent; i < space; i++)
            cout << " ";

        cout << curr->data << "\n";
        printTree(curr->leftChild, space);
    }
};

int main()
{

    Avl_own tree;
    Avl_own *root = nullptr;
    int n, value, t = 0;
    bool flag = false;

    // Node node;

    cout << "Enter 1 to insert" << endl;
    cout << "Enter 2 to search" << endl;
    cout << "Enter 3 to delete" << endl;
    cout << "Enter 4 to display" << endl;
    cout << "Enter 5 to display in a tree stucture " << endl;
    cout << "Enter 6 to exit " << endl;

    while (!flag)
    {
        cout << "Enter Choice :";
        cin >> t;

        if (t == 1)
        {

            cout << "Enter Value:";
            cin >> value;
            cout << endl;

            root = tree.insert(root, value);
        }
        else if (t == 2)
        {
            int val;
            cout << "Enter what to search ";
            cin >> val;

            if (tree.search(root, val) == nullptr)
            {
                cout << "List is empty or no such value found" << endl;
            }
        }
        else if (t == 3)
        {
            int val;
            cout << "Enter what to delete ";
            cin >> val;

            if (tree.search(root, val))
            {
                cout << "The Element was found\n";
                root = tree.del(root, val);
            }
            else
            {
                cout << "The Element was not found\n";
            }
        }
        else if (t == 4)
        {
            // tree.display();
            int choice = 0;
            cout << "Enter which traversal to use ";
            cout << "1 for Pre Order , 2 for In Order, 3 for Post Order";
            cin >> choice;
            switch (choice)
            {
            case 1:
                tree.PreOrder_Traversal(root);
                cout << endl;
                break;
            case 2:
                tree.InOrder_Traversal(root);
                cout << endl;
                break;

            case 3:
                tree.PostOrder_Traversal(root);
                cout << endl;
                break;

            default:
                cout << "Invalid input!";
                break;
            }
        }
        else if (t == 5)
        {
            cout << "Here is the data in a tree Structure.\n";
            tree.printTree(root);
        }
        else if (t == 6)
        {
            /// to exit program
            // flag = true;
            cout << "Program Successfully Exited.\n";
            exit(flag);
        }
        else
        {
            cout << "enter a valid choice from available options." << endl;
        }
    }
}
