#ifndef CPP2_S21_CONTAINERS_1_ADAPTORS_STACK_STACK_H_
#define CPP2_S21_CONTAINERS_1_ADAPTORS_STACK_STACK_H_

#include <cstddef>
#include <initializer_list>

#include "../../sequence/list/list.h"

namespace s21 {
template <typename T, class Container = list<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 public:
  stack() = default;

  stack(const std::initializer_list<T> &items) {
    for (const auto &item : items) {
      push(item);
    }
  }

  stack(const stack &other) : container_{other.container_} {}

  stack(stack &&other) : container_{std::move(other.container_)} {}

  ~stack() = default;

  stack &operator=(const stack &other) {
    container_ = other.container_;
    return *this;
  }

  stack &operator=(stack &&other) {
    container_ = std::move(other.container_);
    return *this;
  }

  [[nodiscard]] reference top() { return *container_.begin(); }

  [[nodiscard]] const_reference top() const { return *container_.cbegin(); }

  [[nodiscard]] bool empty() const { return container_.empty(); }

  [[nodiscard]] size_type size() const { return container_.size(); }

  void push(const_reference value) { container_.push_front(value); }

  void pop() { container_.pop_front(); }

  void swap(stack &other) { container_.swap(other.container_); }

  template <typename... Args>
  void insert_many_front(Args &&...arguments) {
    std::initializer_list<value_type> items{arguments...};
    for (const auto &item : items) {
      push(item);
    }
  }

 private:
  Container container_{};
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_ADAPTORS_STACK_STACK_H_