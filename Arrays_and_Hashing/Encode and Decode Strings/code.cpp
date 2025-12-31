class Solution {
public:
    string encode(vector<string>& strs) {
        string encoded = "";
        for (string& s : strs) {
            encoded += to_string(s.length()) + "#" + s;
        }
        return encoded;
    }
    vector<string> decode(string s) {
        vector<string> res;
        int i = 0;
        
        while (i < s.length()) {
            int j = i;
            while (s[j] != '#') {
                j++;
            }
            int len = stoi(s.substr(i, j - i));
            string str = s.substr(j + 1, len);
            res.push_back(str);
            i = j + 1 + len;
        }
        
        return res;
    }
};