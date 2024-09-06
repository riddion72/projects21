#ifndef CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_H_

#include <iostream>
#include <limits>

#include "RBTree.h"

namespace s21 {

template <typename Key, typename T>
class MapIterator;
template <typename Key, typename T>
class MapConstIterator;

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator<Key, T>;
  using const_iterator = const MapIterator<Key, T>;
  using size_type = size_t;

  map() {}
  map(std::initializer_list<value_type> const& items) {
    for (auto item : items) {
      tree_.Insert(item.first, item.second);
    }
  }
  map(const map& other) : tree_(other.tree_) {}
  map(map&& other) : tree_(std::move(other.tree_)) {}

  map& operator=(map&& other) { tree_ = std::move(other.tree_); }
  map& operator=(const map& other) { tree_ = other.tree_; }

  ~map() {}

  T& at(const Key& key) {
    if (tree_.at(key) == nullptr) {
      throw std::out_of_range("Key does not exist.");
    }
    return *(tree_.at(key));
  }

  T& operator[](const Key& key) {
    if (tree_.at(key) == nullptr) {
      tree_.Insert(key, mapped_type());
    }
    return *(tree_.at(key));
  }

  iterator begin() { return iterator(tree_.begin()); }
  iterator end() { return iterator(tree_.end()); }

  bool empty() { return tree_.empty(); }
  size_type size() { return tree_.size(); }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void clear() { tree_.clear(); }
  std::pair<iterator, bool> insert(const value_type& value) {
    try {
      iterator place = tree_.Insert(value.first, value.second);
      return std::make_pair(place, true);
    } catch (std::logic_error const&) {
      return std::make_pair(tree_.end(), false);
    }
  }
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    try {
      iterator place = tree_.Insert(key, obj);
      return std::make_pair(place, true);
    } catch (std::logic_error const&) {
      return std::make_pair(tree_.end(), false);
    }
  }
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    auto smpl = tree_.find(key);
    if (smpl != tree_.end()) {
      erase(smpl);
    }
    tree_.Insert(key, obj);
    return std::make_pair(tree_.find(key), true);
  }
  void erase(iterator pos) {
    if (pos != end()) {
      typename RBTree<Key, T>::iterator& tree_pos = pos;
      tree_.Delete(tree_pos->data.first);
    }
  }
  void swap(map& other) { std::swap(tree_, other.tree_); }

  void merge(map& other) {
    if (tree_ == other.tree_) return;
    for (auto& item : other.tree_) {
      try {
        tree_.Insert(item.data.first, item.data.second);
      } catch (std::logic_error const&) {
      }
    }
  }

  bool contains(const Key& key) {
    bool ans = true;
    if (tree_.find(key) == tree_.end()) {
      ans = false;
    }
    return ans;
  }

 private:
  RBTree<Key, T> tree_;
};

template <typename Key, typename T>
class MapIterator : public RBTreeIterator<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  MapIterator() : RBTreeIterator<Key, T>() {}
  MapIterator(const RBTreeIterator<Key, T>& rbiter)
      : RBTreeIterator<Key, T>(rbiter) {}
  MapIterator(const MapIterator& other) : RBTreeIterator<Key, T>(other) {}
  MapIterator(MapIterator&& other) : RBTreeIterator<Key, T>(std::move(other)) {}
  MapIterator& operator=(const MapIterator& other) {
    RBTreeIterator<Key, T>::operator=(other);
    return *this;
  }
  MapIterator& operator=(MapIterator&& other) {
    RBTreeIterator<Key, T>::operator=(std::move(other));
    return *this;
  }
  MapIterator& operator++() {
    this->RBTreeIterator<Key, T>::operator++();
    return *this;
  }
  MapIterator operator++(int) {
    MapIterator<Key, T> result(*this);
    ++*this;
    return result;
  }
  MapIterator& operator--() {
    this->RBTreeIterator<Key, T>::operator--();
    return *this;
  }
  MapIterator operator--(int) {
    MapIterator<Key, T> result(*this);
    --*this;
    return result;
  }
  value_type& operator*() { return this->node->data; }
  value_type* operator->() { return &(this->node->data); }
};

}  //  namespace s21

#endif  //  CPP2_S21_CONTAINERS_1_SRC_MAP_S21_MAP_H_