#include <iostream>
#include <stack>
using namespace std;

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;

    return 0;
}

int main()
{
    string infix = "A+B*C";
    string postfix = "";

    stack<char> st;

    for (int i = 0; i < infix.length(); i++)
    {
        char ch = infix[i];

        // Operand
        if (isalnum(ch))
        {
            postfix += ch;
        }

        // Left Parenthesis
        else if (ch == '(')
        {
            st.push(ch);
        }

        // Right Parenthesis
        else if (ch == ')')
        {
            while (st.top() != '(')
            {
                postfix += st.top();
                st.pop();
            }

            st.pop();
        }

        // Operator
        else
        {
            while (!st.empty() && precedence(st.top()) >= precedence(ch))
            {
                postfix += st.top();
                st.pop();
            }

            st.push(ch);
        }
    }

    while (!st.empty())
    {
        postfix += st.top();
        st.pop();
    }

    cout << "Postfix = " << postfix;
}