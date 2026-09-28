#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int path[MAX];

int n;
int pathLength;

int smallest = MAX + 1;
int largest = 0;

void findCycles(int start, int current)
{
    for (int next = 0; next < n; next++)
    {
        if (graph[current][next] == 1)
        {
            // If we return to starting vertex
            if (next == start && pathLength >= 3)
            {
                int cycleLength = pathLength;

                if (cycleLength < smallest)
                    smallest = cycleLength;

                if (cycleLength > largest)
                    largest = cycleLength;
            }

            // Continue DFS if vertex is not already in path
            else if (!visited[next])
            {
                visited[next] = 1;

                path[pathLength] = next;
                pathLength++;

                findCycles(start, next);

                pathLength--;
                visited[next] = 0;
            }
        }
    }
}

int main()
{
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

    // Start DFS from every vertex
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[j] = 0;
        }

        visited[i] = 1;
        pathLength = 1;
        path[0] = i;

        findCycles(i, i);
    }

    if (largest == 0)
    {
        printf("\nNo cycle exists in the graph.\n");
    }
    else
    {
        printf("\nSmallest cycle length = %d\n", smallest);
        printf("Largest cycle length = %d\n", largest);
    }

    return 0;
}