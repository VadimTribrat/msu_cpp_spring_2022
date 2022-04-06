#include "parser.hpp"
#include <string>
#include <iostream>

void numFu(int i)
{
    std::cout << "Digit: " << i << "\n";
}

void strFu(const std::string& str)
{
    std::cout << "String " << str << "\n";
}

void before()
{
	std::cout << "Start\n";
}

void after()
{
	std::cout << "End\n";
}

int main()
{
	callbackOnNum(numFu);
    callbackOnStr(strFu);
    callbackOnStart(before);
    callbackOnEnd(after);
    std::string line;
    getline(std::cin, line);
    parser(line);
    return 0;
}
