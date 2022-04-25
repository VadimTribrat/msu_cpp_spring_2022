#pragma once
#include <iostream>
#include <ostream>
#include <cstddef>

class Matrix
{
    int * * mat;
    size_t rowNum, colNum;
public:
    class Proxy
    {
        int * row;
        size_t colNum;
    public:
        Proxy(int * const, size_t);
        int& operator[](size_t);
        ~Proxy();
        Proxy(const Proxy&);
    };
    Matrix(int, int);
    ~Matrix();
    size_t getRows();
    size_t getColumns();
    Matrix& operator*=(int);
    bool operator==(const Matrix&);
    bool operator!=(const Matrix&);
    Matrix operator+(const Matrix&);
    Matrix(const Matrix&);
    Proxy operator[](size_t);    
    friend std::ostream& operator<<(std::ostream&, const Matrix&);
};