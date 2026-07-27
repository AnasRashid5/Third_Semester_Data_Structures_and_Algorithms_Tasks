#ifndef STACK_H
#define STACK_H

#include <vector>

struct stack_node
{
    int data;
    stack_node *next;
};

void push(int val);
int pop();
bool isEmpty();
std::vector<int> getStackValues();
void clearStack();

#endif
