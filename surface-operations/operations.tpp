#include <cmath>
#include "../matrix/matrix.h"
#include "../eigenpairs-finder/eigenpairs-finder.h"

template<typename T>
Matrix<T> rotation_matrix(T angle) {
    auto result = Matrix<T>(2);
    result[0,0] = std::cos(angle);
    result[0,1] = -std::sin(angle);
    result[1,0] = std::sin(angle);
    result[1,1] = std::cos(angle);
    return result;
}

template<typename T>
Matrix<T> projection_matrix(Matrix<T> direction) {
    direction /= T(norm(direction));
    return direction * conj(direction);
}

template<typename T>
Matrix<T> reflection_matrix(Matrix<T> direction) {
    auto orthogonal = Matrix<T>(2,1);

    if (std::abs(direction[0,0]) < ZERO) {
        orthogonal[0,0] = 1;
    }
    else if (std::abs(direction[1,0]) < ZERO) {
        orthogonal[1,0] = 1;
    }
    else {
        orthogonal[0,0] = T(1) / direction[0,0];
        orthogonal[1,0] = -T(1) / direction[1,0];
    }

    direction /= T(norm(direction));
    orthogonal /= T(norm(orthogonal));

    return direction * conj(direction) - orthogonal * conj(orthogonal);
}