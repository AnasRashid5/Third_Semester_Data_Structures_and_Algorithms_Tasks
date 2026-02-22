#include <iostream>
using namespace std;

struct Link_Node
{
    int data;
    Link_Node *next;
};

struct Node
{
    int data;
    Link_Node *next;
    bool flag = false;
};

Node HT[10];
int len = 10;

int hashFunc(int value)
{
    return value % len;
}

void insert(int val)
{
    int index = hashFunc(val);

    if (HT[index].flag == false)
    {
        HT[index].data = val;
        HT[index].next = NULL;
        HT[index].flag = true;
    }
    // if (HT[index].next == 0)
    // {
    //     HT[index].data = val;
    //     HT[index].next = nullptr;
    //     HT[index].flag = true;
    // }
    else
    {
        Link_Node *temp = new Link_Node;
        temp->data = val;
        temp->next = nullptr;

        Link_Node *current = HT[index].next;

        if (current == NULL)
        {
            HT[index].next = temp;
            return;
        }

        while (current->next != NULL)
        {
            current = current->next;
        }
        HT[index].next = temp;
    }
}

void search(int val)
{
    int index = hashFunc(val);

    if (val == HT[index].data && HT[index].flag == true)
    {
        cout << "Found: " << val << endl;
        return;
    }

    Link_Node *current = HT[index].next;

    while (current != NULL)
    {
        if (val == current->data)
        {
            cout << "Found: " << val << endl;
            return;
        }

        current = current->next;
    }
    cout << "Not Found." << endl;
}
void display()
{
    for (int i = 0; i < 10; i++)
    {
        if (HT[i].flag == false)
        {
            // cout << "Index " << i << " " << HT[i].next << " " << HT[i].data << ": Empty " << endl;
            cout << "Index " << i << ": " << "Empty" << endl;
        }

        else
        {
            // cout << "Index " << i << ": " << HT[i].data << endl;

            cout << "Index " << i << ": " << HT[i].data<<"->";
            // cout<<endl;
            Link_Node* list_current=HT[i].next;
            while (list_current!=nullptr)
            {
                cout<<list_current->data<<""<<endl;
                list_current=list_current->next;
            }
            

            // if (HT[i].)
            // {
            /* code */
            // }
            // zeroth ram cell
            // nullptr ->custom type-> type is nullptr_T->not a int
            // NULL-> defined as a const.value 0->int type
        }
    }
}