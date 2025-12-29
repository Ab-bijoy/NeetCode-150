# Two Sum

**LeetCode Problem:** [https://leetcode.com/problems/two-sum/description/](https://leetcode.com/problems/two-sum/description/)

## Problem Description

Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

You may assume that each input would have **exactly one solution**, and you may not use the same element twice.

You can return the answer in any order.

## Examples

### Example 1:
**Input:** `nums = [2,7,11,15]`, `target = 9`

**Output:** `[0,1]`

**Explanation:** Because `nums[0] + nums[1] == 9`, we return `[0, 1]`.

### Example 2:
**Input:** `nums = [3,2,4]`, `target = 6`

**Output:** `[1,2]`

### Example 3:
**Input:** `nums = [3,3]`, `target = 6`

**Output:** `[0,1]`

## Constraints

- `2 <= nums.length <= 10^4`
- `-10^9 <= nums[i] <= 10^9`
- `-10^9 <= target <= 10^9`
- Only one valid answer exists.

## Follow Up

Can you come up with an algorithm that is less than `O(n²)` time complexity?

---

## Solutions

### Solution 1: Brute Force

**Approach:** Check every pair of elements to see if they sum to target.

**Visual Diagram:**
```
nums = [2, 7, 11, 15], target = 9

Index:   0    1    2    3
       +----+----+----+----+
nums:  | 2  | 7  | 11 | 15 |
       +----+----+----+----+
         ↓    ↓
         i    j
         
Check all pairs:
  i=0, j=1: nums[0] + nums[1] = 2 + 7 = 9 ✓ Found!
  
return [0, 1]
```

**Step-by-step:**
```
For i = 0:
    For j = 1: 2 + 7 = 9 == target ✓ MATCH!
    
→ No need to continue, return [0, 1]
```

**Complexity:**
- **Time Complexity:** `O(n²)` — two nested loops
- **Space Complexity:** `O(1)` — no extra space needed

---

### Solution 2: Two Pointer (with Sorting)

**Approach:** 
1. Create array of (value, original_index) pairs
2. Sort by value
3. Use two pointers from both ends to find the pair

**Visual Diagram:**
```
nums = [3, 2, 4], target = 6

Step 1: Create pairs with original indices
        [(3,0), (2,1), (4,2)]

Step 2: Sort by value
        [(2,1), (3,0), (4,2)]
           ↑              ↑
          left          right

Step 3: Two pointer search
        
        Sorted values: [2, 3, 4]
                        ↑     ↑
                       L=0   R=2
        
        sum = 2 + 4 = 6 == target ✓
        
        Original indices: [1, 2]
```

**Step-by-step:**
```
sorted = [(2,1), (3,0), (4,2)]
left = 0, right = 2

Iteration 1:
  sum = sorted[0].val + sorted[2].val = 2 + 4 = 6
  sum == target ✓
  
return [sorted[0].idx, sorted[2].idx] = [1, 2]
```

**Complexity:**
- **Time Complexity:** `O(n log n)` — due to sorting
- **Space Complexity:** `O(n)` — storing pairs with indices

---

### Solution 3: Hash Map (Optimal) ✅

**Approach:** Use a hash map to store each number and its index. For each element, check if `target - current` exists in the map.

**Visual Diagram:**
```
nums = [2, 7, 11, 15], target = 9

                    HashMap
Index:  0    1    2    3      +-------+-------+
      +----+----+----+----+   | Value | Index |
nums: | 2  | 7  | 11 | 15 |   +-------+-------+
      +----+----+----+----+   |   2   |   0   |
        ↑                     +-------+-------+
        │
        └── For num=2: need 9-2=7
            7 not in map → store (2,0)

        ↑
        └── For num=7: need 9-7=2
            2 IS in map at index 0! ✓
            
return [0, 1]
```

**Step-by-step with Map State:**
```
nums = [2, 7, 11, 15], target = 9

┌─────────┬─────────┬──────────┬───────────────┬────────────┐
│  Step   │   num   │   need   │   Map State   │   Result   │
├─────────┼─────────┼──────────┼───────────────┼────────────┤
│    1    │    2    │  9-2=7   │    {2: 0}     │  Continue  │
│    2    │    7    │  9-7=2   │    {2: 0}     │  Found! ✓  │
└─────────┴─────────┴──────────┴───────────────┴────────────┘

→ 2 exists in map at index 0, current index is 1
→ return [0, 1]
```

**Another Example with Table:**
```
nums = [3, 2, 4], target = 6

┌─────────┬─────────┬──────────┬───────────────────┬────────────┐
│  Step   │   num   │   need   │    Map State      │   Result   │
├─────────┼─────────┼──────────┼───────────────────┼────────────┤
│    1    │    3    │  6-3=3   │     {3: 0}        │  Continue  │
│    2    │    2    │  6-2=4   │   {3: 0, 2: 1}    │  Continue  │
│    3    │    4    │  6-4=2   │   {3: 0, 2: 1}    │  Found! ✓  │
└─────────┴─────────┴──────────┴───────────────────┴────────────┘

→ 2 exists in map at index 1, current index is 2
→ return [1, 2]
```

**Complexity:**
- **Time Complexity:** `O(n)` — single pass through array
- **Space Complexity:** `O(n)` — storing up to n elements in the map

---

## Solution Comparison

| Solution | Time | Space | Notes |
|----------|------|-------|-------|
| Brute Force | O(n²) | O(1) | Simple but slow |
| Two Pointer | O(n log n) | O(n) | Needs sorting, loses original indices |
| **Hash Map** ✅ | **O(n)** | O(n) | **Optimal - single pass** |

---

## Why Hash Map Works

```
Key Insight: For each number x, we need target - x

Instead of:                    We do:
┌─────────────────────┐       ┌─────────────────────┐
│  For each element   │       │  For each element   │
│  Search entire array│       │  O(1) map lookup    │
│  Time: O(n²)        │       │  Time: O(n)         │
└─────────────────────┘       └─────────────────────┘
```

The hash map trades space for time, giving us `O(1)` lookups instead of `O(n)` searches.
