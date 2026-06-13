#include <stdio.h>

#define MAX_NODES 10
#define INF 9999

int main() {
    int cost[MAX_NODES][MAX_NODES];       // Cost matrix
    int dist[MAX_NODES][MAX_NODES];       // Distance vectors
    int via[MAX_NODES][MAX_NODES];        // Next hop information
    int n, i, j, k;
    int updated;

    // Input number of routers
    printf("Enter number of routers: ");
    scanf("%d", &n);

    // Input cost matrix
    printf("Enter cost matrix (use 9999 for no link):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            dist[i][j] = cost[i][j];
            if (i == j)
                via[i][j] = i;
            else if (cost[i][j] != INF)
                via[i][j] = j;
            else
                via[i][j] = -1; // No path yet
        }
    }

    // Distance Vector Algorithm (Bellman-Ford)
    do {
        updated = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                for (k = 0; k < n; k++) {
                    if (dist[i][j] > cost[i][k] + dist[k][j]) {
                        dist[i][j] = cost[i][k] + dist[k][j];
                        via[i][j] = k;
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);

    // Print routing tables
    for (i = 0; i < n; i++) {
        printf("\nRouting table for Router %d:\n", i);
        printf("Destination\tNext Hop\tDistance\n");
        for (j = 0; j < n; j++) {
            if (j == i) continue;
            printf("%d\t\t%d\t\t%d\n", j, via[i][j], dist[i][j]);
        }
    }

    return 0;
}
