#include <iostream>
#include <fstream>
#include "matrix.h"

void ConstSubmatrix_test() {
    std::cout << "ConstSubmatrix test";
    std::cout << '\n' << '\n';

    auto data = std::vector<std::vector<double>>(10, std::vector<double>(5));
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            data[i][j] = j + i * data[0].size() + 1;
        }
    }

    std::cout << "matrix:" << '\n';
    std::cout << ConstSubmatrix(data);

    std::cout << '\n' << '\n';

    std::cout << "matrix[2:7]:" << '\n';
    std::cout << ConstSubmatrix(data, Slice(2,7));

    std::cout << '\n' << '\n';

    std::cout << "matrix[3:8, 0:4]:" << '\n';
    std::cout << ConstSubmatrix(data, Slice(3,8), Slice(0,4));
}

void arithmetic_test() {
    std::cout << "arithmetic test";
    std::cout << '\n' << '\n';

    auto data = std::vector<std::vector<double>>(10, std::vector<double>(5));
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            data[i][j] = j + i * data[0].size() + 1;
        }
    }

    std::cout << "m1:" << '\n';
    auto m1 = ConstSubmatrix(data, Slice(0,5));
    std::cout << m1;
    std::cout << '\n' << '\n';
    std::cout << "m2:" << '\n';
    auto m2 = ConstSubmatrix(data, Slice(5,10));
    std::cout << m2;
    std::cout << '\n' << '\n';
    std::cout << "-m1:" << '\n';
    std::cout << -m1;
    std::cout << '\n' << '\n';
    std::cout << "m1 + m2:" << '\n';
    std::cout << m1 + m2;
    std::cout << '\n' << '\n';
    std::cout << "m2 - m1:" << '\n';
    std::cout << m2 - m1;
    std::cout << '\n' << '\n';
    std::cout << "m1 * m2:" << '\n';
    std::cout << m1 * m2;
    std::cout << '\n' << '\n';
    std::cout << "m1 * 5.5:" << '\n';
    std::cout << m1 * 5.5;
    std::cout << '\n' << '\n';
    std::cout << "m1 / 3.3:" << '\n';
    std::cout << m1 / 3.3;
    std::cout << '\n' << '\n';
    std::cout << "-(m1 + m2 * m1 - m2 * 1.3):" << '\n';
    std::cout << -(m1 + m2 * m1 - m2 * 1.3);
}

void Submatrix_test() {
    std::cout << "submatrix test";
    std::cout << '\n' << '\n';

    auto data = std::vector<std::vector<double>>(10, std::vector<double>(5));
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            data[i][j] = j + i * data[0].size();
        }
    }

    auto matrix = Submatrix(data);
    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';
    Submatrix(data, Slice(1,7)) += Submatrix(data, Slice(3,9));
    std::cout << "matrix[1:7] += matrix[3:9]:" <<'\n';
    std::cout << matrix;
    std::cout <<'\n' << '\n';
    Submatrix(data, Slice(0, matrix.n()), Slice(2,5)) -= Submatrix(data, Slice(0, matrix.n()), Slice(0,3));
    std::cout << "matrix[:, 2:5] -= matrix[:, 0:3]:" << '\n';
    std::cout << matrix;
}

void Matrix_test() {
    std::cout << "matrix test";
    std::cout << '\n' << '\n';

    Matrix<double> matrix;
    std::ifstream file;
    file.open("../matrix/matrix.txt", std::ios::out);
    file >> matrix;
    file.close();

    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';
    matrix[2] = matrix[3];
    std::cout << "matrix[2] = matrix[3]:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';
    matrix[Slice(2, 4)] += matrix[Slice(3, 5)];
    std::cout << "matrix[2:4, 3:5]:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';
    matrix[Slice(4, 8), 1] -= matrix[Slice(6, 10), 3];
    std::cout << "matrix[4:8, 1] -= matrix[6:10, 3]:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';
    Matrix square_matrix = matrix[Slice(0, 5), Slice(0, 5)];
    std::cout << "square_matrix:" << '\n';
    std::cout << square_matrix;
}

int main() {
    ConstSubmatrix_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    arithmetic_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    Submatrix_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    Matrix_test();
}