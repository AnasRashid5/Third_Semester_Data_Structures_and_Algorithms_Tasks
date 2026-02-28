#include <iostream>
using namespace std;

class Binary_Tree
{
private:
    int data;
    Binary_Tree *right;
    Binary_Tree *left;

public:
    Binary_Tree *insert(Binary_Tree *current, int val)
    {
        Binary_Tree *temp = new Binary_Tree;
        if (current == nullptr)
        {
            Binary_Tree *temp = new Binary_Tree;
            temp->data = val;
            temp->right = nullptr;
            temp->left = nullptr;
            return temp;
        }
        else
        {
            if (val > current->data)
            {
                current->right = insert(current->right, val);
            }
            else
            {
                current->left = insert(current->left, val);
            }
            return current;
        }
    }

    Binary_Tree *findMinRight(Binary_Tree *current)
    {
        Binary_Tree *temp = current->right;
        while (temp != nullptr)
        {
            temp = temp->left;
        }

        return temp;
    }

    Binary_Tree *del(Binary_Tree *current, int val)
    {
        if (!search(current, val))
        {
            cout << "No such value present in tree" << endl;
            return nullptr;
        }

        if (current == nullptr)
        {
            return nullptr;
        }

        if (current->data == val)
        {
            // FOR ZERO CHILDS::
            if (current->left == nullptr && current->right == nullptr)
            {
                delete (current);
                current = nullptr;
                return current;
            }

            // FOR ONE CHILD::
            if (current->left == nullptr)
            {
                Binary_Tree *temp = current->right;
                delete (current);
                return temp;
            }

            // FOR ONE CHILD::
            if (current->right == nullptr)
            {
                Binary_Tree *temp = current->left;
                delete (current);
                return temp;
            }
            // FOURTH CASE: IF 2 CHILDS.
            Binary_Tree *minNode = findMinRight(current);
            current->data = minNode->data;
            current->right = del(current->right, minNode->data);
        }
        else
        {
            if (val > current->data)
            {
                current->right = del(current->right, val);
            }
            else
            {
                current->left = del(current->left, val);
            }
            return current;
        }
    }

    bool search(Binary_Tree *current, int val)
    {
        if (current == nullptr)
        {
            return false;
        }

        if (current->data == val)
        {
            return true;
        }
        else
        {
            if (val > current->data)
            {
                return search(current->right, val);
            }
            else
            {
                return search(current->left, val);
            }
        }
    }
    // IN TREE WE HAVE 3 TYPES OF TRAVERSALS::
    // INORDER(LNR) , POSTORDER(LRN) ,PREORDER(NLR)
    // IN INORDER TRAVERSAL WE ALWAYS GET SORTED OUTPUT OF OUR TREE.
    void preorder(Binary_Tree *current)
    {
        // IN PREORDER WE FOLLOW NLR. FIRST NODE WILL BE PRINTED THEN LEFT SIDE AND THEN RIGHT SIDE.
        if (current != nullptr)
        {
            cout << current->data << " ";
            preorder(current->left);
            preorder(current->right);
        }
    }
    void postorder(Binary_Tree *current)
    {
        // IN POSTORDER WE FOLLOW LRN. FIRST LEFT SIDE THEN RIGHT SIDE AND THEN THE NODE GETS PRINTED.
        if (current != nullptr)
        {
            postorder(current->left);
            postorder(current->right);
            cout << current->data << " ";
        }
    }
    void inorder(Binary_Tree *current)
    {
        // IN INORDER WE FOLLOW LNR. FIRST LEFT SIDE THEN NODE AND THEN RIGHT SIDE.
        if (current != nullptr)
        {
            inorder(current->left);
            cout << current->data << " ";
            inorder(current->right);
        }
    }
};