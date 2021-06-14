#include <vector>

#define null NULL  // NULL定义在标准库中值为0的常量

struct TreeNode {
  int val;  // val > 0
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode *getTreeNode(std::vector<int> str) {
  TreeNode *root = new TreeNode(str[0]);
  std::vector<TreeNode *> vecs;
  vecs.push_back(root);
  for (int i = 1; i < str.size(); i++) {
    if (str[i] != NULL) {
      TreeNode *n1 = new TreeNode(str[i]);
      if (i % 2 == 1)  // left
      {
        vecs[(i - 1) / 2]->left = n1;
      } else {
        vecs[(i - 1) / 2]->right = n1;
      }
      vecs.push_back(n1);
    } else {
      vecs.push_back(nullptr);
    }
  }
  return root;
}

int main() {
  std::vector<int> vi{3, 5, 1, 6, 2, 8, null, null, 7, 4};

  auto root = getTreeNode(vi);

  return 0;
}
