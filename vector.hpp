#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <cstddef>

namespace tuto {

template<class T>
class vector {
  public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    vector() = default;

    ~vector() {
        delete _data;
    }

    reference at(size_type pos) {
        if (pos < _size)
            return _data[pos];
        throw std::out_of_range;
    }

    const_reference at(size_type pos) const {
        if (pos < _size)
            return _data[pos];
        throw std::out_of_range;
    }

    reference operator[](size_type pos) { return _data[pos]; }
    const_reference operator[](size_type pos) const { return _data[pos]; }

    T *data() { return _data; }
    const T *data() const { return _data; }

    size_type size() const { return _size; }

    void push_back(const T& value) {
        value_type *temp = new value_type[_size + 1];
        memcpy(temp, _data, _size);
        std::swap(temp, _data);
        _data[_size] = value;
        _size += 1;
        delete temp;
    }

  private:
    value_type *_data{nullptr};
    size_type _size = 0;
};

} // namespace tuto

#endif // __VECTOR_HPP__