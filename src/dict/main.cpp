#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> dict{{1, "first"}, {2, "second"}};

    for (auto iter = dict.begin(); iter != dict.end(); iter++) {
        std::cout << iter->first << ": " << iter->second;
    }
}