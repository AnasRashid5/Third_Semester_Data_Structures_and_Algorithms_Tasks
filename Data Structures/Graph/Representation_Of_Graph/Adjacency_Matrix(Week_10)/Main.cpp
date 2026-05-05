#include <iostream>
#include "AdjacencyMatrix.cpp"
using namespace std;

int choice = 0, noOfVertices = 0;
int adjacencyMatrix[100][100];
string vertices[100];
int edges = 0;

int main()
{
    while (true)
    {
        cout << "\n===== Graph MENU =====" << endl;
        cout << "1. Insert vertices" << endl;
        cout << "2. Degree of vertex" << endl;
        cout << "3. Sum of degree" << endl;
        cout << "4. Find Neighbour" << endl;
        cout << "5. Check Adjacency" << endl;
        cout << "6. Cyclic or Non Cyclic" << endl;
        cout << "7. To display" << endl;
        cout << "8. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Enter number of vertices: ";
            cin >> noOfVertices;

            if (noOfVertices <= 0 || noOfVertices >= 100)
            {
                cout << "Enter valid no of vertices";
                break;
            }

            cout << "\nEnter vertex names (A B C or V1 V2 etc): ";
            for (int i = 0; i < noOfVertices; i++)
            {
                cin >> vertices[i];
            }

            cout << "\nNow enter no of edges: ";
            cin >> edges;

            addEdge();
            break;
        }

        case 2:
        {
            string name;
            cout << "Enter vertex name to find degree: ";
            cin >> name;
            cout << "Degree of vertex " << name << " is " << DegreeOfVertex(name);
            break;
        }

        case 3:
        {
            cout << "Sum of Degree Is: " << SumOfDegree() << endl;
            break;
        }

        case 4:
        {
            string vertex;
            cout << "Enter vertex to find neighbours: " << endl;
            cin >> vertex;
            cout << "Neigbours are:" << findNeighbour(vertex);
            break;
        }

        case 5:
        {
            string vertex1, vertex2;
            cout << "Enter vertex 1 to check adjacency: " << endl;
            cin >> vertex1;
            cout << "Enter vertex 2 to check adjacency: " << endl;
            cin >> vertex2;

            if (isAdjacent(vertex1, vertex2))
            {
                cout << vertex1 << " is adjacent to " << vertex2;
            }
            else
            {
                cout << "Not Adjacent";
            }

            break;
        }

            // case 6:
            // {
            //     if (cyclicCheck())
            //         cout << "Graph is Cyclic" << endl;
            //     else
            //         cout << "Graph is non Cyclic" << endl;

            //     break;
            // }

        case 7:
        {
            display();
            break;
        }

        case 8:
        {
            cout << "Exiting program..." << endl;
            return 0;
        }

        default:
            cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
        }
    }
}