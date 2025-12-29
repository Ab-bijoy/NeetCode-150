class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> freq; 
        for(auto u : nums) {
            if(freq.count(u)) {
                return true; 
            }
            freq.insert(u);
        }
        
        return false;
    }
};
