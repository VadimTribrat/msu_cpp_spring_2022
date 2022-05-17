#pragma once

#include <vector>
#include <sstream>
#include <set>
#include <type_traits>

class MyException: public std::logic_error
{
	std::string msg;
public:
    explicit MyException(const std::string& message)
        : std::logic_error(message), msg(message) 
	{}
	explicit MyException(const char * message)
        : std::logic_error(message), msg(message)
	{}
    virtual ~MyException() noexcept {}
    const char* what() const noexcept override{
       return msg.c_str();
    }
};

void convert(std::stringstream& ss)
{
	ss.clear();
}

template <class T, class... ArgsT>
void convert(std::stringstream& ss,T && arg, ArgsT&&... args)
{
	ss << std::forward<T>(arg) << " ";
	convert(ss, std::forward<ArgsT>(args)...);
}

template <class... ArgsT>
std::string format(std::string str, ArgsT&&... args)
{
	std::string result;
	std::set<unsigned long> set_;
	std::stringstream ss;
	size_t length = str.size();
	convert(ss, std::forward<ArgsT>(args)...);
	std::vector<std::string> params;
	while (ss)
	{
		std::string temp{""};
		ss >> temp;
		if (temp != "")
			params.push_back(temp);
	}
	for (size_t i = 0; i < length; ++i)
	{
		while (str[i] != '{')
		{
			if (str[i] == '}')
				throw MyException("Unbalanced number of brackets\n");
			result.push_back(str[i]);
			i++;
			if (i >= length)
			{
				if ((params.size() != 0) && (set_.find(params.size() - 1) == set_.end()))
					throw MyException("Too much arguments");
				return result;
			}
		}
		std::string tempStr;
		i++;
		while (str[i] != '}')
		{
			if (i < length)
			{
				if (!std::isdigit(str[i]))
					throw MyException("Not a number");
				tempStr.push_back(str[i]);
			}
			else
				throw MyException("Unbalanced number of brackets\n");
			i++;
		}
		if (tempStr == "")
			throw MyException("No index");
		unsigned long ind;
		try
		{
			ind = static_cast<size_t>(std::stoul(tempStr));
		}
		catch(const std::out_of_range & e)
		{
			throw MyException("Too long number");
		}
		set_.insert(ind);
		if (ind >= params.size())
			throw MyException("Not enough arguments\n");
		result += params[ind]; 
	}
	if ((params.size() != 0) && (set_.find(params.size() - 1) == set_.end()))
		throw MyException("Too much arguments");
	return result;
}