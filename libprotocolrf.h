#ifndef LIBPROTOCOLRF_H
#define LIBPROTOCOLRF_H

#include <algorithm>
#include <cstring>
#include <random>
#include <string>
#include "fio.h"
#include "messeng.h"

class Libprotocolrf {
 public:
  Libprotocolrf();

  static int GetRandomNumber(int min, int max);
  static int CreateDataFile(const size_t &number_str,
                            const size_t &max_size_str);
  static int ReadDataInFile();

  void GetTestString(const size_t &max_size_str, const size_t &number_str,
                     std::string &outpu);

  int Mix(MessengRF &messeng);

  virtual int SendData(MessengRF &messeng, const std::string &path,
                       bool flag_mix);
  virtual int ReadData(const MessengRF &messeng, const std::string &path);

 private:
  std::string data_;
};

#endif  // LIBPROTOCOLRF_H
