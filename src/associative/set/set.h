#ifndef CPP2_S21_CONTAINERS_1_ASSOCIATIVE_SET_SET_H_
#define CPP2_S21_CONTAINERS_1_ASSOCIATIVE_SET_SET_H_

#include "../set_base/set_base.h"

namespace s21 {
template <typename Key>
class set : public set_base<Key> {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;

  using RedBlackTreeType = RedBlackTree<Key>;
  using iterator = typename RedBlackTreeType::const_iterator;
  using const_iterator = typename RedBlackTreeType::const_iterator;

  using size_type = std::size_t;

 public: /* Member */
  set() = default;

  set(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      insert(item);
    }
  };

  set(const set &other) {
    iterator other_iterator = other.begin();
    while (other_iterator != other.end()) {
      insert(*other_iterator);
      ++other_iterator;
    }
  }

  set(set &&other) noexcept { this->tree_ = std::move(other.tree_); }

  ~set() = default;

 public: /* Operators */
  set<Key> &operator=(const set &other) {
    this->tree_ = other.tree_;
    iterator other_iterator = other.begin();
    while (other_iterator != other.end()) {
      insert(*other_iterator);
      ++other_iterator;
    }
    return *this;
  }

  set<Key> &operator=(set &&other) noexcept {
    this->tree_ = std::move(other.tree_);
    return *this;
  }

 public: /* Modifiers */
  void merge(set &other) {
    for (const auto &item : other) {
      insert(item);
    }
    other.clear();
  }

  std::pair<iterator, bool> insert(const Key &value) {
    std::pair<iterator, bool> result{};
    result.first = this->find(value);
    if (result.first != this->end()) {
      return result;
    }
    result.first = this->tree_.Insert(value);
    result.second = true;
    return result;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::initializer_list<value_type> items = {std::forward<Args>(args)...};
    std::vector<std::pair<iterator, bool>> result{};

    for (const_reference item : items) {
      std::pair<iterator, bool> pair = this->insert(item);
      result.push_back(pair);
    }
    return result;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_ASSOCIATIVE_SET_SET_H_