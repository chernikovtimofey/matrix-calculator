#include <cmath>
#include <complex>
#include "../matrix/matrix.h"

// all numbers less than ZERO are considered 0
const double ZERO = 1e-15;

// Conjugation implementation //

template<typename T, typename E>
T Conjugation<T, E>::operator[](std::size_t i, std::size_t j) const {
    return conj(expression[j,i]);
}

template<typename T, typename E>
std::size_t Conjugation<T, E>::n() const {
    return expression.m();
}

template<typename T, typename E>
std::size_t Conjugation<T, E>::m() const {
    return expression.n();
}

template<typename T, typename E>
Conjugation<T, E>::Conjugation(const MatrixExpression<T, E> &expression_) :
expression(static_cast<const E&>(expression_)) {}

// conjugation functions implementation //

double conj(double val) { return val; }

template<typename T, typename E>
Conjugation<T, E> conj(const MatrixExpression<T, E> & expression) {
    return Conjugation<T, E>(expression);
}

template<typename T, typename E>
double norm(const MatrixExpression<T, E>& vector) {
    if (vector.m() != 1) {
        throw std::invalid_argument("2-norm can be calculated for vectors only");
    }

    double square_sum = 0;
    for (int i = 0; i < vector.n(); ++i) {
        square_sum += std::abs<double>(vector[i,0]) * std::abs<double>(vector[i,0]);
    }
    return std::sqrt(square_sum);
}

template<typename T>
Matrix<T> identity(std::size_t size) {
    Matrix<T> result = Matrix<T>(size);
    for (int i = 0; i < size; ++i) {
        result[i,i] = 1;
    }
    return result;
}

// Hessenberg decomposition implementation //

template<typename E>
Matrix<double> householder_vector(const MatrixExpression<double, E> &expression) {
    if (expression.m() != 1) {
        throw std::invalid_argument("householder vector can be obtained only from another vector");
    }

    // both signs are appropriate, choose which one makes the longest hessenberg vector to improve stability
    int sign = (expression[0,0] >= 0 ? 1 : -1);
    Matrix<double> vector = expression;
    vector[0,0] += sign * norm(vector);
    return vector / norm(vector);
}

template<typename T, typename E>
Matrix<std::complex<T>> householder_vector(const MatrixExpression<std::complex<T>, E> &expression) {
    if (expression.m() != 1) {
        throw std::invalid_argument("householder vector can be obtained only from another vector");
    }

    Matrix<std::complex<T>> vector = expression;
    vector[0,0] += (vector[0,0] * norm(vector)) / std::abs(vector[0, 0]);
    return vector / std::complex<T>(norm(vector));
}

template<typename T1, typename T2, typename E2>
void left_h_transformation(Submatrix<T1> submatrix, const MatrixExpression<T2, E2> &v) {
    submatrix -= T2(2) * v * (conj(v) * submatrix);
}

template<typename T1, typename T2, typename E2>
void right_h_transformation(Submatrix<T1> submatrix, const MatrixExpression<T2, E2> &v) {
    submatrix -= T2(2) * (submatrix * v) * conj(v);
}

template<typename T>
Matrix<T> hessenberg(Matrix<T> &matrix) {
    if (matrix.n() != matrix.m()) {
        throw std::invalid_argument("only square matrices have Hessenberg decomposition");
    }

    auto Q = identity<T>(matrix.n());

    for (int k = 0; k < matrix.n()-2; ++k) {
        // creates householder vector
        auto x = matrix[Slice(k+1, matrix.n()), k];
        auto v = householder_vector(x);

        // apply householder transformation to both sides of the matrix in order to reach similarity
        left_h_transformation(matrix[Slice(k+1, matrix.n()), Slice(k, matrix.n())], v);

        right_h_transformation(matrix[Slice(0, matrix.n()), Slice(k+1, matrix.n())], v);

        auto Q_submatrix = Q[Slice(1, matrix.n()), Slice(k+1, matrix.n())];

        // updates matrix Q of hessenberg decomposition
        if (k == 0) { Q_submatrix -= T(2) * v * conj(v); }
        else { right_h_transformation(Q_submatrix, v); }
    }
    return Q;
}

template<typename T>
Matrix<T> givens(T x, T y) {
    auto result = Matrix<T>(2);

    double abs_x = std::abs(x);
    double abs_y = std::abs(y);

    result[0,0] = x / std::sqrt(abs_x * abs_x + abs_y * abs_y);
    result[0,1] = conj(-y) / std::sqrt(abs_x * abs_x + abs_y * abs_y);
    result[1,0] = conj(-result[0,1]);
    result[1,1] = conj(result[0,0]);
    return result;
}

template<typename T>
Matrix<T> QR_step(Matrix<T> &matrix) {
    if (matrix.n() != matrix.m()) {
        throw std::invalid_argument("QR step can be applied only to square matrix");
    }

    auto Q = identity<T>(matrix.n());

    // performs QR decomposition via multiplying by givens matrix on left
    auto givenses = std::vector<Matrix<T>>(matrix.n()-1);
    for (int k = 0; k < matrix.n()-1; ++k) {
        if (std::abs(matrix[k+1, k]) > ZERO) {
            givenses[k] = givens(matrix[k, k], matrix[k + 1, k]);
            auto submatrix = matrix[Slice(k, k+2), Slice(k, matrix.n())];
            submatrix = conj(givenses[k]) * submatrix;

            // updates matrix Q of decomposition
            auto Q_submatrix = Q[Slice(0, k+2), Slice(k, k + 2)];
            Q_submatrix = Q_submatrix * givenses[k];
        }
    }

    // multiplying the matrix by Q on right
    for (int k = 0; k < matrix.n()-1; ++k) {
        if (givenses[k].n() != 0) {
            auto submatrix = matrix[Slice(0,k+2), Slice(k,k+2)];
            submatrix = submatrix * givenses[k];
        }
    }
    return Q;
}

