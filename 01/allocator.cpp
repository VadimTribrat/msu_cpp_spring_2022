#include <iostream>
#include "allocator.h"

Allocator::Allocator(): ptr_{nullptr}, ptrFirst_{nullptr}, ptrEnd_{nullptr} 
{}

void Allocator::makeAllocator(size_t maxSize)
{
	if (ptr_)
	{
		delete[] ptrFirst_;
	}
	ptr_ = new char[maxSize];
	ptrEnd_ = ptr_ + maxSize;
	ptrFirst_ = ptr_;
}

char * Allocator::alloc(size_t size)
{
	if (!ptr_)
		return nullptr;
	if (ptr_ + size <= ptrEnd_)
	{
		ptr_ += size;
		return ptr_ - size;
	}
	return nullptr;
}

void Allocator::reset()
{
	ptr_ = ptrFirst_;
}

Allocator::~Allocator()
{
	delete[] ptrFirst_;
}
