#ifndef CPP2_S21_CONTAINERS_1_ASSOCIATIVE_RED_BLACK_TREE_NODE_H_
#define CPP2_S21_CONTAINERS_1_ASSOCIATIVE_RED_BLACK_TREE_NODE_H_

enum class Color {
  kNone = 0,
  kRed = 1 << 0,
  kBlack = 1 << 1,
};

template <typename T>
struct Node {
  T data_;
  Color color_;
  Node *parent_;
  Node *left_;
  Node *right_;

  explicit Node(const T &data)
      : data_(data),
        color_(Color::kRed),
        parent_(nullptr),
        left_(nullptr),
        right_(nullptr){};

  Node()
      : color_(Color::kBlack),
        parent_(nullptr),
        left_(nullptr),
        right_(nullptr){};

  ~Node() = default;
};

#endif  // CPP2_S21_CONTAINERS_1_ASSOCIATIVE_RED_BLACK_TREE_NODE_H_