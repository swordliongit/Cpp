- Shared data must be initialized once. If we'd use a mutex to lock the initialization, threads would have to be locked and unlocked each time they hit the initialization part even if the object is already initialized. To overcome this, we must use a static variable that has to be initialized only once and this is achieved using C++11 singleton ( Meyers Singleton) which guarantees that the static variable is initialized only once and it's thread safe.

singleton.hpp
```cpp
// Singleton class definition
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

class Singleton
{
public:
    // The copy and move operators are deleted
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton &&) = delete;

    Singleton() {
        std::cout << "Initializing Singleton\n";
    }
};

// Function to obtain the Singleton object
Singleton &get_Singleton();

#endif //SINGLETON_H
```

singleton.cpp
```cpp
// Singleton class implementation (Meyers Singleton)
// Uses C++11's guarantees about initializing static variables
#include "cpp11_singleton.h"

// Function to obtain the Singleton object
Singleton &get_Singleton() {
    // Initialized by the first thread that executes this code, other threads won't initialize this and skip that part.
    static Singleton single;
    return single;
}
```

main.cpp
```cpp
// Test program for Meyers Singleton
#include "cpp11_singleton.h"
#include <thread>
#include <vector>

void task() {
    Singleton &single = get_Singleton();
    std::cout << &single << std::endl;
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i)
        threads.push_back(std::thread(task));

    for (auto &thr : threads)
        thr.join();
}
```

## Lazy Initialization
- Common pattern in functional programming
- A variable is only initialized when it is first used
- This is useful when the variable is expensive to construct
	- e.g. it sets up a network connection
- Can be used in multi-threaded code
	- But we need to avoid data races

This example always locks the mutex even though we only need to lock the mutex when initializing it because we don't modify it elsewhere.
```cpp
// Lazy initialization (multi-threaded)
// Inefficient (always locks the mutex)
#include <mutex>

class Test {
	// ...
public:
	void func() { /*...*/ }
};

Test *ptest = nullptr;         // Variable to be lazily initialized
std::mutex mut;

void process() {
    std::unique_lock<std::mutex> uniq_lck(mut);       // Protect ptest

    if (!ptest)
        ptest = new Test;
    uniq_lck.unlock();
    ptest->func();
}
```

This leads us to second example. In this case we hit a data race:
- Thread A checks ptest, which is null
- Thread B checks ptest, which is null
- Thread B locks the mutex
- Thread B initiliazes ptest
- Thread B unlocks the mutex
- Thread A locks the mutex
- Thread A initializes ptest
```cpp
class Test {
	// ...
public:
	void func() { /*...*/ }
};

Test *ptest = nullptr;         // Variable to be lazily initialized
std::mutex mut;

void process() {

    if (!ptest) {
	    std::unique_lock<std::mutex> uniq_lck(mut); 
        ptest = new Test;
    }
    uniq_lck.unlock();
    ptest->func();
}
```

### Double-checked Locking
- We double check to ensure there are no data races. But this time we hit another nastier data race:
```cpp
// Lazy initialization (multi-threaded)
// Uses the Double-checked Locking algorithm
#include <mutex>

class Test {
	// ...
public:
	void func() { /*...*/ }
};

Test *ptest = nullptr;            // Variable to be lazily initialized
std::mutex mut;

void process() {
    if (!ptest) {                     // First check of ptest
        std::lock_guard<std::mutex> lck_guard(mut);
        
        if (!ptest)                  // Second check of ptest
            ptest = new Test;   // Initialize ptest
    }
     ptest->func();
}

```

![[Screenshot 2024-04-28 183059.png]]
![[Screenshot 2024-04-28 183205.png]]

### Solution with call_once
- A given function is only called once
- It is done in one thread
- The thread cannot be interrupted until the function call completes
- We use it with a global instance of std::once_flag
- We pass the instance and the function to std::call_once()
- less overhead than a mutex

```cpp
class Test
{
    // ...
public:
    Test() {
        std::cout << "Test constructor called\n";
    }

    void func() {
        /*...*/
    }
};

Test *ptest = nullptr; // Variable to be lazily initialized

std::once_flag ptest_flag; // The flag stores synchronization data

void process() {
    // Pass a callable object which performs the initialization
    std::call_once(ptest_flag, []() {
        ptest = new Test;
    });
    ptest->func();
}

int main() {
    std::thread thr1(process);
    std::thread thr2(process);
    thr1.join();
    thr2.join();
}
```

### Solution with singleton
```cpp
// Lazy initialization (multi-threaded)
// Uses Meyers singleton
#include <mutex>
#include <thread>
#include <iostream>

class Test {
	// ...
public:
	Test()
	{
		std::cout << "Test constructor called\n";
	}

	void func()
	{
		/*...*/
	}
};

void process()
{
	static Test ptest;            // Variable which is lazily initialized
	ptest.func();
}

int main()
{
	std::thread thr1(process);
	std::thread thr2(process);
	thr1.join(); thr2.join();
}
```

![[Screenshot 2024-04-30 202916.png]]
![[Screenshot 2024-04-30 203040.png]]