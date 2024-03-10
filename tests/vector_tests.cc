#include <gtest/gtest.h>

#include <map>
#include <type_traits>
#include <vector>

#include "../src/sequence/vector/vector.h"
#include "test_utils.h"

namespace s21 {
class VectorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    stdVectorTenElements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    myVectorTenElements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  }

  std::vector<int> stdVectorTenElements{};
  s21::vector<int> myVectorTenElements{};
};

TEST_F(VectorTest, DefaultConstructorTest) {
  std::vector<int> stdVector{};
  s21::vector<int> myVector{};
  AssertContainerEquality(stdVector, myVector);
}

TEST_F(VectorTest, SizeConstructorTest) {
  std::vector<int> stdVector(50);
  s21::vector<int> myVector(50);
  AssertContainerEquality(stdVector, myVector);
}

TEST_F(VectorTest, InitListConstructorTest) {
  std::vector<int> stdVector{1, 2, 3, 4, 5, 6};
  s21::vector<int> myVector{1, 2, 3, 4, 5, 6};
  AssertContainerEquality(stdVector, myVector);
}

TEST_F(VectorTest, CopyConstructorTest) {
  std::vector<int> stdVector{stdVectorTenElements};
  s21::vector<int> myVector{myVectorTenElements};
  AssertContainerEquality(stdVector, stdVectorTenElements);
  AssertContainerEquality(myVectorTenElements, myVector);
}

TEST_F(VectorTest, MoveConstructorTest) {
  std::vector<int> stdVector{std::move(stdVectorTenElements)};
  s21::vector<int> myVector{std::move(myVectorTenElements)};
  AssertContainerEquality(stdVector, myVector);
}

TEST_F(VectorTest, CopyAssignmentOperator) {
  std::vector<int> stdVector{};
  stdVector = stdVectorTenElements;
  s21::vector<int> myVector{};
  myVector = myVectorTenElements;
  AssertContainerEquality(myVector, stdVector);
}

TEST_F(VectorTest, MoveAssignmentOperator) {
  std::vector<int> stdVector{};
  stdVector = std::move(stdVectorTenElements);
  s21::vector<int> myVector{};
  myVector = std::move(myVectorTenElements);
  AssertContainerEquality(myVector, stdVector);
}

TEST_F(VectorTest, ElementAccessAtTestBegin) {
  int stdElement{stdVectorTenElements.at(0)};
  int myElement{myVectorTenElements.at(0)};
  ASSERT_EQ(stdElement, myElement);
}

TEST_F(VectorTest, ElementAccessAtTestMiddle) {
  int stdElement{stdVectorTenElements.at(4)};
  int myElement{myVectorTenElements.at(4)};
  ASSERT_EQ(stdElement, myElement);
}

TEST_F(VectorTest, ElementAccessAtTestEnd) {
  int stdElement{stdVectorTenElements.at(9)};
  int myElement{myVectorTenElements.at(9)};
  ASSERT_EQ(stdElement, myElement);
}

TEST_F(VectorTest, ElementAccessAtTestNegative) {
  EXPECT_THROW(myVectorTenElements.at(-5), std::out_of_range);
}

TEST_F(VectorTest, ElementAccessAtTestExceedSize) {
  EXPECT_THROW(myVectorTenElements.at(100), std::out_of_range);
}

TEST_F(VectorTest, ElementAccessSubscriptOperatorTestBegin) {
  int stdElement{stdVectorTenElements[0]};
  int myElement{myVectorTenElements[0]};
  ASSERT_EQ(stdElement, myElement);
}

TEST_F(VectorTest, ElementAccessSubscriptOperatorTestMiddle) {
  int stdElement{stdVectorTenElements[4]};
  int myElement{myVectorTenElements[4]};
  ASSERT_EQ(stdElement, myElement);
}

TEST_F(VectorTest, ElementAccessSubscriptOperatorTestEnd) {
  int stdElement{stdVectorTenElements[9]};
  int myElement{myVectorTenElements[9]};
  ASSERT_EQ(stdElement, myElement);
}

TEST_F(VectorTest, ElementAccessFrontTest) {
  int stdElement{stdVectorTenElements.front()};
  int myElement{myVectorTenElements.front()};
  ASSERT_EQ(stdElement, myElement);
}

TEST_F(VectorTest, ElementAccessBackTest) {
  int stdElement{stdVectorTenElements.back()};
  int myElement{myVectorTenElements.back()};
  ASSERT_EQ(stdElement, myElement);
}

TEST_F(VectorTest, ElementAccessDataTest) {
  int* stdData{stdVectorTenElements.data()};
  int* myData{myVectorTenElements.data()};
  for (int i{0}; i < 10; ++i) {
    ASSERT_EQ(stdData[i], myData[i]);
  }
  ASSERT_EQ(sizeof(stdData), sizeof(myData));
}

