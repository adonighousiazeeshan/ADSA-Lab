#include <stdio.h>

#define MAX 10
#define INF 99999

void dijkstra(int graph[MAX][MAX], int n, int source)
{
    int distance[MAX];
    int visited[MAX];

    // Initialize
    for (int i = 0; i < n; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
    }

    distance[source] = 0;

    // Find shortest paths
    for (int count = 0; count < n - 1; count++)
    {
        int min = INF;
        int u = -1;

        // Find unvisited vertex with minimum distance
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && distance[i] < min)
            {
                min = distance[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        // Update neighbouring vertices
        for (int v = 0; v < n; v++)
        {
            if (!visited[v] &&
                graph[u][v] != 0 &&
                distance[u] + graph[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    // Print result
    printf("\nShortest distances from vertex %d:\n", source);

    for (int i = 0; i < n; i++)
    {
        if (distance[i] == INF)
            printf("To %d = Not Reachable\n", i);
        else
            printf("To %d = %d\n", i, distance[i]);
    }
}

int main()
{
    int n;
    int graph[MAX][MAX];
    int source;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    printf("(Enter 0 if there is no edge)\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter source vertex: ");
    scanf("%d", &source);

    dijkstra(graph, n, source);

    return 0;
}