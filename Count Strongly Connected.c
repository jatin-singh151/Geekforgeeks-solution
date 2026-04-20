using System;
using System.Collections.Generic;

class Solution
{
    void dfs1(int node, List<int>[] adj, bool[] vis, Stack<int> st)
    {
        vis[node] = true;
        foreach (int next in adj[node])
        {
            if (!vis[next])
                dfs1(next, adj, vis, st);
        }
        st.Push(node);
    }

    void dfs2(int node, List<int>[] rev, bool[] vis)
    {
        vis[node] = true;
        foreach (int next in rev[node])
        {
            if (!vis[next])
                dfs2(next, rev, vis);
        }
    }

    public int kosaraju(int V, List<Tuple<int, int>> edges)
    {
        // 🔥 STEP 0: Convert edges → adjacency list
        List<int>[] adj = new List<int>[V];
        for (int i = 0; i < V; i++)
            adj[i] = new List<int>();

        foreach (var edge in edges)
        {
            int u = edge.Item1;
            int v = edge.Item2;
            adj[u].Add(v);
        }

        // Step 1: DFS and stack
        Stack<int> st = new Stack<int>();
        bool[] vis = new bool[V];

        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
                dfs1(i, adj, vis, st);
        }

        // Step 2: Reverse graph
        List<int>[] rev = new List<int>[V];
        for (int i = 0; i < V; i++)
            rev[i] = new List<int>();

        for (int i = 0; i < V; i++)
        {
            foreach (int j in adj[i])
            {
                rev[j].Add(i);
            }
        }

        // Step 3: Count SCC
        for (int i = 0; i < V; i++)
            vis[i] = false;

        int count = 0;

        while (st.Count > 0)
        {
            int node = st.Pop();

            if (!vis[node])
            {
                dfs2(node, rev, vis);
                count++;
            }
        }

        return count;
    }
}
