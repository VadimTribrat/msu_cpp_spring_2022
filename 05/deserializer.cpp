#include "deserializer.hpp"

Error Deserializer::process(uint64_t & val)
{
	std::string str;
	in_ >> str;
	val = atoi(str.c_str());
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