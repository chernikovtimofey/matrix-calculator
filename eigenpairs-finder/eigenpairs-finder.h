#ifndef MATRIX_CALCULATOR_EIGENPAIRS_FINDER_H
#define MATRIX_CALCULATOR_EIGENPAIRS_FINDER_H

#include <complex>
#include "../matrix/matrix.h"

// class template representing conjugation operation
// T - type of element of matrix obtained by evaluating conjugation of the expression
// E - type of expression for conjugation
template<typename T, typename E>
class Conjugation : public MatrixExpression<T, Conjugation<T, E>> {
private:
    std::conditional_t<E::has_data, const E&, E> expression;

public:
    // access element in i-th row and j-th column of matrix obtained by evaluating conjugation of the expression
    T operator[](std::size_t i, std::size_t j) const;

    // getting size of matrix obtained by evaluating conjugation of the expression
    std::size_t get_n() const;
    std::size_t get_m() const;

    explicit Conjugation(const MatrixExpression<T, E> &expression);
};

// conjugation functions //

double conj(double val);

//template<typename T>
//std::complex<T> conj(std::complex<T> val);

template<typename T, typename E>
Conjugation<T, E> conj(const MatrixExpression<T, E> & expression);

// 2-norm of vector
template<typename T, typename E>
double norm(const MatrixExpression<T, E> &vector);

template<typename T>
Matrix<T> basis_vector(std::size_t size, std::size_t i);

template<typename T>
Matrix<T> identity(std::size_t size);

#include "eigenpairs-finder.tpp"

#endif //MATRIX_CALCULATOR_EIGENPAIRS_FINDER_H
