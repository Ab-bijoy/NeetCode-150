# [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/description/)

**Difficulty:** Easy

## Problem

A phrase is a **palindrome** if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string `s`, return `true` if it is a palindrome, or `false` otherwise.

### Example 1:
```
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
```

### Example 2:
```
Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
```

### Example 3:
```
Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.
```

### Constraints:
- `1 <= s.length <= 2 * 10^5`
- `s` consists only of printable ASCII characters.

---

## 1. Reverse String

### Intuition

To check if a string is a palindrome, we only care about letters and digits—everything else can be ignored.

We can build a cleaned version of the string that contains only alphanumeric characters, all converted to lowercase for consistency.

Once we have this cleaned string, the problem becomes very simple: a string is a palindrome if it is exactly the same as its reverse.

### Algorithm

1. Create an empty string `newStr`.
2. Loop through each character `c` in the input string:
   - If `c` is alphanumeric, convert it to lowercase and add it to `newStr`.
3. Compare `newStr` with its reverse (`newStr[::-1]`):
   - If they are equal, return `true`.
   - Otherwise, return `false`.

### Code

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        string newStr = "";
        for (char c : s) {
            if (isalnum(c)) {
                newStr += tolower(c);
            }
        }
        return newStr == string(newStr.rbegin(), newStr.rend());
    }
};
```

### Complexity

- **Time complexity:** O(n)
- **Space complexity:** O(n)

---

## 2. Two Pointers

### Intuition

Instead of building a new string, we can check the palindrome directly in-place using two pointers.

One pointer starts at the beginning (`l`) and the other at the end (`r`). We move both pointers inward, skipping any characters that are not letters or digits. Whenever both pointers point to valid characters, we compare them in lowercase form. If at any point they differ, the string is not a palindrome.

This method avoids extra space and keeps the logic simple and efficient.

### Algorithm

1. Initialize two pointers:
   - `l` at the start of the string,
   - `r` at the end of the string.
2. While `l` is less than `r`:
   - Move `l` forward until it points to an alphanumeric character.
   - Move `r` backward until it points to an alphanumeric character.
   - Compare the lowercase characters at `l` and `r`:
     - If they don't match, return `false`.
   - Move both pointers inward: `l += 1`, `r -= 1`.
3. If the loop finishes without mismatches, return `true`.

### Code

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0, r = s.length() - 1;

        while (l < r) {
            while (l < r && !alphaNum(s[l])) {
                l++;
            }
            while (r > l && !alphaNum(s[r])) {
                r--;
            }
            if (tolower(s[l]) != tolower(s[r])) {
                return false;
            }
            l++; r--;
        }
        return true;
    }

    bool alphaNum(char c) {
        return (c >= 'A' && c <= 'Z' ||
                c >= 'a' && c <= 'z' ||
                c >= '0' && c <= '9');
    }
};
```

### Complexity

- **Time complexity:** O(n)
- **Space complexity:** O(1)
