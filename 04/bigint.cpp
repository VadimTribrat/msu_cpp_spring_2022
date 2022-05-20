#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string> 
#include "bigint.hpp"

int max(int a, int b)
{
	return a > b? a: b;
}

int min(int a, int b)
{
	return a < b? a : b;
}

bigInt::bigInt(std::string str)
{
	if (str.size() == 0)
		str = std::string("0");
	neg = str[0] == '-';
	size = 0;
	max_size = 5;
	arr_of_int = new int[5];
	for(auto s:str)
	{
		if (s!= '-')
		{			
			push_back(s - '0');
		}			
	}
}

bigInt::bigInt(bigInt&& other)
{
	arr_of_int = other.arr_of_int;
	other.arr_of_int = nullptr;
	size = other.size;
	neg = other.neg;
	max_size = other.max_size;
	other.size = other.max_size = 0;
	other.neg = false;
}

bigInt bigInt::mul_by_int(const bigInt& bi, int d)
{
	bigInt new_bi("0");
	if (d == 0)
		return bigInt("0");
	for (int i = 0; i < d; ++i)
	{
		new_bi = new_bi + bi;
	}
	return new_bi;
}

bigInt bigInt::operator=(bigInt&& other)
{
	delete[] arr_of_int;
	arr_of_int = other.arr_of_int;
	other.arr_of_int = nullptr;
	size = other.size;
	neg = other.neg;
	max_size = other.max_size;
	other.size = other.max_size = 0;
	other.neg = false;
	return *this;
}

bigInt::~bigInt()
{
	delete[] arr_of_int;
}

std::ostream & operator <<(std::ostream & out, const bigInt& obj)
{
	if (obj.neg)
		out << "-";
	for(size_t i = 0; i<obj.size; i++)
		out<< obj.arr_of_int[i];
	return out;
}

bigInt bigInt::operator +(const bigInt & b) const
{
	int flag = 0;
	int sizea = size-1, sizeb = b.size-1;
	int s = max(sizea, sizeb);
	std::string str("");
	if (!neg && b.neg)
		return *this-(-b);
	else if (neg && !b.neg)
		return b-(-*this);
	else if (neg && b.neg)
		return -((-*this) + (-b));
	else
	{
		for(int i = s; i>=0; i--)
		{
			if (sizea < 0)
			{
				int s = b.arr_of_int[sizeb];
				s += flag;
				str.push_back((char)((s%10)+'0'));
				flag = s/10;
				sizeb--;
				continue;
			}
			if(sizeb < 0)
			{
				int s = arr_of_int[sizea];
				s += flag;
				str.push_back((char)((s%10) + '0'));
				flag = s/10;
				sizea--;
				continue;
			}
				int s = arr_of_int[sizea] + b.arr_of_int[sizeb];
				s += flag;
				str.push_back((char)((s%10) + '0'));
				flag = s/10;
				sizea--;
				sizeb--;
		}
		if (flag)
			str.push_back((char)(flag + '0'));
		std::reverse(str.begin(), str.end());
		return bigInt(str);
	}
}

bigInt::bigInt(const bigInt & obj)
{
	int* newline = new int[obj.max_size];
    for (size_t i = 0; i < obj.size; i++)
		newline[i] = obj.arr_of_int[i];
    arr_of_int = newline;
	size = obj.size;
	max_size = obj.max_size;
	neg = obj.neg;
}
bool bigInt::operator ==(const bigInt & obj) const
{
	if (size != obj.size)
		return false;
	if (neg != obj.neg)
		return false;
	bool flag = true;
	for (size_t i =0 ; i< size; i++)
	{
		flag = arr_of_int[i] == obj.arr_of_int[i];
		if (!flag)
			return flag;
	}
	return flag;
}

bool bigInt::operator !=(const bigInt & obj) const
{
	return !((*this)==obj);
}

bool bigInt::operator <=(const bigInt & obj) const
{
	if (neg && !obj.neg)
		return true;
	else if (!neg && obj.neg)
		return false;
	else if (neg && obj.neg)
	{
		if (size < obj.size)
			return false;
		if (size > obj.size)
			return true;
		bool flag = true;
		for (size_t i = 0; i<size; i++)
		{
			flag = arr_of_int[i] >= obj.arr_of_int[i];
			if (!flag)
				return flag;
		}
		return flag;
	}
	else
	{
		if (size < obj.size)
			return true;
		if (size > obj.size)
			return false;
		bool flag = true;
		for (size_t i = 0; i<size; i++)
		{
			flag = arr_of_int[i] <= obj.arr_of_int[i];
			if (!flag)
				return flag;
		}
		return flag;
	}	
}

