
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "matrix.hpp"

class TestFoo : public ::testing::Test
{
};

TEST_F(TestFoo, testGetSizes)
{
    Matrix mat1(10, 15), mat2(2, 4);
    ASSERT_EQ(mat1.getColumns(), 15);
    ASSERT_EQ(mat1.getRows(), 10);
    ASSERT_EQ(mat2.getColumns(), 4);
    ASSERT_EQ(mat2.getRows(), 2);
    ASSERT_ANY_THROW(Matrix(0, 5));
    ASSERT_ANY_THROW(Matrix(1, -10));
}

TEST_F(TestFoo, testMul)
{
    Matrix mat1(2, 2);
    for (size_t i = 0; i < mat1.getRows(); ++i)
        for (size_t j = 0; j < mat1.getColumns(); ++j)
            mat1[i][j] = i * j;
    for (size_t i = 0; i < mat1.getRows(); ++i)
        for (size_t j = 0; j < mat1.getColumns(); ++j)
            ASSERT_TRUE(mat1[i][j] == static_cast<int>(i * j));
    mat1 *= 10;
    for (size_t i = 0; i < mat1.getRows(); ++i)
            for (size_t j = 0; j < mat1.getColumns(); ++j)
                ASSERT_TRUE(mat1[i][j] == static_cast<int>(i * j)*10);
    mat1 *= 0;
    ASSERT_TRUE(mat1 == Matrix(2, 2));
}


TEST_F(TestFoo, testPlus)
{
    Matrix mat1(2, 2), mat2(2, 2);
    for (size_t i = 0; i < mat1.getRows(); ++i)
        for (size_t j = 0; j < mat1.getColumns(); ++j)
        {
            mat1[i][j] = i * j;
            mat2[i][j] = (i + 1) * j*j;
        }
    for (size_t i = 0; i < mat1.getRows(); ++i)
        for (size_t j = 0; j < mat1.getColumns(); ++j)
        {
            ASSERT_TRUE(mat1[i][j] == static_cast<int>(i * j));
            ASSERT_TRUE(mat2[i][j] == static_cast<int>((i + 1) * j*j));
        }
    Matrix mat3 = mat1 + mat2;
    for (size_t i = 0; i < mat1.getRows(); ++i)
            for (size_t j = 0; j < mat1.getColumns(); ++j)
                ASSERT_TRUE(mat3[i][j] == static_cast<int>(i * j + (i + 1) * j*j));
    ASSERT_ANY_THROW(mat1 + Matrix(mat1.getRows() + 1, mat1.getColumns()));
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
