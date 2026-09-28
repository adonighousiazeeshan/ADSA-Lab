#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int color[MAX];
int n;

// DFS
void DFS(int u)
{
    color[u] = 1;   // Gray

    for (int v = 0; v < n; v++)
    {
        if (graph[u][v] == 1)
        {
            if (color[v] == 0)
            {
                printf("%d -> %d : Tree Edge\n", u, v);

                DFS(v);
            }
            else if (color[v] == 1)
            {
                printf("%d -> %d : Back Edge\n", u, v);
            }
            else if (color[v] == 2)
            {
                printf("%d -> %d : Forward/Cross Edge\n", u, v);
            }
        }
    }

    color[u] = 2;   // Black
}

int main()
{
    int start;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    // Initially all vertices are unvisited
    for (int i = 0; i < n; i++)
    {
        color[i] = 0;
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    printf("\nEdge Classification:\n");

    DFS(start);

    return 0;
}