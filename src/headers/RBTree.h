#ifndef CPP2_S21_CONTAINERS_1_SRC_RBTREE_RBTREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_RBTREE_RBTREE_H_

#include <stdexcept>
#include <utility>

namespace s21 {

enum class Color { RED, BLACK };

template <typename Key, typename T>
class RBTreeIterator;
template <typename Key, typename T>
class RBTreeReverseIterator;

template <typename Key, typename T>
struct RBTreeNode {
  RBTreeNode *parent = nullptr;
  RBTreeNode *left = nullptr;
  RBTreeNode *right = nullptr;
  Color color = Color::RED;
  std::pair<Key, T> data;
};

template <typename Key, typename T>
class RBTree {
 public:
  using size_type = size_t;
  using iterator = RBTreeIterator<Key, T>;
  using Node = RBTreeNode<Key, T>;
  RBTree();
  RBTree(const RBTree<Key, T> &other);
  RBTree(RBTree<Key, T> &&other);
  ~RBTree();
  RBTree &operator=(const RBTree<Key, T> &other);
  RBTree &operator=(RBTree<Key, T> &&other);
  bool operator==(const RBTree<Key, T> &other) { return root == other.root; }
  iterator Insert(const Key &key, const T &value);
  void Delete(const Key &key);
  T *at(const Key &key);
  iterator find(const Key &key);
  bool empty() const { return root == TNULL; }
  size_type size() const { return _size; }
  void clear();
  iterator begin();
  iterator end();

 private:
  Node *root = nullptr;
  Node *TNULL;
  size_type _size = 0;

  Node *&FindNode(const Key &key);
  Node *InsertNode(const Key &key, const T &value);
  Node *CopyTree(const Node *from, const Node *fTNULL);
  void DeleteTree(Node *node);
  void Transplant(Node *u, Node *v);
  Node *grandparent(Node *node) const;
  Node *uncle(Node *node) const;
  Node *Minimum(Node *node) const;
  Node *Maximum(Node *node) const;
  void TurnLeft(Node *node);
  void TurnRight(Node *node);
  void FixInsert(Node *node);
  void FixDelete(Node *node);
};

template <typename Key, typename T>
class RBTreeIterator {
 public:
  using Node = typename RBTree<Key, T>::Node;
  RBTreeIterator() {}
  RBTreeIterator(const RBTreeIterator &other)
      : node(other.node), TNULL(other.TNULL), end(other.end) {}
  RBTreeIterator(RBTreeIterator &&other);
  RBTreeIterator(Node *start, Node *mainTNULL);
  RBTreeIterator &operator=(const RBTreeIterator &other);
  RBTreeIterator &operator=(RBTreeIterator &&other);
  RBTreeIterator &operator++();
  RBTreeIterator operator++(int);
  RBTreeIterator &operator--();
  RBTreeIterator operator--(int);
  Node &operator*();
  Node *operator->();
  bool operator==(const RBTreeIterator &other) const {
    return (node == other.node && end == other.end) ||
           (end == other.end && end == true);
  }
  bool operator!=(const RBTreeIterator &other) const {
    return (node != other.node && end != other.end) || end != other.end;
  }

