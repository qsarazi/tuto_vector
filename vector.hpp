#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <cstddef>
#include <cstring>

#include <exception>

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

    explicit vector(size_type count) {
        if (count == 0)
            return;
        _data = new value_type[count];
        _size = count;
    }

    vector(size_type count, const T& value) {
        if (count == 0)
            return;
        _data = new value_type[count];
        for (size_type i = 0; i < count; ++i)
            _data[i] = value;
        _size = count;
    }

    ~vector() {
        delete[] _data;
    }

    void assign(size_type count, const T& value) {
        
    }

    reference at(size_type pos) {
        if (pos < _size)
            return _data[pos];
        throw std::out_of_range("vector::at out of range");
    }

    const_reference at(size_type pos) const {
        if (pos < _size)
            return _data[pos];
        throw std::out_of_range("vector::at out of range");
    }

    reference operator[](size_type pos) { return _data[pos]; }
    const_reference operator[](size_type pos) const { return _data[pos]; }

    T *data() { return _data; }
    const T *data() const { return _data; }

    size_type size() const { return _size; }

    void push_back(const T& value) {
        resize(_size + 1, value);
    }

    void resize(size_type count) {
        resize(count, value_type{});
    }

    void resize(size_type count, const value_type& value) {
        value_type *temp = nullptr;
        if (count != 0)
            temp = new value_type[count];

        memcpy(temp, _data, (_size < count ? _size : count) * sizeof(value_type));
        while (_size < count)
            temp[_size++] = value;
        std::swap(_data, temp);
        _size = count;
        delete[] temp;
    }

    bool operator==(const vector &other) const {
        if (_size != other._size)
            return false;
        
        return memcmp(_data, other._data, _size * sizeof(value_type)) == 0;
    }

    bool operator!=(const vector &other) const {
        if (_size != other._size)
            return true;
        
        return memcmp(_data, other._data, _size * sizeof(value_type)) != 0;
    }

  private:
    value_type *_data{nullptr};
    size_type _size = 0;
};

} // namespace tuto

#endif // __VECTOR_HPP__