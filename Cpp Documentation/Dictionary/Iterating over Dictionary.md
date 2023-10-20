```cpp
// Iterate using C++17 facilities
    for (const auto& [key, value] : m)
        std::cout << '[' << key << "] = " << value << "; ";
        
// C++11 alternative:
  for (const auto& n : m)
      std::cout << n.first << " = " << n.second << "; ";

// C++98 alternative:
  for (std::map<std::string, int>::const_iterator it = m.begin(); it != m.end(); ++it)
      std::cout << it->first << " = " << it->second << "; ";
 
```
