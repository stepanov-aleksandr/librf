#ifndef TST_TEST_1_H
#define TST_TEST_1_H

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "../config.h"
#include "../packed.h"

using namespace testing;

TEST(packed, TestCreate) {
  Packed packed({}, {});
  EXPECT_EQ(1, 1);
}

TEST(packed, TestData) {
  Packed packed(1, 1, "Foo bar");
  auto ret = packed.Data();
  EXPECT_EQ(std::string("Foo bar"), ret);
}

TEST(packed, TestPackField) {
  IDPacked idpacked{1, 1};
  auto ret = idpacked.PackField("idm", 1);
  EXPECT_EQ(std::string("idm=1;"), ret);
}

#endif  // TST_TEST_1_H
