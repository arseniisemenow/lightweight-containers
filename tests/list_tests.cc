#include <iterator>
#include <list>

#include "../src/sequence/list/list.h"
#include "test_utils.h"

namespace s21 {
class ListTest : public ::testing::Test {
 protected:
  void SetUp() override {
    stdListTenElements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    myListTenElements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  }

  std::list<int> stdListTenElements{};
  s21::list<int> myListTenElements{};
};

TEST_F(ListTest, DefaultConstructorTest) {
  std::list<int> list{};
  s21::list<int> myList{};
  AssertContainerEquality(list, myList);
}

TEST_F(ListTest, SizeConstructorTest) {
  std::list<int> list(50);
  s21::list<int> myList(50);
  AssertContainerEquality(list, myList);
}

TEST_F(ListTest, InitListConstructorTest) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> myList{1, 2, 3, 4, 5};
  AssertContainerEquality(list, myList);
}

TEST_F(ListTest, CopyConstructorTest) {
  std::list<int> list{stdListTenElements};
  s21::list<int> myList{myListTenElements};
  AssertContainerEquality(list, myList);
}

TEST_F(ListTest, MoveConstructorTest) {
  std::list<int> list{std::move(stdListTenElements)};
  s21::list<int> myList{std::move(myListTenElements)};
  AssertContainerEquality(list, myList);
}

TEST_F(ListTest, CopyAssignmentTest) {
  std::list<int> list{};
  list = stdListTenElements;
  s21::list<int> myList{};
  myList = myListTenElements;
  AssertContainerEquality(list, myList);
}

TEST_F(ListTest, MoveAssignmentTest) {
  std::list<int> list{};
  list = std::move(stdListTenElements);
  s21::list<int> myList{};
  myList = std::move(myListTenElements);
  AssertContainerEquality(list, myList);
}

TEST_F(ListTest, FrontTest) {
  int stdFront{stdListTenElements.front()};
  int myFront{stdListTenElements.front()};
  ASSERT_EQ(stdFront, myFront);
}

TEST_F(ListTest, BackTest) {
  int stdFront{stdListTenElements.back()};
  int myFront{stdListTenElements.back()};
  ASSERT_EQ(stdFront, myFront);
}

TEST_F(ListTest, IteratorBeginTest) {
  ASSERT_EQ(*stdListTenElements.begin(), *myListTenElements.begin());
  ASSERT_EQ(*stdListTenElements.cbegin(), *myListTenElements.cbegin());
}

TEST_F(ListTest, IteratorEndTest) {
  ASSERT_EQ(*std::prev(stdListTenElements.end()),
            *std::prev(myListTenElements.end()));
  ASSERT_EQ(*std::prev(stdListTenElements.cend()),
            *std::prev(myListTenElements.cend()));
}

TEST_F(ListTest, EmptyTest) {
  std::list<int> list{};
  s21::list<int> myList{};
  ASSERT_EQ(list.empty(), myList.empty());
  ASSERT_EQ(stdListTenElements.empty(), myListTenElements.empty());
}

TEST_F(ListTest, SizeTest) {
  std::list<int> list{};
  s21::list<int> myList{};
  ASSERT_EQ(list.size(), myList.size());
  ASSERT_EQ(stdListTenElements.size(), myListTenElements.size());
}

TEST_F(ListTest, MaxSizeTest) {
  std::list<int> list{};
  s21::list<int> myList{};
  ASSERT_EQ(list.max_size(), myList.max_size());
  ASSERT_EQ(stdListTenElements.max_size(), myListTenElements.max_size());
}

TEST_F(ListTest, ClearTest) {
  std::list<int> list{};
  list.clear();
  s21::list<int> myList{};
  myList.clear();
  AssertContainerEquality(list, myList);

  stdListTenElements.clear();
  myListTenElements.clear();
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, InsertAtBeginTest) {
  auto stdIter = stdListTenElements.insert(stdListTenElements.begin(), 5);
  auto iter = myListTenElements.insert(myListTenElements.begin(), 5);
  ASSERT_EQ(*stdIter, *iter);
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, InsertAtMiddleTest) {
  auto stdIter =
      stdListTenElements.insert(std::next(stdListTenElements.begin(), 4), 5);
  auto iter =
      myListTenElements.insert(std::next(myListTenElements.begin(), 4), 5);
  ASSERT_EQ(*stdIter, *iter);
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, InsertAtEndTest) {
  stdListTenElements.insert(stdListTenElements.end(), 5);
  myListTenElements.insert(myListTenElements.end(), 5);
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, EraseAtBeginTest) {
  stdListTenElements.erase(stdListTenElements.begin());
  myListTenElements.erase(myListTenElements.begin());
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, EraseAtMiddleTest) {
  stdListTenElements.erase(std::next(stdListTenElements.begin(), 4));
  myListTenElements.erase(std::next(myListTenElements.begin(), 4));
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, EraseAtEndTest) {
  stdListTenElements.erase(std::prev(stdListTenElements.end()));
  myListTenElements.erase(std::prev(myListTenElements.end()));
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, PushBackTest) {
  stdListTenElements.push_back(5);
  myListTenElements.push_back(5);
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, PopBackTest) {
  stdListTenElements.pop_back();
  myListTenElements.pop_back();
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, PushFrontTest) {
  stdListTenElements.push_front(5);
  myListTenElements.push_front(5);
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, PopFrontTest) {
  stdListTenElements.pop_front();
  myListTenElements.pop_front();
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, SwapTest) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> myList{1, 2, 3, 4, 5};
  list.swap(stdListTenElements);
  myList.swap(myListTenElements);
  AssertContainerEquality(stdListTenElements, myListTenElements);
  AssertContainerEquality(list, myList);
}

