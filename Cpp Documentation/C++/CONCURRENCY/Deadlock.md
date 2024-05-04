- Thread A locks mutex 1 and waits for mutex 2
- Thread B locks mutex 2 and waits for mutex 1
- Both threads kept waiting, deadlocking each other

## Avoidance
- Make the threads acquire locks in the same order
	- Relies on the programmer
- Lock multiple mutexes in a single operation
	- Thread A locks mut1 and mut2
	- Thread B cannot lock mut2 or mut1 during this operation
	- A much better solution
- C++ provides library features for this


### scoped_lock
- C++17
- Very similar to std::lock_guard, except it can lock more than one mutex at the same time
- The mutexes are locked in the order given in the constructor call
	- In the destructor, the mutexes are unlocked in the reverse order
- This avoids the possibility of deadlock with multiple mutexes

```cpp
// Use std::scoped_lock to avoid deadlock
// All the mutexes are locked in a single operation
// Requires C++17 compiler
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>	

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
	std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
	std::scoped_lock scoped_lck(mut1, mut2);
	std::cout << "Thread A has locked mutexes 1 and 2\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread A releasing mutexes 1 and 2...\n";
}

void funcB()
{
	std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
	std::scoped_lock scoped_lck(mut2, mut1);
	std::cout << "Thread B has locked mutexes 2 and 1\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

int main()
{
	std::thread thrA(funcA);
	std::thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
```


### Before C++ 17, std::lock and adopt_lock
- It can lock multiple mutexes in a single operation
	- std::lock(mut1, mut2);
- But we have to unlock the mutexes manually

- std::unique_lock can "adopt" the locks
	- Pass the std::adopt_lock option to its constructor
	- The std::unique_lock object now owns the lock
```cpp
// Lock two mutexes;
std::lock(mut1, mut2);

//Each lock is adopted by a unique_lock object
std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);
std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);
```

```cpp
// Use std::adopt_lock to avoid deadlock
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
	std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
	std::lock(mut1, mut2);				               // Lock both mutexes
	std::cout << "Thread A has locked mutexes 1 and 2\n";
	
	// Adopt the locks
	std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);   // Associate each mutex
	std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);   // with a unique_lock
	std::cout << "Thread A has adopted the locks\n";
	
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread A releasing mutexes 1 and 2...\n";
}

void funcB() {
	std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
	lock(mut2, mut1);				               // Lock both mutexes
	std::cout << "Thread B has locked mutexes 2 and 1\n";
	
	// Adopt the locks
	std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);   // with a unique_lock
	std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);   // Associate each mutex
	std::cout << "Thread B has adopted the locks\n";
	
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

int main() {
	std::thread thrA(funcA);
	std::thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
```