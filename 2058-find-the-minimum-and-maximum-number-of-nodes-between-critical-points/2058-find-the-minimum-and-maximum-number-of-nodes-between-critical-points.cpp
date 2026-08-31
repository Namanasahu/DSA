class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        
        int first = -1;
        int last = -1;
        
        int minDist = INT_MAX;
        int index = 1;
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        
        while (curr->next != nullptr) {
            
            // Check whether curr is a critical point
            bool isCritical =
                (curr->val > prev->val && curr->val > curr->next->val) ||
                (curr->val < prev->val && curr->val < curr->next->val);
            
            if (isCritical) {
                
                // First critical point
                if (first == -1) {
                    first = index;
                    last = index;
                }
                else {
                    // Distance from previous critical point
                    minDist = min(minDist, index - last);
                    
                    // Update latest critical point
                    last = index;
                }
            }
            
            prev = curr;
            curr = curr->next;
            index++;
        }
        
        // Less than 2 critical points
        if (first == last) {
            return {-1, -1};
        }
        
        int maxDist = last - first;
        
        return {minDist, maxDist};
    }
};