#include <gtest/gtest.h>

#include <map>
#include <type_traits>

#include "../src/associative/map/map.h"
#include "test_utils.h"

namespace s21 {
class MapTest : public ::testing::Test {
 protected:
  void SetUp() override {
    stdMapTenElements = {{0, 2 << 0}, {1, 2 << 1}, {2, 2 << 2},  {3, 2 << 3},
                         {4, 2 << 4}, {5, 2 << 5}, {6, 2 << 6},  {7, 2 << 7},
                         {8, 2 << 8}, {9, 2 << 9}, {10, 2 << 10}};
    myMapTenElements = {{0, 2 << 0}, {1, 2 << 1}, {2, 2 << 2},  {3, 2 << 3},
                        {4, 2 << 4}, {5, 2 << 5}, {6, 2 << 6},  {7, 2 << 7},
                        {8, 2 << 8}, {9, 2 << 9}, {10, 2 << 10}};
  }

  std::map<int, int> stdMapTenElements{};
  s21::map<int, int> myMapTenElements{};
};

TEST_F(MapTest, DefaultConstructorTest) {
  std::map<int, int> stdMap{};
  s21::map<int, int> myMap{};
  AssertContainerEquality(stdMap, myMap);
}

TEST_F(MapTest, ListConstructorTest) {
  std::map<int, int> stdMap{{0, 2 << 0}, {1, 2 << 1}, {2, 2 << 2},  {3, 2 << 3},
                            {4, 2 << 4}, {5, 2 << 5}, {6, 2 << 6},  {7, 2 << 7},
                            {8, 2 << 8}, {9, 2 << 9}, {10, 2 << 10}};
  s21::map<int, int> myMap{{0, 2 << 0}, {1, 2 << 1}, {2, 2 << 2},  {3, 2 << 3},
                           {4, 2 << 4}, {5, 2 << 5}, {6, 2 << 6},  {7, 2 << 7},
                           {8, 2 << 8}, {9, 2 << 9}, {10, 2 << 10}};
  AssertContainerEquality(stdMap, myMap);
}

TEST_F(MapTest, CopyConstructorTest) {
  std::map<int, int> stdMap{stdMapTenElements};
  s21::map<int, int> myMap{myMapTenElements};
  AssertContainerEquality(stdMap, stdMapTenElements);
  AssertContainerEquality(myMapTenElements, myMap);
}

TEST_F(MapTest, MoveConstructorTest) {
  std::map<int, int> stdEmptyMap{};
  std::map<int, int> stdMap{std::move(stdMapTenElements)};

  s21::map<int, int> myEmptyMap{};
  s21::map<int, int> myMap{std::move(myMapTenElements)};

  AssertContainerEquality(stdMap, myMap);
  AssertContainerEquality(stdMapTenElements, stdEmptyMap);
  AssertContainerEquality(myMapTenElements, myEmptyMap);
}

TEST_F(MapTest, CopyAssignmentOperator) {
  std::map<int, int> stdMap{};
  stdMap = stdMapTenElements;
  s21::map<int, int> myMap{};
  myMap = myMapTenElements;
  AssertContainerEquality(stdMap, myMap);
}

TEST_F(MapTest, MoveAssignmentOperator) {
  std::map<int, int> stdMap{};
  stdMap = std::move(stdMapTenElements);
  s21::map<int, int> myMap{};
  myMap = std::move(myMapTenElements);
  AssertContainerEquality(myMap, stdMap);
}

TEST_F(MapTest, ElementAccessOperatorTestBegin) {
  auto stdElement{*stdMapTenElements.begin()};
  auto myElement{*myMapTenElements.begin()};
  ASSERT_EQ(stdElement.first, myElement.first);
  ASSERT_EQ(stdElement.second, myElement.second);
}

TEST_F(MapTest, ElementAccessOperatorTestEnd) {
  auto stdElement{*std::prev(stdMapTenElements.end())};
  auto myElement{*std::prev(myMapTenElements.end())};
  ASSERT_EQ(stdElement.first, myElement.first);
  ASSERT_EQ(stdElement.second, myElement.second);
}

TEST_F(MapTest, EmptyTest1) {
  ASSERT_EQ(stdMapTenElements.empty(), myMapTenElements.empty());
  std::map<int, int> map{{1, 1}};
  s21::map<int, int> myMap{{1, 1}};
  ASSERT_EQ(map.empty(), myMap.empty());
}

TEST_F(MapTest, EmptyTest2) {
  ASSERT_EQ(stdMapTenElements.empty(), myMapTenElements.empty());

  std::map<int, int> map{};
  s21::map<int, int> myMap{};
  ASSERT_EQ(map.empty(), myMap.empty());
}

TEST_F(MapTest, ClearTest1) {
  stdMapTenElements.clear();
  myMapTenElements.clear();
  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, ClearTest2) {
  std::map<int, int> map{};
  map.clear();
  s21::map<int, int> myMap{};
  myMap.clear();
  AssertContainerEquality(map, myMap);
}

TEST_F(MapTest, EraseBeginTest) {
  stdMapTenElements.erase(stdMapTenElements.begin());
  myMapTenElements.erase(myMapTenElements.begin());
  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, EraseBeginByKeyTest) {
  stdMapTenElements.erase(stdMapTenElements.begin()->first);
  myMapTenElements.erase(myMapTenElements.begin()->first);
  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, EraseEndTest) {
  stdMapTenElements.erase(std::prev(stdMapTenElements.end()));
  myMapTenElements.erase(std::prev(myMapTenElements.end()));
  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, EraseEndByKeyTest) {
  stdMapTenElements.erase((*std::prev(stdMapTenElements.end())).first);
  myMapTenElements.erase((*std::prev(myMapTenElements.end())).first);
  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, EraseAllTest) {  // TODO Ask for this
  for (;;) {
    auto std_iter = stdMapTenElements.begin();
    auto my_iter = myMapTenElements.begin();
    if (std_iter != std::prev(stdMapTenElements.end())) {
      stdMapTenElements.erase((*std_iter).first);
      myMapTenElements.erase((*my_iter).first);
    } else {
      break;
    }
  }
  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, InsertTest) {
  std::map<int, int> stdMap{};

  std::pair pair{50, 50};
  auto std_iter1 = stdMap.insert(pair);
  auto std_iter2 = stdMap.insert(pair);

  s21::map<int, int> myMap{};

  auto my_iter1 = myMap.insert(pair);
  auto my_iter2 = myMap.insert(pair);

  ASSERT_EQ(*(std_iter1.first), *(my_iter1.first));
  ASSERT_EQ(std_iter1.second, my_iter1.second);
  ASSERT_EQ(*(std_iter2.first), *(my_iter2.first));
  ASSERT_EQ(std_iter2.second, my_iter2.second);
  AssertContainerEquality(stdMap, myMap);
}
TEST_F(MapTest, InsertOrAssignTest) {
  std::map<int, int> stdMap{};

  std::pair pair{50, 50};
  auto std_iter1 = stdMap.insert_or_assign(pair.first, pair.second);
  auto std_iter2 = stdMap.insert_or_assign(pair.first, pair.second);

  s21::map<int, int> myMap{};

  auto my_iter1 = myMap.insert_or_assign(pair.first, pair.second);
  auto my_iter2 = myMap.insert_or_assign(pair.first, pair.second);

  ASSERT_EQ(*(std_iter1.first), *(my_iter1.first));
  ASSERT_EQ(std_iter1.second, my_iter1.second);
  ASSERT_EQ(*(std_iter2.first), *(my_iter2.first));
  ASSERT_EQ(std_iter2.second, my_iter2.second);
  AssertContainerEquality(stdMap, myMap);
}

TEST_F(MapTest, InsertByElementsTest) {
  std::map<int, int> stdMap{};

  int first_value = 50;
  int second_value = 100;

  std::pair pair{first_value, second_value};

  auto std_iter1 = stdMap.insert(pair);
  auto std_iter2 = stdMap.insert(pair);

  s21::map<int, int> myMap{};

  auto my_iter1 = myMap.insert(first_value, second_value);
  auto my_iter2 = myMap.insert(first_value, second_value);

  ASSERT_EQ(*(std_iter1.first), *(my_iter1.first));
  ASSERT_EQ(std_iter1.second, my_iter1.second);
  ASSERT_EQ(*(std_iter2.first), *(my_iter2.first));
  ASSERT_EQ(std_iter2.second, my_iter2.second);
  AssertContainerEquality(stdMap, myMap);
}

TEST_F(MapTest, InsertManyTest1) {
  s21::map<int, int> myMap{};
  s21::map<int, int> myTestMap{};
  std::pair pair1{100, 100};
  std::pair pair2{200, 200};
  std::pair pair3{300, 300};
  std::pair pair4{400, 400};
  std::pair pair5{500, 500};
  std::pair pair6{600, 600};
  std::pair pair7{700, 700};
  std::pair pair8{800, 800};
  auto vector =
      myMap.insert_many(pair1, pair2, pair3, pair4, pair5, pair6, pair7, pair8);
  auto stdIter0 = myTestMap.insert(pair1);
  auto stdIter1 = myTestMap.insert(pair2);
  auto stdIter2 = myTestMap.insert(pair3);
  auto stdIter3 = myTestMap.insert(pair4);
  auto stdIter4 = myTestMap.insert(pair5);
  auto stdIter5 = myTestMap.insert(pair6);
  auto stdIter6 = myTestMap.insert(pair7);
  auto stdIter7 = myTestMap.insert(pair8);
  ASSERT_EQ(*vector[0].first, *stdIter0.first);
  ASSERT_EQ(vector[0].second, stdIter0.second);
  ASSERT_EQ(*vector[1].first, *stdIter1.first);
  ASSERT_EQ(vector[1].second, stdIter1.second);
  ASSERT_EQ(*vector[2].first, *stdIter2.first);
  ASSERT_EQ(vector[2].second, stdIter2.second);
  ASSERT_EQ(*vector[3].first, *stdIter3.first);
  ASSERT_EQ(vector[3].second, stdIter3.second);
  ASSERT_EQ(*vector[4].first, *stdIter4.first);
  ASSERT_EQ(vector[4].second, stdIter4.second);
  ASSERT_EQ(*vector[5].first, *stdIter5.first);
  ASSERT_EQ(vector[5].second, stdIter5.second);
  ASSERT_EQ(*vector[6].first, *stdIter6.first);
  ASSERT_EQ(vector[6].second, stdIter6.second);
  ASSERT_EQ(*vector[7].first, *stdIter7.first);
  ASSERT_EQ(vector[7].second, stdIter7.second);

  AssertContainerEquality(myMap, myTestMap);
}

TEST_F(MapTest, InsertManyTest2) {
  myMapTenElements.insert_many();
  AssertContainerEquality(myMapTenElements, myMapTenElements);
}

TEST_F(MapTest, MergeTest1) {
  std::map<int, int> stdMap{{1, 2}};
  s21::map<int, int> myMap{{1, 2}};
  stdMap.merge(stdMapTenElements);
  myMap.merge(myMapTenElements);

  AssertContainerEquality(stdMap, myMap);
  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}
/* Negative values in key for some reason segfaults in GTest sin std map and
 * mine Trying to merge maps
 * */
TEST_F(MapTest, MergeTest2) {
  std::map<int, int> stdMap{{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}};
  s21::map<int, int> myMap{{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}};
  stdMap.merge(stdMapTenElements);
  myMap.merge(myMapTenElements);

  AssertContainerEquality(stdMap, myMap);
  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, SwapTest) {
  s21::map<int, int> mySet1{{-1, 2}, {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}};
  s21::map<int, int> mySet1_copy = mySet1;
  s21::map<int, int> mySet2{{-10, 2}, {00, 2}, {10, 2},
                            {20, 2},  {30, 2}, {40, 2}};
  s21::map<int, int> mySet2_copy = mySet2;
  mySet1.swap(mySet2);
  AssertContainerEquality(mySet1, mySet2_copy);
  AssertContainerEquality(mySet2, mySet1_copy);
}

TEST_F(MapTest, EqualRange1) {
  int find_data = 5;

  auto std_pair = stdMapTenElements.equal_range(find_data);

  auto my_pair = myMapTenElements.equal_range(find_data);

  ASSERT_EQ(*std_pair.first, *my_pair.first);
  ASSERT_EQ(*std_pair.second, *my_pair.second);

  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, EqualRange2) {
  int find_data = -12;

  auto std_pair = stdMapTenElements.equal_range(find_data);

  auto my_pair = myMapTenElements.equal_range(find_data);

  ASSERT_EQ(*std_pair.first, *my_pair.first);
  ASSERT_EQ(*std_pair.second, *my_pair.second);

  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

///* Firstly wanted to set find_data bigger then maximum key value in the tree,
// * but I don't understand why original equal_range returns
// * minimal node of right child of root in case when it finds no suitable node.
// * That's wierd, so I will have my implementation here */
//    TEST_F(MapTest, EqualRange3) {
//        int find_data = 9; /* Supposed to set bigger value here,
// * If set upper bound value and bigger, it will work not like original one*/
//
//        auto std_pair = stdMapTenElements.equal_range(find_data);
//
//        auto my_pair = myMapTenElements.equal_range(find_data);
//
//        std::cout << "\n";
//
//        ASSERT_EQ(*std_pair.first, *my_pair.first);
//        ASSERT_EQ(*std_pair.second, *my_pair.second);
//
//        AssertContainerEquality(stdMapTenElements, myMapTenElements);
//    }

TEST_F(MapTest, AtExistedKeyAccessor) {
  int find_data = 9;

  auto std_result = stdMapTenElements.at(find_data);

  auto my_result = myMapTenElements.at(find_data);

  ASSERT_EQ(std_result, my_result);

  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, AtExistedKeyMutator) {
  int find_data = 9;
  int mutator_value = 999;
  auto std_result = stdMapTenElements.at(find_data);
  auto my_result = myMapTenElements.at(find_data);

  ASSERT_EQ(std_result, my_result);
  AssertContainerEquality(stdMapTenElements, myMapTenElements);

  stdMapTenElements.at(find_data) = mutator_value;
  myMapTenElements.at(find_data) = mutator_value;

  std_result = stdMapTenElements.at(find_data);
  my_result = myMapTenElements.at(find_data);

  ASSERT_EQ(std_result, my_result);
  ASSERT_EQ(std_result, mutator_value);

  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, AtNotExistedKey) {
  int find_data = 100;

  EXPECT_THROW(stdMapTenElements.at(find_data), std::out_of_range);
  EXPECT_THROW(myMapTenElements.at(find_data), std::out_of_range);

  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, SubscriptAccessorTest) {
  int find_data = 100;

  ASSERT_EQ(stdMapTenElements[find_data], myMapTenElements[find_data]);

  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, SubscriptAccessorMutatorTest) {
  int find_data = 100;
  int change_value = 999;

  ASSERT_EQ(stdMapTenElements[find_data], myMapTenElements[find_data]);
  stdMapTenElements[find_data] = change_value;
  myMapTenElements[find_data] = change_value;
  ASSERT_EQ(stdMapTenElements[find_data], change_value);
  ASSERT_EQ(myMapTenElements[find_data], change_value);

  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}
/* Can't call contains method from standard library, because it says
 * It will work only on 17+ C library version
 * */
TEST_F(MapTest, ContainsExistTest) {
  int find_data = 1;

  ASSERT_EQ(myMapTenElements.contains(find_data), true);

  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, ContainsNonExistTest) {
  int find_data = 100;

  ASSERT_EQ(myMapTenElements.contains(find_data), false);

  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, SizeTest) {
  ASSERT_EQ(stdMapTenElements.size(), myMapTenElements.size());
  stdMapTenElements.insert({1, 2});
  myMapTenElements.insert({1, 2});
  ASSERT_EQ(stdMapTenElements.size(), myMapTenElements.size());
  stdMapTenElements.insert({1, 2});
  myMapTenElements.insert({1, 2});
  ASSERT_EQ(stdMapTenElements.size(), myMapTenElements.size());
  stdMapTenElements.insert({123, 2});
  myMapTenElements.insert({123, 2});
  ASSERT_EQ(stdMapTenElements.size(), myMapTenElements.size());
  stdMapTenElements.insert({123, 2});
  myMapTenElements.insert({123, 2});
  ASSERT_EQ(stdMapTenElements.size(), myMapTenElements.size());
  stdMapTenElements.insert({-9, 2});
  myMapTenElements.insert({-9, 2});
  ASSERT_EQ(stdMapTenElements.size(), myMapTenElements.size());
  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, MaxSizeTest) {
  bool std_flag = stdMapTenElements.max_size() > 0;
  bool my_flag = myMapTenElements.max_size() > 0;
  ASSERT_EQ(std_flag, my_flag);

  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}

TEST_F(MapTest, EmptyTest) {
  std::map<const int, const int> stdMap{};
  s21::map<const int, const int> myMap{};
  ASSERT_EQ(stdMapTenElements.empty(), myMapTenElements.empty());
  ASSERT_EQ(stdMap.empty(), myMap.empty());

  AssertContainerEquality(stdMapTenElements, myMapTenElements);
}
}  // namespace s21