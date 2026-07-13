#include <iostream>
#include <stack>
#include <algorithm>
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

    reverse(infix.begin(), infix.end());

    // Swap brackets
    for (int i = 0; i < infix.length(); i++)
    {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
    }

    stack<char> st;
    string postfix = "";

    for (char ch : infix)
    {
        if (isalnum(ch))
        {
            postfix += ch;
        }
        else if (ch == '(')
        {
            st.push(ch);
        }
        else if (ch == ')')
        {
            while (st.top() != '(')
            {
                postfix += st.top();
                st.pop();
            }

            st.pop();
        }
        else
        {
            while (!st.empty() &&
                   precedence(st.top()) >= precedence(ch))
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

    reverse(postfix.begin(), postfix.end());

    cout << "Prefix = " << postfix;
}