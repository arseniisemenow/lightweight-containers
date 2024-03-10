#ifndef CPP2_S21_CONTAINERS_1_ADAPTORS_QUEUE_QUEUE_H_
#define CPP2_S21_CONTAINERS_1_ADAPTORS_QUEUE_QUEUE_H_

#include <cstddef>
#include <initializer_list>

#include "../../sequence/list/list.h"

namespace s21 {
template <typename T, class Container = list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 public:
  queue() = default;

  queue(const std::initializer_list<T> &items) {
    for (const auto &item : items) {
      push(item);
    }
  }

  queue(const queue &other) : container_{other.container_} {}

  queue(queue &&other) : container_{std::move(other.container_)} {}

  ~queue() = default;

  queue &operator=(const queue &other) {
    container_ = other.container_;
    return *this;
  }

  queue &operator=(queue &&other) {
    container_ = std::move(other.container_);
    return *this;
  }

  [[nodiscard]] reference front() { return *container_.begin(); }

  [[nodiscard]] const_reference front() const { return *container_.cbegin(); }

  [[nodiscard]] reference back() { return *std::prev(container_.end()); }

  [[nodiscard]] const_reference back() const {
    return *std::prev(container_.cend());
  }

  [[nodiscard]] bool empty() const { return container_.empty(); }

  [[nodiscard]] size_type size() const { return container_.size(); }

  void push(const_reference value) { container_.push_back(value); }

  void pop() { container_.pop_front(); }

  void swap(queue &other) { container_.swap(other.container_); }

  template <typename... Args>
  void insert_many_back(Args &&...arguments) {
    container_.insert_many_back(arguments...);
  }

 private:
  Container container_{};
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_ADAPTORS_QUEUE_QUEUE_H_