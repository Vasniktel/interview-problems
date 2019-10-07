#include <memory>
#include <vector>
#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
using std::vector;

unique_ptr<BstNode<int>> recur(const vector<int>& arr, int lo, int hi) {
  if (hi < lo) return nullptr;
  if (hi == lo) return std::make_unique<BstNode<int>>(arr[lo]);

  int mid = lo + (hi - lo) / 2;
  return std::make_unique<BstNode<int>>(arr[mid], recur(arr, lo, mid - 1), recur(arr, mid + 1, hi));
}

unique_ptr<BstNode<int>> BuildMinHeightBSTFromSortedArray(
    const vector<int>& A) {
  return recur(A, 0, static_cast<int>(A.size()) - 1);
}
int BuildMinHeightBSTFromSortedArrayWrapper(TimedExecutor& executor,
                                            const vector<int>& A) {
  unique_ptr<BstNode<int>> result =
      executor.Run([&] { return BuildMinHeightBSTFromSortedArray(A); });

  if (GenerateInorder(result) != A) {
    throw TestFailure("Result binary tree mismatches input array");
  }
  return BinaryTreeHeight(result);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "bst_from_sorted_array.cc",
                         "bst_from_sorted_array.tsv",
                         &BuildMinHeightBSTFromSortedArrayWrapper,
                         DefaultComparator{}, param_names);
}
