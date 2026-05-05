#include <iostream>
using namespace std;

extern int adjacencyMatrix[100][100];
extern string vertices[100];
extern int noOfVertices;
extern int edges;

void addEdge() // n represents no of vertices.., vertices array contains names of vertices, edges=no of edges
{
    // Filled array with 0 in order to avoid garbage values..
    int iterator = 0;
    for (int i = 0; i < noOfVertices; i++)
    {
        for (int j = 0; j < noOfVertices; j++)
        {
            adjacencyMatrix[i][j] = 0;
        }
    }

    string vertice1, vertice2;

    while (iterator != edges)
    {
        int idx1 = -1, idx2 = -1;

        cout << "Enter " << iterator + 1 << " edge bw vertices: " << endl;
        cout << "Enter starting vertice of edge: ";
        cin >> vertice1;
        cout << "Enter ending vertice of edge: ";
        cin >> vertice2;
        cout << endl;
        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         if (vertice1 == vertices[i])
        //         {
        //             if (vertice2 == vertices[j])
        //             {
        //                 arr[i][j] = 1;
        //                 arr[j][i] = 1;
        //             }
        //         }
        //     }
        // }

        // Refactor for better optimization ::: so now i will save index instead of continuously looping
        for (int i = 0; i < noOfVertices; i++)
        {
            if (vertice1 == vertices[i])
            {

                idx1 = i;
            }
            if (vertice2 == vertices[i])
            {

                idx2 = i;
            }

            if (idx1 != -1 && idx2 != -1)
            {
                break;
            }
        }
        if (idx1 == -1 || idx2 == -1)
        {
            cout << "Invalid Edge Input!";
            continue;
        }

        adjacencyMatrix[idx1][idx2] = 1;
        adjacencyMatrix[idx2][idx1] = 1;
        iterator++;
    }
}

int DegreeOfVertex(string vertex)
{
    int idx = -1, count = 0;
    for (int i = 0; i < noOfVertices; i++)
    {
        if (vertex == vertices[i])
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
    {
        cout << "No such vertex found!";
        return -1;
    }

    for (int j = 0; j < noOfVertices; j++)
    {
        if (adjacencyMatrix[idx][j] == 1)
        {
            count = count + 1;
        }
    }

    return count;
}

void display()
{
    cout << "  ";
    for (int i = 0; i < noOfVertices; i++)
    {
        cout << vertices[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < noOfVertices; i++)
    {
        cout << vertices[i] << " ";
        for (int j = 0; j < noOfVertices; j++)
        {

            // Logic for printing last column:: we need a new line to print other elems after last cloumn ends..

            if (j == noOfVertices - 1)
            {
                /* code */
                cout << adjacencyMatrix[i][j] << " ";
                cout << endl;
            }

            else
            {
                cout << adjacencyMatrix[i][j] << " ";
            }
        }
    }
}

int SumOfDegree()
{
    int total = 0;

    for (int i = 0; i < noOfVertices; i++)
    {
        for (int j = 0; j < noOfVertices; j++)
        {
            if (adjacencyMatrix[i][j] == 1)
            {
                total++;
            }
        }
    }

    return total;
}

// bool findPath(char start, char end)
// {
// }
// bool cyclicCheck()
// {
// }
// bool connectedCheck()
// {
// }

bool isAdjacent(string vertex1, string vertex2)
{
    int idx1 = -1, idx2 = -1;
    for (int i = 0; i < noOfVertices; i++)
    {
        if (vertices[i] == vertex1)
        {
            idx1 = i;
        }
        if (vertices[i] == vertex2)
        {
            idx2 = i;
        }
    }
    if (idx1 == -1 || idx2 == -1)
    {
        cout << "Invalid vertice !";
        return false;
    }

    if (adjacencyMatrix[idx1][idx2] == 1)
    {
        return true;
    }
    return false;
}

string findNeighbour(string vertex) //--> this func returns all neighbours of a vertex or all vertices that are connected to that particular vertex..
{

    int idx = -1;
    string s = "";
    for (int i = 0; i < noOfVertices; i++)
    {
        if (vertex == vertices[i])
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
    {
        cout << "Invalid Index: ";
    }
    for (int j = 0; j < noOfVertices; j++)
    {
        if (adjacencyMatrix[idx][j] == 1)
        {
            s = s + vertices[j] + " ";
        }
    }
    return s;
}

// for directed ::
// indegree ,outdegree,