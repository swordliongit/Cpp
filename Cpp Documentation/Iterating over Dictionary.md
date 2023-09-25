```cpp
std::map<std::string, int> dict{{"first", 1}, {"second", 2}};
for (auto iter = dict.begin(); iter != dict.end(); iter++) {
	std::cout << iter->first << ": " << iter->second << std::endl;
}
```