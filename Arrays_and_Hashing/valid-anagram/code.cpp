class Solution {
public:
    bool isAnagram(string s, string t) {

        if(s.size()==t.size())
        {
            unordered_map<char,int>freq ;
            for(auto u : s)
            {
                freq[u]++;
            }
            for(auto u : t)
            {
                freq[u]--;
            }
            for(auto u : freq)
            {
                if(u.second!=0)
                {
                    return false;
                }
            }
            return true;

        }
        else return false;

        
        
        
    }
};