#include <iostream>
#include <map>
#include <tuple>

void printer(std::tuple<int, int, int> selection) {
    std::cout << std::get<0>(selection) << std::get<1>(selection)
              << std::get<2>(selection) << std::endl;

    const auto [f, s, t] = selection; // c++ 17
    std::cout << f << s << t << std::endl;

    int first, second, third;
    std::tie(first, second, third) = selection;
    std::cout << first << second << third;
}

void parser(std::map<int, std::string> &dict) {
    for (const auto &[key, value] : dict) {
        std::cout << key << ": " << value << std::endl;
    }
}

int main() {
    int key;
    std::string value;

    std::map<int, std::string> dict = {};
    std::cout << "Enter the first set of key value pair: ";
    std::cin >> key >> value;
    dict.insert({key, value});
    std::cout << "Enter the second set of key value pair: ";
    std::cin >> key >> value;
    dict.insert({key, value});

    parser(dict);
}
