// Copyright 2023 abc abc
#include <gtest/gtest.h>

TEST(Sequential, Test_Sum_10) {
  int a = 1;
  int b = 1;
  ASSERT_EQ(a, b);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
