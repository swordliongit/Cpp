#CONCURRENCY
[[Threads]]

- ==Task parallelism==:  Divide a single task into parts and run each in parallel.
- ==Data parallelism==: Each thread performs the same operation on different parts of the data.
- ==Running threads in background==: detach()
- ==Abstraction penalty==:
- ==Data Race==: Occurs when multiple threads access the same memory location concurrently, and at least one thread modifies the data, without synchronization.
- ==Race Condition==: A broader term referring to any situation where the program's behavior depends on the timing and order of events.
- ==Oversubscription==: Running more threads than the hardware can support.