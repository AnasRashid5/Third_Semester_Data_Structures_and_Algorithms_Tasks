#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

struct Edge;

struct Vertex
{
    int data;
    Vertex *next;
    Edge *edgeList;
    bool visited = false;
} *Graph = nullptr;

struct Edge
{
    Vertex *v;
    Edge *next;
};

class DynamicStack
{
public:
    Vertex *element;
    DynamicStack *prev = nullptr;

public:
    DynamicStack *top = nullptr;

public:
    void PushStack(Vertex *item)
    {
        DynamicStack *temp = new DynamicStack;
        temp->element = item;
        temp->prev = nullptr;

        if (top == nullptr)
        {
            top = temp;
            cout << "First element successfully Pushed to stack. \n";
        }
        else
        {
            temp->prev = top;
            top = temp;
            cout << "Element successfully Pushed to stack. \n";
        }
    }

public:
    Vertex *PopStack()
    {
        Vertex *element_popped = 0;
        if (top == nullptr)
        {
            cout << "There is no element in the Stack.\n";
            return 0;
        }
        else if (top->prev != nullptr)
        {
            DynamicStack *temp = top;
            top = top->prev;
            element_popped = temp->element;
            delete temp;

            cout << "Element popped = ";
            return element_popped;
            // cout<<"Element successfully Popped from Stack.\n";
        }
        else
        {
            element_popped = top->element;
            delete top;
            top = nullptr;
            cout << "Element popped = ";
            return element_popped;
            // cout<<"Element successfully Popped from Stack.\n";
        }
    }
};

DynamicStack s;

Vertex *addVertex(Vertex *current, int data)
{
    if (current == nullptr)
    {
        Vertex *temp = new Vertex;
        temp->data = data;
        temp->edgeList = nullptr;
        temp->next = nullptr;
        return temp;
    }

    current->next = addVertex(current->next, data);
    return current;
}

Vertex *existence(int vertex)
{
    Vertex *current = Graph;

    while (current != nullptr)
    {
        if (current->data == vertex)
        {

            return current;
        }

        current = current->next;
    }

    return nullptr;
}

void removeAllIncomingEdges(int vertex)
{
    Vertex *current = Graph;

    while (current != nullptr)
    {
        Edge *edgeCurrent = current->edgeList;
        Edge *prev = nullptr;

        while (edgeCurrent != nullptr)
        {
            if (edgeCurrent->v->data == vertex)
            {
                Edge *toDel = edgeCurrent;

                if (prev == nullptr)
                {
                    current->edgeList = edgeCurrent->next;
                    edgeCurrent = current->edgeList;
                }
                else
                {
                    prev->next = edgeCurrent->next;
                    edgeCurrent = edgeCurrent->next;
                }

                delete toDel;
            }
            else
            {
                prev = edgeCurrent;
                edgeCurrent = edgeCurrent->next;
            }
        }

        current = current->next;
    }
}

void removeVertex(int vertex)
{
    if (Graph == nullptr)
    {
        cout << "Graph empty\n";
        return;
    }

    Vertex *target = existence(vertex);

    if (target == nullptr)
    {
        cout << "Vertex not exists\n";
        return;
    }

    removeAllIncomingEdges(vertex);

    Vertex *current = Graph;
    Vertex *prev = nullptr;

    while (current != nullptr)
    {
        if (current == target)
        {
            Edge *edgeCurr = current->edgeList;

            while (edgeCurr != nullptr)
            {
                Edge *toDel = edgeCurr;
                edgeCurr = edgeCurr->next;
                delete toDel;
            }

            if (prev == nullptr)
                Graph = current->next;
            else
                prev->next = current->next;

            delete current;
            return;
        }

        prev = current;
        current = current->next;
    }
}

void addEdge(int vertex1, int vertex2)
{
    Vertex *v1 = existence(vertex1);
    Vertex *v2 = existence(vertex2);

    if (v1 == nullptr || v2 == nullptr)
    {
        cout << "Vertex not exists\n";
        return;
    }

    Edge *temp = new Edge;
    temp->v = v2;
    temp->next = nullptr;

    if (v1->edgeList == nullptr)
    {
        v1->edgeList = temp;
        return;
    }

    Edge *edgeCurrent = v1->edgeList;

    while (edgeCurrent->next != nullptr)
    {

        edgeCurrent = edgeCurrent->next;
    }

    edgeCurrent->next = temp;
}

void removeEdge(int vertex1, int vertex2)
{
    Vertex *v1 = existence(vertex1);
    Vertex *v2 = existence(vertex2);

    if (v1 == nullptr || v2 == nullptr)
    {
        cout << "Vertex not exists\n";
        return;
    }

    Edge *edgeCurrent = v1->edgeList;
    Edge *prev = nullptr;

    while (edgeCurrent != nullptr)
    {
        if (edgeCurrent->v == v2)
        {
            if (prev == nullptr)
            {
                v1->edgeList = edgeCurrent->next;
            }
            else
            {
                prev->next = edgeCurrent->next;
            }

            delete edgeCurrent;
            return;
        }

        prev = edgeCurrent;
        edgeCurrent = edgeCurrent->next;
    }

    cout << "Edge not found\n";
}

