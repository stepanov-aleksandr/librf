#include "libprotocolrf.h"

using namespace fio;

Libprotocolrf::Libprotocolrf() {}

int Libprotocolrf::GetRandomNumber(int min, int max) {
  static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
  return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void Libprotocolrf::GetTestString(const size_t &max_size_str,
                                  const size_t &number_str,
                                  std::string &output) {
  for (size_t i = 0; i < number_str; i++) {
    auto size_str = GetRandomNumber(1, max_size_str);
    for (int j = 0; j < size_str; j++) {
      output.append({(static_cast<char>(GetRandomNumber(32, 122)))});
    }
    output.append(" \0");
    output.append("\n");
  }
}

int Libprotocolrf::SendData(MessengRF &messeng, const std::string &path,
                            bool flag_mix = false) {
  FIO<std::string> file;
  file.Open(path, std::ios::out);

  file.Write(messeng.ID().Data());

  if (flag_mix == true) {
    auto data = messeng.Data();
    std::vector<Packed> data_(data.begin(), data.end());
    auto rnd = std::default_random_engine{};
    std::shuffle(data_.begin(), data_.end(), rnd);

    for (const auto &unit : data_) {
      file.Write(const_cast<Packed &>(unit).ID().Data() + TypeField.kData +
                 "=" + const_cast<Packed &>(unit).Data() + ";\n\0");
    }

  } else {
    for (const auto &unit : messeng.Data()) {
      file.Write(const_cast<Packed &>(unit).ID().Data() + TypeField.kData +
                 "=" + const_cast<Packed &>(unit).Data() + ";\n\0");
    }
  }

  file.Close();
  return 0;
}

class WordDelimitedByCommas : public std::string {};

int Libprotocolrf::ReadData(MessengRF &messeng, const std::string &path) {
  fio::FIO<std::string> file;
  file.Open(path, std::ios::out);
  std::map<std::string, std::string> data;
  while (file.IsOpen()) {
    auto data = file.GetLine();
    std::istringstream iss(data);
    std::vector<std::string> results(
        (std::istream_iterator<WordDelimitedByCommas>(iss)),
        std::istream_iterator<WordDelimitedByCommas>());
    std::cout << "dd" << std::endl;
  }

  ;

  std::string id_messeng;
  std::string num_packed;
  std::string size_packed;
}

int Libprotocolrf::CreateDataFile(const size_t &number_str,
                                  const size_t &max_size_str) {
  fio::FIO<std::string> file;
  file.Open("test.txt", std::ios::out);
  for (size_t i = 0; i < number_str; i++) {
    auto size_str = GetRandomNumber(1, max_size_str);
    for (int j = 0; j < size_str; j++) {
      file.Write({(static_cast<char>(GetRandomNumber(32, 122)))});
    }
    file.Write("\n\0");
  }
  file.Close();
  return 0;
}
