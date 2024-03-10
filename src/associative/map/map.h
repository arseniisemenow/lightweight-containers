#ifndef CPP2_S21_CONTAINERS_1_ASSOCIATIVE_MAP_MAP_H_
#define CPP2_S21_CONTAINERS_1_ASSOCIATIVE_MAP_MAP_H_

#include "../red_black_tree/RedBlackTree.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using pair_type = std::pair<const Key, T>;
  using reference = value_type &;
  using const_reference = const value_type &;

  using RedBlackTreeIterator =
      typename RedBlackTree<pair_type>::RedBlackTreeIterator;
  using RedBlackTreeConstIterator =
      typename RedBlackTree<pair_type>::RedBlackTreeConstIterator;

  using iterator = RedBlackTreeIterator;
  using const_iterator = RedBlackTreeConstIterator;

  using size_type = std::size_t;

 public: /* Constructors */
  map() = default;

  map(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      insert(item);
    }
  }

  map(const map &other) {
    iterator other_iterator = other.begin();
    while (other_iterator != other.end()) {
      insert(*other_iterator);
      ++other_iterator;
    }
  }

  map(map &&other) noexcept { this->tree_ = std::move(other.tree_); }

  ~map() = default;

 public: /* Operators */
  map<Key, T> &operator=(const map &other) {
    if (this != &other) {
      clear();
      iterator other_iterator = other.begin();
      while (other_iterator != other.end()) {
        insert(*other_iterator);
        ++other_iterator;
      }
    }
    return *this;
  }

  map<Key, T> &operator=(map &&other) noexcept {
    if (this != &other) {
      tree_.Clear();
      tree_ = std::move(other.tree_);
    }
    return *this;
  }

 public: /* Element access-mutate */
  mapped_type &operator[](const key_type &key) {
    iterator it = find(key);
    if (it != end()) {
      return it->second;
    } else {
      value_type default_value = std::make_pair(key, mapped_type());
      insert(default_value);
      return tree_.Search(default_value)->data_.second;
    }
  }

  T &at(const Key &key) {
    iterator it = find(key);
    if (it != end()) {
      return it.operator*().second;
    } else {
      throw std::out_of_range("Key is not found in the map");
    }
  }

 public: /* Iterators */
  [[nodiscard]] iterator begin() const {
    iterator iter(tree_.FindMinNode(tree_.GetRoot()), tree_.GetNil());
    return iter;
  }

  [[nodiscard]] iterator end() const {
    iterator iter(tree_.GetNil(), tree_.GetNil());
    return iter;
  }

 public: /* Modifiers */
  void clear() { tree_.Clear(); }

  std::pair<iterator, bool> insert(const pair_type &pair) {
    std::pair<iterator, bool> result{};
    result.first = find_by_key(pair.first);
    if (result.first == end()) {
      tree_.Insert(pair);
      result.first = find_by_key(pair.first);
      result.second = true;
    }
    return result;
  }

  std::pair<iterator, bool> insert(const Key &key, const T &data) {
    auto pair = std::make_pair(key, data);
    return insert(pair);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &data) {
    iterator it = find(key);
    if (it != end()) {
      it->second = data;
      return std::make_pair(it, false);
    } else {
      return insert(std::make_pair(key, data));
    }
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::initializer_list<pair_type> items = {std::forward<Args>(args)...};
    std::vector<std::pair<iterator, bool>> result{};

    for (const_reference item : items) {
      result.push_back(insert(item));
    }
    return result;
  }

  void erase(const pair_type &data) { tree_.Remove(data); }

  void erase(const Key &key) {
    auto iter = find(key);
    if (iter != end()) {
      tree_.Remove(*iter);
    }
  }

  void erase(iterator iter) {
    auto find_iter = find_by_pair(*iter);
    if (find_iter != end()) {
      tree_.Remove((*find_iter));
    }
  }

  void swap(map &other) { std::swap(tree_, other.tree_); }

  void merge(map &other) {
    auto temp_other{other};
    for (const auto &item : other) {
      auto insert_pair = insert(item);
      if (insert_pair.second == true) {
        temp_other.erase(*insert_pair.first);
      }
    }
    other = temp_other;
  }

 public: /* Capacity */
  [[nodiscard]] bool empty() const { return tree_.IsEmpty(); }

  [[nodiscard]] size_type size() const { return tree_.GetSize(); }

  [[nodiscard]] size_type max_size() const { return tree_.GetMaxSize(); }

 public: /* Lookup */
  [[nodiscard]] bool contains(const Key &key) const {
    return find(key) != end();
  }

  [[nodiscard]] iterator find_by_pair(const pair_type &pair) const {
    auto node_to_find = tree_.Search(pair);
    return iterator(node_to_find, tree_.GetNil());
  }

  [[nodiscard]] iterator find(const Key &key) const { return find_by_key(key); }

  [[nodiscard]] iterator find_by_key(const Key &key) const {
    auto iter = begin();

    while (iter != end()) {
      if ((*iter).first == key) {
        auto node = find_node_by_pair(*iter);
        return iterator(node, tree_.GetNil());
      }
      ++iter;
    }
    return iterator(tree_.GetNil(), tree_.GetNil());
  }

  [[nodiscard]] std::pair<iterator, iterator> equal_range(
      const Key &key) const {
    auto lower = lower_bound(key);
    auto upper = upper_bound(key);
    return {lower, upper};
  }

  [[nodiscard]] iterator lower_bound(const Key &key) const {
    auto iter_node = find_by_key(key);
    if (iter_node == end()) {
      return begin();
    }
    auto lower = lower_bound_by_pair(*iter_node);
    return lower;
  }

  [[nodiscard]] iterator upper_bound(const Key &key) const {
    auto iter_node = find_by_key(key);
    if (iter_node == end()) {
      return begin();
    }
    auto upper = upper_bound_by_pair(*iter_node);
    return upper;
  }

 private:
  Node<pair_type> *find_node_by_pair(const pair_type &pair) const {
    Node<pair_type> *node_to_find = tree_.Search(pair);
    return node_to_find;
  }

  iterator lower_bound_by_pair(const pair_type &pair) const {
    auto temp_iter = tree_.GetLowerBoundIteratorForMap(pair);
    auto iter_node = find_by_pair(*temp_iter);
    return iter_node;
  }

  iterator upper_bound_by_pair(const pair_type &pair) const {
    auto temp_iter = tree_.GetUpperBoundIteratorForMap(pair);
    auto iter_node = find_by_pair(*temp_iter);
    return iter_node;
  }

 private:
  RedBlackTree<pair_type> tree_;
};

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_ASSOCIATIVE_MAP_MAP_H_