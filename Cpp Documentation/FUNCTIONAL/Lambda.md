
- Type is callable object, read as "lambda"
- Can be directly invoked with ()
- Capturing ==this== lets lambda access to all member functions


## Lambda Local Variables - C++14

- Implicitly auto
- Must be initialized

```cpp
[y = 2](int x) {
	return x + y;
};

int z = 5;
[y = z + 1](int x) {
	return x + y;
};
```

### Capture by Move

- type of vec_strings is deduced as std:.vector<std::string>
- std::vector's move constructor is called to initialize vec_strings
- The vector elements are now owned by vec_strings

```cpp
std::vector<std::string> strings(5);

[vec_strings = std::move(strings)]() {

};
```

```cpp
std::vector<int> vec(5);
[vec_strings = std::move(vec)]() {
	std::cout << vec_strings.size() << std::endl; // 5
}();

std::cout << vec.size(); // 0
```