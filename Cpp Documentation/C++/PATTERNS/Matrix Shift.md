
## Diagonal - recursive

```cpp
void shift_matrix_diagonal_recursive(std::vector<std::vector<int>> &grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    std::vector<std::vector<int>> temp(numRows, std::vector<int>(numCols, 0));

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            int new_i = (i + 1) % numRows;
            int new_j = (j + 1) % numCols;
            temp[new_i][new_j] = grid[i][j];
        }
    }
    grid = temp;
}
```

## Diagonal - decaying

```cpp
void shift_matrix_diagonal_decaying(std::vector<std::vector<int>> &grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Shift each row down by one and each column to the right by one
    for (int i = numRows - 1; i >= 1; --i) {
        for (int j = numCols - 1; j >= 1; --j) {
            grid[i][j] = grid[i - 1][j - 1];
        }
    }

    // Clear the first row and first column
    for (int i = 0; i < numRows; ++i) {
        grid[i][0] = 0;
    }
    for (int j = 0; j < numCols; ++j) {
        grid[0][j] = 0;
    }
}
```

## Shift Right

```cpp
void shift_matrix_right(std::vector<std::vector<int>> &grid) {
    int size = grid.size();
    for (int i = 0; i < size; ++i) {
        int temp = grid[i][size - 1];
        for (int j = size - 1; j > 0; --j) {
            grid[i][j] = grid[i][j - 1];
        }
        grid[i][0] = temp;
    }
}
```

## Shift Down

```cpp
void shift_matrix_down(std::vector<std::vector<int>> &matrix) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    // Save the last row
    std::vector<int> lastRow = matrix[numRows - 1];

    // Shift each row down by one position
    for (int i = numRows - 1; i > 0; --i) {
        matrix[i] = matrix[i - 1];
    }

    // Place the last row at the top
    matrix[0] = lastRow;
}
```

## Shift Up

```cpp
void shift_matrix_up(std::vector<std::vector<int>> &matrix) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    // Save the first row
    std::vector<int> firstRow = matrix[0];

    // Shift each row up by one position
    for (int i = 0; i < numRows - 1; ++i) {
        matrix[i] = matrix[i + 1];
    }

    // Place the first row at the bottom
    matrix[numRows - 1] = firstRow;
}
```