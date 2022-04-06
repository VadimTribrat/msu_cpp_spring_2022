#include "parser.hpp"
#include <iostream>

onNumber numHandler = nullptr;
onStr strHandler = nullptr;
func before = nullptr;
func after = nullptr;

void parser(const std::string & str)
{
	if (before)
		before();
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
            if (word[0]>='0' && word[0]<='9')
            {
                if (numHandler)
				    numHandler(atoi(word.c_str()));
            }
			else	
            {
                if (strHandler)	
				    strHandler(word);
            }
        }
    }
    if (after)
		after();
}

void callbackOnNum(onNumber func)
{
    numHandler = func;
}

void callbackOnStr(onStr func)
{
    strHandler = func;
}

void callbackOnStart(func f)
{
	before = f;
}

void callbackOnEnd(func f)
{
	after = f;
}
