- unique_ptr is a smart pointer that does automatic garbage collection
- move-only class


```cpp
std::unique_ptr<int> ptr(new int(30));
// C++14, calls new() internally
std::unique_ptr<int> ptr = std::make_unique<int>(30);
```

```cpp
void pfunc(std::unique_ptr<int> ptr) {
    std::cout << *ptr;
}

int x = 10;
std::unique_ptr<int> ptr(new int(x));
pfunc(std::move(ptr));
```