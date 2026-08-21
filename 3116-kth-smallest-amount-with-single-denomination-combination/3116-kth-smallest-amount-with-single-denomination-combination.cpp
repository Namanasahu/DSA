class Solution {
public:
    using ll = long long;

    ll gcd(ll a, ll b) {
        while (b) {
            ll t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    ll lcm(ll a, ll b) {
        return a / gcd(a, b) * b;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();

        auto check = [&](ll x) {
            ll cnt = 0;

            for (int mask = 1; mask < (1 << n); mask++) {
                ll cur = 1;
                bool ok = true;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        cur = lcm(cur, (ll)coins[i]);
                        if (cur > x) {
                            ok = false;
                            break;
                        }
                    }
                }

                if (!ok) continue;

                if (__builtin_popcount(mask) & 1)
                    cnt += x / cur;
                else
                    cnt -= x / cur;
            }

            return cnt >= k;
        };

        ll lo = 1;
        ll hi = 1e11;

        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;
            if (check(mid))
                hi = mid;
            else
                lo = mid + 1;
        }

        return lo;
    }
};