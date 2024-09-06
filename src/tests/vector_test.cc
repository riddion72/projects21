#include "test_header.h"

class VectorTest : public testing::Test {
 protected:
  s21::Vector<int> s21_vector, s21_vector_dest, s21_vector_src;
  std::vector<int> std_vector, std_vector_dest, std_vector_src;

  void initWithSize(s21::Vector<int> &s21_vector,
                    std::vector<int> &std_vector) {
    s21_vector = s21::Vector<int>(5);
    std_vector = std::vector<int>(5);
  }
  void initInitializerList(s21::Vector<int> &s21_vector,
                           std::vector<int> &std_vector) {
    s21_vector = s21::Vector<int>({1, 2, 3, 4});
    std_vector = std::vector<int>({1, 2, 3, 4});
  }
  void checkEqVector(const s21::Vector<int> &s21_vector,
                     const std::vector<int> &std_vector) const {
    EXPECT_EQ(s21_vector.size(), std_vector.size());
    EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
    // unsigned long dataSize = s21_vector.size() * sizeof(int);
    // EXPECT_EQ(memcmp(s21_vector.data(), std_vector.data(), dataSize), 0);
  }
  void printSizeCapacity() const {
    std::cout << "size: " << s21_vector.size() << " " << std_vector.size()
              << std::endl;
    std::cout << "capacity: " << s21_vector.capacity() << " "
              << std_vector.capacity() << std::endl;
  }
};

TEST_F(VectorTest, DefaultConstructor) {
  checkEqVector(s21_vector, std_vector);
}
TEST_F(VectorTest, ConstructorWithSize) {
  initWithSize(s21_vector, std_vector);
  checkEqVector(s21_vector, std_vector);
}
TEST_F(VectorTest, ConstructorWithInitializerList) {
  initInitializerList(s21_vector, std_vector);
  checkEqVector(s21_vector, std_vector);
}
TEST_F(VectorTest, CopyConstructor) {
  initInitializerList(s21_vector_src, std_vector_src);
  s21::Vector<int> s21_vector_dest(s21_vector_src);
  std::vector<int> std_vector_dest(std_vector_src);
  checkEqVector(s21_vector_dest, std_vector_dest);
}
TEST_F(VectorTest, MoveConstructor) {
  initInitializerList(s21_vector_src, std_vector_src);
  s21::Vector<int> s21_vector_dest(std::move(s21_vector_src));
  std::vector<int> std_vector_dest(std::move(std_vector_src));
  checkEqVector(s21_vector_dest, std_vector_dest);
}
TEST_F(VectorTest, MoveOperator) {
  initInitializerList(s21_vector_src, std_vector_src);

  s21_vector_dest = std::move(s21_vector_src);
  std_vector_dest = std::move(std_vector_src);

  checkEqVector(s21_vector_dest, std_vector_dest);
  checkEqVector(s21_vector_src, std_vector_src);
}

TEST_F(VectorTest, ReferenceAt) {
  initInitializerList(s21_vector, std_vector);
  for (std::size_t i = 0; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector.at(i), std_vector.at(i));
  }
  EXPECT_THROW(s21_vector.at(-1), std::out_of_range);
  EXPECT_THROW(s21_vector.at(4), std::out_of_range);
  EXPECT_THROW(std_vector.at(-1), std::out_of_range);
  EXPECT_THROW(std_vector.at(4), std::out_of_range);
}

TEST_F(VectorTest, OperatorBracket) {
  initInitializerList(s21_vector, std_vector);
  s21_vector[0] = 5;
  std_vector[0] = 5;
  checkEqVector(s21_vector, std_vector);
}

TEST_F(VectorTest, Front) {
  initInitializerList(s21_vector, std_vector);
  EXPECT_EQ(s21_vector.front(), std_vector.front());
}

TEST_F(VectorTest, FrontThrow) {
  EXPECT_THROW(s21_vector.front(), std::out_of_range);
}

