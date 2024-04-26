- ==Multiple locking==: A thread locks and std::mutex, it must not call lock() again until it has called unlock()
	- Undefined behaviour
	- Usually the program blocks indefinitely

## std::recursive_mutex - Bad Example

- Its lock() member function can be called recursively
- For each lock() call there must be eventually be an unlock() call
- Normally a sign of bad design
```cpp
// Example of std::recursive_mutex
#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rmut;

int bad_factorial(int n)
{
	if (n <= 1) {
		std::cout << "Returning " << 1 << '\n';
		return 1;
	}
	
	std::lock_guard<std::recursive_mutex> lck_guard(rmut);
	//rmut.lock();
	
	// Start of critical section
	int retval = n*bad_factorial(n-1);
	std::cout << "Returning " << retval << std::endl;
	// End of critical section
	
	//rmut.unlock();
	return retval;
}

int main()
{
	std::thread thr1(bad_factorial, 10);
	std::thread thr2(bad_factorial, 11);
	
	thr1.join(); thr2.join();
}
```

## std::timed_mutex
- Similar to std::mutex but with extra member functions
	- try_lock_for()
		- Keep trying to lock the mutex for a specified duration
	 - try_lock_until()
		 - Keep trying to lock the mutex until a specified time
- These return bool
	- True if the mutex was locked
	- Otherwise false

```cpp
void task2()
{
	std::this_thread::sleep_for(500ms);
	std::cout << "Task2 trying to lock the mutex\n";

	// Try for 1 second to lock the mutex
	while (!the_mutex.try_lock_for(1s)) {
		// Returned false
		std::cout << "Task2 could not lock the mutex\n";

		// Try again on the next iteration
	}

	// Returned true - the mutex is now locked

	// Start of critical section
	std::cout << "Task2 has locked the mutex\n";
	// End of critical section

	the_mutex.unlock();
}
```



## std::timed_mutex with std::unique_lock
 - bool try_lock_for()
- bool try_lock_until
	- These are forwarded to the wrapped mutex, will only compile if the mutex supports the operation

```cpp
void task2() {
    std::this_thread::sleep_for(500ms);
    std::cout << "Task2 trying to lock the mutex\n";

    std::unique_lock<std::timed_mutex> uniq_lck(the_mutex, std::defer_lock);

    // Try for 1 second to lock the mutex
    while (!uniq_lck.try_lock_for(1s)) {
        // Returned false
        std::cout << "Task2 could not lock the mutex\n";

        // Try again on the next iteration
    }

    // Returned true - the mutex is now locked

    // Start of critical section
    std::cout << "Task2 has locked the mutex\n";
    // End of critical section
}
```