#ifndef UQUEUE_H
#define UQUEUE_H

#include <queue>
#include <set>
#include <tuple>

struct CompareOrder
{
    bool ascending;
    explicit CompareOrder(bool asc = true) : ascending(asc) {}
    bool operator()(const std::tuple<const uint8_t*, int>& a, const std::tuple<const uint8_t*, int>& b) const
    {
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
    UniqueQueue(bool ascending = true) : pqueue(CompareOrder(ascending)) {}
    void push(const std::tuple<const uint8_t*, int>& t)
    {
        if (this->proxy.insert(t).second)
            {
                this->pqueue.push(t);
            }
    }

    void pop()
    {
        this->proxy.erase(pqueue.top());
        this->pqueue.pop();
    }

    size_t size()
    {
        return this->pqueue.size();
    }

    bool empty()
    {
        return this->pqueue.empty();
    }

    std::tuple<const uint8_t*, int> top()
    {
        return this->pqueue.top();
    }
};

#endif
