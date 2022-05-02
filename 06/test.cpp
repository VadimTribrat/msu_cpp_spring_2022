#include <gtest/gtest.h>
#include <iostream>
#include <string>
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

class TestFoo : public ::testing::Test
{
};

TEST_F(TestFoo, test1)
{
	auto text = format("{1}+{1} = {0}", 2, "one");
	ASSERT_TRUE(text == "one+one = 2");
	ASSERT_ANY_THROW(format("{0}, {1}, {3}", 1, 2));
	ASSERT_ANY_THROW(format("{0}, {1} {", 1, 2));
	ASSERT_TRUE(format("{0}, {1}, {0}, {2}", false, 1, "abc") == "0, 1, 0, abc");
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
