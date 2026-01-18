#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// Solution 1: Brute Force
// Time Complexity: O(n²)
// Space Complexity: O(1) extra space, O(n) for output array
// ============================================================================
class Solution1 {
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

// ============================================================================
// Solution 2: Division
// Time Complexity: O(n)
// Space Complexity: O(1) extra space, O(n) for output array
// Note: This approach doesn't satisfy the problem constraint of not using division
// ============================================================================
class Solution2 {
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

// ============================================================================
// Solution 3: Prefix & Suffix
// Time Complexity: O(n)
// Space Complexity: O(n)
// ============================================================================
class Solution3 {
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

// ============================================================================
// Solution 4: Prefix & Suffix (Optimal) 
// Time Complexity: O(n)
// Space Complexity: O(1) extra space, O(n) for output array
// ============================================================================
class Solution4 {
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

// Use Solution4 as the main solution (rename to Solution for LeetCode submission)
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
