#include "util.hpp"
#include "master.hpp"
#include "uqueue.hpp"
#include <Arduino.h>
#include <cstring>

uint8_t broadcastAddress_1[6] = {0x48, 0xE7, 0x29, 0xB7, 0xE1, 0xCC};
uint8_t broadcastAddress_2[6] = {0x78, 0x21, 0x84, 0xBB, 0x9F, 0x18};
uint8_t broadcastAddress_3[6] = {0x40, 0x22, 0xD8, 0x6E, 0x7F, 0xCC};

esp_now_peer_info_t peerInfo;

std::string serial2_get_data(const char* prefix, const char* suffix)
    {
    if (Serial2.available() > 0)
        {
        String raw_serial2 = Serial2.readStringUntil('\n');
        // Serial.print("raw_serial2: ");
        // Serial.print(raw_serial2);
        // Serial.println();
        if (raw_serial2.indexOf(prefix) >= 0 && raw_serial2.indexOf(suffix) >= 0)
            {
            // yield();
            int prefix_end_index = raw_serial2.indexOf(prefix) + static_cast<int>(std::strlen(prefix));
            int suffix_start_index = raw_serial2.indexOf(suffix);
            return std::string(raw_serial2.substring(prefix_end_index, suffix_start_index).c_str());
            }
        }
    return std::string("");
    }

void register_peers(UniqueQueue& slave_queue)
    {
    // Register peer
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    UniqueQueue proxy(false);

    // std::copy(mac, mac + 6, copied_mac);
    // std::tuple<uint8_t *, int> peer{copied_mac, message_to_rcv.order};
    // slave_queue.push(peer);
    // Serial.print("Registering peers: ");
    // Serial.println(slave_queue.size());

    while (!slave_queue.empty())
        {
        const uint8_t* addr = std::get<0>(slave_queue.top());
        // Serial.print("Registering peer: ");
        for (int i = 0; i < 6; i++)
            {
            if (i > 0)
                Serial.print(":");
            Serial.printf("%02X", addr[i]);
            }
        Serial.println();

        memcpy(peerInfo.peer_addr, std::get<0>(slave_queue.top()), 6);
        esp_err_t add_peer_result = esp_now_add_peer(&peerInfo);
        if (add_peer_result != ESP_OK)
            {
            Serial.print("Failed to add peer, error: ");
            Serial.println(add_peer_result);
            }
        proxy.push(slave_queue.top());
        slave_queue.pop();
        }
    while (!proxy.empty())
        {
        slave_queue.push(proxy.top());
        proxy.pop();
        }
    Serial.println("All peers registered successfully");
    }

void unregister_all_peers(UniqueQueue& slave_queue)
    {
    while (!slave_queue.empty())
        {
        const uint8_t* addr = std::get<0>(slave_queue.top());
        if (esp_now_is_peer_exist(addr))
            {
            Serial.println("Peer exists");
            if (esp_now_del_peer(addr) != ESP_OK)
                {
                Serial.println("Failed to delete peer");
                }
            else
                {
                Serial.println("Peer deleted successfully");
                }
            }
        slave_queue.pop();
        }
    }

int32_t getWiFiChannel(const char* ssid)
    {
    if (int32_t n = WiFi.scanNetworks())
        {
        for (uint8_t i = 0; i < n; i++)
            {
            if (!strcmp(ssid, WiFi.SSID(i).c_str()))
                {
                return WiFi.channel(i);
                }
            }
        }
    return 0;
    }

void prepare_next_matrix(std::vector<std::vector<int>>& matrix)
    {
    std::string bitString = convertToBitString(matrix);
    std::string compressedString = compressBitString(bitString);

    size_t compressedSize = compressedString.size();
    // Serial.println(compressedSize);
    for (size_t i = 0; i < compressedSize; ++i)
        {
        message_to_send_master.charArray[i] = compressedString[i];
        }
    }

void prepare_and_shift_next_matrix(std::vector<std::vector<int>>& matrix, std::function<void(std::vector<std::vector<int>>&)> shifter,
                                   bool should_print)
    {
    shifter(matrix);

    std::string bitString = convertToBitString(matrix);
    std::string compressedString = compressBitString(bitString);

    size_t compressedSize = compressedString.size();
    // Serial.println(compressedSize);
    for (size_t i = 0; i < compressedSize; ++i)
        {
        message_to_send_master.charArray[i] = compressedString[i];
        }

    if (should_print)
        {
        Serial.println(bitString.c_str());
        Serial.print("Compressed String: ");
        Serial.println();
        for (unsigned char c : message_to_send_master.charArray)
            {
            Serial.print(binaryString(c).c_str());
            Serial.println();
            }
        }
    }

