#include <cstddef>
#include <type_traits>

#ifndef MATRIX_CALCULATOR_ABSTRACTMATRIX_H
#define MATRIX_CALCULATOR_ABSTRACTMATRIX_H

// abstract superclass template representing expression with matrices
// E - subclass of MatrixExpression
template<typename E>
class MatrixExpression {
public:
    // type of elements in expression obtained by evaluating expression
    static constexpr bool has_data = E::has_data;

    // access element in n-th row and m-th column of expression obtained by evaluating expression
    auto operator[](std::size_t n, std::size_t m) const;

    // getting size of expression obtained by evaluating expression
    std::size_t n_size() const;
    std::size_t m_size() const;
};

// throw exception if matrices are not match by rows, columns or columns-rows respectively
template<typename T>
void check_n(const MatrixExpression<T> &first, const MatrixExpression<T> &second);

template<typename T>
void check_m(const MatrixExpression<T> &first, const MatrixExpression<T> &second);

template<typename T>
void check_mn(const MatrixExpression<T> &first, const MatrixExpression<T> &second);

// class template representing negation operation
// E - type of expression
template<typename E>
class Negation : public MatrixExpression<Negation<E>> {
private:
    std::conditional_t<E::has_data, const E&, E> expression;

public:
    auto operator[](std::size_t n, std::size_t m) const;

    std::size_t n_size() const;
    std::size_t m_size() const;

    explicit Negation(const MatrixExpression<E>& expression_);
};

// class representing sum operation
// E1, E2 - types of expressions
template<typename E1, typename E2>
class Summation : public MatrixExpression<Summation<E1, E2>> {
private:
    std::conditional_t<E1::has_data, const E1&, E1> first;
    std::conditional_t<E2::has_data, const E2&, E2> second;
public:
    auto operator[](std::size_t n, std::size_t m) const;

    std::size_t n_size() const;
    std::size_t m_size() const;

    Summation(const MatrixExpression<E1>& first_, const MatrixExpression<E2>& second);
};

template<typename E1, typename E2>
class Substruction : public MatrixExpression<Substruction<E1, E2>> {
private:
    std::conditional_t<MatrixExpression<E1>::has_data, const E1&, E1> first;
    std::conditional_t<MatrixExpression<E2>::has_data, const E2&, E2> second;

public:
    auto operator[](std::size_t n, std::size_t m) const;

    std::size_t n_size() const;
    std::size_t m_size() const;

    Substruction(const MatrixExpression<E1> &first, const MatrixExpression<E2> &second);
};

template<typename E1, typename E2>
class Product : public MatrixExpression<Product<E1, E2>> {
private:
    std::conditional_t<MatrixExpression<E1>::has_data, E1&, E1> first;
    std::conditional_t<MatrixExpression<E2>::has_data, E2&, E2> second;

public:
    auto operator[](std::size_t n, std::size_t m) const;

    std::size_t n_size() const;
    std::size_t m_size() const;

    Product(const MatrixExpression<E1> &first, const MatrixExpression<E2> &second);
};

template<typename E, typename V>
class ScalarProduct : public MatrixExpression<ScalarProduct<E, V>> {
private:
    std::conditional_t<E::has_data, E&, E> expression;
    V val;
public:
    auto operator[](std::size_t n, std::size_t m) const;

    std::size_t n_size() const;
    std::size_t m_size() const;

    ScalarProduct(const MatrixExpression<E> &expression, V val);
};

// expressions operation functions //

template<typename E>
auto operator-(const MatrixExpression<E> &expression);

template<typename E1, typename E2>
auto operator+(const MatrixExpression<E1> &first, const MatrixExpression<E2> &second);

template<typename E1, typename E2>
auto operator-(const MatrixExpression<E1> &first, const MatrixExpression<E2> &second);

template<typename E1, typename E2>
auto operator*(const MatrixExpression<E1> &first, const MatrixExpression<E2> &second);

template<typename E>
std::ostream& operator<<(std::ostream &os, const MatrixExpression<E> &matrix);

#include "matrix-expression.tpp"
#endif //MATRIX_CALCULATOR_ABSTRACTMATRIX_H
