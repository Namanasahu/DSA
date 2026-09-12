class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> ids;
    };

    State better(State a, State b) {
        if (a.score != b.score)
            return a.score > b.score ? a : b;

        sort(a.ids.begin(), a.ids.end());
        sort(b.ids.begin(), b.ids.end());

        return a.ids < b.ids ? a : b;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {end, start, weight, original index}
        vector<array<long long, 4>> a;
        for (int i = 0; i < n; ++i) {
            a.push_back({
                intervals[i][1],
                intervals[i][0],
                intervals[i][2],
                i
            });
        }

        sort(a.begin(), a.end());

        vector<long long> ends(n);
        for (int i = 0; i < n; ++i)
            ends[i] = a[i][0];

        // p[i] = number of intervals among [0..i-1]
        // whose end is strictly smaller than start of interval i.
        vector<int> p(n);

        for (int i = 0; i < n; ++i) {
            long long start = a[i][1];

            // First end >= start.
            // Therefore all intervals before this position have end < start.
            p[i] = lower_bound(ends.begin(), ends.begin() + i, start)
                 - ends.begin();
        }

        vector<vector<State>> dp(n + 1, vector<State>(5));

        for (int i = 1; i <= n; ++i) {
            for (int k = 1; k <= 4; ++k) {
                // Don't choose interval i-1.
                State skip = dp[i - 1][k];

                // Choose interval i-1.
                State take = dp[p[i - 1]][k - 1];
                take.score += a[i - 1][2];
                take.ids.push_back((int)a[i - 1][3]);
                sort(take.ids.begin(), take.ids.end());

                dp[i][k] = better(skip, take);
            }
        }

        return dp[n][4].ids;
    }
};