template<typename T>
Matrix<std::complex<T>> complex_schur(Matrix<std::complex<T>> &matrix) {
    auto Q = identity<std::complex<T>>(matrix.n());
    auto id = Q;
    for (int n = matrix.n(); n >= 2; --n) {
        do {
            auto tr = matrix[n-2,n-2] + matrix[n-1,n-1];
            auto det = matrix[n-2,n-2] * matrix[n-1,n-1] - matrix[n-2,n-1] * matrix[n-1,n-2];

            // computes Wilkinson shift
            std::complex<T> shift = (tr + std::sqrt(tr * tr - std::complex<T>(4) * det)) / std::complex<T>(2);

            // performs QR step with shift on the matrix
            matrix -= shift * id;
            Q = Q * QR_step(matrix);
            matrix += shift * id;
        } while (std::abs(matrix[n-1, n-2]) > ZERO);
        // after making element on the left of n-th diagonal element sufficiently small
        // deflates matrix and chooses different Wilkinson shift
    }
    return Q;
}

template<typename T>
Matrix<std::complex<T>> schur_eigenvector(Matrix<std::complex<T>> matrix, std::size_t value_index) {
    matrix -= matrix[value_index, value_index] * identity<std::complex<T>>(matrix.n());
    Matrix<std::complex<T>> result = Matrix<T>(matrix.n(), 1);
    result[value_index,0] = 1;

    // solves triangular system which finds eigenvalue of the desired value
    for (std::size_t i = value_index - 1; i < matrix.n(); --i) {
        for (std::size_t j = i+1; j < matrix.n(); ++j) {
            result[i,0] -= matrix[i, j] * result[j, 0];
        }
        result[i,0] /= matrix[i, i];
    }
    return result / std::complex<T>(norm(result));
}

template<typename T>
std::vector<std::pair<std::complex<T>, Matrix<std::complex<T>>>> eigenpairs(Matrix<std::complex<T>> matrix) {
    if (matrix.n() != matrix.m()) {
        throw std::invalid_argument("only square matrix is allowed");
    }

    auto Q1 = hessenberg(matrix);
    auto Q2 = complex_schur(matrix);

    auto id = identity<std::complex<T>>(matrix.n());

    auto result = std::vector<std::pair<std::complex<T>, Matrix<std::complex<T>>>>(matrix.n());
    for (int i = 0; i < matrix.n(); ++i) {
        auto eigenvalue = matrix[i, i];
        Matrix<std::complex<T>> eigenvector = Q1 * (Q2 * schur_eigenvector(matrix, i)) ;
        result[i] = (std::make_pair(eigenvalue, eigenvector));
    }

    return result;
}

// extra function. Isn't required to find eigenpairs but cost me a lot of time to implement :(
// decomposes real matrix to QTQ* where T is block-upper triangular and Q is unitary
template<typename T>
Matrix<T> real_schur(Matrix<T> &matrix) {
    Matrix<T> Q = identity<T>(matrix.n());

    std::size_t p = matrix.n();
    while (p > 2) {
        int count = 1;

        T s = matrix[p-2,p-2] + matrix[p-1,p-1];
        T t = matrix[p-2,p-2] * matrix[p-1,p-1] - matrix[p-2,p-1] * matrix[p-1,p-2];

        Matrix<T> column = Matrix<T>(3,1);
        column[0,0] = matrix[0,0] * matrix[0,0] + matrix[0,1] * matrix[1,0] - s * matrix[0,0] + t;
        column[1,0] = matrix[1,0] * (matrix[0,0] + matrix[1,1] - s);
        column[2,0] = matrix[1,0] * matrix[2,1];

        auto v = householder_vector(column);
        left_h_transformation(matrix[Slice(0,3), Slice(0, matrix.n())],v);
        std::size_t r = (p > 3 ? 4 : 3);
        right_h_transformation(matrix[Slice(0,r), Slice(0,3)], v);

        right_h_transformation(Q[Slice(0,matrix.n()), Slice(0,3)], v);

        for (std::size_t k = 0; k < p-3; ++k) {
            ++count;

            column[0,0] = matrix[k+1,k];
            column[1,0] = matrix[k+2,k];
            column[2,0] = matrix[k+3,k];

            v = householder_vector(column);
            left_h_transformation(matrix[Slice(k+1,k+4), Slice(k, matrix.n())], v);
            r = (k+5 < p ? k+5 : p);
            right_h_transformation(matrix[Slice(0,r), Slice(k+1,k+4)], v);

            right_h_transformation(Q[Slice(0,matrix.n()), Slice(k+1,k+4)], v);
        }

        ++count;

        column = Matrix<T>(2,1);
        column[0,0] = matrix[p-2,p-3];
        column[1,0] = matrix[p-1,p-3];

        v = householder_vector(column);
        left_h_transformation(matrix[Slice(p-2,p), Slice(p-3,matrix.n())], v);
        right_h_transformation(matrix[Slice(0, matrix.n()), Slice(p-2,p)], v);

        right_h_transformation(Q[Slice(0, matrix.n()), Slice(p-2,p)], v);

        if (std::abs(matrix[p-1,p-2]) < ZERO) { p -= 1; }
        else if (std::abs(matrix[p-2,p-3]) < ZERO) { p -= 2; }
    }
    return Q;
}