class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIndex = 0;
        int maxIndex = 0;

        // Find minimum and maximum indices
        for (int i = 0; i < n; i++) {
            if (nums[i] < nums[minIndex])
                minIndex = i;

            if (nums[i] > nums[maxIndex])
                maxIndex = i;
        }

        // left = smaller index
        // right = larger index
        int left = min(minIndex, maxIndex);
        int right = max(minIndex, maxIndex);

        // 3 possibilities:
        // 1. Both from front
        int fromFront = right + 1;

        // 2. Both from back
        int fromBack = n - left;

        // 3. One from front, one from back
        int fromBoth = (left + 1) + (n - right);

        return min({fromFront, fromBack, fromBoth});
    }
};