#ifndef CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class Vector {
 private:
  T* vector;  // Указатель на массив элементов вектора
  size_t size_;  // Текущий размер вектора (количество элементов)
  size_t capacity_;  // Емкость вектора (количество элементов, которое может
                     // содержать)

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;  // Используйте size_t

  // Конструктор по умолчанию, создающий пустой вектор
  Vector() : vector(nullptr), size_(0), capacity_(0) {}

  // Параметризованный конструктор, создающий вектор размера n
  Vector(size_type n) : vector(new T[n]), size_(n), capacity_(n) {}

  Vector(std::initializer_list<value_type> const& items)
      : vector(nullptr), size_(0), capacity_(0) {
    reserve(items.size());
    for (const auto& item : items) {
      push_back(item);
    }
  }

  Vector(const Vector& other) : vector(nullptr), size_(0), capacity_(0) {
    reserve(other.size());

    for (size_type i = 0; i < other.size_; ++i) {
      push_back(other.vector[i]);
    }
  }

  Vector(Vector&& other) noexcept : vector(nullptr), size_(0), capacity_(0) {
    // Перемещаем указатель на данные и размер/емкость из другого объекта
    vector = other.vector;
    size_ = other.size_;
    capacity_ = other.capacity_;

    // Обнуляем указатель на данные и сбрасываем размер/емкость у другого
    // объекта
    other.vector = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  Vector& operator=(Vector&& other) noexcept {
    if (this != &other) {
      // Освобождаем ресурсы текущего объекта
      delete[] vector;

      // Перемещаем данные из другого объекта
      vector = other.vector;
      size_ = other.size_;
      capacity_ = other.capacity_;

      // Обнуляем данные в другом объекте, чтобы избежать утечки памяти
      other.vector = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  // Деструктор для освобождения памяти
  ~Vector() { delete[] vector; }

  // итераторы !!!!!

  iterator begin() { return vector; }

  iterator end() { return vector + size_; }

  // !!! методы для доступа к элементам класса:

  // Метод для доступа к элементу с проверкой границ
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return vector[pos];
  }

  reference operator[](size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range");
    }

    return vector[pos];
  }
  //доступ к первому элементу
  const_reference front() const {
    if (size_ == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return vector[0];
  }
  // 	доступ к последнему элементу
  const_reference back() const {
    if (size_ == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return vector[size_ - 1];
  }

  T* data() { return vector; }

  //--------------

  // !!! методы для доступа к информации о наполнении контейнера:

  // Метод для получения размера вектора
  size_type size() const { return size_; }

  // Метод для проверки, пуст ли контейнер
  bool empty() const { return size_ == 0; }

  // Метод для получения максимально возможного размера
  size_type max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
  }

  // выделяет хранилище элементов размера и копирует текущие элементы массива в
  // вновь выделенный массив
  void reserve(size_type new_capacity) {
    if (new_capacity > capacity_) {
      // Выделяем новый массив с увеличенной емкостью
      T* new_vector = new T[new_capacity];

      // Копируем текущие элементы в новый массив
      for (size_type i = 0; i < size_; ++i) {
        new_vector[i] = vector[i];
      }

      // Освобождаем старое хранилище
      delete[] vector;

      // Обновляем указатель на данные и емкость
      vector = new_vector;
      capacity_ = new_capacity;
    }
  }

  // возвращает количество элементов, которые могут храниться в выделенном на
  // данный момент хранилище
  size_type capacity() const { return capacity_; }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      // Создаем новый массив с размером, соответствующим размеру вектора
      T* newvector = new T[size_];

      // Копируем элементы из старого массива в новый
      for (size_type i = 0; i < size_; ++i) {
        newvector[i] = vector[i];
      }

      // Освобождаем старый массив
      delete[] vector;

      // Обновляем указатель на данные и емкость
      vector = newvector;
      capacity_ = size_;
    }
  }

  // !!! методы для изменения контейнера:

  void clear() {
    // Удалите все элементы, но не освобождайте память
    for (size_type i = 0; i < size_; ++i) {
      vector[i].~T();
    }
    size_ = 0;  // Установите размер вектора в ноль
  }

  iterator insert(iterator pos, const_reference value) {
    // Рассчитываем индекс из итератора
    size_type index = pos - begin();

    // Проверяем, находится ли индекс в пределах допустимого диапазона
    if (index > size_) {
      throw std::out_of_range(
          "Позиция вставки находится вне допустимого диапазона");
    }

    // Проверяем, нужно ли увеличивать емкость
    if (size_ == capacity_) {
      size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
      reserve(new_capacity);
    }

    // Сдвигаем элементы вправо, чтобы освободить место для нового элемента
    for (size_type i = size_; i > index; --i) {
      vector[i] = vector[i - 1];
    }

    // Вставляем новый элемент на указанную позицию
    vector[index] = value;

    // Увеличиваем размер
    ++size_;

    // Возвращаем итератор, указывающий на вставленный элемент
    return begin() + index;
  }

  void erase(iterator pos) {
    if (pos < begin() || pos >= end()) {
      throw std::out_of_range("Iterator is out of range");
    }

    // Сдвигаем элементы справа от удаляемой позиции на одну позицию влево
    for (iterator it = pos; it != end() - 1; ++it) {
      *it = *(it + 1);
    }

    // Уменьшаем размер вектора
    --size_;
  }

  void push_back(const_reference value) {
    // Проверяем, есть ли достаточно емкости для добавления нового элемента
    if (size_ == capacity_) {
      // Если нет, увеличиваем емкость (например, вдвое)
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    // Добавляем новый элемент в конец текущего массива
    vector[size_] = value;

    // Увеличиваем размер вашего вектора
    ++size_;
  }

  void pop_back() {
    if (size_ > 0) {
      --size_;
    }
  }

  void swap(Vector& other) {
    std::swap(vector, other.vector);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);
};

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  Vector<value_type> tmp{args...};
  iterator insert_pos = begin() + (pos - begin());
  for (size_t i = 0; i < tmp.size(); i++, insert_pos++) {
    insert_pos = insert(insert_pos, tmp[i]);
  }

  return insert_pos;
}

template <typename T>
template <typename... Args>
void Vector<T>::insert_many_back(Args&&... args) {
  insert_many(end(), args...);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_
