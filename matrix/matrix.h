#ifndef MATRIX_CALCULATOR_MATRIX_H
#define MATRIX_CALCULATOR_MATRIX_H

#include <vector>
#include "matrix-expression/matrix-expression.h"

// struct representing slice
struct Slice {
    std::size_t start;
    std::size_t end;

    Slice();
    Slice(std::size_t start, std::size_t end);
};

// abstract classes //

// abstract superclass template representing submatrices
// Cont - type of nested containing for inner representation of expression data
// E - type of specific submatrix
template<typename Cont, typename E>
class AbstractSubmatrix : public MatrixExpression<typename Cont::value_type::value_type, AbstractSubmatrix<Cont, E>> {
private:
    Slice n_slice; // horizontal bound of submatrix
    Slice m_slice; // vertical bound of submatrix

protected:
    Cont &data; // reference to data of a matrix

public:
    // type of elements of original matrix
    using value_type = Cont::value_type::value_type;

    // access to elements of original matrix in this submatrix
    value_type operator[](std::size_t i, std::size_t j) const;

    // operation of substitution elements of matrix in this submatrix by elements of "other"
    AbstractSubmatrix operator=(const AbstractSubmatrix &other);

    // getting size of matrix in this submatrix
    std::size_t get_n() const;
    std::size_t get_m() const;

    // bound access
    std::size_t n_start() const;
    std::size_t n_end() const;
    std::size_t m_start() const;
    std::size_t m_end() const;

    explicit AbstractSubmatrix(Cont &data);
    AbstractSubmatrix(Cont &data, Slice n_slice);
    AbstractSubmatrix(Cont &data, Slice n_slice, Slice m_slice);
};

// specific classes //

// Submatrix with no possibility of changing elements of matrix
// T - type of elements of original matrix
template<typename T>
class ConstSubmatrix : public AbstractSubmatrix<const std::vector<std::vector<T>>, ConstSubmatrix<T>> {
    // inheriting all constructors
    using AbstractSubmatrix<const std::vector<std::vector<T>>, ConstSubmatrix<T>>::AbstractSubmatrix;
};

// Submatrix with possibility of changing elements of matrix in this submatrix
// T - type of elements of original matrix
template<typename T1>
class Submatrix : public AbstractSubmatrix<std::vector<std::vector<T1>>, Submatrix<T1>> {
    using AbstractSubmatrix<std::vector<std::vector<T1>>, Submatrix<T1>>::AbstractSubmatrix;
public:
    // access to elements of original matrix in this submatrix
    T1& operator[](std::size_t i, std::size_t j);

    // operation of substitution elements of matrix in this submatrix by elements of "other"
    template<typename T2, typename E2>
    Submatrix operator=(const MatrixExpression<T2, E2> &other);

    template<typename T2, typename E2>
    Submatrix operator+=(const MatrixExpression<T2, E2> &other);

    template<typename T2, typename E2>
    Submatrix operator-=(const MatrixExpression<T2, E2> &other);

    template<typename T2, typename E2>
    Submatrix operator*=(const MatrixExpression<T2, E2> &other);

    Submatrix operator*=(T1 val);

    Submatrix operator/=(T1 val);
};

// class representing matrix
// T - type of elements in matrix
template<typename T1>
class Matrix : public MatrixExpression<T1, Matrix<T1>> {
private:
    std::size_t n;
    std::size_t m;

protected:
    std::vector<std::vector<T1>> data;

public:
    static constexpr bool has_data = true;

    T1 operator[](std::size_t i, std::size_t j) const;
    T1& operator[](std::size_t i, std::size_t j);

    // access to elements of matrix
    ConstSubmatrix<T1> operator[](std::size_t i) const;
    Submatrix<T1> operator[](std::size_t i);

    // access to elements of matrix by submatrix
    ConstSubmatrix<T1> operator[](Slice n_slice) const;
    Submatrix<T1> operator[](Slice n_slice);

    ConstSubmatrix<T1> operator[](Slice n_slice, std::size_t m) const;
    Submatrix<T1> operator[](Slice n_slice, std::size_t m);

    ConstSubmatrix<T1> operator[](std::size_t n, Slice m_slice) const;
    Submatrix<T1> operator[](std::size_t n, Slice m_slice);

    ConstSubmatrix<T1> operator[](Slice n_slice, Slice m_slice) const;
    Submatrix<T1> operator[](Slice n_slice, Slice m_slice);

    // getting size of matrix
    std::size_t get_n() const;
    std::size_t get_m() const;

    template<typename T2, typename E2>
    Matrix& operator=(const MatrixExpression<T2, E2> &other);

    template<typename T2, typename E2>
    Matrix& operator+=(const MatrixExpression<T2, E2> &other);

    template<typename T2, typename E2>
    Matrix& operator-=(const MatrixExpression<T2, E2> &other);

    template<typename T2, typename E2>
    Matrix& operator*=(const MatrixExpression<T2, E2> &other);

    Matrix& operator*=(T1 val);

    Matrix& operator/=(T1 val);

    Matrix();
    explicit Matrix(std::size_t size);
    Matrix(std::size_t row_count, std::size_t column_count);
    Matrix(const std::vector<std::vector<T1>> &data);

    template<typename T2, typename E2>
    Matrix(const MatrixExpression<T2, E2> &expression);

    template<typename T>
    friend std::istream& operator>>(std::istream &istream, Matrix<T1> &matrix);
};

#include "matrix.tpp"

#endif //MATRIX_CALCULATOR_MATRIX_H
