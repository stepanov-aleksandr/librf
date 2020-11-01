#ifndef PACKED_H
#define PACKED_H

#include <iostream>
#include <string>
#include "config.h"

class IDPacked {
 public:
  IDPacked() {}
  IDPacked(const size_t &id_messeng, const size_t &id_packed)
      : id_messeng_(id_messeng), id_packed_(id_packed) {}

  static const std::string PackField(const std::string &type,
                                     const uint64_t &value) {
    return std::string{type + "=" + std::to_string(value) + ";"};
  }

  const std::string Data() {
    return PackField(TypeField.kIdMesseng, id_messeng_) +
           PackField(TypeField.kNumPacked, id_packed_);
  }

  size_t id_messeng_{0};
  size_t id_packed_{0};
};

class Packed {
 public:
  Packed(const IDPacked &id, const std::string &data);
  Packed(const size_t &id_messeng, const size_t &id_packed,
         const std::string &data);

  std::string &Data();
  IDPacked &ID();

  friend bool operator<(const Packed &lhs, const Packed &rhs);
  friend std::ostream &operator<<(std::ostream &out, const Packed &packed);

 private:
  IDPacked id_;
  std::string data_;
};

#endif  // PACKED_H
