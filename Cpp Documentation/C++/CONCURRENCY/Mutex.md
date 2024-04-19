- lock()
	- Tries to lock the mutex
	- If not successful, waits until it locks the mutex
- try_lock()
	- Tries to lock the mutex
	- Returns True if the mutex is locked
	- Returns False otherwise
	- Returns immediately if not successful
- unlock()
	- Releases the lock on the mutex

```cpp
#include <mutex>
```

## Example 1:
```cpp
int num = 0;
std::mutex mutex;

void adder() {

    for (int i = 0; i < 100'000; i++) {
        mutex.lock();
        ++num;
        mutex.unlock();
    }
} 

{
std::thread t1(adder);
std::thread t2(adder);
std::thread t3(adder);

t1.join();
t2.join();
t3.join();

std::cout << num; // 300'000
}
```
---

## Example 2:
```cpp
void task1() {
    mutex.lock();
    std::cout << "Task 1 locked the mutex" << std::endl;
    std::this_thread::sleep_for(2s);
    mutex.unlock();
    std::cout << "Task 1 unlocked the mutex" << std::endl;
}

void task2() {
    std::this_thread::sleep_for(500ms);
    while (!mutex.try_lock()) {
        std::cout << "Task 2 trying to lock the mutex" << std::endl;
        std::this_thread::sleep_for(200ms);
    }
    std::cout << "Task 2 locked the mutex" << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << "Task 2 unlocked the mutex" << std::endl;
}

{
std::thread t1(task1);
std::thread t2(task2);

t1.join();
t2.join();
}
```

```
Task 1 locked the mutex
Task 2 trying to lock the mutex
Task 2 trying to lock the mutex
Task 2 trying to lock the mutex
Task 2 trying to lock the mutex
Task 2 trying to lock the mutex
Task 2 trying to lock the mutex
Task 2 trying to lock the mutex
Task 2 trying to lock the mutex
Task 1 unlocked the mutex
Task 2 locked the mutex
Task 2 unlocked the mutex
```
---

## Internally Synchronized Class Example:
```cpp
class Vector
{
    std::mutex mutex;
    std::vector<int> vec;

public:
    void push_back(const int& i) {
        mutex.lock();
        vec.push_back(i);
        mutex.unlock();
    }
};
```

