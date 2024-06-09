
## Sum of iterator elements: accumulate
```cpp
// Sum of iterator elements:
std::cout << std::accumulate(vect.begin(), vect.end(), 1) << "\n";
```

## Distance Between Two Locations: distance
```cpp
// Distance between 2 locations inside the iterator
std::cout << std::distance(vect.begin(), vect.end()) << "\n";
```

## Advancing the Iterator: advance
```cpp
// Moving to locations on the iterator
std::vector<int> vect{1, 2, 3, 4, 5};
auto it = vect.begin();

std::advance(it, 2);
std::cout << *it << "\n"; // 3
```

## Finding an Element: find
```cpp
std::list<int> some_list;
auto it = std::find(some_list.begin(), some_list.end(), value_to_find);

if (it != some_list.end()) {
	// element is found
}
```