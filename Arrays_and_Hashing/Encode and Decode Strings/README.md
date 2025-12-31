# Encode and Decode Strings

🔗 **Problem Link:** [NeetCode - String Encode and Decode](https://neetcode.io/problems/string-encode-and-decode/question?list=neetcode150)

---

## Problem Description

Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

**Machine 1 (sender)** has the function:
```cpp
string encode(vector<string> strs) {
    // ... your code
    return encoded_string;
}
```

**Machine 2 (receiver)** has the function:
```cpp
vector<string> decode(string s) {
    //... your code
    return strs;
}
```

So Machine 1 does:
```cpp
string encoded_string = encode(strs);
```

And Machine 2 does:
```cpp
vector<string> strs2 = decode(encoded_string);
```

`strs2` in Machine 2 should be the same as `strs` in Machine 1.

Implement the `encode` and `decode` methods.

---

## Examples

### Example 1:
| Input | Output |
|-------|--------|
| `["Hello","World"]` | `["Hello","World"]` |

**Explanation:**
```
Machine 1:
Codec encoder = new Codec();
String msg = encoder.encode(strs);
Machine 1 ---msg---> Machine 2

Machine 2:
Codec decoder = new Codec();
String[] strs = decoder.decode(msg);
```

### Example 2:
| Input | Output |
|-------|--------|
| `[""]` | `[""]` |

---

## Constraints

- `0 <= strs.length < 100`
- `0 <= strs[i].length < 200`
- `strs[i]` contains any possible characters out of 256 valid ASCII characters.

---

## Solution 1: Encoding & Decoding (Length Prefix with Separator)

### Intuition
To encode a list of strings into a single string, we need a way to store each string so that we can later separate them correctly during decoding.

A simple and reliable strategy is to record the length of each string first, followed by a special separator, and then append all the strings together. During decoding, we can read the recorded lengths to know exactly how many characters to extract for each original string.

This avoids any issues with special characters, commas, or symbols inside the strings because the lengths tell us precisely where each string starts and ends.

### Algorithm

**Encoding:**
1. If the input list is empty, return an empty string.
2. Create an empty list to store the sizes of each string.
3. For each string, append its length to the sizes list.
4. Build a single string by:
   - Writing all sizes separated by commas.
   - Adding a `#` to mark the end of the size section.
   - Appending all the actual strings in order.
5. Return the final encoded string.

**Decoding:**
1. If the encoded string is empty, return an empty list.
2. Read characters from the start until reaching `#` to extract all recorded sizes:
   - Parse each size by reading until a comma.
3. After the `#`, extract substrings according to the sizes list:
   - For each size, read that many characters and append the substring to the result.
4. Return the list of decoded strings.

### Code

**C++:**
```cpp
class Solution {
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
```



### Complexity Analysis

| Complexity | Value |
|------------|-------|
| **Time** | O(m) for each `encode()` and `decode()` call |
| **Space** | O(m + n) for each `encode()` and `decode()` call |

Where `m` is the sum of lengths of all strings and `n` is the number of strings.

---

## Solution 2: Encoding & Decoding (Optimal - Inline Length Prefix)

### Intuition
Instead of storing all string lengths first and then appending the strings, we can directly attach each string to its length.

For every string, we write `length#string`. The `#` character acts as a clear boundary between the length and the actual content, and using the length ensures we know exactly how many characters to read—no matter what characters appear in the string itself.

During decoding, we simply read characters until we reach `#` to find the length, then extract exactly that many characters as the string.

This approach is both simpler and more efficient because it avoids building separate sections for lengths and content.

### Algorithm

**Encoding:**
1. Initialize an empty result string.
2. For each string in the list:
   - Compute its length.
   - Append `"length#string"` to the result.
3. Return the final encoded string.

**Decoding:**
1. Initialize an empty list for the decoded strings and a pointer `i = 0`.
2. While `i` is within the bounds of the encoded string:
   - Move a pointer `j` forward until it finds `#` — this segment represents the length.
   - Convert the substring `s[i:j]` into an integer length.
   - Move `i` to the character right after `#`.
   - Extract the next `length` characters — this is the original string.
   - Append the extracted string to the result list.
   - Move `i` forward by `length` to continue decoding the next segment.
3. Return the list of decoded strings.

### Code

**C++:**
```cpp
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
```


### Complexity Analysis

| Complexity | Value |
|------------|-------|
| **Time** | O(m) for each `encode()` and `decode()` call |
| **Space** | O(m + n) for each `encode()` and `decode()` call |

Where `m` is the sum of lengths of all strings and `n` is the number of strings.

---

## Complexity Comparison

| Aspect | Solution 1 (Length Prefix with Separator) | Solution 2 (Optimal - Inline Prefix) |
|--------|-------------------------------------------|--------------------------------------|
| **Time Complexity** | O(m) | O(m) |
| **Space Complexity** | O(m + n) | O(m + n) |
| **Encoding Format** | `len1,len2,...,lenN#str1str2...strN` | `len1#str1len2#str2...lenN#strN` |
| **Implementation** | Two-pass (collect lengths, then strings) | Single-pass (length + string together) |


> **Note:** Both solutions have the same asymptotic complexity. However, **Solution 2 is preferred** because:
> - It uses a single-pass approach
> - The code is cleaner and easier to understand
> - Each string is self-contained with its length prefix
