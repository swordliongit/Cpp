
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <thread>
#include <tuple>

#include <chrono>

using namespace std::literals;

// Rvalue reference
class Socket
{
};

void roo(Socket&& socket) {
    std::cout << "Will be called with move";
}

void roo(const Socket socket) {
    std::cout << "Will be called with normal";
}


void func(int& ref) {
    std::cout << ref;
}

void pfunc(std::unique_ptr<int> ptr) {
    std::cout << *ptr;
}


int main() {


    // int x = 10;
    // std::unique_ptr<int> ptr(new int(x));
    // pfunc(std::move(ptr));


    int number1 = 15;
    int number2 = 017;        // octal
    int number3 = 0x0f;       // hex
    int number4 = 0b00001111; // binary - C++!4

    // std::cout << number1 << std::endl;
    // std::cout << number2 << std::endl;
    // std::cout << number3 << std::endl;
    // std::cout << number4 << std::endl;

    // tuple
    std::tuple<std::string, int> student = {"William", 0b0001100};
    std::tuple<std::string, int> student_2 = {"Jackob", 0b0011101};

    // std::cout << std::get<0>(student) << std::endl;
    // std::cout << std::get<1>(student) << std::endl;

    const auto [name_1, grade] = student;
    const auto [name_2, grade_2] = student_2;

    // dict
    std::map<std::string, std::string> student_names = {{"name_1", name_1}, {"name_2", name_2}};

    for (const auto& [key, value] : student_names) {
        // std::cout << key << ": " << value << std::endl;
    }

    // lambda
    auto foo = [](int a, int b) -> int {
        return a * b;
    };
    // std::cout << foo(5, 10);

    int a, b;
    // std::cin >> a >> b;

    std::function<int(int, int)> poo = [&a, &b](int, int) -> int {
        return a * b;
    };

    // std::cout << poo(a, b);

    bool test = false;
    // std::cout << test << " " << std::boolalpha << test << std::boolalpha
    //   << true;

    // Formatting Output
    // std::cout << std::left;
    // std::cout << std::setw(10) << "Hello World " << std::setw(14)
    //           << "How are you?";
    // std::cout << std::left;
    // std::cout << std::setfill('-');
    // std::cout << std::setw(15) << "Firstname" << std::setw(15) << "Lastname" << std::endl;
    // std::cout << std::setw(15) << "Sword" << std::setw(15) << "Lion" << std::endl;

    double num = 2006.0;
    // std::cout << std::dec << num << std::endl;
    // std::cout << std::hex << num << std::endl;
    // std::cout << std::oct << num << std::endl;

    // std::cout << std::uppercase;
    // std::cout << std::hex << num << std::endl;

    // std::cout << std::scientific;
    // std::cout << num;

    // Literals and Chrono
    // using namespace std::literals;
    // std::cout << 2s << " "
    //           << " " << 20ms << " " << 50us;

    // Filtering
    std::vector<int> vec{1, 10, 123, 5, -34};
    auto t = std::count_if(vec.begin(), vec.end(), [](int n) {
        return n > 8;
    });
    // std::cout << t;

    // Capture by move
    [vec_strings = std::move(vec)]() {
        // std::cout << vec_strings.size() << std::endl;
    }();
    // std::cout << vec.size();

    // Random numbers
    std::mt19937 mt;
    std::uniform_int_distribution<int> uid(0, 100);
    std::uniform_real_distribution<double> did(0, 1);

    // for (int i = 0; i < 5; i++) {
    //     std::cout << uid(mt) << std::endl;
    // }

    // Threads
}
