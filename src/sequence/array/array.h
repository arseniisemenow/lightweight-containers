#ifndef CPP2_S21_CONTAINERS_1_SEQUENCE_ARRAY_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SEQUENCE_ARRAY_ARRAY_H_

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <type_traits>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  constexpr array() = default;

  constexpr array(const std::initializer_list<T> &items) {
    if (items.size() > N) {
      throw std::out_of_range{
          "s21::array::array(const std::initializer_list<T>&): Initializer "
          "list size exceeds GetSize of array"};
    }

    std::size_t index{0};
    for (const auto &element : items) {
      data_[index++] = element;
    }
  }

  constexpr array(const array &other) = default;

  constexpr array(array &&other) noexcept = default;

  ~array() = default;

  constexpr array &operator=(const array &other) noexcept = default;

  constexpr array &operator=(array &&other) noexcept = default;

  constexpr reference at(size_type position) {
    if (position >= size()) {
      throw std::out_of_range{
          "s21::array::at(size_type): position index out of range"};
    }

    return data_[position];
  }

  constexpr const_reference at(size_type position) const {
    if (position >= size()) {
      throw std::out_of_range{
          "s21::array::at(size_type): position index out of range"};
    }

    return data_[position];
  }

  constexpr reference operator[](size_type position) { return data_[position]; }

  constexpr const_reference operator[](size_type position) const {
    return data_[position];
  }

  [[nodiscard]] constexpr const_reference front() const { return *cbegin(); }

  [[nodiscard]] constexpr const_reference back() const { return *(cend() - 1); }

  [[nodiscard]] constexpr const_iterator data() const noexcept {
    return cbegin();
  }

  [[nodiscard]] constexpr iterator data() noexcept { return begin(); }

  [[nodiscard]] constexpr iterator begin() noexcept { return &data_[0]; }

  [[nodiscard]] constexpr iterator end() noexcept { return &data_[N]; }

  [[nodiscard]] constexpr const_iterator begin() const noexcept {
    return &data_[0];
  }

  [[nodiscard]] constexpr const_iterator end() const noexcept {
    return &data_[N];
  }

  [[nodiscard]] constexpr const_iterator cbegin() const noexcept {
    return &data_[0];
  }

  [[nodiscard]] constexpr const_iterator cend() const noexcept {
    return &data_[N];
  }

  [[nodiscard]] constexpr bool empty() const { return (cbegin() == cend()); }

  [[nodiscard]] constexpr size_type size() const noexcept {
    return (cend() - cbegin());
  }

  [[nodiscard]] constexpr size_type max_size() const noexcept {
    return (cend() - cbegin());
  }

  constexpr void swap(array &other) noexcept(std::is_nothrow_swappable<T>{}) {
    for (std::size_t i{0}; i < size(); ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  }

  constexpr void fill(const T &item) {
    for (std::size_t index{0}; index < size(); ++index) {
      data_[index] = item;
    }
  }

 private:
  T data_[N]{};
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SEQUENCE_ARRAY_ARRAY_H_
