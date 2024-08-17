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
public:
  int diameterOfBinaryTree(TreeNode *root) {
    int result = 0;
    if (root) {
      // capture result by reference
      auto dfs = [result](auto &self, TreeNode *node) mutable {
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

  bool isBalanced(TreeNode *root) {
    function<int(TreeNode *)> dfs = [&dfs](auto node) mutable {
      if (!node)
        return 0;
      int left = dfs(node->left);
      int right = dfs(node->right);
      if (abs(left - right) > 1 || left == -1 || right == -1)
        return -1;
      return 1 + max(left, right);
    };
    return dfs(root) != -1;
  }

  bool isSameTree(TreeNode *p, TreeNode *q) {
    if (!p || !q)
      return p == q;
    return p->val == q->val && isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
  }
};