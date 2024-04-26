#include <iostream>

// currying

auto sum3(int v1, int v2, int v3) {
    return v1 + v2 + v3;
}

auto curried_sum3(int v1) {
    return [=](int v2) {
        return [=](int v3) {
            return sum3(v1, v2, v3);
        };
    };
}

int main() {
    std::cout << sum3(38, 3, 1) << std::endl;
    std::cout << curried_sum3(38)(3)(1) << std::endl;
}


// deferred execution

// Curried function for deferred execution
// auto deferred_print(const std::string& prefix) {
//     return [=](const std::string& message) {
//         return [=]() {
//             std::cout << prefix << message << std::endl;
//         };
//     };
// }

// int main() {
//     // Create deferred print functions
//     auto print_hello = deferred_print("Hello, ");
//     auto print_world = deferred_print("World! ");

//     // Execute the deferred print functions
//     print_hello("this is ")();
//     print_world("Currying")();

//     return 0;
// }