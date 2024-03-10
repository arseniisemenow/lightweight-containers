namespace s21 {
template <typename T, typename U>
void AssertContainerEquality(const T &first_container,
                             const U &second_container) {
  ASSERT_EQ(first_container.empty(), second_container.empty());
  ASSERT_EQ(first_container.size(), second_container.size());

  if constexpr (HasIterator<T>::value && HasIterator<U>::value) {
    auto first_iter = first_container.begin();
    auto second_iter = second_container.begin();
    while (first_iter != first_container.end()) {
      if constexpr (HasFirstAndSecond<decltype(first_iter)>::value &&
                    HasFirstAndSecond<decltype(second_iter)>::value) {
        ASSERT_EQ(first_iter->first, second_iter->first);
        ASSERT_EQ(first_iter->second, second_iter->second);
      } else {
        ASSERT_EQ(*first_iter, *second_iter);
      }
      ++first_iter;
      ++second_iter;
    }
  }
}

template <typename T>
void AssertStackEquality(std::stack<T> first_stack,
                         s21::stack<T> second_stack) {
  ASSERT_EQ(first_stack.empty(), second_stack.empty());
  ASSERT_EQ(first_stack.size(), second_stack.size());

  std::size_t original_size{first_stack.size()};
  for (std::size_t i{0}; i < original_size; ++i) {
    ASSERT_EQ(first_stack.top(), second_stack.top());
    first_stack.pop();
    second_stack.pop();
  }
}

template <typename T>
void AssertQueueEquality(std::queue<T> first_queue,
                         s21::queue<T> second_queue) {
  ASSERT_EQ(first_queue.empty(), second_queue.empty());
  ASSERT_EQ(first_queue.size(), second_queue.size());

  std::size_t original_size{first_queue.size()};
  for (std::size_t i{0}; i < original_size; ++i) {
    ASSERT_EQ(first_queue.front(), second_queue.front());
    ASSERT_EQ(first_queue.back(), second_queue.back());
    first_queue.pop();
    second_queue.pop();
  }
}

template <typename T>
void PrintContainer(const T &container, std::string_view container_type) {
  if (!container_type.empty())
    std::cout << "container type: " << container_type << '\n';

  std::cout << "values:\n";
  for (const auto &element : container) {
    std::cout << element << ' ';
  }
  std::cout << '\n';
}
}  // namespace s21