#include <cmath>
#include <complex>
#include "../matrix/matrix.h"

// Conjugation implementation //

template<typename T, typename E>
T Conjugation<T, E>::operator[](std::size_t i, std::size_t j) const {
    return conj(expression[j, i]);
}

template<typename T, typename E>
std::size_t Conjugation<T, E>::get_n() const {
    return expression.get_m();
}

template<typename T, typename E>
std::size_t Conjugation<T, E>::get_m() const {
    return expression.get_n();
}

template<typename T, typename E>
Conjugation<T, E>::Conjugation(const MatrixExpression<T, E> &expression_) :
expression(static_cast<const E&>(expression_)) {}

// conjugation functions implementation //

double conj(double val) {
    return val;
}

template<typename T, typename E>
Conjugation<T, E> conj(const MatrixExpression<T, E> & expression) {
    return Conjugation<T, E>(expression);
}

template<typename T, typename E>
double norm(const MatrixExpression<T, E>& vector) {
    if (vector.get_m() != 1) {
        throw std::invalid_argument("2-norm can be calculated for vectors only");
    }

    double square_sum = 0;
    for (int i = 0; i < vector.get_n(); ++i) {
        square_sum += std::abs<double>(vector[i, 0]) * std::abs<double>(vector[i, 0]);
    }
    return std::sqrt(square_sum);
}

template<typename T>
Matrix<T> basis_vector(std::size_t size, std::size_t i) {
    Matrix<T> result = Matrix<T>(size, 1);
    result[i, i] = 1;
    return result;
}

template<typename T>
Matrix<T> identity(std::size_t size) {
    Matrix<T> result = Matrix<T>(size);
    for (int i = 0; i < result.get_n(); ++i) {
        result[i, i] = 1;
    }
    return result;
}

template<typename E>
Matrix<double> householder_vector(const MatrixExpression<double, E> &expression) {
    if (expression.get_m() != 1) {
        throw std::invalid_argument("householder vector can be obtained only from another vector");
    }

    int sign = (expression[0, 0] >= 0 ? 1 : -1);
    Matrix<double> vector = expression;
    vector[0, 0] += sign * norm(vector);
    return vector / norm(vector);
}

template<typename T, typename E>
Matrix<std::complex<T>> householder_vector(const MatrixExpression<std::complex<T>, E> &expression) {
    if (expression.get_m() != 1) {
        throw std::invalid_argument("householder vector can be obtained only from another vector");
    }

    Matrix<std::complex<T>> vector = expression;
    vector[0, 0] += (vector[0, 0] * norm(vector)) / std::abs(vector[0, 0]);
    return vector / std::complex<T>(norm(vector));
}


template<typename T>
void householder_reduction(Matrix<T> &matrix) {
    if (matrix.get_n() != matrix.get_m()) {
        throw std::invalid_argument("only square matrices have hessenberg decomposition");
    }

    for (int k = 0; k < matrix.get_n() - 2; ++k) {
        Matrix<T> x = matrix[Slice(k + 1, matrix.get_n()), k];
        Matrix<T> v = householder_vector(x);

        auto first_submatrix = matrix[Slice(k + 1, matrix.get_n()), Slice(k, matrix.get_n())];
        first_submatrix -= T(2) * v * (conj(v) * first_submatrix);

        auto second_submatrix = matrix[Slice(0, matrix.get_n()), Slice(k + 1, matrix.get_n())];
        second_submatrix -= T(2) * (second_submatrix * v) * conj(v);

        for (int i = k+2; i < matrix.get_n(); ++i) {
            matrix[i, k] = 0;
        }
    }
}