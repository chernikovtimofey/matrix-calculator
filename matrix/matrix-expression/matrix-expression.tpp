#include <format>

// MatrixExpression implementation //

template<typename T, typename E>
T MatrixExpression<T, E>::operator[](std::size_t i, std::size_t j) const {
    return static_cast<const E&>(*this)[i, j];
}

template<typename T, typename E>
std::size_t MatrixExpression<T, E>::get_n() const {
    return static_cast<const E &>(*this).get_n();
}

template<typename T, typename E>
std::size_t MatrixExpression<T, E>::get_m() const {
    return static_cast<const E &>(*this).get_m();
}

// non-member MatrixExpression's functions implementation //

template<typename T1, typename E1, typename T2, typename E2>
void check_n(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second) {
    if (first.get_n() != second.get_n()) {
        throw std::invalid_argument("matrices rows don't match");
    }
}

template<typename T1, typename E1, typename T2, typename E2>
void check_m(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second) {
    if (first.get_m() != second.get_m()) {
        throw std::invalid_argument("matrices columns don't match");
    }
}

template<typename T1, typename E1, typename T2, typename E2>
void check_mn(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second) {
    if (first.get_m() != second.get_n() || first.get_m() == 0) {
        throw std::invalid_argument("matrices columns and rows don't match");
    }
}

// Negation implementation //
template<typename T, typename E>
T Negation<T, E>::operator[](std::size_t i, std::size_t j) const {
    return -expression[i, j];
}

template<typename T, typename E>
std::size_t Negation<T, E>::get_n() const {
    return expression.get_n();
}

template<typename T, typename E>
std::size_t Negation<T, E>::get_m() const {
    return expression.get_m();
}

template<typename T, typename E>
Negation<T, E>::Negation(const MatrixExpression<T, E>& expression_) : expression(static_cast<const E&>(expression_)) {}

// Summation implementation //

template<typename T, typename E1, typename E2>
T Summation<T, E1, E2>::operator[](std::size_t i, std::size_t j) const {
    return first[i, j] + second[i, j];
}

template<typename T, typename E1, typename E2>
std::size_t Summation<T, E1, E2>::get_n() const {
    return first.get_n();
}

template<typename T, typename E1, typename E2>
std::size_t Summation<T, E1, E2>::get_m() const {
    return second.get_m();
}

template<typename T, typename E1, typename E2>
template<typename T1, typename T2>
Summation<T, E1, E2>::Summation(const MatrixExpression<T1, E1> &first_, const MatrixExpression<T2, E2> &second_) :
first(static_cast<const E1&>(first_)), second(static_cast<const E2&>(second_)) {
    check_n(first, second);
    check_m(first, second);
}

// Subtraction implementation //

template<typename T, typename E1, typename E2>
T Subtraction<T, E1, E2>::operator[](std::size_t i, std::size_t j) const {
    return first[i, j] - second[i, j];
}

template<typename T, typename E1, typename E2>
std::size_t Subtraction<T, E1, E2>::get_n() const {
    return first.get_n();
}

template<typename T, typename E1, typename E2>
std::size_t Subtraction<T, E1, E2>::get_m() const {
    return second.get_m();
}

template<typename T, typename E1, typename E2>
template<typename T1, typename T2>
Subtraction<T, E1, E2>::Subtraction(const MatrixExpression<T1, E1> &first_, const MatrixExpression<T2, E2> &second_) :
first(static_cast<const E1&>(first_)), second(static_cast<const E2&>(second_)) {
    check_n(first, second);
    check_m(first, second);
}

// Product implementation //

template<typename T, typename E1, typename E2>
T Product<T, E1, E2>::operator[](std::size_t i, std::size_t j) const {
    T result = T();
    for (int k = 0; k < first.get_m(); ++k) {
        result += first[i, k] * second[k, j];
    }
    return result;
}

template<typename T, typename E1, typename E2>
std::size_t Product<T, E1, E2>::get_n() const {
    return first.get_n();
}

template<typename T, typename E1, typename E2>
std::size_t Product<T, E1, E2>::get_m() const {
    return second.get_m();
}

template<typename T, typename E1, typename E2>
template<typename T1, typename T2>
Product<T, E1, E2>::Product(const MatrixExpression<T1, E1> &first_, const MatrixExpression<T2, E2> &second_) :
first(static_cast<const E1&>(first_)), second(static_cast<const E2&>(second_)) {
    check_mn(first, second);
}

// ScalarProduct implementation//
template<typename T, typename E, typename V>
T ScalarProduct<T, E, V>::operator[](std::size_t i, std::size_t j) const {
    return expression[i, j] * val;
}

template<typename T, typename E, typename V>
std::size_t ScalarProduct<T, E, V>::get_n() const {
    return expression.get_n();
}

template<typename T, typename E, typename V>
std::size_t ScalarProduct<T, E, V>::get_m() const {
    return expression.get_m();
}

template<typename T, typename E, typename V>
ScalarProduct<T, E, V>::ScalarProduct(const MatrixExpression<T, E> &expression_, V val_) :
expression(static_cast<const E&>(expression_)), val(val_) {}

// expression operations functions implementation //

template<typename T, typename E>
Negation<T, E> operator-(const MatrixExpression<T, E> &expression) {
    return Negation<T, E>(expression);
}

template<typename T, typename E1, typename E2>
Summation<T, E1, E2> operator+(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second) {
    return Summation<T, E1, E2>(first, second);
}

template<typename T, typename E1, typename E2>
Subtraction<T, E1, E2> operator-(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second) {
    return Subtraction<T, E1, E2>(first, second);
}

template<typename T, typename E1, typename E2>
Product<T, E1, E2> operator*(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second) {
    return Product<T, E1, E2>(first, second);
}

template<typename T, typename E>
ScalarProduct<T, E, T> operator*(const MatrixExpression<T, E> &expression, T val) {
    return ScalarProduct<T, E, T>(expression, val);
}

template<typename T, typename E>
ScalarProduct<T, E, T> operator*(T val, const MatrixExpression<T, E> &expression) {
    return expression * val;
}

template<typename T, typename E>
std::ostream& operator<<(std::ostream &ostream, const MatrixExpression<T, E> &matrix) {
    if (matrix.get_n() > 0) {
        ostream << matrix.get_n() << " " << matrix.get_m() << '\n';

        int max_length = 1;
        for (int i = 0; i < matrix.get_n(); ++i) {
            for (int j = 0; j < matrix.get_m(); ++j) {
                int length = std::format("{}", matrix[i, j]).length();
                if (length > max_length) {
                    max_length = length;
                }
            }
        }

        int element_space = max_length + 2;
        ostream << std::format("{:<{}}", matrix[0, 0], element_space);
        for (int j = 1; j < matrix.get_m(); ++j) {
            ostream << std::format("{:<{}}", matrix[0, j], element_space);
        }
        for (int i = 1; i < matrix.get_n(); ++i) {
            ostream << '\n' << std::format("{:<{}}", matrix[i, 0], element_space);
            for (int j = 1; j < matrix.get_m(); ++j) {
                ostream << std::format("{:<{}}", matrix[i, j], element_space);
            }
        }
    }
    return ostream;
}