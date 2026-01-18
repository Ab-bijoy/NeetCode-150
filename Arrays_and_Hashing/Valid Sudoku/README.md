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

**Intuition:** A valid Sudoku board must follow three rules:
- Each row can contain digits 1–9 at most once
- Each column can contain digits 1–9 at most once  
- Each 3×3 box can contain digits 1–9 at most once

We directly check all these conditions one by one. For every row, column, and 3×3 box, we keep a set of seen digits and ensure no number appears twice.

**Algorithm:**

1. **Check all rows:**
   - For each row (0 to 8), create an empty set `seen`
   - Iterate through each cell in the row
   - Skip if cell is `'.'`
   - If value already in `seen` → return `false`
   - Otherwise, add value to `seen`

2. **Check all columns:**
   - For each column (0 to 8), create an empty set `seen`
   - Iterate through each cell in the column
   - Same duplicate detection logic as rows

3. **Check all 3×3 boxes:**
   - Number the boxes 0-8 (left to right, top to bottom)
   - For each box, iterate through its 9 cells using:
     - `row = (square / 3) * 3 + i`
     - `col = (square % 3) * 3 + j`
   - Same duplicate detection logic

**Dry Run Example (Box Calculation):**
```
Box 0: square=0 → rows 0-2, cols 0-2
Box 4: square=4 → rows 3-5, cols 3-5 (center box)
Box 8: square=8 → rows 6-8, cols 6-8
```

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
| Time | O(n²) - We iterate through 81 cells three times |
| Space | O(n) - Set stores at most 9 elements at a time |

---

### 2. Hash Set (One Pass)

**Intuition:** Instead of checking rows, columns, and boxes separately (3 passes), we can validate everything in **one single pass** through the board.

For each cell, we simultaneously check if the digit has already appeared in:
- The same **row**
- The same **column**  
- The same **3×3 box**

We maintain three data structures:
- `rows[r]` → set of digits seen in row `r`
- `cols[c]` → set of digits seen in column `c`
- `squares[(r/3, c/3)]` → set of digits seen in the corresponding box

**Algorithm:**

1. Create three hash maps of sets for rows, columns, and squares
2. Loop through every cell `(r, c)`:
   - Skip if cell is `'.'`
   - Calculate box key as `(r/3, c/3)`
   - If digit exists in `rows[r]` OR `cols[c]` OR `squares[key]` → return `false`
   - Add digit to all three sets
3. Return `true` if no duplicates found

**Dry Run Example:**
```
Processing cell (0,0) with value '5':
  - rows[0] = {} → add '5' → {5}
  - cols[0] = {} → add '5' → {5}
  - squares[(0,0)] = {} → add '5' → {5}

Processing cell (0,1) with value '3':
  - rows[0] = {5} → add '3' → {5,3}
  - cols[1] = {} → add '3' → {3}
  - squares[(0,0)] = {5} → add '3' → {5,3}

If we encounter '5' again at (0,4):
  - rows[0] = {5,3,...} → '5' EXISTS! → return false
```

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
| Time | O(n²) - Single pass through 81 cells |
| Space | O(n²) - Store up to 81 entries across all maps |

---

### 3. Bitmask (Optimal)

**Intuition:** Instead of hash sets, we can use **integers as bitmasks** where each bit represents whether a digit (1-9) has been seen.

```
Digit 1 → bit 0 → mask = 0000 0001 (1)
Digit 2 → bit 1 → mask = 0000 0010 (2)
Digit 3 → bit 2 → mask = 0000 0100 (4)
...
Digit 9 → bit 8 → mask = 1 0000 0000 (256)
```

**Why is this efficient?**
- Checking if a digit exists: `rows[r] & mask` (bitwise AND)
- Adding a digit: `rows[r] |= mask` (bitwise OR)
- Both operations are O(1) and use less memory than hash sets

**Algorithm:**

1. Create three arrays of integers (size 9 each): `rows`, `cols`, `squares`
2. For each cell `(r, c)`:
   - Skip if `'.'`
   - Calculate: `val = board[r][c] - '1'` (converts '1'-'9' to 0-8)
   - Calculate: `mask = 1 << val` (creates bit position)
   - Calculate: `boxIdx = (r/3)*3 + (c/3)` (box index 0-8)
   - If `(rows[r] & mask)` OR `(cols[c] & mask)` OR `(squares[boxIdx] & mask)` → duplicate found, return `false`
   - Set bits: `rows[r] |= mask`, `cols[c] |= mask`, `squares[boxIdx] |= mask`
3. Return `true`

**Dry Run Example:**
```
Processing '5' at (0,0):
  val = '5' - '1' = 4
  mask = 1 << 4 = 0001 0000 (16)
  boxIdx = (0/3)*3 + (0/3) = 0
  
  rows[0] = 0000 0000 → (rows[0] & mask) = 0 (no duplicate)
  rows[0] |= mask → rows[0] = 0001 0000

Processing '5' again at (3,0):
  val = 4, mask = 0001 0000
  cols[0] = 0001 0000 (from earlier)
  (cols[0] & mask) = 0001 0000 ≠ 0 → DUPLICATE! return false
```

**Box Index Mapping:**
```
┌───┬───┬───┐
│ 0 │ 1 │ 2 │  (r/3)*3 + (c/3)
├───┼───┼───┤
│ 3 │ 4 │ 5 │  Example: (4,7) → (1)*3 + (2) = 5
├───┼───┼───┤
│ 6 │ 7 │ 8 │
└───┴───┴───┘
```

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
| Time | O(n²) - Single pass through 81 cells |
| Space | O(n) - Only 27 integers (3 arrays × 9) |

---

## Approach Comparison

| Approach | Time | Space | Passes | Key Insight |
|----------|------|-------|--------|-------------|
| Brute Force | O(n²) | O(n) | 3 | Simple, check each constraint separately |
| Hash Set | O(n²) | O(n²) | 1 | Track all constraints simultaneously |
| Bitmask | O(n²) | O(n) | 1 | Use bits instead of sets for efficiency |

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
