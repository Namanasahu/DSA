class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        vector<int> arr1, arr2;
        
        // Initial distribution
        arr1.push_back(nums[0]);
        arr2.push_back(nums[1]);
        
        // Distribute the rest based on the last elements
        for (int i = 2; i < nums.size(); ++i) {
            if (arr1.back() > arr2.back()) {
                arr1.push_back(nums[i]);
            } else {
                arr2.push_back(nums[i]);
            }
        }
        
        // Concatenate arr2 to the end of arr1
        arr1.insert(arr1.end(), arr2.begin(), arr2.end());
        
        return arr1;
    }
};