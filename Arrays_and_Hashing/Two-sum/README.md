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

#### Intuition
We can check every pair of different elements in the array and return the first pair that sums up to the target. This is the most intuitive approach but it's not the most efficient.

#### Algorithm
1. Iterate through the array with two nested loops to check every pair of different elements.
2. If the sum of the pair equals the target, return the indices of the pair.
3. If no such pair is found, return an empty array.
4. There is guaranteed to be exactly one solution, so we will never return an empty array.

#### Visual Example
```
nums = [2, 7, 11, 15], target = 9

Check all pairs:
  i=0, j=1: nums[0] + nums[1] = 2 + 7 = 9 ✓ Found!
  
return [0, 1]
```

#### Code
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
};
```

#### Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n²) | Two nested loops checking every pair |
| **Space** | O(1) | No extra space needed |

---

### Solution 2: Sorting

#### Intuition
We can sort the array and use two pointers to find the two numbers that sum up to the target. This is more efficient than the brute force approach. This approach is similar to the one used in Two Sum II.

#### Algorithm
1. Create a copy of the array and sort it in ascending order.
2. Initialize two pointers, one at the beginning and one at the end of the array.
3. Iterate through the array with the two pointers and check if the sum of the two numbers is equal to the target.
4. If the sum is equal to the target, return the indices of the two numbers.
5. If the sum is less than the target, move the left pointer to the right, which will increase the sum.
6. If the sum is greater than the target, move the right pointer to the left, which will decrease the sum.
7. There is guaranteed to be exactly one solution, so we will never return an empty array.

#### Visual Example
```
nums = [3, 2, 4], target = 6

Step 1: Create pairs with original indices
        [(3,0), (2,1), (4,2)]

Step 2: Sort by value
        [(2,1), (3,0), (4,2)]
           ↑              ↑
          left          right

Step 3: Two pointer search
        sum = 2 + 4 = 6 == target ✓
        
        Original indices: [1, 2]
```

#### Code
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int, int>> A;
        for (int i = 0; i < nums.size(); i++) {
            A.push_back({nums[i], i});
        }

        sort(A.begin(), A.end());

        int i = 0, j = nums.size() - 1;
        while (i < j) {
            int cur = A[i].first + A[j].first;
            if (cur == target) {
                return {min(A[i].second, A[j].second),
                        max(A[i].second, A[j].second)};
            } else if (cur < target) {
                i++;
            } else {
                j--;
            }
        }
        return {};
    }
};
```

#### Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n log n) | Dominated by sorting |
| **Space** | O(n) | Storing pairs with original indices |

---

### Solution 3: Hash Map (Two Pass)

#### Intuition
We can use a hash map to store the value and index of each element in the array. Then, we can iterate through the array and check if the complement of the current element exists in the hash map. The complement must be at a different index, because we can't use the same element twice.

By using a hashmap, we can achieve a time complexity of O(n) because the insertion and lookup time of a hashmap is O(1).

#### Algorithm
1. Create a hash map to store the value and index of each element in the array.
2. Iterate through the array and compute the complement of the current element, which is `target - nums[i]`.
3. Check if the complement exists in the hash map.
4. If it does, return the indices of the current element and its complement.
5. If no such pair is found, return an empty array.

#### Visual Example
```
nums = [2, 7, 11, 15], target = 9

Pass 1: Build map
  Map: {2: 0, 7: 1, 11: 2, 15: 3}

Pass 2: Find complement
  i=0: need 9-2=7, found at index 1 ✓
  
return [0, 1]
```

#### Code
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indices;  // val -> index

        for (int i = 0; i < nums.size(); i++) {
            indices[nums[i]] = i;
        }

        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums[i];
            if (indices.count(diff) && indices[diff] != i) {
                return {i, indices[diff]};
            }
        }

        return {};
    }
};
```

#### Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n) | Two passes through the array |
| **Space** | O(n) | Storing n elements in the hash map |

---

### Solution 4: Hash Map (One Pass) ✅

#### Intuition
We can solve the problem in a single pass by iterating through the array and checking if the complement of the current element exists in the hash map.

If it does, we return the indices of the current element and its complement. If not, we store the current element in the hash map. This guarantees that we will never use the same element twice, but we still check every element in the array.

#### Algorithm
1. Create a hash map to store the value and index of each element in the array.
2. Iterate through the array and compute the complement of the current element, which is `target - nums[i]`.
3. Check if the complement exists in the hash map.
4. If it does, return the indices of the current element and its complement.
5. If no such pair is found, return an empty array.

#### Visual Example
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

#### Another Example
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

#### Code
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int, int> prevMap;

        for (int i = 0; i < n; i++) {
            int diff = target - nums[i];
            if (prevMap.find(diff) != prevMap.end()) {
                return {prevMap[diff], i};
            }
            prevMap.insert({nums[i], i});
        }
        return {};
    }
};
```

#### Complexity Analysis

| Metric | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n) | Single pass through the array |
| **Space** | O(n) | Storing up to n elements in the hash map |

---

## Summary Comparison

| Solution | Time Complexity | Space Complexity | Notes |
|----------|-----------------|------------------|-------|
| **Brute Force** | O(n²) | O(1) | Simple but slow |
| **Sorting** | O(n log n) | O(n) | Uses two pointers |
| **Hash Map (Two Pass)** | O(n) | O(n) | Build map first, then search |
| **Hash Map (One Pass)** ✅ | O(n) | O(n) | Optimal - single pass |

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
