
## Thread Handle - native_handle()

- Used internally by the system's thread implementation
- Needed when making calls into the implementation's API
```cpp
std::thread thr([]() {
        ;
});
std::cout << thr.native_handle();
thr.join();
```

## Thread Id - get_id(), std::this_thread::get_id()

- Used internally by the system's implementation
- A new thread may get the id of an earlier thread which has completed

```cpp
 std::thread thr([]() {
        ;
});
std::cout << thr.get_id() << std::endl; // 2
std::cout << std::this_thread::get_id(); // 12
```


## Pausing Threads - sleep_for()
- Works for single threaded programs too. Pauses thread that executes main()

```cpp
// C++14
using namespace std::literals;

std::thread thr([]() {
	std::cout << "Processing..." << std::endl;
	std::this_thread::sleep_for(2s);
	std::cout << "Done" << std::endl;
});

// C++11
std::thread thr([]() {
	std::cout << "Processing..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "Done" << std::endl;
});

```


## Passing and Returning Threads

```cpp
void thread_controller(std::thread&& t) {
    std::cout << t.get_id() << " is running..." << std::endl;
    std::this_thread::sleep_for(5s);
    std::cout << "Execution finished." << std::endl;

    t.join();
}

std::thread thr([]() {
	std::cout << "Hello, I am a thread" << std::endl;
});

thread_controller(std::move(thr));
```

- Compiler automatically returns the thread with std::move
```cpp
std::thread create_thread(int id) {
	std::thread t([&id]() {
		std::cout << "Custom id " << id << std::endl;
	});
	return t;
}

std::thread t1 = create_thread(5);
t1.join();
std::thread t2 = create_thread(12);
t2.join();
```

## Thread Exception Handling

- Each thread has its own execution stack
- The stack is unwound when the thread throws an exception
	- Destructors for all objects in scope are called
	- The program moves up the thread's stack until it finds a suitable handler
	- If no handler is found, the program is terminated
- Other threads in the program can't catch the exception
- Exceptions can only be handled in the thread where they occur
Works as expected:
```cpp
void poo() {
    try {
        throw std::exception();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

std::thread thr(poo);
thr.join();
```

```
std::exception
```

```cpp
void poo() {
    throw std::exception();

    std::cout << "Hello from thread";
}

try {
	std::thread thr(poo);
	thr.join();
} catch (const std::exception& e) {
	std::cerr << e.what() << '\n';
}
```

```
terminate called after throwing an instance of 'std::exception'
  what():  std::exception
```

### Exception in Parent Thread - Danger

- The destructors are called for every object in scope
	- Including std::thread's destructor
	- This checks whether join() or detach() have been called
	- If neither, it calls std::terminate()
- We must call either join() or detach() before the thread is destroyed in all paths through the code

```cpp
int main() {
	try {
        std::thread thr(poo);
        
        throw std::exception(); // all of the program is terminated because thr can't be joined and it will call std::terminate()
        
        thr.join(); // couldn't reach here
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
```

### Solution with Thread Guard

- After main thread throws an exception, the destructor of the tguard object will be called that will join() the controlled thread that is thr so it will gracefully be destroyed, preventing it from calling std::terminate()

```cpp
class ThreadGuard
{
    std::thread thr;

public:
    explicit ThreadGuard(std::thread&& thrpassed) : thr(std::move(thrpassed)) {
    }

    ~ThreadGuard() {
        if (thr.joinable()) {
            thr.join();
        }
    }

    ThreadGuard(const ThreadGuard&) = delete; // Deleted copy constructor to prevent copying
    ThreadGuard& operator=(const ThreadGuard&) = delete;
};

int main(int argc, char const* argv[]) {

    try {
        std::thread thr(poo);
        ThreadGuard tguard(std::move(thr));

        throw std::exception();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
```

## Thread Detachment

- The main thread will continue executing and it won't terminate the program. The main thread can end before the child thread.

```cpp
{
	std::thread shr([]() {
		std::this_thread::sleep_for(5s);
		std::cout << "Child completed" << std::endl;
	});
	shr.detach();
	// main thread will complete independent of the child
}
```

## Launching Multiple Threads

```cpp
std::vector<std::thread> threads;

for (int i = 0; i < 20; ++i)
	threads.push_back(std::thread(func));
```