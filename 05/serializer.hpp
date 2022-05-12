#pragma once
#include <iostream>
#include <ostream>
#include <string>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream& out_;
    Error process(bool arg);
    Error process(uint64_t arg);
    template <typename T, typename... ArgsT>
    Error process(T&& arg, ArgsT&&... args);
public:
    explicit Serializer(std::ostream& out);
    template <class T>
    Error save(T& object);
    template <class... ArgsT>
    Error operator()(ArgsT&&... args);
};

template <typename T, typename... ArgsT>
Error Serializer::process(T&& arg, ArgsT&&... args)
{
    if (process(std::forward<T>(arg)) == Error::NoError)
        return process(std::forward<ArgsT>(args)...);
    return Error::CorruptedArchive;
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT&&... args)
{
    return process(std::forward<ArgsT>(args)...);
}

template <class T>
Error Serializer::save(T& object)
{
    return object.serialize(*this);
}