#include "test_header.h"

TEST(multiset_test, constr1) {
  s21::multiset<int> s1{3};
  std::multiset<int> s2{3};
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(multiset_test, constr2) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  EXPECT_EQ(s1.size(), s2.size());
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (; it1 != s1.end() || it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, constr3) {
  s21::multiset<int> s1 = {1, 2, 3};
  std::multiset<int> s2 = {1, 2, 3};
  auto s1_1 = s1;
  auto s2_1 = s2;
  auto it1 = s1_1.begin();
  auto it2 = s2_1.begin();
  for (; it1 != s1_1.end() || it2 != s2_1.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1_1.size(), s2_1.size());
}

TEST(multiset_test, constr4) {
  s21::multiset<int> s1 = {1, 2, 3};
  std::multiset<int> s2 = {1, 2, 3};
  auto s1_1 = std::move(s1);
  auto s2_1 = std::move(s2);
  auto it1 = s1_1.begin();
  auto it2 = s2_1.begin();
  for (; it1 != s1_1.end() || it2 != s2_1.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1_1.size(), s2_1.size());
}

TEST(multiset_test, constr5) {
  s21::multiset<int> s1 = {1, 2, 3};
  std::multiset<int> s2 = {1, 2, 3};
  s21::multiset<int> s1_1;
  std::multiset<int> s2_1;
  s1_1 = std::move(s1);
  s2_1 = std::move(s2);
  auto it1 = s1_1.begin();
  auto it2 = s2_1.begin();
  for (; it1 != s1_1.end() || it2 != s2_1.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1_1.size(), s2_1.size());
}

TEST(multiset_test, begin1) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, end1) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};

  auto it1 = s1.end();
  auto it2 = s2.end();
  it1--, it2--;
  EXPECT_EQ(*it2, *it1);
}

TEST(multiset_test, empty1) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(multiset_test, empty2) {
  s21::multiset<int> s1;
  std::multiset<int> s2;
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(multiset_test, size1) {
  s21::multiset<int> s1;
  std::multiset<int> s2;
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(multiset_test, size2) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(multiset_test, clear) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  s1.clear();
  s2.clear();
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(multiset_test, insert1) {
  s21::multiset<int> s1;
  std::multiset<int> s2;
  s1.insert(6);
  s2.insert(6);
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (; it1 != s1.end() || it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, insert2) {
  s21::multiset<int> s1 = {1};
  std::multiset<int> s2 = {1};
  s1.insert(6);
  s2.insert(6);
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (; it1 != s1.end() || it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, insert3) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  s1.insert(6);
  s2.insert(6);
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (; it1 != s1.end() || it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, insert4) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  s1.insert(3);
  s2.insert(3);
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (; it1 != s1.end() || it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, find1) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto it1 = s1.find(5);
  auto it2 = s2.find(5);
  EXPECT_TRUE(*it1 == *it2);
}

TEST(multiset_test, find2) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto it1 = s1.find(0);
  EXPECT_TRUE(it1 == s1.end());
}

TEST(multiset_test, erase1) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  s1.erase(s1.find(5));
  s2.erase(s2.find(5));
  auto it1 = s1.cbegin();
  auto it2 = s2.cbegin();
  for (; it1 != s1.cend() || it2 != s2.cend(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, erase2) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  s1.erase(s1.find(3));
  s2.erase(s2.find(3));
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (; it1 != s1.end() || it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

// TEST(multiset_test, contains1) {
//     s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
//     std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
//     EXPECT_EQ(s1.contains(13), s2.contains(13));
// }

// TEST(multiset_test, contains2) {
//     s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
//     std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
//     EXPECT_EQ(s1.contains(0), s2.contains(0));
// }

TEST(multiset_test, count1) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  EXPECT_EQ(s1.count(0), s2.count(0));
}

TEST(multiset_test, count2) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  EXPECT_EQ(s1.count(21), s2.count(21));
}

TEST(multiset_test, count3) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  EXPECT_EQ(s1.count(3), s2.count(3));
}

TEST(multiset_test, swap1) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  s21::multiset<int> s1_1;
  std::multiset<int> s2_1;
  s1.swap(s1_1);
  s2.swap(s2_1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1_1.size(), s2_1.size());
  auto it1 = s1_1.begin();
  auto it2 = s2_1.begin();
  for (; it1 != s1_1.end() || it2 != s2_1.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, swap2) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  s21::multiset<int> s1_1 = {11, 22, 33, 55, 88};
  std::multiset<int> s2_1 = {11, 22, 33, 55, 88};
  s1.swap(s1_1);
  s2.swap(s2_1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1_1.size(), s2_1.size());
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (; it1 != s1.end() || it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  auto it1_1 = s1_1.begin();
  auto it2_1 = s2_1.begin();
  for (; it1_1 != s1_1.end() || it2_1 != s2_1.end(); ++it1_1, ++it2_1)
    EXPECT_EQ(*it1_1, *it2_1);
}

TEST(multiset_test, merge1) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  s21::multiset<int> s1_1;
  std::multiset<int> s2_1;
  s1.merge(s1_1);
  s2.merge(s2_1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1_1.size(), s2_1.size());
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (; it1 != s1.end() || it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  auto it1_1 = s1_1.begin();
  auto it2_1 = s2_1.begin();
  for (; it1_1 != s1_1.end() || it2_1 != s2_1.end(); ++it1_1, ++it2_1)
    EXPECT_EQ(*it1_1, *it2_1);
}

TEST(multiset_test, merge2) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  s21::multiset<int> s1_1 = {11, 22, 8, 55, 88};
  std::multiset<int> s2_1 = {11, 22, 8, 55, 88};
  s1.merge(s1_1);
  s2.merge(s2_1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1_1.size(), s2_1.size());
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (; it1 != s1.end() || it2 != s2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  auto it1_1 = s1_1.begin();
  auto it2_1 = s2_1.begin();
  for (; it1_1 != s1_1.end() || it2_1 != s2_1.end(); ++it1_1, ++it2_1)
    EXPECT_EQ(*it1_1, *it2_1);
}

TEST(multiset_test, equal_range1) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto range1 = s1.equal_range(3);
  auto range2 = s2.equal_range(3);
  auto it1_1 = range1.first;
  auto it1_2 = range1.second;
  auto it2_1 = range2.first;
  auto it2_2 = range2.second;
  for (; it1_1 != it1_2 || it2_1 != it2_2; ++it1_1, ++it2_1)
    EXPECT_EQ(*it1_1, *it2_1);
}

