/*
╔═══════════════════════════════════════════════════════════════╗
║  Solution 1: Length Prefix with Separator                     ║
║  Format: len1,len2,...,lenN#str1str2...strN                   ║
║  Time: O(m)          Space: O(m + n)                          ║
╚═══════════════════════════════════════════════════════════════╝
*/
class Solution1 {
public:
    string encode(vector<string>& strs) {
        if (strs.empty()) return "";
        vector<int> sizes;
        string res = "";
        for (string& s : strs) {
            sizes.push_back(s.size());
        }
        for (int sz : sizes) {
            res += to_string(sz) + ',';
        }
        res += '#';
        for (string& s : strs) {
            res += s;
        }
        return res;
    }

    vector<string> decode(string s) {
        if (s.empty()) return {};
        vector<int> sizes;
        vector<string> res;
        int i = 0;
        while (s[i] != '#') {
            string cur = "";
            while (s[i] != ',') {
                cur += s[i];
                i++;
            }
            sizes.push_back(stoi(cur));
            i++;
        }
        i++;
        for (int sz : sizes) {
            res.push_back(s.substr(i, sz));
            i += sz;
        }
        return res;
    }
};

/*
╔═══════════════════════════════════════════════════════════════╗
║  Solution 2: Optimal - Inline Length Prefix                   ║
║  Format: len1#str1len2#str2...lenN#strN                       ║
║  Time: O(m)          Space: O(m + n)                          ║
╚═══════════════════════════════════════════════════════════════╝
*/
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