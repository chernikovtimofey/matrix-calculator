#ifndef MATRIX_CALCULATOR_MATRIXEXPRESSION_H
#define MATRIX_CALCULATOR_MATRIXEXPRESSION_H

// abstract class of expression with matrices
// T - type of elements of matrix obtained by evaluating expression
// E - subclass of MatrixExpression
template<typename T, typename E>
class MatrixExpression {
public:
    using value_type = T;

    // has_data equals true if class contains data (not reference to data) about elements of matrix
    static constexpr bool has_data = false;

    // returns copy of element on i-th row and j-th column of matrix obtained by evaluating expression
    T operator[](std::size_t i, std::size_t j) const;

    // return size of matrix obtained by evaluating expression
    std::size_t n() const;
    std::size_t m() const;
};

// throw exception if matrices are not match by row count, column count or column-row count respectively
template<typename T1, typename E1, typename T2, typename E2>
void check_n(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);

template<typename T1, typename E1, typename T2, typename E2>
void check_m(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);

template<typename T1, typename E1, typename T2, typename E2>
void check_mn(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);

// class of negation operation
// T - type of elements of matrix obtained by evaluating negation of the expression
// E - type of expression for negation
template<typename T, typename E>
class Negation : public MatrixExpression<T, Negation<T, E>> {
protected:
    std::conditional_t<E::has_data, const E&, E> expression;

public:
    // returns copy of element on i-th row and j-th column of matrix obtained by evaluating negation of the expression
    T operator[](std::size_t i, std::size_t j) const;

    // return size of matrix obtained by evaluating negation of the expression
    std::size_t n() const;
    std::size_t m() const;

    explicit Negation(const MatrixExpression<T, E>& expression);
};

// class of summation operation
// T - type of elements of matrix obtained by evaluating summation of the expressions
// E1, E2 - types of expressions for summation
template<typename T, typename E1, typename E2>
class Summation : public MatrixExpression<T, Summation<T, E1, E2>> {
protected:
    std::conditional_t<E1::has_data, const E1&, E1> first;
    std::conditional_t<E2::has_data, const E2&, E2> second;
public:
    // returns copy of element on i-th row and j-th column of matrix obtained by evaluating summation of the expressions
    T operator[](std::size_t i, std::size_t j) const;

    // return size of matrix obtained by evaluating summation of the expressions
    std::size_t n() const;
    std::size_t m() const;

    template<typename T1, typename T2>
    Summation(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);
};

// class of subtraction operation
// T - type of elements of matrix obtained by evaluating subtraction of the expressions
// E1, E2 - types of expressions for subtraction
template<typename T, typename E1, typename E2>
class Subtraction : public MatrixExpression<T, Subtraction<T, E1, E2>> {
protected:
    std::conditional_t<E1::has_data, const E1&, E1> first;
    std::conditional_t<E2::has_data, const E2&, E2> second;

public:
    // returns copy of element on i-th row and j-th column of matrix obtained by evaluating subtraction of the expressions
    T operator[](std::size_t i, std::size_t j) const;

    // return size of matrix obtained by evaluating subtraction of the expressions
    std::size_t n() const;
    std::size_t m() const;

    template<typename T1, typename T2>
    Subtraction(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);
};

// class of product operation
// T - type of elements of matrix obtained by evaluating product of the expressions
// E1, E2 - types of expressions for product
template<typename T, typename E1, typename E2>
class Product : public MatrixExpression<T, Product<T, E1, E2>> {
protected:
    std::conditional_t<E1::has_data, const E1&, E1> first;
    std::conditional_t<E2::has_data, const E2&, E2> second;

public:
    // returns copy of element on i-th row and j-th column of matrix obtained by evaluating product of the expressions
    T operator[](std::size_t i, std::size_t j) const;

    // return size of matrix obtained by evaluating product of the expressions
    std::size_t n() const;
    std::size_t m() const;

    template<typename T1, typename T2>
    Product(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second);
};

// class of product of matrix and scalar
// T - type of elements of matrix obtained by evaluating product of the expression and scalar
// E - type of expression for product
// V - type of scalar for product
template<typename T, typename E, typename V>
class ScalarProduct : public MatrixExpression<T, ScalarProduct<T, E, V>> {
protected:
    std::conditional_t<E::has_data, const E&, E> expression;
    V val;
public:
    // returns copy of element on i-th row and j-th column of matrix obtained by evaluating product of the expression and scalar
    T operator[](std::size_t i, std::size_t j) const;

    // return size of matrix obtained by evaluating product of the expression and scalar
    std::size_t n() const;
    std::size_t m() const;

    ScalarProduct(const MatrixExpression<T, E> &expression, V val);
};

// class of division of matrix by scalar
// T - type of elements of matrix obtained by evaluating division of the expression by scalar
// E - type of expression for division
// V - type of scalar for division
template<typename T, typename E, typename V>
class ScalarDivision : public MatrixExpression<T, ScalarDivision<T, E, V>> {
private:
    std::conditional_t<E::has_data, const E&, E> expression;
    V val;

public:
    // returns copy of element on i-th row and j-th column of matrix obtained by evaluating division of the expression by scalar
    T operator[](std::size_t i, std::size_t j) const;

    // return size of matrix obtained by evaluating division of the expression by scalar
    std::size_t n() const;
    std::size_t m() const;

    ScalarDivision(const MatrixExpression<T, E> &expression, V val);
};

// expression operations functions //
// NOTE: for reasons of possibility of deduction of return type of operations,
// those functions can be used only with expressions/scalars with a same value_type

template<typename T, typename E>
Negation<T, E> operator-(const MatrixExpression<T, E> &expression);

template<typename T, typename E1, typename E2>
Summation<T, E1, E2> operator+(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second);

template<typename T, typename E1, typename E2>
Subtraction<T, E1, E2> operator-(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second);

template<typename T, typename E1, typename E2>
Product<T, E1, E2> operator*(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second);

template<typename T, typename E>
ScalarProduct<T, E, T> operator*(const MatrixExpression<T, E> &expression, T val);

template<typename T, typename E>
ScalarProduct<T, E, T> operator*(T val, const MatrixExpression<T, E> &expression);

template<typename T, typename E>
ScalarDivision<T, E, T> operator/(const MatrixExpression<T, E> &expression, T val);

// output function //
template<typename T, typename E>
std::ostream& operator<<(std::ostream &ostream, const MatrixExpression<T, E> &expression);

#include "matrix-expression.tpp"
#endif //MATRIX_CALCULATOR_MATRIXEXPRESSION_H
