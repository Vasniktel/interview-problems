#include "test_framework/generic_test.h"
unsigned long long ReverseBits(unsigned long long x) {
  constexpr auto kSize = sizeof(x) * 8;

  auto result = 0ull;

  for (int i = 0; i < kSize; ++i) {
    result <<= 1u;
    result |= x & 1u;
    x >>= 1u;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
