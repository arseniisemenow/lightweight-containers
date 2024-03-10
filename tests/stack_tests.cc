#include <iterator>
#include <stack>

#include "../src/adaptors/stack/stack.h"
#include "test_utils.h"

namespace s21 {
class StackTest : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i{0}; i < 10; ++i) {
      stdStackTenElements.push(i + 1);
      myStackTenElements.push(i + 1);
    }
  }

  std::stack<int> stdStackTenElements{};
  s21::stack<int> myStackTenElements{};
};

TEST_F(StackTest, DefaultConstructorTest) {
  std::stack<int> stack{};
  s21::stack<int> myStack{};
  AssertStackEquality(stack, myStack);
}

TEST_F(StackTest, InitListConstructorTest) {
  std::stack<int> stack{};
  for (int i{0}; i < 5; ++i) {
    stack.push(i);
  }
  s21::stack<int> myStack{0, 1, 2, 3, 4};
  AssertStackEquality(stack, myStack);
}

TEST_F(StackTest, CopyConstructorTest) {
  std::stack<int> stack{stdStackTenElements};
  s21::stack<int> myStack{myStackTenElements};
  AssertStackEquality(stack, myStack);
}

TEST_F(StackTest, MoveConstructorTest) {
  std::stack<int> stack{std::move(stdStackTenElements)};
  s21::stack<int> myStack{std::move(myStackTenElements)};
  AssertStackEquality(stack, myStack);
}

TEST_F(StackTest, CopyAssignmentOperatorTest) {
  std::stack<int> stack{};
  s21::stack<int> myStack{};
  stack = stdStackTenElements;
  myStack = myStackTenElements;
  AssertStackEquality(stack, myStack);
}

TEST_F(StackTest, MoveAssignmentOperatorTest) {
  std::stack<int> stack{};
  s21::stack<int> myStack{};
  stack = std::move(stdStackTenElements);
  myStack = std::move(myStackTenElements);
  AssertStackEquality(stack, myStack);
}

TEST_F(StackTest, TopTest) {
  ASSERT_EQ(stdStackTenElements.top(), myStackTenElements.top());
}

TEST_F(StackTest, EmptyTest) {
  std::stack<int> stack{};
  s21::stack<int> myStack{};
  ASSERT_EQ(stack.empty(), myStack.empty());
  ASSERT_EQ(stdStackTenElements.empty(), myStackTenElements.empty());
}

TEST_F(StackTest, SizeTest) {
  std::stack<int> stack{};
  s21::stack<int> myStack{};
  ASSERT_EQ(stack.size(), myStack.size());
  ASSERT_EQ(stdStackTenElements.size(), myStackTenElements.size());
}

TEST_F(StackTest, PushTest1) {
  std::stack<int> stack{};
  stack.push(1);
  s21::stack<int> myStack{};
  myStack.push(1);
  AssertStackEquality(stack, myStack);
}

TEST_F(StackTest, PushTest2) {
  std::stack<int> stack{};
  s21::stack<int> myStack{};
  for (int i{0}; i < 15; ++i) {
    stack.push(i * i);
    myStack.push(i * i);
  }
  AssertStackEquality(stack, myStack);
}

TEST_F(StackTest, PopTest) {
  stdStackTenElements.pop();
  myStackTenElements.pop();
  AssertStackEquality(stdStackTenElements, myStackTenElements);
}

TEST_F(StackTest, SwapTest) {
  std::stack<int> stack{};
  stack.push(1);
  s21::stack<int> myStack{};
  myStack.push(1);

  stdStackTenElements.swap(stack);
  myStackTenElements.swap(myStack);
  AssertStackEquality(stdStackTenElements, myStackTenElements);
  AssertStackEquality(stack, myStack);
}

TEST_F(StackTest, InsertManyFrontTest) {
  s21::stack<int> stack{};
  stack.insert_many_front(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  AssertStackEquality(stdStackTenElements, stack);
}
}  // namespace s21
