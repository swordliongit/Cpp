
## Pointers and const

### ==Pointer to Const== : Restricting change of the value in pointed location through dereferencing but the pointed location can be changed

```cpp
int n = 5;
int m = 10;
const int* ptr = &n;

ptr = &m; // OK
*ptr = 8; // ERROR
```

### ==Const Pointer== : Restricting pointed location change but value in the location can be changed through dereferencing

```cpp
int n = 5;
int m = 10;
int* const ptr = &n;

ptr = &m; // ERROR
*ptr = 8; // OK
```

### Neither location nor value in the location can be changed

```cpp
int n = 5;
int m = 10;
const int* const ptr = &n;

ptr = &m; // ERROR
*ptr = 8; // ERROR
```