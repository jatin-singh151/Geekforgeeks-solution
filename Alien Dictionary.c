using System;
using System.Collections.Generic;

public class Solution {
    public string findOrder(string[] words, int k) {
        int n = words.Length;
        
        List<int>[] adj = new List<int>[k];
        int[] inDegree = new int[k];
        
        for (int i = 0; i < k; i++)
            adj[i] = new List<int>();
        
        for (int i = 0; i < n - 1; i++) {
            string w1 = words[i];
            string w2 = words[i + 1];
            int minLen = Math.Min(w1.Length, w2.Length);
            
            if (w1.Length > w2.Length && w1.Substring(0, minLen) == w2.Substring(0, minLen))
                return "";
            
            for (int j = 0; j < minLen; j++) {
                if (w1[j] != w2[j]) {
                    int u = w1[j] - 'a';
                    int v = w2[j] - 'a';
                    adj[u].Add(v);
                    inDegree[v]++;
                    break;
                }
            }
        }
        
        Queue<int> queue = new Queue<int>();
        for (int i = 0; i < k; i++)
            if (inDegree[i] == 0)
                queue.Enqueue(i);
        
        string result = "";
        while (queue.Count > 0) {
            int node = queue.Dequeue();
            result += (char)('a' + node);
            
            foreach (int neighbor in adj[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0)
                    queue.Enqueue(neighbor);
            }
        }
        
        if (result.Length != k)
            return "";
        
        return result;
    }
}
