# Top K Frequent Elements

## Problem Link
[LeetCode - Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/description/)

---

## Problem Description

Given an integer array `nums` and an integer `k`, return the `k` most frequent elements. You may return the answer in any order.

---

## Examples

### Example 1:

| Input | Output |
|-------|--------|
| `nums = [1,1,1,2,2,3], k = 2` | `[1,2]` |

### Example 2:

| Input | Output |
|-------|--------|
| `nums = [1], k = 1` | `[1]` |

### Example 3:

| Input | Output |
|-------|--------|
| `nums = [1,2,1,2,1,2,3,1,3,2], k = 2` | `[1,2]` |

---

## Constraints

| Constraint | Range |
|------------|-------|
| `nums.length` | `1 <= nums.length <= 10⁵` |
| `nums[i]` | `-10⁴ <= nums[i] <= 10⁴` |
| `k` | `k` is in the range `[1, the number of unique elements in the array]` |

> It is guaranteed that the answer is unique.

**Follow up:** Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

---

## Solutions

### 1. Sorting

#### Intuition

To find the k most frequent elements, we first need to know how often each number appears. Once we count the frequencies, we can sort the unique numbers based on how many times they occur. After sorting, the numbers with the highest frequencies will naturally appear at the end of the list. By taking the last k entries, we get the k most frequent elements.

This approach is easy to reason about: **count the frequencies → sort by frequency → take the top k**.

#### Algorithm

1. Create a hash map to store the frequency of each number.
2. Build a list of `[frequency, number]` pairs from the map.
3. Sort this list in descending order based on frequency.
4. Create an empty result list.
5. Take the first k elements from the sorted list and append the numbers to the result.
6. Return the result list.

#### Code

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for (auto u : nums) {
            mp[u]++;
        }

        vector<pair<int, int>> v;
        for (auto u : mp) {
            v.push_back({u.second, u.first});
        }
        sort(v.rbegin(), v.rend());

        vector<int> res;
        for (int i = 0; i < k; ++i) {
            res.push_back(v[i].second);
        }
        return res;
    }
};
```

#### Complexity Analysis

| Complexity | Value |
|------------|-------|
| **Time** | O(n log n) |
| **Space** | O(n) |

---

### 2. Min-Heap

#### Intuition

After counting how often each number appears, we want to efficiently keep track of only the k most frequent elements. A min-heap is perfect for this because it always keeps the smallest element at the top. By pushing `(frequency, value)` pairs into the heap and removing the smallest whenever the heap grows beyond size k, we ensure that the heap always contains the top k most frequent elements. In the end, the heap holds exactly the k values with the highest frequencies.

#### Algorithm

1. Build a frequency map that counts how many times each number appears.
2. Create an empty min-heap.
3. For each number in the frequency map:
   - Push `(frequency, number)` into the heap.
   - If the heap size becomes greater than k, pop once to remove the smallest frequency.
4. After processing all numbers, the heap contains the k most frequent elements.
5. Pop all elements from the heap and collect their numbers into the result list.
6. Return the result.

#### Code

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for (auto u : nums) {
            mp[u]++;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        for (auto u : mp) {
            heap.push({u.second, u.first});
            if (heap.size() > k) {
                heap.pop();
            }
        }

        vector<int> res;
        for (int i = 0; i < k; i++) {
            res.push_back(heap.top().second);
            heap.pop();
        }
        return res;
    }
};
```

#### Complexity Analysis

| Complexity | Value |
|------------|-------|
| **Time** | O(n log k) |
| **Space** | O(n + k) |

> Where `n` is the length of the array and `k` is the number of top frequent elements.

---

### 3. Bucket Sort

#### Intuition

Each number in the array appears a certain number of times, and the maximum possible frequency is the length of the array. We can use this idea by creating a list where the index represents a frequency, and at each index we store all numbers that appear exactly that many times.

For example:
- All numbers that appear 1 time go into group `freq[1]`.
- All numbers that appear 2 times go into group `freq[2]`.
- And so on.

After we build these groups, we look from the highest possible frequency down to the lowest and collect numbers from these groups until we have k of them. This way, we directly jump to the most frequent numbers without sorting all the elements by frequency.

#### Algorithm

1. Build a frequency map that counts how many times each number appears.
2. Create a list of groups `freq`, where `freq[i]` will store all numbers that appear exactly `i` times.
3. For each number and its frequency in the map, add the number to `freq[frequency]`.
4. Initialize an empty result list.
5. Loop from the largest possible frequency down to 1:
   - For each number in `freq[i]`, add it to the result list.
   - Once the result contains k numbers, return it.

#### Code

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        vector<vector<int>> v(nums.size() + 1);
        for (auto u : nums) {
            mp[u]++;
        }
        for (auto u : mp) {
            v[u.second].push_back(u.first);
        }

        vector<int> ans;
        for (int i = v.size() - 1; i >= 0; i--) {
            for (auto u : v[i])
                ans.push_back(u);
            if (ans.size() == k) return ans;
        }
        return ans;
    }
};
```

#### Complexity Analysis

| Complexity | Value |
|------------|-------|
| **Time** | O(n) |
| **Space** | O(n) |

---

## Complexity Comparison

| Solution | Time Complexity | Space Complexity |
|----------|-----------------|------------------|
| **1. Sorting** | O(n log n) | O(n) |
| **2. Min-Heap** | O(n log k) | O(n + k) |
| **3. Bucket Sort** | O(n) | O(n) |  Yes |