TEST_F(VectorTest, IteratorBeginTest) {
  ASSERT_EQ(*myVectorTenElements.begin(), myVectorTenElements[0]);
  ASSERT_EQ(*myVectorTenElements.cbegin(), myVectorTenElements[0]);
}

TEST_F(VectorTest, IteratorEndTest) {
  ASSERT_EQ(*(myVectorTenElements.end() - 1), myVectorTenElements[9]);
  ASSERT_EQ(*(myVectorTenElements.cend() - 1), myVectorTenElements[9]);
}

TEST_F(VectorTest, IteratorConversionTest) {
  s21::vector<int>::iterator nonConstIter{myVectorTenElements.begin()};
  s21::vector<int>::const_iterator constIter{myVectorTenElements.cbegin()};
  s21::vector<int>::const_iterator constIterCopy{nonConstIter};
  s21::vector<int>::iterator nonConstIterCopy{nonConstIter};
  s21::vector<int>::const_iterator constIterCopy2{constIter};
}

TEST_F(VectorTest, EmptyTest1) {
  ASSERT_EQ(stdVectorTenElements.empty(), myVectorTenElements.empty());

  std::vector<int> vector(1);
  s21::vector<int> myVector(1);
  ASSERT_EQ(vector.empty(), myVector.empty());
}

TEST_F(VectorTest, EmptyTest2) {
  std::vector<int> vector(0);
  s21::vector<int> myVector(0);
  ASSERT_EQ(vector.empty(), myVector.empty());
}

TEST_F(VectorTest, SizeTest1) {
  ASSERT_EQ(stdVectorTenElements.size(), myVectorTenElements.size());

  std::vector<int> vector(1);
  s21::vector<int> myVector(1);
  ASSERT_EQ(vector.size(), myVector.size());
}

TEST_F(VectorTest, SizeTest2) {
  std::vector<int> vector(0);
  s21::vector<int> myVector(0);
  ASSERT_EQ(vector.size(), myVector.size());
}

TEST_F(VectorTest, MaxSizeTest1) {
  ASSERT_EQ(stdVectorTenElements.max_size(), myVectorTenElements.max_size());

  std::vector<int> vector(1);
  s21::vector<int> myVector(1);
  ASSERT_EQ(vector.max_size(), myVector.max_size());
}

TEST_F(VectorTest, MaxSizeTest2) {
  std::vector<int> vector(0);
  s21::vector<int> myVector(0);
  ASSERT_EQ(vector.max_size(), myVector.max_size());
}

TEST_F(VectorTest, CapacityTest1) {
  ASSERT_EQ(stdVectorTenElements.capacity(), myVectorTenElements.capacity());

  std::vector<int> vector(1);
  s21::vector<int> myVector(1);
  ASSERT_EQ(vector.capacity(), myVector.capacity());
}

TEST_F(VectorTest, CapacityTest2) {
  std::vector<int> vector(0);
  s21::vector<int> myVector(0);
  ASSERT_EQ(vector.capacity(), myVector.capacity());
}

TEST_F(VectorTest, ReserveTest1) {
  stdVectorTenElements.reserve(100);
  myVectorTenElements.reserve(100);
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, ReserveTest2) {
  stdVectorTenElements.reserve(3);
  myVectorTenElements.reserve(3);
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, ReserveTest3) {
  EXPECT_THROW(myVectorTenElements.reserve(-1), std::length_error);
}

TEST_F(VectorTest, ReserveTest4) {
  std::vector<int> vector{};
  vector.reserve(100000);
  s21::vector<int> myVector{};
  myVector.reserve(100000);
  AssertContainerEquality(vector, myVector);
}

TEST_F(VectorTest, ShrinkToFitTest1) {
  stdVectorTenElements.shrink_to_fit();
  myVectorTenElements.shrink_to_fit();
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, ShrinkToFitTest2) {
  std::vector<int> vector{};
  vector.reserve(100000);
  vector.shrink_to_fit();
  s21::vector<int> myVector{};
  myVector.reserve(100000);
  myVector.shrink_to_fit();
  AssertContainerEquality(vector, myVector);
}

TEST_F(VectorTest, ClearTest1) {
  stdVectorTenElements.clear();
  myVectorTenElements.clear();
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, ClearTest2) {
  std::vector<int> vector{};
  vector.clear();
  s21::vector<int> myVector{};
  myVector.clear();
  AssertContainerEquality(vector, myVector);
}