TEST_F(VectorTest, Back) {
  initInitializerList(s21_vector, std_vector);
  EXPECT_EQ(s21_vector.back(), std_vector.back());
}

TEST_F(VectorTest, BackThrow) {
  EXPECT_THROW(s21_vector.back(), std::out_of_range);
}

TEST_F(VectorTest, Data) {
  initInitializerList(s21_vector, std_vector);
  EXPECT_EQ(&s21_vector[0], s21_vector.data());
  EXPECT_EQ(&std_vector[0], std_vector.data());
}

TEST_F(VectorTest, Empty) {
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  initInitializerList(s21_vector, std_vector);
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST_F(VectorTest, Size) {
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  initInitializerList(s21_vector, std_vector);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST_F(VectorTest, MaxSize) {
  initInitializerList(s21_vector, std_vector);
  EXPECT_EQ(s21_vector.max_size() ? 1 : 0, std_vector.max_size() ? 1 : 0);
}

TEST_F(VectorTest, DISABLED_MaxSizeComparison) {
  initInitializerList(s21_vector, std_vector);

  // Сравнение максимальных размеров.
  EXPECT_EQ(s21_vector.max_size(), std_vector.max_size());
}

TEST_F(VectorTest, Reserve) {
  s21_vector.reserve(10);
  EXPECT_EQ(s21_vector.capacity(), 10);
  s21_vector.reserve(5);
  EXPECT_EQ(s21_vector.capacity(), 10);
}

TEST_F(VectorTest, Capacity) {
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  s21_vector.reserve(10);
  std_vector.reserve(10);
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
}

TEST_F(VectorTest, ShrinkToFit) {
  initInitializerList(s21_vector, std_vector);
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  s21_vector.reserve(10);
  std_vector.reserve(10);
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  s21_vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
}
TEST_F(VectorTest, Clear) {
  initInitializerList(s21_vector, std_vector);
  checkEqVector(s21_vector, std_vector);
  s21_vector.clear();
  std_vector.clear();
  checkEqVector(s21_vector, std_vector);
}

// TEST_F(VectorTest, Insert) {
//   checkEqVector(s21_vector_src, std_vector_src);
//   s21::Vector<int>::iterator s21_iter = s21_vector.begin();
//   std::vector<int>::iterator std_iter = std_vector.begin();
//   s21_vector.insert(s21_iter, 100);
//   std_vector.insert(std_iter, 100);
//   checkEqVector(s21_vector, std_vector);

//   s21_iter = s21_vector.begin();  // Сначала вернитесь к началу
//   std_iter = std_vector.begin();  // Сначала вернитесь к началу
//   s21_iter = s21_vector.insert(s21_iter, 100);  // Теперь выполняйте вставку
//   std_iter = std_vector.insert(std_iter, 100);
//   checkEqVector(s21_vector, std_vector);

//   // Теперь вы можете выполнить проверку для итераторов за пределами диапазона
//   s21_iter = s21_vector.begin() - 1;
//   EXPECT_THROW(s21_vector.insert(s21_iter, 100), std::out_of_range);

//   s21_iter = s21_vector.end() + 1;
//   EXPECT_THROW(s21_vector.insert(s21_iter, 100), std::out_of_range);
// }

TEST_F(VectorTest, Erase) {
  initInitializerList(s21_vector, std_vector);
  checkEqVector(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter = s21_vector.begin() + 2;
  std::vector<int>::iterator std_iter = std_vector.begin() + 2;
  s21_vector.erase(s21_iter);
  std_vector.erase(std_iter);
  checkEqVector(s21_vector, std_vector);

  s21_iter = s21_vector.begin() - 1;
  std_iter = std_vector.begin() - 1;

  EXPECT_THROW(s21_vector.erase(s21_iter), std::out_of_range);
}

TEST_F(VectorTest, PushBack) {
  s21_vector.push_back(5);
  std_vector.push_back(5);
  checkEqVector(s21_vector, std_vector);

  s21_vector.push_back(1);
  s21_vector.push_back(2);

  std_vector.push_back(1);
  std_vector.push_back(2);
  checkEqVector(s21_vector, std_vector);
}
TEST_F(VectorTest, PopBack) {
  initInitializerList(s21_vector, std_vector);

  s21_vector.pop_back();
  s21_vector.pop_back();
  s21_vector.pop_back();
  std_vector.pop_back();
  std_vector.pop_back();
  std_vector.pop_back();
  checkEqVector(s21_vector, std_vector);

  s21_vector.pop_back();
  std_vector.pop_back();
  checkEqVector(s21_vector, std_vector);
}

TEST_F(VectorTest, Swap) {
  initInitializerList(s21_vector_src, std_vector_src);
  s21_vector_dest.push_back(5);
  std_vector_dest.push_back(5);

  s21_vector_dest.swap(s21_vector_src);
  std_vector_dest.swap(std_vector_src);

  checkEqVector(s21_vector_dest, std_vector_dest);
  checkEqVector(s21_vector_src, std_vector_src);
}

TEST_F(VectorTest, DefaultConstructorIterator) {
  s21::Vector<int>::iterator iterator = nullptr;
  ASSERT_TRUE(iterator == nullptr);
}

TEST_F(VectorTest, ConstructorIterator) {
  s21::Vector<int>::iterator iterator(s21_vector.data());
  ASSERT_TRUE(iterator == nullptr);
}

TEST_F(VectorTest, EqIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator iter1(s21_vector.data());
  s21::Vector<int>::iterator iter2(s21_vector.data());
  s21::Vector<int>::iterator iter3(std_vector.data());
  ASSERT_TRUE(iter1 == iter2);
  ASSERT_FALSE(iter1 == iter3);
}

TEST_F(VectorTest, NoEqIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator iter1(s21_vector.data());
  s21::Vector<int>::iterator iter2(std_vector.data());
  ASSERT_TRUE(iter1 != iter2);
}

TEST_F(VectorTest, PreOperPlusPlusIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter = s21_vector.begin();
  std::vector<int>::iterator std_iter = std_vector.begin();
  ++s21_iter;
  ++std_iter;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, PreOperMinMinIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter = s21_vector.begin();
  std::vector<int>::iterator std_iter = std_vector.begin();
  ++s21_iter;
  ++std_iter;
  --s21_iter;
  --std_iter;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, PostOperPlusPlusIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter = s21_vector.begin();
  std::vector<int>::iterator std_iter = std_vector.begin();
  s21_iter++;
  std_iter++;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, PostOperMinMinIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter = s21_vector.end();
  std::vector<int>::iterator std_iter = std_vector.end();
  s21_iter--;
  std_iter--;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, PlusIterAndInt) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter = s21_vector.begin();
  std::vector<int>::iterator std_iter = std_vector.begin();
  s21_iter = s21_iter + 2;
  std_iter = std_iter + 2;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, MinusIterAndInt) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter = s21_vector.end();
  std::vector<int>::iterator std_iter = std_vector.end();
  s21_iter = s21_iter - 2;
  std_iter = std_iter - 2;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, MinusIterIter) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter1 = s21_vector.end();
  s21::Vector<int>::iterator s21_iter2 = s21_vector.begin();
  std::vector<int>::iterator std_iter1 = std_vector.end();
  std::vector<int>::iterator std_iter2 = std_vector.begin();
  int s21_result = s21_iter1 - s21_iter2;
  int std_result = std_iter1 - std_iter2;
  ASSERT_EQ(s21_result, std_result);
}

