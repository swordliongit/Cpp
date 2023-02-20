#include <iostream>

#include <vector>

int main()
{
    int numCols;

    std::cin >> numCols;

    // define a 2D vector with 7 rows and "numCols" columns
    std::vector<std::vector<int>> sp(7, std::vector<int>(numCols));

    // populate the vector with values
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < numCols; j++) {
            sp[i][j] = i * numCols + j;
        }
    }

    // print the vector as a matrix
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << sp[i][j] << " ";
        }
        std::cout << std::endl;
    }


}