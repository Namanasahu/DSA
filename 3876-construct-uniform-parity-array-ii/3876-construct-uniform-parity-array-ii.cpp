#include <vector>
#include <algorithm>

class Solution {
public:
    bool uniformArray(std::vector<int>& nums1) {
        // Find the smallest element in the array
        int min_val = *std::min_element(nums1.begin(), nums1.end());
        
        // If the smallest element is odd, we can make all elements odd
        if (min_val % 2 != 0) {
            return true;
        }
        
        // If the smallest element is even, we can only succeed if ALL elements are already even
        for (int num : nums1) {
            if (num % 2 != 0) {
                return false; // Found an odd number that can't be converted
            }
        }
        
        return true;
    }
};