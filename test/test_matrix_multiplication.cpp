#include "matrix_multiplication.h"
#include "../src/matrix_mult.cpp"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

// ######################### Source code of multiplyMatrices in src/matrix_mult

// In this file we're going to briefly describe the behaviour of the function multiplyMatrices.
// In particular, for each test we're going to list the errors that we discovered (below the test code).

TEST(MatrixMultiplicationTest, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<int>> B = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 3, 2);

    std::vector<std::vector<int>> expected = {
        {58, 64},
        {139, 154}
    };

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// From this given example we get four errors:
// * Error 6: Result matrix contains a number bigger than 100!
// * Error 12: The number of rows in A is equal to the number of columns in B!
// * Error 14: The result matrix C has an even number of rows!
// * Error 20: Number of columns in matrix A is odd!

// We can infer that the test will fail any time:
// - the matrix C contains at least one element greater than 100;
// - the matrix C is a square matrix because rowsC = rowsA = colsB = colsC;
// - the matrix C has an even number of rows;
// - the matrix A has an odd number of columns, therefore the matrix B has an odd number of rows for compatibility of dimensions.

// In order to detect all the other errors, we can start with the simplest possible case: multiplication between two scalars.
// We expect errors 12 and 20.
TEST(MatrixMultiplicationTest1, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {1}
    };
    std::vector<std::vector<int>> B = {
        {2}
    };
    std::vector<std::vector<int>> C(1, std::vector<int>(1, 0));

    multiplyMatrices(A, B, C, 1, 1, 1);

    std::vector<std::vector<int>> expected(1, std::vector<int>(1, 0));

    multiplyMatricesWithoutErrors(A, B, expected, 1, 1, 1);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// * Error 12.
// * Error 18: Matrix A is a square matrix!
// * Error 20.

// We can infer that the test will fail any time the matrix A is a square matrix.

// So we can check again error 12 by multiplying a 2x2 matric by a 2x1 vector. We expect errors 14 and 18.
TEST(MatrixMultiplicationTest2, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {1, 2},
        {1, 2}
    };
    std::vector<std::vector<int>> B = {
        {3},
        {3}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(1, 0));

    multiplyMatrices(A, B, C, 2, 2, 1);

    std::vector<std::vector<int>> expected(2, std::vector<int>(1, 0));

    multiplyMatricesWithoutErrors(A, B, expected, 2, 2, 1);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// * Error 4: Matrix B contains the number 3!
// * Error 14.
// * Error 18.

// By trying again with small martices containing lots of zeros and a three in B, we expect errors 4, 12, 14 and 18.
TEST(MatrixMultiplicationTest3, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {0, 0},
        {5, 5}
    };
    std::vector<std::vector<int>> B = {
        {0, 3},
        {0, 3}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 2, 2);

    std::vector<std::vector<int>> expected(2, std::vector<int>(2, 0));
    multiplyMatricesWithoutErrors(A, B, expected, 2, 2, 2);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// * Error 4.
// * Error 8: Result matrix contains zero!
// * Error 11: Every row in matrix B contains at least one '0'!
// * Error 12.
// * Error 13: The first element of matrix A is equal to the first element of matrix B!
// * Error 14.
// * Error 15: A row in matrix A is filled entirely with 5s!
// * Error 18.

// From here we understand that we neen to explore the behaviour of the function by changing:
// - the size of the matrices;
// - the magnitude of the values of the matrices;
// - the presence of various digits within the matrices.
// In order to investigate the latter point in the previous list, we can try to fill B with all decimal places
// so that we can detect other errors of the same type.
TEST(MatrixMultiplicationTest4, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<int>> B = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 0, 1}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(4, 0));

    multiplyMatrices(A, B, C, 2, 3, 4);

    std::vector<std::vector<int>> expected(2, std::vector<int>(4, 0));

    multiplyMatricesWithoutErrors(A, B, expected, 2, 3, 4);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// * Error 1: Element-wise multiplication of ones detected!
// * Error 4.
// * Error 7: Result matrix contains a number between 11 and 20!
// * Error 14.
// * Error 16: Matrix B contains the number 6!
// * Error 20.

// We can infer that the test will fail any time the current element in A and the current element in B are both one,
// so you get an element-wise multiplication.

// Test truncation-matrix, the expected errors are 1, 7, 11, 12, 13, 14.
TEST(MatrixMultiplicationTest5, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {1, 3, 5, 7, 9, 11},
        {2, 6, 10, 14, 18, 22},
        {98, 94, 90, 86, 82, 78},
        {99, 97, 95, 93, 91, 89}
    };
    std::vector<std::vector<int>> B = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    std::vector<std::vector<int>> C(4, std::vector<int>(4, 0));

    multiplyMatrices(A, B, C, 4, 6, 4);

    std::vector<std::vector<int>> expected(4, std::vector<int>(4, 0));
    multiplyMatricesWithoutErrors(A, B, expected, 4, 6, 4);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// * Error 1.
