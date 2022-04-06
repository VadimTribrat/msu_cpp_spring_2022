#pragma once
#include <string>

using onNumber = void (*)(int);
using onStr = void (*)(const std::string&);
using func = void (*)();

void parser(const std::string & str);
void callbackOnNum(onNumber);
void callbackOnStr(onStr);
void callbackOnStart(func);
void callbackOnEnd(func);
