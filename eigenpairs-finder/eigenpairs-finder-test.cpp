#include <iostream>
#include <fstream>

#include "eigenpairs-finder.h"

void conjugation_test() {
    Matrix<double> matrix;
    std::ifstream file;
    file.open("../matrix/matrix.txt");
    file >> matrix;
    file.close();

    std::cout << "matrix:" <<'\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';
    std::cout << conj(matrix);
}

void norm_test() {
    Matrix<double> vector;
    std::ifstream file;
    file.open("../matrix/vector.txt");
    file >> vector;
    file.close();

    std::cout << "vector:" << '\n';
    std::cout << vector;
    std::cout << '\n' << '\n';
    std::cout << "2-norm:" << '\n';
    std::cout << norm(vector);
}

// householder reduction tests//

template<typename T>
Matrix<T> hessenberg_decomposition_Q(Matrix<T> matrix) {
    if (matrix.get_n() != matrix.get_m()) {
        throw std::invalid_argument("only square matrices have hessenberg decomposition");
    }

    Matrix<T> Q = identity<T>(matrix.get_n());
    for (int k = 0; k < matrix.get_n() - 2; ++k) {
        Matrix<T> x = matrix[Slice(k + 1, matrix.get_n()), k];
        Matrix<T> v = householder_vector(x);

        Matrix<T> Q_k = identity<T>(matrix.get_n());
        Q_k[Slice(k+1, matrix.get_n()), Slice(k+1, matrix.get_n())] -= T(2) * v * conj(v);
        Q *= Q_k;

        auto first_submatrix = matrix[Slice(k + 1, matrix.get_n()), Slice(k, matrix.get_n())];
        first_submatrix -= T(2) * v * (conj(v) * first_submatrix);

        auto second_submatrix = matrix[Slice(0, matrix.get_n()), Slice(k + 1, matrix.get_n())];
        second_submatrix -= T(2) * (second_submatrix * v) * conj(v);

        for (int i = k + 2; i < matrix.get_n(); ++i) {
            matrix[i, k] = 0;
        }
    }
    return Q;
}

void householder_reduction_real_test() {
    Matrix<double> H;
    std::ifstream file;
    file.open("../matrix/matrix.txt");
    file >> H;
    file.close();

    H = H[Slice(0, 5)];
    Matrix<double> H_copy = H;

    std::cout << "matrix:" << '\n';
    std::cout << H;
    std::cout << '\n' << '\n';

    std::cout << "H:" << '\n';
    householder_reduction(H);;
    std::cout << H;
    std::cout << '\n' << '\n';

    std::cout << "Q:" << '\n';
    Matrix<double> Q = hessenberg_decomposition_Q(H_copy);
    std::cout << Q;
    std::cout << '\n' << '\n';

    std::cout << "QH(Q^*):" << '\n';
    std::cout << Q * H * conj(Q);
}

void householder_reduction_complex_test() {
    Matrix<std::complex<double>> H;
    std::ifstream file;
    file.open("../matrix/complex_matrix.txt");
    file >> H;
    file.close();

    Matrix<std::complex<double>> H_copy = H;

    std::cout << "matrix:" << '\n';
    std::cout << H;
    std::cout << '\n' << '\n';

    std::cout << "H:" << '\n';
    householder_reduction(H);
    std::cout << H;
    std::cout << '\n' << '\n';

    std::cout << "Q:" << '\n';
    Matrix<std::complex<double>> Q = hessenberg_decomposition_Q(H_copy);
    std::cout << Q;
    std::cout << '\n' << '\n';

    std::cout << "QH(Q^*):" << '\n';
    std::cout << Q * H * conj(Q);
}

int main() {
    conjugation_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    norm_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    householder_reduction_real_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    householder_reduction_complex_test();
}