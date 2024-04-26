#include <iostream>
#include <tuple>
#include <vector>

template <typename... Args>
auto Sum(const std::tuple<Args...> & tp) {
    auto sum = 0;
    std::apply(
        [&sum](const auto &... args) {
            ((sum += args), ...);
        },
        tp);
    return sum;
}

int main() {
    std::cout << "Enter 5 values: ";
    int a, b, c, d, e;
    std::cin >> a >> b >> c >> d >> e;
    auto res = Sum(std::make_tuple(a, b, c, d, e));
    std::cout << "Res: " << res;

    return 0;
}