#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <bitset>
#include <random>


using namespace std::literals;

int main() {


    std::bitset<8> flags;

    std::bitset<8> lower_mask = 0b00001111;
    std::bitset<8> upper_mask = 0b11110000;

    flags |= lower_mask;

    std::cout << flags << "\n";

    flags.reset();
    flags = flags | upper_mask;

    flags = flags & std::bitset<8>(0b10000000);

    std::cout << flags << "\n";

    int n = static_cast<int>(flags.to_ulong());

    std::cout << n;


    return 0;
}
