
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
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
    ASSERT_ANY_THROW(Matrix(0, 0));
}

TEST_F(TestFoo, testGetElement)
{
    Matrix mat1(2, 2);
    for (size_t i = 0; i < mat1.getRows(); ++i)
        for (size_t j = 0; j < mat1.getColumns(); ++j)
            mat1[i][j] = (i + 1) * (j + 1);
    ASSERT_TRUE(mat1[0][0] == 1);
    ASSERT_TRUE(mat1[0][1] == 2);
    ASSERT_TRUE(mat1[1][0] == 2);
    ASSERT_TRUE(mat1[1][1] == 4);
    ASSERT_ANY_THROW(mat1[0][-1]);
    ASSERT_ANY_THROW(mat1[2][0]);
    ASSERT_ANY_THROW(mat1[0][2]);
    ASSERT_ANY_THROW(mat1[-1][0]);
    ASSERT_ANY_THROW(mat1[-1][-1]);
    ASSERT_ANY_THROW(mat1[10000][0]);
    ASSERT_ANY_THROW(mat1[1000][1000]);    
}


TEST_F(TestFoo, testMul)
{
    Matrix mat1(2, 2), mat1_res(2, 2);
    for (size_t i = 0; i < mat1.getRows(); ++i)
        for (size_t j = 0; j < mat1.getColumns(); ++j)
            mat1[i][j] = (i + 1) * (j + 2);
    mat1_res[0][0] = 20;
    mat1_res[0][1] = 30;
    mat1_res[1][0] = 40;
    mat1_res[1][1] = 60;
    mat1 *= 10;
    ASSERT_TRUE(mat1 == mat1_res);
    mat1 *= 0;
    ASSERT_TRUE(mat1 == Matrix(2, 2));
}

TEST_F(TestFoo, testEqual)
{
    Matrix mat1(2, 2), mat2(2, 2), mat3(2, 2), mat4(3, 2);
    for (size_t i = 0; i < mat1.getRows(); ++i)
        for (size_t j = 0; j < mat1.getColumns(); ++j)
        {
            mat1[i][j] = (i + 1) * (j + 1) * (j + 1);
            mat2[i][j] = (i + 1) * (j + 1) * (j + 1);
            mat3[i][j] = i * j;
        }
    ASSERT_TRUE(mat1 == mat2);
    mat1[0][0] = 100;
    ASSERT_TRUE(mat1 != mat2);
    mat2[0][0] = 100;
    ASSERT_TRUE(mat1 == mat2);
    ASSERT_TRUE(mat2 != mat3);
    ASSERT_ANY_THROW(mat1 == mat4);
}


TEST_F(TestFoo, testPlus)
{
    Matrix mat1(2, 2), mat2(2, 2), mat_res1(2, 2), mat_res2(2, 2);
    for (size_t i = 0; i < mat1.getRows(); ++i)
        for (size_t j = 0; j < mat1.getColumns(); ++j)
        {
            mat1[i][j] = i * j;
            mat2[i][j] = (i + 1) * j*j;
        }
    mat_res1[0][0] = mat_res1[1][0] = mat_res1[0][1] = 0;
    mat_res1[1][1] = 1;
    mat_res2[0][0] = mat_res2[1][0] = 0;
    mat_res2[0][1] = 1;
    mat_res2[1][1] = 2;
    ASSERT_TRUE(mat1 == mat_res1);
    ASSERT_TRUE(mat2 == mat_res2);
    Matrix mat3 = mat1 + mat2;
    for (size_t i = 0; i < mat1.getRows(); ++i)
            for (size_t j = 0; j < mat1.getColumns(); ++j)
                ASSERT_TRUE(mat3[i][j] == static_cast<int>(i * j + (i + 1) * j*j));
    ASSERT_ANY_THROW(mat1 + Matrix(mat1.getRows() + 1, mat1.getColumns()));
    ASSERT_TRUE(mat1 == mat_res1);
    ASSERT_TRUE(mat2 == mat_res2);
}

TEST_F(TestFoo, testStream)
{
    std::stringstream ss1, ss2;
    Matrix mat1(2, 2);
        for (size_t i = 0; i < mat1.getRows(); ++i)
            for (size_t j = 0; j < mat1.getColumns(); ++j)
                mat1[i][j] = (i + 1) * (j + 1);
    ss1 << mat1;
    std::vector<uint64_t> res{1, 2, 2, 4};
    std::vector<uint64_t> pred;
    for (size_t i = 0; i < 4; ++i)
    {
        std::string str;
        ss1 >> str;
        int elem = static_cast<uint64_t>(std::stoi(str));
        pred.push_back(elem);
    }
    ASSERT_TRUE(pred == res);
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
