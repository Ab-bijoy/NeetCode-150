/*
+--------------------------------------------------+
|              Solution 1: Sorting                 |
+--------------------------------------------------+
| Time Complexity : O(n log n)                     |
| Space Complexity: O(n)                           |
|                                                  |
| n = length of the array                          |
+--------------------------------------------------+
*/
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

/*
+--------------------------------------------------+
|              Solution 2: Min-Heap                |
+--------------------------------------------------+
| Time Complexity : O(n log k)                     |
| Space Complexity: O(n + k)                       |
|                                                  |
| n = length of the array, k = top frequent count  |
+--------------------------------------------------+
*/
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

/*
+--------------------------------------------------+
|            Solution 3: Bucket Sort               |
+--------------------------------------------------+
| Time Complexity : O(n)                           |
| Space Complexity: O(n)                           |
|                                                  |
| n = length of the array                          |
+--------------------------------------------------+
*/
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