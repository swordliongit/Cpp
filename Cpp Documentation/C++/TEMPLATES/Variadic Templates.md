```cpp
template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest);
```
- ==class...== or ==typename...== indicates that the following parameter represents a list of zero or more types
- Args is a template parameter pack; rest is a function parameter pack
- Args represents zero or more template type parameters
- rest represents zero or more function parameters


## Example:
```cpp

#include <iostream> 
  
template<typename... Types> 
int sum(Types&&... args) 
{ 
    return (args + ...); // Performs a binary right fold with addition 
} 
  
int main() 
{ 
    int result = sum(1, 2, 3, 4); 
    std::cout << "Result: " << result << std::endl; 
    return 0; 
}
```

### Multi-type function arguments and vector
```cpp

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
```