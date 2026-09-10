class Solution {
public:
    int ans = 0;
    
    pair<int, int> dfs(TreeNode* root) {
        if (root == nullptr) {
            return {0, 0}; 
        }
        
        auto left = dfs(root->left);
        auto right = dfs(root->right);
        
        int sum = left.first + right.first + root->val;
        int count = left.second + right.second + 1;
        
        if (sum / count == root->val) {
            ans++; 
        }
        
        return {sum, count};
    }
    
    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};