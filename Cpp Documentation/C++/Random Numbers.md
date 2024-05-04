
```cpp
#include <random>

std::mt19937 mt;
std::uniform_int_distribution<int> uid(0, 100);
std::uniform_real_distribution<double> did(0, 1);

for (int i = 0; i < 5; i++) {
	std::cout << uid(mt) << std::endl;
}
```

```cpp
// Create a random device to seed the generator
std::random_device rd;
// Create a random number generator engine using the random device as a seed
std::mt19937 gen(rd());
// Define a uniform distribution for integers between 0 and 10.0
std::uniform_real_distribution<> dis(0, 10.0f);

// Generate a random number
double random_number = dis(gen);
std::cout << random_number;
```