TEST_F(VectorTest, LessIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter1 = s21_vector.begin();
  s21::Vector<int>::iterator s21_iter2 = s21_vector.end();
  std::vector<int>::iterator std_iter1 = std_vector.begin();
  std::vector<int>::iterator std_iter2 = std_vector.end();
  ASSERT_TRUE(s21_iter1 < s21_iter2);
  ASSERT_FALSE(s21_iter1 < s21_iter1);
  ASSERT_FALSE(s21_iter2 < s21_iter1);
  ASSERT_TRUE(std_iter1 < std_iter2);
  ASSERT_FALSE(std_iter1 < std_iter1);
  ASSERT_FALSE(std_iter2 < std_iter1);
}

TEST_F(VectorTest, LessOrEqualIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter1 = s21_vector.begin();
  s21::Vector<int>::iterator s21_iter2 = s21_vector.end();
  std::vector<int>::iterator std_iter1 = std_vector.begin();
  std::vector<int>::iterator std_iter2 = std_vector.end();
  ASSERT_TRUE(s21_iter1 <= s21_iter2);
  ASSERT_TRUE(s21_iter1 <= s21_iter1);
  ASSERT_FALSE(s21_iter2 <= s21_iter1);
  ASSERT_TRUE(std_iter1 <= std_iter2);
  ASSERT_TRUE(std_iter1 <= std_iter1);
  ASSERT_FALSE(std_iter2 <= std_iter1);
}

