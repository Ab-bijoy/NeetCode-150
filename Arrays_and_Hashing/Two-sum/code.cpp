// ============================================
// Two Sum - All Solutions
// ============================================

#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// ============================================
// Solution 1: Brute Force
// Time: O(n²) | Space: O(1)
// ============================================
class Solution1_BruteForce {
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

// ============================================
// Solution 2: Sorting + Two Pointers
// Time: O(n log n) | Space: O(n)
// ============================================
class Solution2_Sorting {
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

// ============================================
// Solution 3: Hash Map (Two Pass)
// Time: O(n) | Space: O(n)
// ============================================
class Solution3_HashMapTwoPass {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;  // val -> index

        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]] = i;
        }

        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums[i];
            if (mp.count(diff) && mp[diff] != i) {
                return {i, mp[diff]};
            }
        }

        return {};
    }
};

// ============================================
// Solution 4: Hash Map (One Pass) - Optimal
// Time: O(n) | Space: O(n)
// ============================================
class Solution4_HashMapOnePass {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int, int> mp;

        for (int i = 0; i < n; i++) {
            int diff = target - nums[i];
            if (mp.find(diff) != mp.end()) {
                return {mp[diff], i};
            }
            mp.insert({nums[i], i});
        }
        return {};
    }
};

// ============================================
// Default Solution (for LeetCode submission)
// ============================================
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        
        for(int i = 0; i < nums.size(); i++) {
            int need = target - nums[i];
            auto it = mp.find(need);
            if(it != mp.end()) {
                return {it->second, i};
            }
            mp[nums[i]] = i;  
        }

        return {};  
    } 
};