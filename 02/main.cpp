#include <iostream>
#include "allocator.hpp"

int main()
{
	Allocator allocator = Allocator();
	allocator.makeAllocator(0);
	char * ptr = allocator.alloc(10);
	std::cout << (ptr == nullptr) << "\n";
	ptr = allocator.alloc(10);
	std::cout << (ptr == nullptr) << "\n";
	return 0;
}
