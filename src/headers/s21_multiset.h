#ifndef CPP2_S21_CONTAINERS_1_SRC_MULTISET_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_1_SRC_MULTISET_S21_MULTISET_H_

#include <limits>

#include "RBTree.h"

namespace s21 {

template <typename Key>
class MultisetIterator;

template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MultisetIterator<Key>;
  using const_iterator = MultisetIterator<Key>;
  using size_type = size_t;

  multiset() {}
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& s);
  multiset(multiset&& s);
  ~multiset() {}
  multiset& operator=(const multiset& s);
  multiset& operator=(multiset&& s);
  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  size_type count(const Key& key);
  iterator find(const Key& key);
  bool contains(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

 private:
  RBTree<Key, size_t> tree;
  size_type _size = 0;
};

template <typename Key>
class MultisetIterator : public RBTreeIterator<Key, size_t> {
 public:
  using key_type = Key;
  using value_type = Key;
  MultisetIterator() : RBTreeIterator<Key, size_t>() {}
  MultisetIterator(const RBTreeIterator<Key, size_t>& rbiter)
      : RBTreeIterator<Key, size_t>(rbiter), index(0) {}
  MultisetIterator(const RBTreeIterator<Key, size_t>& rbiter, size_t pos)
      : RBTreeIterator<Key, size_t>(rbiter), index(pos) {}
  MultisetIterator(const MultisetIterator& other)
      : RBTreeIterator<Key, size_t>(other), index(other.index) {}
  MultisetIterator(MultisetIterator&& other)
      : RBTreeIterator<Key, size_t>(std::move(other)), index(other.index) {}
  MultisetIterator& operator=(const MultisetIterator& other);
  MultisetIterator& operator=(MultisetIterator&& other);
  MultisetIterator& operator++();
  MultisetIterator operator++(int);
  MultisetIterator& operator--();
  MultisetIterator operator--(int);
  const value_type& operator*() { return this->node->data.first; }
  const value_type* operator->() { return this->node->data.first; }
  bool operator==(const MultisetIterator& other) const;
  bool operator!=(const MultisetIterator& other) const;

 private:
  size_t index = 0;

  friend class multiset<Key>;
};

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items) {
  // iterator end_iter = end();
  for (auto item : items) {
    insert(item);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset& s) : tree(s.tree), _size(s._size) {}

template <typename Key>
multiset<Key>::multiset(multiset&& s)
    : tree(std::move(s.tree)), _size(s._size) {
  s._size = 0;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(const multiset& s) {
  tree = s.tree;
  _size = s._size;
  return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& s) {
  tree = std::move(s.tree);
  _size = s._size;
  s._size = 0;
  return *this;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  return iterator(tree.begin());
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  return iterator(tree.end());
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::cbegin() {
  return const_iterator(tree.begin());
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::cend() {
  return const_iterator(tree.end());
}

template <typename Key>
bool multiset<Key>::empty() {
  return tree.empty();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() {
  return _size;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(value_type);
}

template <typename Key>
void multiset<Key>::clear() {
  tree.clear();
  _size = 0;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, bool> multiset<Key>::insert(
    const value_type& value) {
  auto iter = tree.find(value);
  if (iter != tree.end()) {
    iter->data.second++;
  } else {
    iter = tree.Insert(value, 1);
  }
  iterator place = iterator(iter, iter->data.second);
  ++_size;

  return std::make_pair(place, true);
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  if (pos != end()) {
    typename RBTree<Key, size_t>::iterator& tree_pos = pos;
    if (tree_pos->data.second > 1) {
      tree_pos->data.second--;
    } else {
      tree.Delete(tree_pos->data.first);
    }
    --_size;
  }
}

template <typename Key>
void multiset<Key>::swap(multiset& other) {
  std::swap(tree, other.tree);
  std::swap(_size, other._size);
}

template <typename Key>
void multiset<Key>::merge(multiset& other) {
  if (tree == other.tree) return;
  auto iter = other.begin();
  while (iter != other.end()) {
    auto prev_iter = iter++;
    if (insert(*prev_iter).second) {
      other.erase(prev_iter);
    }
  }
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  size_type* ptr = tree.at(key);
  if (ptr) {
    return *ptr;
  } else {
    return 0;
  }
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& key) {
  return iterator(tree.find(key));
}

template <typename Key>
bool multiset<Key>::contains(const Key& key) {
  return tree.at(key);
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  auto iter = find(key);
  if (iter != begin() && iter != end()) {
    --iter;
  }
  return iter;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  auto iter = find(key);
  if (iter != end()) {
    iter.RBTreeIterator<Key, size_t>::operator++();
  }
  return iter;
}

template <typename Key>
MultisetIterator<Key>& MultisetIterator<Key>::operator=(
    const MultisetIterator& other) {
  RBTreeIterator<Key, size_t>::operator=(other);
  index = other.index;
  return *this;
}

template <typename Key>
MultisetIterator<Key>& MultisetIterator<Key>::operator=(
    MultisetIterator&& other) {
  RBTreeIterator<Key, size_t>::operator=(std::move(other));
  index = other.index;
  other.index = 0;
  return *this;
}

template <typename Key>
MultisetIterator<Key>& MultisetIterator<Key>::operator++() {
  if (!this->end && index + 1 < this->node->data.second) {
    ++index;
  } else {
    this->RBTreeIterator<Key, size_t>::operator++();
    index = 0;
  }
  return *this;
}

template <typename Key>
MultisetIterator<Key> MultisetIterator<Key>::operator++(int) {
  MultisetIterator<Key> result(*this);
  ++*this;
  return result;
}

template <typename Key>
MultisetIterator<Key>& MultisetIterator<Key>::operator--() {
  if (!this->end && index > 0) {
    --index;
  } else {
    this->RBTreeIterator<Key, size_t>::operator--();
    index = this->node->data.second - 1;
  }
  return *this;
}

template <typename Key>
MultisetIterator<Key> MultisetIterator<Key>::operator--(int) {
  MultisetIterator<Key> result(*this);
  --*this;
  return result;
}

template <typename Key>
bool MultisetIterator<Key>::operator==(const MultisetIterator& other) const {
  return (this->node == other.node && index == other.index &&
          this->end == other.end) ||
         (this->end == other.end && this->end == true);
}

template <typename Key>
bool MultisetIterator<Key>::operator!=(const MultisetIterator& other) const {
  return ((this->node != other.node || index != other.index) &&
          this->end != other.end) ||
         this->end != other.end;
  ;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_MULTISET_S21_MULTISET_H_
