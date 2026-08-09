class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* pA = headA;
        ListNode* pB = headB;

        while (pA != pB) {
            if (pA == nullptr)
                pA = headB;
            else
                pA = pA->next;

            if (pB == nullptr)
                pB = headA;
            else
                pB = pB->next;
        }

        return pA;
    }
};