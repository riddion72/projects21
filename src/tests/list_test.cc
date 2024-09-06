#include "test_header.h"

TEST(ListTest, CompareLists) {
  s21::List<int> my_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  EXPECT_TRUE(my_list.compare_lists(std_list));
  std_list.push_back(6);
  EXPECT_FALSE(my_list.compare_lists(std_list));
  std_list.pop_back();
  my_list.push_front(0);
  std_list.push_front(0);
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, DefaultConstructor) {
  s21::List<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.size(), 0);
  EXPECT_TRUE(my_list.empty());

  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, SizeConstructor) {
  s21::List<int> my_list(1000000);
  std::list<int> std_list(1000000);
  EXPECT_EQ(my_list.size(), 1000000);
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, InitializerListConstructor) {
  s21::List<int> my_list{1, 2, 3, 7, 9};
  std::list<int> std_list{1, 2, 3, 7, 9};
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, InitializerListConstructor_2) {
  std::initializer_list<int> b;
  s21::List<int> my_list{b};
  std::list<int> std_list{b};
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, CopyConstructor) {
  s21::List<int> my_list{1, 2, 3};
  s21::List<int> my_list_copy(my_list);
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, CopyConstructorEmpty) {
  s21::List<int> my_list;
  s21::List<int> my_list_copy(my_list);
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, MoveConstructor) {
  s21::List<int> my_list{1, 2, 3};
  s21::List<int> my_list_copy(my_list);
  s21::List<int> my_list_move(std::move(my_list));
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, MoveConstructorEmpty) {
  s21::List<int> my_list;
  s21::List<int> my_list_copy(my_list);
  s21::List<int> my_list_move(std::move(my_list));
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, Front) {
  s21::List<int> my_list{99, 2, 3, 4, 5};
  std::list<int> std_list{99, 2, 3, 4, 5};
  EXPECT_EQ(my_list.front(), std_list.front());
}

TEST(ListTest, Back) {
  s21::List<int> my_list{1, 2, 3, 4, 99};
  std::list<int> std_list{1, 2, 3, 4, 99};
  EXPECT_EQ(my_list.back(), std_list.back());
}

TEST(ListTest, Empty) {
  s21::List<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.empty(), std_list.empty());
  my_list.push_back(10);
  std_list.push_back(10);
  EXPECT_EQ(my_list.empty(), std_list.empty());
}

TEST(ListTest, Size) {
  s21::List<int> my_list{1, 2, 3, 4, 5, 6, 7, 8};
  std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListTest, SizeEmpty) {
  s21::List<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListTest, Clear) {
  s21::List<int> my_list{1, 2, 3, 4};
  my_list.clear();
  std::list<int> std_list{1, 2, 5, 4, 3};
  std_list.clear();
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, PushBackTest) {
  s21::List<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  int expected[] = {1, 2, 3};
  int index = 0;

  for (const auto& elem : myList) {
    ASSERT_EQ(elem, expected[index]);
    ++index;
  }
}

TEST(ListTest, begin_1) {
  s21::List<int> my_list1{500, 15000, 30000};

  std::list<int> std_list2{500, 15000, 30000};
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, end_2) {
  s21::List<int> my_list1;
  std::list<int> std_list2;

  // Сравним end() итераторы на равенство (они должны быть равны)
  EXPECT_EQ(my_list1.end() == my_list1.begin(),
            std_list2.end() == std_list2.begin());
}

TEST(ListTest, end_3) {
  s21::List<int> my_list{1, 2, 31};
  std::list<int> std_list2{1, 2, 31};

  // Сравним end() итераторы на равенство (они должны быть равны)
  EXPECT_EQ(my_list.end() == my_list.begin(),
            std_list2.end() == std_list2.begin());
}

