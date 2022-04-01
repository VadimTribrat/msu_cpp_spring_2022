#pragma once

class Allocator
{
	char* ptr_,* ptrFirst_,* ptrEnd_;
public:
	Allocator();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};
