/**
 * Definition for a binary tree node.
 */
#include <functional>
using namespace std;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};
class Solution {
private:
  int result = 0;

public:
  int diameterOfBinaryTree(TreeNode *root) {
    if (root) {
      // capture result by reference
      auto dfs = [this](auto &self, TreeNode *node) {
        if (!node)
          return 0;
        int left = self(self, node->left);
        int right = self(self, node->right);

        result = max(result, left + right);
        return 1 + max(left, right);
      };
      dfs(dfs, root);
    }
    return result;
  }

  bool isBalanced(TreeNode *root) {}
};