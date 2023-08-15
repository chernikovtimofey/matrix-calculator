#include <iostream>
#include "matrix.h"

void ConstSubmatrix_test() {
    auto data = std::vector<std::vector<double>>(10, std::vector<double>(5));
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            data[i][j] = j + i * data[0].size() + 1;
        }
    }

    std::cout << "matrix:" << '\n';
    std::cout << ConstSubmatrix(data);

    std::cout << '\n' << '\n';

    std::cout << "submatrix with rows 2-6:" << '\n';
    std::cout << ConstSubmatrix(data, Slice(2, 7));

    std::cout << '\n' << '\n';

    std::cout << "submatrix with rows 3-7 and columns 0-3:" << '\n';
    std::cout << ConstSubmatrix(data, Slice(3, 8), Slice(0, 4));
}

void arithmetic_test() {
    auto data = std::vector<std::vector<double>>(10, std::vector<double>(5));
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            data[i][j] = j + i * data[0].size() + 1;
        }
    }

    std::cout << "matrix1:" << '\n';
    auto matrix1 = ConstSubmatrix(data, Slice(0, 5));
    std::cout << matrix1;
    std::cout << '\n' << '\n';
    std::cout << "matrix2:" << '\n';
    auto matrix2 = ConstSubmatrix(data, Slice(5, 10));
    std::cout << matrix2;
    std::cout << '\n' << '\n';
    std::cout << "negative matrix1:" << '\n';
    std::cout << -matrix1;
    std::cout << '\n' << '\n';
    std::cout << "sum of matrix1 and matrix2:" << '\n';
    std::cout << matrix1 + matrix2;
    std::cout << '\n' << '\n';
    std::cout << "substruction of matrix2 and matrix1:" << '\n';
    std::cout << matrix2 - matrix1;
    std::cout << '\n' << '\n';
    std::cout << "product of matrix1 and matrix2:" << '\n';
    std::cout << matrix1 * matrix2;
    std::cout << '\n' << '\n';
}

//void Submatrix_test() {
//    auto data = std::vector<std::vector<double>>(10, std::vector<double>(5));
//    for (int i = 0; i < data.size(); ++i) {
//        for (int j = 0; j < data[0].size(); ++j) {
//            data[i][j] = j + i * data[0].size();
//        }
//    }
//
//    std::cout << "matrix:" << '\n';
//    std::cout << Submatrix(data);
//    std::cout << '\n' << '\n';
//    std::cout << "rows 3-8 were multiplied by 4";
//    std::cout << "result:" << '\n';
//}

int main() {
    ConstSubmatrix_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    arithmetic_test();
//    Submatrix_test();
}