- We may want readers to not block each other because they don't modify the shared data. But with normal mutexes it's not possible. Reader threads kept waiting unnecessarily, if the reading operation takes time, the program will slow down significantly.
## Read-Write Lock
- It would be useful to have "selective" locking
	- Lock when there is a thread which is writing
	- Do not lock when there are only reading threads
	- Often called a "read-write" lock


## shared_mutex

- It can be locked in ==two== different ways:
- Exclusive lock
	- No other thread may acquire a lock
	- No other thread can enter a critical section
	- lock()
	- try_lock()
	- unlock()
- Shared lock
	- Other threads may acquire a shared lock
	- They can execute critical sections concurrently
	- lock_shared()
	- try_lock_shared()
	- unlock_shared()

```cpp
#include <shared_mutex>
```

```cpp
std::shared_mutex shmut;

void write() {
	std::lock_guard lck_guard(shmut); // Write thread with exclusive lock
	...
}

void read() {
	std::shared_lock sh_lck(shmut); // Read thread with shared lock
	...
}
```

### Pros and Cons

- Uses more memory than std::mutex
- Slower than std::mutex
- Best suited to situations where:
	- Reader threads greatly outnumber writer threads
	- Read operations take a long time