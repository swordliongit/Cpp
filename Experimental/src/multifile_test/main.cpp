#include <iostream>
#include <vector>

void caller();

void printer()
{
    std::cout << "Printed from the main function. Hello!!";
}

int main() 
{
    caller();
    
    return 0;
}
