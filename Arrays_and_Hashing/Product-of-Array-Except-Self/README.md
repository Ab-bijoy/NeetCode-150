# Product of Array Except Self

[LeetCode Problem Link](https://leetcode.com/problems/product-of-array-except-self/description/)

## Problem Description

Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of `nums` except `nums[i]`.

The product of any prefix or suffix of `nums` is guaranteed to fit in a 32-bit integer.

**You must write an algorithm that runs in O(n) time and without using the division operation.**

### Examples

**Example 1:**
```
Input: nums = [1,2,3,4]
Output: [24,12,8,6]
```

**Example 2:**
```
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
```

### Constraints

- `2 <= nums.length <= 10^5`
- `-30 <= nums[i] <= 30`
- The input is generated such that `answer[i]` is guaranteed to fit in a 32-bit integer.

### Follow up
Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)

---

## Solutions

### 1. Brute Force

#### Intuition
For each position in the array, we can compute the product of all other elements by multiplying every value except the one at the current index.

This directly follows the problem statement and is the most straightforward approach: for each index, multiply all elements except itself.

Although simple, this method is inefficient because it repeats a full pass through the array for every element.

#### Algorithm
1. Let `n` be the length of the input array and create a result array `ans_main` of size `n`.
2. For each index `i` from `0` to `n - 1`:
   - Initialize a running product `ans = 1`.
   - Loop through all indices `j` from `0` to `n - 1`:
     - If `j` is not equal to `i`, multiply `ans` by `nums[j]`.
   - Store `ans` in `ans_main[i]`.
3. After all indices are processed, return `ans_main`.

#### Code

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans_main(n);

        for (int i = 0; i < n; i++) {
            int ans = 1;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    ans *= nums[j];
                }
            }
            ans_main[i] = ans;
        }
        return ans_main;
    }
};
```

#### Complexity Analysis
- **Time complexity:** O(n²)
- **Space complexity:** O(1) extra space, O(n) for the output array.

---

### 2. Division

#### Intuition
This approach works by using a simple idea: If we know the product of all non-zero numbers, we can easily compute the answer for each position using division — as long as there are no division-by-zero issues.

So we first check how many zeros the array has:
- If there are **two or more zeros**, then every product will include at least one zero → the entire result is all zeros.
- If there is **exactly one zero**, then only the position containing that zero will get the product of all non-zero numbers. All other positions become 0.
- If there are **no zeros**, we can safely do: `ans_main[i] = ans / nums[i]`

#### Algorithm
1. Traverse the array once:
   - Multiply all non-zero numbers to get the `ans`.
   - Count how many zeros appear (`zero_cnt`).
2. If the `zero_cnt` is greater than 1:
   - Return an array of all zeros.
3. Create a result array `ans_main` of size `n`.
4. Loop through the numbers again:
   - If there is one zero:
     - The index with zero gets the `ans` of all non-zero numbers.
     - All other positions get 0.
   - If there are no zeros:
     - Set each result value to `ans / nums[i]`.
5. Return the result array `ans_main`.

#### Code

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        int ans = 1, zero_cnt = 0;
        
        for (int i = 0; i < n; i++) {
            if (nums[i] != 0) {
                ans *= nums[i];
            } else {
                zero_cnt++;
            }
        }
        
        if (zero_cnt > 1) {
            return vector<int>(n, 0);
        }

        vector<int> ans_main(n, 0);
        for (int i = 0; i < n; i++) {
            if (zero_cnt) {
                ans_main[i] = (nums[i] == 0) ? ans : 0;
            } else {
                ans_main[i] = ans / nums[i];
            }
        }
        return ans_main;
    }
};
```

#### Complexity Analysis
- **Time complexity:** O(n)
- **Space complexity:** O(1) extra space, O(n) for the output array.

---

### 3. Prefix & Suffix

#### Intuition
For each index, we need the product of all elements before it and all elements after it. Instead of recomputing the product repeatedly, we can pre-compute two helpful arrays:

- **Prefix product:** `pre[i]` = product of all elements to the left of `i`
- **Suffix product:** `post[i]` = product of all elements to the right of `i`

Then, the final answer for each index is simply:
```
ans_main[i] = pre[i] × post[i]
```

