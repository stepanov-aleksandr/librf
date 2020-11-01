#include "messeng.h"

MessengRF::MessengRF() {}

MessengRF::MessengRF(const Packed& packed) { packeds_.insert(packed); }

MessengRF::MessengRF(const std::string& data) { SplitMesseng(data); }

std::set<Packed>& MessengRF::Data() { return packeds_; }
IDMessang& MessengRF::ID() { return id_; }

size_t MessengRF::Size() { return packeds_.size(); }

size_t MessengRF::SplitMesseng(const std::string& data) {
  auto num_packed = data.size() / MAX_SIZE_PACKED;
  auto start = data.begin();

  while (start < data.begin() + num_packed * MAX_SIZE_PACKED) {
    packeds_.insert(
        {{id_.id_messeng, id_.num_packed++}, {start, start + MAX_SIZE_PACKED}});
    start += MAX_SIZE_PACKED;
  }
  if (start != data.end()) {
    packeds_.insert({{id_.id_messeng, id_.num_packed++}, {start, data.end()}});
  }
  return 0;
}

std::ostream& operator<<(std::ostream& out, const MessengRF& messeng) {
  out << "Messeng[" << messeng.id_.id_messeng << "]" << std::endl;
  out << "size[" << messeng.id_.num_packed << "]" << std::endl << std::endl;
  for (const auto& unit : messeng.packeds_) {
    out << unit << std::endl;
  }
  return out;
}
