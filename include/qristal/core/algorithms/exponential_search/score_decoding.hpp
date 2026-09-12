#pragma once

#include <limits>
#include <stdexcept>
#include <string>

namespace qristal::detail {

// Input is MSB-first. Do not parse the binary digits as a decimal integer:
// that intermediate can overflow even when the binary value fits in int.
inline int decode_search_score(const std::string& bits) {
  if (bits.empty()) throw std::invalid_argument("Empty exponential-search score");
  int value = 0;
  for (char bit : bits) {
    if (bit != '0' && bit != '1')
      throw std::invalid_argument("Non-binary exponential-search score");
    const int digit = bit - '0';
    if (value > (std::numeric_limits<int>::max() - digit) / 2)
      throw std::overflow_error("Exponential-search score exceeds int range");
    value = value * 2 + digit;
  }
  return value;
}
}
