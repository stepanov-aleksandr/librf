#ifndef MESSENG_H
#define MESSENG_H

#include <set>
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

#endif  // MESSENG_H
