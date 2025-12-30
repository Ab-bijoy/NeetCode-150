# Group Anagrams

## Problem Link
[LeetCode - Group Anagrams](https://leetcode.com/problems/group-anagrams/description/)

---

## Problem Description

Given an array of strings `strs`, group the anagrams together. You can return the answer in any order.

---

## Examples

### Example 1:

| Input | Output |
|-------|--------|
| `strs = ["eat","tea","tan","ate","nat","bat"]` | `[["bat"],["nat","tan"],["ate","eat","tea"]]` |

**Explanation:**
- There is no string in `strs` that can be rearranged to form `"bat"`.
- The strings `"nat"` and `"tan"` are anagrams as they can be rearranged to form each other.
- The strings `"ate"`, `"eat"`, and `"tea"` are anagrams as they can be rearranged to form each other.

### Example 2:

| Input | Output |
|-------|--------|
| `strs = [""]` | `[[""]]` |

### Example 3:

| Input | Output |
|-------|--------|
| `strs = ["a"]` | `[["a"]]` |

---

## Constraints

| Constraint | Range |
|------------|-------|
| `strs.length` | `1 <= strs.length <= 10⁴` |
| `strs[i].length` | `0 <= strs[i].length <= 100` |
| Character set | `strs[i]` consists of lowercase English letters |

---

## Solutions

### 1. Sorting

#### Intuition

Anagrams become identical when their characters are sorted. For example, `"eat"`, `"tea"`, and `"ate"` all become `"aet"` after sorting. By using the sorted version of each string as a key, we can group all anagrams together. Strings that share the same sorted form must be anagrams, so placing them in the same group is both natural and efficient.

#### Algorithm

1. Create a hash map where each key is the sorted version of a string, and the value is a list of strings belonging to that anagram group.
2. Iterate through each string in the input list:
   - Sort the characters of the string to form a key.
   - Append the original string to the list corresponding to this key.
3. After processing all strings, return all values from the hash map, which represent the grouped anagrams.

#### Code

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (auto u : strs) {
            string sorted_S = u;
            sort(sorted_S.begin(), sorted_S.end());
            mp[sorted_S].push_back(u);
        }
        vector<vector<string>> res;
        for (auto u : mp) {
            res.push_back(u.second);
        }
        return res;
    }
};
```

#### Complexity Analysis

| Complexity | Value |
|------------|-------|
| **Time** | O(m * n log n) |
| **Space** | O(m * n) |

> Where `m` is the number of strings and `n` is the length of the longest string.

---

### 2. Hash Table (Character Frequency)

#### Intuition

Instead of sorting each string, we can represent every string by the frequency of its characters. Since the problem uses lowercase English letters, a fixed-size array of length 26 can capture how many times each character appears. Two strings are anagrams if and only if their frequency arrays are identical. By using this frequency array (converted to a string key), we can group all strings that share the same character counts.

#### Algorithm

1. Create a hash map where each key is a string representation of character frequencies, and each value is a list of strings belonging to that anagram group.
2. For each string in the input:
   - Initialize a frequency array of size 26 with all zeros.
   - For each character in the string, increment the count at the corresponding index.
   - Convert the frequency array to a string and use it as the key.
   - Append the string to the list associated with this key.
3. After processing all strings, return all the lists stored in the hash map.

#### Code

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (auto u : strs) {
            vector<int> frq(26, 0);
            for (auto c : u) {
                frq[c - 'a']++;
            }
            string key = to_string(frq[0]);
            for (int i = 1; i < 26; ++i) {
                key += ',' + to_string(frq[i]);
            }
            mp[key].push_back(u);
        }
        vector<vector<string>> res;
        for (auto u : mp) {
            res.push_back(u.second);
        }
        return res;
    }
    
};
```

#### Complexity Analysis

| Complexity | Value |
|------------|-------|
| **Time** | O(m * n) |
| **Space** | O(m) extra space, O(m * n) for the output list |

> Where `m` is the number of strings and `n` is the length of the longest string.

---

## Complexity Comparison

| Solution | Time Complexity | Space Complexity |
|----------|-----------------|------------------|
| **1. Sorting** | O(m * n log n) | O(m * n) |
| **2. Hash Table (Character Frequency)** | O(m * n) | O(m * n) |

> **Note:** The Hash Table approach is more efficient as it avoids the O(n log n) sorting overhead per string.
