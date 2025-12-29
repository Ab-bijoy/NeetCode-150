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

**Approach:** Sort both strings and compare if they are equal.

**Example:**
```
s = "anagram"  →  sorted: "aaagmnr"
t = "nagaram"  →  sorted: "aaagmnr"

Both sorted strings are equal → return true
```

**Complexity:**
- **Time Complexity:** `O(n log n)` — due to sorting
- **Space Complexity:** `O(n)` — space needed for sorted strings

---

### Solution 2: Hash Map / Frequency Count (Optimal) ✅

**Approach:** Count the frequency of each character in both strings. If the frequency counts match, they are anagrams.

**Example 1 (Anagram):**
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

**Example 2 (Not Anagram):**
```
s = "rat"
t = "car"

Frequency count for s:     Frequency count for t:
r → 1                      c → 1
a → 1                      a → 1
t → 1                      r → 1

Counts don't match (s has 't', t has 'c') → return false
```

**Complexity:**
- **Time Complexity:** `O(n)` — single pass through both strings
- **Space Complexity:** `O(1)` — fixed size array (26 letters) or `O(k)` for Unicode where k = unique characters

---

### Solution 3: Array Frequency Count (Best for lowercase letters)

**Approach:** Use a fixed-size array of 26 elements. Increment for characters in `s`, decrement for characters in `t`. If all counts are 0, they are anagrams.

**Example:**
```
s = "anagram", t = "nagaram"

Initialize: freq[26] = {0, 0, 0, ..., 0}

Process s: increment counts
Process t: decrement counts

Final: freq[26] = {0, 0, 0, ..., 0}  → All zeros → return true
```

**Complexity:**
- **Time Complexity:** `O(n)` — single pass
- **Space Complexity:** `O(1)` — fixed 26-element array

---

## Unicode Follow-up Answer

For Unicode characters, use a **Hash Map** instead of a fixed-size array:
- Use `unordered_map<char, int>` (C++) or `HashMap<Character, Integer>` (Java) or `Counter` (Python)
- This handles any character set dynamically
- Space complexity becomes `O(k)` where k = number of unique characters