TEST_F(VectorTest, MoreIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter1 = s21_vector.begin();
  s21::Vector<int>::iterator s21_iter2 = s21_vector.end();
  std::vector<int>::iterator std_iter1 = std_vector.begin();
  std::vector<int>::iterator std_iter2 = std_vector.end();
  ASSERT_FALSE(s21_iter1 > s21_iter2);
  ASSERT_FALSE(s21_iter1 > s21_iter1);
  ASSERT_TRUE(s21_iter2 > s21_iter1);
  ASSERT_FALSE(std_iter1 > std_iter2);
  ASSERT_FALSE(std_iter1 > std_iter1);
  ASSERT_TRUE(std_iter2 > std_iter1);
}

TEST_F(VectorTest, MoreOrEqualIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::iterator s21_iter1 = s21_vector.begin();
  s21::Vector<int>::iterator s21_iter2 = s21_vector.end();
  std::vector<int>::iterator std_iter1 = std_vector.begin();
  std::vector<int>::iterator std_iter2 = std_vector.end();
  ASSERT_FALSE(s21_iter1 >= s21_iter2);
  ASSERT_TRUE(s21_iter1 >= s21_iter1);
  ASSERT_TRUE(s21_iter2 >= s21_iter1);
  ASSERT_FALSE(std_iter1 >= std_iter2);
  ASSERT_TRUE(std_iter1 >= std_iter1);
  ASSERT_TRUE(std_iter2 >= std_iter1);
}

TEST_F(VectorTest, ConstDefaultConstructorIterator) {
  s21::Vector<int>::const_iterator iterator = nullptr;
  ASSERT_TRUE(iterator == nullptr);
}

TEST_F(VectorTest, ConstConstructorIterator) {
  s21::Vector<int>::const_iterator iterator(s21_vector.data());
  ASSERT_TRUE(iterator == nullptr);
}

TEST_F(VectorTest, ConstEqIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::const_iterator iter1(s21_vector.data());
  s21::Vector<int>::const_iterator iter2(s21_vector.data());
  s21::Vector<int>::const_iterator iter3(std_vector.data());
  ASSERT_TRUE(iter1 == iter2);
  ASSERT_FALSE(iter1 == iter3);
}

TEST_F(VectorTest, ConstNoEqIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::const_iterator iter1(s21_vector.data());
  s21::Vector<int>::const_iterator iter2(std_vector.data());
  ASSERT_TRUE(iter1 != iter2);
}

