#include <stdio.h>

#define MAX 10
#define INF 99999

void prim(int graph[MAX][MAX], int n)
{
    int selected[MAX] = {0};
    int edges = 0;
    int totalCost = 0;

    // Start from vertex 0
    selected[0] = 1;

    printf("\nEdges in Minimum Spanning Tree:\n");

    while (edges < n - 1)
    {
        int min = INF;
        int x = -1;
        int y = -1;

        // Find minimum edge
        for (int i = 0; i < n; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < n; j++)
                {
                    if (!selected[j] &&
                        graph[i][j] != 0 &&
                        graph[i][j] < min)
                    {
                        min = graph[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }

        if (x == -1 || y == -1)
        {
            printf("Graph is not connected.\n");
            return;
        }

        printf("%d - %d : %d\n", x, y, min);

        totalCost += min;
        selected[y] = 1;
        edges++;
    }

    printf("\nMinimum Cost = %d\n", totalCost);
}

int main()
{
    int graph[MAX][MAX];
    int n;

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

    prim(graph, n);

    return 0;
}