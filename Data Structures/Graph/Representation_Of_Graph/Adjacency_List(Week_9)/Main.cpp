#include <iostream>
#include "AdjacencyList.cpp"

using namespace std;

int main()
{
    int choice;

    while (true)
    {
        cout << "\n===== GRAPH MENU =====\n";
        cout << "1. Add Vertex\n";
        cout << "2. Remove Vertex\n";
        cout << "3. Add Edge\n";
        cout << "4. Remove Edge\n";
        cout << "5. Find Degree\n";
        cout << "6. Find In-Degree\n";
        cout << "7. Find Out-Degree\n";
        cout << "8. Find Path\n";
        cout << "9. Check Cyclic\n";
        cout << "10. Check Connected\n";
        cout << "11. Check Adjacent\n";
        cout << "12. Find Neighbours\n";
        cout << "13. Search Vertex\n";
        cout << "14. Display Graph\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        int v1, v2;

        switch (choice)
        {
        case 1:
        {
            int data;
            cout << "Enter vertex value: ";
            cin >> data;
            Graph = addVertex(Graph, data);
            break;
        }

        case 2:
            int data;
            cout << "Enter vertex value: ";
            cin >> data;
            removeVertex(data);
            break;

        case 3:
            cout << "Enter value of start vertex  and end vertex 2: ";
            cin >> v1 >> v2;
            addEdge(v1, v2);
            break;

        case 4:
            cout << "Enter value of start vertex  and end vertex 2: ";
            cin >> v1 >> v2;
            removeEdge(v1, v2);
            break;

        case 5:
            cout << "Enter vertex: ";
            cin >> v1;
            cout << findDegree(v1) << endl;
            break;

        case 6:
            cout << "Enter vertex: ";
            cin >> v1;
            cout << findInDegree(v1) << endl;
            break;

        case 7:
            cout << "Enter vertex: ";
            cin >> v1;
            cout << findOutDegree(v1) << endl;
            break;

        case 8:
            cout << "Enter vertex 1 and vertex 2: ";
            cin >> v1 >> v2;
            cout << findPath(v1, v2) << endl;
            break;

        case 9:

            int no = 0;
            cout << "Enter no of vertices : ";
            cin >> no;
            Vertex *temp=Graph;
            cout << (isCyclic(temp,no) ? "Cyclic\n" : "Not Cyclic\n");
            break;

        case 10:
            cout << (isConnected() ? "Connected\n" : "Not Connected\n");
            break;

        case 11:
            cout << "Enter vertex 1 and vertex 2: ";
            cin >> v1 >> v2;
            cout << (isAdjacent(v1, v2) ? "Adjacent\n" : "Not Adjacent\n");
            break;

        case 12:
            cout << "Enter vertex: ";
            cin >> v1;
            cout << findNeighbours(v1) << endl;
            break;

        case 13:
            cout << "Enter vertex: ";
            cin >> v1;
            cout << (searchVertex(v1) ? "Found\n" : "Not Found\n");
            break;

        case 14:
            outputAll();
            break;

        case 0:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid choice\n";
        }
    }
}