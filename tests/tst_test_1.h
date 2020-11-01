#ifndef TST_TEST_1_H
#define TST_TEST_1_H

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "../fio.h"
#include "../libprotocolrf.h"
#include "../messeng.h"

using namespace testing;
using namespace fio;

// TEST(function, test_1) {
//  Libprotocolrf librf;
//  FIO<std::string> file;
//  file.Open("/home/stam/test.txt");
//  std::vector<char> output;
//  file.Read(output);
//  EXPECT_EQ(1, 1);
//  ASSERT_THAT(0, Eq(0));
//}

// TEST(function, Generation_Data) { Libprotocolrf::CreateDataFile(1000, 100); }

// TEST(function, Create_Messeng) {
//  Libprotocolrf lib;
//  std::string path = "outdatapacked_1.txt";
//  MessengRF messeng("Hello World");
//  lib.SendData(messeng, path, false);
//  std::cout << messeng << std::endl;
//  EXPECT_EQ(1, 1);
//  ASSERT_THAT(0, Eq(0));
//}

TEST(function, SendData) {
  Libprotocolrf lib;
  std::string path = "outdatapacked_2.txt";
  MessengRF messeng("Hello  World");
  lib.SendData(messeng, path, true);

  EXPECT_EQ(1, 1);
  ASSERT_THAT(0, Eq(0));
}

TEST(function, ReadData) {
  Libprotocolrf lib;
  std::string path = "outdatapacked_2.txt";
  MessengRF messeng;
  lib.ReadData(messeng, path);
  std::cout << messeng.GetMesseng() << std::endl;
  EXPECT_EQ(1, 1);
  ASSERT_THAT(0, Eq(0));
}

#endif  // TST_TEST_1_H
