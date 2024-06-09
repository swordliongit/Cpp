/*
Complex Led Animation Simulation Program
*/


#include <cstdint>
#include <queue>
#include <set>
#include <thread>
#include <vector>
#include <iostream>
#include <functional>
#include <bitset>
#include <chrono>
#include <tuple>

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

std::vector<std::vector<int>> square_32 = {
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

};


struct CompareOrder
{
    bool ascending;
    explicit CompareOrder(bool asc = true) : ascending(asc) {
    }
    bool operator()(const std::tuple<const uint8_t*, int>& a, const std::tuple<const uint8_t*, int>& b) const {
        // Compare based on the order value
        if (ascending)
            return std::get<1>(a) < std::get<1>(b); // Ascending order
        else
            return std::get<1>(a) > std::get<1>(b); // Descending order
    }
};

class UniqueQueue
{
    std::priority_queue<std::tuple<const uint8_t*, int>, std::vector<std::tuple<const uint8_t*, int>>, CompareOrder> pqueue{};
    std::set<std::tuple<const uint8_t*, int>> proxy{};

public:
    explicit UniqueQueue(bool ascending = true) : pqueue(CompareOrder(ascending)) {
    }
    void push(const std::tuple<const uint8_t*, int>& t) {
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

    std::tuple<const uint8_t*, int> top() {
        return this->pqueue.top();
    }
};

UniqueQueue slave_queue(false);
UniqueQueue proxy_queue(true);

uint8_t broadcastAddress_1[6] = {0x48, 0xE7, 0x29, 0xB7, 0xE1, 0xCC};
uint8_t broadcastAddress_2[6] = {0x78, 0x21, 0x84, 0xBB, 0x9F, 0x18};
uint8_t broadcastAddress_3[6] = {0x40, 0x22, 0xD8, 0x6E, 0x7F, 0xCC};

using struct_message_to_send = struct struct_message_to_send
{
    // Animation anim;
    char charArray[64];
    size_t bitSetStringSize;
    bool cmd = true;
    // int delay;
    // Flags slave_flag = Flags::None;
};

struct_message_to_send message_to_send;


using struct_message_to_receive = struct struct_message_to_receive
{
    // Animation anim;
    char charArray[64];
    size_t bitSetStringSize;
    bool cmd = true;
    // int delay;
    // Flags slave_flag = Flags::None;
};

struct_message_to_receive message_to_rcv;


void shift_matrix_down(std::vector<std::vector<int>>& matrix) {
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

void shift_matrix_up(std::vector<std::vector<int>>& matrix) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    // Save the first row
    std::vector<int> firstRow = matrix[0];

    // Shift each row up by one position
    for (int i = 0; i < numRows - 1; ++i) {
        matrix[i] = matrix[i + 1];
    }

    // Place the first row at the bottom
    matrix[numRows - 1] = firstRow;
}


// Function to convert 2D vector to a bit string
std::string convertToBitString(const std::vector<std::vector<int>>& grid) {
    std::string bitString;
    for (const auto& row : grid) {
        for (int cell : row) {
            bitString += (cell == 1) ? '1' : '0';
        }
    }
    return bitString;
}


// Function to compress the bit string into bit fields
std::string compressBitString(const std::string& bitString) {
    std::string compressedString;
    for (size_t i = 0; i < bitString.size(); i += 8) {
        std::bitset<8> bits(bitString.substr(i, 8));
        compressedString += static_cast<char>(bits.to_ulong());
    }
    return compressedString;
}


// Function to convert bit string back into 2D vector
std::vector<std::vector<int>> convertFromBitString(const std::string& bitString, int numRows, int numCols) {
    std::vector<std::vector<int>> grid(numRows, std::vector<int>(numCols));
    int index = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            grid[i][j] = (bitString[index++] == '1') ? 1 : 0;
        }
    }
    return grid;
}


// Function to decompress the compressed string back into bit string
std::string decompressBitString(const std::string& compressedString) {
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


void shift_matrix_diagonal_once(std::vector<std::vector<int>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    std::vector<std::vector<int>> temp(numRows, std::vector<int>(numCols, 0));

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            int new_i = (i + 1) % numRows;
            int new_j = (j + 1) % numCols;
            temp[new_i][new_j] = grid[i][j];
        }
    }
    grid = temp;
}

