#include <iomanip>

// MatrixExpression implementation //

template<typename T, typename E>
T MatrixExpression<T, E>::operator[](std::size_t i, std::size_t j) const {
    return static_cast<const E&>(*this)[i, j];
}

template<typename T, typename E>
std::size_t MatrixExpression<T, E>::n() const {
    return static_cast<const E&>(*this).n();
}

template<typename T, typename E>
std::size_t MatrixExpression<T, E>::m() const {
    return static_cast<const E&>(*this).m();
}

// matrices compatibility functions //

template<typename T1, typename E1, typename T2, typename E2>
void check_n(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second) {
    if (first.n() != second.n()) {
        throw std::invalid_argument("matrices rows don't match");
    }
}

template<typename T1, typename E1, typename T2, typename E2>
void check_m(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second) {
    if (first.m() != second.m()) {
        throw std::invalid_argument("matrices columns don't match");
    }
}

template<typename T1, typename E1, typename T2, typename E2>
void check_mn(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second) {
    if (first.m() != second.n() || first.m() == 0) {
        throw std::invalid_argument("matrices columns and rows don't match");
    }
}

// Negation implementation //

template<typename T, typename E>
T Negation<T, E>::operator[](std::size_t i, std::size_t j) const {
    return -expression[i, j];
}

template<typename T, typename E>
std::size_t Negation<T, E>::n() const {
    return expression.n();
}

template<typename T, typename E>
std::size_t Negation<T, E>::m() const {
    return expression.m();
}

template<typename T, typename E>
Negation<T, E>::Negation(const MatrixExpression<T, E>& expression_) : expression(static_cast<const E&>(expression_)) {}

// Summation implementation //

template<typename T, typename E1, typename E2>
T Summation<T, E1, E2>::operator[](std::size_t i, std::size_t j) const {
    return first[i, j] + second[i, j];
}

template<typename T, typename E1, typename E2>
std::size_t Summation<T, E1, E2>::n() const {
    return first.n();
}

template<typename T, typename E1, typename E2>
std::size_t Summation<T, E1, E2>::m() const {
    return second.m();
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
std::size_t Subtraction<T, E1, E2>::n() const {
    return first.n();
}

template<typename T, typename E1, typename E2>
std::size_t Subtraction<T, E1, E2>::m() const {
    return second.m();
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
    T result = T(0);
    for (int k = 0; k < first.m(); ++k) {
        result += first[i, k] * second[k, j];
    }
    return result;
}

template<typename T, typename E1, typename E2>
std::size_t Product<T, E1, E2>::n() const {
    return first.n();
}

template<typename T, typename E1, typename E2>
std::size_t Product<T, E1, E2>::m() const {
    return second.m();
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
std::size_t ScalarProduct<T, E, V>::n() const {
    return expression.n();
}

template<typename T, typename E, typename V>
std::size_t ScalarProduct<T, E, V>::m() const {
    return expression.m();
}

template<typename T, typename E, typename V>
ScalarProduct<T, E, V>::ScalarProduct(const MatrixExpression<T, E> &expression_, V val_) :
expression(static_cast<const E&>(expression_)), val(val_) {}

// ScalarDivision implementation //

template<typename T, typename E, typename V>
T ScalarDivision<T, E, V>::operator[](std::size_t i, std::size_t j) const {
    return expression[i, j] / val;
}

template<typename T, typename E, typename V>
std::size_t ScalarDivision<T, E, V>::n() const {
    return expression.n();
}

template<typename T, typename E, typename V>
std::size_t ScalarDivision<T, E, V>::m() const {
    return expression.m();
}

template<typename T, typename E, typename V>
ScalarDivision<T, E, V>::ScalarDivision(const MatrixExpression<T, E> &expression_, V val_) :
expression(static_cast<const E&>(expression_)), val(val_) {}

// expression surface-operations functions implementation //

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
ScalarDivision<T, E, T> operator/(const MatrixExpression<T, E> &expression, T val) {
    return ScalarDivision<T, E, T>(expression, val);
}

// output function implementation //

template<typename T>
std::size_t number_length(T num) {
    std::stringstream ss;
    ss << num;
    return ss.str().length();
}

template<typename T, typename E>
std::ostream& operator<<(std::ostream &ostream, const MatrixExpression<T, E> &expression) {
    if (expression.n() > 0) {
        std::vector<std::size_t> columns_lengths = std::vector<std::size_t>(expression.m());
        for (int j = 0; j < expression.m(); ++j) {
            for (int i = 0; i < expression.n(); ++i) {
                std::size_t element_length = number_length(expression[i, j]);
                if (element_length > columns_lengths[j]) {
                    columns_lengths[j] = element_length;
                }
            }
        }

        for (int j = 0; j < expression.m(); ++j) {
            ostream << std::setw(columns_lengths[j] + 3) << std::left << expression[0, j];
        }
        for (int i = 1; i < expression.n(); ++i) {
            ostream << '\n';
            for (int j = 0; j < expression.m(); ++j) {
                ostream << std::setw(columns_lengths[j] + 3) << std::left << expression[i, j];
            }
        }
    }
    return ostream;
}