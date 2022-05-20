#pragma once
#include <cstring>

template<class T,
		class _Category=std::random_access_iterator_tag,
		class _Distance=ptrdiff_t,
		class _Pointer=T*,
		class _Reference=T&>
class iterator: public std::iterator<_Category, T, _Distance, _Pointer, _Reference>
{
	_Pointer ptr;
	bool reverse;
public:
	iterator(_Pointer p, bool rev=false): ptr{p}, reverse{rev}
	{}
	bool operator ==(const iterator<T>& other)
	{
		return ptr == other.ptr;
	}
	void operator =(const T& obj)
	{
		*ptr = obj;
	}
	bool operator !=(const iterator<T>& other)
	{
		return (ptr) != (other.ptr);
	}
	_Reference operator *()
	{
		return *ptr;
	}
	iterator<T>& operator++()
	{
		if (reverse)
			ptr--;
		else
			ptr++;
		return *this; 
	}
	iterator<T>& operator+(int i)
	{
		if (reverse)
			ptr -= i;
		else
			ptr += i;
		return *this; 
	}
	iterator<T>& operator--()
	{
		if (reverse)
			ptr++;
		else
			ptr--;
		return *this; 
	}
	iterator<T>& operator-(int i)
	{
		if (reverse)
			ptr += i;
		else
			ptr -= i;
		return *this; 
	}
};


template <class T>
class allocator
{
    using ptr_t = T*;
    using constref_t = const T&;
public:
    ptr_t allocate(size_t count) {
        ptr_t p = new T[count];
        if (p == nullptr) {
            throw std::bad_alloc();
        }
        return p;
    }

    void deallocate(ptr_t p, size_t count) {
		delete[] p;
    }
};


template<class T, class Allocator=std::allocator<T>>
class vector
{
	T * arr;
	size_t sz;
	size_t max_size;
	Allocator allocator;
public:
	vector(size_t ms= 0): max_size{ms}
	{
		allocator = Allocator();
		sz = 0;
		arr = allocator.allocate(max_size);
	}
	~vector()
	{
		allocator.deallocate(arr, max_size);
	}
	T& operator [](size_t ind)
	{
		return arr[ind];
	}
	void push_back(T obj)
	{
		if (sz < max_size)
			arr[sz++] = obj;
		else
		{
			T * new_arr = allocator.allocate(max_size + 1);
			std::memcpy(new_arr, arr, sz * sizeof(T));
			allocator.deallocate(arr, max_size);
			max_size += 1;
			arr = new_arr;
			arr[sz++] = obj;
		}		
	}
	T pop_back()
	{
		if (sz)
		{
			auto res = arr[--sz];
			return res;
		}
		throw std::out_of_range("Pop_back error");
	}
	template <class... Args>
	void emplace_back(Args&&... args)
	{
		if (sz < max_size)
			arr[sz++] = T(std::forward<Args>(args)...);
		else
		{
			T * new_arr = allocator.allocate(max_size + 1);
			allocator.deallocate(arr, max_size);
			max_size += 1;
			arr = new_arr;
			arr[sz++] = T(std::forward<Args>(args)...);
		}	
	}
	bool empty()
	{
		return sz == 0;
	}
	size_t size()
	{
		return sz;
	}
	void clear()
	{
		sz = 0;
	}
	iterator<T> begin()
	{
		return iterator<T>(arr);
	}
	iterator<T> rbegin()
	{
		return iterator<T>(arr + sz - 1, true);
	}
	iterator<T> end()
	{
		return iterator<T>(arr + sz);
	}
	iterator<T> rend()
	{
		return iterator<T>(arr - 1, true);
	}
	size_t capacity()
	{
		return max_size;
	}
	void reserve(size_t new_size)
	{
		if (max_size < new_size)
		{
			T * new_arr = allocator.allocate(new_size);
			std::memcpy(new_arr, arr, sz * sizeof(T));
			allocator.deallocate(arr, max_size);
			max_size = new_size;
			arr = new_arr;	
		}
	}
	void resize(size_t new_size)
	{
		if (max_size != new_size)
		{
			sz = std::min(sz, new_size);
			T * new_arr = allocator.allocate(new_size);
			std::memcpy(new_arr, arr, sz * sizeof(T));
			allocator.deallocate(arr, max_size);
			max_size = new_size;
			arr = new_arr;				
		}
	}
};