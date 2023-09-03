#include <iostream>
#include <cmath>
#include <complex>
#include "operations.h"

void rotation_matrix_test() {
    std::cout << "rotation test";
    std::cout << '\n' << '\n';

    auto vector1 = Matrix<double>(2,1);
    vector1[0,0] = 1;
    vector1[1,0] = 0;

    std::cout << "vector1:" << '\n';
    std::cout << vector1;
    std::cout << '\n' << '\n';

    std::cout << "rotating vector1 by pi/2:" << '\n';
    std::cout << rotation_matrix<double>(M_PI/2) * vector1;
    std::cout << '\n' << '\n';

    std::cout << "rotating vector1 by pi:" << '\n';
    std::cout << rotation_matrix<double>(M_PI) * vector1;
    std::cout << '\n' << '\n';

    auto vector2 = Matrix<double>(2,1);
    vector2[0,0] = 83;
    vector2[1,0] = 6;

    std::cout << "vector2:" << '\n';
    std::cout << vector2;
    std::cout << '\n' << '\n';

    std::cout << "rotating vector2 by 1:" << '\n';
    std::cout << rotation_matrix<double>(1) * vector2;
    std::cout << '\n' << '\n';

    std::cout << "rotating back:" << '\n';
    std::cout << rotation_matrix<double>(double(-1)) * (rotation_matrix<double>(1) * vector2);

    auto vector3 = Matrix<std::complex<double>>(2,1);
    vector3[0,0] = std::complex<double>(2,33);
    vector3[1,0] = std::complex<double>(14,35);
    std::cout << '\n' << '\n';

    std::cout << "vector3:" << '\n';
    std::cout << vector3;
    std::cout << '\n' << '\n';

    std::cout << "rotating vector3 by pi/4:" << '\n';
    std::cout << rotation_matrix<std::complex<double>>(M_PI/4) * vector3;
    std::cout << '\n' << '\n';

    std::cout << "rotating back:" << '\n';
    std::cout << rotation_matrix<std::complex<double>>(-M_PI/4) * (rotation_matrix<std::complex<double>>(M_PI/4) * vector3);
}

void projection_matrix_test() {
    std::cout << "projection matrix test";
    std::cout << '\n' << '\n';

    auto vector1 = Matrix<double>(2,1);
    vector1[0,0] = 1;
    vector1[1,0] = 0;

    auto direction1 = Matrix<double>(2,1);
    direction1[0,0] = 0;
    direction1[1,0] = 1;

    std::cout << "vector1:" << '\n';
    std::cout << vector1;
    std::cout << '\n' << '\n';

    std::cout << "direction1:" << '\n';
    std::cout << direction1;
    std::cout << '\n' << '\n';

    std::cout << "projection of vector1 on direction1:" << '\n';
    std::cout << projection_matrix(direction1) * vector1;
    std::cout << '\n' << '\n';

    auto vector2 = Matrix<double>(2,1);
    vector2[0,0] = 2;
    vector2[1,0] = 3;

    std::cout << "vector2:" << '\n';
    std::cout << vector2;
    std::cout << '\n' << '\n';

    std::cout << "projection of vector2 on direction1:" << '\n';
    std::cout << projection_matrix(direction1) * vector2;
    std::cout << '\n' << '\n';

    auto direction2 = Matrix<double>(2,1);
    direction2[0,0] = 1;
    direction2[1,0] = 2;

    std::cout << "direction2:" << '\n';
    std::cout << direction2;
    std::cout << '\n' << '\n';

    std::cout << "projection of vector1 on direction2:" << '\n';
    std::cout << projection_matrix(direction2) * vector1;
    std::cout << '\n' << '\n';

    std::cout << "projection of vector2 on direction2:" << '\n';
    std::cout << projection_matrix(direction2) * vector2;
    std::cout << '\n' << '\n';

    auto vector3 = Matrix<std::complex<double>>(2,1);
    vector3[0,0] = std::complex<double>(6,7);
    vector3[1,0] = std::complex<double>(4,5);

    auto direction3 = Matrix<std::complex<double>>(2,1);
    direction3[0,0] = std::complex<double>(2,7);
    direction3[1,0] = std::complex<double>(0,10);

    std::cout << "vector3:" << '\n';
    std::cout << vector3;
    std::cout << '\n' << '\n';

    std::cout << "direction3:" << '\n';
    std::cout << direction3;
    std::cout << '\n' << '\n';

    std::cout << "projection of vector3 on direction3:" << '\n';
    std::cout << projection_matrix(direction3) * vector3;
}

void reflection_matrix_test() {
    std::cout << "reflection matrix test";
    std::cout << '\n' << '\n';

    auto vector1 = Matrix<double>(2,1);
    vector1[0,0] = 1;
    vector1[1,0] = 0;

    auto direction1 = Matrix<double>(2,1);
    direction1[0,0] = 0;
    direction1[1,0] = 1;

    std::cout << "vector1:" << '\n';
    std::cout << vector1;
    std::cout << '\n' << '\n';

    std::cout << "direction1:" << '\n';
    std::cout << direction1;
    std::cout << '\n' << '\n';

    std::cout << "reflection of vector1 along direction1:" << '\n';
    std::cout << reflection_matrix(direction1) * vector1;
    std::cout << '\n' << '\n';

    auto vector2 = Matrix<double>(2,1);
    vector2[0,0] = 2;
    vector2[1,0] = 3;

    std::cout << "vector2:" << '\n';
    std::cout << vector2;
    std::cout << '\n' << '\n';

    std::cout << "reflection of vector2 along direction1:" << '\n';
    std::cout << reflection_matrix(direction1) * vector2;
    std::cout << '\n' << '\n';

    auto direction2 = Matrix<double>(2,1);
    direction2[0,0] = 1;
    direction2[1,0] = 2;

    std::cout << "direction2:" << '\n';
    std::cout << direction2;
    std::cout << '\n' << '\n';

    std::cout << "reflection of vector1 along direction2:" << '\n';
    std::cout << reflection_matrix(direction2) * vector1;
    std::cout << '\n' << '\n';

    std::cout << "reflection of vector2 along direction2:" << '\n';
    std::cout << reflection_matrix(direction2) * vector2;
    std::cout << '\n' << '\n';

    auto vector3 = Matrix<std::complex<double>>(2,1);
    vector3[0,0] = std::complex<double>(6,7);
    vector3[1,0] = std::complex<double>(4,5);

    auto direction3 = Matrix<std::complex<double>>(2,1);
    direction3[0,0] = std::complex<double>(2,7);
    direction3[1,0] = std::complex<double>(0,10);

    std::cout << "vector3:" << '\n';
    std::cout << vector3;
    std::cout << '\n' << '\n';

    std::cout << "direction3:" << '\n';
    std::cout << direction3;
    std::cout << '\n' << '\n';

    std::cout << "projection of vector3 on direction3:" << '\n';
    std::cout << reflection_matrix(direction3) * vector3;
}

int main() {
    rotation_matrix_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    projection_matrix_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    reflection_matrix_test();
}