TEST_F(ListTest, MergeTest1) {
  std::list<int> list1{1, 2, 4};
  std::list<int> list2{5, 6, 7, 8};
  list1.merge(list2);

  s21::list<int> myList1{1, 2, 4};
  s21::list<int> myList2{5, 6, 7, 8};
  myList1.merge(myList2);

  AssertContainerEquality(list1, myList1);
  AssertContainerEquality(list2, myList2);
}

TEST_F(ListTest, MergeTest2) {
  std::list<int> list1{1, 3, 3, 5};
  std::list<int> list2{2, 3, 4, 4, 7, 8};
  list1.merge(list2);

  s21::list<int> myList1{1, 3, 3, 5};
  s21::list<int> myList2{2, 3, 4, 4, 7, 8};
  myList1.merge(myList2);

  AssertContainerEquality(list1, myList1);
  AssertContainerEquality(list2, myList2);
}

TEST_F(ListTest, SpliceAtBeginTest) {
  std::list<int> list{1, 2, 3, 4, 5};
  list.splice(list.begin(), stdListTenElements);

  s21::list<int> myList{1, 2, 3, 4, 5};
  myList.splice(myList.begin(), myListTenElements);
}

TEST_F(ListTest, SpliceAtMiddleTest) {
  std::list<int> list{1, 2, 3, 4, 5};
  list.splice(std::next(list.begin(), 3), stdListTenElements);

  s21::list<int> myList{1, 2, 3, 4, 5};
  myList.splice(std::next(myList.begin(), 3), myListTenElements);
}

TEST_F(ListTest, SpliceAtEndTest) {
  std::list<int> list{1, 2, 3, 4, 5};
  list.splice(list.end(), stdListTenElements);

  s21::list<int> myList{1, 2, 3, 4, 5};
  myList.splice(myList.end(), myListTenElements);
}

TEST_F(ListTest, ReverseTest) {
  stdListTenElements.reverse();
  myListTenElements.reverse();
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, UniqueTest) {
  std::list<int> list{1, 1, 2, 2, 3, 4, 5, 5, 5, 8, 3, 2, 9, 9, 8, 8};
  list.unique();
  s21::list<int> myList{1, 1, 2, 2, 3, 4, 5, 5, 5, 8, 3, 2, 9, 9, 8, 8};
  myList.unique();
  AssertContainerEquality(list, myList);

  myListTenElements.unique();
  stdListTenElements.unique();
  AssertContainerEquality(myListTenElements, stdListTenElements);
}

TEST_F(ListTest, SortTest1) {
  stdListTenElements.sort();
  myListTenElements.sort();
  AssertContainerEquality(stdListTenElements, myListTenElements);
}

TEST_F(ListTest, SortTest2) {
  std::list<int> list{6, 5, 4, 3, 2};
  list.sort();
  s21::list<int> myList{6, 5, 4, 3, 2};
  myList.sort();
  AssertContainerEquality(list, myList);
}

TEST_F(ListTest, SortTest3) {
  std::list<int> list{5, 3, 2, 6, 111, 35324, 2};
  list.sort();
  s21::list<int> myList{5, 3, 2, 6, 111, 35324, 2};
  myList.sort();
  AssertContainerEquality(list, myList);
}

TEST_F(ListTest, InsertManyAtBeginTest) {
  auto iter = myListTenElements.insert_many(myListTenElements.begin(), 5, 6, 7);
  s21::list<int> result{5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(*iter, 5);
  AssertContainerEquality(myListTenElements, result);
}

TEST_F(ListTest, InsertManyAtMiddleTest) {
  auto iter = myListTenElements.insert_many(
      std::next(myListTenElements.begin(), 4), 5, 6, 7);
  s21::list<int> result{1, 2, 3, 4, 5, 6, 7, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(*iter, 5);
  AssertContainerEquality(myListTenElements, result);
}

TEST_F(ListTest, InsertManyAtEndTest) {
  auto iter = myListTenElements.insert_many(myListTenElements.end(), 5, 6, 7);
  s21::list<int> result{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 5, 6, 7};
  ASSERT_EQ(*iter, 5);
  AssertContainerEquality(myListTenElements, result);
}

TEST_F(ListTest, InsertManyFrontTest) {
  myListTenElements.insert_many_front(5, 6, 7);
  s21::list<int> result{5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  AssertContainerEquality(myListTenElements, result);
}

TEST_F(ListTest, InsertManyBackTest) {
  myListTenElements.insert_many_back(5, 6, 7);
  s21::list<int> result{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 5, 6, 7};
  AssertContainerEquality(myListTenElements, result);
}
}  // namespace s21
