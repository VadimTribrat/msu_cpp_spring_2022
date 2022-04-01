#include <iostream>
#include "allocator.h"

int main()
{
	Allocator allocator = Allocator();
	allocator.makeAllocator(15);
	char * ptr = allocator.alloc(10);
	std::cout << (ptr == nullptr) << "\n";
	ptr = allocator.alloc(10);
	std::cout << (ptr == nullptr) << "\n";
	return 0;
}
