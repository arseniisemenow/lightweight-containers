#ifndef CPP2_S21_CONTAINERS_1_ASSOCIATIVE_RED_BLACK_TREE_RED_BLACK_TREE_H_
#define CPP2_S21_CONTAINERS_1_ASSOCIATIVE_RED_BLACK_TREE_RED_BLACK_TREE_H_

#include <algorithm>
#include <iostream>
#include <iterator>

#include "Node.h"

namespace s21 {
template <typename T>
class RedBlackTree {
 public:
  template <bool IsConst>
  class RedBlackTreeIteratorBase {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = std::conditional_t<IsConst, const T *, T *>;
    using reference = std::conditional_t<IsConst, const T &, T &>;

    using RedBlackTreeIterator = RedBlackTreeIteratorBase<false>;
    using RedBlackTreeConstIterator = RedBlackTreeIteratorBase<true>;

   public:
    RedBlackTreeIteratorBase() = default;

    explicit RedBlackTreeIteratorBase(Node<T> *node, Node<T> *nil)
        : current_node_(node), nil_(nil){};

   public:
    RedBlackTreeIteratorBase &operator++() {
      if (current_node_ == nullptr || current_node_ == nil_ ||
          nil_ == nullptr) {
        return *this;
      }

      if (current_node_->right_ != nil_) {
        current_node_ = current_node_->right_;
        while (current_node_->left_ != nil_) {
          current_node_ = current_node_->left_;
        }
      } else {
        while (current_node_->parent_ != nullptr &&
               current_node_ == current_node_->parent_->right_) {
          current_node_ = current_node_->parent_;
        }
        if (current_node_->parent_ != nullptr) {
          current_node_ = current_node_->parent_;
        } else {
          current_node_ = nil_;
        }
      }

      return *this;
    }

    RedBlackTreeIteratorBase &operator--() {
      if (current_node_ == nil_) {
        current_node_ = nil_->parent_;
      } else {
        if (current_node_->left_ != nil_ && current_node_->left_ != nullptr) {
          current_node_ = current_node_->left_;
          while (current_node_->right_ != nil_) {
            current_node_ = current_node_->right_;
          }
        } else {
          while (current_node_->parent_ != nullptr &&
                 current_node_ == current_node_->parent_->left_) {
            current_node_ = current_node_->parent_;
          }
          current_node_ = current_node_->parent_;
        }
      }

      return *this;
    }

    RedBlackTreeIteratorBase operator--(int) {
      RedBlackTreeIteratorBase iter(current_node_, nil_);
      --(*this);
      return iter;
    }

    RedBlackTreeIteratorBase operator++(int) {
      RedBlackTreeIteratorBase iter(current_node_, nil_);
      ++(*this);
      return iter;
    }

    reference operator*() const { return current_node_->data_; }

    pointer operator->() const { return &current_node_->data_; }

    bool operator==(const RedBlackTreeIteratorBase &other) const {
      return current_node_ == other.current_node_;
    }

    bool operator!=(const RedBlackTreeIteratorBase &other) const {
      return current_node_ != other.current_node_;
    }

   private:
    Node<T> *current_node_;
    Node<T> *nil_;
  };

 public:
  using RedBlackTreeIterator = RedBlackTreeIteratorBase<false>;
  using RedBlackTreeConstIterator = RedBlackTreeIteratorBase<true>;

  using mapped_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = RedBlackTreeConstIterator;
  using const_iterator = RedBlackTreeConstIterator;
  using size_type = std::size_t;

  RedBlackTree() = default;

  RedBlackTree(std::initializer_list<T> const &items) {
    for (const auto &item : items) {
      Insert(item);
    }
  }

  RedBlackTree(const RedBlackTree &other) {
    iterator other_iter = other.begin();
    while (other_iter != other.end()) {
      Insert(*other_iter);
      ++other_iter;
    }
  }

  RedBlackTree(RedBlackTree &&other) {
    root_ = other.root_;
    delete nil_;
    nil_ = other.nil_;
    other.nil_ = new Node<T>{};
    other.root_ = other.nil_;
  }

  ~RedBlackTree() {
    Clear();
    delete nil_;
    nil_ = nullptr;
    root_ = nil_;
  }

  RedBlackTree &operator=(const RedBlackTree &other) {
    if (this != &other) {
      Clear();
      iterator other_iter = other.begin();
      while (other_iter != other.end()) {
        Insert(*other_iter);
        ++other_iter;
      }
    }
    return *this;
  }

