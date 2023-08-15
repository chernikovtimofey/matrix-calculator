#include <cstddef>
#include <type_traits>

#ifndef MATRIX_CALCULATOR_ABSTRACTMATRIX_H
#define MATRIX_CALCULATOR_ABSTRACTMATRIX_H

// abstract superclass template representing expression with matrices
// E - subclass of MatrixExpression
template<typename T, typename E>
class MatrixExpression {
public:
    using value_type = T;

    // type of elements in expression obtained by evaluating expression
    static constexpr bool has_data = false;

    // access element in n-th row and m-th column of expression obtained by evaluating expression
    T operator[](std::size_t n, std::size_t m) const;

    // getting size of expression obtained by evaluating expression
    std::size_t n_size() const;
    std::size_t m_size() const;
};

// throw exception if matrices are not match by rows, columns or columns-rows respectively
template<typename T1, typename E1, typename T2, typename E2>
void check_n(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);

template<typename T1, typename E1, typename T2, typename E2>
void check_m(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);

template<typename T1, typename E1, typename T2, typename E2>
void check_mn(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);

// class template representing negation operation
// E - type of expression
template<typename T, typename E>
class Negation : public MatrixExpression<T, Negation<T, E>> {
private:
    std::conditional_t<E::has_data, const E&, E> expression;

public:
    T operator[](std::size_t n, std::size_t m) const;

    std::size_t n_size() const;
    std::size_t m_size() const;

    explicit Negation(const MatrixExpression<T, E>& expression_);
};

// class representing sum operation
// E1, E2 - types of expressions
template<typename T, typename E1, typename E2>
class Summation : public MatrixExpression<T, Summation<T, E1, E2>> {
private:
    std::conditional_t<E1::has_data, const E1&, E1> first;
    std::conditional_t<E2::has_data, const E2&, E2> second;
public:
    T operator[](std::size_t n, std::size_t m) const;

    std::size_t n_size() const;
    std::size_t m_size() const;

    template<typename T1, typename T2>
    Summation(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);
};

template<typename T, typename E1, typename E2>
class Substruction : public MatrixExpression<T, Substruction<T, E1, E2>> {
private:
    std::conditional_t<E1::has_data, const E1&, E1> first;
    std::conditional_t<E2::has_data, const E2&, E2> second;

public:
    T operator[](std::size_t n, std::size_t m) const;

    std::size_t n_size() const;
    std::size_t m_size() const;

    template<typename T1, typename T2>
    Substruction(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);
};

template<typename T, typename E1, typename E2>
class Product : public MatrixExpression<T, Product<T, E1, E2>> {
private:
    std::conditional_t<E1::has_data, E1&, E1> first;
    std::conditional_t<E2::has_data, E2&, E2> second;

public:
    T operator[](std::size_t n, std::size_t m) const;

    std::size_t n_size() const;
    std::size_t m_size() const;

    template<typename T1, typename T2>
    Product(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);
};

template<typename T, typename E>
class ScalarProduct : public MatrixExpression<T, ScalarProduct<T, E>> {
private:
    std::conditional_t<E::has_data, E&, E> expression;
    T val;
public:
    auto operator[](std::size_t n, std::size_t m) const;

    std::size_t n_size() const;
    std::size_t m_size() const;

    ScalarProduct(const MatrixExpression<T, E> &expression, T val);
};

// expressions operation functions //

template<typename T, typename E>
Negation<T, E> operator-(const MatrixExpression<T, E> &expression);

template<typename T, typename E1, typename E2>
Summation<T, E1, E2> operator+(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second);

template<typename T, typename E1, typename E2>
Substruction<T, E1, E2> operator-(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second);

template<typename T, typename E1, typename E2>
Product<T, E1, E2> operator*(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second);

template<typename T, typename E>
ScalarProduct<T, E> operator*(const MatrixExpression<T, E> &expression, T val);

template<typename T, typename E>
ScalarProduct<T, E> operator*(T val, const MatrixExpression<T, E> &expression);

template<typename T, typename E>
std::ostream& operator<<(std::ostream &os, const MatrixExpression<T, E> &matrix);

#include "matrix-expression.tpp"
#endif //MATRIX_CALCULATOR_ABSTRACTMATRIX_H
