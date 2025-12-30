// ============================================
// Contains Duplicate - All Solutions
// ============================================

#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

// ============================================
// Solution 1: Brute Force
// Time: O(n²) | Space: O(1)
// ============================================
class Solution1_BruteForce {
public:
    bool containsDuplicate(vector<int>& nums) {
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

// ============================================
// Solution 2: Sorting
// Time: O(n log n) | Space: O(1) or O(n)
// ============================================
class Solution2_Sorting {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                return true;
            }
        }
        return false;
    }
};

// ============================================
// Solution 3: Hash Set (Optimal)
// Time: O(n) | Space: O(n)
// ============================================
class Solution3_HashSet {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> freq;
        for (int num : nums) {
            if (freq.count(num)) {
                return true;
            }
            freq.insert(num);
        }
        return false;
    }
};

// ============================================
// Solution 4: Hash Set Length
// Time: O(n) | Space: O(n)
// ============================================
class Solution4_HashSetLength {
public:
    bool containsDuplicate(vector<int>& nums) {
        return unordered_set<int>(nums.begin(), nums.end()).size() < nums.size();
    }
};

// ============================================
// Default Solution (for LeetCode submission)
// ============================================
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> freq;
        for (int num : nums) {
            if (freq.count(num)) {
                return true;
            }
            freq.insert(num);
        }
        return false;
    }
};
