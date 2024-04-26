
#include <iostream>
#include <variant>
#include <vector>

template <typename... Types>
void vard(Types... args) {
    // Create a vector of std::variant to handle different types
    std::vector<std::variant<Types...>> vec;

    // Use a fold expression to push each argument into the vector
    (vec.push_back(args), ...);

    // Print the vector contents
    std::cout << "Vector contains: ";
    for (const auto& elem : vec) {
        std::visit(
            [](auto&& val) {
                std::cout << val << " ";
            },
            elem);
    }
    std::cout << std::endl;
}

int main() {
    // Call vard with different types of arguments
    vard(1, 2.5, 'a', "hello");
    vard(3.14, true, 42);

    return 0;
}