 protected:
  Node *node = nullptr;
  Node *TNULL = nullptr;
  bool end = true;
};

template <typename Key, typename T>
RBTree<Key, T>::RBTree() {
  TNULL = new Node;
  TNULL->color = Color::BLACK;
  root = TNULL;
}

template <typename Key, typename T>
RBTree<Key, T>::RBTree(const RBTree<Key, T> &other) {
  TNULL = new Node;
  TNULL->color = Color::BLACK;
  root = CopyTree(other.root, other.TNULL);
  _size = other._size;
}

template <typename Key, typename T>
RBTree<Key, T>::RBTree(RBTree<Key, T> &&other) {
  root = other.root;
  TNULL = other.TNULL;
  _size = other._size;
  other.root = nullptr;
  other.TNULL = nullptr;
  other._size = 0;
}

template <typename Key, typename T>
RBTree<Key, T>::~RBTree() {
  DeleteTree(root);
  delete TNULL;
  _size = 0;
}

template <typename Key, typename T>
RBTree<Key, T> &RBTree<Key, T>::operator=(const RBTree<Key, T> &other) {
  if (root == other.root) return *this;
  DeleteTree(root);
  delete TNULL;
  TNULL = new Node;
  TNULL->color = Color::BLACK;
  root = CopyTree(other.root, other.TNULL);
  _size = other._size;
  return *this;
}

template <typename Key, typename T>
RBTree<Key, T> &RBTree<Key, T>::operator=(RBTree<Key, T> &&other) {
  if (root == other.root) return *this;
  DeleteTree(root);
  delete TNULL;
  root = other.root;
  TNULL = other.TNULL;
  _size = other._size;
  other.root = nullptr;
  other.TNULL = nullptr;
  other._size = 0;
  return *this;
}

template <typename Key, typename T>
typename RBTree<Key, T>::iterator RBTree<Key, T>::Insert(const Key &key,
                                                         const T &value) {
  Node *newNode = InsertNode(key, value);
  FixInsert(newNode);
  ++_size;
  return iterator(newNode, TNULL);
}

template <typename Key, typename T>
void RBTree<Key, T>::Delete(const Key &key) {
  Node *nodeToDelete = FindNode(key);

  if (!nodeToDelete) {
    throw std::invalid_argument("Key does not exist.");
  }

  Node *toFix;
  Color originalColor = nodeToDelete->color;

  if (nodeToDelete->left == TNULL) {
    toFix = nodeToDelete->right;
    Transplant(nodeToDelete, nodeToDelete->right);
  } else if (nodeToDelete->right == TNULL) {
    toFix = nodeToDelete->left;
    Transplant(nodeToDelete, nodeToDelete->left);
  } else {
    Node *successor = Minimum(nodeToDelete->right);
    originalColor = successor->color;
    toFix = successor->right;

    if (successor->parent != nodeToDelete) {
      Transplant(successor, toFix);
      successor->right = nodeToDelete->right;
      successor->right->parent = successor;
    } else {
      toFix->parent = successor;
    }

    Transplant(nodeToDelete, successor);
    successor->left = nodeToDelete->left;
    successor->left->parent = successor;
    successor->color = nodeToDelete->color;
  }

  delete nodeToDelete;

  if (originalColor == Color::BLACK) {
    FixDelete(toFix);
  }
  --_size;
}

template <typename Key, typename T>
T *RBTree<Key, T>::at(const Key &key) {
  Node *result = FindNode(key);
  if (result != TNULL) return &result->data.second;
  return nullptr;
}

template <typename Key, typename T>
typename RBTree<Key, T>::iterator RBTree<Key, T>::find(const Key &key) {
  Node *result = FindNode(key);
  if (result != TNULL) return iterator(result, TNULL);
  return end();
}

template <typename Key, typename T>
void RBTree<Key, T>::clear() {
  DeleteTree(root);
  root = TNULL;
  _size = 0;
}

template <typename Key, typename T>
typename RBTree<Key, T>::iterator RBTree<Key, T>::begin() {
  return iterator(Minimum(root), TNULL);
}

template <typename Key, typename T>
typename RBTree<Key, T>::iterator RBTree<Key, T>::end() {
  return ++iterator(Maximum(root), TNULL);
}

template <typename Key, typename T>
typename RBTree<Key, T>::Node *&RBTree<Key, T>::FindNode(const Key &key) {
  Node **current = &root;
  while (*current != TNULL) {
    if (key < (*current)->data.first) {
      current = &(*current)->left;
    } else if ((*current)->data.first < key) {
      current = &(*current)->right;
    } else {
      return *current;
    }
  }
  return *current;
}

template <typename Key, typename T>
typename RBTree<Key, T>::Node *RBTree<Key, T>::InsertNode(const Key &key,
                                                          const T &value) {
  Node *newNode = new Node;
  newNode->data = std::make_pair(key, value);
  newNode->left = TNULL;
  newNode->right = TNULL;
  if (root == TNULL) {
    root = newNode;
    return newNode;
  }

  Node *current = root;
  Node *parent;

  while (current != TNULL) {
    parent = current;
    if (key < current->data.first) {
      current = current->left;
    } else if (current->data.first < key) {
      current = current->right;
    } else {
      delete newNode;
      throw std::logic_error("Key already exists");
    }
  }

  if (key < parent->data.first) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }
  newNode->parent = parent;

  return newNode;
}

template <typename Key, typename T>
typename RBTree<Key, T>::Node *RBTree<Key, T>::CopyTree(const Node *from,
                                                        const Node *fTNULL) {
  if (from == fTNULL) return TNULL;
  Node *to = new Node;
  to->color = from->color;
  to->data = from->data;
  if (from->left != fTNULL) {
    to->left = CopyTree(from->left, fTNULL);
    to->left->parent = to;
  } else {
    to->left = TNULL;
  }
  if (from->right != fTNULL) {
    to->right = CopyTree(from->right, fTNULL);
    to->right->parent = to;
  } else {
    to->right = TNULL;
  }
  return to;
}

