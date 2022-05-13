#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <type_traits>

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
				throw std::logic_error("Unbalanced number of brackets\n");
			result.push_back(str[i]);
			i++;
			if (i >= length)
			{
				if ((params.size() != 0) && (set_.find(params.size() - 1) == set_.end()))
					throw std::logic_error("Too much arguments");
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
					throw std::logic_error("Not a number");
				tempStr.push_back(str[i]);
			}
			else
				throw std::runtime_error("Unbalanced number of brackets\n");
			i++;
		}
		unsigned long ind = static_cast<size_t>(std::stoul(tempStr));
		set_.insert(ind);
		if (ind >= params.size())
			throw std::runtime_error("Not enough arguments\n");
		result += params[ind]; 
	}
	if ((params.size() != 0) && (set_.find(params.size() - 1) == set_.end()))
		throw std::logic_error("Too much arguments");
	return result;
}