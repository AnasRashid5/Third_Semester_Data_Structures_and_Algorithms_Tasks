#include <iostream>
using namespace std;

// STATIC STACK->LIMTED SIZE
class Stack
{
    // STACK HAS ONE ACCESS POINT CALLED TOP, FROM WHERE VALUES ARE BOTH PUSHED AND POPPED.
    // WE CAN TAKE THE EXAMPLE OF A REAL-LIFE STACK LIKE A PILE OF PLATES OR BOOKS. YOU PLACE A NEW PLATE ON TOP AND REMOVE THE TOP PLATE FIRST.
    // BASICALLY, STACK OPERATES ON LIFO(LAST IN FIRST OUT) PRINCIPLE.

private:
    int stack[10];
    // int top = 0;
    int top = -1;

public:
    void push(int value)
    {
        if (top == 9)
        {
            cout << "Stack Overflow" << endl;
            return;
        }
        // cout << "inside push" << endl;
        stack[top] = value;
        top++;

        // if (top < 10)
        // {
        //     /* code */
        //     push(6);
        // }
    }

    int pop()
    {
        if (top == -1)
        {
            cout << "Stack Underflow!" << endl;
            return -11;
        }
        // cout << "inside pop" << endl;
        top--;
        return stack[top];

        // if (top > 0)
        // {
        //     /* code */
        //     pop();
        // }
    }
};

int main()
{
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    cout << s.pop();
    cout << s.pop();
    cout << s.pop();
    cout << s.pop();
    cout << s.pop();
}