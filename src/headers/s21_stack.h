#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <iostream>

#include "s21_vector.h"

namespace s21 {

template <class T, class Container = s21::Vector<T> >
class stack {
 public:
  using size_type = size_t;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;

  stack() = default;
  explicit stack(std::initializer_list<value_type> const &items) : st(items) {}
  stack(const stack &s) = default;
  stack(stack &&s) = default;
  stack &operator=(stack &&s) = default;
  ~stack() = default;

  const_reference top() { return st.back(); }

  bool empty() { return st.empty(); }
  size_type size() { return st.size(); }

  void push(const_reference value) { this->st.push_back(value); }
  void pop() { this->st.pop_back(); }
  void swap(stack &other) { st.swap(other.st); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    insert_many_front_aux_(args...);
  }

 private:
  void insert_many_front_aux_(void) {}

  template <typename U>
  void insert_many_front_aux_(U &&arg) {
    push(arg);
  }

  template <typename U, typename... Args>
  void insert_many_front_aux_(U &&arg, Args &&...args) {
    push(arg);
    insert_many_front_aux_(args...);
  }

 private:
  Container st;
};

}  // namespace s21

#endif  // S21_STACK_H_