TEST_F(VectorTest, ConstPreOperPlusPlusIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::const_iterator s21_iter = s21_vector.begin();
  std::vector<int>::const_iterator std_iter = std_vector.begin();
  ++s21_iter;
  ++std_iter;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, ConstPreOperMinMinIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::const_iterator s21_iter = s21_vector.begin();
  std::vector<int>::const_iterator std_iter = std_vector.begin();
  ++s21_iter;
  ++std_iter;
  --s21_iter;
  --std_iter;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, ConstPostOperPlusPlusIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::const_iterator s21_iter = s21_vector.begin();
  std::vector<int>::const_iterator std_iter = std_vector.begin();
  s21_iter++;
  std_iter++;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, ConstPostOperMinMinIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::const_iterator s21_iter = s21_vector.end();
  std::vector<int>::const_iterator std_iter = std_vector.end();
  s21_iter--;
  std_iter--;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, ConstPlusIterAndInt) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::const_iterator s21_iter = s21_vector.begin();
  std::vector<int>::const_iterator std_iter = std_vector.begin();
  s21_iter = s21_iter + 2;
  std_iter = std_iter + 2;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, ConstMinusIterAndInt) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::const_iterator s21_iter = s21_vector.end();
  std::vector<int>::const_iterator std_iter = std_vector.end();
  s21_iter = s21_iter - 2;
  std_iter = std_iter - 2;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST_F(VectorTest, ConstMinusIterIter) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::const_iterator s21_iter1 = s21_vector.end();
  s21::Vector<int>::const_iterator s21_iter2 = s21_vector.begin();
  std::vector<int>::const_iterator std_iter1 = std_vector.end();
  std::vector<int>::const_iterator std_iter2 = std_vector.begin();
  int s21_result = s21_iter1 - s21_iter2;
  int std_result = std_iter1 - std_iter2;
  ASSERT_EQ(s21_result, std_result);
}

TEST_F(VectorTest, ConstLessIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::const_iterator s21_iter1 = s21_vector.begin();
  s21::Vector<int>::const_iterator s21_iter2 = s21_vector.end();
  std::vector<int>::const_iterator std_iter1 = std_vector.begin();
  std::vector<int>::const_iterator std_iter2 = std_vector.end();
  ASSERT_TRUE(s21_iter1 < s21_iter2);
  ASSERT_FALSE(s21_iter1 < s21_iter1);
  ASSERT_FALSE(s21_iter2 < s21_iter1);
  ASSERT_TRUE(std_iter1 < std_iter2);
  ASSERT_FALSE(std_iter1 < std_iter1);
  ASSERT_FALSE(std_iter2 < std_iter1);
}

TEST_F(VectorTest, ConstLessOrEqualIterator) {
  initInitializerList(s21_vector, std_vector);
  s21::Vector<int>::const_iterator s21_iter1 = s21_vector.begin();
  s21::Vector<int>::const_iterator s21_iter2 = s21_vector.end();
  std::vector<int>::const_iterator std_iter1 = std_vector.begin();
  std::vector<int>::const_iterator std_iter2 = std_vector.end();
  ASSERT_TRUE(s21_iter1 <= s21_iter2);
  ASSERT_TRUE(s21_iter1 <= s21_iter1);
  ASSERT_FALSE(s21_iter2 <= s21_iter1);
  ASSERT_TRUE(std_iter1 <= std_iter2);
  ASSERT_TRUE(std_iter1 <= std_iter1);
  ASSERT_FALSE(std_iter2 <= std_iter1);
}

TEST_F(VectorTest, InsertMany) {
  s21::Vector<int> v = {1, 2, 3};
  std::vector<int> cv = {4, 5, 6, 1, 2, 3};
  auto pos_s21 = v.begin();
  v.insert_many(pos_s21, 4, 5, 6);
  EXPECT_TRUE(std::equal(v.begin(), v.end(), cv.begin()));
}

TEST_F(VectorTest, InsertManyBack) {
  s21::Vector<int> v = {1, 2, 3};
  std::vector<int> cv = {1, 2, 3, 4, 5, 6};
  v.insert_many_back(4, 5, 6);
  EXPECT_TRUE(std::equal(v.begin(), v.end(), cv.begin()));
}
