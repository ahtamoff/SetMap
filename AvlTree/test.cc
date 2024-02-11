#include "AvlTree.h"

#include "gtest/gtest.h"
#include <set>

TEST(set, SetIteratorsSet) {
  s21::AvlTree<std::string> my_tree{"This", "is", "my", "set"};
  std::set<std::string> orig_set{"This", "is", "my", "set"};
  auto my_it = my_tree.begin();
  auto orig_it = orig_set.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_tree.end();
  orig_it = orig_set.end();
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}