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

### Solution 1: Sorting

**Approach:** Sort the array first, then check adjacent elements for duplicates.

**Example:**
```
nums: [3, 5, 1, 3]
         ↓
Sort: [1, 3, 3, 5]
          ↑  ↑
       Adjacent duplicates found!
       
return true
```

**Complexity:**
- **Time Complexity:** `O(n log n)` — due to sorting
- **Space Complexity:** `O(1)` or `O(n)` — depending on sorting algorithm

---

### Solution 2: Hash Set (Optimal) ✅

**Approach:** Keep track of all numbers using a HashSet/unordered_set. For each element:
1. Check if it already exists in the set → return `true` (duplicate found)
2. If not, insert the element into the set
3. If we finish iterating without finding duplicates → return `false`

**Example 1 (Duplicate Found):**
```
nums: [3, 1, 4, 1, 5]

Step 1: Check 3 → Not in set → Insert 3      Set: {3}
Step 2: Check 1 → Not in set → Insert 1      Set: {3, 1}
Step 3: Check 4 → Not in set → Insert 4      Set: {3, 1, 4}
Step 4: Check 1 → Already in set! ✓          
        
return true (duplicate found)
```

**Example 2 (No Duplicate):**
```
nums: [3, 1, 4, 6, 5]

Step 1: Check 3 → Not in set → Insert 3      Set: {3}
Step 2: Check 1 → Not in set → Insert 1      Set: {3, 1}
Step 3: Check 4 → Not in set → Insert 4      Set: {3, 1, 4}
Step 4: Check 6 → Not in set → Insert 6      Set: {3, 1, 4, 6}
Step 5: Check 5 → Not in set → Insert 5      Set: {3, 1, 4, 6, 5}

return false (no duplicates)
```

**Complexity:**
- **Time Complexity:** `O(n)` — single pass through array, O(1) set operations
- **Space Complexity:** `O(n)` — storing up to n elements in the set


```
