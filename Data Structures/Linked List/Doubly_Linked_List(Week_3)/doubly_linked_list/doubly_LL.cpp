#include <iostream>
#include <stdlib.h>
using namespace std;

struct D_Node
{
    int data;
    D_Node *next;
    D_Node *prev;
};

D_Node *list = NULL;

void insert(int val)
{
    D_Node *temp;
    temp = (D_Node *)malloc(sizeof(D_Node));
    temp->data = val;
    temp->next = NULL;

    if (list == NULL)
    {
        list = temp;
        list->prev = NULL;
    }
    else
    {
        D_Node *current = list;

        while (current->next != NULL)
        {
            current = current->next;
        }
        // current->next = temp;
        // current->prev=prev;
        temp->prev = current;
        current->next = temp;
    }
}

void search(int val)
{
    if (list == NULL)
    {
        cout << "No Values Present Inside List" << endl;
        return;
    }

    D_Node *current = list;
    while (current != NULL)
    {
        if (val == current->data)
        {
            cout << "Found " << current->data << endl;
            return;
        }
        current = current->next;
    }
    cout << "value not exists" << endl;
}
void del(int val)
{
    if (list == NULL)
    {
        cout << "No Values Present Inside List" << endl;
        return;
    }
    D_Node *current = list;

    if (list->data == val)
    {
        if (list->next == NULL)
        {
            free(list);
            list = NULL;
            return;
        }

        list = list->next;
        list->prev = NULL;
        free(current);
        return;
    }
    current = current->next;

    while (current != NULL)
    {
        if (current->data == val)
        {
            if (current->next == NULL)
            {
                current->prev->next = NULL;
                free(current);
                return;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            return;
        }
        current = current->next;
    }
    cout << "No such Element Found! " << endl;
}
void display()
{
    if (list == NULL)
    {
        cout << "No Values Present Inside List" << endl;
        return;
    }

    D_Node *current = list;
    while (current != NULL)
    {
        cout << current->data << endl;
        current = current->next;
    }
}