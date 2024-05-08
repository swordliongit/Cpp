// C++ program to demonstrate
// min heap for priority queue
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <functional>

struct CompareOrder
{
    bool ascending;
    explicit CompareOrder(bool asc = true) : ascending(asc) {
    }
    bool operator()(const std::tuple<std::string, int> &a, const std::tuple<std::string, int> &b) const {
        // Compare based on the order value
        if (ascending)
            return std::get<1>(a) < std::get<1>(b); // Ascending order
        else
            return std::get<1>(a) > std::get<1>(b); // Descending order
    }
};

class UniqueQueue
{
    std::priority_queue<std::tuple<std::string, int>, std::vector<std::tuple<std::string, int>>, CompareOrder> pqueue;
    std::set<std::tuple<std::string, int>> proxy;

public:
    UniqueQueue(bool ascending = true) : pqueue(CompareOrder(ascending)) {
    }


    void push(const std::tuple<std::string, int> &t) {
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

    std::tuple<std::string, int> top() {
        return this->pqueue.top();
    }
};

int main() {
    std::tuple<std::string, int> t1{"first", 1}, t2{"second", 2}, t3{"third", 3};
    UniqueQueue queue(false), queue2(true);

    queue.push(std::make_tuple("first", 1));
    std::cout << queue.size() << "\n";
    queue.push(t2);
    std::cout << queue.size() << "\n";
    queue.push(t2);
    std::cout << queue.size() << "\n";
    queue.push(t3);
    std::cout << queue.size() << "\n";

    std::vector<std::tuple<std::string, int>> popped_list;
    while (!queue.empty()) {
        std::cout << std::get<0>(queue.top()) << "," << std::get<1>(queue.top()) << "\n";
        popped_list.push_back(queue.top());
        queue.pop();
    }

    for (auto &el : popped_list) {
        queue2.push(el);
    }

    std::cout << "\n\n";
    while (!queue2.empty()) {
        std::cout << std::get<0>(queue2.top()) << "," << std::get<1>(queue2.top()) << "\n";
        queue2.pop();
    }
}