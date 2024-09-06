#include "test_header.h"

template <class T>
bool checkEqQ(s21::queue<T> a, std::queue<T> b) {
  if (a.size() != b.size()) return false;
  if (a.empty() != b.empty()) return false;
  if (a.empty()) return true;
  for (size_t i = 0; i < a.size(); i++) {
    if (a.front() != b.front()) return false;
    a.pop();
    b.pop();
  }
  return true;
}

TEST(Init, EmptyIntQ) {
  s21::queue<int> a;
  std::queue<int> b;
  ASSERT_EQ(true, checkEqQ(a, b));
}
TEST(Init, EmptyVecQ) {
  s21::queue<std::vector<int>> a;
  std::queue<std::vector<int>> b;
  ASSERT_EQ(true, checkEqQ(a, b));
}
TEST(Init, SeriasIQ) {
  s21::queue<int> a({1, 2, 3, 4});
  std::queue<int> b({1, 2, 3, 4});
  ASSERT_EQ(true, checkEqQ(a, b));
}
TEST(Init, SeriasDQ) {
  s21::queue<double> a({1, 2, 3, 4});
  std::queue<double> b({4, 3, 2, 1});
  ASSERT_EQ(false, checkEqQ(a, b));
}
TEST(Init, queueCopyQ) {
  s21::queue<int> a({1, 2, 3, 4});
  std::queue<int> b({1, 2, 3, 4});

  s21::queue<int> c(a);
  std::queue<int> d(b);
  ASSERT_EQ(true, checkEqQ(c, d));
}
TEST(Init, queueMoveQ) {
  s21::queue<int> a({1, 2, 3, 4});
  std::queue<int> b({1, 2, 3, 4});

  s21::queue<int> c(std::move(a));
  std::queue<int> d(std::move(b));
  ASSERT_EQ(true, checkEqQ(c, d));
}
TEST(Operator, moveQ) {
  s21::queue<int> a({1, 2, 3, 4});
  std::queue<int> b({1, 2, 3, 4});

  s21::queue<int> c = a;
  std::queue<int> d = b;
  ASSERT_EQ(true, checkEqQ(c, d));
}

TEST(Acsseor, areEmptyQ) {
  s21::queue<int> a;
  std::queue<int> b;
  ASSERT_EQ(true, a.empty() == b.empty());
}
TEST(Acsseor, notEmptyQ) {
  s21::queue<double> a({1, 2, 3, 4});
  std::queue<double> b({4, 3, 2});
  ASSERT_EQ(true, a.empty() == b.empty());
}

TEST(size, eqQ) {
  s21::queue<double> a({1, 2, 3, 4});
  std::queue<double> b({4, 3, 2, 1});
  ASSERT_EQ(true, a.size() == b.size());
}
TEST(size, emptyQ) {
  s21::queue<int> a;
  std::queue<int> b;
  ASSERT_EQ(true, a.size() == b.size());
}
TEST(size, notEqQ) {
  s21::queue<double> a({1, 2, 3, 4});
  std::queue<double> b({4, 3, 2});
  ASSERT_EQ(false, a.size() == b.size());
}

TEST(push, intQ) {
  s21::queue<int> a;
  std::queue<int> b;

  a.push(1);
  a.push(100);
  a.push(-5);

  b.push(1);
  b.push(100);
  b.push(-5);

  ASSERT_EQ(true, checkEqQ(a, b));
}

TEST(pop, intQ) {
  s21::queue<int> a({1, 2, 3, 4});
  std::queue<int> b({1, 2, 3, 4});

  a.pop();
  a.pop();
  a.pop();

  b.pop();
  b.pop();
  b.pop();

  ASSERT_EQ(true, checkEqQ(a, b));
}

TEST(swap, intQ) {
  s21::queue<int> a({1, 2, 3, 4});
  std::queue<int> b({1, 2, 3, 4});
  s21::queue<int> c({5, 6, 7, 8, 9, 10});
  std::queue<int> d({5, 6, 7, 8, 9, 10});
  a.swap(c);
  b.swap(d);

  ASSERT_EQ(true, checkEqQ(a, b));
  ASSERT_EQ(true, checkEqQ(c, d));
}

TEST(swap, insert_maney1) {
  s21::queue<int> a({1, 2, 3});
  std::queue<int> b({1, 2, 3, 5, 6, 7, 8});
  a.insert_many_back(5, 6, 7, 8);
  ASSERT_EQ(a.size(), b.size());
  ASSERT_EQ(a.front(), b.front());
  b.pop();
  a.pop();
  ASSERT_EQ(a.front(), b.front());
  b.pop();
  a.pop();
  ASSERT_EQ(a.front(), b.front());
  b.pop();
  a.pop();
  ASSERT_EQ(a.front(), b.front());
}

TEST(swap, insert_maney2) {
  s21::queue<int> a({1, 2, 3});
  std::queue<int> b({1, 2, 3, 5});
  a.insert_many_back(5);
  ASSERT_EQ(a.size(), b.size());
  ASSERT_EQ(a.front(), b.front());
  b.pop();
  a.pop();
  ASSERT_EQ(a.front(), b.front());
  b.pop();
  a.pop();
  ASSERT_EQ(a.front(), b.front());
  b.pop();
  a.pop();
  ASSERT_EQ(a.front(), b.front());
}

TEST(swap, insert_maney3) {
  s21::queue<int> a({1, 2, 3});
  std::queue<int> b({1, 2, 3});
  a.insert_many_back();
  ASSERT_EQ(a.size(), b.size());
  ASSERT_EQ(a.front(), b.front());
  b.pop();
  a.pop();
  ASSERT_EQ(a.front(), b.front());
  b.pop();
  a.pop();
  ASSERT_EQ(a.front(), b.front());
}
