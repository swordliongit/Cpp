#ifndef MASTER_H
#define MASTER_H


#include <esp_now.h>
#include <bitset>
#include "esp_system.h"
#include <Arduino.h>
#include <vector>
#include <ArduinoJson.h>
#include <array>
#include <tuple>

#include "espnow_role_manager.hpp"
#include "util.hpp"

extern const bool DEBUG;

// Receive
struct struct_message_to_receive_master
{
    bool is_anim_completed;
};


struct struct_message_to_send_master
{
    // Animation anim;
    char charArray[64];
    std::bitset<8> flags;
    char bChar[64];
    // 0000 0001 : Draw Pattern Static
    // 0000 0010 : Scrolling Marquee
    // int delay;
    // Flags slave_flag = Flags::None;
};

extern struct_message_to_receive_master message_to_rcv_master;
extern struct_message_to_send_master message_to_send_master;

void on_data_sent_master(const uint8_t* mac_addr, esp_now_send_status_t status);
void on_data_recv_master(const uint8_t* mac, const uint8_t* incomingData, int len);
bool connect_cloud();
void send_heartbeat();
bool get_action_from_cloud();
void setup_action(UniqueQueue& slave_queue);
#endif