  RedBlackTree &operator=(RedBlackTree &&other) {
    if (this != &other) {
      root_ = other.root_;
      delete nil_; /* Need to free already allocated for nil_ memory */
      nil_ = other.nil_;
      other.nil_ = new Node<T>{};
      other.root_ = other.nil_;
    }
    return *this;
  }

  bool operator!=(const RedBlackTree &other) const {
    return !operator==(other);
  }

  bool operator==(const RedBlackTree &other) const {
    if (GetSize() != other.GetSize()) {
      return false;
    }
    iterator iter_first = begin();
    iterator iter_second = other.begin();
    while (iter_first != end()) {
      if (*iter_first != *iter_second) {
        return false;
      }
      ++iter_first;
      ++iter_second;
    }
    return true;
  }

 public:
  [[nodiscard]] iterator GetLowerBoundIterator(const T &key) const {
    iterator lower_bound_iter = --end();
    for (iterator it = begin(); it != end(); ++it) {
      if (*it >= key) {
        lower_bound_iter = it;
        break;
      }
    }
    return lower_bound_iter;
  }

  [[nodiscard]] iterator GetLowerBoundIteratorForMap(const T &pair) const {
    iterator lower_bound_iter = --end();
    for (iterator it = begin(); it != end(); ++it) {
      if ((*it).first >= pair.first) {
        lower_bound_iter = it;
        break;
      }
    }
    return lower_bound_iter;
  }

  [[nodiscard]] iterator GetUpperBoundIterator(const T &key) const {
    iterator upper_bound_iter = --end();
    for (iterator it = begin(); it != end(); ++it) {
      if (*it > key) {
        upper_bound_iter = it;
        break;
      }
    }
    return upper_bound_iter;
  }

  [[nodiscard]] iterator GetUpperBoundIteratorForMap(const T &pair) const {
    iterator upper_bound_iter = --end();
    for (iterator it = begin(); it != end(); ++it) {
      if ((*it).first > pair.first) {
        upper_bound_iter = it;
        break;
      }
    }
    return upper_bound_iter;
  }

  [[nodiscard]] size_type GetMaxSize() const {
    std::allocator<mapped_type> memory;
    return std::min(memory.max_size(), std::numeric_limits<size_type>::max());
  }

  [[nodiscard]] bool IsEmpty() const { return root_ == nil_; }

  [[nodiscard]] size_type GetSize() const { return SizeHelper(root_); }

  [[nodiscard]] Node<T> *GetRoot() const { return root_; }

  [[nodiscard]] Node<T> *GetNil() const { return nil_; }

  void Clear() {
    ClearHelper(root_);
    nil_->parent_ = nullptr;
    root_ = nil_;
  }

  iterator Insert(const T &data) {
    Node<T> *new_node = new Node<T>(data);
    new_node->parent_ = nullptr;
    new_node->left_ = nil_;
    new_node->right_ = nil_;
    new_node->color_ = Color::kRed;

    InsertNode(new_node);
    iterator new_iterator(new_node, nil_);
    return new_iterator;
  }

  void Remove(const T &data) {
    auto node_to_remove = Search(data);
    if (node_to_remove != nullptr) {
      RemoveNode(node_to_remove);
    }
  }

 public:
  [[maybe_unused]] void PrintTree() const {
    if (root_ != nil_) {
      PrintHelper(root_, "", true);
    } else {
      std::cerr << "Tree is IsEmpty\n";
    }
  }

 public:
  [[nodiscard]] Node<T> *Search(const T &key) const {
    return FindNode(root_, key);
  }

 public:
  [[nodiscard]] const_iterator begin() const noexcept {
    return RedBlackTreeConstIterator(FindMinNode(root_), nil_);
  }

  [[nodiscard]] const_iterator end() const noexcept {
    return RedBlackTreeConstIterator(nil_, nil_);
  }

  Node<T> *FindMinNode(Node<T> *root) const {
    while (root->left_ != nil_ && root->left_ != nullptr) {
      root = root->left_;
    }
    return root;
  }

  Node<T> *FindMaxNode(Node<T> *root) const {
    while (root->right_ != nil_) {
      root = root->right_;
    }
    return root;
  }

 private:
  Node<T> *nil_{new Node<T>{}};
  Node<T> *root_{nil_};

 private:
  [[nodiscard]] size_type SizeHelper(Node<T> *node) const {
    if (node == nil_) {
      return 0;
    }
    return 1 + SizeHelper(node->left_) + SizeHelper(node->right_);
  }

