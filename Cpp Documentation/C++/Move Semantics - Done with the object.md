
1. You are done with the object and want to pass it to another place
2. You want to avoid copying the object
3. Built-in types are regarded as moveable but are always copied
4. An argument can be moved if;
	- it's an rvalue
	- its type defines move operators
5. 


```cpp
// Rvalue reference
void foo(Egclass&& x) {
    std::cout << x;
}

Egclass y;
foo(y); // ERROR

foo(std::move(y)); // y is casted into rvalue reference &&

// Usage of y here is unpredictable, Compiler can freely use its resources
```

```cpp
class Socket
{
public:
    Socket() {
        std::cout << "Default Constructor";
    }
    Socket(Socket&& socket) {
        std::cout << "Move Constructor";
    }
};

Socket socket; // Default
Socket socket2 = std::move(socket); // Move
```

![[Screenshot 2024-04-10 121648.png]]![[Screenshot 2024-04-10 201341.png]]![[Screenshot 2024-04-10 202028.png]]