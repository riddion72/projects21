#include <cstdlib>
#include <ctime>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <random>

namespace s21 {
template <typename T>

class List {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
  };

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class iterator {
   private:
    Node* current;

   public:
    iterator(Node* node) : current(node) {}

    iterator& operator++() {
      current = current->next;
      return *this;
    }
    reference operator*() const { return current->data; }

    bool operator!=(const iterator& other) const {
      return current != other.current;
    }

    bool operator==(const iterator& other) const {
      return current == other.current;
    }

    friend class List<T>;
  };

  class const_iterator {
   private:
    const Node* current;

   public:
    const_iterator(const Node* node) : current(node) {}

    const_iterator& operator++() {
      current = current->next;
      return *this;
    }

    const T& operator*() const { return current->data; }

    bool operator!=(const const_iterator& other) const {
      return current != other.current;
    }

    bool operator==(const const_iterator& other) const {
      return current == other.current;
    }

    friend class List<T>;
  };

 private:
  Node* list_front;
  Node* list_back;
  size_type size_;

 public:
  List() : list_front(nullptr), list_back(nullptr), size_(0) {}
  List(size_type n) : list_front(nullptr), list_back(nullptr), size_(0) {
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
  }

  List(std::initializer_list<value_type> const& items)
      : list_front(nullptr), list_back(nullptr), size_(0) {
    for (const auto& item : items) {
      push_back(item);
    }
  }

  // copy
  List(const List& l) : list_front(nullptr), list_back(nullptr), size_(0) {
    Node* sourceNode =
        l.list_front;  // Устанавливаем начальный узел для копирования из l

    while (sourceNode) {
      push_back(
          sourceNode
              ->data);  // Копируем значение и добавляем его в новый список
      sourceNode = sourceNode->next;  // Переходим к следующему узлу в списке l
    }
  }

  // move
  List(List&& l)
      : list_front(l.list_front), list_back(l.list_back), size_(l.size_) {
    l.list_front = l.list_back = nullptr;
    l.size_ = 0;
  }

  ~List() { clear(); }

  List& operator=(List&& l) {
    if (this != &l) {
      clear();
      list_front = l.list_front;
      list_back = l.list_back;
      size_ = l.size_;
      l.list_front = l.list_front = nullptr;
      l.size_ = 0;
    }
    return *this;
  }

  const_reference front() const {
    if (list_front) {
      return list_front->data;
    } else {
      static const T default_value =
          T();               // Default-construct a static variable.
      return default_value;  // Return a reference to the static default value.
    }
  }

  const_reference back() const {
    if (list_back) {
      return list_back->data;
    } else {
      static const T default_value =
          T();               // Default-construct a static variable.
      return default_value;  // Return a reference to the static default value.
    }
  }

  iterator begin() { return iterator(list_front); }

  iterator end() { return iterator(nullptr); }

  bool empty() const { return list_front == nullptr; }

  size_type size() const { return size_; }

  size_type max_size() const {
    return (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
  }

  void clear() {
    while (list_front) {
      Node* temp = list_front;  // Сохраняем указатель на текущий узел
      list_front =
          list_front->next;  // Перемещаем указатель front на следующий узел
      delete temp;           // Удаляем текущий узел
    }
    list_back = nullptr;
    size_ = 0;
  }

  void push_back(const_reference value) {
    Node* newNode = new Node(value);
    if (!list_front) {
      // Если список пуст, устанавливаем front и back на новый узел
      list_front = list_back = newNode;
    } else {
      list_back->next = newNode;
      list_back = newNode;
    }
    size_++;
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos == end()) {
      push_back(value);
      return iterator(list_back);
    } else if (pos == begin()) {
      push_front(value);
      return iterator(list_front);
    } else {
      Node* newNode = new Node(value);
      Node* prevNode = list_front;
      // узел, перед которым мы хотим вставить новый узел
      newNode->next = pos.current;
      // находит узел, предшествующий pos.current в списке.
      while (prevNode->next != pos.current) {
        prevNode = prevNode->next;
      }
      // обновляем указатель next, чтобы он указывал на новый узел newNode
      //  тем самым вставляя newNode в список перед pos.current.
      prevNode->next = newNode;
      size_++;
      return iterator(newNode);
    }
  }

  void erase(iterator pos) {
    if (pos == end()) {
      return;
    } else if (pos == begin()) {
      pop_front();
    } else {
      Node* prevNode = list_front;
      while (prevNode->next != pos.current) {
        prevNode = prevNode->next;
      }
      prevNode->next = pos.current->next;
      if (pos.current == list_back) {
        list_back = prevNode;
      }
      delete pos.current;
      size_--;
    }
  }

