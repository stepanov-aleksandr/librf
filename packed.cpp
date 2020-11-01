#include "packed.h"

bool operator<(const Packed &lhs, const Packed &rhs) {
  return lhs.id_.id_packed_ < rhs.id_.id_packed_;
}

Packed::Packed(const IDPacked &id, const std::string &data) {
  id_.id_messeng_ = id.id_messeng_;
  id_.id_packed_ = id.id_packed_;
  data_ = data;
}

std::string &Packed::Data() { return data_; }

IDPacked &Packed::ID() { return id_; }

std::ostream &operator<<(std::ostream &out, const Packed &packed) {
  out << "Packed" << std::endl;
  out << "Messeng ID[" << packed.id_.id_messeng_ << "]" << std::endl;
  out << "Number packed[" << packed.id_.id_packed_ << "]" << std::endl;
  return out;
}
