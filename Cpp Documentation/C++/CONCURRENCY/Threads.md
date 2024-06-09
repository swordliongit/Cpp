[[Thread Management and Interface]]
[[Shared Data]]

- Move-only class following RAII
- Constructor acquires a resource and destructor releases it


```cpp
#include <thread>
```


- When the main function ends, the child thread's destructor is called that calls std::terminate() that kills all threads, including the main thread. So this program will cause errors.
- To avoid this, we have to use join() to block the main thread from further execution and wait for the child thread to finish.
```cpp
#include <thread>
int main() {
	 std::thread thr([]() {
        std::cout << "Hello from child thread";
    });
}
```

```cpp
int main() {
	 std::thread thr([]() {
        std::cout << "Hello from child thread";
    });
	thr.join();
}
```


## Thread Task Object - Functor Thread

```cpp
class Task
{
public:
    void operator()() {
        std::cout << "Functor Thread!";
    }
};

Task task1; // this object is now callable due to () operator overload.
std::thread thr(task1); // pass the callable object to thread constructor.
thr.join();
```


## Reference Arguments

- thread launch arguments are copied to the function by default and threads don't check parameters of the function, so we have to explicitly tell the thread that we need the variable passed as a reference instead of value.
- ==std::cref== for const reference

```cpp
void func(int& ref) {
    std::cout << ref;
}

int y = 10;
std::thread thr(func, std::ref(y));

thr.join();
```

