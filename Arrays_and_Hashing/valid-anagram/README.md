# Valid Anagram

**LeetCode Problem:** [https://leetcode.com/problems/valid-anagram/description/](https://leetcode.com/problems/valid-anagram/description/)

## Problem Description

Given two strings `s` and `t`, return `true` if `t` is an anagram of `s`, and `false` otherwise.

An **anagram** is a word formed by rearranging the letters of another word, using all the original letters exactly once.

## Examples

### Example 1:
**Input:** `s = "anagram"`, `t = "nagaram"`

**Output:** `true`

### Example 2:
**Input:** `s = "rat"`, `t = "car"`

**Output:** `false`

## Constraints

- `1 <= s.length, t.length <= 5 * 10^4`
- `s` and `t` consist of lowercase English letters.

## Follow Up

What if the inputs contain Unicode characters? How would you adapt your solution to such a case?

---

## Solutions

### Solution 1: Sorting

#### Intuition
If two strings are anagrams, they must contain exactly the same characters with the same frequencies. By sorting both strings, all characters will be arranged in a consistent order. If the two sorted strings are identical, then every character and its count match, which means the strings are anagrams.

#### Algorithm
1. If the lengths of the two strings differ, return `false` immediately because they cannot be anagrams.
2. Sort both strings.
3. Compare the sorted versions of the strings:
   - If they are equal, return `true`.
   - Otherwise, return `false`.

#### Visual Example
```
s = "anagram"  →  sorted: "aaagmnr"
t = "nagaram"  →  sorted: "aaagmnr"

Both sorted strings are equal → return true
```

#### Code
```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};
```

#### Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n log n + m log m) | Sorting both strings |
| **Space** | O(1) or O(n + m) | Depends on the sorting algorithm |

> Where `n` is the length of string `s` and `m` is the length of string `t`.

---

### Solution 2: Hash Map

#### Intuition
If two strings are anagrams, they must use the same characters with the same frequencies. Instead of sorting, we can count how many times each character appears in both strings. By using two hash maps (or dictionaries), we track the frequency of every character in each string. If both frequency maps match exactly, then the strings contain the same characters with same frequencies, meaning they are anagrams.

#### Algorithm
1. If the two strings have different lengths, return `false` immediately.
2. Create two hash maps to store character frequencies for each string.
3. Iterate through both strings at the same time:
   - Increase the character count for `s[i]` in the first map.
   - Increase the character count for `t[i]` in the second map.
4. After building both maps, compare them:
   - If the maps are equal, return `true`.
   - Otherwise, return `false`.

#### Visual Example
```
s = "anagram"
t = "nagaram"

Frequency count for s:     Frequency count for t:
a → 3                      a → 3
n → 1                      n → 1
g → 1                      g → 1
r → 1                      r → 1
m → 1                      m → 1

Counts match → return true
```

#### Code
```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        unordered_map<char, int> countS;
        unordered_map<char, int> countT;
        for (int i = 0; i < s.length(); i++) {
            countS[s[i]]++;
            countT[t[i]]++;
        }
        return countS == countT;
    }
};
```

#### Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n + m) | Single pass through both strings |
| **Space** | O(1) | At most 26 different characters |

> Where `n` is the length of string `s` and `m` is the length of string `t`.

---

### Solution 3: Hash Table (Using Array) ✅

#### Intuition
Since the problem guarantees lowercase English letters, we can use a fixed-size array of length 26 to count character frequencies instead of a hash map. As we iterate through both strings simultaneously, we increment the count for each character in `s` and decrement the count for each character in `t`. If the strings are anagrams, every increment will be matched by a corresponding decrement, and all values in the array will end at zero. This approach is efficient because it avoids hashing and uses constant space.

#### Algorithm
1. If the lengths of the strings differ, return `false` immediately.
2. Create a frequency array `count` of size 26 initialized to zero.
3. Iterate through both strings:
   - Increment the count at the index corresponding to `s[i]`.
   - Decrement the count at the index corresponding to `t[i]`.
4. After processing both strings, scan through the count array:
   - If any value is not zero, return `false` because the frequencies differ.
   - If all values are zero, return `true` since the strings are anagrams.

#### Visual Example
```
s = "anagram", t = "nagaram"

Initialize: count[26] = {0, 0, 0, ..., 0}

Process simultaneously:
  s[0]='a', t[0]='n' → count['a'-'a']++, count['n'-'a']--
  s[1]='n', t[1]='a' → count['n'-'a']++, count['a'-'a']--
  ... (continues for all characters)

Final: count[26] = {0, 0, 0, ..., 0} → All zeros → return true
```

#### Code
```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        vector<int> count(26, 0);
        for (int i = 0; i < s.length(); i++) {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }

        for (int val : count) {
            if (val != 0) {
                return false;
            }
        }
        return true;
    }
};
```

#### Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n + m) | Single pass through both strings + array scan |
| **Space** | O(1) | Fixed 26-element array |

> Where `n` is the length of string `s` and `m` is the length of string `t`.

---

## Summary Comparison

| Solution | Time Complexity | Space Complexity | Notes |
|----------|-----------------|------------------|-------|
| **Sorting** | O(n log n + m log m) | O(1) or O(n + m) | Simple but slower |
| **Hash Map** | O(n + m) | O(1) | Good for any character set |
| **Array (Optimal)** | O(n + m) | O(1) | Best for lowercase letters |

---

## Unicode Follow-up Answer

For Unicode characters, use a **Hash Map** instead of a fixed-size array:
- Use `unordered_map<char, int>` (C++) or `HashMap<Character, Integer>` (Java) or `Counter` (Python)
- This handles any character set dynamically
- Space complexity becomes `O(k)` where k = number of unique characters