bool bigInt::operator>=(const bigInt& obj)const
{
	if (neg && !obj.neg)
		return false;
	else if (!neg && obj.neg)
		return true;
	else if (neg && obj.neg)
	{
		if (size < obj.size)
			return true;
		if (size > obj.size)
			return false;
		bool flag = true;
		for (size_t i = 0; i<size; i++)
		{
			flag = arr_of_int[i] <= obj.arr_of_int[i];
			if (!flag)
				return flag;
		}
		return flag;
	}
	else 
	{
		if (size < obj.size)
			return false;
		if (size > obj.size)
			return true;
		bool flag = true;
		for (size_t i = 0; i<size; i++)
		{
			flag = arr_of_int[i] >= obj.arr_of_int[i];
			if (!flag)
				return flag;
		}
		return flag;
	}	
}

bool bigInt::operator<(const bigInt& other)const
{
	bool flag = ((*this)<=other);
	return flag && (*this)!=other;
}

bool bigInt::operator>(const bigInt& other)const
{
	return ((*this)>=other) && (*this) != other;
}

bigInt bigInt::operator -(const bigInt & b) const
{
	int sizea = size - 1, sizeb = b.size - 1;
	bigInt inc(""), dec("");
	if (!neg && b.neg)
		return *this+(-b);
	else if (neg && !b.neg)
		return -(-*this+b);
	else if (neg && b.neg)
		return (-b)-(-*this);
	else
	{
		if (sizea >= sizeb)
		{
			int * s = new int[size + 1];
			std::string str("");
			for (long unsigned i = 0; i < size+1; i++)
				s[i] = 0;
			int mi = min(sizea, sizeb);
			int ma = max(sizea, sizeb);
			for (int i = 0; i <= mi; i++)
			{
				int temp = arr_of_int[sizea] - b.arr_of_int[sizeb] - s[sizea+1];
				if (temp >= 0)
					str.push_back((char)(temp + '0'));
				else
				{
					s[sizea] += 1;
					str.push_back((char)(temp + 10 + '0'));
				}
				sizeb--;
				sizea--;
			}
			for (int i =mi+1  ; i<= ma; i++)
			{
				int temp = arr_of_int[sizea] - s[sizea + 1];
				if (temp >= 0)
					str.push_back((char)(temp + '0'));
				else
				{
					s[sizea] += 1;
					str.push_back((char)(temp + 10 + '0'));
				}
				sizeb--;
				sizea--;
	
			}
			delete[] s;
			std::reverse(str.begin(), str.end());
			std::string tempstr("");
			size_t i = 0;
			while (str[i] == '0')
				i++;
			for(size_t j = i; j<str.size(); j++)
				tempstr.push_back(str[j]);
//			std::reverse(tempstr.begin(), tempstr.end());
			if (tempstr.size()== 0)
				tempstr.push_back('0');
			return bigInt(tempstr);
		}
		else
		{
			return -(b-(*this));
		}
	}
			
}

bigInt bigInt::operator =(const bigInt & obj)
{
	if (*this == obj)
		return *this;
	int* newline = new int[obj.max_size];
    for (size_t i = 0; i < obj.size; i++)
		newline[i] = obj.arr_of_int[i];
	delete[] arr_of_int;
    arr_of_int = newline;
	size = obj.size;
	max_size = obj.max_size;
	neg = obj.neg;
	return *this;
}

bigInt bigInt::operator -()const
{
	bigInt temp = *this;
	temp.neg = !temp.neg;
	return temp;
}

void bigInt::push_back(int n)
{

    if (size < max_size) {
        arr_of_int[size] = n;
        size += 1;
    }
    else {
            int* newline = new int[max_size * 2];
            max_size *= 2;
            memcpy(newline, arr_of_int, size*sizeof(int));
            delete[] arr_of_int;
            arr_of_int = newline;
            arr_of_int[size] = n;
			size += 1;
        }
}

bigInt bigInt::operator*(const bigInt& other)
{
	bigInt acc("0"), bi("0");
	acc = bigInt::mul_by_int(*this, other.arr_of_int[other.size - 1]);
	for (int ind = other.size - 2; ind >= 0; --ind)
	{
		auto temp = bigInt::mul_by_int(*this, other.arr_of_int[ind]);
		for (size_t j = 0; j < other.size - ind - 1; ++j)
			temp.push_back(0);
		acc = acc + temp;
	}
	if (!other.neg)
	{
		return acc;
	}
	else
	{
		return -acc;
	}
	
}

bigInt bigInt::operator +(int i)
{
	return *this + std::to_string(i);
}

bigInt bigInt::operator -(int i)
{
	return *this - std::to_string(i);
}

std::string bigInt::repr() const
{
	std::string str("");
	if (neg)
		str.push_back('-');
	for (size_t i = 0 ; i < size; ++i)
	{
		str.push_back('0' + arr_of_int[i]);
	}
	return str;
}