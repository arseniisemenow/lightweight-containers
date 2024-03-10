#ifndef CPP2_S21_CONTAINERS_1_ASSOCIATIVE_SET_BASE_SET_BASE_H_
#define CPP2_S21_CONTAINERS_1_ASSOCIATIVE_SET_BASE_SET_BASE_H_

#include "../red_black_tree/RedBlackTree.h"

namespace s21 {
template <typename Key>
class set_base {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;

  using RedBlackTreeType = RedBlackTree<Key>;
  using iterator = typename RedBlackTreeType::const_iterator;
  using const_iterator = typename RedBlackTreeType::const_iterator;

  using size_type = std::size_t;

 public: /* Iterators */
  iterator begin() { return tree_.begin(); }

  const_iterator begin() const { return tree_.begin(); }

  iterator end() { return tree_.end(); }

  const_iterator end() const { return tree_.end(); }

 public: /* Modifiers */
  void clear() { tree_.Clear(); }

  void erase(const value_type &value) { tree_.Remove(value); }

  void swap(set_base &other) { std::swap(tree_, other.tree_); }

 public: /* Capacity */
  [[nodiscard]] size_t max_size() const { return tree_.GetMaxSize(); }

  [[nodiscard]] bool empty() const { return tree_.IsEmpty(); }

  [[nodiscard]] size_t size() const { return tree_.GetSize(); }

 public: /* Lookup */
  [[nodiscard]] iterator find(const value_type &value) const {
    iterator iter = begin();
    iterator end_iter = end();

    while (iter != end_iter) {
      if (*iter == value) {
        return iter;
      }
      ++iter;
    }

    return end();
  }

  [[nodiscard]] bool contains(const value_type &value) const {
    return tree_.Search(value) != nullptr;
  }

 protected:
  RedBlackTreeType tree_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_ASSOCIATIVE_SET_BASE_SET_BASE_H_
