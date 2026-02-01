#include <iostream>
#include <stdlib.h>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

Node *list = NULL;

void insert(int val)
{
    Node *temp;
    temp = (Node *)malloc(sizeof(Node));
    temp->data = val;
    temp->next = NULL;
    
    if (list == NULL)
    {
        list = temp;
    }
    else
    {
        Node *current = list; // current is a traversal pointer
        
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = temp;
    }
}

// void search(int val)
// {
//     Node *current = list;
//     bool flag = false;
//     while (current != NULL)
//     {
//         if (val == current->data)
//         {
//             flag = true;
//             break;
//         }
//         current = current->next;
//     }

//     if (!flag)
//     {
//         cout << "Not Found" << endl;
//     }
//     else
//     {
//         cout << "Found: " << current->data << endl;
//     }
// }
void search(int val)
{
    if (list == NULL)
    {
        cout << "No Values Present Inside List";
        return;
    }

    Node *current = list;
    while (current != NULL)
    {
        if (val == current->data)
        {
            cout << "Found: " << current->data << endl;
            return;
        }
        current = current->next;
    }

    cout << "Not Found: " << val << endl;
}

void del(int val)
{
    if (list == NULL)
    {
        cout << "No Values Present Inside List"<<endl;
        return;
    }

    Node *current = list;
    Node *prev = list;

    if (val==list->data){
        list=list->next;
        free(current);
        return;
    }
    current=list->next;

    while (current!= NULL)
    {
        if (val == current->data)
        {
            prev->next=current->next;
            free(current);
            return;
        }
        prev=current;
        current = current->next;
    }
    cout<<"value not exists"<<endl;
}
void display()
{
    if (list == NULL)
    {
        cout << "No Values Present Inside List"<<endl;
        return;
    }

    Node *current = list;
    while (current != NULL)
    {
        cout << current->data << endl;
        current = current->next;
    }
}
void exit(bool flag)
{
    flag = true;
}