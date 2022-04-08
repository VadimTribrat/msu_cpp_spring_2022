#include "parser.hpp"
#include <iostream>
#include <cstdlib>


void TokenParser::SetDigitTokenCallback(onNumber func)
{
    numHandler = func;
}

void TokenParser::SetStringCallback(onStr func)
{
    strHandler = func;
}

void TokenParser::SetStartCallback(func f)
{
	before = f;
}

void TokenParser::SetEndCallback(func f)
{
	after = f;
}

void TokenParser::Parse(const std::string& str)
{
	if (before)
    {
		before();
        forTest.push_back(std::string("Start"));
    }
    if (!str.empty())
    {
        for (size_t i = 0; i < str.length(); ++i)
        {
            char c = str[i];
            if ((c == ' ') || (c == '\t') || (c == '\n'))
                continue;
            size_t j = -1;
            std::string word;
            for(j = i; j < str.length(); ++j)
			{
				char s = str[j];
				if ((s != ' ') && (s != '\t') && (s != '\n'))
					word.push_back(s);
				else
					break;
			}
            i = j;
            unsigned long digit;
            bool isTrue = true;
            for (auto val: word)
            {
                if (!isTrue)
                    break;
                isTrue = std::isdigit(val);
            }
            if (isTrue)
            {
                digit = strtoul(word.c_str(), nullptr, 10);
                if (numHandler && digit && (errno != ERANGE))
                {
				    numHandler(digit);
                    forTest.push_back(std::string("Dig:") + word);
                }
                else
                {
                    if (strHandler)
                    {
                        strHandler(word);
                        forTest.push_back(std::string("Str:") + word);
                    }

                }
                
            }
			else	
            {
                if (strHandler)	
                {
				    strHandler(word);
                    forTest.push_back(std::string("Str:") + word);
                }
            }
        }
    }
    if (after)
    {
        forTest.push_back(std::string("End"));
		after();
    }
}
