# Contains Duplicate

**LeetCode Problem:** [https://leetcode.com/problems/contains-duplicate/](https://leetcode.com/problems/contains-duplicate/)

## Problem Description

Given an integer array `nums`, return `true` if any value appears at least twice in the array, and return `false` if every element is distinct.

## Examples

### Example 1:
**Input:** `nums = [1,2,3,1]`

**Output:** `true`

**Explanation:** The element 1 occurs at the indices 0 and 3.

### Example 2:
**Input:** `nums = [1,2,3,4]`

**Output:** `false`

**Explanation:** All elements are distinct.

### Example 3:
**Input:** `nums = [1,1,1,3,3,4,3,2,4,2]`

**Output:** `true`

## Constraints

- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

---

## Solutions

### Solution 1: Brute Force

#### Intuition
We can check every pair of different elements in the array and return `true` if any pair has equal values. This is the most intuitive approach because it directly compares all possible pairs, but it is also the least efficient since it examines every combination.

#### Algorithm
1. Iterate through the array using two nested loops to check all possible pairs of distinct indices.
2. If any pair of elements has the same value, return `true`.
3. If all pairs are checked and no duplicates are found, return `false`.

#### Visual Example
```
nums = [3, 1, 4, 1, 5]

Compare all pairs:
  i=0: (3,1) (3,4) (3,1) (3,5) → No match
  i=1: (1,4) (1,1) ← MATCH FOUND!

return true
```

#### Code
```cpp
class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        return false;
    }
};
```

#### Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n²) | Nested loops compare every pair of elements |
| **Space** | O(1) | No additional data structures used |

---

### Solution 2: Sorting

#### Intuition
If we sort the array, then any duplicate values will appear next to each other. Sorting groups identical elements together, so we can simply check adjacent positions to detect duplicates. This reduces the problem to a single linear scan after sorting, making it easy to identify if any value repeats.

#### Algorithm
1. Sort the array in non-decreasing order.
2. Iterate through the array starting from index 1.
3. Compare the current element with the previous element.
4. If both elements are equal, we have found a duplicate — return `true`.
5. If the loop finishes without detecting equal neighbors, return `false`.

#### Visual Example
```
nums: [3, 5, 1, 3]
         ↓
Sort: [1, 3, 3, 5]
          ↑  ↑
       Adjacent duplicates found!
       
return true
```

#### Code
```cpp
class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                return true;
            }
        }
        return false;
    }
};
```

#### Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n log n) | Dominated by the sorting algorithm |
| **Space** | O(1) or O(n) | Depends on the sorting algorithm used |

---

### Solution 3: Hash Set ✅

#### Intuition
We can use a hash set to efficiently keep track of the values we have already encountered. As we iterate through the array, we check whether the current value is already present in the set. If it is, that means we've seen this value before, so a duplicate exists. Using a hash set allows constant-time lookups, making this approach much more efficient than comparing every pair.

#### Algorithm
1. Initialize an empty hash set to store seen values.
2. Iterate through each number in the array.
3. For each number:
   - If it is already in the set, return `true` because a duplicate has been found.
   - Otherwise, add it to the set.
4. If the loop finishes without finding any duplicates, return `false`.

#### Visual Example (Duplicate Found)
```
nums: [3, 1, 4, 1, 5]

Step 1: Check 3 → Not in set → Insert 3      Set: {3}
Step 2: Check 1 → Not in set → Insert 1      Set: {3, 1}
Step 3: Check 4 → Not in set → Insert 4      Set: {3, 1, 4}
Step 4: Check 1 → Already in set! ✓          
        
return true (duplicate found)
```

#### Visual Example (No Duplicate)
```
nums: [3, 1, 4, 6, 5]

Step 1: Check 3 → Not in set → Insert 3      Set: {3}
Step 2: Check 1 → Not in set → Insert 1      Set: {3, 1}
Step 3: Check 4 → Not in set → Insert 4      Set: {3, 1, 4}
Step 4: Check 6 → Not in set → Insert 6      Set: {3, 1, 4, 6}
Step 5: Check 5 → Not in set → Insert 5      Set: {3, 1, 4, 6, 5}

return false (no duplicates)
```

#### Code
```cpp
class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.count(num)) {
                return true;
            }
            seen.insert(num);
        }
        return false;
    }
};
```

#### Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n) | Single pass through the array with O(1) set operations |
| **Space** | O(n) | Storing up to n elements in the hash set |

---

### Solution 4: Hash Set Length

#### Intuition
This approach uses the same idea as the previous hash set method: a set only stores unique values, so duplicates are automatically removed. Instead of checking each element manually, we simply compare the length of the set to the length of the original array. If duplicates exist, the set will contain fewer elements. The logic is identical to the earlier approach — this version is just a shorter and more concise implementation of it.

#### Algorithm
1. Convert the array into a hash set, which removes duplicates.
2. Compare the size of the set with the size of the original array.
3. If the set is smaller, return `true` because duplicates must have been removed.
4. Otherwise, return `false`.

#### Visual Example
```
nums: [3, 1, 4, 1, 5]  → size = 5

Convert to set: {3, 1, 4, 5}  → size = 4

5 > 4 → Duplicates exist!

return true
```

#### Code
```cpp
class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        return unordered_set<int>(nums.begin(), nums.end()).size() < nums.size();
    }
};
```

#### Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n) | Inserting n elements into the hash set |
| **Space** | O(n) | Storing up to n elements in the hash set |

---

## Summary Comparison

| Solution | Time Complexity | Space Complexity | Notes |
|----------|-----------------|------------------|-------|
| **Brute Force** | O(n²) | O(1) | Simple but inefficient |
| **Sorting** | O(n log n) | O(1) or O(n) | Modifies the original array |
| **Hash Set** | O(n) | O(n) | Optimal, early termination |
| **Hash Set Length** | O(n) | O(n) | Concise one-liner |