TEST(ListTest, Insert_1) {
  s21::List<int> my_list1{1, 9999, 20000};
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Insert_2) {
  s21::List<int> my_list1{1, 9999, 20000};
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Insert_3) {
  s21::List<int> my_list1;
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1;
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Insert_4) {
  s21::List<int> my_list1;
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1;
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Insert_5) {
  s21::List<int> my_list1(4);
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1(4);
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Insert_6) {
  s21::List<int> my_list1(4);
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1(4);
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Erase_1) {
  s21::List<int> my_list1{1, 9999, 20000};
  my_list1.erase(my_list1.begin());

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.erase(std_list1.begin());

  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, PopFront) {
  s21::List<int> my_list{1, 2, 3, 4, 5};
  my_list.pop_front();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_front();
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, Swap) {
  s21::List<int> my_list1{1, 2, 3, 4, 5};
  s21::List<int> my_list2{6, 7, 8, 9, 10, 11};
  my_list1.swap(my_list2);

  std::list<int> std_list1{1, 2, 3, 4, 5};
  std::list<int> std_list2{6, 7, 8, 9, 10, 11};
  std_list1.swap(std_list2);

  EXPECT_TRUE(my_list1.compare_lists(std_list1));
  EXPECT_TRUE(my_list2.compare_lists(std_list2));
}

TEST(ListTest, Swap_2) {
  s21::List<int> my_list1{1, 5, 8, 100};
  s21::List<int> my_list2;
  my_list1.swap(my_list2);

  std::list<int> std_list1{1, 5, 8, 100};
  std::list<int> std_list2;
  std_list1.swap(std_list2);

  EXPECT_TRUE(my_list1.compare_lists(std_list1));
  EXPECT_TRUE(my_list2.compare_lists(std_list2));
}

TEST(ListTest, Merge_1) {
  s21::List<int> my_list1{1, 9999, 20000};
  s21::List<int> my_list2{500, 15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Merge_2) {
  s21::List<int> my_list1{1, 9999, 20000};
  s21::List<int> my_list2{15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Merge_3) {
  s21::List<int> my_list1{1, 20000, 666};
  s21::List<int> my_list2{15000, 154, 124, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 20000, 666};
  std::list<int> std_list2{15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Merge_4) {
  s21::List<int> my_list1;
  s21::List<int> my_list2{15000, 154, 124, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2{15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Merge_5) {
  s21::List<int> my_list1{1, 20000, 666};
  s21::List<int> my_list2;
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 20000, 666};
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Merge_6) {
  s21::List<int> my_list1;
  s21::List<int> my_list2;
  my_list1.merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Splice_1) {
  s21::List<int> my_list1{1, 9999, 20000};
  s21::List<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Splice_2) {
  s21::List<int> my_list1{1, 9999, 20000};
  s21::List<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Splice_3) {
  s21::List<int> my_list1;
  s21::List<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(my_list1.compare_lists(std_list1));
}

TEST(ListTest, Reverse_1) {
  s21::List<int> my_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, Reverse_2) {
  s21::List<int> my_list(4);
  std::list<int> std_list(4);
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, Reverse_3) {
  s21::List<int> my_list;
  std::list<int> std_list;
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, Unique_1) {
  s21::List<int> my_list{90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  std::list<int> std_list{90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, Unique_2) {
  s21::List<int> my_list(3);
  std::list<int> std_list(3);
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, Unique_3) {
  s21::List<int> my_list;
  std::list<int> std_list;
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, Sort_1) {
  s21::List<int> my_list{90, 10, 3, 40, 30, 20, 555, 21, 1};
  std::list<int> std_list{90, 10, 3, 40, 30, 20, 555, 21, 1};

  my_list.sort();
  std_list.sort();

  EXPECT_TRUE(my_list.compare_lists(std_list));
}

TEST(ListTest, InsertMany) {
  s21::List<int> v = {1, 2, 3};
  std::list<int> cv = {4, 5, 6, 1, 2, 3};
  auto pos_s21 = v.begin();
  v.insert_many(pos_s21, 4, 5, 6);
  EXPECT_TRUE(v.compare_lists(cv));
}

TEST(ListTest, InsertManyBack) {
  s21::List<int> v = {1, 2, 3};
  std::list<int> cv = {1, 2, 3, 4, 5, 6};
  v.insert_many_back(4, 5, 6);
  EXPECT_TRUE(v.compare_lists(cv));
}

/* ВКЛЮЧАТЬ ЗАПРЕЩЕНО */
// TEST(ListTest, Secret_Sort_test) {
//     s21::List<int> my_list{90, 10, 3, 40, 30, 20,1,21,1,555};
//     std::list<int> std_list{90, 10, 3, 40, 30, 20,1,21,1,555};
//     my_list.secret_sort();
//     std_list.sort();
//     EXPECT_TRUE(my_list.compare_lists(std_list));
// }
