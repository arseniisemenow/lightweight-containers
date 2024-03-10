#include <gtest/gtest.h>

#include <set>
#include <type_traits>

#include "../src/associative/set/set.h"
#include "test_utils.h"

namespace s21 {
class SetTest : public ::testing::Test {
 protected:
  std::set<int> stdSetTenElements{};
  s21::set<int> mySetTenElements{};

  void SetUp() override {
    stdSetTenElements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    mySetTenElements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  }
};

TEST_F(SetTest, DefaultConstructorTest) {
  std::set<int> stdSet{};
  s21::set<int> mySet{};
  AssertContainerEquality(stdSet, mySet);
}

TEST_F(SetTest, ListConstructorTest) {
  std::set<int> stdSet{1, 2, 3, 4, 5, 4, 3, 2, 1};
  s21::set<int> mySet{1, 2, 3, 4, 5, 4, 3, 2, 1};
  AssertContainerEquality(stdSet, mySet);
}

TEST_F(SetTest, ListConstructorTest2) {
  std::set<std::string> stdSet{"Here", "is", "some", "random", "words"};
  s21::set<std::string> mySet{"Here", "is", "some", "random", "words"};
  AssertContainerEquality(stdSet, mySet);
}

/* copy constructor is deprecated for std::set c++17 */
TEST_F(SetTest, CopyConstructorTest) {
  std::set<int> stdSet{stdSetTenElements};
  s21::set<int> mySet{mySetTenElements};
  AssertContainerEquality(stdSet, stdSetTenElements);
  AssertContainerEquality(mySetTenElements, mySet);
}

TEST_F(SetTest, MoveConstructorTest)  // TODO it is not actually working correct
{
  std::set<int> stdSet{std::move(stdSetTenElements)};
  s21::set<int> mySet{std::move(mySetTenElements)};
  AssertContainerEquality(stdSet, mySet);
}

TEST_F(SetTest, CopyAssignmentOperator) {
  std::set<int> stdSet{};
  stdSet = stdSetTenElements;
  s21::set<int> mySet{};
  mySet = mySetTenElements;
  AssertContainerEquality(stdSet, mySet);
}

TEST_F(SetTest, MoveAssignmentOperator) {
  std::set<int> stdSet{};
  stdSet = std::move(stdSetTenElements);
  s21::set<int> mySet{};
  mySet = std::move(mySetTenElements);
  AssertContainerEquality(mySet, stdSet);
}
TEST_F(SetTest, ElementAccessOperatorTestBegin) {
  int stdElement{*stdSetTenElements.begin()};
  int myElement{*mySetTenElements.begin()};
  ASSERT_EQ(stdElement, myElement);
}

TEST_F(SetTest, ElementAccessOperatorTestEnd) {
  int stdElement{*std::prev(stdSetTenElements.end())};
  int myElement{*std::prev(mySetTenElements.end())};
  ASSERT_EQ(stdElement, myElement);
}
TEST_F(SetTest, EmptyTest1) {
  ASSERT_EQ(stdSetTenElements.empty(), mySetTenElements.empty());

  std::set<int> set{1};
  s21::set<int> mySet{1};
  ASSERT_EQ(set.empty(), mySet.empty());
}
TEST_F(SetTest, EmptyTest2) {
  ASSERT_EQ(stdSetTenElements.empty(), mySetTenElements.empty());

  std::set<int> set{};
  s21::set<int> mySet{};
  ASSERT_EQ(set.empty(), mySet.empty());
}
TEST_F(SetTest, ClearTest1) {
  stdSetTenElements.clear();
  mySetTenElements.clear();
  AssertContainerEquality(stdSetTenElements, mySetTenElements);
}

TEST_F(SetTest, ClearTest2) {
  std::set<int> set{};
  set.clear();
  s21::set<int> mySet{};
  mySet.clear();
  AssertContainerEquality(set, mySet);
}
TEST_F(SetTest, EraseBeginTest) {
  stdSetTenElements.erase(*stdSetTenElements.begin());
  mySetTenElements.erase(*mySetTenElements.begin());
  AssertContainerEquality(stdSetTenElements, mySetTenElements);
}

TEST_F(SetTest, EraseEndTest) {
  stdSetTenElements.erase(*std::prev(stdSetTenElements.end()));
  mySetTenElements.erase(*std::prev(mySetTenElements.end()));
  AssertContainerEquality(stdSetTenElements, mySetTenElements);
}

TEST_F(SetTest, EraseAllTest) {
  for (;;) {
    auto iter = mySetTenElements.begin();
    if (iter != std::prev(mySetTenElements.end())) {
      stdSetTenElements.erase(*iter);
      mySetTenElements.erase(*iter);
    } else {
      break;
    }
  }
  AssertContainerEquality(stdSetTenElements, mySetTenElements);
}

TEST_F(SetTest, InsertTest) {
  std::set<int> stdSet{};

  std::pair std_pair_success = stdSet.insert(123);
  std::pair std_pair_fail = stdSet.insert(123);

  s21::set<int> mySet{};

  std::pair s21_pair_success = mySet.insert(123);
  std::pair s21_pair_fail = mySet.insert(123);

  ASSERT_EQ(*std_pair_success.first, *s21_pair_success.first);
  ASSERT_EQ(std_pair_success.second, s21_pair_success.second);
  ASSERT_EQ(*std_pair_fail.first, *s21_pair_fail.first);
  ASSERT_EQ(std_pair_fail.second, s21_pair_fail.second);
  AssertContainerEquality(stdSet, mySet);
}

TEST_F(SetTest, InsertManyTest1) {
  s21::set<int> mySet{};
  mySet.insert_many(1, 2, 3, 4, 5);
  s21::set<int> resultSet{1, 2, 3, 4, 5};
  AssertContainerEquality(mySet, resultSet);
}

TEST_F(SetTest, InsertManyTest2) {
  mySetTenElements.insert_many();
  AssertContainerEquality(mySetTenElements, mySetTenElements);
}

TEST_F(SetTest, InsertManyTest3) {
  mySetTenElements.insert_many(5);
  s21::set<int> resultSet{5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  AssertContainerEquality(resultSet, mySetTenElements);
}
TEST_F(SetTest, InsertManyTest4) {
  mySetTenElements.insert_many(1, 2, 3, 4, 5, 6, 7, 8, 9, 5);
  s21::set<int> resultSet{1, 2, 3, 5, 4, 5, 6, 7, 8, 9, 10};
  AssertContainerEquality(resultSet, mySetTenElements);
}
TEST_F(SetTest, MergeTest) {
  std::set<int> stdSet{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  s21::set<int> mySet{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  stdSet.merge(stdSetTenElements);
  mySet.merge(mySetTenElements);
  AssertContainerEquality(mySet, stdSet);
}

TEST_F(SetTest, SwapTest) {
  s21::set<int> mySet1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::set<int> mySet1_copy = mySet1;
  s21::set<int> mySet2{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  s21::set<int> mySet2_copy = mySet2;
  mySet1.swap(mySet2);
  AssertContainerEquality(mySet1, mySet2_copy);
  AssertContainerEquality(mySet2, mySet1_copy);
}
}  // namespace s21
