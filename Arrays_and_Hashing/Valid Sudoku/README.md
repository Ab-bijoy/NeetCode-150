# Valid Sudoku

[LeetCode Problem Link](https://leetcode.com/problems/valid-sudoku/description/)

## Problem Description

Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

1. Each row must contain the digits 1-9 without repetition.
2. Each column must contain the digits 1-9 without repetition.
3. Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

> [!NOTE]
> - A Sudoku board (partially filled) could be valid but is not necessarily solvable.
> - Only the filled cells need to be validated according to the mentioned rules.

## Examples

### Example 1
```
Input: board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true
```

### Example 2
```
Input: board = 
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: false
Explanation: Two 8's in the top left 3x3 sub-box makes it invalid.
```

## Constraints

- `board.length == 9`
- `board[i].length == 9`
- `board[i][j]` is a digit `1-9` or `'.'`

---

## Solution Approaches

### 1. Brute Force

**Intuition:** Directly check all three Sudoku rules separately - validate each row, each column, and each 3×3 box using a set to detect duplicates.

```cpp
bool isValidSudoku(vector<vector<char>>& board) {
    // Check rows
    for (int row = 0; row < 9; row++) {
        unordered_set<char> seen;
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == '.') continue;
            if (seen.count(board[row][i])) return false;
            seen.insert(board[row][i]);
        }
    }
    
    // Check columns
    for (int col = 0; col < 9; col++) {
        unordered_set<char> seen;
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == '.') continue;
            if (seen.count(board[i][col])) return false;
            seen.insert(board[i][col]);
        }
    }
    
    // Check 3x3 boxes
    for (int square = 0; square < 9; square++) {
        unordered_set<char> seen;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int row = (square / 3) * 3 + i;
                int col = (square % 3) * 3 + j;
                if (board[row][col] == '.') continue;
                if (seen.count(board[row][col])) return false;
                seen.insert(board[row][col]);
            }
        }
    }
    return true;
}
```

| Complexity | Value |
|------------|-------|
| Time | O(n²) |
| Space | O(n) |

---

### 2. Hash Set (One Pass)

**Intuition:** Validate the entire board in one pass by tracking seen digits for each row, column, and 3×3 box simultaneously using three hash maps.

```cpp
bool isValidSudoku(vector<vector<char>>& board) {
    unordered_map<int, unordered_set<char>> rows, cols;
    map<pair<int, int>, unordered_set<char>> squares;

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == '.') continue;
            
            pair<int, int> squareKey = {r / 3, c / 3};
            
            if (rows[r].count(board[r][c]) || 
                cols[c].count(board[r][c]) || 
                squares[squareKey].count(board[r][c])) {
                return false;
            }
            
            rows[r].insert(board[r][c]);
            cols[c].insert(board[r][c]);
            squares[squareKey].insert(board[r][c]);
        }
    }
    return true;
}
```

| Complexity | Value |
|------------|-------|
| Time | O(n²) |
| Space | O(n²) |

---

### 3. Bitmask (Optimal)

**Intuition:** Use integers as bitmasks where each bit represents a digit (1-9). This is more memory efficient than hash sets.

```cpp
bool isValidSudoku(vector<vector<char>>& board) {
    int rows[9] = {0};
    int cols[9] = {0};
    int squares[9] = {0};

    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (board[r][c] == '.') continue;
            
            int val = board[r][c] - '1';
            int mask = 1 << val;
            int boxIdx = (r / 3) * 3 + (c / 3);
            
            if ((rows[r] & mask) || (cols[c] & mask) || (squares[boxIdx] & mask)) {
                return false;
            }
            
            rows[r] |= mask;
            cols[c] |= mask;
            squares[boxIdx] |= mask;
        }
    }
    return true;
}
```

| Complexity | Value |
|------------|-------|
| Time | O(n²) |
| Space | O(n) |

---

## Common Pitfalls

> [!WARNING]
> **Wrong Box Index Calculation**
> ```cpp
> // ❌ Wrong: doesn't uniquely identify boxes
> int boxIdx = r / 3 + c / 3;  // Box (0,1) and (1,0) both give 1
> 
> // ✅ Correct: unique box index 0-8
> int boxIdx = (r / 3) * 3 + c / 3;
> ```

> [!CAUTION]
> **Not Skipping Empty Cells**
> 
> Empty cells represented by `'.'` must be skipped. Forgetting this check causes errors or incorrect duplicate detection.

> [!IMPORTANT]
> **Validity vs Solvability**
> 
> This problem only checks if the current board state is valid, not whether the puzzle is solvable. A board with no duplicates is valid even if impossible to complete.