  void ClearHelper(Node<T> *node) {
    if (node != nil_) {
      ClearHelper(node->left_);
      ClearHelper(node->right_);
      delete node;
      node = nullptr;
    }
  }

  void LeftRotate(Node<T> *node) {
    Node<T> *y = node->right_;
    node->right_ = y->left_;

    if (y->left_ != nil_) {
      y->left_->parent_ = node;
    }
    y->parent_ = node->parent_;

    if (node->parent_ == nullptr) {
      root_ = y;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = y;
    } else {
      node->parent_->right_ = y;
    }

    y->left_ = node;
    node->parent_ = y;
  }

  void RightRotate(Node<T> *node) {
    Node<T> *x = node->left_;
    node->left_ = x->right_;

    if (x->right_ != nil_) {
      x->right_->parent_ = node;
    }
    x->parent_ = node->parent_;

    if (node->parent_ == nullptr) {
      root_ = x;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = x;
    } else {
      node->parent_->right_ = x;
    }

    x->right_ = node;
    node->parent_ = x;
  }

  void FixInsertHelper(Node<T> *&y, Node<T> *&node,
                       std::function<void(Node<T> *)> first_rotate,
                       std::function<void(Node<T> *)> second_rotate,
                       const Node<T> *child_to_check) {
    if (y && y->color_ == Color::kRed) {
      y->color_ = Color::kBlack;
      node->parent_->color_ = Color::kBlack;
      node->parent_->parent_->color_ = Color::kRed;
      node = node->parent_->parent_;
    } else {
      if (node == child_to_check) {
        node = node->parent_;
        first_rotate(node);
      }
      node->parent_->color_ = Color::kBlack;
      node->parent_->parent_->color_ = Color::kRed;
      second_rotate(node->parent_->parent_);
    }
  }

  void FixInsert(Node<T> *node) {
    auto right_rotate{[this](Node<T> *temp_node) { RightRotate(temp_node); }};
    auto left_rotate{[this](Node<T> *temp_node) { LeftRotate(temp_node); }};

    while (node != root_ && node->parent_->color_ == Color::kRed) {
      if (node->parent_ == node->parent_->parent_->right_) {
        Node<T> *aunt_node = node->parent_->parent_->left_;
        FixInsertHelper(aunt_node, node, right_rotate, left_rotate,
                        node->parent_->left_);
      } else {
        Node<T> *uncle_node = node->parent_->parent_->right_;
        FixInsertHelper(uncle_node, node, left_rotate, right_rotate,
                        node->parent_->right_);
      }
      if (node == root_) {
        break;
      }
    }
    root_->color_ = Color::kBlack;
    UpdateParentForMaxNode();
  }

  void UpdateParentForMaxNode() {
    auto maxNode = FindMaxNode(root_);
    maxNode->right_->parent_ = maxNode;
    maxNode->left_->parent_ = maxNode;
  }

  void InsertNode(Node<T> *node) {
    Node<T> *y = nullptr;
    Node<T> *root = root_;

    while (root != nil_) {
      y = root;
      if (node->data_ < root->data_) {
        root = root->left_;
      } else {
        root = root->right_;
      }
    }

    node->parent_ = y;

    if (y == nullptr) {
      root_ = node;
    } else if (node->data_ < y->data_) {
      y->left_ = node;
    } else {
      y->right_ = node;
    }

    if (node->parent_ == nullptr) {
      node->color_ = Color::kRed;
      return;
    }

    if (node->parent_->parent_ == nullptr) {
      return;
    }

    FixInsert(node);
  }

  [[nodiscard]] Node<T> *GetMinimalNode(Node<T> *node) {
    while (node->left_ != nil_) {
      node = node->left_;
    }
    return node;
  }

  void Transplant(Node<T> *replaced_node, Node<T> *replacing_node) {
    if (replaced_node->parent_ == nullptr) {
      root_ = replacing_node;
    } else if (replaced_node == replaced_node->parent_->left_) {
      replaced_node->parent_->left_ = replacing_node;
    } else {
      replaced_node->parent_->right_ = replacing_node;
    }

    replacing_node->parent_ = replaced_node->parent_;
  }

