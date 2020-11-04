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

// TEST(librf, SendData) {
//  Libprotocolrf lib;
//  std::string path = "outdatapacked_2.txt";
//  MessengRF messeng("Hello  World");
//  lib.SendData(messeng, path, true);  // true перемешивание включено
//  std::cout << messeng.GetMesseng() << std::endl;
//  EXPECT_EQ(1, 1);
//  ASSERT_THAT(0, Eq(0));
//}

// TEST(librf, ReadData) {
//  Libprotocolrf lib;
//  std::string path = "outdatapacked_2.txt";
//  MessengRF messeng;
//  lib.ReadData(messeng, path);
//  std::cout << messeng.GetMesseng() << std::endl;
//  EXPECT_EQ(1, 1);
//  ASSERT_THAT(0, Eq(0));
//}

TEST(librf, SendData_) {
  Libprotocolrf lib;
  std::string path = "outdatapacked_1.txt";
  Messeng_<std::string> msg_1("Hello world Hello world Hello world", 1);
  Messeng_<std::string> msg_2("Foo bar Foo bar Foo bar Foo bar Foo bar", 2);
  auto data_0 = msg_1.GetRaw();
  auto data_1 = msg_2.GetRaw();
  lib.SendData(data_0, path, 0);
  lib.SendData(data_1, path, 0);

  std::map<int, std::map<int, Packed_>> packeds;
  lib.ReadData(packeds, "outdatapacked_1.txt");

  std::map<int, Messeng_<std::string>> messengs;

  for (auto messeng : packeds) {
    for (auto packed : messeng.second) {
      auto data = packed.second;
      messengs[data.Header_().number_messeng_].PushPacked(data);
    }
  }

  std::cout << messengs[1].Messeng() << std::endl;
  std::cout << messengs[2].Messeng() << std::endl;
  EXPECT_EQ(1, 1);
  ASSERT_THAT(0, Eq(0));
}

#endif  // TST_TEST_1_H
