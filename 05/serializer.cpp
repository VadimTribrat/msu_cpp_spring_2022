#include "serializer.hpp"

Error Serializer::process(bool arg)
{
    if (arg)
        out_ << "true" << Separator;
    else
        out_ << "false" << Separator;
    return Error::NoError;
}

Error Serializer::process(uint64_t arg)
{
    out_ << arg << Separator;
    return Error::NoError;
}

Serializer::Serializer(std::ostream& out): out_(out)
{
    
}