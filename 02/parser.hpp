#pragma once
#include <string>

using onNumber = void (*)(int);
using onStr = void (*)(const std::string&);

void parser(const std::string & str);
void callbackOnNum(onNumber);
void callbackOnStr(onStr);