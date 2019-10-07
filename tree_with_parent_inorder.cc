#include <vector>
#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree) return {};
  vector<int> result;

  for (auto node = tree.get();;) {
    if (node->left) node = node->left.get();
    else {
      while (node && !node->right) {
        result.push_back(node->data);
        auto parent = node->parent;

        while (parent && parent->right.get() == node) {
          node = parent;
          parent = node->parent;
        }

        node = parent;
      }

      if (!node) break;
      result.push_back(node->data);
      node = node->right.get();
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
