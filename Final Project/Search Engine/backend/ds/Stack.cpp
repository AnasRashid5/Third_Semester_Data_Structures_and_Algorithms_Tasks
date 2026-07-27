// ISSUE FIX: Match the Stack header filename case for case-sensitive systems.
#include "Stack.h"

#include <iostream>

using namespace std;

stack_node *top = NULL;

void push(int val)
{
    stack_node *temp = new stack_node;
    temp->data = val;
    temp->next = NULL;

    if (top == NULL)
    {
        top = temp;
        return;
    }

    temp->next = top;
    top = temp;
}

int pop()
{
    if (top == NULL)
    {
        cout << "Stack Underflow" << endl;
        return -1;
    }

    stack_node *current = top;
    int data = current->data;
    top = top->next;
    delete current;
    return data;
}

bool isEmpty()
{
    return top == NULL;
}

vector<int> getStackValues()
{
    vector<int> values;

    for (stack_node *current = top; current != NULL; current = current->next)
    {
        values.push_back(current->data);
    }

    return values;
}

void clearStack()
{
    while (!isEmpty())
    {
        pop();
    }
}
