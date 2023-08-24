cmake_minimum_required(VERSION 3.0)
project(matrix-calculator)

set(CMAKE_CXX_STANDARD 23)

add_executable(test main.cpp)

add_executable(
        matrix-test
        matrix/matrix-test.cpp
        matrix/matrix.h
        matrix/matrix.tpp
        matrix/matrix-expression/matrix-expression.h
        matrix/matrix-expression/matrix-expression.tpp
)

add_executable(
        eigenpairs-finder-test
        eigenpairs-finder/eigenpairs-finder-test.cpp
        eigenpairs-finder/eigenpairs-finder.h
        eigenpairs-finder/eigenpairs-finder.tpp
        matrix/matrix.h
)

#set(CMAKE_PREFIX_PATH "C:/Users/timcher/.vcpkg-clion/vcpkg/packages/eigen3_x86-windows/share/eigen3")
#
#find_package(Eigen3 CONFIG REQUIRED)
#target_link_libraries(eigenpairs-finder-test PRIVATE Eigen3::Eigen)