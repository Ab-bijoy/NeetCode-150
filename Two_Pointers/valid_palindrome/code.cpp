// 125. Valid Palindrome
// https://leetcode.com/problems/valid-palindrome/description/

// Two Pointers Approach
// Time Complexity: O(n)
// Space Complexity: O(1)

class Solution {
public:
    bool isPalindrome(string s) {
        for (auto& x : s) {
            x = tolower(x);
        }

        int i = 0;
        int j = s.size() - 1;

        while (i <= j && j >= 0 && i < s.size()) {
            if (!isalnum(s[i])) { i++; continue; }
            if (!isalnum(s[j])) { j--; continue; }

            if (s[i] != s[j]) { return false; }

            i++;
            j--;
        }

        return true;
    }
};
