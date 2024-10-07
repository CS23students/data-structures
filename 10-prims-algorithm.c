#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

void primsAlgorithm(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int parent[MAX_VERTICES]; // Array to store the MST
    int key[MAX_VERTICES];    // Key values used to pick the minimum weight edge
    bool included[MAX_VERTICES]; // To track vertices included in MST

    // Initialize all keys as infinite and included as false
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        included[i] = false;
    }

    // Always include the first vertex in MST
    key[0] = 0;    // Make key 0 so that this vertex is picked first
    parent[0] = -1; // First node is always root of MST

    for (int count = 0; count < numVertices - 1; count++) {
        // Find the minimum key vertex not included in the MST
        int minKey = INT_MAX, minIndex;

        for (int v = 0; v < numVertices; v++) {
            if (!included[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        // Add the picked vertex to the MST
        included[minIndex] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex
        for (int v = 0; v < numVertices; v++) {
            if (graph[minIndex][v] && !included[v] && graph[minIndex][v] < key[v]) {
                parent[v] = minIndex;
                key[v] = graph[minIndex][v];
            }
        }
    }

    // Print the constructed MST
    printf("Edge \tWeight\n");
    for (int i = 1; i < numVertices; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

int main() {
    int numVertices;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    int graph[MAX_VERTICES][MAX_VERTICES];

    // Initialize the graph with 0
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph[i][j] = 0;
        }
    }

    // Input edges and weights
    int edges;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges in the format (u v weight):\n");
    for (int i = 0; i < edges; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        graph[u][v] = weight;
        graph[v][u] = weight; // Undirected graph
    }

    primsAlgorithm(graph, numVertices);

    return 0;
}


// Enter the number of vertices: 5
// Enter the number of edges: 7
// Enter the edges in the format (u v weight):
// 0 1 2
// 0 3 6
// 1 2 3
// 1 3 8
// 1 4 5
// 2 4 7
// 3 4 9
// Sample Output:
// Copy code
// Edge     Weight
// 0 - 1   2
// 1 - 2   3
// 1 - 4   5
// 0 - 3   6




