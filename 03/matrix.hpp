#pragma once
#include <iostream>

class Matrix
{
    int * * mat;
    size_t rowNum, colNum;
public:
    class Proxy
    {
        int * row, colNum;
    public:
        Proxy(int * const, size_t);
        int& operator[](size_t);
        ~Proxy();
        Proxy(const Proxy&);
    };
    Matrix(size_t, size_t);
    ~Matrix();
    size_t getRows():
    size_t getColumns();
    Matrix& operator*=(int);
    bool operator==(const Matrix&);
    bool operator!=(const Matrix&);
    Matrix operator+(const Matrix&);
    Matrix(const Matrix&);
    Proxy operator[](size_t);    
};