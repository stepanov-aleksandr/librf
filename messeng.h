#ifndef MESSENG_H
#define MESSENG_H

#include <set>
#include <vector>

#include "config.h"
#include "packed.h"

class IDMessang {
 public:
  uint64_t id_messeng{0};  /// < идентификатор пакета
  uint64_t num_packed{0};  /// < число пакетов в сообщении
  uint64_t size_packed{MAX_SIZE_PACKED};  /// < размер пакета

  const std::string PackField(std::string type, const uint64_t& value) {
    return std::string{type + "=" + std::to_string(value) + ";"};
  }

  const std::string Data() {
    return PackField(TypeField.kIdMesseng, id_messeng) +
           PackField(TypeField.kNumPacked, num_packed) +
           PackField(TypeField.kSizePacked, size_packed) + "\n\0";
  }
};

class MessengRF {
 public:
  MessengRF();
  MessengRF(const Packed& packed);
  MessengRF(const std::string& data);

  std::set<Packed>& GetPacked();
  std::ostream& PrintPacked(const MessengRF& messeng);
  const std::string GetMesseng();
  void AddPacked(const Packed& packed);

  IDMessang& ID();

  size_t Size();
  friend std::ostream& operator<<(std::ostream& out, const MessengRF& messeng);

 private:
  IDMessang id_;
  size_t SplitMesseng(const std::string& data);
  std::set<Packed> packeds_;
};

class Header {
 public:
  Header() {}
  Header(uint8_t number_messeng, uint8_t number_packed, uint8_t number_packeds,
         uint8_t size_packed)
      : number_messeng_(number_messeng),
        number_packed_(number_packed),
        number_packeds_(number_packeds),
        size_packed_(size_packed) {}

  size_t Size() { sizeof(*this); }

  uint8_t number_messeng_{0};  ///< номер сообщения
  uint8_t number_packed_{0};   ///< номер пакета
  uint8_t number_packeds_{0};  /// < число пакетов на который разбито сообщение
  uint8_t size_packed_{0};  /// < размер пакета сообщения
};

class Packed_ {
 public:
  Packed_() {}
  Packed_(const Header& header, const std::vector<uint8_t>& data)
      : header_(header), data_(data) {}
  std::vector<uint8_t> Data() {
    std::vector<uint8_t> out;
    out.push_back(header_.number_messeng_);
    out.push_back(header_.number_packed_);
    out.push_back(header_.number_packeds_);
    out.push_back(header_.size_packed_);
    out.insert(out.end(), data_.begin(), data_.end());
    return out;
  }

  std::vector<uint8_t> Data_() { return data_; }
  Header Header_() { return header_; }

  size_t Size() { return sizeof(Header) + data_.size(); }

  friend bool operator<(const Packed_& lhs, const Packed_& rhs);

 private:
  Header header_;
  std::vector<uint8_t> data_;
};

template <class Type>
class Messeng_ {
 public:
  Messeng_() {}
  Messeng_(const Type& data, int number) : data_(data), number_(number) {}
  Messeng_(const std::set<Packed_>& packeds, const int& number)
      : number_(number) {
    std::set<Packed_> packeds_;
    for (auto& packed : packeds) {
      packeds_.insert(const_cast<Packed_&>(packed));
    }

    for (auto unit : packeds_) {
      auto i = unit.Data_();
      data_.append({i.begin(), i.end()});
    }
  }

  int PushPacked(Packed_& packed) {
    auto i = packed.Data_();
    data_.append({i.begin(), i.end()});
    return 0;
  }

  const std::vector<Packed_> SplitPacked(const Type& data) {
    auto num_full_pack = (data.size() + sizeof(Header)) / (MAX_SIZE_PACKED)-1;
    if (num_full_pack == 0) {
      Packed_ pkg({number_, 1, 1, MAX_SIZE_PACKED}, {data.begin(), data.end()});
      return {pkg};
    }

    uint8_t num_pack = num_full_pack;

    if (((data.size() + sizeof(Header)) % MAX_SIZE_PACKED) == false) {
      num_pack++;
    }

    auto start = data.begin();

    std::vector<Packed_> packeds_;
    auto cp = 1;
    for (; start < data.begin() + MAX_SIZE_PACKED * num_full_pack;
         start += MAX_SIZE_PACKED) {
      packeds_.push_back({{number_, cp++, num_pack, MAX_SIZE_PACKED},
                          {start, start + MAX_SIZE_PACKED}});
    }
    if (start < data.end()) {
      packeds_.push_back(
          {{number_, cp, num_pack, data.end() - start}, {start, data.end()}});
    }
    return packeds_;
  }

  std::vector<Packed_> GetRaw() {
    auto ret = SplitPacked(data_);
    return ret;
  }

  Type Messeng() { return data_; }

  friend bool operator<(const Messeng_& lhs, const Messeng_& rhs);

 private:
  uint8_t number_{1};
  Type data_;
};

#endif  // MESSENG_H
