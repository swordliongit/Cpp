- The destructors are called for all objects in the scope
- The program flow jumps into the catch handler
- The unlock call is never executed
- The mutex remains locked
- All other threads which are waiting to lock the mutex are blocked
- If main() is joined on these blocked threads, main() will be blocked as well, the entire program gets blocked

```cpp
try{
	mutex.lock(); // Entering critical section, lock the mutex
	// Critical section throws exception
	mutex.unlock(); // never gets called
} catch(const std::exception& e) {
	...
}
```

## Solution with Mutex Wrapper Class lock_guard
- Because the unlock has to be called no matter what, for the program to work correctly even when an exception is thrown, we don't directly use a std::mutex.

```cpp
std::lock_guard<std::mutex> lck_guard(task_mutex);
std::lock_guard lck_guard(task_mutex); // C++17, compiler deduces the type
```

```cpp
for(int i = 0; i < 5; ++i) {
	// this calls task_mutex.lock()
	std::lock_guard<std::mutex> lck_guard(task_mutex);
	// critical section
	std::cout << str[0] << str[1] << str[2] << std::endl;
	// end of critical section
} // calls ~std::lock_guard()
```

- We have no way to unlock the mutex before it gets destroyed by the function exiting. It's solved using ==unique_lock==
## unique_lock

Constructor's optional second arguments:
- std::try_lock
	- Calls the mutex's try_lock() member function
	- The owns_lock() member function checks if the mutex is locked
- std::defer_lock
	- Does not lock the mutex
	- Can lock it later by calling the lock() member function
	- Or by passing the std::unique_lock object to std::lock()
- std::adopt_lock
	- Takes a mutex that is already locked
	- Avoids locking the mutex twice
- bool try_lock_for()
- bool try_lock_until
	- These are forwarded to the wrapped mutex, will only compile if the mutex supports the operation

```cpp
void printer_task_alt(std::string str, std::mutex& mtx) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> uqlock{mtx}; // lock called
        std::cout << str[0] << str[1] << str[2] << std::endl;
        uqlock.unlock();
        std::this_thread::sleep_for(50ms);
    }
}
```

## unique_lock vs lock_guard
- std::unique_lock is much more flexible but 
	- Requires slightly more storage
	- Slightly slower
- Use lock_guard to lock a mutex for an entire scope
- Use unique_lock if you need to unlock within the scope
- Use unique_lock if you need the extra features