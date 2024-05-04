1. Example: 
```cpp
std::vector<std::vector<int>> vec; // 8x64 array

typedef struct struct_message_to_send
{
    char charArray[64]; // transfer block

} struct_message_to_send;
```

2. Convert the vector into a bit string:
```cpp
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

 std::string bitString = convertToBitString(p10.grid);
```

2. Compress the bit string into a bitset string:
```cpp
// Function to compress the bit string into bit fields
std::string compressBitString(const std::string &bitString) {
    std::string compressedString;
    for (size_t i = 0; i < bitString.size(); i += 8) {
        std::bitset<8> bits(bitString.substr(i, 8));
        compressedString += static_cast<char>(bits.to_ulong());
    }
    return compressedString;
}

std::string compressedString = compressBitString(bitString);
```

3. Copy the bitset string into the char array and send it:
```cpp
size_t compressedSize = compressedString.size();
for (size_t i = 0; i < compressedSize; ++i) {
	message_to_send.charArray[i] = compressedString[i];
}
esp_err_t result = esp_now_send(slave_address, (uint8_t *)&message_to_send, sizeof(message_to_send));
```

4. Map the bitset chat array into a string in the receiver:
```cpp
std::string compressedString;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&message_to_rcv, incomingData, sizeof(message_to_rcv));
    Serial.print("Bytes received: ");
    Serial.println(len);
    for (unsigned char c : message_to_rcv.charArray) {
        Serial.print(binaryString(c).c_str());
        Serial.println();
    }
    compressedString = std::string(message_to_rcv.charArray, compressedSize);
}
```

5. Decompress the bitset string into a bit string:
```cpp
// Function to decompress the compressed string back into bit string
std::string decompressBitString(const std::string &compressedString) {
    std::string bitString;
    for (unsigned char c : compressedString) {
        std::bitset<8> bits(c);
        bitString += bits.to_string();
    }
    return bitString;
}

 std::string decompressedString = decompressBitString(compressedString);
```

6. Convert the bit string back into a vector:
```cpp

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

std::vector<std::vector<int>> reconstructedGrid = convertFromBitString(decompressedString, p10.grid.size(), p10.grid[0].size());

// Check if the reconstruction is correct
for (const auto &row : reconstructedGrid) {
	for (int cell : row) {
		std::cout << cell << " ";
	}
	std::cout << std::endl;
}
```