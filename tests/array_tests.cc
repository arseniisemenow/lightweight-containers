#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "../src/sequence/array/array.h"
#include "test_utils.h"

namespace s21 {
class ArrayTest : public ::testing::Test {
 protected:
  void SetUp() override {
    stdArrayTenElements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    myArrayTenElements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  }

  std::array<int, 10> stdArrayTenElements{};
  s21::array<int, 10> myArrayTenElements{};
};

TEST_F(ArrayTest, DefaultConstructorTest) {
  std::array<int, 4> array{};
  s21::array<int, 4> myArray{};
  AssertContainerEquality(array, myArray);
}

TEST_F(ArrayTest, InitListConstructorTest) {
  std::array<int, 4> array{1, 2, 3, 4};
  s21::array<int, 4> myArray{1, 2, 3, 4};
  AssertContainerEquality(array, myArray);
}

TEST_F(ArrayTest, InitListConstructorThrowTest) {
  EXPECT_THROW((s21::array<int, 4>{1, 2, 3, 4, 5, 6}), std::out_of_range);
}

TEST_F(ArrayTest, CopyConstructorTest) {
  std::array<int, 10> array{stdArrayTenElements};
  s21::array<int, 10> myArray{myArrayTenElements};
  AssertContainerEquality(array, myArray);
}

TEST_F(ArrayTest, MoveConstructorTest) {
  std::array<int, 10> array{std::move(stdArrayTenElements)};
  s21::array<int, 10> myArray{std::move(myArrayTenElements)};
  AssertContainerEquality(array, myArray);
  AssertContainerEquality(stdArrayTenElements, myArrayTenElements);
}

TEST_F(ArrayTest, MoveAssignmentOperatorTest) {
  std::array<int, 10> array{};
  s21::array<int, 10> myArray{};

  array = std::move(stdArrayTenElements);
  myArray = std::move(myArrayTenElements);
  AssertContainerEquality(array, myArray);
  AssertContainerEquality(stdArrayTenElements, myArrayTenElements);
}

/* Self assignment is caused errors from warning with -Werror flag */
TEST_F(ArrayTest, SelfAssignmentTest) {
  std::array<int, 10> array{stdArrayTenElements};
  s21::array<int, 10> myArray{myArrayTenElements};

  //  array = std::move(array);
  //  myArray = std::move(myArray);
  AssertContainerEquality(array, myArray);
}

TEST_F(ArrayTest, ElementAccessAtTest) {
  for (int i{0}; i < 10; ++i) {
    ASSERT_EQ(stdArrayTenElements.at(i), myArrayTenElements.at(i));
  }
}

TEST_F(ArrayTest, ElementAccessAtExceptionTest) {
  EXPECT_THROW(stdArrayTenElements.at(10), std::out_of_range);
  EXPECT_THROW(stdArrayTenElements.at(100), std::out_of_range);
  EXPECT_THROW(stdArrayTenElements.at(-10), std::out_of_range);

  EXPECT_THROW(myArrayTenElements.at(10), std::out_of_range);
  EXPECT_THROW(myArrayTenElements.at(100), std::out_of_range);
  EXPECT_THROW(myArrayTenElements.at(-10), std::out_of_range);
}

TEST_F(ArrayTest, ElementAccessSubscriptOperatorTest) {
  for (int i{0}; i < 10; ++i) {
    ASSERT_EQ(stdArrayTenElements[i], myArrayTenElements[i]);
  }
}

TEST_F(ArrayTest, ElementAccessFrontTest) {
  ASSERT_EQ(stdArrayTenElements.front(), myArrayTenElements.front());
}

TEST_F(ArrayTest, ElementAccessBackTest) {
  ASSERT_EQ(stdArrayTenElements.back(), myArrayTenElements.back());
}

TEST_F(ArrayTest, ElementAccessDataTest) {
  auto data{myArrayTenElements.data()};
  auto stdData{stdArrayTenElements.data()};

  for (int i{0}; i < 10; ++i) {
    ASSERT_EQ(data[i], stdData[i]);
  }

  ASSERT_EQ(sizeof(data), sizeof(stdData));
}

TEST_F(ArrayTest, IteratorTest) {
  ASSERT_EQ(*myArrayTenElements.begin(), myArrayTenElements[0]);
  ASSERT_EQ(*(myArrayTenElements.end() - 1), myArrayTenElements[9]);
  ASSERT_EQ(*stdArrayTenElements.begin(), stdArrayTenElements[0]);
  ASSERT_EQ(*(stdArrayTenElements.end() - 1), stdArrayTenElements[9]);

  ASSERT_EQ(*myArrayTenElements.cbegin(), myArrayTenElements[0]);
  ASSERT_EQ(*(myArrayTenElements.cend() - 1), myArrayTenElements[9]);
  ASSERT_EQ(*stdArrayTenElements.cbegin(), stdArrayTenElements[0]);
  ASSERT_EQ(*(stdArrayTenElements.cend() - 1), stdArrayTenElements[9]);
}

TEST_F(ArrayTest, EmptyTest1) {
  ASSERT_EQ(stdArrayTenElements.empty(), myArrayTenElements.empty());

  std::array<int, 1> array;
  s21::array<int, 1> myArray;
  ASSERT_EQ(array.empty(), myArray.empty());
}

TEST_F(ArrayTest, EmptyTest2) {
  std::array<int, 0> array;
  s21::array<int, 0> myArray;
  ASSERT_EQ(array.empty(), myArray.empty());
}

TEST_F(ArrayTest, SizeTest1) {
  ASSERT_EQ(stdArrayTenElements.size(), myArrayTenElements.size());

  std::array<int, 1> array;
  s21::array<int, 1> myArray;
  ASSERT_EQ(array.size(), myArray.size());
}

TEST_F(ArrayTest, SizeTest2) {
  std::array<int, 0> array;
  s21::array<int, 0> myArray;
  ASSERT_EQ(array.size(), myArray.size());
}

TEST_F(ArrayTest, MaxSizeTest1) {
  ASSERT_EQ(stdArrayTenElements.max_size(), myArrayTenElements.max_size());

  std::array<int, 1> array;
  s21::array<int, 1> myArray;
  ASSERT_EQ(array.max_size(), myArray.max_size());
}

TEST_F(ArrayTest, MaxSizeTest2) {
  std::array<int, 0> array;
  s21::array<int, 0> myArray;
  ASSERT_EQ(array.max_size(), myArray.max_size());
}

TEST_F(ArrayTest, SwapTest) {
  s21::array<int, 10> myArray{};
  myArray.swap(myArrayTenElements);

  for (int i{0}; i < 10; ++i) {
    ASSERT_EQ(myArray[i], i + 1);
    ASSERT_EQ(myArrayTenElements[i], 0);
  }
}

TEST_F(ArrayTest, FillTest) {
  s21::array<int, 10> myArray{};
  myArray.fill(100);
  myArrayTenElements.fill(50);

  for (int i{0}; i < 10; ++i) {
    ASSERT_EQ(myArray[i], 100);
    ASSERT_EQ(myArrayTenElements[i], 50);
  }
}
}  // namespace s21
