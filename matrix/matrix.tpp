// Slice implementation //

Slice::Slice() : start(0), end(0) {}
Slice::Slice(std::size_t start_, std::size_t end_) :
start(start_), end(end_) {}

// AbstractSubmatrix implementation //

template<typename Cont, typename E>
AbstractSubmatrix<Cont, E>::value_type AbstractSubmatrix<Cont, E>::operator[](std::size_t i, std::size_t j) const {
    if (i >= n() || j >= m()) {
        throw std::out_of_range("attempt to access outside of the bounds");
    }
    return data[i + n_start()][j + m_start()];
}

template<typename Cont, typename E>
AbstractSubmatrix<Cont, E> AbstractSubmatrix<Cont, E>::operator=(const AbstractSubmatrix<Cont, E> &other) {
    return (static_cast<E&>(*this) = other);
}

template<typename Cont, typename E>
std::size_t AbstractSubmatrix<Cont, E>::n() const {
    return n_slice.end - n_slice.start;
}

template<typename Cont, typename E>
std::size_t AbstractSubmatrix<Cont, E>::m() const {
    return m_slice.end - m_slice.start;
}

template<typename Cont, typename E>
std::size_t AbstractSubmatrix<Cont, E>::n_start() const {
    return n_slice.start;
}

template<typename Cont, typename E>
std::size_t AbstractSubmatrix<Cont, E>::n_end() const {
    return n_slice.end;
}

template<typename Cont, typename E>
std::size_t AbstractSubmatrix<Cont, E>::m_start() const {
    return m_slice.start;
}

template<typename Cont, typename E>
std::size_t AbstractSubmatrix<Cont, E>::m_end() const {
    return m_slice.end;
}

template<typename Cont, typename E>
AbstractSubmatrix<Cont, E>::AbstractSubmatrix(Cont &data_) : AbstractSubmatrix(data_, Slice(0, data_.size())) {}

template<typename Cont, typename E>
AbstractSubmatrix<Cont, E>::AbstractSubmatrix(Cont &data_, Slice n_slice_) :
data(data_), n_slice(n_slice_) {
    if (data.size() < n_end()) {
        throw std::invalid_argument("row slice out of bounds of matri");
    }
    else if (data.empty()) {
        n_slice = Slice();
        m_slice = Slice();
    }
    else {
        m_slice = Slice(0, data[0].size());
    }
}

template<typename Cont, typename E>
AbstractSubmatrix<Cont, E>::AbstractSubmatrix(Cont &data_, Slice n_slice_, Slice m_slice_) :
data(data_), n_slice(n_slice_), m_slice(m_slice_) {
    if (data.size() < n_end() || (!data.empty() && data[0].size() < m_end())) {
        throw std::invalid_argument("bounds of submatrix inappropriate for this data");
    }
}

// ConstSubmatrix constructors deduction guide //

template<typename Cont>
ConstSubmatrix(Cont &data) -> ConstSubmatrix<typename Cont::value_type::value_type>;

template<typename Cont>
ConstSubmatrix(Cont &data, Slice n_slice) -> ConstSubmatrix<typename Cont::value_type::value_type>;

template<typename Cont>
ConstSubmatrix(Cont &data, Slice n_slice, Slice m_slice) -> ConstSubmatrix<typename Cont::value_type::value_type>;

// Submatrix implementation //

template<typename T1>
T1& Submatrix<T1>::operator[](std::size_t i, std::size_t j) {
    if (i >= this->n() || j >= this->m()) {
        throw std::out_of_range("attempt to access outside of the bounds");
    }
    return this->data[i + this->n_start()][j + this->m_start()];
}

template<typename T1>
template<typename T2, typename E2>
Submatrix<T1> Submatrix<T1>::operator=(const MatrixExpression<T2, E2> &other) {
    check_n(*this, other);
    check_m(*this, other);

    std::vector<std::vector<T1>> result = std::vector<std::vector<T1>>(this->n(), std::vector<T1>(this->m()));
    for (int i = 0; i < this->n(); ++i) {
        for (int j = 0; j < this->m(); ++j) {
            result[i][j] = other[i,j];
        }
    }

    for (int i = 0; i < this->n(); ++i) {
        for (int j = 0; j < this->m(); ++j) {
            (*this)[i,j] = result[i][j];
        }
    }
    return *this;
}

template<typename T1>
template<typename T2, typename E2>
Submatrix<T1> Submatrix<T1>::operator+=(const MatrixExpression<T2, E2> &other) {
    *this = Summation<T1, AbstractSubmatrix<std::vector<std::vector<T1>>, Submatrix<T1>>, E2>(*this, other);
    return *this;
}

template<typename T1>
template<typename T2, typename E2>
Submatrix<T1> Submatrix<T1>::operator-=(const MatrixExpression<T2, E2> &other) {
    *this = Subtraction<T1, AbstractSubmatrix<std::vector<std::vector<T1>>, Submatrix<T1>>, E2>(*this, other);
    return *this;
}

template<typename T1>
Submatrix<T1> Submatrix<T1>::operator*=(T1 val) {
    *this = *this * val;
    return *this;
}

