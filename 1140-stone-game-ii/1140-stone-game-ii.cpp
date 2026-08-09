class Solution {
public:
    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int dfs(int i, int M) {
        if (i >= n)
            return 0;

        if (2 * M >= n - i)
            return suffix[i];

        if (dp[i][M] != -1)
            return dp[i][M];

        int ans = 0;

        for (int X = 1; X <= 2 * M; X++) {
            ans = max(ans,
                      suffix[i] - dfs(i + X, max(M, X)));
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        suffix.resize(n);
        suffix[n - 1] = piles[n - 1];

        for (int i = n - 2; i >= 0; i--)
            suffix[i] = suffix[i + 1] + piles[i];

        dp.assign(n, vector<int>(n + 1, -1));

        return dfs(0, 1);
    }
};