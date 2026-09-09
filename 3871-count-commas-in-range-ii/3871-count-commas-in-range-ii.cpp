class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;

        for (long long p = 1000; p <= n; ) {
            ans += n - p + 1;

            // Avoid overflow
            if (p > n / 1000)
                break;

            p *= 1000;
        }

        return ans;
    }
};