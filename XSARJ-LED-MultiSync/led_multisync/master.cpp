#include "master.hpp"
#include <WiFi.h>
#include <HTTPClient.h>

const bool DEBUG = false;

struct_message_to_receive_master message_to_rcv_master;
struct_message_to_send_master message_to_send_master;

void on_data_sent_master(const uint8_t* mac_addr, esp_now_send_status_t status) {
    bool print = false;
    if (print) {
        Serial.print("\r\nLast Packet Send Status:\t");
        Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
        char macStr[18];
        Serial.print("Packet to: ");
        // Copies the sender mac address to a string
        snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        Serial.print(macStr);
        Serial.print(" send status:\t");
    }
    // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    // Serial.println(sizeof(message_to_send.anim));
}

void on_data_recv_master(const uint8_t* mac, const uint8_t* incomingData, int len) {
    // Serial.println((uintptr_t)mac, HEX);
    memcpy(&message_to_rcv_master, incomingData, sizeof(message_to_rcv_master));

    Serial.print("Bytes received: ");
    Serial.println(len);
}


bool connect_cloud() {
    const char* server_endpoint = "https://panel.xsarj.com/led/subscribe_master";

    // Serialize JSON document
    JsonDocument doc;
    doc["master_mac"] = WiFi.macAddress();
    // doc["led_count"] = 4;

    std::string json;
    serializeJson(doc, json);

    HTTPClient http;
    // Send request
    http.begin(server_endpoint);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Accept", "*/*");
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    http.setConnectTimeout(5000);

    bool success = false;

    int http_response_code = http.POST(json.c_str());
    if (http_response_code > 0) {
        String response = http.getString();
        JsonDocument response_doc;
        DeserializationError error = deserializeJson(response_doc, response);
        if (!error) {
            if (response_doc["result"].containsKey("status") && response_doc["result"]["status"] == "OK") {
                success = true;
            }
        } else {
            Serial.println(error.c_str());
        }
        Serial.println(response);

    } else {
        // Print error message if the request failed
        Serial.print("Error on HTTP request: ");
        Serial.println(http_response_code);
    }
    // Disconnect
    http.end();

    return success;
}

void send_heartbeat() {

    EspNowRoleManager& role_manager = EspNowRoleManager::get_instance();

    const char* server_endpoint = "https://panel.xsarj.com/led/heartbeat";

    // Serialize JSON document
    JsonDocument doc;
    doc["master_mac"] = WiFi.macAddress();

    std::string json;
    serializeJson(doc, json);

    HTTPClient http;
    // Send request
    http.begin(server_endpoint);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Accept", "*/*");
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    http.setConnectTimeout(5000);

    int http_response_code = http.POST(json.c_str());
    if (http_response_code > 0) {
        // Serial.println("Heartbeat sent...");

        String response = http.getString();
        JsonDocument response_doc;
        DeserializationError error = deserializeJson(response_doc, response);
        if (!error) {
            if (response_doc["result"].containsKey("should_update")) {
                bool should_update = response_doc["result"]["should_update"];
                role_manager.set_update_required(should_update);
                // Serial.println(role_manager.is_update_required());
            } else {
                Serial.print("deserializeJson() failed: ");
                Serial.println(error.c_str());
            }
            // Serial.println(response);

        } else {
            // Print error message if the request failed
            Serial.print("Error on HTTP request: ");
            Serial.println(http_response_code);
        }
    }
}

bool get_action_from_cloud() {

    const char* server_endpoint = "https://panel.xsarj.com/led/get_action";

    // Serialize JSON document
    JsonDocument doc;
    doc["master_mac"] = WiFi.macAddress();

    std::string json;
    serializeJson(doc, json);

    HTTPClient http;
    // Send request
    http.begin(server_endpoint);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Accept", "*/*");
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    http.setConnectTimeout(5000);

    int http_response_code = http.POST(json.c_str());
    if (http_response_code > 0) {
        // Serial.println("Getting action list...");

        String response = http.getString();
        JsonDocument response_doc;
        DeserializationError error = deserializeJson(response_doc, response);
        if (!error) {
            bool is_pattern = response_doc["result"]["is_pattern"];
            String slave_mac_list = response_doc["result"]["slave_mac_list"];
            String display_text = response_doc["result"]["display_text"];
            String pattern_animation = response_doc["result"]["pattern_animation"];
            String pattern = response_doc["result"]["pattern"];
            Serial.println(response);

            // Extract and convert MAC addresses
            std::vector<String> mac_addresses = split_string(slave_mac_list, ',');
            std::vector<std::array<uint8_t, 6>> broadcast_addresses;

            for (const String& mac : mac_addresses) {
                std::array<uint8_t, 6> mac_array;
                extract_mac(mac, mac_array);
                broadcast_addresses.push_back(mac_array);
            }


            EspNowRoleManager& role_manager = EspNowRoleManager::get_instance();
            role_manager.broadcast_addresses = broadcast_addresses;
            role_manager.is_pattern = is_pattern;
            role_manager.display_texts = split_string(display_text, ',');
            role_manager.pattern_animation = pattern_animation;
            Serial.println(pattern_animation);
            Serial.println(role_manager.pattern_animation);
            role_manager.pattern = convertFromBitString(std::string(pattern.c_str()), p10.grid_32.size(), p10.grid_32[0].size());

            // Serial.print("Broadcast addresses size: ");
            // Serial.println(role_manager.broadcast_addresses.size());

            return true;


        } else {
            // Print error message if the request failed
            Serial.print("Error on HTTP request: ");
            Serial.println(http_response_code);

            return false;
        }
    }
}


void setup_action(UniqueQueue& slave_queue) {
    EspNowRoleManager& role_manager = EspNowRoleManager::get_instance();

    Serial.println("Setting up actions...");

    if (role_manager.is_pattern) {
        message_to_send_master.flags.set(0, true);
        message_to_send_master.flags.set(1, false);
    } else {
        message_to_send_master.flags.set(0, false);
        message_to_send_master.flags.set(1, true);
    }

    // Serial.println("Addresses received from cloud: ");
    // for (int i = 0; i < role_manager.broadcast_addresses.size(); i++) {
    //     Serial.print("broadcastAddress_");
    //     Serial.print(i + 1);
    //     Serial.print(": ");
    //     for (int j = 0; j < 6; j++) {
    //         if (j > 0)
    //             Serial.print(":");
    //         Serial.printf("%02X", role_manager.broadcast_addresses[i][j]);
    //     }
    //     Serial.println();
    // }
    // Refresh the Queue
    // Unregister existing peers
    // Serial.print("Queue size before: ");
    // Serial.print(slave_queue.size());
    // Serial.println();

    unregister_all_peers(slave_queue);
    Serial.println("Unregistered all peers and cleared the Queue");

    // Serial.print("Queue size after clearing: ");
    // Serial.print(slave_queue.size());
    // Serial.println();

    for (size_t i = 0; i < role_manager.broadcast_addresses.size(); ++i) {
        auto& addr = role_manager.broadcast_addresses[i];
        slave_queue.push(std::make_tuple(addr.data(), i + 1));
    }

    // Serial.print("Queue size after adding new addresses: ");
    // Serial.println(slave_queue.size());

    register_peers(slave_queue);
    Serial.println("Queue refreshed");

    role_manager.set_action(); // Action is set -> true
    role_manager.set_update_required(false);
    Serial.println("[MASTER] -> Action is set, ready");
}