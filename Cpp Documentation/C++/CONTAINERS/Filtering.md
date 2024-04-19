
```cpp
std::vector<int> vec{1, 10, 123, 5, -34};
auto numbers_larger_than_8 = std::count_if(vec.begin(), vec.end(), [](int n) {
	return n > 8;
});
std::cout << numbers_larger_than_8; // 2
```