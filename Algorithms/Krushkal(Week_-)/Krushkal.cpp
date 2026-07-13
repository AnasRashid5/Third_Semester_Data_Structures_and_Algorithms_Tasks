#include <iostream>
#include <algorithm>
using namespace std;

struct Edge
{
    int src, dest, weight;
};

bool compare(Edge a, Edge b)
{
    return a.weight < b.weight;
}

int parent[10];

int find(int x)
{
    while (parent[x] != x)
        x = parent[x];

    return x;
}

void Union(int a, int b)
{
    parent[a] = b;
}

int main()
{
    Edge edges[] =
        {
            {0, 1, 2},
            {1, 2, 3},
            {0, 3, 6},
            {1, 3, 8},
            {1, 4, 5},
            {2, 4, 7},
            {3, 4, 9}};

    int E = 7;

    sort(edges, edges + E, compare);

    for (int i = 0; i < 5; i++)
        parent[i] = i;

    cout << "Edges in MST\n";

    for (int i = 0; i < E; i++)
    {
        int x = find(edges[i].src);
        int y = find(edges[i].dest);

        if (x != y)
        {
            cout << edges[i].src << " - "
                 << edges[i].dest
                 << " = "
                 << edges[i].weight << endl;

            Union(x, y);
        }
    }
}