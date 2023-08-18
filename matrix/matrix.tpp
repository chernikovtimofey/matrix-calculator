// Slice implementation //

Slice::Slice() : start(0), end(0) {}
Slice::Slice(std::size_t start_, std::size_t end_) :
start(start_), end(end_) {}

// AbstractSubmatrix implementation //

template<typename Cont, typename E>
AbstractSubmatrix<Cont, E>::value_type AbstractSubmatrix<Cont, E>::operator[](std::size_t i, std::size_t j) const {
    if (i >= get_n() || j >= get_m()) {
        throw std::out_of_range("attempt to access outside of the bounds");
    }
    return data[i + n_start()][j + m_start()];
}

template<typename Cont, typename E>
AbstractSubmatrix<Cont, E> AbstractSubmatrix<Cont, E>::operator=(const AbstractSubmatrix<Cont, E> &other) {
    return (static_cast<E&>(*this) = other);
}

template<typename Cont, typename E>
std::size_t AbstractSubmatrix<Cont, E>::get_n() const {
    return n_slice.end - n_slice.start;
}

template<typename Cont, typename E>
std::size_t AbstractSubmatrix<Cont, E>::get_m() const {
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
AbstractSubmatrix<Cont, E>::AbstractSubmatrix(Cont &data_) : AbstractSubmatrix(data_, Slice(0, data_.size())) {}

template<typename Cont, typename E>
AbstractSubmatrix<Cont, E>::AbstractSubmatrix(Cont &data_, Slice n_slice_) :
data(data_), n_slice(n_slice_) {
    if (data.empty()) {
        n_slice = Slice();
        m_slice = Slice();
    }
    else {
        m_slice = Slice(0, data[0].size());
    }
}

template<typename Cont, typename E>
AbstractSubmatrix<Cont, E>::AbstractSubmatrix(Cont &data_, Slice n_slice_, Slice m_slice_) :
data(data_), n_slice(n_slice_), m_slice(m_slice_) {}

// ConstSubmatrix constructors deduction guide //

template<typename Cont>
ConstSubmatrix(Cont &data) -> ConstSubmatrix<typename Cont::value_type::value_type>;

template<typename Cont>
ConstSubmatrix(Cont &data, Slice n_slice) -> ConstSubmatrix<typename Cont::value_type::value_type>;

template<typename Cont>
ConstSubmatrix(Cont &data, Slice n_slice, Slice m_slice) -> ConstSubmatrix<typename Cont::value_type::value_type>;

// Submatrix implementation //

template<typename T1>
T1& Submatrix<T1>::operator[](std::size_t n, std::size_t m) {
    if (n >= this->get_n() || m >= this->get_m()) {
        throw std::out_of_range("attempt to access outside of the bounds");
    }
    return this->data[n + this->n_start()][m + this->m_start()];
}

template<typename T1>
template<typename T2, typename E2>
Submatrix<T1> Submatrix<T1>::operator=(const MatrixExpression<T2, E2> &other) {
    check_n(*this, other);
    check_m(*this, other);

    std::vector<std::vector<T1>> result = std::vector<std::vector<T1>>(this->get_n(), std::vector<T1>(this->get_m()));
    for (int i = 0; i < this->get_n(); ++i) {
        for (int j = 0; j < this->get_m(); ++j) {
            result[i][j] = other[i, j];
        }
    }

    for (int i = 0; i < this->get_n(); ++i) {
        for (int j = 0; j < this->get_m(); ++j) {
            (*this)[i, j] = result[i][j];
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
template<typename T2, typename E2>
Submatrix<T1> Submatrix<T1>::operator*=(const MatrixExpression<T2, E2> &other) {
    if (this->get_n() != this->get_m()) {
        throw std::invalid_argument("operation *= available only for square matrix");
    }

    *this = Product<T1, AbstractSubmatrix<std::vector<std::vector<T1>>, Submatrix<T1>>, E2>(*this, other);
    return *this;
}

template<typename T1>
Submatrix<T1> Submatrix<T1>::operator*=(T1 val) {
    *this = *this * val;
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
T1 Matrix<T1>::operator[](std::size_t n, std::size_t m) const {
    return data[n][m];
}

template<typename T1>
T1& Matrix<T1>::operator[](std::size_t n, std::size_t m) {
    return data[n][m];
}

template<typename T1>
ConstSubmatrix<T1> Matrix<T1>::operator[](std::size_t n) const {
    return (*this)[Slice(n, n+1), Slice(0, get_m())];
}

template<typename T1>
Submatrix<T1> Matrix<T1>::operator[](std::size_t n) {
    return (*this)[Slice(n, n+1), Slice(0, get_m())];
}

template<typename T1>
ConstSubmatrix<T1> Matrix<T1>::operator[](Slice n_slice) const {
    return (*this)[n_slice, Slice(0, get_m())];
}

template<typename T1>
Submatrix<T1> Matrix<T1>::operator[](Slice n_slice) {
    return (*this)[n_slice, Slice(0, get_m())];
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
std::size_t Matrix<T1>::get_n() const {
    return width;
}

template<typename T1>
std::size_t Matrix<T1>::get_m() const {
    return height;
}

template<typename T1>
template<typename T2, typename E2>
Matrix<T1>& Matrix<T1>::operator=(const MatrixExpression<T2, E2> &other) {
    (*this)[Slice(0, get_n()), Slice(0, get_m())] = other;
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
template<typename T2, typename E2>
Matrix<T1>& Matrix<T1>::operator*=(const MatrixExpression<T2, E2> &other) {
    if (width != height) {
        throw std::invalid_argument("operation *= available only for square matrix");
    }

    *this = Product<T1, Matrix<T1>, E2>(*this, other);
    return *this;
}

template<typename T1>
Matrix<T1>& Matrix<T1>::operator*=(T1 val) {
    *this = *this * val;
    return *this;
}

template<typename T1>
Matrix<T1>::Matrix() : Matrix(0, 0) {}

template<typename T1>
Matrix<T1>::Matrix(std::size_t size) : Matrix(size, size) {}

template<typename T1>
Matrix<T1>::Matrix(std::size_t row_count_, std::size_t column_count_)
: width(row_count_), height(column_count_),
  data(std::vector<std::vector<T1>>(width, std::vector<T1>(height))) {}

template<typename T1>
Matrix<T1>::Matrix(const std::vector<std::vector<T1>> &data_) : width(data.size()), data(data_) {
    height = (data.empty() ? 0 : data[0].size());
}

template<typename T1>
template<typename T, typename E>
Matrix<T1>::Matrix(const MatrixExpression<T, E> &expression) : Matrix(expression.get_n(), expression.get_m()) {
    *this = expression;
}

template<typename Cont, typename E>
Matrix(AbstractSubmatrix<Cont, E>) -> Matrix<typename AbstractSubmatrix<Cont, E>::value_type>;

// non-member Matrix's functions implementation//

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