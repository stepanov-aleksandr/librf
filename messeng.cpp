#include "messeng.h"

MessengRF::MessengRF() {}

MessengRF::MessengRF(const Packed& packed) { packeds_.insert(packed); }

MessengRF::MessengRF(const std::string& data) { SplitMesseng(data); }

std::set<Packed>& MessengRF::GetPacked() { return packeds_; }

std::ostream& MessengRF::PrintPacked(const MessengRF& messeng) {
  std::cout << "Messeng[" << messeng.id_.id_messeng << "]" << std::endl;
  std::cout << "size[" << messeng.id_.num_packed << "]" << std::endl
            << std::endl;
  for (const auto& unit : messeng.packeds_) {
    std::cout << unit << std::endl;
  }
  return std::cout;
}

const std::string MessengRF::GetMesseng() {
  std::string out;

  for (const auto& unit : packeds_) {
    out.append(const_cast<Packed&>(unit).Data());
  }
  return out;
}

void MessengRF::AddPacked(const Packed& packed) { packeds_.insert(packed); }

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

bool operator<(const Packed_& lhs, const Packed_& rhs) {
  return lhs.header_.number_packed_ < rhs.header_.number_packed_;
}
