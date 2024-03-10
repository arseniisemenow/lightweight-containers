#ifndef CPP2_S21_CONTAINERS_1_SEQUENCE_VECTOR_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_SEQUENCE_VECTOR_VECTOR_H_

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  template <bool IsConst>
  class VectorIteratorBase {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = std::conditional_t<IsConst, const T *, T *>;
    using reference = std::conditional_t<IsConst, const T &, T &>;

    VectorIteratorBase() = default;

    VectorIteratorBase(const VectorIteratorBase<IsConst> &other) = default;

    template <bool WasConst, class = std::enable_if_t<IsConst && !WasConst>>
    VectorIteratorBase(const VectorIteratorBase<WasConst> &other)
        : pointer_{other.operator->()} {}

    explicit VectorIteratorBase(pointer ptr) : pointer_{ptr} {}

    [[nodiscard]] reference operator*() const { return *pointer_; }

    [[nodiscard]] pointer operator->() const { return pointer_; }

    VectorIteratorBase &operator++() {
      ++pointer_;
      return *this;
    }

    VectorIteratorBase operator++(int) {
      return VectorIteratorBase{pointer_++};
    }

    VectorIteratorBase &operator--() {
      --pointer_;
      return *this;
    }

    VectorIteratorBase operator--(int) {
      return VectorIteratorBase{pointer_--};
    }

    reference operator[](difference_type offset) const {
      return pointer_[offset];
    }

    VectorIteratorBase operator+(difference_type offset) const {
      return VectorIteratorBase{pointer_ + offset};
    }

    difference_type operator+(const VectorIteratorBase &other) const {
      return pointer_ + other.pointer_;
    }

    VectorIteratorBase &operator+=(difference_type offset) {
      pointer_ += offset;
      return *this;
    }

    VectorIteratorBase operator-(difference_type offset) const {
      return VectorIteratorBase{pointer_ - offset};
    }

    difference_type operator-(const VectorIteratorBase &other) const {
      return pointer_ - other.pointer_;
    }

    VectorIteratorBase &operator-=(difference_type offset) {
      pointer_ -= offset;
      return *this;
    }

    bool operator==(const VectorIteratorBase &other) const {
      return (other.pointer_ == pointer_);
    }

    bool operator!=(const VectorIteratorBase &other) const {
      return other.pointer_ != pointer_;
    }

    bool operator<(const VectorIteratorBase &other) const {
      return pointer_ < other.pointer_;
    }

    bool operator<=(const VectorIteratorBase &other) const {
      return pointer_ <= other.pointer_;
    }

    bool operator>(const VectorIteratorBase &other) const {
      return pointer_ > other.pointer_;
    }

    bool operator>=(const VectorIteratorBase &other) const {
      return pointer_ >= other.pointer_;
    }

   private:
    pointer pointer_{};
  };

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = VectorIteratorBase<false>;
  using const_iterator = VectorIteratorBase<true>;
  using size_type = std::size_t;

  vector() = default;

  explicit vector(size_type size)
      : data_{new T[size]{}}, capacity_{size}, size_{size} {}

  vector(const std::initializer_list<T> &items)
      : data_{new T[items.size()]{}},
        capacity_{items.size()},
        size_{items.size()} {
    size_type index{0};
    for (const auto &item : items) {
      data_[index++] = item;
    }
  }

  vector(const vector &other)
      : data_{new T[other.capacity()]{}},
        capacity_{other.capacity()},
        size_{other.size()} {
    std::copy_n(other.begin(), size_, begin());
  }

  vector(vector &&other) noexcept
      : data_{other.data_}, capacity_{other.capacity_}, size_{other.size_} {
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
  }

  ~vector() {
    delete[] data_;
    data_ = nullptr;
  }

  vector &operator=(const vector &other) {
    if (this != &other) {
      delete[] data_;

      size_ = other.size_;
      capacity_ = other.capacity_;
      data_ = new T[capacity_]{};

      std::copy_n(other.begin(), size_, begin());
    }

    return *this;
  }

  vector &operator=(vector &&other) noexcept {
    if (this != &other) {
      delete[] data_;

      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;

      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }

    return *this;
  }

  reference at(size_type position) {
    if (position >= size()) {
      throw std::out_of_range{
          "s21::vector<T>::at(size_type): index out of range"};
    }
    return data_[position];
  }

  const_reference at(size_type position) const {
    if (position >= size()) {
      throw std::out_of_range{
          "s21::vector<T>::at(size_type): index out of range"};
    }
    return data_[position];
  }

  reference operator[](size_type position) { return data_[position]; }

  const_reference operator[](size_type position) const {
    return data_[position];
  }

  [[nodiscard]] const_reference front() const { return *begin(); }

  [[nodiscard]] const_reference back() const { return *(end() - 1); }

  [[nodiscard]] iterator begin() noexcept { return iterator{&data_[0]}; }

  [[nodiscard]] iterator end() noexcept { return iterator{&data_[size()]}; }

  [[nodiscard]] const_iterator begin() const noexcept {
    return const_iterator{&data_[0]};
  }

  [[nodiscard]] const_iterator end() const noexcept {
    return const_iterator{&data_[size()]};
  }

  [[nodiscard]] const_iterator cbegin() const noexcept {
    return const_iterator{&data_[0]};
  }

  [[nodiscard]] const_iterator cend() const noexcept {
    return const_iterator{&data_[size()]};
  }

  [[nodiscard]] T *data() noexcept { return data_; }

  [[nodiscard]] bool empty() const noexcept { return (begin() == end()); }

  [[nodiscard]] size_type size() const noexcept { return size_; }

  [[nodiscard]] size_type max_size() const noexcept {
    size_type max_difference{
        std::numeric_limits<typename iterator::difference_type>::max()};
    size_type max_allocator_size{std::allocator<T>{}.max_size()};
    return std::min(max_difference, max_allocator_size);
  }

  [[nodiscard]] size_type capacity() const noexcept { return capacity_; }

  void reserve(size_type reserve_size) {
    if (reserve_size > max_size())
      throw std::length_error{
          "s21::vector<T>::reserve(size_type): reserve_size exceeded max_size "
          "of vector"};
    if (reserve_size <= capacity_) return;

    reallocate(reserve_size);
  }

  void shrink_to_fit() {
    if (size_ == capacity_) return;

    reallocate(size_);
  }

  void clear() noexcept {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
  }

  iterator insert(iterator position, const_reference value) {
    auto distance{position - begin()};
    if (size_ == capacity_) {
      reserve(capacity_ * 2);
      position = begin() + distance;
    }

    size_type index_to_insert{static_cast<size_type>(position - begin())};
    T previous_element{data_[index_to_insert]};
    for (size_type i{index_to_insert + 1}; i <= size(); ++i) {
      std::swap(data_[i], previous_element);
    }

    data_[index_to_insert] = value;

    ++size_;

    return position;
  }

  void erase(iterator position) {
    if (empty()) return;

    size_type index_to_erase{static_cast<size_type>(position - begin())};

    data_[index_to_erase].~T();

    for (size_type i{index_to_erase + 1}; i < size(); ++i) {
      data_[i - 1] = data_[i];
    }

    --size_;
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() { erase(end() - 1); }

  void swap(vector &other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator position, Args &&...arguments) {
    auto distance{position - cbegin()};
    size_type number_of_arguments{sizeof...(arguments)};

    if (size_ + number_of_arguments > capacity_) {
      reserve(size_ + number_of_arguments);
      position = cbegin() + distance;
    }

    size_type index_to_insert{static_cast<size_type>(position - cbegin())};
    for (size_type i{size()}; i > index_to_insert; --i) {
      data_[i + number_of_arguments - 1] = data_[i - 1];
    }

    ((data_[index_to_insert++] = std::forward<Args>(arguments)), ...);

    size_ += number_of_arguments;

    return begin() + distance;
  }

  template <typename... Args>
  void insert_many_back(Args &&...arguments) {
    insert_many(cend(), arguments...);
  }

 private:
  void reallocate(size_type new_size) {
    T *new_data{new T[new_size]{}};
    std::copy_n(begin(), size_, new_data);
    delete[] data_;
    capacity_ = new_size;
    data_ = new_data;
  }

 private:
  T *data_{};
  size_type capacity_{};
  size_type size_{};
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SEQUENCE_VECTOR_VECTOR_H_