#include "deserializer.hpp"

const std::string Deserializer::maxVal = "18446744073709551615";

Error Deserializer::process(uint64_t & val)
{
	std::string str;
	in_ >> str;
	uint64_t temp = 0;
	for (int i = str.size() - 1; i >= 0; --i)
		if (!std::isdigit(str[i]))
			return Error::CorruptedArchive;
	if (str.size() > maxVal.size())
		return Error::CorruptedArchive;
	if (str.size() == maxVal.size())
	{
		for (size_t i = 0; i < str.size(); ++i)
			if (str[i] < maxVal[i])
				break;
			else if (str[i] > maxVal[i])
				return Error::CorruptedArchive;
	}
	for(size_t i = 0; i < str.size(); ++i)
	{
		temp *= 10;
		temp += str[i] - '0';
	}
	val = temp;
	return Error::NoError;
}

Deserializer::Deserializer(std::stringstream& in): in_{in}
{}

Error Deserializer::process(bool & val)
{
	std::string str;
	in_ >> str;
	if (str == "true")
		val = true;
	else
		if (str == "false")
			val = false;
		else
			return Error::CorruptedArchive;
	return Error::NoError;
}