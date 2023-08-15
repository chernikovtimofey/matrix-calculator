#include <format>

// MatrixExpression implementation //

template<typename T, typename E>
T MatrixExpression<T, E>::operator[](std::size_t n, std::size_t m) const {
    return static_cast<const E&>(*this)[n, m];
}

template<typename T, typename E>
std::size_t MatrixExpression<T, E>::n_size() const {
    return static_cast<const E&>(*this).n_size();
}

template<typename T, typename E>
std::size_t MatrixExpression<T, E>::m_size() const {
    return static_cast<const E&>(*this).m_size();
}

// non-member MatrixExpression's functions implementation //

template<typename T1, typename E1, typename T2, typename E2>
void check_n(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second) {
    if (first.n_size() != second.n_size()) {
        throw std::invalid_argument("matrices rows don't match");
    }
}

template<typename T1, typename E1, typename T2, typename E2>
void check_m(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second) {
    if (first.m_size() != second.m_size()) {
        throw std::invalid_argument("matrices columns don't match");
    }
}

template<typename T1, typename E1, typename T2, typename E2>
void check_mn(const MatrixExpression<T1, E1> &first, const MatrixExpression<T2, E2> &second) {
    if (first.m_size() != second.n_size() || first.m_size() == 0) {
        throw std::invalid_argument("matrices columns and rows don't match");
    }
}

// Negation implementation //
template<typename T, typename E>
T Negation<T, E>::operator[](std::size_t n, std::size_t m) const {
    return -expression[n, m];
}

template<typename T, typename E>
std::size_t Negation<T, E>::n_size() const {
    return expression.n_size();
}

template<typename T, typename E>
std::size_t Negation<T, E>::m_size() const {
    return expression.m_size();
}

template<typename T, typename E>
Negation<T, E>::Negation(const MatrixExpression<T, E>& expression_) : expression(static_cast<const E&>(expression_)) {}

// Summation implementation //

template<typename T, typename E1, typename E2>
T Summation<T, E1, E2>::operator[](std::size_t n, std::size_t m) const {
    return first[n, m] + second[n, m];
}

template<typename T, typename E1, typename E2>
std::size_t Summation<T, E1, E2>::n_size() const {
    return first.n_size();
}

template<typename T, typename E1, typename E2>
std::size_t Summation<T, E1, E2>::m_size() const {
    return second.m_size();
}

template<typename T, typename E1, typename E2>
template<typename T1, typename T2>
Summation<T, E1, E2>::Summation(const MatrixExpression<T1, E1> &first_, const MatrixExpression<T2, E2> &second_) :
first(static_cast<const E1&>(first_)), second(static_cast<const E2&>(second_)) {
    check_n(first, second);
    check_m(first, second);
}

// Substruction implementation //

template<typename T, typename E1, typename E2>
T Substruction<T, E1, E2>::operator[](std::size_t n, std::size_t m) const {
    return first[n, m] - second[n, m];
}

template<typename T, typename E1, typename E2>
std::size_t Substruction<T, E1, E2>::n_size() const {
    return first.n_size();
}

template<typename T, typename E1, typename E2>
std::size_t Substruction<T, E1, E2>::m_size() const {
    return second.m_size();
}

template<typename T, typename E1, typename E2>
template<typename T1, typename T2>
Substruction<T, E1, E2>::Substruction(const MatrixExpression<T1, E1> &first_, const MatrixExpression<T2, E2> &second_) :
first(static_cast<const E1&>(first_)), second(static_cast<const E2&>(second_)) {
    check_n(first, second);
    check_m(first, second);
}

// Product implementation //

template<typename T, typename E1, typename E2>
T Product<T, E1, E2>::operator[](std::size_t n, std::size_t m) const {
    T result;
    for (int k = 0; k < first.m_size(); ++k) {
        result += first[n, k] * second[k, m];
    }
    return result;
}

template<typename T, typename E1, typename E2>
std::size_t Product<T, E1, E2>::n_size() const {
    return first.n_size();
}

template<typename T, typename E1, typename E2>
std::size_t Product<T, E1, E2>::m_size() const {
    return second.m_size();
}

template<typename T, typename E1, typename E2>
template<typename T1, typename T2>
Product<T, E1, E2>::Product(const MatrixExpression<T1, E1> &first_, const MatrixExpression<T2, E2> &second_) :
first(static_cast<const E1&>(first_)), second(static_cast<const E2&>(second_)) {
    check_mn(first, second);
}

// ScalarProduct implementation//
template<typename T, typename E>
auto ScalarProduct<T, E>::operator[](std::size_t n, std::size_t m) const {
    return expression[n, m] * val;
}

template<typename T, typename E>
std::size_t ScalarProduct<T, E>::n_size() const {
    return expression.n_size();
}

template<typename T, typename E>
std::size_t ScalarProduct<T, E>::m_size() const {
    return expression.m_size();
}

template<typename T, typename E>
ScalarProduct<T, E>::ScalarProduct(const MatrixExpression<T, E> &expression_, T val_) :
expression(static_cast<const E&>(expression_)), val(val_) {}

// expressions operation functions implementation //

template<typename T, typename E>
Negation<T, E> operator-(const MatrixExpression<T, E> &expression) {
    return Negation<T, E>(expression);
}

template<typename T, typename E1, typename E2>
Summation<T, E1, E2> operator+(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second) {
    return Summation<T, E1, E2>(first, second);
}

template<typename T, typename E1, typename E2>
Substruction<T, E1, E2> operator-(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second) {
    return Substruction<T, E1, E2>(first, second);
}

template<typename T, typename E1, typename E2>
Product<T, E1, E2> operator*(const MatrixExpression<T, E1> &first, const MatrixExpression<T, E2> &second) {
    return Product<T, E1, E2>(first, second);
}

template<typename T, typename E>
ScalarProduct<T, E> operator*(const MatrixExpression<T, E> &expression, T val) {
    return ScalarProduct<T, E>(expression, val);
}

template<typename T, typename E>
ScalarProduct<T, E> operator*(T val, const MatrixExpression<T, E> &expression) {
    return expression * val;
}

template<typename T, typename E>
std::ostream& operator<<(std::ostream &os, const MatrixExpression<T, E> &matrix) {
    if (matrix.n_size() > 0) {
        int max_length = 1;
        for (int i = 0; i < matrix.n_size(); ++i) {
            for (int j = 0; j < matrix.m_size(); ++j) {
                int length = std::format("{}", matrix[i, j]).length();
                if (length > max_length) {
                    max_length = length;
                }
            }
        }

        int element_space = max_length + 2;
        std::cout << std::format("{:<{}}", matrix[0, 0], element_space);
        for (int j = 1; j < matrix.m_size(); ++j) {
            std::cout << std::format("{:<{}}", matrix[0, j], element_space);
        }
        for (int i = 1; i < matrix.n_size(); ++i) {
            std::cout << '\n' << std::format("{:<{}}", matrix[i, 0], element_space);
            for (int j = 1; j < matrix.m_size(); ++j) {
                std::cout << std::format("{:<{}}", matrix[i, j], element_space);
            }
        }
    }
    return os;
}