#include "test_header.h"

TEST(array_test, constr1) {
  s21::Array<int, 10> arr1;
  std::array<int, 10> arr2;
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(array_test, constr2) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr1.at(i), arr2.at(i));
}

// TEST(array_test, constr4) {
//     EXPECT_ANY_THROW((s21::Array<int, 3> arr1 = {1, 2, 3, 4}));
// }

TEST(array_test, constr5) {
  s21::Array<int, 3> arr1 = {1, 2, 3};
  std::array<int, 3> arr2 = {1, 2, 3};
  auto arr1_1 = std::move(arr1);
  auto arr2_1 = std::move(arr2);
  auto it1 = arr1_1.begin();
  for (auto it2 = arr2_1.begin(); it2 != arr2_1.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1_1.size(), arr2_1.size());
}

TEST(array_test, constr6) {
  s21::Array<int, 3> arr1 = {1, 2, 3};
  std::array<int, 3> arr2 = {1, 2, 3};
  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  for (; it2 != arr2.end(); ++it1, ++it2) EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST(array_test, constr7) {
  s21::Array<int, 3> arr1 = {1, 2, 3};
  std::array<int, 3> arr2 = {1, 2, 3};
  s21::Array<int, 3> arr1_1;
  std::array<int, 3> arr2_1;
  arr1_1 = std::move(arr1);
  arr2_1 = std::move(arr2);
  auto it1 = arr1_1.begin();
  for (auto it2 = arr2_1.begin(); it2 != arr2_1.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1_1.size(), arr2_1.size());
}

TEST(array_test, at1) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr1.at(i), arr2.at(i));
}

// TEST(array_test, at2) {
//     s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
//     EXPECT_ANY_THROW(arr1.at(-3));
// }

TEST(array_test, operator1) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr1[i], arr2[i]);
}

TEST(array_test, front1) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  EXPECT_EQ(arr1.front(), arr2.front());
}

TEST(array_test, back1) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  EXPECT_EQ(arr1.back(), arr2.back());
}

TEST(array_test, data1) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  EXPECT_EQ(*(arr1.data()), *(arr2.data()));
}

TEST(array_test, begin1) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(array_test, end1) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};

  auto it1 = arr1.end();
  auto it2 = arr2.end();
  it1--, it2--;
  EXPECT_EQ(*it2, *it1);
}

TEST(array_test, empty1) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  EXPECT_EQ(arr1.empty(), arr2.empty());
}

TEST(array_test, empty2) {
  s21::Array<int, 10> arr1;
  std::array<int, 10> arr2;
  EXPECT_EQ(arr1.empty(), arr2.empty());
}

TEST(array_test, size1) {
  s21::Array<int, 10> arr1;
  std::array<int, 10> arr2;
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST(array_test, size2) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST(array_test, max_size1) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(array_test, max_size2) {
  s21::Array<double, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<double, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(array_test, swap1) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  s21::Array<int, 10> arr1_1;
  std::array<int, 10> arr2_1;
  arr1.swap(arr1_1);
  arr2.swap(arr2_1);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1_1.size(), arr2_1.size());
  auto it1 = arr1_1.begin();
  for (auto it2 = arr2_1.begin(); it2 != arr2_1.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(array_test, swap2) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  s21::Array<int, 10> arr1_1 = {11, 22, 33, 55, 88};
  std::array<int, 10> arr2_1 = {11, 22, 33, 55, 88};
  arr1.swap(arr1_1);
  arr2.swap(arr2_1);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1_1.size(), arr2_1.size());
  auto it1 = arr1_1.begin();
  for (auto it2 = arr2_1.begin(); it2 != arr2_1.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(array_test, swap3) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  s21::Array<int, 10> arr1_1;
  std::array<int, 10> arr2_1;
  arr1.swap(arr1_1);
  arr2.swap(arr2_1);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1_1.size(), arr2_1.size());
  auto it1 = arr1_1.begin();
  for (auto it2 = arr2_1.begin(); it2 != arr2_1.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(array_test, fill1) {
  s21::Array<int, 0> arr1;
  std::array<int, 0> arr2;
  arr1.fill(225);
  arr2.fill(225);
  EXPECT_EQ(arr1.size(), arr2.size());
  auto it1 = arr1.begin();
  for (auto it2 = arr2.begin(); it2 != arr2.end(); ++it2) EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST(array_test, fill2) {
  s21::Array<int, 10> arr1;
  std::array<int, 10> arr2;
  arr1.fill(225);
  arr2.fill(225);
  EXPECT_EQ(arr1.size(), arr2.size());
  auto it1 = arr1.begin();
  for (auto it2 = arr2.begin(); it2 != arr2.end(); ++it2) EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST(array_test, iter1) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  for (int i = 0; i < 4; i++) ++it1, ++it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(array_test, iter2) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  std::array<int, 10> arr2 = {1, 2, 3, 5, 8, 13, 21};
  auto it1 = arr1.end();
  auto it2 = arr2.end();
  for (int i = 0; i < 3; i++) --it1, --it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(array_test, iter3) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  auto it1 = arr1.end();
  auto it2 = arr1.end();
  EXPECT_EQ(it1 == it2, true);
}

TEST(array_test, iter4) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  auto it1 = arr1.end();
  auto it2 = arr1.end();
  EXPECT_EQ(it1 != it2, false);
}

TEST(array_test, iter5) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 5, 8, 13, 21};
  auto it1 = arr1.end();
  auto it2 = arr1.end();
  ++it2;
  EXPECT_EQ(it1 == it2, false);
}