int findInDegree(int vertex)
{
    Vertex *toFind = existence(vertex);
    if (toFind == nullptr)
        return -1;

    int count = 0;
    Vertex *current = Graph;

    while (current != nullptr)
    {
        Edge *edgeCurrent = current->edgeList;

        while (edgeCurrent != nullptr)
        {
            if (edgeCurrent->v->data == toFind->data)
            {
                count++;
            }

            edgeCurrent = edgeCurrent->next;
        }

        current = current->next;
    }

    return count;
}

int findOutDegree(int vertex)
{
    Vertex *v = existence(vertex);

    if (v == nullptr)
        return -1;

    int count = 0;
    Edge *edgeCurrent = v->edgeList;

    while (edgeCurrent != nullptr)
    {
        count++;
        edgeCurrent = edgeCurrent->next;
    }

    return count;
}

int findDegree(int vertex)
{
    int inD = findInDegree(vertex);
    int outD = findOutDegree(vertex);

    if (inD == -1 || outD == -1)
        return -1;

    return inD + outD;
}

bool isAdjacent(int vertex1, int vertex2)
{
    Vertex *v1 = existence(vertex1);
    Vertex *v2 = existence(vertex2);

    if (v1 == nullptr || v2 == nullptr)
        return false;

    Edge *edgeCurrent = v1->edgeList;

    while (edgeCurrent != nullptr)
    {
        if (edgeCurrent->v == v2)
            return true;

        edgeCurrent = edgeCurrent->next;
    }

    return false;
}

string findNeighbours(int vertex)
{
    Vertex *v = existence(vertex);

    if (v == nullptr)
        return "";

    string s = "";
    Edge *edgeCurrent = v->edgeList;

    while (edgeCurrent != nullptr)
    {
        s += to_string(edgeCurrent->v->data) + " ";
        edgeCurrent = edgeCurrent->next;
    }

    return s;
}
string findPath(int vertex1, int vertex2)
{
    if (Graph == nullptr)
        return "Graph empty";

    Vertex *start = existence(vertex1);
    Vertex *target = existence(vertex2);

    if (start == nullptr || target == nullptr)
        return "Vertex not found";

    // reset visited
    Vertex *temp = Graph;
    while (temp != nullptr)
    {
        temp->visited = false;
        temp = temp->next;
    }

    string path = "";

    s.PushStack(start);

    while (s.top != nullptr)
    {
        Vertex *current = s.PopStack();

        if (current->visited)
            continue;

        current->visited = true;

        path += to_string(current->data) + " ";

        if (current == target)
            return path;

        Edge *edgeCurr = current->edgeList;

        while (edgeCurr != nullptr)
        {
            if (!edgeCurr->v->visited)
            {
                s.PushStack(edgeCurr->v);
            }
            edgeCurr = edgeCurr->next;
        }
    }

    return "No path found";
}

bool isCyclic(Vertex *current, int noOfVertices)
{
    findPath(current->data, current->data);

    return isCyclic(current->next, noOfVertices);
}

bool isConnected()
{
    // Step 1: reset visited
    Vertex *temp = Graph;
    int totalVertices = 0;

    while (temp != nullptr)
    {
        temp->visited = false;
        totalVertices++;
        temp = temp->next;
    }

    // Step 2: start DFS from first vertex
    Vertex *start = Graph;
    start->visited = true;
    s.PushStack(start);

    int visitedCount = 1;

    while (s.top != nullptr)
    {
        Vertex *current = s.top->element; // IMPORTANT: use stack top

        Edge *edgeCurr = current->edgeList;
        bool foundUnvisited = false;

        while (edgeCurr != nullptr)
        {
            if (edgeCurr->v->visited == false)
            {
                edgeCurr->v->visited = true;
                s.PushStack(edgeCurr->v);
                visitedCount++;
                foundUnvisited = true;
                break;
            }
            edgeCurr = edgeCurr->next;
        }

        // 🔥 THIS IS YOUR POP CONDITION
        if (!foundUnvisited)
        {
            s.PopStack();
        }
    }

    // Step 3: check if all visited
    return (visitedCount == totalVertices);
}

bool searchVertex(int vertex)
{
}

void outputAll()
{

    Vertex *curr;
    Edge *edgeCurr;
    curr = Graph;
    while (curr != NULL)
    {
        cout << curr->data;
        if (curr->edgeList != NULL)
        {
            edgeCurr = curr->edgeList;
            while (edgeCurr != NULL)
            {
                cout << " => " << edgeCurr->v->data;
                edgeCurr = edgeCurr->next;
            }
        }
        cout << "\n";
        curr = curr->next;
    }
    return;
}