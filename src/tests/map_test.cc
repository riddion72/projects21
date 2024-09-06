#include "test_header.h"

TEST(map, ConstructorDefaultMap) {
  s21::map<int, char> my_empty_map;
  std::map<int, char> orig_empty_map;
  EXPECT_EQ(my_empty_map.empty(), orig_empty_map.empty());
}

TEST(map, ConstructorInitializerMap) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorInitializerMap2) {
  s21::map<int, char> my_map = {};
  std::map<int, char> orig_map = {};
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorCopyMap) {
  s21::map<int, int> my_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> my_map_copy = my_map;
  std::map<int, int> orig_map_copy = orig_map;
  EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
  auto my_it = my_map_copy.begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorMoveMap) {
  s21::map<int, int> my_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> my_map_copy = std::move(my_map);
  std::map<int, int> orig_map_copy = std::move(orig_map);
  EXPECT_EQ(my_map.size(), orig_map.size());
  EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
  auto my_it = my_map_copy.begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, OperatorMap) {
  s21::map<char, std::string> my_map = {
      {'+', "summ"}, {'-', "sub"}, {'*', "mul"}};
  std::map<char, std::string> orig_map = {
      {'+', "summ"}, {'-', "sub"}, {'*', "mul"}};
  my_map['+'] = "add";
  orig_map['+'] = "add";
  orig_map['-'] = "exp";
  EXPECT_TRUE(my_map['+'] == orig_map['+']);
  EXPECT_FALSE(my_map['-'] == orig_map['-']);
  EXPECT_TRUE(my_map['*'] == orig_map['*']);
}

TEST(map, DISABLED_AtOperatorExceptionMap) {
  s21::map<char, std::string> my_map = {
      {'+', "summ"}, {'-', "sub"}, {'*', "mul"}};
  EXPECT_THROW(my_map.at('g') = "add", std::out_of_range);
}

TEST(map, AtOperatorMap) {
  s21::map<char, std::string> my_map = {
      {'+', "summ"}, {'-', "sub"}, {'*', "mul"}};
  std::map<char, std::string> orig_map = {
      {'+', "summ"}, {'-', "sub"}, {'*', "mul"}};
  my_map.at('+') = "add";
  orig_map.at('+') = "add";
  orig_map.at('-') = "exp";
  EXPECT_TRUE(my_map['+'] == orig_map['+']);
  EXPECT_FALSE(my_map['-'] == orig_map['-']);
  EXPECT_TRUE(my_map['*'] == orig_map['*']);
}

TEST(map, CapacityMap) {
  s21::map<char, std::string> my_map;
  std::map<char, std::string> orig_map;
  EXPECT_TRUE(my_map.empty() == orig_map.empty());
  my_map.insert('k', "now");
  EXPECT_FALSE(my_map.empty() == orig_map.empty());
  EXPECT_EQ(my_map.size(), 1);
}

TEST(map, ClearMap) {
  s21::map<int, int> my_map;
  std::map<int, int> orig_map;
  my_map.clear();
  orig_map.clear();
  EXPECT_EQ(my_map.empty(), orig_map.empty());
  my_map.insert(std::make_pair(1, 1));
  orig_map.insert(std::make_pair(1, 1));
  EXPECT_EQ(my_map.empty(), orig_map.empty());
  my_map.clear();
  orig_map.clear();
  EXPECT_EQ(my_map.empty(), orig_map.empty());
}

TEST(map, MapInsert1) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(std::make_pair(1, 'a'));
  my_map.insert(std::make_pair(2, 'b'));
  my_map.insert(std::make_pair(3, 'c'));
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'b'));
  orig_map.insert(std::make_pair(3, 'c'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert(std::make_pair(1, 'a'));
  auto pr2 = orig_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert2) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'b');
  my_map.insert(3, 'c');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'b'));
  orig_map.insert(std::make_pair(3, 'c'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert(1, 'a');
  auto pr2 = orig_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert3) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert_or_assign(1, 'b');
  auto i = orig_map.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}

TEST(map, MapErase) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(my_map.size(), orig_map.size());
  my_map.erase(my_map.begin());
  orig_map.erase(orig_map.begin());
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, SwapMap) {
  s21::map<int, int> my_map = {{1, 1}};
  s21::map<int, int> my_swap_map = {{3, 3}, {4, 4}};

  my_map.swap(my_swap_map);
  EXPECT_EQ(my_map.size(), 2);
  EXPECT_EQ(my_swap_map.size(), 1);
  auto x = (*(my_map.begin())).first;
  auto y = (*(my_swap_map.begin())).first;
  EXPECT_EQ(x, 3);
  EXPECT_EQ(y, 1);
}

TEST(map, MergeMap) {
  s21::map<int, int> my_map = {{1, 1}, {4, 4}, {2, 2}};
  s21::map<int, int> my_map_merge = {{3, 3}, {4, 4}};

  std::map<int, int> orig_map = {{1, 1}, {4, 4}, {2, 2}};
  std::map<int, int> orig_map_merge = {{3, 3}, {4, 4}};

  my_map.merge(my_map_merge);
  orig_map.merge(orig_map_merge);

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
  EXPECT_EQ(my_map_merge.contains(4), true);
  EXPECT_EQ(my_map_merge.contains(3), true);
}