template<typename T1>
Submatrix<T1> Submatrix<T1>::operator/=(T1 val) {
    *this = *this / val;
    return *this;
}

// Submatrix constructions deduction guide //

template<typename Cont>
Submatrix(Cont &data) -> Submatrix<typename Cont::value_type::value_type>;

template<typename Cont>
Submatrix(Cont &data, Slice n_slice) -> Submatrix<typename Cont::value_type::value_type>;

template<typename Cont>
Submatrix(Cont &data, Slice n_slice, Slice m_slice) -> Submatrix<typename Cont::value_type::value_type>;

// Matrix implementation //

template<typename T1>
T1 Matrix<T1>::operator[](std::size_t i, std::size_t j) const {
    return data[i][j];
}

template<typename T1>
T1& Matrix<T1>::operator[](std::size_t i, std::size_t j) {
    return data[i][j];
}

template<typename T1>
ConstSubmatrix<T1> Matrix<T1>::operator[](std::size_t i) const {
    return (*this)[Slice(i, i+1), Slice(0, m())];
}

template<typename T1>
Submatrix<T1> Matrix<T1>::operator[](std::size_t i) {
    return (*this)[Slice(i, i+1), Slice(0, m())];
}

template<typename T1>
ConstSubmatrix<T1> Matrix<T1>::operator[](Slice n_slice) const {
    return (*this)[n_slice, Slice(0, m())];
}

template<typename T1>
Submatrix<T1> Matrix<T1>::operator[](Slice n_slice) {
    return (*this)[n_slice, Slice(0, m())];
}

template<typename T1>
ConstSubmatrix<T1> Matrix<T1>::operator[](Slice n_slice, std::size_t m) const {
    return (*this)[n_slice, Slice(m, m+1)];
}

template<typename T1>
Submatrix<T1> Matrix<T1>::operator[](Slice n_slice, std::size_t m) {
    return (*this)[n_slice, Slice(m, m+1)];
}

template<typename T1>
ConstSubmatrix<T1> Matrix<T1>::operator[](std::size_t n, Slice m_slice) const {
    return (*this)[Slice(n, n+1), m_slice];
}

template<typename T1>
Submatrix<T1> Matrix<T1>::operator[](std::size_t n, Slice m_slice) {
    return (*this)[Slice(n, n+1), m_slice];
}

template<typename T1>
ConstSubmatrix<T1> Matrix<T1>::operator[](Slice n_slice, Slice m_slice) const {
    return ConstSubmatrix<T1>(data, n_slice, m_slice);
}

template<typename T1>
Submatrix<T1> Matrix<T1>::operator[](Slice n_slice, Slice m_slice) {
    return Submatrix<T1>(data, n_slice, m_slice);
}

template<typename T1>
std::size_t Matrix<T1>::n() const {
    return N;
}

template<typename T1>
std::size_t Matrix<T1>::m() const {
    return M;
}

template<typename T1>
template<typename T2, typename E2>
Matrix<T1>& Matrix<T1>::operator=(const MatrixExpression<T2, E2> &other) {
    *this = Matrix<T1>(other);
    return *this;
}

template<typename T1>
template<typename T2, typename E2>
Matrix<T1>& Matrix<T1>::operator+=(const MatrixExpression<T2, E2> &other) {
    *this = Summation<T1, Matrix<T1>, E2>(*this, other);
    return *this;
}

template<typename T1>
template<typename T2, typename E2>
Matrix<T1>& Matrix<T1>::operator-=(const MatrixExpression<T2, E2> &other) {
    *this = Subtraction<T1, Matrix<T1>, E2>(*this, other);
    return *this;
}

template<typename T1>
Matrix<T1>& Matrix<T1>::operator*=(T1 val) {
    *this = *this * val;
    return *this;
}

template<typename T1>
Matrix<T1>& Matrix<T1>::operator/=(T1 val) {
    *this = *this / val;
    return *this;
}

template<typename T1>
Matrix<T1>::Matrix() : Matrix(0, 0) {}

template<typename T1>
Matrix<T1>::Matrix(std::size_t size) : Matrix(size, size) {}

template<typename T1>
Matrix<T1>::Matrix(std::size_t N_, std::size_t M_)
: N(N_), M(M_), data(std::vector<std::vector<T1>>(n(), std::vector<T1>(m()))) {}

template<typename T1>
Matrix<T1>::Matrix(const std::vector<std::vector<T1>> &data_) : N(data.size()), data(data_) {
    M = (data.empty() ? 0 : data[0].size());
}

template<typename T1>
template<typename T2, typename E2>
Matrix<T1>::Matrix(const MatrixExpression<T2, E2> &expression) : Matrix(expression.n(), expression.m()) {
    (*this)[Slice(0, n()), Slice(0, m())] = expression;
}

template<typename Cont, typename E>
Matrix(AbstractSubmatrix<Cont, E>) -> Matrix<typename AbstractSubmatrix<Cont, E>::value_type>;

// input function //

template<typename T>
std::istream& operator>>(std::istream &istream, Matrix<T> &matrix) {
    std::size_t n, m;
    istream >> n >> m;

    matrix = Matrix<T>(n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            istream >> matrix[i, j];
        }
    }
    return istream;
}