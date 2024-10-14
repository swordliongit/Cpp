#include "slave.hpp"

std::string compressedString;
std::vector<std::vector<int>> reconstructedGrid;
bool should_animate;

struct_message_to_receive_slave message_to_rcv_slave;
struct_message_to_send_slave message_to_send_slave;

void on_data_sent_slave(const uint8_t* mac_addr, esp_now_send_status_t status)
{
    char macStr[18];
    Serial.print("Packet to: ");
    // Copies the sender mac address to a string
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4],
             mac_addr[5]);
    Serial.print(macStr);
    Serial.print(" send status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");

    // Serial.println(status);
    // if (!status)
    //     mac_sent = true;
}

void on_data_recv_slave(const uint8_t* mac, const uint8_t* incomingData, int len)
{
    memcpy(&message_to_rcv_slave, incomingData, sizeof(message_to_rcv_slave));
    // Serial.print("Bytes received: ");
    // Serial.println(len);
    // for (unsigned char c : message_to_rcv.charArray) {
    //     Serial.print(binaryString(c).c_str());
    //     Serial.println();
    // }
    // Serial.println();
    // Serial.println();
    compressedString = std::string(message_to_rcv_slave.charArray, 64);

    std::string decompressedString = decompressBitString(compressedString);
    reconstructedGrid = convertFromBitString(decompressedString, p10.grid.size(), p10.grid[0].size());

    // Serial.println(message_to_rcv.flags.to_string().c_str());
    // Serial.print("Char: ");
    // Serial.println(message_to_rcv.t);
    // Serial.println();

    should_animate = true;
}