#pragma once
#include <string>
#include <vector>

using onNumber = void (*)(unsigned long);
using onStr = void (*)(const std::string&);
using func = void (*)();

class TokenParser
{
    onNumber numHandler = nullptr;
    onStr strHandler = nullptr;
    func before = nullptr;
    func after = nullptr;
public:
    std::vector<std::string> forTest;
    TokenParser() = default;

    void SetStartCallback(func);

    void SetEndCallback(func);

    void SetDigitTokenCallback(onNumber);

    void SetStringCallback(onStr);

    void Parse(const std::string &);
};
