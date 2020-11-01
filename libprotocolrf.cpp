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
    auto data = messeng.GetPacked();
    std::vector<Packed> data_(data.begin(), data.end());
    auto rnd = std::default_random_engine{};
    std::shuffle(data_.begin(), data_.end(), rnd);

    for (const auto &unit : data_) {
      file.Write(const_cast<Packed &>(unit).ID().Data() + TypeField.kData +
                 "=" + const_cast<Packed &>(unit).Data() + ";\n\0");
    }

  } else {
    for (const auto &unit : messeng.GetPacked()) {
      file.Write(const_cast<Packed &>(unit).ID().Data() + TypeField.kData +
                 "=" + const_cast<Packed &>(unit).Data() + ";\n\0");
    }
  }

  file.Close();
  return 0;
}

std::vector<std::string> Libprotocolrf::Split(const std::string &s,
                                              char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

int Libprotocolrf::ReadData(MessengRF &messeng, const std::string &path) {
  fio::FIO<std::string> file;
  file.Open(path, std::ios::in);
  std::map<std::string, std::string> data;
  if (!file.IsEOF()) {
    auto header = Split(file.GetLine(), ';');
    int size_packed = 0;
    if (header[0].substr(0, 3) == "idm" && header[1].substr(0, 2) == "np" &&
        header[2].substr(0, 2) == "sp") {
      size_packed = std::atoi(Split(header[1], '=')[1].data());
    }

    while (size_packed != 0) {
      auto fields = Split(file.GetLine(), ';');
      if (fields[0].substr(0, 3) == "idm" && fields[1].substr(0, 2) == "np" &&
          fields[2].substr(0, 4) == "data") {
        auto f1 = std::atoi(Split(fields[0], '=')[1].data());
        auto f2 = std::atoi(Split(fields[1], '=')[1].data());
        auto f3 = Split(fields[2], '=')[1].data();
        messeng.AddPacked({f1, f2, f3});
        size_packed--;
      }
    }
  }
  return 0;
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
