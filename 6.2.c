#include <stdio.h>

#define INF 99999

void floydWarshall(int graph[][5], int V) {

    int dist[5][5];

    // Copy graph into dist
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Floyd-Warshall
    for (int k = 0; k < V; k++) {

        for (int i = 0; i < V; i++) {

            for (int j = 0; j < V; j++) {

                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] =
                        dist[i][k] + dist[k][j];
            }
        }
    }

    printf("Shortest distance matrix:\n");

    for (int i = 0; i < V; i++) {

        for (int j = 0; j < V; j++) {

            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", dist[i][j]);
        }

        printf("\n");
    }
}

int main() {

    int V = 5;

    int graph[5][5] = {
        {0,   3,   8, INF, -4},
        {INF, 0,   INF, 1,   7},
        {INF, 4,   0,   INF, INF},
        {2,   INF, -5,  0,  INF},
        {INF, INF, INF, 6,   0}
    };

    floydWarshall(graph, V);

    return 0;
}