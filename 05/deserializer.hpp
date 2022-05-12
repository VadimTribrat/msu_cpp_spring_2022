#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include "serializer.hpp"


class Deserializer
{
	static const std::string maxVal;
	std::stringstream & in_;
	static constexpr char Separator = ' ';
	Error process(bool&);
	Error process(uint64_t&);
	template <class T, class... ArgT>
	Error process(T&& t, ArgT&&...);
public:
	Deserializer(std::stringstream &);
	template <class T>
	Error load(T & t);
	template <class... ArgT>
	Error operator ()(ArgT&&... args);	
};

template <class T, class... ArgT>
Error Deserializer::process(T&& t, ArgT&&... args)
{
	if (process(std::forward<T>(t)) == Error::NoError)
		return process(std::forward<ArgT>(args)...);
	return Error::CorruptedArchive;
}

template <class... ArgT>
Error Deserializer::operator ()(ArgT&&... args)
{
	if (process(std::forward<ArgT>(args)...) == Error::NoError)
		return Error::NoError;
	return Error::CorruptedArchive;
}

template <class T>
Error Deserializer::load(T & object)
{
	return object.serialize(*this);
}