void shift_matrix_diagonal_decaying(std::vector<std::vector<int>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Shift each row down by one and each column to the right by one
    for (int i = numRows - 1; i >= 1; --i) {
        for (int j = numCols - 1; j >= 1; --j) {
            grid[i][j] = grid[i - 1][j - 1];
        }
    }

    // Clear the first row and first column
    for (int i = 0; i < numRows; ++i) {
        grid[i][0] = 0;
    }
    for (int j = 0; j < numCols; ++j) {
        grid[0][j] = 0;
    }
}

void shift_matrix_diagonal_decaying_upwards(std::vector<std::vector<int>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Shift each row up by one and each column to the right by one
    for (int i = 0; i < numRows - 1; ++i) {
        for (int j = numCols - 1; j >= 1; --j) {
            grid[i][j] = grid[i + 1][j - 1];
        }
    }

    // Clear the first column, except for the first row
    for (int i = 1; i < numRows; ++i) {
        grid[i][0] = 0;
    }

    // Clear the last row
    for (int j = 0; j < numCols; ++j) {
        grid[numRows - 1][j] = 0;
    }
}


void shift_matrix_right(std::vector<std::vector<int>>& grid) {
    int size = grid.size();
    for (int i = 0; i < size; ++i) {
        int temp = grid[i][size - 1];
        for (int j = size - 1; j > 0; --j) {
            grid[i][j] = grid[i][j - 1];
        }
        grid[i][0] = temp;
    }
}


void prepare_next_matrix(std::vector<std::vector<int>>& matrix) {
    std::string bitString = convertToBitString(matrix);
    std::string compressedString = compressBitString(bitString);

    size_t compressedSize = compressedString.size();
    // Serial.println(compressedSize);
    message_to_send.bitSetStringSize = compressedSize;
    for (size_t i = 0; i < compressedSize; ++i) {
        message_to_send.charArray[i] = compressedString[i];
    }
}

void prepare_and_shift_next_matrix(std::vector<std::vector<int>>& matrix, std::function<void(std::vector<std::vector<int>>&)> shifter, bool should_print = false) {

    shifter(matrix);

    std::string bitString = convertToBitString(matrix);
    std::string compressedString = compressBitString(bitString);

    size_t compressedSize = compressedString.size();
    // Serial.println(compressedSize);
    message_to_send.bitSetStringSize = compressedSize;
    for (size_t i = 0; i < compressedSize; ++i) {
        message_to_send.charArray[i] = compressedString[i];
    }

    if (should_print) {
        std::cout << bitString.c_str() << "\n";
        std::cout << "Compressed String: "
                  << "\n";
        for (unsigned char c : message_to_send.charArray) {
            std::cout << binaryString(c).c_str() << "\n";
        }
    }
}

void setup() {
    slave_queue.push(std::make_tuple(broadcastAddress_1, 1));
    slave_queue.push(std::make_tuple(broadcastAddress_2, 2));
    slave_queue.push(std::make_tuple(broadcastAddress_3, 3));
}

