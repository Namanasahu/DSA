class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> cnt;

        // Count in how many length-k subarrays each number appears.
        for (int i = 0; i <= n - k; i++) {
            unordered_set<int> seen;

            for (int j = i; j < i + k; j++) {
                seen.insert(nums[j]);
            }

            for (int x : seen) {
                cnt[x]++;
            }
        }

        int ans = -1;

        for (auto &[x, c] : cnt) {
            if (c == 1) {
                ans = max(ans, x);
            }
        }

        return ans;
    }
};