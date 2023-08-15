#include <format>

// MatrixExpression implementation //

template<typename E>
auto MatrixExpression<E>::operator[](std::size_t n, std::size_t m) const {
    return static_cast<const E&>(*this)[n, m];
};

template<typename E>
std::size_t MatrixExpression<E>::n_size() const {
    return static_cast<const E&>(*this).n_size();
}

template<typename E>
std::size_t MatrixExpression<E>::m_size() const {
    return static_cast<const E&>(*this).m_size();
}

// non-member MatrixExpression's functions implementation //

template<typename T>
void check_n(const MatrixExpression<T> &first, const MatrixExpression<T> &second) {
    if (first.n_size() != second.n_size()) {
        throw std::invalid_argument("matrices rows don't match");
    }
}

template<typename T>
void check_m(const MatrixExpression<T> &first, const MatrixExpression<T> &second) {
    if (first.m_size() != second.m_size()) {
        throw std::invalid_argument("matrices columns don't match");
    }
}

template<typename T>
void check_mn(const MatrixExpression<T> &first, const MatrixExpression<T> &second) {
    if (first.m_size() != second.n_size()) {
        throw std::invalid_argument("matrices columns and rows don't match");
    }
}

// Negation implementation //
template<typename E>
auto Negation<E>::operator[](std::size_t n, std::size_t m) const {
    return -expression[n, m];
}

template<typename E>
std::size_t Negation<E>::n_size() const {
    return expression.n_size();
}

template<typename E>
std::size_t Negation<E>::m_size() const {
    return expression.m_size();
}

template<typename E>
Negation<E>::Negation(const MatrixExpression<E>& expression_) : expression(static_cast<const E&>(expression_)) {
    expression[0, 0];
}

// Summation implementation //

template<typename E1, typename E2>
auto Summation<E1, E2>::operator[](std::size_t n, std::size_t m) const {
    return first[n, m] + second[n, m];
}

template<typename E1, typename E2>
std::size_t Summation< E1, E2>::n_size() const {
    return first.n_size();
}

template<typename E1, typename E2>
std::size_t Summation<E1, E2>::m_size() const {
    return second.m_size();
}

template<typename E1, typename E2>
Summation<E1, E2>::Summation(const MatrixExpression<E1>& first_, const MatrixExpression<E2>& second_) :
first(static_cast<const E1&>(first_)), second(static_cast<const E2&>(second_)) {
    check_n(first, second);
    check_m(first, second);
}

// Substruction implementation //

template<typename E1, typename E2>
auto Substruction<E1, E2>::operator[](std::size_t n, std::size_t m) const {
    return first[n, m] - second[n, m];
}

template<typename E1, typename E2>
std::size_t Substruction<E1, E2>::n_size() const {
    return first.n_size();
}

template<typename E1, typename E2>
std::size_t Substruction<E1, E2>::m_size() const {
    return second.m_size();
}

template<typename E1, typename E2>
Substruction<E1, E2>::Substruction(const MatrixExpression<E1> &first_, const MatrixExpression<E2> &second_) :
first(static_cast<const E1&>(first_)), second(static_cast<const E2&>(second_)) {
    check_n(first, second);
    check_m(first, second);
}

// Product implementation //

template<typename E1, typename E2>
auto Product<E1, E2>::operator[](std::size_t n, std::size_t m) const {
    auto result = first[n, 0] * second[0, m];
    for (int k = 1; k < first.m_size(); ++k) {
        result += first[n, k] * second[k, m];
    }
    return result;
}

template<typename E1, typename E2>
std::size_t Product<E1, E2>::n_size() const {
    return first.n_size();
}

template<typename E1, typename E2>
std::size_t Product<E1, E2>::m_size() const {
    return second.m_size();
}

template<typename E1, typename E2>
Product<E1, E2>::Product(const MatrixExpression<E1> &first_, const MatrixExpression<E2> &second_) :
first(static_cast<const E1&>(first_)), second(static_cast<const E2&>(second_)) {
    check_mn(first, second);
}

// ScalarProduct implementation//
template<typename E, typename V>
auto ScalarProduct<E, V>::operator[](std::size_t n, std::size_t m) const {
    return expression[n, m] * val;
}

template<typename E, typename V>
std::size_t ScalarProduct<E, V>::n_size() const {
    return expression.n_size();
}

template<typename E, typename V>
std::size_t ScalarProduct<E, V>::m_size() const {
    return expression.m_size();
}

template<typename E, typename V>
ScalarProduct<E, V>::ScalarProduct(const MatrixExpression<E> &expression_, V val_) :
expression(static_cast<const E&>(expression_)), val(val_) {}

// expressions operation functions implementation //

template<typename E>
auto operator-(const MatrixExpression<E> &expression) {
    return Negation<E>(expression);
}

template<typename E1, typename E2>
auto operator+(const MatrixExpression<E1> &first, MatrixExpression<E2> &second) {
    return Summation<E1, E2>(first, second);
}

template<typename E1, typename E2>
auto operator-(const MatrixExpression<E1> &first, const MatrixExpression<E2> &second) {
    return Substruction(first, second);
}

template<typename E1, typename E2>
auto operator*(const MatrixExpression<E1> &first, const MatrixExpression<E2> &second) {
    return Product(first, second);
}

template<typename E>
std::ostream& operator<<(std::ostream &os, const MatrixExpression<E> &matrix) {
    if (matrix.n_size() > 0) {
        int digit_count = 1;
        int absolute_bound = 10;
        bool is_there_negatives = false;
        for (int i = 0; i < matrix.n_size(); ++i) {
            for (int j = 0; j < matrix.m_size(); ++j) {
                if (std::abs(matrix[i, j]) >= absolute_bound) {
                    ++digit_count;
                    absolute_bound *= 10;
                }
                if (matrix[i, j] < 0) { is_there_negatives = true; }
            }
        }

        int element_space = digit_count + is_there_negatives + 2;
        std::cout << matrix[0, 0];
        for (int j = 1; j < matrix.m_size(); ++j) {
            std::cout << std::format("{:>{}}", matrix[0, j], element_space);
        }
        for (int i = 1; i < matrix.n_size(); ++i) {
            std::cout << '\n' << matrix[i, 0];
            for (int j = 1; j < matrix.m_size(); ++j) {
                std::cout << std::format("{:>{}}", matrix[i, j], element_space);
            }
        }
    }
    return os;
}