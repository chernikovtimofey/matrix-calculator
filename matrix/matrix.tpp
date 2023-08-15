// Slice implementation //

Slice::Slice() = default;
Slice::Slice(std::size_t start_, std::size_t end_) :
start(start_), end(end_) {}

// AbstractSubmatrix implementation //

template<typename E, typename Cont>
auto AbstractSubmatrix<E, Cont>::operator[](std::size_t n, std::size_t m) const {
    if (n >= n_size() || m >= m_size()) {
        throw std::out_of_range("attempt to access outside of the bounds");
    }
    return data[n + n_start()][m + m_start()];
}

template<typename E, typename Cont>
std::size_t AbstractSubmatrix<E, Cont>::n_size() const {
    return n_slice.end - n_slice.start;
}

template<typename E, typename Cont>
std::size_t AbstractSubmatrix<E, Cont>::m_size() const {
    return m_slice.end - m_slice.start;
}

template<typename E, typename Cont>
std::size_t AbstractSubmatrix<E, Cont>::n_start() const {
    return n_slice.start;
}

template<typename E, typename Cont>
std::size_t AbstractSubmatrix<E, Cont>::n_end() const {
    return n_slice.end;
}

template<typename E, typename Cont>
std::size_t AbstractSubmatrix<E, Cont>::m_start() const {
    return m_slice.start;
}

template<typename E, typename Cont>
std::size_t AbstractSubmatrix<E, Cont>::m_end() const {
    return m_slice.end;
}

template<typename E, typename Cont>
AbstractSubmatrix<E, Cont>::AbstractSubmatrix(Cont &data_) : AbstractSubmatrix(data_, Slice(0, data_.size())) {}

template<typename E, typename Cont>
AbstractSubmatrix<E, Cont>::AbstractSubmatrix(Cont &data_, Slice n_slice_) :
data(data_), n_slice(n_slice_) {
    if (data.empty()) {
        n_slice = Slice(0, 0);
        m_slice = Slice(0, 0);
    }
    else {
        m_slice = Slice(0, data[0].size());
    }
}

template<typename E, typename Cont>
AbstractSubmatrix<E, Cont>::AbstractSubmatrix(Cont &data_, Slice n_slice_, Slice m_slice_) :
data(data_), n_slice(n_slice_), m_slice(m_slice_) {}

// VolatileMatrix implementation //

template<typename E>
auto& VolatileMatrix<E>::operator[](std::size_t n, std::size_t m) {
    return static_cast<const E&>(*this)[n, m];
}

// ConstSubmatrix constructors template guide //

template<typename Cont>
ConstSubmatrix(Cont &data) -> ConstSubmatrix<typename Cont::value_type::value_type>;

template<typename Cont>
ConstSubmatrix(Cont &data, Slice n_slice) -> ConstSubmatrix<typename Cont::value_type::value_type>;

template<typename Cont>
ConstSubmatrix(Cont &data, Slice n_slice, Slice m_slice) -> ConstSubmatrix<typename Cont::value_type::value_type>;