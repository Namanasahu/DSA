class Solution {
public:
    bool sumGame(string num) {
        int n = num.length();
        double sumLeft = 0, sumRight = 0;
        double qLeft = 0, qRight = 0;

        // Process the first half
        for (int i = 0; i < n / 2; i++) {
            if (num[i] == '?') {
                qLeft++;
            } else {
                sumLeft += num[i] - '0';
            }
        }

        // Process the second half
        for (int i = n / 2; i < n; i++) {
            if (num[i] == '?') {
                qRight++;
            } else {
                sumRight += num[i] - '0';
            }
        }

        // If the total number of '?' is odd, Alice makes the last move and wins.
        if (static_cast<int>(qLeft + qRight) % 2 != 0) {
            return true;
        }

        // Check if Bob can perfectly balance the sums. 
        // If not, Alice wins (return true).
        return (sumLeft - sumRight) != (qRight - qLeft) * 4.5;
    }
};