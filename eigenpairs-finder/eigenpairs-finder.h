#ifndef MATRIX_CALCULATOR_EIGENPAIRS_FINDER_H
#define MATRIX_CALCULATOR_EIGENPAIRS_FINDER_H

#include <complex>
#include "../matrix/matrix.h"

// class of conjugation operation
// T - type of elements of matrix obtained by evaluating conjugation of the expression
// E - type of expression for conjugation
template<typename T, typename E>
class Conjugation : public MatrixExpression<T, Conjugation<T, E>> {
private:
    std::conditional_t<E::has_data, const E&, E> expression;

public:
    // returns copy of element on i-th row and j-th column of matrix obtained by evaluating conjugation of the expression
    T operator[](std::size_t i, std::size_t j) const;

    // return size of matrix obtained by evaluating conjugation of the expression
    std::size_t n() const;
    std::size_t m() const;

    explicit Conjugation(const MatrixExpression<T, E> &expression);
};

// conjugation functions //

double conj(double val);

template<typename T, typename E>
Conjugation<T, E> conj(const MatrixExpression<T, E> & expression);

// 2-norm of vector
template<typename T, typename E>
double norm(const MatrixExpression<T, E> &vector);

// returns identity matrix of size "size"
template<typename T>
Matrix<T> identity(std::size_t size);

// Hessenberg decomposition //

// return householder vector which used in householder projection
template<typename E>
Matrix<double> householder_vector(const MatrixExpression<double, E> &expression);

template<typename T, typename E>
Matrix<std::complex<T>> householder_vector(const MatrixExpression<std::complex<T>, E> &expression);

// functions which apply householder reflector with householder vector "v" to "matrix" //

// apply householder projection on left of "submatrix"
template<typename T1, typename T2, typename E2>
void left_h_transformation(Submatrix<T1> submatrix, const MatrixExpression<T2, E2> &v);

// apply householder projection on right of "submatrix"
template<typename T1, typename T2, typename E2>
void right_h_transformation(Submatrix<T1> submatrix, const MatrixExpression<T2, E2> &v);

// decomposes matrix A. A=QHQ* where Q - unitary matrix, H - upper Hessenberg matrix.
// H overwrites matrix, Q returned;
template<typename T>
Matrix<T> hessenberg(Matrix<T> &matrix);

// returns 2x2 givens matrix which transform vector (x, y)* to (0, z)
template<typename T>
Matrix<T> givens(T x, T y);

// performs QR step of hessenberg matrix by overriding matrix, returns Q matrix
template<typename T>
Matrix<T> QR_step(Matrix<T> &matrix);

// decomposes upper heisenberg matrix to QTQ* where T is upper triangular and Q is unitary.
// Overwrites matrix with T and returns Q
template<typename T>
Matrix<std::complex<T>> complex_schur(Matrix<std::complex<T>> &matrix);

// returns eigenvector associated with eigenvalue on value_index'th diagonal element of triangular matrix
template<typename T>
Matrix<std::complex<T>> schur_eigenvector(Matrix<std::complex<T>> matrix, std::size_t value_index);

// returns vector of eigenpairs of matrix
template<typename T>
std::vector<std::pair<std::complex<T>, Matrix<std::complex<T>>>> eigenpairs(Matrix<std::complex<T>> matrix);

#include "eigenpairs-finder.tpp"

#endif //MATRIX_CALCULATOR_EIGENPAIRS_FINDER_H