void shift_matrix_down(std::vector<std::vector<int>>& matrix)
    {
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    // Save the last row
    std::vector<int> lastRow = matrix[numRows - 1];

    // Shift each row down by one position
    for (int i = numRows - 1; i > 0; --i)
        {
        matrix[i] = matrix[i - 1];
        }

    // Place the last row at the top
    matrix[0] = lastRow;
    }

void shift_matrix_up(std::vector<std::vector<int>>& matrix)
    {
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    // Save the first row
    std::vector<int> firstRow = matrix[0];

    // Shift each row up by one position
    for (int i = 0; i < numRows - 1; ++i)
        {
        matrix[i] = matrix[i + 1];
        }

    // Place the first row at the bottom
    matrix[numRows - 1] = firstRow;
    }

std::string convertToBitString(const std::vector<std::vector<int>>& grid)
    {
    std::string bitString;
    for (const auto& row : grid)
        {
        for (int cell : row)
            {
            bitString += (cell == 1) ? '1' : '0';
            }
        }
    return bitString;
    }

std::string compressBitString(const std::string& bitString)
    {
    std::string compressedString;
    for (size_t i = 0; i < bitString.size(); i += 8)
        {
        std::bitset<8> bits(bitString.substr(i, 8));
        compressedString += static_cast<char>(bits.to_ulong());
        }
    return compressedString;
    }

std::vector<std::vector<int>> convertFromBitString(const std::string& bitString, int numRows, int numCols)
    {
    std::vector<std::vector<int>> grid(numRows, std::vector<int>(numCols));
    int index = 0;
    for (int i = 0; i < numRows; ++i)
        {
        for (int j = 0; j < numCols; ++j)
            {
            grid[i][j] = (bitString[index++] == '1') ? 1 : 0;
            }
        }
    return grid;
    }

std::string decompressBitString(const std::string& compressedString)
    {
    std::string bitString;
    for (unsigned char c : compressedString)
        {
        std::bitset<8> bits(c);
        bitString += bits.to_string();
        }
    return bitString;
    }

std::string binaryString(unsigned char c)
    {
    std::string result;
    for (int i = 7; i >= 0; --i)
        {
        result += ((c >> i) & 1) ? '1' : '0';
        }
    return result;
    }

void shift_matrix_diagonal_once(std::vector<std::vector<int>>& grid)
    {
    int numRows = grid.size();
    int numCols = grid[0].size();

    std::vector<std::vector<int>> temp(numRows, std::vector<int>(numCols, 0));

    for (int i = 0; i < numRows; ++i)
        {
        for (int j = 0; j < numCols; ++j)
            {
            int new_i = (i + 1) % numRows;
            int new_j = (j + 1) % numCols;
            temp[new_i][new_j] = grid[i][j];
            }
        }
    grid = temp;
    }

void shift_matrix_diagonal_decaying(std::vector<std::vector<int>>& grid)
    {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Shift each row down by one and each column to the right by one
    for (int i = numRows - 1; i >= 1; --i)
        {
        for (int j = numCols - 1; j >= 1; --j)
            {
            grid[i][j] = grid[i - 1][j - 1];
            }
        }

    // Clear the first row and first column
    for (int i = 0; i < numRows; ++i)
        {
        grid[i][0] = 0;
        }
    for (int j = 0; j < numCols; ++j)
        {
        grid[0][j] = 0;
        }
    }

void shift_matrix_diagonal_decaying_upwards(std::vector<std::vector<int>>& grid)
    {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Shift each row up by one and each column to the right by one
    for (int i = 0; i < numRows - 1; ++i)
        {
        for (int j = numCols - 1; j >= 1; --j)
            {
            grid[i][j] = grid[i + 1][j - 1];
            }
        }

    // Clear the first column, except for the first row
    for (int i = 1; i < numRows; ++i)
        {
        grid[i][0] = 0;
        }

    // Clear the last row
    for (int j = 0; j < numCols; ++j)
        {
        grid[numRows - 1][j] = 0;
        }
    }

void shift_matrix_right(std::vector<std::vector<int>>& grid)
    {
    int size = grid.size();
    for (int i = 0; i < size; ++i)
        {
        int temp = grid[i][size - 1];
        for (int j = size - 1; j > 0; --j)
            {
            grid[i][j] = grid[i][j - 1];
            }
        grid[i][0] = temp;
        }
    }

std::vector<String> split_string(const String& str, char delimiter)
    {
    std::vector<String> result;
    int start = 0;
    int end = str.indexOf(delimiter);
    while (end != -1)
        {
        result.push_back(str.substring(start, end));
        start = end + 1;
        end = str.indexOf(delimiter, start);
        }
    result.push_back(str.substring(start));
    return result;
    }

void extract_mac(const String& mac_str, std::array<uint8_t, 6>& mac_array)
    {
    std::vector<String> hex_strs = split_string(mac_str, ':');
    for (int i = 0; i < 6; i++)
        {
        mac_array[i] = (uint8_t)strtol(hex_strs[i].c_str(), NULL, 16);
        }
    }