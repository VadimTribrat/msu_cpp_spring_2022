#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <type_traits>

void convert(std::stringstream& ss)
{

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
	std::stringstream ss;
	size_t length = str.size();
	convert(ss, std::forward<ArgsT>(args)...);
	std::vector<std::string> params;
	while (ss)
	{
		std::string temp;
		ss >> temp;
		params.push_back(temp);
	}
	for (size_t i = 0; i < length; ++i)
	{
		while (str[i] != '{')
		{
			result.push_back(str[i]);
			i++;
			if (i >= length)
				break;
		}
		std::string tempStr;
		i++;
		while (str[i] != '}')
		{
			if (i < length)
				tempStr.push_back(str[i]);
			else
				throw std::runtime_error("Unbalanced number of brackets\n");
			i++;
		}
		size_t ind = static_cast<size_t>(std::stoul(tempStr));
		if (ind >= params.size())
			throw std::runtime_error("Not enough arguments\n");
		result += params[ind]; 
	}
	return result;
}


int main()
{
    auto text = format("{1}+{1} = {0}", 2, "one");
    std::cout << text << "\n";
    // std::to_string('3');
    return 0;
}