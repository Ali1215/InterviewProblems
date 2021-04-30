#include <iostream>
#include "matrix.h"

float arr_ptr[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

int main()
{
    // Test the first constructor
    Matrix A = Matrix(2, 3, 1.0);
    Matrix B = Matrix(2, 3, 2.0);
    const Matrix C = Matrix(3, 2, 3.0);

    std::cout << "A\n" << A << std::endl;
    std::cout << "B\n" << B << std::endl;

    // Test the second constructor
    Matrix D = Matrix(3, 2, arr_ptr);
    std::cout << "D\n" << D << std::endl;

    // // Test matrix addition
    std::cout << "A + B\n" << (A + B) << std::endl;

    // // Test matrix subtraction
    std::cout << "A - B\n" << (A - B) << std::endl;

    std::cout << "test" << std::endl;
    // // Test matrix multiplication
    std::cout << "B * C\n" << ((A+B) * C) << std::endl;

    // // Test unary negation
    std::cout << "-B\n" << (-B) << std::endl;

    // Test bracket operator
    // non-const
    A[0][0] = 0.0;
    std::cout << "modified A\n" << A << std::endl;
    // const
    std::cout << "C[0][0]\n" << C[0][0] << std::endl << std::endl;
    // C[0][0] = 1.0;  // compiler error!

    // Test transpose
    std::cout << "A.transpose()\n" << A.transpose() << std::endl;

    // Test submatrix
    std::cout << "D.submatrix(1, 3, 0, 1)\n"
              << D.submatrix(1, 3, 0, 1) << std::endl;

    // Test extraction operator
    Matrix E = Matrix(3, 2, 0.0);
    std::cout << "Please enter 6 floats to populate E" << std::endl;
    std::cin >> E;
    std::cout << "E after extraction\n" << E << std::endl;
//
    // Test copy constructor
    Matrix F = B;
    F[0][0] = 100;
    std::cout << "B after B's copy is modified\n" << B << std::endl;
    std::cout << "F after B's copy is modified\n" << F << std::endl;
    return 0;
}