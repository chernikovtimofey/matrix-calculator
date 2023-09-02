#include <iostream>
#include <fstream>
#include <format>
//#include <Eigen/Eigenvalues>

#include "eigenpairs-finder.h"

void conjugation_test() {
    std::cout << "conjugation test";
    std::cout << '\n' <<'\n';

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
    std::cout << "norm test";
    std::cout << '\n' << '\n';

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

void real_hessenberg_test() {
    std::cout << "real matrix hessenberg decomposition test";
    std::cout << '\n' <<'\n';

    Matrix<double> matrix;
    std::ifstream file;
    file.open("../matrix/matrix.txt");
    file >> matrix;
    file.close();

    matrix = matrix[Slice(0, matrix.m())];
    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    auto Q = hessenberg(matrix);
    std::cout << "H:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    std::cout << "Q:" << '\n';
    std::cout << Q;
    std::cout << '\n' << '\n';

    std::cout << "QHQ*:" << '\n';
    std::cout << Q * matrix * conj(Q);
}

void complex_hessenberg_test() {
    std::cout << "complex matrix hessenberg decomposition test";
    std::cout << '\n' << '\n';

    Matrix<std::complex<double>> matrix;
    std::ifstream file;
    file.open("../matrix/complex_matrix.txt");
    file >> matrix;
    file.close();

    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    auto Q = hessenberg(matrix);
    std::cout << "H:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    std::cout << "Q:" << '\n';
    std::cout << Q;
    std::cout << '\n' << '\n';

    std::cout << "QHQ*:" << '\n';
    std::cout << Q * matrix * conj(Q);
}

void QR_step_test() {
    std::cout << "QR step test";
    std::cout << '\n' << '\n';

    Matrix<std::complex<double>> matrix;
    std::ifstream file;
    file.open("../matrix/complex_matrix.txt");
    file >> matrix;
    file.close();

    hessenberg(matrix);

    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    auto Q = QR_step(matrix);
    std::cout << "H:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    std::cout << "Q:" << '\n';
    std::cout << Q;
    std::cout << '\n' << '\n';

    std::cout << "QHQ*:" << '\n';
    std::cout << Q * matrix * conj(Q);
}

void complex_schur_real_test() {
    std::cout << "complex schur decomposition of real matrix test";
    std::cout << '\n' << '\n';

    Matrix<std::complex<double>> matrix;
    std::ifstream file;
    file.open("../matrix/matrix.txt");
    file >> matrix;
    file.close();

    matrix = matrix[Slice(0,4), Slice(0,4)];
    hessenberg(matrix);

    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    auto Q = complex_schur(matrix);

    std::cout << "Q:" << '\n';
    std::cout << Q;
    std::cout << '\n' << '\n';

    std::cout << "T:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    std::cout << "QTQ*:" << '\n';
    std::cout << Q * matrix * conj(Q);
}

void complex_schur_complex_test() {
    std::cout << "complex schur decomposition of complex matrix test";
    std::cout << '\n' << '\n';

    Matrix<std::complex<double>> matrix;
    std::ifstream file;
    file.open("../matrix/complex_matrix.txt");
    file >> matrix;
    file.close();

    hessenberg(matrix);

    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    auto Q = complex_schur(matrix);
    std::cout << "T:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    std::cout << "Q:" << '\n';
    std::cout << Q;
    std::cout << '\n' << '\n';

    std::cout << "QTQ*:" << '\n';
    std::cout << Q * matrix * conj(Q);
}

void complex_schur_eigenvector_real_test() {
    std::cout << "eigenvector of real matrix finder test";
    std::cout << '\n' << '\n';

    Matrix<std::complex<double>> matrix;
    std::ifstream file;
    file.open("../matrix/matrix.txt");
    file >> matrix;
    file.close();

    matrix = matrix[Slice(0,4), Slice(0,4)];
    hessenberg(matrix);

    hessenberg(matrix);
    complex_schur(matrix);

    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    auto id = identity<std::complex<double>>(matrix.n());

    auto eigenvectors = Matrix<std::complex<double>>(matrix.n());
    for (int i = 0; i < matrix.n(); ++i) {
        auto eigenvalue = matrix[i,i];
        auto eigenvector = schur_eigenvector(matrix, i);

        std::cout << std::format("Rayleigh quotient of eigenvector {}:", i) << '\n';
        std::cout << (conj(eigenvector) * (matrix * eigenvector)) / (conj(eigenvector) * eigenvector)[0,0];
        std::cout << '\n' << '\n';

        eigenvectors[Slice(0, matrix.n()), i] = eigenvector;
    }

    std::cout << "eigenvectors:" << '\n';
    std::cout << eigenvectors;
}

void complex_schur_eigenvector_complex_test() {
    std::cout << "eigenvector of complex matrix finder test";
    std::cout << '\n' << '\n';

    Matrix<std::complex<double>> matrix;
    std::ifstream file;
    file.open("../matrix/complex_matrix.txt");
    file >> matrix;
    file.close();

    hessenberg(matrix);
    complex_schur(matrix);

    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    auto id = identity<std::complex<double>>(matrix.n());

    auto eigenvectors = Matrix<std::complex<double>>(matrix.n());
    for (int i = 0; i < matrix.n(); ++i) {
        auto eigenvalue = matrix[i,i];
        auto eigenvector = schur_eigenvector(matrix, i);

        std::cout << std::format("Rayleigh quotient of eigenvector {}:", i) << '\n';
        std::cout << (conj(eigenvector) * (matrix * eigenvector)) / (conj(eigenvector) * eigenvector)[0,0];
        std::cout << '\n' << '\n';

        eigenvectors[Slice(0, matrix.n()), i] = eigenvector;
    }

    std::cout << "eigenvectors:" << '\n';
    std::cout << eigenvectors;
}

void eigenpairs_real_matrix_test() {
    std::cout << "eigenpairs of real matrix finder test";
    std::cout << '\n' << '\n';

    Matrix<std::complex<double>> matrix;
    std::ifstream file;
    file.open("../matrix/matrix.txt");
    file >> matrix;
    file.close();

    matrix = matrix[Slice(0,4), Slice(0,4)];

    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    auto eigenparis = eigenpairs(matrix);
    for (int i = 0; i < eigenparis.size(); ++i) {
        auto eigenvalue = eigenparis[i].first;
        auto eigenvector = eigenparis[i].second;

        std::cout << "eigenvector with eigenvalue " << eigenvalue << ":" << '\n';
        std::cout << eigenvector;
        std::cout << '\n' << '\n';

        std::cout << "Rayleigh quotient:" << '\n';
        std::cout << (conj(eigenvector) * (matrix * eigenvector)) / (conj(eigenvector) * eigenvector)[0,0];
        if (i != eigenparis.size()-1) {
            std::cout << '\n' << '\n';
        }
    }
}

void eigenpairs_test() {
    std::cout << "eigenpairs of complex matrix finder test";
    std::cout << '\n' << '\n';

    Matrix<std::complex<double>> matrix;
    std::ifstream file;
    file.open("../matrix/complex_matrix.txt");
    file >> matrix;
    file.close();

    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    auto eigenparis = eigenpairs(matrix);
    for (int i = 0; i < eigenparis.size(); ++i) {
        auto eigenvalue = eigenparis[i].first;
        auto eigenvector = eigenparis[i].second;

        std::cout << "eigenvector with eigenvalue " << eigenvalue << ":" << '\n';
        std::cout << eigenvector;
        std::cout << '\n' << '\n';

        std::cout << "Rayleigh quotient:" << '\n';
        std::cout << (conj(eigenvector) * (matrix * eigenvector)) / (conj(eigenvector) * eigenvector)[0,0];
        if (i != eigenparis.size()-1) {
            std::cout << '\n' << '\n';
        }
    }
}

void real_schur_test() {
    std::cout << "real schur test";
    std::cout << '\n' << '\n';

    Matrix<double> matrix;
    std::ifstream file;
    file.open("../matrix/matrix2.txt");
    file >> matrix;
    file.close();

    hessenberg(matrix);

    std::cout << "matrix:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    Matrix<double> Q = real_schur(matrix);

    std::cout << "Q:" << '\n';
    std::cout << Q << '\n' << '\n';

    std::cout << "T:" << '\n';
    std::cout << matrix;
    std::cout << '\n' << '\n';

    std::cout << "QTQ*:" << '\n';
    std::cout << Q * matrix * conj(Q);
}

int main() {
    conjugation_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    norm_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    real_hessenberg_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    complex_hessenberg_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    QR_step_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    complex_schur_real_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    complex_schur_complex_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    complex_schur_eigenvector_real_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    complex_schur_eigenvector_complex_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    eigenpairs_real_matrix_test();
    std::cout << "\n\n" << "-----------------" << "\n\n";
    eigenpairs_test();
//    std::cout << "\n\n" << "-----------------" << "\n\n";
//    real_schur_test();
}