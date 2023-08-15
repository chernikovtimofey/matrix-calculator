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

// abstract superclass template representing Submatrices
// Cont - type of nested containing for inner representation of expression data
template<typename E, typename Cont>
class AbstractSubmatrix : public MatrixExpression<AbstractSubmatrix<E, Cont>> {
private:
    Slice n_slice; // horizontal bound of expression
    Slice m_slice; // vertical bound of expression

protected:
    Cont &data;

public:
    static constexpr bool has_data = false;

    auto operator[](std::size_t n, std::size_t m) const;

    std::size_t n_size() const;
    std::size_t m_size() const;

    // bound access
    std::size_t n_start() const;
    std::size_t n_end() const;
    std::size_t m_start() const;
    std::size_t m_end() const;

    explicit AbstractSubmatrix(Cont &data);
    AbstractSubmatrix(Cont &data, Slice n_slice);
    AbstractSubmatrix(Cont &data, Slice n_slice, Slice m_slice);
};

template<typename E>
class VolatileMatrix : public MatrixExpression<VolatileMatrix<E>> {
public:
    auto& operator[](std::size_t n, std::size_t m);
};

// specific classes //

template<typename T>
class ConstSubmatrix : public AbstractSubmatrix<ConstSubmatrix<T>, const std::vector<std::vector<T>>> {
    // inheriting all constructors
    using AbstractSubmatrix<ConstSubmatrix<T>, const std::vector<std::vector<T>>>::AbstractSubmatrix;
};

template<typename T>
class Submatrix : public AbstractSubmatrix<Submatrix<T>, std::vector<std::vector<T>>>, public VolatileMatrix<Submatrix<T>> {

};

#include "matrix.tpp"

#endif //MATRIX_CALCULATOR_MATRIX_H