  void pop_back() {
    if (list_front) {
      if (list_front == list_back) {
        // если 1 элемент
        delete list_front;
        list_front = list_back = nullptr;
      } else {
        Node* current = list_front;
        Node* previous = nullptr;
        while (current->next != nullptr) {
          previous = current;
          current = current->next;
        }
        list_back = previous;
        list_back->next = nullptr;
        delete current;
      }

      size_--;
    }
  }

  void push_front(const_reference value) {
    Node* newNode = new Node(value);
    if (!list_front) {
      // Если список пуст, новый узел становится как началом, так и концом
      list_front = list_back = newNode;
    } else {
      // Иначе, новый узел становится перед текущим началом
      newNode->next = list_front;
      list_front = newNode;
    }
    size_++;
  }

  void pop_front() {
    if (list_front) {
      Node* temp = list_front;
      list_front = list_front->next;
      delete temp;
      size_--;
    }
  }

  void swap(List& other) {
    using std::swap;
    swap(list_front, other.list_front);
    swap(list_back, other.list_back);
    swap(size_, other.size_);
  }

  void merge(List& other) {
    if (this == &other) {
      return;
    }
    List mergedList;
    iterator it1 = begin();
    iterator it2 = other.begin();

    while (it1 != end() && it2 != other.end()) {
      if (*it1 < *it2) {
        mergedList.push_back(*it1);
        ++it1;
      } else {
        mergedList.push_back(*it2);
        ++it2;
      }
    }
    while (it1 != end()) {
      mergedList.push_back(*it1);
      ++it1;
    }
    while (it2 != other.end()) {
      mergedList.push_back(*it2);
      ++it2;
    }
    swap(mergedList);
  }
  void splice(const_iterator pos, List& other) {
    splice(const_cast<iterator>(pos), other);
  }

  void splice(iterator pos, List& other) {
    if (this == &other || other.empty() || pos == other.end()) {
      return;
    }
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(pos, *it);
    }
    other.clear();
  }

  void reverse() {
    if (empty() || size() == 1) {
      return;
    }

    Node* prev = nullptr;
    Node* current = list_front;
    Node* next = nullptr;

    while (current != nullptr) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }

    list_back = list_front;
    list_front = prev;
  }

  void unique() {
    if (empty() || size() == 1) {
      return;
    }
    s21::List<T> uniqueList;
    iterator current = begin();
    uniqueList.push_back(*current);
    while (++current != end()) {
      if (*current != uniqueList.back()) {
        uniqueList.push_back(*current);
      }
    }
    swap(uniqueList);
  }

  void sort() {
    if (size() <= 1) {
      return;
    }
    bool swapped;
    do {
      swapped = false;
      iterator prev = begin();
      iterator current = begin();
      iterator next = current;
      ++next;
      while (next != end()) {
        if (*current > *next) {
          std::swap(*current, *next);
          swapped = true;
        }
        ++prev;
        ++current;
        ++next;
      }
    } while (swapped);
  }

  void quick_sort() {
    while (!is_sorted()) {
      shuffle();  // Randomly shuffle the elements until they are sorted.
    }
  }

  bool is_sorted() {
    if (empty() || size() == 1) {
      return true;  // An empty or single-element list is considered sorted.
    }

    iterator prev = begin();
    iterator current = begin();
    ++current;

    while (current != end()) {
      if (*prev > *current) {
        return false;
      }
      ++prev;
      ++current;
    }

    return true;
  }

  void shuffle() {
    if (size() <= 1) {
      return;
    }
    std::vector<T> elements;
    for (iterator it = begin(); it != end(); ++it) {
      elements.push_back(*it);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(elements.begin(), elements.end(), g);
    size_type i = 0;
    for (iterator it = begin(); it != end(); ++it, ++i) {
      *it = elements[i];
    }
  }

  bool compare_lists(const std::list<T>& std_list) {
    auto my_it = begin();
    auto std_it = std_list.begin();

    while (my_it != end() && std_it != std_list.end()) {
      if (*my_it != *std_it) {
        return false;
      }
      ++my_it;
      ++std_it;
    }

    return my_it == end() && std_it == std_list.end();
  }

  template <typename... Args>
  iterator insert_many(const iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);
};

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::insert_many(const iterator pos,
                                                Args&&... args) {
  List<value_type> tmp{args...};
  if (!tmp.empty()) {
    iterator insert_pos = pos;  // Start with the specified position
    for (const auto& item : tmp) {
      insert_pos = insert(insert_pos, item);
      ++insert_pos;  // Move the insert position forward
    }
  }
  return pos;  // Return the original position
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_back(Args&&... args) {
  insert_many(end(), args...);
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_front(Args&&... args) {
  insert_many(begin(), args...);
}

}  // namespace s21
