class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long ans = 0;
        long long cnt = 0;

        for (int x : nums) {
            if (x == 0) {
                cnt++;
                ans += cnt;
            } else {
                cnt = 0;
            }
        }

        return ans;
    }
};