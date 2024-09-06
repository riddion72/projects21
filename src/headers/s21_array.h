#ifndef CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_

#include <iostream>
#include <limits>

namespace s21 {

template <typename T, std::size_t N>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array() : size_(N) {}
  Array(std::initializer_list<value_type> const &items) : Array() {
    if (size_ < items.size())
      throw std::out_of_range("Too many initializers for s21::array");
    size_type i = 0;
    for (auto item = items.begin(); item != items.end(); item++, i++) {
      elements_[i] = *item;
    }
  }
  Array(const Array &a) : Array() {
    std::copy(a.cbegin(), a.cend(), elements_);
  }
  Array(Array &&a) noexcept : Array() {
    std::move(a.cbegin(), a.cend(), elements_);
  };

  void operator=(Array &other) {
    std::copy(other.cbegin(), other.cend(), elements_);
  }
  void operator=(Array &&other) {
    std::move(other.cbegin(), other.cend(), elements_);
  }

  ~Array() = default;

  iterator begin() noexcept { return elements_; }
  iterator end() noexcept { return &elements_[size_]; }
  const_iterator cbegin() const noexcept { return elements_; }
  const_iterator cend() const noexcept { return &elements_[size_]; }

  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("Out of range");
    return elements_[pos];
  }
  reference operator[](size_type pos) { return elements_[pos]; }
  const_reference front() const {
    if (size_ == 0) {
      throw std::out_of_range("Array is empty");
    }
    return elements_[0];
  }
  const_reference back() const {
    if (size_ == 0) {
      throw std::out_of_range("Array is empty");
    }
    return elements_[size_ - 1];
  }
  iterator data() noexcept { return begin(); }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const { return size_; }

  void swap(Array &other) { std::swap(*this, other); }
  void fill(const_reference value) {
    for (size_type i = 0; i < size_; i++) elements_[i] = value;
  }

 private:
  value_type elements_[N] = {};
  size_type size_;
};
}  //  namespace s21

#endif  //  CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_