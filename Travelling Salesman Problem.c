class Solution {
    public int tsp(int[,] cost) {
        int n = cost.GetLength(0);
        if (n <= 1) return n == 1 ? cost[0, 0] : 0;

        // maximum cost to visit all cities
        int INF = int.MaxValue;
        int FULL = 1 << n, fullMask = FULL - 1;

        // dp[mask][i] represents the minimum cost to visit all cities
        // corresponding to the set bits in 'mask', ending at city 'i'
        int[,] dp = new int[FULL, n];
        for (int i = 0; i < FULL; i++)
            for (int j = 0; j < n; j++) dp[i, j] = INF;
        dp[1, 0] = 0;

        // iterate over all subsets of cities
        for (int mask = 1; mask < FULL; mask++) {
            for (int i = 0; i < n; i++) {

                // skip if city i is not included in mask
                if ((mask & (1 << i)) == 0) continue;
                if (dp[mask, i] == INF) continue;

                // try to go to every unvisited city j
                for (int j = 0; j < n; j++) {

                    // skip if city j is already visited
                    if ((mask & (1 << j)) != 0) continue;

                    // cost to visit new city j from city i
                    // such that previously visited cities
                    // remain visited
                    int nxt = mask | (1 << j);
                    dp[nxt, j] = Math.Min(dp[nxt, j], dp[mask, i] + cost[i, j]);
                }
            }
        }

        int ans = INF;
        for (int i = 0; i < n; i++) {

            // if last city on path is i and
            // cost of path is not infinity
            if (dp[fullMask, i] != INF)

                // update net cost such that city 0 is visited in last
                ans = Math.Min(ans, dp[fullMask, i] + cost[i, 0]);
        }

        return ans;
    }
}
