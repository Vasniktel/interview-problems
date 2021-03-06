#include <string>
#include "test_framework/generic_test.h"
using std::string;

bool IsPalindrome(const string& s) {
  int lo = 0, hi = s.size() - 1;

  while (true) {
    while (!isalnum(s[lo])) lo++;
    while (!isalnum(s[hi])) hi--;
    if (lo > hi) break;
    if (tolower(s[lo]) != tolower(s[hi])) return false;
    lo++;
    hi--;
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
