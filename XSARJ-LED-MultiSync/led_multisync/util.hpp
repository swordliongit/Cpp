#ifndef UTIL_H
#define UTIL_H

#include <ArduinoJson.h>
#include <esp_now.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <vector>
#include <bitset>
#include <functional>
#include <tuple>
#include <array>

#include "uqueue.hpp"
#include "espnow_role_manager.hpp"
#include "pattern_animator.hpp"

#include <DMD32.h> //

extern esp_now_peer_info_t peerInfo;

#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
extern DMD dmd;
extern PatternAnimator p10;

std::string serial2_get_data(const char* prefix, const char* suffix);

void register_peers(UniqueQueue& slave_queue);
void unregister_all_peers(UniqueQueue& slave_queue);

template <typename Function, typename... Args> void run_every_seconds(const unsigned long Interval, Function func, Args... args)
{
    static unsigned long last_time_run = 0;
    unsigned long current_time = millis();

    if (current_time - last_time_run >= Interval)
        {
            func(args...);
            last_time_run = current_time;
        }
}

int32_t getWiFiChannel(const char* ssid);

void prepare_next_matrix(std::vector<std::vector<int>>& matrix);

void prepare_and_shift_next_matrix(std::vector<std::vector<int>>& matrix, std::function<void(std::vector<std::vector<int>>&)> shifter,
                                   bool should_print = false);

void shift_matrix_down(std::vector<std::vector<int>>& matrix);

void shift_matrix_up(std::vector<std::vector<int>>& matrix);

// Function to convert 2D vector to a bit string
std::string convertToBitString(const std::vector<std::vector<int>>& grid);

// Function to compress the bit string into bit fields
std::string compressBitString(const std::string& bitString);

// Function to convert bit string back into 2D vector
std::vector<std::vector<int>> convertFromBitString(const std::string& bitString, int numRows, int numCols);

// Function to decompress the compressed string back into bit string
std::string decompressBitString(const std::string& compressedString);

// Function to print binary representation of a character
std::string binaryString(unsigned char c);

void shift_matrix_diagonal_once(std::vector<std::vector<int>>& grid);

void shift_matrix_diagonal_decaying(std::vector<std::vector<int>>& grid);

void shift_matrix_diagonal_decaying_upwards(std::vector<std::vector<int>>& grid);

void shift_matrix_right(std::vector<std::vector<int>>& grid);

std::vector<String> split_string(const String& str, char delimiter);

void extract_mac(const String& mac_str, std::array<uint8_t, 6>& mac_array);

#endif