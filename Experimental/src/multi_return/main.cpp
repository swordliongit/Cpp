#include <iostream>
#include <tuple>
#include <vector>

std::tuple<int, int> getFirstLast(std::vector<int> ar) {
    int first = -1;
    int last = -1;
    if (ar.size() > 0) {
        first = ar[0];
        last = ar[ar.size() - 1];
    }
    return std::make_tuple(first, last);
}

int main() {
    std::vector<int> ar{2, 3, 5};
    auto result = getFirstLast(ar);
    int first, last;
    std::tie(first, last) = result;
    // first is 2
    // last is 5
    std::cout << first << ";" << last;
}