template <typename Key, typename T>
void RBTree<Key, T>::DeleteTree(Node *node) {
  if (node == TNULL) return;
  DeleteTree(node->left);
  DeleteTree(node->right);
  delete node;
}

template <typename Key, typename T>
void RBTree<Key, T>::Transplant(Node *u, Node *v) {
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }

  v->parent = u->parent;
}

template <typename Key, typename T>
typename RBTree<Key, T>::Node *RBTree<Key, T>::grandparent(Node *node) const {
  if (node != nullptr && node->parent != nullptr)
    return node->parent->parent;
  else
    return nullptr;
}

template <typename Key, typename T>
typename RBTree<Key, T>::Node *RBTree<Key, T>::uncle(Node *node) const {
  Node *g = grandparent(node);

  if (g == nullptr) return nullptr;

  if (node->parent == g->left)
    return g->right;
  else
    return g->left;
}

template <typename Key, typename T>
typename RBTree<Key, T>::Node *RBTree<Key, T>::Minimum(Node *node) const {
  if (node == TNULL) return node;
  while (node->left != TNULL) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename T>
typename RBTree<Key, T>::Node *RBTree<Key, T>::Maximum(Node *node) const {
  if (node == TNULL) return node;
  while (node->right != TNULL) {
    node = node->right;
  }
  return node;
}

template <typename Key, typename T>
void RBTree<Key, T>::TurnLeft(Node *node) {
  Node *pivot = node->right;
  pivot->parent = node->parent;

  if (node == this->root) this->root = pivot;

  if (node->parent != nullptr) {
    if (node->parent->left == node)
      node->parent->left = pivot;
    else
      node->parent->right = pivot;
  }
  node->right = pivot->left;

  if (pivot->left != TNULL) pivot->left->parent = node;

  node->parent = pivot;
  pivot->left = node;
}

template <typename Key, typename T>
void RBTree<Key, T>::TurnRight(Node *node) {
  Node *pivot = node->left;
  pivot->parent = node->parent;

  if (node == this->root) this->root = pivot;

  if (node->parent != nullptr) {
    if (node->parent->left == node)
      node->parent->left = pivot;
    else
      node->parent->right = pivot;
  }

  node->left = pivot->right;
  if (pivot->right != TNULL) pivot->right->parent = node;

  node->parent = pivot;
  pivot->right = node;
}

template <typename Key, typename T>
void RBTree<Key, T>::FixInsert(Node *node) {
  if (node->parent == nullptr) {
    node->color = Color::BLACK;
  } else if (node->parent->color == Color::RED) {
    Node *g = grandparent(node);
    Node *u = uncle(node);

    if (u != nullptr && u->color == Color::RED) {
      node->parent->color = Color::BLACK;
      u->color = Color::BLACK;
      g->color = Color::RED;
      FixInsert(g);
    } else {
      if (node == node->parent->right && node->parent == g->left) {
        TurnLeft(node->parent);
        node = node->left;
      } else if (node == node->parent->left && node->parent == g->right) {
        TurnRight(node->parent);
        node = node->right;
      }
      node->parent->color = Color::BLACK;
      g->color = Color::RED;
      if (node == node->parent->left && node->parent == g->left) {
        TurnRight(g);
      } else {
        TurnLeft(g);
      }
    }
  }
}

template <typename Key, typename T>
void RBTree<Key, T>::FixDelete(Node *node) {
  while (node != root && node->color == Color::BLACK) {
    if (node == node->parent->left) {
      Node *sibling = node->parent->right;

      if (sibling->color == Color::RED) {
        sibling->color = Color::BLACK;
        node->parent->color = Color::RED;
        TurnLeft(node->parent);
        sibling = node->parent->right;
      }

      if (sibling->left->color == Color::BLACK &&
          sibling->right->color == Color::BLACK) {
        sibling->color = Color::RED;
        node = node->parent;
      } else {
        if (sibling->right->color == Color::BLACK) {
          sibling->left->color = Color::BLACK;
          sibling->color = Color::RED;
          TurnRight(sibling);
          sibling = node->parent->right;
        }

        sibling->color = node->parent->color;
        node->parent->color = Color::BLACK;
        sibling->right->color = Color::BLACK;
        TurnLeft(node->parent);
        node = root;
      }
    } else {
      Node *sibling = node->parent->left;

      if (sibling->color == Color::RED) {
        sibling->color = Color::BLACK;
        node->parent->color = Color::RED;
        TurnRight(node->parent);
        sibling = node->parent->left;
      }

      if (sibling->right->color == Color::BLACK &&
          sibling->left->color == Color::BLACK) {
        sibling->color = Color::RED;
        node = node->parent;
      } else {
        if (sibling->left->color == Color::BLACK) {
          sibling->right->color = Color::BLACK;
          sibling->color = Color::RED;
          TurnLeft(sibling);
          sibling = node->parent->left;
        }

        sibling->color = node->parent->color;
        node->parent->color = Color::BLACK;
        sibling->left->color = Color::BLACK;
        TurnRight(node->parent);
        node = root;
      }
    }
  }
  TNULL->left = nullptr;
  TNULL->right = nullptr;

  node->color = Color::BLACK;
}

template <typename Key, typename T>
RBTreeIterator<Key, T>::RBTreeIterator(RBTreeIterator<Key, T> &&other)
    : node(other.node), TNULL(other.TNULL), end(other.end) {
  other.node = other.TNULL;
}

template <typename Key, typename T>
RBTreeIterator<Key, T>::RBTreeIterator(Node *start, Node *mainTNULL)
    : node(start), TNULL(mainTNULL) {
  if (start != mainTNULL) {
    end = false;
  }
}

template <typename Key, typename T>
RBTreeIterator<Key, T> &RBTreeIterator<Key, T>::operator=(
    const RBTreeIterator<Key, T> &other) {
  node = other.node;
  TNULL = other.TNULL;
  end = other.end;
  return *this;
}

template <typename Key, typename T>
RBTreeIterator<Key, T> &RBTreeIterator<Key, T>::operator=(
    RBTreeIterator<Key, T> &&other) {
  node = other.node;
  TNULL = other.TNULL;
  end = other.end;
  other.node = other.TNULL;
  return *this;
}

template <typename Key, typename T>
RBTreeIterator<Key, T> &RBTreeIterator<Key, T>::operator++() {
  if (node == TNULL || node == nullptr) return *this;
  if (end) {
    while (node->parent != nullptr) node = node->parent;
    while (node->right != TNULL) node = node->right;
    return *this;
  }
  if (node->right == TNULL) {
    Node *parent = node->parent;
    while (parent && parent->right == node) {
      node = parent;
      parent = node->parent;
    }
    if (parent == nullptr) {
      while (node->right != TNULL) node = node->right;
      end = true;
      return *this;
    }
    node = parent;
  } else {
    node = node->right;
    while (node->left != TNULL) node = node->left;
  }
  return *this;
}

template <typename Key, typename T>
RBTreeIterator<Key, T> RBTreeIterator<Key, T>::operator++(int) {
  RBTreeIterator result(*this);
  ++*this;
  return result;
}

template <typename Key, typename T>
RBTreeIterator<Key, T> &RBTreeIterator<Key, T>::operator--() {
  if (node == TNULL || node == nullptr) return *this;
  if (end) {
    while (node->parent != nullptr) node = node->parent;
    while (node->right != TNULL) node = node->right;
    end = false;
  } else if (node->left == TNULL) {
    Node *parent = node->parent;
    while (parent && parent->left == node) {
      node = parent;
      parent = node->parent;
    }
    if (parent == nullptr) {
      while (node->right != TNULL) node = node->right;
      end = true;
      return *this;
    }
    node = parent;
  } else {
    node = node->left;
    while (node->right != TNULL) node = node->right;
  }
  return *this;
}

template <typename Key, typename T>
RBTreeIterator<Key, T> RBTreeIterator<Key, T>::operator--(int) {
  RBTreeIterator result(*this);
  --*this;
  return result;
}

template <typename Key, typename T>
typename RBTreeIterator<Key, T>::Node &RBTreeIterator<Key, T>::operator*() {
  if (end) {
    while (node->parent != nullptr) node = node->parent;
    while (node->right != TNULL) node = node->right;
  }
  return *node;
}

template <typename Key, typename T>
typename RBTreeIterator<Key, T>::Node *RBTreeIterator<Key, T>::operator->() {
  if (end) {
    while (node->parent != nullptr) node = node->parent;
    while (node->right != TNULL) node = node->right;
  }
  return node;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_RBTREE_RBTREE_H_