// todo: check for iterator return!!!
TEST_F(VectorTest, InsertBeginTest) {
  stdVectorTenElements.insert(stdVectorTenElements.begin(), 100);
  myVectorTenElements.insert(myVectorTenElements.begin(), 100);
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, InsertMiddleTest) {
  stdVectorTenElements.insert(stdVectorTenElements.begin() + 3, 100);
  myVectorTenElements.insert(myVectorTenElements.begin() + 3, 100);
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, InsertEndTest) {
  stdVectorTenElements.insert(stdVectorTenElements.end(), 100);
  myVectorTenElements.insert(myVectorTenElements.end(), 100);
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, EraseBeginTest) {
  stdVectorTenElements.erase(stdVectorTenElements.begin());
  myVectorTenElements.erase(myVectorTenElements.begin());
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, EraseMiddleTest) {
  stdVectorTenElements.erase(stdVectorTenElements.begin() + 3);
  myVectorTenElements.erase(myVectorTenElements.begin() + 3);
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, EraseEndTest) {
  stdVectorTenElements.erase(stdVectorTenElements.end() - 1);
  myVectorTenElements.erase(myVectorTenElements.end() - 1);
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, EraseAllTest) {
  for (int i{0}; i < 10; ++i) {
    stdVectorTenElements.erase(stdVectorTenElements.begin());
    myVectorTenElements.erase(myVectorTenElements.begin());
  }
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, PushBackTest) {
  stdVectorTenElements.push_back(1000);
  myVectorTenElements.push_back(1000);
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, PushBackManyTest) {
  for (int i{0}; i < 1000; ++i) {
    stdVectorTenElements.push_back(i);
    myVectorTenElements.push_back(i);
  }
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, PopBackTest) {
  stdVectorTenElements.pop_back();
  myVectorTenElements.pop_back();
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, PopBackManyTest) {
  for (int i{0}; i < 5; ++i) {
    stdVectorTenElements.pop_back();
    myVectorTenElements.pop_back();
  }
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, SwapTest) {
  std::vector<int> otherStdVector{1, 2, 3, 4, 5};
  s21::vector<int> myOtherVector{1, 2, 3, 4, 5};
  stdVectorTenElements.swap(otherStdVector);
  myVectorTenElements.swap(myOtherVector);
  AssertContainerEquality(stdVectorTenElements, myVectorTenElements);
  AssertContainerEquality(otherStdVector, myOtherVector);
}

TEST_F(VectorTest, InsertManyTest1) {
  s21::vector<int> myVector{};
  auto iter = myVector.insert_many(myVector.cbegin(), 1, 2, 3, 4, 5);
  s21::vector<int> resultVector{1, 2, 3, 4, 5};
  ASSERT_EQ(*iter, 1);
  AssertContainerEquality(myVector, resultVector);
}

TEST_F(VectorTest, InsertManyTest2) {
  myVectorTenElements.insert_many(myVectorTenElements.cbegin());
  AssertContainerEquality(myVectorTenElements, myVectorTenElements);
}

TEST_F(VectorTest, InsertManyTest3) {
  auto iter = myVectorTenElements.insert_many(myVectorTenElements.cbegin(), 5);
  s21::vector<int> resultVector{5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(*iter, 5);
  AssertContainerEquality(resultVector, myVectorTenElements);
}

TEST_F(VectorTest, InsertManyTest4) {
  auto iter =
      myVectorTenElements.insert_many(myVectorTenElements.cbegin(), 5, 6);
  s21::vector<int> resultVector{5, 6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(*iter, 5);
  AssertContainerEquality(resultVector, myVectorTenElements);
}

TEST_F(VectorTest, InsertManyTest5) {
  myVectorTenElements.insert_many(myVectorTenElements.cbegin() + 3, 5);
  s21::vector<int> resultVector{1, 2, 3, 5, 4, 5, 6, 7, 8, 9, 10};
  AssertContainerEquality(resultVector, myVectorTenElements);
}

TEST_F(VectorTest, InsertManyTest6) {
  myVectorTenElements.insert_many(myVectorTenElements.cbegin() + 3);
  s21::vector<int> resultVector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  AssertContainerEquality(resultVector, myVectorTenElements);
}

TEST_F(VectorTest, InsertManyTest7) {
  myVectorTenElements.insert_many(myVectorTenElements.cend() - 1, 1, 2);
  s21::vector<int> resultVector{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 10};
  AssertContainerEquality(resultVector, myVectorTenElements);
}

TEST_F(VectorTest, InsertManyTest8) {
  myVectorTenElements.insert_many(myVectorTenElements.cend(), 1, 2);
  s21::vector<int> resultVector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2};
  AssertContainerEquality(resultVector, myVectorTenElements);
}

TEST_F(VectorTest, InsertManyBackTest1) {
  myVectorTenElements.insert_many_back(1, 2, 3);
  s21::vector<int> resultVector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3};
  AssertContainerEquality(resultVector, myVectorTenElements);
}

TEST_F(VectorTest, InsertManyBackTest2) {
  myVectorTenElements.insert_many_back(1);
  s21::vector<int> resultVector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1};
  AssertContainerEquality(resultVector, myVectorTenElements);
}

TEST_F(VectorTest, InsertManyBackTest3) {
  myVectorTenElements.insert_many_back();
  s21::vector<int> resultVector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  AssertContainerEquality(resultVector, myVectorTenElements);
}
}  // namespace s21
