
#include <barrier>
#include <exception>
#include <iostream>
#include <iterator>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>


using namespace std::literals;


auto thread_controller(std::thread&& t) {
    std::cout << t.get_id() << " is running..." << std::endl;
    std::this_thread::sleep_for(5s);
    std::cout << "Execution finished." << std::endl;

    return t;
}

std::thread create_thread(int id) {
    std::thread t([&id]() {
        std::cout << "Custom id " << id << std::endl;
    });
    return t;
}

void poo() {
    std::cout << "Hello from thread";
}

class Task
{
public:
    void operator()() {
        std::cout << "Functor Thread!";
    }
};

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

int num = 0;
std::mutex mutex;

void adder() {

    try {
        for (int i = 0; i < 100'000; i++) {
            std::lock_guard lguard{mutex};
            ++num;
            // throw std::exception();
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

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

std::barrier barrier{3};

void btask1() {
    std::this_thread::sleep_for(3s);
    std::cout << "thread 1 arrived to barrier"
              << "\n";
    barrier.arrive_and_wait();
    std::cout << "thread 1 exited the barrier"
              << "\n";
}

void btask2() {
    std::cout << "thread 2 arrived to barrier"
              << "\n";
    barrier.arrive_and_wait();
    std::cout << "thread 2 exited the barrier"
              << "\n";
}

void btask3() {
    std::this_thread::sleep_for(5s);
    std::cout << "thread 3 arrived to barrier"
              << "\n";
    barrier.arrive_and_wait();
    std::cout << "thread 3 exited the barrier"
              << "\n";
}

void printer_task(std::string str, std::mutex& mtx) {
    for (int i = 0; i < 5; ++i) {
        try {
            std::lock_guard lguard{mtx};
            std::cout << str[0] << str[1] << str[2] << std::endl;
            throw std::exception();
            std::this_thread::sleep_for(50ms);
        } catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
    }
}

void printer_task_alt(std::string str, std::mutex& mtx) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> uqlock{mtx};
        std::cout << str[0] << str[1] << str[2] << std::endl;
        uqlock.unlock();
        std::this_thread::sleep_for(50ms);
    }
}

int main(int argc, char const* argv[]) {

    // std::thread t1(btask1);
    // std::thread t2(btask2);
    // std::thread t3(btask3);
    std::mutex mtx;
    // std::thread t1(printer_task, "abc", std::ref(mtx));
    // std::thread t2(printer_task, "xyz", std::ref(mtx));
    // std::thread t3(printer_task, "def", std::ref(mtx));

    std::thread t1(printer_task_alt, "abc", std::ref(mtx));
    std::thread t2(printer_task_alt, "xyz", std::ref(mtx));
    std::thread t3(printer_task_alt, "def", std::ref(mtx));

    // std::cout << "";

    t1.join();
    t2.join();
    t3.join();

    // for (auto it = jsdict.) {
    //     std::cout << key << value;
    // }
    // t1.join();
    // t2.join();
    // t3.join();
    // basic mutex
    // std::thread t1(adder);
    // std::thread t2(adder);
    // std::thread t3(adder);

    // t1.join();
    // t2.join();
    // t3.join();

    // std::cout << num;


    // try {
    //     std::thread thr(poo);
    //     ThreadGuard tguard(std::move(thr));

    //     throw std::exception();
    // } catch (const std::exception& e) {
    //     std::cerr << e.what() << '\n';
    // }

    // detachment

    // std::thread thr([]() {
    //     std::thread shr([]() {
    //         std::this_thread::sleep_for(5s);
    //         std::cout << "Second child completed" << std::endl;
    //     });
    //     shr.detach();
    //     std::cout << "First child completed" << std::endl;
    // });

    // thr.join();
    // std::this_thread::sleep_for(7s);

    // std::cout << "Main thread is still running and about to finish.";


    // std::thread thr([]() {
    //     std::cout << "Hello, I am a thread" << std::endl;
    // });

    // std::thread thrback = thread_controller(std::move(thr));
    // std::cout << "Grabbed the thread back to main" << std::endl;
    // thrback.join();

    // std::cout << "Main continues normally" << std::endl;

    // std::thread t1 = create_thread(5);
    // t1.join();
    // std::thread t2 = create_thread(12);
    // t2.join();

    // int y = 10;
    // std::thread thr(func, std::ref(y));
    // thr.join();

    // std::thread thr([]() {
    //     ;
    // });
    // std::cout << thr.native_handle() << std::endl;
    // thr.join();
    // std::cout << thr.native_handle();

    // std::cout << thr.get_id() << std::endl;
    // std::cout << std::this_thread::get_id();
    // thr.join();

    // thread pause

    // using namespace std::literals;
    // std::thread thr([]() {
    //     std::cout << "Processing..." << std::endl;
    //     std::this_thread::sleep_for(2s);
    //     std::cout << "Done" << std::endl;
    // });
    // thr.join();

    // std::thread thr([]() {
    //     std::cout << "Hello from child thread";
    // });
    // thr.join();

    // Task task1;
    // std::thread thr(task1);
    // thr.join();
    return 0;
}
