#ifndef FIO_H
#define FIO_H

#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

namespace fio {

#define RETURN_OK 1
#define NOT_DATA -1
#define NOT_FIND_FILE -2
#define UNSPECIFIED_ERROR 0

enum Operation {
  read = std::ios::in,
  write = std::ios::out,
  append = std::ios::app,
};

enum TypeOpen {
  binary = std::ios::binary,
};

template <class T>
class FIO {
 public:
  FIO() {}
  FIO(const std::string &path, std::ios::openmode modeOpen = std::ios::in)
      : path_(path), modeOpen_(modeOpen) {
    if (path_.size() == 0) {
      std::cerr << "name" << path << "file is not correct" << std::endl;
    }
  }

  ~FIO() {
    if (file_.is_open()) {
      file_.close();
    }
  }

  /**
   * @brief Open открывает файл после закрытия
   * @param path путь до файла
   * @param modeOpen режим открытия std::ios::in или std::ios::out
   * @param typeOpen режим чтения или записи std::ios::binary или текст
   * @return результат открытия , 1 - ОК , -1 ошибка
   */

  int Open(const std::string &path,
           std::ios::openmode modeOpen = std::ios::in) {
    path_ = path;
    modeOpen_ = modeOpen;

    file_.open(path, modeOpen);
    if (!file_.is_open()) {
      std::cerr << "Error open file:" << path << std::endl;
      return NOT_FIND_FILE;
    }
    return RETURN_OK;
  }

  /**
   * @brief Open открывает файл после обьявления коструктора
   * @return результат открытия , 1 - ОК , -1 ошибка
   */

  int Open() {
    file_.open(path_, modeOpen_ | typeOpen_);
    if (!file_.is_open()) {
      std::cerr << "Error open file:" << path_ << std::endl;
      return NOT_FIND_FILE;
    }
    return RETURN_OK;
  }

  /**
   * @brief Close закрывает файл
   * @return результат открытия , 1 - ОК , -1 ошибка
   */
  int Close() {
    if (file_.is_open()) {
      file_.close();
    }
    return RETURN_OK;
  }

  /**
   * @brief Read
   * @param buffer
   * @return результат открытия , 1 - ОК , -1 ошибка
   */
  template <class Conteiner>
  int Read(Conteiner &buffer) {
    if (!file_.is_open()) {
      std::cerr << "file is not open" << std::endl;
      return 0;
    }
    int symbol;
    while (!file_.eof()) {
      symbol = file_.get();
      buffer.push_back(symbol);
    }
    buffer.erase(buffer.end() - 1);
    return buffer.size();
  }

  /**
   * @brief Read читает файл возвращает вектор векторов
   * @return размер прочитатнного
   */
  int Read(std::vector<std::vector<unsigned char>> &pars_data) {
    if (!file_.is_open()) return 0;
    std::string str;
    while (!file_.eof()) {
      std::getline(file_, str);
      if (str.size() != 0)
        pars_data.push_back(std::vector<unsigned char>(str.begin(), str.end()));
    }
    if (pars_data.size() == 0) {
      return NOT_DATA;
    }
    return pars_data.size();
  }

  /**
   * @brief Read читает файл возвращая прочитанное
   * @return результат типа T
   */
  T Read() {
    if (!file_.is_open()) return buffer;
    int symbol;
    while (!file_.eof()) {
      symbol = file_.get();
      buffer.push_back(symbol);
    }
    buffer.erase(buffer.end() - 1);
    return buffer;
  }

  T GetLine() {
    if (!file_.is_open()) return 0;
    std::string str;
    std::getline(file_, str);
    return str;
  }

  /**
   * @brief Write
   * @param buffer
   * @return результат записи , 1 - ОК , -1 ошибка
   */
  int Write(T buffer) {
    if (buffer.size() == 0) {
      std::cerr << "Error FIO::Write(T &buffer) null input data buffer"
                << std::endl;
    }

    for (auto unit : buffer) {
      this->buffer.push_back(unit);
    }

    if (typeid(std::string).name() == typeid(T).name()) {
      file_.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
      return buffer.size();
    }

    if (typeid(int).name() == typeid(T).name() ||
        typeid(double).name() == typeid(T).name() ||
        typeid(float).name() == typeid(T).name()) {
      file_.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
      return buffer.size();
    }
    return buffer.size();
  }

  int Write_(typename T::iterator itr_begin, typename T::iterator itr_end) {
    for (auto itr = itr_begin; itr < itr_end; itr++) {
      if (typeid(int).name() == typeid(T).name() ||
          typeid(double).name() == typeid(T).name() ||
          typeid(float).name() == typeid(T).name()) {
        file_.write(std::to_string(*itr));
      }
      if (typeid(std::string).name() == typeid(T).name()) {
        file_.write(*itr);
      }
    }
    return 0;
  }

  inline bool Existence() {
    struct stat buffer;
    auto ret(stat(path_.c_str(), &buffer) == 0);
    return ret;
  }

  int Put(const char &symbol) {
    file_.put(symbol);
    return 0;
  }

  static bool Copy(std::string infile, std::string outfile) {
    FIO in(infile);
    FIO out(outfile, std::ios::out, std::ios::binary);
    auto retInOpen = in.Open();
    if (retInOpen != RETURN_OK) {
      std::cerr << "Error input file not open" << std::endl;
      return UNSPECIFIED_ERROR;
    }
    auto retReadOpen = in.Read();
    if (retInOpen != RETURN_OK) {
      std::cerr << "Error input file not read" << std::endl;
      return UNSPECIFIED_ERROR;
    }
    auto retOutOpen = out.Open();
    if (retInOpen != RETURN_OK) {
      std::cerr << "Error output file not open" << std::endl;
      return UNSPECIFIED_ERROR;
    }
    auto retOutWrite = out.Write(in.buffer);
    if (retInOpen != RETURN_OK) {
      std::cerr << "Error output file not open" << std::endl;
      return UNSPECIFIED_ERROR;
    }

    in.Close();
    out.Close();

    return RETURN_OK;
  }

  size_t Size() { return this->file_.tellg(); }
  T Data() const { return buffer; }

  bool IsOpen() { return file_.is_open(); }
  bool IsEOF() { return file_.eof(); }

 private:
  std::fstream file_;
  std::string path_;
  std::ios::openmode modeOpen_;
  std::ios::openmode typeOpen_;
  T buffer;
};

}  // namespace fio
#endif  // FIO_H
