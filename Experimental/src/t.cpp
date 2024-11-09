#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>
#include <vector>

#include <future>
#include <functional>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    // lambda templates
    auto L = []<typename T>(std::vector<T>& vec) {
        for (auto& el : vec)
            {
                std::cout << el << std::endl;
            }
    };

    std::vector vec{1, 10, 200, 23, 412};
    L(vec);

    // packaged task
    std::packaged_task<int(int, int)> task(add);
    std::future<int> result = task.get_future();

    task(2, 3);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Result: " << result.get() << std::endl;
}
