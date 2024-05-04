#include <iostream>
#include <thread>
#include <vector>
#include <bitset>

#include <iostream>
#include <bitset>
#include <cstring>

using namespace std::literals;

std::vector<std::vector<int>> grid = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};


// Function to convert 2D vector to a bit string
std::string convertToBitString(const std::vector<std::vector<int>> &grid) {
    std::string bitString;
    for (const auto &row : grid) {
        for (int cell : row) {
            bitString += (cell == 1) ? '1' : '0';
        }
    }
    return bitString;
}

// Function to convert bit string back into 2D vector
std::vector<std::vector<int>> convertFromBitString(const std::string &bitString, int numRows, int numCols) {
    std::vector<std::vector<int>> grid(numRows, std::vector<int>(numCols));
    int index = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            grid[i][j] = (bitString[index++] == '1') ? 1 : 0;
        }
    }
    return grid;
}


// Function to compress the bit string into bit fields
std::string compressBitString(const std::string &bitString) {
    std::string compressedString;
    for (size_t i = 0; i < bitString.size(); i += 8) {
        std::bitset<8> bits(bitString.substr(i, 8));
        compressedString += static_cast<char>(bits.to_ulong());
    }
    return compressedString;
}

// Function to decompress the compressed string back into bit string
std::string decompressBitString(const std::string &compressedString) {
    std::string bitString;
    for (unsigned char c : compressedString) {
        std::bitset<8> bits(c);
        bitString += bits.to_string();
    }
    return bitString;
}


// Function to print binary representation of a character
std::string binaryString(unsigned char c) {
    std::string result;
    for (int i = 7; i >= 0; --i) {
        result += ((c >> i) & 1) ? '1' : '0';
    }
    return result;
}

void shiftMatrixDownOnce(std::vector<std::vector<int>> &matrix) {
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
struct struct_message_to_send
{
    char charArray[64];
};

struct_message_to_send message_to_send;

void prepare_next_matrix(std::vector<std::vector<int>> &matrix) {


    std::string bitString = convertToBitString(matrix);
    std::string compressedString = compressBitString(bitString);

    size_t compressedSize = compressedString.size();
    for (size_t i = 0; i < compressedSize; ++i) {
        message_to_send.charArray[i] = compressedString[i];
    }
    // Null-terminate the char array
    // message_to_send.charArray[compressedSize] = '\0';

    std::cout << "Bit String: " << bitString.c_str();
    std::cout << "\n\nCompressed String: \n";
    for (unsigned char c : message_to_send.charArray) {
        std::cout << binaryString(c).c_str() << "\n";
    }


    std::string second_compstring(message_to_send.charArray, compressedSize);
    std::cout << "\n\nSecond Comp String: \n";
    for (unsigned char c : second_compstring) {
        std::cout << binaryString(c).c_str() << "\n";
    }
    std::cout << second_compstring.size();
    std::string decompressedString = decompressBitString(second_compstring);

    std::vector<std::vector<int>> reconstructedGrid = convertFromBitString(decompressedString, matrix.size(), matrix[0].size());

    std::cout << "\n\n\n"
              << "Decompressed Vector: \n";
    // Check if the reconstruction is correct
    for (const auto &row : reconstructedGrid) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    shiftMatrixDownOnce(matrix);
}

int main() {

    for (int i = 0; i < 8; ++i) {
        prepare_next_matrix(grid);
        std::cout << "\n\n\n";
        std::this_thread::sleep_for(1s);
    }

    // std::string bitString = convertToBitString(grid);
    // std::string compressedString = compressBitString(bitString);
    // std::string decompressedString = decompressBitString(compressedString);

    // std::cout << "Bit String: " << bitString << std::endl;
    // std::cout << "Compressed String: ";
    // for (unsigned char c : compressedString) {
    //     std::cout << binaryString(c) << ' ';
    // }
    // std::cout << std::endl;
    // std::cout << "Decompressed String: " << decompressedString << "\n";

    // // Reconstruct the original grid from the bit string
    // std::vector<std::vector<int>> reconstructedGrid = convertFromBitString(decompressedString, grid.size(), grid[0].size());

    // // Check if the reconstruction is correct
    // for (const auto &row : reconstructedGrid) {
    //     for (int cell : row) {
    //         std::cout << cell << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << bitString.size() << "\n";
    // std::cout << compressedString.size() << "\n";
    // std::cout << decompressedString.size() << "\n";


    return 0;
}
