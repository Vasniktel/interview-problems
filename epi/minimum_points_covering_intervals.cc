#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Interval {
  int left, right;
};

int FindMinimumVisits(vector<Interval> intervals) {
  if (intervals.empty()) return 0;
  std::sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
    return a.right < b.right;
  });

  int result = 1, end = intervals.front().right;
  for (int i = 1, n = intervals.size(); i < n; ++i) {
    if (intervals[i].left > end) {
      result++;
      end = intervals[i].right;
    }
  }

  return result;
}
template <>
struct SerializationTraits<Interval> : UserSerTraits<Interval, int, int> {};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"intervals"};
  return GenericTestMain(args, "minimum_points_covering_intervals.cc",
                         "minimum_points_covering_intervals.tsv",
                         &FindMinimumVisits, DefaultComparator{}, param_names);
}
