class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int mn = INT_MAX, mx = INT_MIN;
        unordered_set<int> st;

        for (int x : nums) {
            mn = min(mn, x);
            mx = max(mx, x);
            st.insert(x);
        }

        vector<int> ans;
        for (int x = mn + 1; x < mx; x++) {
            if (!st.count(x))
                ans.push_back(x);
        }

        return ans;
    }
};