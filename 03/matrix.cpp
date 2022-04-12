#include "matrix.hpp"

Matrix::Matrix(size_t row, size_t col)
{
    rowNum = row;
    colNum = col;
    mat = new int *[rowNum];
    for (size_t i = 0; i < rowNum; ++i)
    {
        mat[i] = new int[colNum];
    }
    for (size_t i = 0; i < rowNum; ++i)
        for (size_t j = 0; j < colNum; ++j)
            mat[i][j] = 0;
}

Matrix::~Matrix()
{
    for (size_t i = 0; i < rowNum; ++i)
        delete[] mat[i];
    delete[] mat;
}

size_t Matrix::getRows()
{
    return rowNum;
}

size_t Matrix::getColumns()
{
    return colNum;
}

Matrix& Matrix::operator*=(int mul)
{
    for (size_t i = 0; i < rowNum; ++i)
        for (size_t j = 0; j < colNum; ++j)
            mat[i][j] *= mul;
    return *this;   
}

bool Matrix::operator==(const Matrix& other)
{
    if (this->colNum != other.colNum || this->rowNum != other.rowNum)
        throw std::exception();
    for (size_t i = 0; i < rowNum; ++i)
        for (size_t j = 0; j < colNum; ++j)
            if (mat[i][j] != other[i][j])
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix& other)
{
    if (this->colNum != other.colNum || this->rowNum != other.rowNum)
        throw std::exception();
    return !(*this == other);
}

bool Matrix::operator+(const Matrix& other)
{
    if (this->colNum != other.colNum || this->rowNum != other.rowNum)
        throw std::exception();
    Matrix temp(rowNum, colNum):
    for (size_t i = 0; i < rowNum; ++i)
        for (size_t j = 0; j < colNum; ++j)
            temp[i][j] = mat[i][j] + other[i][j];
    return temp;
}

Matrix::Matrix(const Matrix& other)
{
    rowNum = other.rowNum;
    colNum = other.colNum;
    mat = new int *[rowNum];
    for (size_t i = 0; i < rowNum; ++i)
    {
        mat[i] = new int[colNum];
    }
    for (size_t i = 0; i < rowNum; ++i)
        for (size_t j = 0; j < colNum; ++j)
            mat[i][j] = other[i][j];    
}
Matrix::Proxy Matrix::operator[](size_t i)
{
    return Matrix::Proxy(mat[i], colNum);
}

Matrix::Proxy::Proxy(int * const ptr, size_t size)
{
    row = ptr;
    colNum = size;
}

Matrix::Proxy::Proxy(const Proxy& other)
{
    row = other.row;
    colNum = other.colNum;
}

Matrix::Proxy::~Proxy()
{
    row = nullptr;
}

int& Matrix::Proxy::operator[](size_t i)
{
    return row[i];
}