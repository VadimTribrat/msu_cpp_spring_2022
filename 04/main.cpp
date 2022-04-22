#include <iostream>
#include "bigint.hpp"

int main()
{
    bigInt bi("12");
    std::cout << bi << "\n";
    auto new_bi = bi * bigInt("0");
    std::cout << new_bi << "\n";
    return 0;
}