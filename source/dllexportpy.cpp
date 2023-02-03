#include <iostream>

// int main(int, char**) {
//     std::cout << "Hello, world!\n";
// }

#define DLLEXPORT extern "C" __declspec(dllexport) // Windows only

class Pytest
{
public:
    int var = 5;

    int get_var()
    {
        return var;
    }
};

DLLEXPORT int adder(int arg1, int arg2)
{
    return arg1 + arg2;
}