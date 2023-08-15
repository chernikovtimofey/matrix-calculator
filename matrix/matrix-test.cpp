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

    std::cout << "m1:" << '\n';
    auto m1 = ConstSubmatrix(data, Slice(0, 5));
    std::cout << m1;
    std::cout << '\n' << '\n';
    std::cout << "m2:" << '\n';
    auto m2 = ConstSubmatrix(data, Slice(5, 10));
    std::cout << m2;
    std::cout << '\n' << '\n';
    std::cout << "negative m1:" << '\n';
    std::cout << -m1;
    std::cout << '\n' << '\n';
    std::cout << "sum of m1 and m2:" << '\n';
    std::cout << m1 + m2;
    std::cout << '\n' << '\n';
    std::cout << "substruction of m2 and m1:" << '\n';
    std::cout << m2 - m1;
    std::cout << '\n' << '\n';
    std::cout << "product of m1 and m2:" << '\n';
    std::cout << m1 * m2;
    std::cout << '\n' << '\n';
    std::cout << "product of m1 and 5.5:" << '\n';
    std::cout << m1 * 5.5;
    std::cout << '\n' << '\n';
    std::cout << "-(m1 + m2 * m1 - m2 * 1.3):" << '\n';
    std::cout << -(m1 + m2 * m1 - m2 * 1.3);
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