  void RemoveNode(Node<T> *node_to_delete) {
    Node<T> *successor_node;
    Node<T> *child_node;
    Color current_node_color = node_to_delete->color_;

    if (node_to_delete->left_ == nil_) {
      child_node = node_to_delete->right_;
      Transplant(node_to_delete, node_to_delete->right_);
    } else if (node_to_delete->right_ == nil_) {
      child_node = node_to_delete->left_;
      Transplant(node_to_delete, node_to_delete->left_);
    } else {
      successor_node = GetMinimalNode(node_to_delete->right_);
      current_node_color = successor_node->color_;
      child_node = successor_node->right_;

      if (successor_node->parent_ == node_to_delete) {
        child_node->parent_ = successor_node;
      } else {
        Transplant(successor_node, successor_node->right_);
        successor_node->right_ = node_to_delete->right_;
        successor_node->right_->parent_ = successor_node;
      }
      Transplant(node_to_delete, successor_node);
      successor_node->left_ = node_to_delete->left_;
      successor_node->left_->parent_ = successor_node;
      successor_node->color_ = node_to_delete->color_;
    }

    delete node_to_delete;
    node_to_delete = nullptr;

    if (current_node_color == Color::kBlack) {
      FixDelete(child_node);
    }
  }

  void FixDelete(Node<T> *node) {
    while (node != root_ &&
           (node == nullptr || node->color_ == Color::kBlack)) {
      if (node == node->parent_->left_) {
        Node<T> *sibling_node = node->parent_->right_;
        if (sibling_node->color_ == Color::kRed) {
          sibling_node->color_ = Color::kBlack;
          node->parent_->color_ = Color::kRed;
          LeftRotate(node->parent_);
          sibling_node = node->parent_->right_;
        }
        if (sibling_node->left_->color_ == Color::kBlack &&
            sibling_node->right_->color_ == Color::kBlack) {
          sibling_node->color_ = Color::kRed;
          node = node->parent_;
        } else {
          if (sibling_node->right_->color_ == Color::kBlack) {
            sibling_node->left_->color_ = Color::kBlack;
            sibling_node->color_ = Color::kRed;
            RightRotate(sibling_node);
            sibling_node = node->parent_->right_;
          }
          sibling_node->color_ = node->parent_->color_;
          node->parent_->color_ = Color::kBlack;
          sibling_node->right_->color_ = Color::kBlack;
          LeftRotate(node->parent_);
          node = root_;
        }
      } else {
        Node<T> *sibling_node = node->parent_->left_;
        if (sibling_node->color_ == Color::kRed) {
          sibling_node->color_ = Color::kBlack;
          node->parent_->color_ = Color::kRed;
          RightRotate(node->parent_);
          sibling_node = node->parent_->left_;
        }
        if ((sibling_node->right_->color_ == Color::kBlack) &&
            (sibling_node->left_->color_ == Color::kBlack)) {
          sibling_node->color_ = Color::kRed;
          node = node->parent_;
        } else {
          if (sibling_node->left_->color_ == Color::kBlack) {
            sibling_node->right_->color_ = Color::kBlack;
            sibling_node->color_ = Color::kRed;
            LeftRotate(sibling_node);
            sibling_node = node->parent_->left_;
          }
          sibling_node->color_ = node->parent_->color_;
          node->parent_->color_ = Color::kBlack;
          sibling_node->left_->color_ = Color::kBlack;
          RightRotate(node->parent_);
          node = root_;
        }
      }
    }
    node->color_ = Color::kBlack;
  }

  Node<T> *FindNode(Node<T> *root, const T &data) const {
    if (GetSize() == 0) {
      return root;
    }
    if (root == nullptr) {
      return nil_;
    }
    if (root->data_ == data) {
      return root;
    }
    if (data < root->data_) {
      return FindNode(root->left_, data);
    } else {
      return FindNode(root->right_, data);
    }
  }

  Node<T> *FindNodeByKey(Node<T> *root, const T &key) const {
    if (GetSize() == 0) {
      return root;
    }
    if (root == nullptr) {
      return nil_;
    }
    if (root->data_.first == key) {
      return root;
    }
    if (key < root->data_.first) {
      return FindNodeForMap(root->left_, key);
    } else {
      return FindNodeForMap(root->right_, key);
    }
  }

  void PrintHelper(Node<T> *root, std::string indent, bool last) const {
    if (root != nil_) {
      std::cerr << indent;
      if (last) {
        std::cerr << "R----";
        indent += "     ";
      } else {
        std::cerr << "L----";
        indent += "|    ";
      }
      std::string print_color = root->color_ == Color::kRed ? "RED" : "BLACK";
      std::cerr << root->data_ << "(" << print_color << ")"
                << "\n";
      PrintHelper(root->left_, indent, false);
      PrintHelper(root->right_, indent, true);
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_ASSOCIATIVE_RED_BLACK_TREE_RED_BLACK_TREE_H_