# Score conversion regression

The canonical exponential-search path used `atoi` on an MSB-first binary digit
string, then reinterpreted the decimal digits as binary. For `11111111111`, the
binary score is only 2047, but the decimal intermediate is 11,111,111,111, beyond
a 32-bit signed integer. The old conversion therefore had undefined overflow
behavior before binary reconstruction even began.

The replacement accumulates base-two digits directly, checking the signed-int
limit before multiplication/addition. Empty/non-binary input throws
`std::invalid_argument`; an unrepresentable score throws `std::overflow_error`.
Leading zeros are accepted. The existing LSB-to-MSB reversal is unchanged.

Reproduce the independent regression checks without XACC or a simulator:

```sh
c++ -std=c++17 -O1 -DNDEBUG -Wall -Wextra -Werror -fsanitize=address,undefined -Iinclude tests/algorithms/exponential_search/ScoreDecodingStandalone.cpp -o /tmp/search-score-checks
/tmp/search-score-checks
```

4,110 checks passed on macOS arm64 with Apple clang 17, AddressSanitizer and
UndefinedBehaviorSanitizer. Tests use a standard-library bitset encoder for all
4096 small integers and check larger values, padding and invalid/overflow inputs.
A lightweight Linux workflow runs the same production helper. The initial host
compile failed on a copy-in-range-loop warning under `-Werror`; changing that loop
to a const reference resolved it. The initial full-source syntax check required
the existing CMake bundle-name define; the corrected check passed with
`US_BUNDLE_NAME=algorithm_es_plugin_bundle` and the documented libc++ legacy
function compatibility switch.

This is arithmetic regression coverage, not a linked XACC run, plugin rebuild or
full Decoder correctness proof. Native integration remains deferred while the
managed-platform release lane uses shared Docker. Do not advance runtime source
locks or claim distributed-image coverage until that qualification succeeds.