// * Error 2: Matrix A contains the number 7!
// * Error 7.
// * Error 9: Result matrix contains the number 99!
// * Error 11.
// * Error 12.
// * Error 13.
// * Error 14.
// * Error 17: Result matrix C contains the number 17!
// With this test we found two more cases in which a specific number present in an input or output matrix causes an error.

// We multiply by the identity matrix to see if the result doesn't change. We also set a wrong number of columns of B to see
// what happens.
TEST(MatrixMultiplicationTest6, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    std::vector<std::vector<int>> B = {
        {1, 1},
        {1, 1},
        {1, 1}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));

    multiplyMatrices(A, B, C, 3, 3, 3);

    std::vector<std::vector<int>> expected(3, std::vector<int>(3, 0));

    multiplyMatricesWithoutErrors(A, B, expected, 3, 3, 3);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// * Error 1.
// * Error 8.
// * Error 13.
// * Error 18.
// * Error 20.
// The fact that we've set a wrong number of columns of B doesn't interfere with the result of multiplyMatricesWithoutErrors
// which is { { 1, 1, 0 }, { 1, 1, 0 }, { 1, 1, 0 } }, a column of zeros is added to the matrix B.

// Now we multiply by the null matrix.
TEST(MatrixMultiplicationTest7, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<int>> B = {
        {0, 0},
        {0, 0},
        {0, 0}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 3, 2);

    std::vector<std::vector<int>> expected(2, std::vector<int>(2, 0));

    multiplyMatricesWithoutErrors(A, B, expected, 2, 3, 2);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// * Error 8.
// * Error 11.
// * Error 12.
// * Error 14.
// * Error 20.

// Then we follow up with matrices containing negative numbers to see if that causes any issues.
TEST(MatrixMultiplicationTest8, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {1, -1},
        {-1, 1}
    };
    std::vector<std::vector<int>> B = {
        {-1, -1},
        {-1, -1}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 2, 2);

    std::vector<std::vector<int>> expected(2, std::vector<int>(2, 0));
    multiplyMatricesWithoutErrors(A, B, expected, 2, 2, 2);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// * Error 3: Matrix A contains a negative number!
// * Error 5: Matrix B contains a negative number!
// * Error 7.
// * Error 12.
// * Error 14.
// * Error 18.
// We discovered that the test will fail any time at least one element of A or B is negative.

// We contithe testing the presence of various digits within the matrices.
TEST(MatrixMultiplicationTest9, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {0, 0, 0},
        {1, 1, 1},
        {2, 2, 2},
        {3, 3, 3},
        {4, 4, 4},
        {5, 5, 5},
        {6, 6, 6},
        {7, 7, 7},
        {8, 8, 8},
        {9, 9, 9}
    };
    std::vector<std::vector<int>> B = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    };
    std::vector<std::vector<int>> C(10, std::vector<int>(10, 0));

    multiplyMatrices(A, B, C, 10, 3, 10);

    std::vector<std::vector<int>> expected(10, std::vector<int>(10, 0));

    multiplyMatricesWithoutErrors(A, B, expected, 10, 3, 10);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// * Error 1.
// * Error 2.
// * Error 4.
// * Error 6.
// * Error 7.
// * Error 8.
// * Error 10: A row in matrix A contains more than one '1'!
// * Error 11.
// * Error 12.
// * Error 13.
// * Error 14.
// * Error 15.
// * Error 16.
// * Error 17.
// * Error 20.

TEST(MatrixMultiplicationTest10, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    };
    std::vector<std::vector<int>> B = {
        {0, 0, 0},
        {1, 1, 1},
        {2, 2, 2},
        {3, 3, 3},
        {4, 4, 4},
        {5, 5, 5},
        {6, 6, 6},
        {7, 7, 7},
        {8, 8, 8},
        {9, 9, 9}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));

    multiplyMatrices(A, B, C, 3, 10, 3);

    std::vector<std::vector<int>> expected(3, std::vector<int>(3, 0));

    multiplyMatricesWithoutErrors(A, B, expected, 3, 10, 3);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// * Error 1.
// * Error 2.
// * Error 4.
// * Error 6.
// * Error 12.
// * Error 13.
// * Error 16.
// * Error 19: Every row in matrix A contains the number 8!

// Finally, we multiply bigger matrices to see if more big values cause any more errors.
TEST(MatrixMultiplicationTest11, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
    };
    std::vector<std::vector<int>> B = {
        {10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
        {110, 120, 130, 140, 150, 160, 170, 180, 190, 200},
        {210, 220, 230, 240, 250, 260, 270, 280, 290, 300},
        {310, 320, 330, 340, 350, 360, 370, 380, 390, 400},
        {410, 420, 430, 440, 450, 460, 470, 480, 490, 500}
    };
    std::vector<std::vector<int>> C(4, std::vector<int>(10, 0));

    multiplyMatrices(A, B, C, 4, 5, 10);

    std::vector<std::vector<int>> expected(4, std::vector<int>(10, 0));
    multiplyMatricesWithoutErrors(A, B, expected, 4, 5, 10);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}
// The test doesn't show any additional errors so we can move on to the next step.

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
