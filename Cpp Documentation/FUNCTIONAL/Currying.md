
```cpp
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

void curry_showcase() {
    // output: 42
    std::cout << sum3(38, 3, 1) << std::endl;
    std::cout << curried_sum3(38)(3)(1) << std::endl;
}
```

## Step 1:
```cpp
auto first = curried_sum3(38);

// Expands to
auto first = [=](int v2) {
	return [=](int v3) {
		return sum3(38, v2, v3);
	}
}
```

## Step 2:
```cpp
auto second = first(3); // curried_sum3(38)(3)

// Expands to
auto second = [=](int v3) {
	return sum3(38, 3, v3);
}
```

## Step 3:
```cpp
auto third = second(1); // curried_sum3(38)(3)(1)

// Expands to
auto third = sum3(38, 3, 1);
```

## Deferred Execution

```cpp
auto deferred_print(const std::string& prefix) {
    return [=](const std::string& message) {
        return [=]() {
            std::cout << prefix << message << std::endl;
        };
    };
}

int main() {
    // Create deferred print functions
    auto print_hello = deferred_print("Hello, ");
    auto print_world = deferred_print("World! ");

    // Execute the deferred print functions
    print_hello("this is ")();
    print_world("Currying")();

    return 0;
}
```