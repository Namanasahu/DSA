class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        // right[i] = minimum element from i to n-1
        vector<int> right(n);

        right[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            right[i] = min(nums[i], right[i + 1]);
        }

        // left = maximum element from 0 to i
        int left = 0;

        for (int i = 0; i < n; i++) {
            left = max(left, nums[i]);

            if (left - right[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};