This works because:
- The `pre` handles everything before the index
- The `post` handles everything after the index
- Both pieces together form the product of all numbers except the one at that position.

#### Algorithm
1. Create two arrays:
   - `pre` for prefix products
   - `post` for suffix products
2. Initialize `ans = 1` and push it to `pre` (nothing to the left of index 0).
3. Build the prefix product array:
   - For each `i` from `1` to `n - 1`:
     - Multiply `ans` by `nums[i - 1]`
     - Push `ans` to `pre`
4. Reset `ans = 1` and push it to `post` (nothing to the right of last index).
5. Build the suffix product array (in reverse):
   - For each `i` from `n - 2` down to `0`:
     - Multiply `ans` by `nums[i + 1]`
     - Push `ans` to `post`
6. Reverse the `post` array to align indices correctly.
7. Build the result:
   - For each index `i`, compute: `ans_main[i] = pre[i] × post[i]`
8. Return the result array `ans_main`.

#### Code

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {

        vector<int>pre;
        vector<int>post;

        int ans = 1;
        pre.push_back(ans);
        for(int i = 1; i < nums.size(); i++)
        {
            ans *= nums[i-1];
            pre.push_back(ans);
        }
        ans = 1;
        post.push_back(ans);
        for(int i = nums.size() - 2; i >= 0; i--)
        {
            ans *= nums[i+1];
            post.push_back(ans);
        }

        reverse(post.begin(), post.end());
        
        vector<int>ans_main(nums.size());
        
        for(int i = 0; i < nums.size(); i++)
        {
            ans_main[i] = (pre[i] * post[i]);
        }

        return ans_main;
    }
};
```

#### Complexity Analysis
- **Time complexity:** O(n)
- **Space complexity:** O(n)

---

### 4. Prefix & Suffix (Optimal) ⭐

#### Intuition
We can compute the product of all elements except the current one without using extra prefix and suffix arrays. Instead, we reuse the result array and build the answer in two simple passes:

1. In the **first pass**, we fill `ans_main[i]` with the product of all elements to the left of `i` (prefix product).
2. In the **second pass**, we multiply each `ans_main[i]` with the product of all elements to the right of `i` (postfix product).

By maintaining two running values — `pre` and `post` — we avoid the need for separate prefix and suffix arrays. This gives us the same logic as the previous method, but with **O(1) extra space**.

#### Algorithm
1. Initialize the result array `ans_main` with all values set to `1`.
2. Create a variable `ans = 1` for tracking prefix product.
3. **First pass (left to right):**
   - For each index `i`:
     - Set `ans_main[i] = ans` (product of all elements to the left).
     - Update `ans *= nums[i]`.
4. Reset `ans = 1` for tracking postfix product.
5. **Second pass (right to left):**
   - For each index `i`:
     - Multiply `ans_main[i]` by `ans` (product of all elements to the right).
     - Update `ans *= nums[i]`.
6. Return the result array `ans_main`.

#### Code

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans_main(n, 1);

        int ans = 1;
        for (int i = 1; i < n; i++) {
            ans *= nums[i - 1];
            ans_main[i] = ans;
        }

        ans = 1;
        for (int i = n - 1; i >= 0; i--) {
            ans_main[i] *= ans;
            ans *= nums[i];
        }
        return ans_main;
    }
};
```

#### Complexity Analysis
- **Time complexity:** O(n)
- **Space complexity:** O(1) extra space, O(n) for the output array.

---

## Common Pitfalls

### Using Division Without Handling Zeros
The division approach (`ans / nums[i]`) fails when the array contains zeros. Dividing by zero causes runtime errors, and having multiple zeros requires special handling. Always count zeros first: with two or more zeros, the entire result is zeros; with exactly one zero, only the zero's position gets the product of other elements.

### Off-by-One Errors in Prefix/Suffix Array Construction
When building prefix products, `pre[i]` should contain the product of elements **before** index `i`, not including `nums[i]`. A common mistake is including `nums[i]` in the prefix, which double-counts the element. The same applies to suffix arrays: `post[i]` should exclude `nums[i]`.

### Integer Overflow with Large Products
When the array contains many large numbers, the product can overflow 32-bit integers. In languages with fixed-size integers, consider using `long` or `BigInteger`. The problem constraints usually prevent overflow, but edge cases with many elements near the maximum value should be tested.
