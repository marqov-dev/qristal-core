#include <qristal/core/algorithms/exponential_search/score_decoding.hpp>
#include <bitset>
#include <iostream>
#include <limits>
#include <stdexcept>

int main() {
  int checks = 0;
  auto check = [&](bool ok) {
    ++checks;
    if (!ok) throw std::runtime_error("Score decoding check failed");
  };
  // Independent standard-library encoder, exhaustive small scores with padding.
  for (int value = 0; value < 4096; ++value)
    check(qristal::detail::decode_search_score(std::bitset<16>(value).to_string()) == value);
  check(qristal::detail::decode_search_score("11111111111") == 2047);
  check(qristal::detail::decode_search_score("10000000001") == 1025);
  check(qristal::detail::decode_search_score("000000") == 0);
  check(qristal::detail::decode_search_score("10110") == 22);
  const int digits = std::numeric_limits<int>::digits;
  check(qristal::detail::decode_search_score(std::string(digits, '1')) == std::numeric_limits<int>::max());
  check(qristal::detail::decode_search_score(std::string(100, '0') + "1") == 1);
  for (const std::string bits : {"", "2", "10x1", "-1", " 1", "1 "}) {
    bool rejected = false;
    try { qristal::detail::decode_search_score(bits); }
    catch (const std::invalid_argument&) { rejected = true; }
    check(rejected);
  }
  for (const std::string& bits : {"1" + std::string(digits, '0'), std::string(digits+1, '1')}) {
    bool rejected = false;
    try { qristal::detail::decode_search_score(bits); }
    catch (const std::overflow_error&) { rejected = true; }
    check(rejected);
  }
  std::cout << "PASS: " << checks << " exponential-search score checks\n";
}
