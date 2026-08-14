class Solution {
public:
    vector<int> divisibilityArray(string word, int m) {
        vector<int> ans(word.size());
        
        long long rem = 0;

        for (int i = 0; i < word.size(); i++) {
            int digit = word[i] - '0';

            rem = (rem * 10 + digit) % m;

            if (rem == 0)
                ans[i] = 1;
            else
                ans[i] = 0;
        }

        return ans;
    }
};