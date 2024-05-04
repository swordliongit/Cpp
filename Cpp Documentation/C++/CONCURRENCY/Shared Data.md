- ==Criticial Section==: A region of code that must be executed by one thread at a time. Shared data, network connection, hardware device. Thread "enters" and "leaves" the critical section.
- ==Locking Protocol==: One thread can enter the c.s.  All other threads are locked out. One of the other threads can enter after leaving the c.s.

 
[[Mutex]]
[[Critical Section Exceptions - lock_guard - unique_lock]]
[[Shared Data Initialization - Lazy init, call_once]]