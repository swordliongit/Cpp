#ifndef SLAVE_H
#define SLAVE_H

#include <string>
#include <bitset>
#include <esp_now.h>
#include "util.hpp"

extern std::string compressedString;
extern std::vector<std::vector<int>> reconstructedGrid;
extern bool should_animate;

struct struct_message_to_receive_slave
{
    char charArray[64];
    std::bitset<8> flags;
    char bChar[64];
    // char t[32];
};

struct struct_message_to_send_slave
{
    bool is_anim_completed;
};

extern struct_message_to_receive_slave message_to_rcv_slave;
extern struct_message_to_send_slave message_to_send_slave;

void on_data_sent_slave(const uint8_t* mac_addr, esp_now_send_status_t status);
void on_data_recv_slave(const uint8_t* mac, const uint8_t* incomingData, int len);

#endif