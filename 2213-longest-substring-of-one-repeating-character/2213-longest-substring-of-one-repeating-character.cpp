#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int max_len;   // Longest substring length within this segment
    int pref_len;  // Length of prefix with repeating character
    int suff_len;  // Length of suffix with repeating character
    char left_ch;  // First character of segment
    char right_ch; // Last character of segment
    int size;      // Range length covered by node
};

class Solution {
private:
    vector<Node> tree;
    string s;

    // Helper to merge two child nodes into a parent node
    Node merge(const Node& left, const Node& right) {
        Node res;
        res.size = left.size + right.size;
        res.left_ch = left.left_ch;
        res.right_ch = right.right_ch;

        // Base prefix length from left child
        res.pref_len = left.pref_len;
        // If left child is uniform and matches right child's prefix character
        if (left.pref_len == left.size && left.right_ch == right.left_ch) {
            res.pref_len += right.pref_len;
        }

        // Base suffix length from right child
        res.suff_len = right.suff_len;
        // If right child is uniform and matches left child's suffix character
        if (right.suff_len == right.size && right.left_ch == left.right_ch) {
            res.suff_len += left.suff_len;
        }

        // Maximum sequence within left, right, or bridging the boundary
        res.max_len = max(left.max_len, right.max_len);
        if (left.right_ch == right.left_ch) {
            res.max_len = max(res.max_len, left.suff_len + right.pref_len);
        }

        return res;
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = {1, 1, 1, s[start], s[start], 1};
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, char val) {
        if (start == end) {
            s[idx] = val;
            tree[node] = {1, 1, 1, val, val, 1};
            return;
        }
        int mid = start + (end - start) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        this->s = s;
        int n = s.size();
        tree.resize(4 * n);
        
        build(1, 0, n - 1);

        int k = queryIndices.size();
        vector<int> ans(k);

        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans[i] = tree[1].max_len;
        }

        return ans;
    }
};