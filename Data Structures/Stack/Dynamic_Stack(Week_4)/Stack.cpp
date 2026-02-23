#include <bits/stdc++.h>
using namespace std;

struct stack_node
{

    int data;
    stack_node *next;
};

stack_node *top = NULL;

void push(int val)
{

    stack_node *temp;
    temp = (stack_node *)new (stack_node);
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
    delete (current);
    return data;
}