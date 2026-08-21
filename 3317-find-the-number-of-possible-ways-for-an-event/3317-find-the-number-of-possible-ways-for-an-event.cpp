class Solution {
public:
    int numberOfWays(int n, int x, int y) {
        const long long MOD = 1e9 + 7;

        vector<vector<long long>> dp(n + 1,
                                     vector<long long>(x + 1, 0));

        dp[0][0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(i, x); j++) {

                // Put current performer in an already used stage
                dp[i][j] = (dp[i][j] +
                            dp[i - 1][j] * j) % MOD;

                // Put current performer in a new stage
                dp[i][j] = (dp[i][j] +
                            dp[i - 1][j - 1] * (x - j + 1)) % MOD;
            }
        }

        long long ans = 0;
        long long power = 1;

        for (int j = 1; j <= min(n, x); j++) {
            power = (power * y) % MOD;

            ans = (ans + dp[n][j] * power) % MOD;
        }

        return ans;
    }
};