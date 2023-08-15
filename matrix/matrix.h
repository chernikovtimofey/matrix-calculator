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
template<typename Cont, typename E>
class AbstractSubmatrix : public MatrixExpression<typename Cont::value_type::value_type, AbstractSubmatrix<Cont, E>> {
private:
    Slice n_slice; // horizontal bound of expression
    Slice m_slice; // vertical bound of expression

protected:
    Cont &data;

public:
    using value_type = Cont::value_type::value_type;
    static constexpr bool has_data = false;

    value_type operator[](std::size_t n, std::size_t m) const;

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

template<typename T, typename E>
class VolatileMatrix : public MatrixExpression<T, VolatileMatrix<T, E>> {
public:
    T& operator[](std::size_t n, std::size_t m);
};

// specific classes //

template<typename T>
class ConstSubmatrix : public AbstractSubmatrix<const std::vector<std::vector<T>>, ConstSubmatrix<T>> {
    // inheriting all constructors
    using AbstractSubmatrix<const std::vector<std::vector<T>>, ConstSubmatrix<T>>::AbstractSubmatrix;
};

template<typename T>
class Submatrix : public AbstractSubmatrix<std::vector<std::vector<T>>, Submatrix<T>>, public VolatileMatrix<T, Submatrix<T>> {

};

#include "matrix.tpp"

#endif //MATRIX_CALCULATOR_MATRIX_H
