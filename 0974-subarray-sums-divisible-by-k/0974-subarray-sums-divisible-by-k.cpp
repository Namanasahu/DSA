class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        vector<int> freq(k, 0);

        // Empty prefix sum has remainder 0
        freq[0] = 1;

        int prefix = 0;
        int ans = 0;

        for (int x : nums) {
            prefix += x;

            int rem = prefix % k;

            // C++ can give negative remainder
            if (rem < 0)
                rem += k;

            // Previous same remainder forms valid subarrays
            ans += freq[rem];

            freq[rem]++;
        }

        return ans;
    }
};