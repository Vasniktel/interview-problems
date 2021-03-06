#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

bool MatrixSearch(const vector<vector<int>>& A, int x) {
  if (A.empty()) return false;

  int rows = A.size(), cols = A[0].size();
  int row = rows - 1, col = 0;

  while (row >= 0 && col < cols) {
    if      (A[row][col] > x) row--;
    else if (A[row][col] < x) col++;
    else return true;
  }

  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "x"};
  return GenericTestMain(args, "search_row_col_sorted_matrix.cc",
                         "search_row_col_sorted_matrix.tsv", &MatrixSearch,
                         DefaultComparator{}, param_names);
}
