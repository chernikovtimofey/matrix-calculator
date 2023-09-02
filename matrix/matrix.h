#ifndef MATRIX_CALCULATOR_MATRIX_H
#define MATRIX_CALCULATOR_MATRIX_H

#include <vector>
#include "matrix-expression/matrix-expression.h"

// structure of slice
struct Slice {
    std::size_t start;
    std::size_t end;

    Slice();
    Slice(std::size_t start, std::size_t end);
};

// abstract class of submatrix associated with matrix
// Cont - type of nested container for inner representation of matrix data
// E - subclass of AbstractSubmatrix
template<typename Cont, typename E>
class AbstractSubmatrix : public MatrixExpression<typename Cont::value_type::value_type, AbstractSubmatrix<Cont, E>> {
private:
    Slice n_slice; // horizontal bound of submatrix
    Slice m_slice; // vertical bound of submatrix

protected:
    Cont &data; // reference to data of a matrix

public:
    // type of elements of matrix
    using value_type = Cont::value_type::value_type;

    // returns copy of element on i-th row and j-th column of submatrix
    value_type operator[](std::size_t i, std::size_t j) const;

    // substitute elements of matrix with elements of "other"
    AbstractSubmatrix operator=(const AbstractSubmatrix &other);

    // return size of submatrix
    std::size_t n() const;
    std::size_t m() const;

    // return bounds of submatrix
    std::size_t n_start() const;
    std::size_t n_end() const;
    std::size_t m_start() const;
    std::size_t m_end() const;

    explicit AbstractSubmatrix(Cont &data);
    AbstractSubmatrix(Cont &data, Slice n_slice);
    AbstractSubmatrix(Cont &data, Slice n_slice, Slice m_slice);
};

// Submatrix with no possibility of changing elements of matrix
// T - type of elements of matrix
template<typename T>
class ConstSubmatrix : public AbstractSubmatrix<const std::vector<std::vector<T>>, ConstSubmatrix<T>> {
    // inheriting all constructors
    using AbstractSubmatrix<const std::vector<std::vector<T>>, ConstSubmatrix<T>>::AbstractSubmatrix;
};

// Submatrix with possibility of changing elements of matrix
// T - type of elements of original matrix
template<typename T1>
class Submatrix : public AbstractSubmatrix<std::vector<std::vector<T1>>, Submatrix<T1>> {
    // inheriting all constructors
    using AbstractSubmatrix<std::vector<std::vector<T1>>, Submatrix<T1>>::AbstractSubmatrix;
public:
    // returns reference to element of matrix on i-th row and j-th column
    T1& operator[](std::size_t i, std::size_t j);

    // substitute elements of matrix with elements of "other"
    template<typename T2, typename E2>
    Submatrix operator=(const MatrixExpression<T2, E2> &other);

    // operations which change matrix
    template<typename T2, typename E2>
    Submatrix operator+=(const MatrixExpression<T2, E2> &other);

    template<typename T2, typename E2>
    Submatrix operator-=(const MatrixExpression<T2, E2> &other);

    Submatrix operator*=(T1 val);

    Submatrix operator/=(T1 val);
};

// class of matrix
// T - type of elements of matrix
template<typename T1>
class Matrix : public MatrixExpression<T1, Matrix<T1>> {
private:
    std::size_t N;
    std::size_t M;

protected:
    std::vector<std::vector<T1>> data;

public:
    // class Matrix contains data
    static constexpr bool has_data = true;

    // returns copy of element on i-th row and j-th column
    T1 operator[](std::size_t i, std::size_t j) const;

    // returns reference to element on i-th row and j-th column
    T1& operator[](std::size_t i, std::size_t j);

    // return i-th row
    ConstSubmatrix<T1> operator[](std::size_t i) const;
    Submatrix<T1> operator[](std::size_t i);

    // return submatrix with rows included in "n_slice"
    ConstSubmatrix<T1> operator[](Slice n_slice) const;
    Submatrix<T1> operator[](Slice n_slice);

    // return submatrix with part of m-th column with elements included in "n_slice"
    ConstSubmatrix<T1> operator[](Slice n_slice, std::size_t m) const;
    Submatrix<T1> operator[](Slice n_slice, std::size_t m);

    // return submatrix with part of i-th row with elements included in "m_slice"
    ConstSubmatrix<T1> operator[](std::size_t i, Slice m_slice) const;
    Submatrix<T1> operator[](std::size_t i, Slice m_slice);

    // return submatrix
    ConstSubmatrix<T1> operator[](Slice n_slice, Slice m_slice) const;
    Submatrix<T1> operator[](Slice n_slice, Slice m_slice);

    // return size of matrix
    std::size_t n() const;
    std::size_t m() const;

    // substitute elements of matrix with elements of "other"
    template<typename T2, typename E2>
    Matrix& operator=(const MatrixExpression<T2, E2> &other);

    // operations which change matrix
    template<typename T2, typename E2>
    Matrix& operator+=(const MatrixExpression<T2, E2> &other);

    template<typename T2, typename E2>
    Matrix& operator-=(const MatrixExpression<T2, E2> &other);

    Matrix& operator*=(T1 val);

    Matrix& operator/=(T1 val);

    Matrix();
    explicit Matrix(std::size_t size);
    Matrix(std::size_t N, std::size_t M);
    Matrix(const std::vector<std::vector<T1>> &data);

    template<typename T2, typename E2>
    Matrix(const MatrixExpression<T2, E2> &expression);

    // output function
    template<typename T>
    friend std::istream& operator>>(std::istream &istream, Matrix<T1> &matrix);
};

#include "matrix.tpp"

#endif //MATRIX_CALCULATOR_MATRIX_H
