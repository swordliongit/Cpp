
```cpp
#include <random>

std::mt19937 mt;
std::uniform_int_distribution<int> uid(0, 100);
std::uniform_real_distribution<double> did(0, 1);

for (int i = 0; i < 5; i++) {
	std::cout << uid(mt) << std::endl;
}
```