#include <stdio.h>

#define MAX 100

struct Edge
{
    int source;
    int destination;
    int weight;
};

int parent[MAX];

// Find parent of a vertex
int find(int vertex)
{
    if (parent[vertex] == vertex)
        return vertex;

    return find(parent[vertex]);
}

// Join two sets
void unionSets(int u, int v)
{
    int parentU = find(u);
    int parentV = find(v);

    parent[parentU] = parentV;
}

// Sort edges by weight
void sortEdges(struct Edge edges[], int edgeCount)
{
    struct Edge temp;

    for (int i = 0; i < edgeCount - 1; i++)
    {
        for (int j = 0; j < edgeCount - i - 1; j++)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n, edgeCount;

    struct Edge edges[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edgeCount);

    printf("Enter edges (source destination weight):\n");

    for (int i = 0; i < edgeCount; i++)
    {
        scanf("%d %d %d",
              &edges[i].source,
              &edges[i].destination,
              &edges[i].weight);
    }

    // Initially, every vertex is its own parent
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }

    // Sort edges
    sortEdges(edges, edgeCount);

    int selectedEdges = 0;
    int totalCost = 0;

    printf("\nEdges in Minimum Spanning Tree:\n");

    for (int i = 0; i < edgeCount && selectedEdges < n - 1; i++)
    {
        int u = edges[i].source;
        int v = edges[i].destination;

        // Check whether adding edge creates a cycle
        if (find(u) != find(v))
        {
            printf("%d - %d : %d\n",
                   u, v, edges[i].weight);

            totalCost += edges[i].weight;

            unionSets(u, v);

            selectedEdges++;
        }
    }

    if (selectedEdges != n - 1)
    {
        printf("\nGraph is not connected.\n");
    }
    else
    {
        printf("\nMinimum Cost = %d\n", totalCost);
    }

    return 0;
}