#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_QUEUE_H_

#include <cstddef>
#include <cstdio>
#include <iostream>

#include "s21_vector.h"  // Включаем вашу реализацию вектора

namespace s21 {

template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 private:
  s21::Vector<value_type>
      vector;  // Добавлено объявление вектора для хранения элементов очереди
  size_type front_;
  size_type rear_;

 public:
  // Конструктор по умолчанию
  queue() : front_(0), rear_(0) {}
  // Конструктор, инициализирующий очередь из списка инициализаторов
  queue(std::initializer_list<value_type> const &items) : front_(0), rear_(0) {
    for (const auto &item : items) {
      vector.push_back(item);
      rear_++;
    }
  }

  queue(const queue &q) : vector(q.vector), front_(q.front_), rear_(q.rear_) {}

  // Перегрузка оператора присваивания для движущегося объекта
  queue &operator=(queue &&q) noexcept {
    if (this != &q) {  // Проверка на самоприсваивание
      vector.clear();
      // Переносим ресурсы из q в текущий объект, используя перегрузку operator=
      // для вектора
      front_ = q.front_;
      rear_ = q.rear_;
      vector = std::move(q.vector);
      q.front_ = 0;
      q.rear_ = 0;
    }
    return *this;
  }

  queue(queue &&q)
      : vector(std::move(q.vector)), front_(q.front_), rear_(q.rear_) {
    // Обнуляем исходную очередь
    q.front_ = 0;
    q.rear_ = 0;
  }

  ~queue() {
    // вызывает деструктор вектора где храняться данные
  }
  //!!! для доступа к информации о наполнении контейнера:
  bool empty() const { return front_ >= rear_; }

  size_type size() const { return rear_ - front_; }
  //------------
  //!!!!! методы для изменения контейнера:

  // Метод для удаления первого элемента очереди
  void pop() {
    if (front_ < rear_) {
      front_++;
    }
  }
  // вставляет элемент в конец
  void push(const_reference value) {
    vector.push_back(value);
    rear_++;
  }
  void swap(queue &other) {
    vector.swap(other.vector);
    std::swap(front_, other.front_);
    std::swap(rear_, other.rear_);
  }
  // ---------------------

  // Получение элемента из начала очереди
  const_reference front() {
    if (front_ < rear_) {
      return vector[front_];
    }
    throw std::out_of_range("Queue is empty");
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
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
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_QUEUE_H_
