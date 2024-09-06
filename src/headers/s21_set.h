#ifndef CPP2_S21_CONTAINERS_1_SRC_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_SET_S21_SET_H_

#include <limits>

#include "RBTree.h"

namespace s21 {

template <typename Key>
class SetIterator;

template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = SetIterator<Key>;
  using const_iterator = SetIterator<Key>;
  using size_type = size_t;

  set() {}
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set() {}
  set& operator=(const set& s);
  set& operator=(set&& s);
  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);
  iterator find(const Key& key);
  bool contains(const Key& key);

 private:
  RBTree<Key, bool> tree;
};

template <typename Key>
class SetIterator : public RBTreeIterator<Key, bool> {
 public:
  using key_type = Key;
  using value_type = Key;
  SetIterator() : RBTreeIterator<Key, bool>() {}
  SetIterator(const RBTreeIterator<Key, bool>& rbiter)
      : RBTreeIterator<Key, bool>(rbiter) {}
  SetIterator(const SetIterator& other) : RBTreeIterator<Key, bool>(other) {}
  SetIterator(SetIterator&& other)
      : RBTreeIterator<Key, bool>(std::move(other)) {}
  SetIterator& operator=(const SetIterator& other);
  SetIterator& operator=(SetIterator&& other);
  SetIterator& operator++();
  SetIterator operator++(int);
  SetIterator& operator--();
  SetIterator operator--(int);
  const value_type& operator*() const { return this->node->data.first; }
  const value_type* operator->() const { return this->node->data.first; }
};

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items) {
  for (auto item : items) {
    tree.Insert(item, true);
  }
}

template <typename Key>
set<Key>::set(const set& s) : tree(s.tree) {}

template <typename Key>
set<Key>::set(set&& s) : tree(std::move(s.tree)) {}

template <typename Key>
set<Key>& set<Key>::operator=(const set& s) {
  tree = s.tree;
  return *this;
}

template <typename Key>
set<Key>& set<Key>::operator=(set&& s) {
  tree = std::move(s.tree);
  return *this;
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() {
  return iterator(tree.begin());
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  return iterator(tree.end());
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::cbegin() {
  return const_iterator(tree.begin());
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::cend() {
  return const_iterator(tree.end());
}

template <typename Key>
bool set<Key>::empty() const {
  return tree.empty();
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() const {
  return tree.size();
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() const {
  return std::numeric_limits<size_t>::max() / sizeof(value_type);
}

template <typename Key>
void set<Key>::clear() {
  tree.clear();
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  try {
    iterator place = tree.Insert(value, true);
    return std::make_pair(place, true);
  } catch (std::logic_error const&) {
    return std::make_pair(tree.end(), false);
  }
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  if (pos != end()) {
    typename RBTree<Key, bool>::iterator& tree_pos = pos;
    tree.Delete(tree_pos->data.first);
  }
}

template <typename Key>
void set<Key>::swap(set& other) {
  std::swap(tree, other.tree);
}

template <typename Key>
void set<Key>::merge(set& other) {
  if (tree == other.tree) return;
  auto iter = other.begin();
  while (iter != other.end()) {
    auto value = *iter++;
    if (insert(value).second) {
      other.tree.Delete(value);
    }
  }
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  return iterator(tree.find(key));
}

template <typename Key>
bool set<Key>::contains(const Key& key) {
  return tree.at(key);
}

template <typename Key>
SetIterator<Key>& SetIterator<Key>::operator=(const SetIterator& other) {
  RBTreeIterator<Key, bool>::operator=(other);
  return *this;
}

template <typename Key>
SetIterator<Key>& SetIterator<Key>::operator=(SetIterator&& other) {
  RBTreeIterator<Key, bool>::operator=(std::move(other));
  return *this;
}

template <typename Key>
SetIterator<Key>& SetIterator<Key>::operator++() {
  this->RBTreeIterator<Key, bool>::operator++();
  return *this;
}

template <typename Key>
SetIterator<Key> SetIterator<Key>::operator++(int) {
  SetIterator<Key> result(*this);
  ++*this;
  return result;
}

template <typename Key>
SetIterator<Key>& SetIterator<Key>::operator--() {
  this->RBTreeIterator<Key, bool>::operator--();
  return *this;
}

template <typename Key>
SetIterator<Key> SetIterator<Key>::operator--(int) {
  SetIterator<Key> result(*this);
  --*this;
  return result;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_SET_S21_SET_H_
