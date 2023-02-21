#include <iostream>
#include <vector>
#include <cmath>


void rotate_matrix(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    
    // Transpose matrix
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
    // Reverse each row
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n/2; j++) {
            std::swap(matrix[i][j], matrix[i][n-1-j]);
        }
    }
}

int main() {
    std::vector<std::vector<int>> grid =
    {
        {0,0,0,0,0,0,1},
        {0,0,0,0,0,1,0},
        {1,0,0,0,1,0,0},
        {0,1,0,1,0,0,0},
        {0,0,1,0,0,0,0},
        {0,1,0,1,0,0,0},
        {1,0,0,0,1,0,0}
    };
    
    // Rotate matrix by 90 degrees
    rotate_matrix(grid);
    
    // Print rotated matrix
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    // Rotate matrix by 90 degrees
    rotate_matrix(grid);
    
    // Print rotated matrix
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