TEST(multiset_test, equal_range2) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto range1 = s1.equal_range(21);
  auto range2 = s2.equal_range(21);
  auto it1_1 = range1.first;
  auto it1_2 = range1.second;
  auto it2_1 = range2.first;
  auto it2_2 = range2.second;
  for (; it1_1 != it1_2 || it2_1 != it2_2; ++it1_1, ++it2_1)
    EXPECT_EQ(*it1_1, *it2_1);
}

TEST(multiset_test, equal_range3) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto range1 = s1.equal_range(1);
  auto range2 = s2.equal_range(1);
  auto it1_1 = range1.first;
  auto it1_2 = range1.second;
  auto it2_1 = range2.first;
  auto it2_2 = range2.second;
  for (; it1_1 != it1_2 || it2_1 != it2_2; ++it1_1, ++it2_1)
    EXPECT_EQ(*it1_1, *it2_1);
}

TEST(multiset_test, equal_range4) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto range1 = s1.equal_range(0);
  auto range2 = s2.equal_range(0);
  auto it1_1 = range1.first;
  auto it1_2 = range1.second;
  auto it2_1 = range2.first;
  auto it2_2 = range2.second;
  for (; it1_1 != it1_2 || it2_1 != it2_2; ++it1_1, ++it2_1)
    EXPECT_EQ(*it1_1, *it2_1);
}

TEST(multiset_test, equal_range5) {
  s21::multiset<int> s1 = {3, 3, 3, 3, 3, 3, 3, 3};
  std::multiset<int> s2 = {3, 3, 3, 3, 3, 3, 3, 3};
  auto range1 = s1.equal_range(3);
  auto range2 = s2.equal_range(3);
  auto it1_1 = range1.first;
  auto it1_2 = range1.second;
  auto it2_1 = range2.first;
  auto it2_2 = range2.second;
  for (; it1_1 != it1_2 || it2_1 != it2_2; ++it1_1, ++it2_1)
    EXPECT_EQ(*it1_1, *it2_1);
}

TEST(multiset_test, iter1) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (int i = 0; i < 4; i++) {
    ++it1;
    ++it2;
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(multiset_test, iter2) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  std::multiset<int> s2 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto it1 = s1.end();
  auto it2 = s2.end();
  for (int i = 0; i < 4; i++) {
    --it1;
    --it2;
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(multiset_test, iter3) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto it1 = s1.end();
  auto it2 = s1.end();
  EXPECT_TRUE(it1 == it2);
}

TEST(multiset_test, iter4) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto it1 = s1.end();
  auto it2 = s1.end();
  EXPECT_FALSE(it1 != it2);
}

TEST(multiset_test, iter5) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto it1 = s1.end();
  auto it2 = s1.end();
  --it2;
  EXPECT_FALSE(it1 == it2);
}

TEST(multiset_test, iter6) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto it1 = s1.end();
  auto it2 = it1;
  EXPECT_TRUE(it1 == it2);
}

TEST(multiset_test, iter7) {
  s21::multiset<int> s1 = {1, 3, 21, 5, 8, 2, 3, 13};
  auto it1 = s1.find(5);
  auto it2 = std::move(it1);
  EXPECT_TRUE(it2 == s1.find(5));
}
