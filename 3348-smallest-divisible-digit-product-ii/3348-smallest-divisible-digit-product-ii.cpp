#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    // Returns {cnt9, cnt8, cnt7, cnt6, cnt5, cnt4, cnt3, cnt2}
    vector<int> getMinDigits(long long c2, long long c3, long long c5, long long c7) {
        c2 = max(0LL, c2);
        c3 = max(0LL, c3);
        c5 = max(0LL, c5);
        c7 = max(0LL, c7);

        int cnt9 = c3 / 2;
        int r3 = c3 % 2;

        int cnt8 = c2 / 3;
        int r2 = c2 % 3;

        int cnt7 = c7;
        int cnt5 = c5;
        int cnt6 = 0, cnt4 = 0, cnt3 = 0, cnt2 = 0;

        if (r2 == 1 && r3 == 1) {
            cnt6 = 1;
        } else if (r2 == 2 && r3 == 1) {
            cnt6 = 1;
            cnt2 = 1;
        } else {
            if (r2 == 2) cnt4 = 1;
            if (r2 == 1) cnt2 = 1;
            if (r3 == 1) cnt3 = 1;
        }

        return {cnt9, cnt8, cnt7, cnt6, cnt5, cnt4, cnt3, cnt2};
    }

    int sumDigits(const vector<int>& counts) {
        int total = 0;
        for (int x : counts) total += x;
        return total;
    }

    // Helper to extract prime factors of digits 2..9
    void addFactors(int digit, long long& c2, long long& c3, long long& c5, long long& c7, int mult = 1) {
        if (digit == 2) c2 += mult * 1;
        else if (digit == 3) c3 += mult * 1;
        else if (digit == 4) c2 += mult * 2;
        else if (digit == 5) c5 += mult * 1;
        else if (digit == 6) { c2 += mult * 1; c3 += mult * 1; }
        else if (digit == 7) c7 += mult * 1;
        else if (digit == 8) c2 += mult * 3;
        else if (digit == 9) c3 += mult * 2;
    }

    string constructSuffix(long long c2, long long c3, long long c5, long long c7, int len) {
        vector<int> counts = getMinDigits(c2, c3, c5, c7);
        // Digit order: 2, 3, 4, 5, 6, 7, 8, 9
        int req = sumDigits(counts);
        string res = string(len - req, '1');
        
        int digits[] = {9, 8, 7, 6, 5, 4, 3, 2};
        for (int i = 7; i >= 0; --i) {
            res.append(counts[i], '0' + digits[i]);
        }
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        long long req2 = 0, req3 = 0, req5 = 0, req7 = 0;
        
        // Prime factorize t
        while (t % 2 == 0) { req2++; t /= 2; }
        while (t % 3 == 0) { req3++; t /= 3; }
        while (t % 5 == 0) { req5++; t /= 5; }
        while (t % 7 == 0) { req7++; t /= 7; }
        
        // Impossible if t has prime factors > 7
        if (t > 1) return "-1";

        int n = num.length();
        int firstZero = num.find('0');
        if (firstZero == string::npos) firstZero = n;

        // Check if original num is valid
        if (firstZero == n) {
            long long cur2 = 0, cur3 = 0, cur5 = 0, cur7 = 0;
            for (char c : num) {
                addFactors(c - '0', cur2, cur3, cur5, cur7);
            }
            if (cur2 >= req2 && cur3 >= req3 && cur5 >= req5 && cur7 >= req7) {
                return num;
            }
        }

    
        long long pref2 = 0, pref3 = 0, pref5 = 0, pref7 = 0;
        for (int i = 0; i < firstZero; ++i) {
            addFactors(num[i] - '0', pref2, pref3, pref5, pref7);
        }

        
        for (int i = min(n - 1, firstZero); i >= 0; --i) {
            if (i < firstZero) {
                addFactors(num[i] - '0', pref2, pref3, pref5, pref7, -1);
            }

            int startDigit = (i == firstZero) ? 1 : (num[i] - '0' + 1);
            int remSpace = n - 1 - i;

            for (int d = startDigit; d <= 9; ++d) {
                long long rem2 = req2 - pref2;
                long long rem3 = req3 - pref3;
                long long rem5 = req5 - pref5;
                long long rem7 = req7 - pref7;

               
                addFactors(d, rem2, rem3, rem5, rem7, -1);

                vector<int> minD = getMinDigits(rem2, rem3, rem5, rem7);
                if (sumDigits(minD) <= remSpace) {
                    string ans = num.substr(0, i);
                    ans += (char)('0' + d);
                    ans += constructSuffix(rem2, rem3, rem5, rem7, remSpace);
                    return ans;
                }
            }
        }

        
        vector<int> minD = getMinDigits(req2, req3, req5, req7);
        int targetLen = max(n + 1, sumDigits(minD));
        return constructSuffix(req2, req3, req5, req7, targetLen);
    }
};