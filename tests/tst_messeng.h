#ifndef TST_TEST_1_H
#define TST_TEST_1_H

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "../config.h"
#include "../messeng.h"

using namespace testing;

TEST(messeng, TestCreate) {
  MessengRF msrf_0;
  MessengRF msrf_1(Packed());
  MessengRF msrf_2("Hello world");
  EXPECT_EQ(1, 1);
}

TEST(messeng, TestGetPacked) {
  MessengRF msrf_2("Hello world");
  auto ret = msrf_2.GetPacked();
  EXPECT_EQ(ret.size(), 4);
}

TEST(messeng, TestGetMesseng) {
  MessengRF msrf_2("Hello world");
  auto ret = msrf_2.GetMesseng();
  EXPECT_EQ(ret.size(), std::string("Hello world").size());
}

TEST(messeng, TestPackField) { EXPECT_EQ(1, 1); }

#endif  // TST_TEST_1_H
