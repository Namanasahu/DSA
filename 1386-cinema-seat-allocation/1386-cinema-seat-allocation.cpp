class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        // Store reserved seats as bitmask for each row
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            mp[row] |= (1 << col);
        }

        // Initially, every row can accommodate 2 families
        int ans = 2 * n;

        for (auto &[row, mask] : mp) {
            bool left = true;    // seats 2,3,4,5
            bool middle = true;  // seats 4,5,6,7
            bool right = true;   // seats 6,7,8,9

            for (int seat = 2; seat <= 5; seat++) {
                if (mask & (1 << seat)) {
                    left = false;
                    break;
                }
            }

            for (int seat = 4; seat <= 7; seat++) {
                if (mask & (1 << seat)) {
                    middle = false;
                    break;
                }
            }

            for (int seat = 6; seat <= 9; seat++) {
                if (mask & (1 << seat)) {
                    right = false;
                    break;
                }
            }

            // We initially counted 2 families for this row.
            // Now calculate the actual number.
            if (left && right) {
                // Both sides are available => 2 families
            }
            else if (left || middle || right) {
                // At least one group is available => 1 family
                ans -= 1;
            }
            else {
                // No group is available => 0 families
                ans -= 2;
            }
        }

        return ans;
    }
};