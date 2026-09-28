#include <stdio.h>

#define INF 99999

struct Edge {
    int u, v, w;
};

void bellmanFord(struct Edge edges[], int V, int E, int source) {
    int dist[V];

    // Initialize distances
    for (int i = 0; i < V; i++)
        dist[i] = INF;

    dist[source] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {

            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // Check for negative weight cycle
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Negative weight cycle exists.\n");
            return;
        }
    }

    printf("Shortest distances from source %d:\n", source);

    for (int i = 0; i < V; i++)
        printf("%d -> %d = %d\n", source, i, dist[i]);
}

int main() {

    int V = 5;
    int E = 8;

    struct Edge edges[] = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    int source = 0;

    bellmanFord(edges, V, E, source);

    return 0;
}