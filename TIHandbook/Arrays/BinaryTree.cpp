/**
 * Definition for a binary tree node.
 */
#include <algorithm>
#include <functional>
#include <queue>
#include <ranges>
#include <stack>
#include <vector>

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

  bool isSubtree(TreeNode *root, TreeNode *subRoot) {
    if (!root)
      return false;
    function<bool(TreeNode *, TreeNode *)> isSame = [&isSame](auto p, auto q) {
      if (!p || !q)
        return p == q;
      return p->val == q->val && isSame(p->left, q->left) &&
             isSame(p->right, q->right);
    };
    return isSame(root, subRoot) || isSubtree(root->left, subRoot) ||
           isSubtree(root->right, subRoot);
  }

  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (!root || root == p || root == q)
      return root;
    vector<TreeNode *> pathP, pathQ;
    function<vector<TreeNode *>(TreeNode *, TreeNode *)> findPath =
        [&findPath](auto node, auto target) {
          //
          auto path = vector<TreeNode *>();
          if (!node)
            return path;
          if (node == target) {
            path.push_back(node);
            return path;
          }
          auto left = findPath(node->left, target);
          auto right = findPath(node->right, target);
          if (!left.empty()) {
            path.push_back(node);
            path.insert(path.end(), left.begin(), left.end());
          } else if (!right.empty()) {
            path.push_back(node);
            path.insert(path.end(), right.begin(), right.end());
          }
          return path;
        };
    pathP = findPath(root, p);
    pathQ = findPath(root, q);

    for (int i = 0; i < min(pathP.size(), pathQ.size()); i++) {
      if (pathP[i] != pathQ[i])
        return pathP[i - 1];
    }

    return pathP.back();
  }

  vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> result;
    if (!root)
      return result;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      int size = q.size();
      vector<int> level;
      for (int i = 0; i < size; i++) {
        auto node = q.front();
        q.pop();
        level.push_back(node->val);
        if (node->left)
          q.push(node->left);
        if (node->right)
          q.push(node->right);
      }
      result.push_back(level);
    }
    return result;
  }

  vector<int> rightSideView(TreeNode *root) {
    vector<int> result;
    if (!root)
      return result;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      int size = q.size();
      for (int i = 0; i < size; i++) {
        auto node = q.front();
        q.pop();
        if (i == size - 1)
          result.push_back(node->val);
        if (node->left)
          q.push(node->left);
        if (node->right)
          q.push(node->right);
      }
    }
    return result;
  }

  int goodNodes(TreeNode *root) {
    // Node X is good if X is the maximum value in its path from the root to X.
    function<int(TreeNode *, int)> dfs = [&dfs](auto node, int maxVal) {
      if (!node)
        return 0;
      int good = node->val >= maxVal;
      maxVal = max(maxVal, node->val);
      return good + dfs(node->left, maxVal) + dfs(node->right, maxVal);
    };

    return !root ? 0 : dfs(root, root->val);
  }

  bool isValidBST(TreeNode *root) {
    function<bool(TreeNode *, long, long)> dfs = [&dfs](auto node, long min,
                                                        long max) {
      if (!node)
        return true;
      if (node->val <= min || node->val >= max)
        return false;
      return dfs(node->left, min, node->val) &&
             dfs(node->right, node->val, max);
    };
    return dfs(root, LONG_MIN, LONG_MAX);
  }

  int kthSmallest(TreeNode *root, int k) {
    // function<int(TreeNode *)> dfs = [&dfs, &k](TreeNode *node) {
    //   if (!node)
    //     return 0;
    //   auto left = dfs(node->left);
    //   if (left)
    //     return left;
    //   if (--k == 0)
    //     return node->val;
    //   return dfs(node->right);
    // };
    // return dfs(root);
    stack<TreeNode *> s;
    s.push(root);
    while (!s.empty()) {
      while (root) {
        s.push(root);
        root = root->left;
      }
      root = s.top();
      s.pop();
      if (--k == 0)
        return root->val;
      root = root->right;
    }
    return 0;
  }

  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    function<TreeNode *(int, int, int, int)> build = [&](int preStart,
                                                         int inStart, int inEnd,
                                                         int n) {
      if (n == 0)
        return (TreeNode *)nullptr;
      auto root = new TreeNode(preorder[preStart]);
      int i = inStart;
      while (inorder[i] != preorder[preStart])
        i++;
      root->left = build(preStart + 1, inStart, i - 1, i - inStart);
      root->right = build(preStart + i - inStart + 1, i + 1, inEnd, inEnd - i);
      return root;
    };
    return build(0, 0, inorder.size() - 1, inorder.size());
  }
};