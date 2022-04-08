#include "parser.hpp"
#include <string>
#include <iostream>

void numFu(unsigned long i)
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
    TokenParser tp;
	tp.SetDigitTokenCallback(numFu);
    tp.SetStringCallback(strFu);
    tp.SetStartCallback(before);
    tp.SetEndCallback(after);
    std::string line;
    getline(std::cin, line);
    tp.Parse(line);
    return 0;
}