void receive(const uint8_t* peer_addr, const uint8_t* data) {
    std::vector<std::vector<int>> reconstructedGrid;
    std::string compressedString;

    memcpy(&message_to_rcv, data, sizeof(message_to_rcv));
    compressedString = std::string(message_to_rcv.charArray, 64);

    std::string decompressedString = decompressBitString(compressedString);
    reconstructedGrid = convertFromBitString(decompressedString, grid.size(), grid[0].size());
    for (auto& row : reconstructedGrid) {
        for (auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n\n";
}

void send(const uint8_t* peer_addr, const uint8_t* data) {
    receive(peer_addr, data);
}

void multianim_diagonal_shift() {
    constexpr auto ANIM_DELAY = std::chrono::milliseconds(500);
    constexpr auto SWITCH_DELAY = ANIM_DELAY * 4;

    std::vector<std::vector<int>> grid = square_32;

    for (size_t i = 0; i < 32; ++i) {
        // Animate Self

        std::vector<std::vector<int>> self_anim_part;
        auto end_iterator = grid.begin() + 8;
        for (auto it = grid.begin(); it != end_iterator; ++it) {
            self_anim_part.push_back(*it);
        }
        std::cout << "Master: "
                  << "\n";
        for (auto& row : self_anim_part) {
            for (auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n\n";
        int count = 2;
        // std::cout << "Queue Size: " << slave_queue.size() << "\n";

        // Animate Slaves
        while (!slave_queue.empty()) {
            std::vector<std::vector<int>> slave_anim_part;
            auto end_iterator = grid.begin() + (8 * count);
            for (auto it = grid.begin() + (8 * (count - 1)); it != end_iterator; ++it) {
                slave_anim_part.push_back(*it);
            }
            prepare_next_matrix(slave_anim_part);

            ++count;

            std::cout << "Slave " << std::get<1>(slave_queue.top()) << ": "
                      << "\n";
            send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send);

            proxy_queue.push(slave_queue.top());
            slave_queue.pop();
        }
        while (!proxy_queue.empty()) {
            slave_queue.push(proxy_queue.top());
            proxy_queue.pop();
        }
        shift_matrix_diagonal_decaying(grid);
        std::this_thread::sleep_for(std::chrono::seconds(1s));
    }
}

void multianim_diagonal_shift_fold() {
    constexpr auto ANIM_DELAY = std::chrono::milliseconds(500);
    constexpr auto SWITCH_DELAY = ANIM_DELAY * 4;
    constexpr size_t MAX_ROW = 32;
    bool flip = false;
    bool fold = true;
    int shape_length = 4;

    std::vector<std::vector<int>> grid = square_32;

    for (size_t i = 0; i < MAX_ROW - shape_length; ++i) {
        // Animate Self

        std::vector<std::vector<int>> self_anim_part;
        auto end_iterator = grid.begin() + 8;
        for (auto it = grid.begin(); it != end_iterator; ++it) {
            self_anim_part.push_back(*it);
        }
        std::cout << "Master: "
                  << "\n";
        for (auto& row : self_anim_part) {
            for (auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n\n";
        int count = 2;
        // std::cout << "Queue Size: " << slave_queue.size() << "\n";

        // Animate Slaves
        while (!slave_queue.empty()) {
            std::vector<std::vector<int>> slave_anim_part;
            auto end_iterator = grid.begin() + (8 * count);
            for (auto it = grid.begin() + (8 * (count - 1)); it != end_iterator; ++it) {
                slave_anim_part.push_back(*it);
            }
            prepare_next_matrix(slave_anim_part);

            ++count;

            std::cout << "Slave " << std::get<1>(slave_queue.top()) << ": "
                      << "\n";
            send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send);

            // if (fold && count == 5 && i == (MAX_ROW - shape_length)) {
            //     std::this_thread::sleep_for(5s);
            // }

            proxy_queue.push(slave_queue.top());
            slave_queue.pop();
        }
        while (!proxy_queue.empty()) {
            slave_queue.push(proxy_queue.top());
            proxy_queue.pop();
        }
        shift_matrix_diagonal_decaying(grid);
        std::this_thread::sleep_for(50ms);
    }

    while (!slave_queue.empty()) {
        proxy_queue.push(slave_queue.top());
        slave_queue.pop();
    }

    std::this_thread::sleep_for(5s);

    // Fold to reverse direction
    for (size_t i = 0; i < MAX_ROW + 1; ++i) {
        int count = 4;
        while (!proxy_queue.empty()) {
            std::vector<std::vector<int>> slave_anim_part;
            auto end_iterator = grid.begin() + (8 * count);
            for (auto it = grid.begin() + (8 * (count - 1)); it != end_iterator; ++it) {
                slave_anim_part.push_back(*it);
            }
            prepare_next_matrix(slave_anim_part);

            --count;

            std::cout << "Slave " << std::get<1>(proxy_queue.top()) << ": "
                      << "\n";
            send(std::get<0>(proxy_queue.top()), (uint8_t*)&message_to_send);

            slave_queue.push(proxy_queue.top());
            proxy_queue.pop();
        }
        while (!slave_queue.empty()) {
            proxy_queue.push(slave_queue.top());
            slave_queue.pop();
        }
        std::vector<std::vector<int>> self_anim_part;
        auto end_iterator = grid.begin() + 8;
        for (auto it = grid.begin(); it != end_iterator; ++it) {
            self_anim_part.push_back(*it);
        }
        std::cout << "Master: "
                  << "\n";
        for (auto& row : self_anim_part) {
            for (auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n\n";
        shift_matrix_diagonal_decaying_upwards(grid);
        std::this_thread::sleep_for(50ms);
    }
}

int main(int argc, char const* argv[]) {

    setup();

    multianim_diagonal_shift_fold();

    return 0;
}