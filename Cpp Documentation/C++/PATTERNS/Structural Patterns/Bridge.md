```cpp
#include <iostream>

// Implementor Interface
class Implementor
{
public:
    virtual void implementation() const = 0;
    virtual ~Implementor() = default;
};

class ImplementorA : public Implementor
{
public:
    ImplementorA() = default;

    void implementation() const {
        std::cout << "ImplementationA::implementation" << std::endl;
    }
};

class ImplementorB : public Implementor
{
public:
    ImplementorB() = default;

    void implementation() const {
        std::cout << "ImplementationB::implementation" << std::endl;
    }
};

// Bridge interface
class Abstraction
{
public:
    virtual void function() const = 0;
    virtual ~Abstraction() = default;
};
// Bridge abstraction, it's not affected by implementation changes
class RefinedAbstraction : public Abstraction
{
public:
    RefinedAbstraction(Implementor &implementation)
        : implementor(implementation){};

    void function() const {
        std::cout << "RefinedAbstraction::function" << std::endl;
        implementor.implementation();
    }

private:
    Implementor &implementor;
};


int main() {

    ImplementorA implementorA;
    ImplementorB implementorB;

    RefinedAbstraction refinedAbstraction1(implementorA);
    RefinedAbstraction refinedAbstraction2(implementorB);

    Abstraction *abstraction1 = &refinedAbstraction1;
    Abstraction *abstraction2 = &refinedAbstraction2;

    abstraction1->function();
    std::cout << std::endl;
    abstraction2->function();
    std::cout << std::endl;

    return 0;
}
```