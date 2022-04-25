#include "matrix.hpp"

Matrix::Matrix(int row, int col)
{
    if (row <= 0 || col <= 0)
        throw std::exception();
    rowNum = static_cast<size_t>(row);
    colNum = static_cast<size_t>(col);
    mat = new int *[rowNum];
    for (size_t i = 0; i < rowNum; ++i)
    {
        mat[i] = new int[colNum];
        if (mat[i] == nullptr)
        {
            throw std::exception();
        }
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
        throw std::length_error("Inequal sizes");
    for (size_t i = 0; i < rowNum; ++i)
        for (size_t j = 0; j < colNum; ++j)
            if (mat[i][j] != other.mat[i][j])
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix& other)
{
    if (this->colNum != other.colNum || this->rowNum != other.rowNum)
        throw std::length_error("Inequal sizes");
    return !(*this == other);
}

Matrix Matrix::operator+(const Matrix& other)
{
    if (this->colNum != other.colNum || this->rowNum != other.rowNum)
        throw std::length_error("Inequal sizes");
    Matrix temp(rowNum, colNum);
    for (size_t i = 0; i < rowNum; ++i)
        for (size_t j = 0; j < colNum; ++j)
            temp[i][j] = mat[i][j] + other.mat[i][j];
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
            mat[i][j] = other.mat[i][j];    
}
Matrix::Proxy Matrix::operator[](size_t i)
{
    if (i >= rowNum)
        throw std::out_of_range("out og range");
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
    if (i >= colNum)
        throw std::out_of_range("out of range");
    return row[i];
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (size_t i = 0; i < m.rowNum; ++i)
    {
        for (size_t j = 0; j < m.colNum; ++j)
            os << m.mat[i][j] << " ";
        os << "\n";
    }
    return os;
}
