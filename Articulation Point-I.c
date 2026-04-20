using System;
using System.Collections.Generic;

class Solution
{
    private int time;

    void DFS(int u, bool[] visited, int[] disc, int[] low,
             int[] parent, bool[] ap, List<int>[] adj)
    {
        visited[u] = true;
        disc[u] = low[u] = ++time;
        int children = 0;

        foreach (int v in adj[u])
        {
            if (!visited[v])
            {
                children++;
                parent[v] = u;
                DFS(v, visited, disc, low, parent, ap, adj);

                // Update low value
                low[u] = Math.Min(low[u], low[v]);

                // Case 1: root node
                if (parent[u] == -1 && children > 1)
                    ap[u] = true;

                // Case 2: non-root
                if (parent[u] != -1 && low[v] >= disc[u])
                    ap[u] = true;
            }
            else if (v != parent[u])
            {
                // Back edge
                low[u] = Math.Min(low[u], disc[v]);
            }
        }
    }

    public List<int> articulationPoints(int V, List<int>[] adj)
    {
        bool[] visited = new bool[V];
        int[] disc = new int[V];
        int[] low = new int[V];
        int[] parent = new int[V];
        bool[] ap = new bool[V];

        for (int i = 0; i < V; i++)
            parent[i] = -1;

        time = 0;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                DFS(i, visited, disc, low, parent, ap, adj);
        }

        List<int> result = new List<int>();

        for (int i = 0; i < V; i++)
        {
            if (ap[i])
                result.Add(i);
        }

        if (result.Count == 0)
            result.Add(-1);

        result.Sort(); // GFG expects sorted output
        return result;
    }
}
