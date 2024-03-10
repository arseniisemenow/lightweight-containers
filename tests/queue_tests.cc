#include <iterator>
#include <queue>

#include "../src/adaptors/queue/queue.h"
#include "test_utils.h"

namespace s21 {
class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i{0}; i < 10; ++i) {
      stdQueueTenElements.push(i + 1);
      myQueueTenElements.push(i + 1);
    }
  }

  std::queue<int> stdQueueTenElements{};
  s21::queue<int> myQueueTenElements{};
};

TEST_F(QueueTest, DefaultConstructorTest) {
  std::cout << "in default constructor test\n";
  std::queue<int> queue{};
  s21::queue<int> myQueue{};
  AssertQueueEquality(queue, myQueue);
}

TEST_F(QueueTest, InitListConstructorTest) {
  std::queue<int> queue{};
  for (int i{1}; i < 6; ++i) {
    queue.push(i);
  }

  s21::queue<int> myQueue{1, 2, 3, 4, 5};
  AssertQueueEquality(queue, myQueue);
}

TEST_F(QueueTest, CopyConstructorTest) {
  std::queue<int> queue{stdQueueTenElements};
  s21::queue<int> myQueue{myQueueTenElements};
  AssertQueueEquality(queue, myQueue);
}

TEST_F(QueueTest, MoveConstructorTest) {
  std::queue<int> queue{std::move(stdQueueTenElements)};
  s21::queue<int> myQueue{std::move(myQueueTenElements)};
  AssertQueueEquality(queue, myQueue);
}

TEST_F(QueueTest, CopyAssignmentOperatorTest) {
  std::queue<int> queue{};
  s21::queue<int> myQueue{};
  queue = stdQueueTenElements;
  myQueue = myQueueTenElements;
  AssertQueueEquality(queue, myQueue);
}

TEST_F(QueueTest, MoveAssignmentOperatorTest) {
  std::queue<int> queue{};
  s21::queue<int> myQueue{};
  queue = std::move(stdQueueTenElements);
  myQueue = std::move(myQueueTenElements);
  AssertQueueEquality(queue, myQueue);
}

TEST_F(QueueTest, FrontTest) {
  ASSERT_EQ(stdQueueTenElements.front(), myQueueTenElements.front());
}

TEST_F(QueueTest, BackTest) {
  ASSERT_EQ(stdQueueTenElements.back(), myQueueTenElements.back());
}

TEST_F(QueueTest, EmptyTest) {
  std::queue<int> queue{};
  s21::queue<int> myQueue{};
  ASSERT_EQ(queue.empty(), myQueue.empty());
  ASSERT_EQ(stdQueueTenElements.empty(), myQueueTenElements.empty());
}

TEST_F(QueueTest, SizeTest) {
  std::queue<int> queue{};
  s21::queue<int> myQueue{};
  ASSERT_EQ(queue.size(), myQueue.size());
  ASSERT_EQ(stdQueueTenElements.size(), myQueueTenElements.size());
}

TEST_F(QueueTest, PushTest1) {
  std::queue<int> queue{};
  queue.push(5);
  s21::queue<int> myQueue{};
  myQueue.push(5);
  AssertQueueEquality(queue, myQueue);
}

TEST_F(QueueTest, PushTest2) {
  std::queue<int> queue{};
  s21::queue<int> myQueue{};
  for (int i{0}; i < 10; ++i) {
    queue.push(i * i);
    myQueue.push(i * i);
  }
  AssertQueueEquality(queue, myQueue);
}

TEST_F(QueueTest, PopTest1) {
  std::queue<int> queue{};
  queue.push(5);
  s21::queue<int> myQueue{};
  myQueue.push(5);
  queue.pop();
  myQueue.pop();
  AssertQueueEquality(queue, myQueue);
}

TEST_F(QueueTest, PopTest2) {
  stdQueueTenElements.pop();
  myQueueTenElements.pop();
  AssertQueueEquality(stdQueueTenElements, myQueueTenElements);
}

TEST_F(QueueTest, SwapTest) {
  std::queue<int> queue{};
  queue.push(1);
  s21::queue<int> myQueue{};
  myQueue.push(1);

  stdQueueTenElements.swap(queue);
  myQueueTenElements.swap(myQueue);
  AssertQueueEquality(stdQueueTenElements, myQueueTenElements);
  AssertQueueEquality(queue, myQueue);
}

TEST_F(QueueTest, InsertManyBackTest) {
  s21::queue<int> queue{};
  queue.insert_many_back(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  AssertQueueEquality(stdQueueTenElements, myQueueTenElements);
}
}  // namespace s21
