// Example using std::promise and std::future
// to throw an exception from a producer thread
// to a consumer thread
#include <future>
#include <iostream>
#include <thread>
#include <exception>
#include <chrono>

// The producer's task function takes a std::promise as argument
void produce(std::promise<int>& px)
{
	using namespace std::literals;
	int x = 42;
	std::this_thread::sleep_for(2s);
		
	// Code that may throw
	if (1) {
		px.set_exception(std::make_exception_ptr(std::out_of_range("Oops")));
		return;
	}
	
	// No exception - store the result in the shared state
	std::cout << "Promise sets shared state to " << x << '\n';
	px.set_value(x);
}

// The consumer's task function takes an std::future as argument
void consume(std::future<int>& fx)
{
	std::cout << "Future calling get()...\n";
	try {
		// Get the result from the shared state - may throw
		int x = fx.get();
		std::cout << "Future returns from calling get()\n";
		std::cout << "The answer is " << x << '\n';
	}
	catch(std::exception& e) {
		// Exception thrown - get it from the shared state
		std::cout << "Exception caught: " << e.what() << '\n';
	}
}

int main()
{
	// Create an std::promise object
	// This creates an associated std::future object
	// and sets up a shared state between them
	std::promise<int> prom;
	
	// Get the future associated with the promise
	std::future<int> fut = prom.get_future();
	
	// Start the threads
	// The producer task function takes the promise as argument
	std::thread thr_producer(produce, std::ref(prom));
	
	// The consumer task function takes the future as argument
	std::thread thr_consumer(consume, std::ref(fut));
	
	thr_consumer.join();
	thr_producer.join();
}
