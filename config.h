#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <memory>

constexpr int MAX_SIZE_PACKED = 3;  ///< максимальный размер пакета

const struct {
  const std::string kIdMesseng = "idm";
  const std::string kNumPacked = "np";
  const std::string kSizePacked = "sp";
  const std::string kData = "data";
} TypeField;

#endif  // CONFIG_H
