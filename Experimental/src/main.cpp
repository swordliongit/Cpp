

#include <cstring>
#include <iostream>
#include <cstdint>
#include <queue>
#include <set>
#include <thread>
// const uint8_t broadcastAddress[6] = {0x78, 0x21, 0x84, 0xBB, 0x9F, 0x18};

using namespace std::literals;

uint8_t copied[6];

struct CompareOrder
{
    bool operator()(const std::tuple<const uint8_t *, int> &a, const std::tuple<const uint8_t *, int> &b) const {
        // Compare based on the order value
        return std::get<1>(a) > std::get<1>(b); // Change > to < for ascending order
    }
};

class UniqueQueue
{
    std::priority_queue<std::tuple<const uint8_t *, int>, std::vector<std::tuple<const uint8_t *, int>>, CompareOrder>
        pqueue{};
    std::set<std::tuple<const uint8_t *, int>> proxy{};

public:
    void push(const std::tuple<const uint8_t *, int> &t) {
        if (this->proxy.insert(t).second) {
            this->pqueue.push(t);
        }
    }

    void pop() {
        this->proxy.erase(pqueue.top());
        this->pqueue.pop();
    }

    size_t size() {
        return this->pqueue.size();
    }

    bool empty() {
        return this->pqueue.empty();
    }

    std::tuple<const uint8_t *, int> top() {
        return this->pqueue.top();
    }
};

UniqueQueue slave_queue;

void OnDataRecv(const uint8_t *mac) {
    // Serial.println((uintptr_t)mac, HEX);
    // memcpy(&message_to_rcv, incomingData, sizeof(message_to_rcv));

    // uint8_t copied_mac[6];
    // std::copy(mac, mac + 6, copied_mac);

    std::copy(mac, mac + 6, copied);
    slave_queue.push(std::make_tuple(copied, 1));

    try {
        char macStr[18];
        std::cout << "Mac received:";
        const uint8_t *t = std::get<0>(slave_queue.top());
        snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", t[0], t[1], t[2], t[3], t[4], t[5]);
        std::cout << macStr;
    } catch (const std::exception &e) {
        // std::cout << e.what();
        std::cerr << e.what() << '\n';
    }
}


void register_peers() {

    const uint8_t *t = std::get<0>(slave_queue.top());
    char macStr2[18];
    snprintf(macStr2, sizeof(macStr2), "%02x:%02x:%02x:%02x:%02x:%02x", t[0], t[1], t[2], t[3], t[4], t[5]);
    std::cout << "Mac in register_peers(): "
              << "\n";
    std::cout << macStr2;
    std::vector<std::tuple<const uint8_t *, int>> popped_list;
    while (!slave_queue.empty()) {
        popped_list.push_back(slave_queue.top());
        slave_queue.pop();
    }

    for (auto &el : popped_list) {
        slave_queue.push(el);
    }
}

int main() {

    uint8_t mac[6] = {0x78, 0x21, 0x84, 0xBB, 0x9F, 0x18};
    OnDataRecv(mac);
    register_peers();
    // std::this_thread::sleep_for(4s);
    mac[0] = 0x12;
    uint8_t mac2[6] = {0x2B, 0x21, 0x84, 0xBB, 0x9F, 0x20};
    OnDataRecv(mac2);
    register_peers();
}