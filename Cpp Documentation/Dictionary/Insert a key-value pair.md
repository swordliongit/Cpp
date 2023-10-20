```cpp
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
```