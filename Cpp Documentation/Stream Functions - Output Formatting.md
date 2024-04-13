```cpp
#include <iomanip>
```
## Displaying Bool Values
```CPP
std::cout << std::boolalpha << false;
```

## Formatting
```cpp
std::cout << std::setw(10) << "Hello World " << std::setw(14) << "How are you?";
```

```
Hello World   How are you?
```
---

```cpp
std::cout << std::right;
std::cout << std::left;
```

```cpp
std::cout << std::left;
std::cout << std::setfill('-');
std::cout << std::setw(15) << "Firstname" << std::setw(15) << "Lastname" << std::endl;
std::cout << std::setw(15) << "Sword" << std::setw(15) << "Lion" << std::endl;
```

```
Firstname------Lastname-------
Sword----------Lion-----------
```
---

```cpp
std::cout << std::showpos;
std::cout << 34; // +34

std::cout << std::noshowpos;
std::cout << 34; // 34
```

```cpp
int num = 120045;
std::cout << std::dec << num << std::endl;
std::cout << std::hex << num << std::endl;
std::cout << std::oct << num << std::endl;
```

```cpp
120045
1d4ed
352355
```

```cpp
std::cout << std::uppercase;
std::cout << std::hex << num << std::endl; // 1D4ED
```
---
## Scientific Notation
```cpp
double num = 2006.0;
std::cout << std::scientific;
std::cout << num; // 2.006000e+03
```

## Reversing Floating Point Output
```cpp
std::cout.unsetf(std::ios::scientific | std::ios::fixed);
```