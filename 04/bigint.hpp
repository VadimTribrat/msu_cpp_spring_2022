#pragma once

class bigInt
{
	size_t size;
	size_t max_size;
	int * arr_of_int;
	bool neg;
public:
	bigInt(std::string str);
	~bigInt();
	bigInt(const bigInt&);
	bigInt operator=(const bigInt&);
    bigInt(bigInt&&);
    bigInt operator=(bigInt&&);
	bool operator ==(const bigInt&) const;
	bigInt operator-() const;
	bool operator!=(const bigInt& other) const;
	bool operator<(const bigInt& other)const;
	bool operator>(const bigInt& other)const;
	bool operator>=(const bigInt& other)const;
	bool operator<=(const bigInt& other)const;
	void push_back(int n);
    static bigInt mul_by_int(const bigInt&, int);
    bigInt operator *(const bigInt&);
    bigInt operator +(int);
    bigInt operator -(int);
	
	bigInt operator +(const bigInt&) const;
	bigInt operator -(const bigInt&) const;
	friend std::ostream & operator <<(std::ostream & out,const bigInt& obj);
	std::string repr() const;
};