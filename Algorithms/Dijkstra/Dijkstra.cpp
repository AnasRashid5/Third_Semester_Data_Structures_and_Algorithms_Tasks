#include <iostream>
using namespace std;

const int V = 5;

int minDistance(int dist[], bool visited[])
{
    int min = 9999;
    int index = -1;

    for (int i = 0; i < V; i++)
    {
        if (!visited[i] && dist[i] < min)
        {
            min = dist[i];
            index = i;
        }
    }

    return index;
}

void dijkstra(int graph[V][V], int start)
{
    int dist[V];
    bool visited[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = 9999;
        visited[i] = false;
    }

    dist[start] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited);

        visited[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] &&
                graph[u][v] != 0 &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout << "Vertex\tDistance\n";

    for (int i = 0; i < V; i++)
        cout << i << "\t" << dist[i] << endl;
}

int main()
{
    int graph[V][V] =
        {
            {0, 10, 0, 30, 100},
            {10, 0, 50, 0, 0},
            {0, 50, 0, 20, 10},
            {30, 0, 20, 0, 60},
            {100, 0, 10, 60, 0}};

    dijkstra(graph, 0);
}