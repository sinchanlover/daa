#include <stdio.h>
#include <limits.h>

#define MAX 100

void printPathUtil(int parent[], int j) {
    if (parent[j] == -1)
        return;

    printPathUtil(parent, parent[j]);
    printf("->%d", j);
}

void printAllPaths(int parent[], int dist[], int V, int src) {
    printf("\nPath:\n");
    for (int i = 1; i <= V; i++) {
        if (i == src) continue;

        printf("%d", src);
        printPathUtil(parent, i);

        if (dist[i] == INT_MAX)
            printf(" : No path\n");
        else
            printf(" : %d\n", dist[i]);
    }
}

void printTable(int table[][MAX], int V, int src) {
    printf("\nk\t");
    for (int i = 1; i <= V; i++)
        printf("%d->%d\t", src, i);
    printf("\n");

    for (int k = 1; k <= V - 1; k++) {
        printf("%d\t", k);
        for (int i = 1; i <= V; i++) {
            if (table[k][i] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", table[k][i]);
        }
        printf("\n");
    }
}

void BellmanFord(int graph[][3], int V, int E, int src) {
    int dist[MAX];
    int parent[MAX];
    int table[MAX][MAX];
    int prev[MAX];
    int curr[MAX];

    for (int i = 1; i <= V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int i = 1; i <= V; i++)
        prev[i] = dist[i];

    for (int k = 1; k <= V - 1; k++) {
        for (int i = 1; i <= V; i++)
            curr[i] = prev[i];

        for (int j = 0; j < E; j++) {
            int u = graph[j][0];
            int v = graph[j][1];
            int weight = graph[j][2];

            if (prev[u] != INT_MAX && prev[u] + weight < curr[v]) {
                curr[v] = prev[u] + weight;
                parent[v] = u;
            }
        }

        for (int i = 1; i <= V; i++)
            table[k][i] = curr[i];

        for (int i = 1; i <= V; i++)
            prev[i] = curr[i];
    }

    for (int i = 1; i <= V; i++)
        dist[i] = prev[i];

    for (int j = 0; j < E; j++) {
        int u = graph[j][0];
        int v = graph[j][1];
        int weight = graph[j][2];

        if (prev[u] != INT_MAX && prev[u] + weight < prev[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printTable(table, V, src);
    printAllPaths(parent, dist, V, src);
}

int main() {
    int V, E, src;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    int graph[E][3];

    printf("Enter edges (u v weight) [1-based vertices]:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph[i][0], &graph[i][1], &graph[i][2]);
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    BellmanFord(graph, V, E, src);

    return 0;
}
