#ifndef MATRIX_CALCULATOR_OPERATIONS_H
#define MATRIX_CALCULATOR_OPERATIONS_H

#include<cmath>
#include "../matrix/matrix.h"

// returns matrix which rotates vector of size 2 by an "angle"
template<typename T>
Matrix<T> rotation_matrix(T angle);

// returns matrix which projects vector on the line directed by "direction" vector
template<typename T>
Matrix<T> projection_matrix(Matrix<T> direction);

// returns matrix which reflects vector along the line directed by "direction" vector
template<typename T>
Matrix<T> reflection_matrix(Matrix<T> direction);

#include"operations.tpp"

#endif //MATRIX_CALCULATOR_OPERATIONS_H
