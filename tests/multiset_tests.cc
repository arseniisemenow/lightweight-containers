#include <gtest/gtest.h>

#include <set>
#include <type_traits>

#include "../src/associative/multiset/multiset.h"
#include "test_utils.h"

namespace s21 {
class MultisetTest : public ::testing::Test {
 protected:
  void SetUp() override {
    stdMultisetTenElements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    myMultisetTenElements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  }

  std::multiset<int> stdMultisetTenElements{};
  s21::multiset<int> myMultisetTenElements{};
};

TEST_F(MultisetTest, DefaultConstructorTest) {
  std::multiset<int> stdMultiset{};
  s21::multiset<int> myMultiset{};
  AssertContainerEquality(stdMultiset, myMultiset);
}

TEST_F(MultisetTest, ListConstructorTest) {
  std::multiset<int> stdMultiset{1, 2, 3, 4, 5, 4, 3, 2, 1};
  s21::multiset<int> myMultiset{1, 2, 3, 4, 5, 4, 3, 2, 1};
  AssertContainerEquality(stdMultiset, myMultiset);
}

TEST_F(MultisetTest, ListConstructorTest2) {
  std::multiset<std::string> stdMultiset{"Here", "is", "some", "random",
                                         "words"};
  s21::multiset<std::string> myMultiset{"Here", "is", "some", "random",
                                        "words"};
  AssertContainerEquality(stdMultiset, myMultiset);
}

TEST_F(MultisetTest, CopyConstructorTest) {
  std::multiset<int> stdMultiset{stdMultisetTenElements};
  s21::multiset<int> myMultiset{myMultisetTenElements};
  AssertContainerEquality(stdMultiset, stdMultisetTenElements);
  AssertContainerEquality(myMultisetTenElements, myMultiset);
}

TEST_F(MultisetTest, MoveConstructorTest) {
  std::multiset<int> stdEmptyMultiset{};
  std::multiset<int> stdMultiset{std::move(stdMultisetTenElements)};

  s21::multiset<int> myEmptyMultiset{};
  s21::multiset<int> myMultiset{std::move(myMultisetTenElements)};

  AssertContainerEquality(stdMultiset, myMultiset);
  AssertContainerEquality(stdMultisetTenElements, stdEmptyMultiset);
  AssertContainerEquality(myMultisetTenElements, myEmptyMultiset);
}

TEST_F(MultisetTest, CopyAssignmentOperator) {
  std::multiset<int> stdMultiset{};
  stdMultiset = stdMultisetTenElements;
  s21::multiset<int> myMultiset{};
  myMultiset = myMultisetTenElements;
  AssertContainerEquality(stdMultiset, myMultiset);
}

TEST_F(MultisetTest, MoveAssignmentOperator) {
  std::multiset<int> stdMultiset{};
  stdMultiset = std::move(stdMultisetTenElements);
  s21::multiset<int> myMultiset{};
  myMultiset = std::move(myMultisetTenElements);
  AssertContainerEquality(myMultiset, stdMultiset);
}

TEST_F(MultisetTest, ElementAccessOperatorTestBegin) {
  int stdElement{*stdMultisetTenElements.begin()};
  int myElement{*myMultisetTenElements.begin()};
  ASSERT_EQ(stdElement, myElement);
}

TEST_F(MultisetTest, ElementAccessOperatorTestEnd) {
  int stdElement{*std::prev(stdMultisetTenElements.end())};
  int myElement{*std::prev(myMultisetTenElements.end())};
  ASSERT_EQ(stdElement, myElement);
}

TEST_F(MultisetTest, EmptyTest1) {
  ASSERT_EQ(stdMultisetTenElements.empty(), myMultisetTenElements.empty());

  std::multiset<int> multiset{1};
  s21::multiset<int> myMultiset{1};
  ASSERT_EQ(multiset.empty(), myMultiset.empty());
}

TEST_F(MultisetTest, EmptyTest2) {
  ASSERT_EQ(stdMultisetTenElements.empty(), myMultisetTenElements.empty());

  std::multiset<int> multiset{};
  s21::multiset<int> myMultiset{};
  ASSERT_EQ(multiset.empty(), myMultiset.empty());
}

TEST_F(MultisetTest, ClearTest1) {
  stdMultisetTenElements.clear();
  myMultisetTenElements.clear();
  AssertContainerEquality(stdMultisetTenElements, myMultisetTenElements);
}

TEST_F(MultisetTest, ClearTest2) {
  std::multiset<int> multiset{};
  multiset.clear();
  s21::multiset<int> myMultiset{};
  myMultiset.clear();
  AssertContainerEquality(multiset, myMultiset);
}

TEST_F(MultisetTest, EraseBeginTest) {
  stdMultisetTenElements.erase(*stdMultisetTenElements.begin());
  myMultisetTenElements.erase(*myMultisetTenElements.begin());
  AssertContainerEquality(stdMultisetTenElements, myMultisetTenElements);
}

TEST_F(MultisetTest, EraseEndTest) {
  stdMultisetTenElements.erase(*std::prev(stdMultisetTenElements.end()));
  myMultisetTenElements.erase(*std::prev(myMultisetTenElements.end()));
  AssertContainerEquality(stdMultisetTenElements, myMultisetTenElements);
}

TEST_F(MultisetTest, EraseAllTest) {
  for (;;) {
    auto iter = myMultisetTenElements.begin();
    if (iter != std::prev(myMultisetTenElements.end())) {
      stdMultisetTenElements.erase(*iter);
      myMultisetTenElements.erase(*iter);
    } else {
      break;
    }
  }
  AssertContainerEquality(stdMultisetTenElements, myMultisetTenElements);
}

TEST_F(MultisetTest, InsertTest) {
  std::multiset<int> stdMultiset{};

  auto std_iter1 = stdMultiset.insert(123);
  auto std_iter2 = stdMultiset.insert(123);

  s21::multiset<int> myMultiset{};

  auto my_iter1 = myMultiset.insert(123);
  auto my_iter2 = myMultiset.insert(123);

  ASSERT_EQ(*std_iter1, *std_iter2);
  ASSERT_EQ(*my_iter1, *my_iter2);
  AssertContainerEquality(stdMultiset, myMultiset);
}

TEST_F(MultisetTest, InsertManyTest1) {
  s21::multiset<int> myMultiset{};
  myMultiset.insert_many(1, 2, 3, 4, 5);
  s21::multiset<int> resultMultiset{1, 2, 3, 4, 5};
  AssertContainerEquality(myMultiset, resultMultiset);
}

TEST_F(MultisetTest, InsertManyTest2) {
  myMultisetTenElements.insert_many();
  AssertContainerEquality(myMultisetTenElements, myMultisetTenElements);
}

TEST_F(MultisetTest, InsertManyTest3) {
  myMultisetTenElements.insert_many(5);
  s21::multiset<int> resultMultiset{5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  AssertContainerEquality(resultMultiset, myMultisetTenElements);
}

TEST_F(MultisetTest, InsertManyTest4) {
  myMultisetTenElements.insert_many(1, 2, 3, 4, 5, 6, 7, 8, 9, 5);
  s21::multiset<int> resultMultiset{1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                    1, 2, 3, 4, 5, 6, 7, 8, 9, 5};
  AssertContainerEquality(resultMultiset, myMultisetTenElements);
}

TEST_F(MultisetTest, MergeTest) {
  std::multiset<int> stdMultiset{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  s21::multiset<int> myMultiset{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  stdMultiset.merge(stdMultisetTenElements);
  myMultiset.merge(myMultisetTenElements);

  AssertContainerEquality(myMultiset, stdMultiset);
  AssertContainerEquality(stdMultisetTenElements, myMultisetTenElements);
}

TEST_F(MultisetTest, SwapTest) {
  s21::multiset<int> mySet1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::multiset<int> mySet1_copy = mySet1;
  s21::multiset<int> mySet2{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  s21::multiset<int> mySet2_copy = mySet2;
  mySet1.swap(mySet2);
  AssertContainerEquality(mySet1, mySet2_copy);
  AssertContainerEquality(mySet2, mySet1_copy);
}

TEST_F(MultisetTest, EqualRange1) {
  int find_data = 5;

  auto std_pair = stdMultisetTenElements.equal_range(find_data);

  auto my_pair = myMultisetTenElements.equal_range(find_data);

  ASSERT_EQ(*std_pair.first, *my_pair.first);
  ASSERT_EQ(*std_pair.second, *my_pair.second);

  AssertContainerEquality(stdMultisetTenElements, myMultisetTenElements);
}

TEST_F(MultisetTest, EqualRange2) {
  int find_data = -12;

  auto std_pair = stdMultisetTenElements.equal_range(find_data);

  auto my_pair = myMultisetTenElements.equal_range(find_data);

  ASSERT_EQ(*std_pair.first, *my_pair.first);
  ASSERT_EQ(*std_pair.second, *my_pair.second);

  AssertContainerEquality(stdMultisetTenElements, myMultisetTenElements);
}

TEST_F(MultisetTest, EqualRange3) {
  int find_data = 100;

  auto std_pair = stdMultisetTenElements.equal_range(find_data);

  auto my_pair = myMultisetTenElements.equal_range(find_data);

  std::cout << "\n";

  ASSERT_EQ(*std_pair.first, *my_pair.first);
  ASSERT_EQ(*std_pair.second, *my_pair.second);

  AssertContainerEquality(stdMultisetTenElements, myMultisetTenElements);
}
}  // namespace s21
