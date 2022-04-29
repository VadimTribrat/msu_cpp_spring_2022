#include <iostream>
#include <sstream>
#include "serializer.hpp"
#include "deserializer.hpp"

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;
    Data(uint64_t a,bool b,uint64_t c): a{a}, b{b}, c{c}
    {}

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

int main()
{
    std::stringstream ss("");
    Serializer serializer(ss);
    Deserializer deserializer(ss);
    Data data{10, true, 1};
    serializer.save(data);
    data.a = 11;
    deserializer.load(data);
    std::cout << data.a << "\n";
    return 0;
}