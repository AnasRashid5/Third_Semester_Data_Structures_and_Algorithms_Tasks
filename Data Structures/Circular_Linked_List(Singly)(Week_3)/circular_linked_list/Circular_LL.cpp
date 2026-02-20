#include <iostream>
#include <stdlib.h>
using namespace std;

struct C_Node
{
    int data;
    C_Node *next;
};

C_Node *list = NULL;

void insert(int val)
{

    C_Node *temp;

    temp = (C_Node *)malloc(sizeof(C_Node));
    temp->data = val;

    if (list == NULL)
    {
        list = temp;
        temp->next = list;
    }
    else
    {
        C_Node *current = list;

        while (current->next != list)
        {
            current = current->next;
        }
        current->next = temp;
        temp->next = list;
    }
}

void search(int val)
{
    if (list == NULL)
    {
        cout << "No Values Present Inside List" << endl;
        return;
    }

    C_Node *current = list;
    if (current != NULL)
    {
        if (val == current->data)
        {
            cout << "Found " << current->data << endl;
            return;
        }
        current = current->next;

        while (current != list)
        {
            if (val == current->data)
            {
                cout << "Found " << current->data << endl;
                return;
            }
            current = current->next;
        }
        cout << "Not Found " << val << endl;
    }
}
void del(int val)
{
    if (list == NULL)
    {
        cout << "No Values Present Inside List" << endl;
        return;
    }

    C_Node *current = list;
    C_Node *prev = list;

    if (list->next == list && val==list->data)
    {
        list = NULL;
        return;
    }
    if (val == list->data)
    {
        current = current->next;
        while (current->next != list)
        {
            current = current->next;
        }
        current->next = list->next;
        list = list->next;
        free(prev);
        current = list;
        prev = list;
        return;
    }
    while (current->next != list)
    {
        current = current->next;
        if (val == current->data)
        {
            prev->next = current->next;
            free(current);
            return;
        }

        prev = prev->next;
    }

    cout << "Value Not Present Inside List" << endl;
}

void display()
{
    if (list == NULL)
    {
        cout << "No Values Present Inside List" << endl;
        return;
    }

    C_Node *current = list;

    if (current != NULL)
    {
        cout << current->data << endl;
        current = current->next;
    }

    while (current != list)
    {
        cout << current->data << endl;
        current = current->next;
    }
}