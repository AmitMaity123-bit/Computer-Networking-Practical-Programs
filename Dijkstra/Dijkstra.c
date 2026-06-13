#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 9999

// Function to find the vertex with minimum distance
int minDistance(int dist[], int visited[], int V) {
    int min = INF, min_index;

    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Print the shortest path from source to all vertices
void printSolution(int dist[], int V, int src) {
    printf("\nShortest paths from source vertex %d:\n", src);
    for (int i = 0; i < V; i++)
        printf("To vertex %d -> Distance = %d\n", i, dist[i]);
}

// Dijkstra's algorithm implementation
void dijkstra(int graph[MAX][MAX], int V, int src) {
    int dist[MAX];     // Output array: dist[i] holds shortest distance from src to i
    int visited[MAX];  // visited[i] is true if vertex i is processed

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;  // Distance from source to itself is 0

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist, V, src);
}

int main() {
    int V, graph[MAX][MAX], src;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);

    printf("Enter the adjacency matrix (0 for no direct edge):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
            if (i != j && graph[i][j] == 0)
                graph[i][j] = INF;  // Set to INF if no edge between i and j
        }
    }

    printf("Enter the source vertex (0 to %d): ", V - 1);
    scanf("%d", &src);

    dijkstra(graph, V, src);

    return 0;
}
