class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> ans;

        // nextMatch[i] = maximum length of word2 that can be
        // matched as a subsequence in word1[i...n-1]
        vector<int> suf(n + 1, 0);

        int j = m - 1;

        for (int i = n - 1; i >= 0; --i) {
            suf[i] = suf[i + 1];

            if (j >= 0 && word1[i] == word2[j]) {
                suf[i]++;
                j--;
            }
        }

        int p = 0;
        bool used = false;

        for (int k = 0; k < m; k++) {

            // Find the earliest possible position.
            while (p < n) {

                // Case 1: exact match
                if (word1[p] == word2[k]) {
                    ans.push_back(p);
                    p++;
                    break;
                }

                // Case 2: use the one allowed mismatch
                if (!used) {
                    int remaining = m - k - 1;

                    // Can the remaining word2 be matched
                    // after choosing p?
                    if (suf[p + 1] >= remaining) {
                        ans.push_back(p);
                        p++;
                        used = true;
                        break;
                    }
                }

                p++;
            }

            // Couldn't find a valid position
            if ((int)ans.size() != k + 1)
                return {};
        }

        return ans;
    }
};