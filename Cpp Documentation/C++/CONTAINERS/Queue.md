
## Custom Ordered Queue
```cpp
// C++ program to demonstrate
// min heap for priority queue
#include <iostream>
#include <queue>
#include <tuple>
#include <functional>
using namespace std;

struct CompareOrder
{
    bool operator()(const std::tuple<std::string, int>& a, const std::tuple<std::string, int>& b) const {
        // Compare based on the order value
        return std::get<1>(a) > std::get<1>(b); // Change > to < for ascending order
    }
};

int main() {
    priority_queue<std::tuple<std::string, int>, vector<std::tuple<std::string, int>>, CompareOrder> pqueue;
    pqueue.emplace("dsfsdfsd", 2);
    pqueue.emplace("qweq", 3);
    pqueue.emplace("gwegwe", 1);
    pqueue.emplace("__s", 10);
    pqueue.emplace("__s", 7);


    while (!pqueue.empty()) {
        std::cout << std::get<0>(pqueue.top()) << "," << std::get<1>(pqueue.top()) << "\n";
        pqueue.pop();
    }
}
```

## Custom Ordered Unique Queue
```cpp
struct CompareOrder
{
    bool operator()(const std::tuple<std::string, int> &a, const std::tuple<std::string, int> &b) const {
        // Compare based on the order value
        return std::get<1>(a) > std::get<1>(b); // Change > to < for ascending order
    }
};

class UniqueQueue
{
    std::priority_queue<std::tuple<std::string, int>, std::vector<std::tuple<std::string, int>>, CompareOrder> pqueue;
    std::set<std::tuple<std::string, int>> proxy;

public:
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
        return pqueue.empty();
    }

    std::tuple<std::string, int> top() {
        return pqueue.top();
    }
};

int main() {
    std::tuple<std::string, int> t1{"first", 1}, t2{"second", 2}, t3{"third", 3};
    UniqueQueue queue;

    queue.push(std::make_tuple("first", 1));
    std::cout << queue.size() << "\n";
    queue.push(t2);
    std::cout << queue.size() << "\n";
    queue.push(t2);
    std::cout << queue.size() << "\n";
    queue.push(t1);
    std::cout << queue.size() << "\n";


    while (!queue.empty()) {
        std::cout << std::get<0>(queue.top()) << "," << std::get<1>(queue.top()) << "\n";
        queue.pop();
    }
}
```