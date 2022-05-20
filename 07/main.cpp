#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <type_traits>
#include "vector.hpp"

int main()
{
    vector<int, std::allocator<int>> vec(3);
	for (size_t i = 0; i < 50; ++i)
	{
		vec.push_back(i);
	}
	int i = 0;
	for (auto val: vec)
	{
        std::cout << val << " ";
		assert(val == i++);
	}
	i = 49;
    std::cout << "\n";
	for(auto it = vec.rbegin(); it != vec.rend(); ++it)
	{
        std::cout << *it << " ";
	}
    return 0;
}