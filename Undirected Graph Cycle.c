bool dfs(int current, int parent, bool* visited, struct Node** adjList) {
    visited[current] = true;

    struct Node* temp = adjList[current];
    while (temp != NULL) {
        int neighbor = temp->vertex;

        if (!visited[neighbor]) {
            if (dfs(neighbor, current, visited, adjList))
                return true;
        } else if (neighbor != parent) {
            return true; // Found a cycle
        }

        temp = temp->next;
    }

    return false;
}

// Main cycle detection function
bool isCycle(int edges[][2], int E, int V) {
    // Create adjacency list
    struct Node** adjList = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++) {
        adjList[i] = NULL;
    }

    for (int i = 0; i < E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        addEdge(adjList, u, v);
    }

    // Visited array
    bool* visited = (bool*)calloc(V, sizeof(bool));

    // Check all components
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(i, -1, visited, adjList)) {
                // Free memory before returning
                for (int j = 0; j < V; j++) {
                    struct Node* temp = adjList[j];
                    while (temp != NULL) {
                        struct Node* next = temp->next;
                        free(temp);
                        temp = next;
                    }
                }
                free(adjList);
                free(visited);
                return true;
            }
        }
    }

    // Free memory
    for (int i = 0; i < V; i++) {
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            struct Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(adjList);
    free(visited);
    return false;
}
