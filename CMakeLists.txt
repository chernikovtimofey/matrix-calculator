cmake_minimum_required(VERSION 3.0)
project(matrix-calculator)

set(CMAKE_CXX_STANDARD 23)

add_executable(test main.cpp)

add_executable(
        matrix-test
        matrix/matrix-test.cpp
#        matrix/matrix.h
#        matrix/matrix.tpp
#        matrix/matrix-expression/matrix-expression.h
#        matrix/matrix-expression/matrix-expression.tpp
)

add_executable(
        eigenpairs-finder-test
        eigenpairs-finder/eigenpairs-finder-test.cpp
#        eigenpairs-finder/eigenpairs-finder.h
#        eigenpairs-finder/eigenpairs-finder.tpp
#        matrix/matrix.h
)

add_executable(
        surface-operations-test
        surface-operations/operations-test.cpp
#        surface-operations/operations.h
#        surface-operations/operations.tpp
)