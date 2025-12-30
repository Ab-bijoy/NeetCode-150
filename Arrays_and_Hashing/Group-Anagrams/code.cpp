/*
+--------------------------------------------------+
|            Solution 1: Sorting                   |
+--------------------------------------------------+
| Time Complexity : O(m * n log n)                 |
| Space Complexity: O(m * n)                       |
|                                                  |
| m = number of strings, n = longest string length |
+--------------------------------------------------+
*/
class Solution1 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (auto u : strs) {
            string sorted_S = u;
            sort(sorted_S.begin(), sorted_S.end());
            mp[sorted_S].push_back(u);
        }
        vector<vector<string>> res;
        for (auto u : mp) {
            res.push_back(u.second);
        }
        return res;
    }
};

/*
+--------------------------------------------------+
|   Solution 2: Hash Table (Character Frequency)   |
+--------------------------------------------------+
| Time Complexity : O(m * n)                       |
| Space Complexity: O(m) extra, O(m * n) output    |
|                                                  |
| m = number of strings, n = longest string length |
+--------------------------------------------------+
*/
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (auto u : strs) {
            vector<int> frq(26, 0);
            for (auto c : u) {
                frq[c - 'a']++;
            }
            string key = to_string(frq[0]);
            for (int i = 1; i < 26; ++i) {
                key += ',' + to_string(frq[i]);
            }
            mp[key].push_back(u);
        }
        vector<vector<string>> res;
        for (auto u : mp) {
            res.push_back(u.second);
        }
        return res;
    }

};