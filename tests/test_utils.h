#ifndef CPP_S21_CONTAINERS_1_TESTS_TEST_UTILS_H_
#define CPP_S21_CONTAINERS_1_TESTS_TEST_UTILS_H_

#include <gtest/gtest.h>

#include <iostream>
#include <queue>
#include <stack>
#include <string_view>
#include <type_traits>
#include <utility>

#include "../src/adaptors/queue/queue.h"
#include "../src/adaptors/stack/stack.h"

namespace s21 {
template <typename Iterator, typename = void>
struct HasFirstAndSecond : std::false_type {};

template <typename Iterator>
struct HasFirstAndSecond<Iterator,
                         std::void_t<decltype(std::declval<Iterator>().first),
                                     decltype(std::declval<Iterator>().second)>>
    : std::true_type {};

template <typename T>
struct HasIterator {
 private:
  template <typename U>
  static auto detect(int)
      -> decltype(std::declval<U>().begin(), std::true_type{});

  template <typename>
  static auto detect(...) -> std::false_type;

 public:
  static constexpr bool value{decltype(detect<T>(0))::value};
};

template <typename T, typename U>
void AssertContainerEquality(const T& first_container,
                             const U& second_container);

template <typename T>
void AssertStackEquality(std::stack<T> first_stack, s21::stack<T> second_stack);

template <typename T>
void AssertQueueEquality(std::queue<T> first_stack, s21::queue<T> second_stack);

template <typename T>
void PrintContainer(const T& container, std::string_view container_type = "");
}  // namespace s21

#include "test_utils.inl"

#endif  // CPP_S21_CONTAINERS_1_TESTS_TEST_UTILS_H_