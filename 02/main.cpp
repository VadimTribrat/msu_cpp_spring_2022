#include "parser.hpp"
#include <string>
#include <iostream>

int main()
{
    std::string line;
    getline(std::cin, line);
    parser(line);
    return 0;
}