#ifndef CPP2_S21_CONTAINERS_1_ASSOCIATIVE_MULTISET_MULTISET_H_
#define CPP2_S21_CONTAINERS_1_ASSOCIATIVE_MULTISET_MULTISET_H_

#include "../set_base/set_base.h"

namespace s21 {
template <typename Key>
class multiset : public set_base<Key> {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;

  using RedBlackTreeType = RedBlackTree<Key>;
  using iterator = typename RedBlackTreeType::const_iterator;
  using const_iterator = typename RedBlackTreeType::const_iterator;

  using size_type = std::size_t;

 public: /* Member */
  multiset() = default;

  multiset(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      insert(item);
    }
  };

  multiset(const multiset &other) {
    iterator other_iterator = other.begin();
    while (other_iterator != other.end()) {
      insert(*other_iterator);
      ++other_iterator;
    }
  }

  multiset(multiset &&other) noexcept { this->tree_ = std::move(other.tree_); }

 public: /* Operators */
  multiset<Key> &operator=(const multiset &other) {
    if (this != &other) {
      iterator other_iterator = other.begin();
      while (other_iterator != other.end()) {
        insert(*other_iterator);
        ++other_iterator;
      }
    }
    return *this;
  }

  multiset<Key> &operator=(multiset &&other) noexcept {
    if (this != &other) {
      this->tree_.Clear();
      this->tree_ = std::move(other.tree_);
    }
    return *this;
  }

 public: /* Modifiers */
  iterator insert(const value_type &value) {
    iterator result = this->tree_.Insert(value);
    return result;
  }

  template <typename... Args>
  std::vector<iterator> insert_many(Args &&...args) {
    std::initializer_list<value_type> items = {std::forward<Args>(args)...};
    std::vector<iterator> result{};

    for (const_reference item : items) {
      result.push_back(insert(item));
    }
    return result;
  }

  void merge(multiset &other) {
    for (const auto &item : other) {
      insert(item);
    }
    other.clear();
  }

 public: /* Lookup */
  std::pair<iterator, iterator> equal_range(const value_type &data) const {
    auto lower = lower_bound(data);
    auto upper = upper_bound(data);
    return {lower, upper};
  }

  iterator lower_bound(const value_type &data) const {
    return this->tree_.GetLowerBoundIterator(data);
  }

  iterator upper_bound(const value_type &data) const {
    return this->tree_.GetUpperBoundIterator(data);
  }
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_ASSOCIATIVE_MULTISET_MULTISET_H_