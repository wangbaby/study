https://light-city.club/sc/
https://github.com/huihut/interview
https://github.com/0voice/interview_internal_reference
https://github.com/linw7/Skill-Tree



leetcode-147. 对链表进行插入排序

//对链表进行插入排序。 
//
// 
//插入排序的动画演示如上。从第一个元素开始，该链表可以被认为已经部分排序（用黑色表示）。 
//每次迭代时，从输入数据中移除一个元素（用红色表示），并原地将其插入到已排好序的链表中。 
//
// 
//
// 插入排序算法： 
//
// 
// 插入排序是迭代的，每次只移动一个元素，直到所有元素可以形成一个有序的输出列表。 
// 每次迭代中，插入排序只从输入数据中移除一个待排序的元素，找到它在序列中适当的位置，并将其插入。 
// 重复直到所有输入数据插入完为止。 
// 
//
// 
//
// 示例 1： 
//
// 输入: 4->2->1->3
//输出: 1->2->3->4
// 
//
// 示例 2： 
//
// 输入: -1->5->3->4->0
//输出: -1->0->3->4->5
// 
// Related Topics 链表 排序 
// 👍 405 👎 0


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {

    }
};
//leetcode submit region end(Prohibit modification and deletion)


#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x = 0, ListNode *next = nullptr) : val(x), next(next) {}
};

ListNode *createLinkedList(int *arr, size_t n) {
  if (n == 0)
    return nullptr;

  ListNode *head = new ListNode(arr[0]);
  ListNode *cur = head;
  for (int i = 1; i < n; i++) {
    cur->next = new ListNode(arr[i]);
    cur = cur->next;
  }

  return head;
}

void printLinkedList(ListNode *head) {
  while (head) {
    std::cout << head->val << " -> ";
    head = head->next;
  }

  std::cout << " NULL " << std::endl;
}

void deleteLinkedList(ListNode *head) {
  while (head) {
    ListNode *cur = head;
    head = cur->next;
    delete cur;
  }
}
/**
 * 设立链表的虚拟头结点
 */
class Solution {
public:
  ListNode *insertionSortList(ListNode *head) {
    if (head == NULL || head->next == NULL)
      return head;

    ListNode *p = head->next;
    ListNode *dummpHead = new ListNode(0), *pend = head;
    dummpHead->next = head;

    while (p) {
      ListNode *tmp = dummpHead->next, *pre = dummpHead;
      while (tmp != p && p->val >= tmp->val) //找到插入位置
      {
        tmp = tmp->next;
        pre = pre->next;
      }
      if (tmp == p)
        pend = p;
      else {
        pend->next = p->next;
        p->next = tmp;
        pre->next = p;
      }
      p = pend->next;
    }

    head = dummpHead->next;
    delete dummpHead;
    return head;
  }
};

int main() {
  int arr[]{2, 1, 3, 5, 4};
  int n = sizeof(arr) / sizeof(int);

  ListNode *head = createLinkedList(arr, n);
  printLinkedList(head);

  head = Solution().insertionSortList(head);
  printLinkedList(head);

  deleteLinkedList(head);

  return 0;
}
leetcode-143. 重排链表

//给定一个单链表 L：L0→L1→…→Ln-1→Ln ， 
//将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→… 
//
// 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。 
//
// 示例 1: 
//
// 给定链表 1->2->3->4, 重新排列为 1->4->2->3. 
//
// 示例 2: 
//
// 给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3. 
// Related Topics 栈 递归 链表 双指针 
// 👍 610 👎 0


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {

    }
};
//leetcode submit region end(Prohibit modification and deletion)


#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x = 0, ListNode *next = nullptr) : val(x), next(next) {}
};

ListNode *createLinkedList(int *arr, size_t n) {
  if (n == 0)
    return nullptr;

  ListNode *head = new ListNode(arr[0]);
  ListNode *cur = head;
  for (int i = 1; i < n; i++) {
    cur->next = new ListNode(arr[i]);
    cur = cur->next;
  }

  return head;
}

void printLinkedList(ListNode *head) {
  while (head) {
    std::cout << head->val << " -> ";
    head = head->next;
  }

  std::cout << " NULL " << std::endl;
}

void deleteLinkedList(ListNode *head) {
  while (head) {
    ListNode *cur = head;
    head = cur->next;
    delete cur;
  }
}

class Solution {
public:
  void reorderList(ListNode *head) {
    // 链表为空或者只有一个结点
    while (!head || !head->next)
      return;

    // 找到中间结点
    ListNode *mid, *quick = head, *slow = head;
    while (quick->next && quick->next->next) {
      quick = quick->next->next;
      slow = slow->next;
    }
    mid = slow->next;
    slow->next = nullptr;

    // 对后半部分链表反转
    ListNode *temp = mid;
    while (temp->next) {
      ListNode *cur = temp->next;
      temp->next = cur->next;
      cur->next = mid;
      mid = cur;
    }

    // 合并两个链表
    temp = head;
    ListNode *node1, *node2;
    while (temp && mid) {
      node1 = temp->next;
      node2 = mid->next;
      temp->next = mid;
      mid->next = node1;
      temp = node1;
      mid = node2;
    }

    // 对剩余部分进行处理
    if (node1 && !node1->next) {
      node1->next = node2;
      return;
    }
    if (node2 && !node2->next) {
      node2->next = node1;
      return;
    }
  }
};

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  int n = sizeof(arr) / sizeof(int);
  ListNode *head = createLinkedList(arr, n);
  Solution().reorderList(head);
  printLinkedList(head);

  return 0;
}
nowcoder-逆时针打印二叉树边界节点



题目
给定一棵完全二叉树，返回最后一层的最右边的节点。

思路
层次遍历，用一个last变量记录每次出队列的值，遍历结束之后last变量记录的就是所求节点。时间、空间复杂度都是O(N)。

递归，求子树的高度：如果当前根节点为叶子节点，则返回；如果左子树高度>右子树高度，则在左子树继续递归过程；否则在右子树继续递归。由于是完全二叉树，求高度时只需一直往左遍历即可。每次递归都下降一层，每次都求树的高度，时间复杂度为O(lgN * lgN)

/*
 * 递归
 * 求子树高度：如果当前根节点为叶子节点，则返回
 * 如果左子树高度>右子树高度，则在左子树递归
 * 否则在右子树递归
 * 时间复杂度O(logN * logN) （求高度 * 遍历层数）
 */
class Solution {
public:
    TreeNode* getLastNode(TreeNode* root) {
        if(!root || root->left == nullptr)
            return root;
        int leftHeight = 0;     // 左子树高度
        TreeNode *node = root->left;
        while (node){
            node = node->left;
            ++ leftHeight;
        }

        int rightHeight = 0;    // 右子树高度
        node = root->right;
        while(node){
            node = node->left;
            ++ rightHeight;
        }

        if(leftHeight > rightHeight)
            return getLastNode(root->left);
        else
            return getLastNode(root->right);
    }
};





Input
整个输入有两行，第一行给出前序遍历的访问顺序，第二行给出后序遍历的访问顺序。
二叉树的结点用一个大写字母表示，不会有两个结点标上相同字母。输入数据不包含空格，且保证至少有一棵二叉树符合要求。
Output
输出一个整数，为符合要求的不同形态二叉树的数目。
Sample Input
ABCD
CBDA

Sample Output
2

/*
如果只知道二叉树的前序遍历结果与后序遍历结果，是无法确定唯一的二叉树
我们注意到的是，当一结点只有一个孩子时，无论他是左孩子还是右孩子，他们的前序遍历与后序遍历结果都是一样的
这就是无法唯一确定的原因，一棵树中有多少个这种情况，就会有2*^多少种中序遍历结果
现在就要找前序遍历为AB，后序遍历为BA的情况
*/
#include<iostream>
#include<string>
using namespace std;
 
int main()
{
    string pre,post;
    cin>>pre>>post;
 
    int count=1;
 
    int temp=post.size()-1;     //对于前序遍历与后序遍历，前序的第一个结点与后序的最后一个结点是一样的
    int size=post.size();
 
    for(int i=1;i<size;i++)
    {
        int j=post.find(pre[i]);
        if(j==temp-1)count*=2;
        temp=j;
    }
 
    cout<<count;
 
    return 0;
}

 



leetcode-236. 二叉树的最近公共祖先

//给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。 
//
// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（
//一个节点也可以是它自己的祖先）。” 
//
// 
//
// 示例 1： 
//
// 
//输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
//输出：3
//解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
// 
//
// 示例 2： 
//
// 
//输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
//输出：5
//解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
// 
//
// 示例 3： 
//
// 
//输入：root = [1,2], p = 1, q = 2
//输出：1
// 
//
// 
//
// 提示： 
//
// 
// 树中节点数目在范围 [2, 105] 内。 
// -109 <= Node.val <= 109 
// 所有 Node.val 互不相同 。 
// p != q 
// p 和 q 均存在于给定的二叉树中。 
// 
// Related Topics 树 深度优先搜索 二叉树 
// 👍 1185 👎 0


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
    }
};
//leetcode submit region end(Prohibit modification and deletion)


class Solution {
public:
    unordered_map<int, TreeNode*> fa;
    unordered_map<int, bool> vis;
    void dfs(TreeNode* root){
        if (root->left != nullptr) {
            fa[root->left->val] = root;
            dfs(root->left);
        }
        if (root->right != nullptr) {
            fa[root->right->val] = root;
            dfs(root->right);
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        fa[root->val] = nullptr;
        dfs(root);
        while (p != nullptr) {
            vis[p->val] = true;
            p = fa[p->val];
        }
        while (q != nullptr) {
            if (vis[q->val]) return q;
            q = fa[q->val];
        }
        return nullptr;
    }
};


时间复杂度：O(N)，其中 N 是二叉树的节点数。二叉树的所有节点有且只会被访问一次，从 p 和 q 节点往上跳经过的祖先节点个数不会超过 N，因此总的时间复杂度为 O(N)。

空间复杂度：O(N) ，其中 N 是二叉树的节点数。递归调用的栈深度取决于二叉树的高度，二叉树最坏情况下为一条链，此时高度为 N，因此空间复杂度为 O(N)，哈希表存储每个节点的父节点也需要O(N) 的空间复杂度，因此最后总的空间复杂度为 O(N)



leetcode-235. 二叉搜索树的最近公共祖先



//给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。 
//
// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（
//一个节点也可以是它自己的祖先）。” 
//
// 例如，给定如下二叉搜索树: root = [6,2,8,0,4,7,9,null,null,3,5] 
//
// 
//
// 
//
// 示例 1: 
//
// 输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
//输出: 6 
//解释: 节点 2 和节点 8 的最近公共祖先是 6。
// 
//
// 示例 2: 
//
// 输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
//输出: 2
//解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。 
//
// 
//
// 说明: 
//
// 
// 所有节点的值都是唯一的。 
// p、q 为不同节点且均存在于给定的二叉搜索树中。 
// 
// Related Topics 树 深度优先搜索 二叉搜索树 二叉树 
// 👍 612 👎 0


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
    }
};
//leetcode submit region end(Prohibit modification and deletion)

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right, p, q);
        else if(p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);
        else
            return root;
    }
};
leetcode-416. 分割等和子集
 
//给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。 
//
// 
//
// 示例 1： 
//
// 
//输入：nums = [1,5,11,5]
//输出：true
//解释：数组可以分割成 [1, 5, 5] 和 [11] 。 
//
// 示例 2： 
//
// 
//输入：nums = [1,2,3,5]
//输出：false
//解释：数组不能分割成两个元素和相等的子集。
// 
//
// 
//
// 提示： 
//
// 
// 1 <= nums.length <= 200 
// 1 <= nums[i] <= 100 
// 
// Related Topics 数组 动态规划 
// 👍 854 👎 0
 
 
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool canPartition(vector<int>& nums) {
 
    }
};
//leetcode submit region end(Prohibit modification and deletion)
 
 
class Solution {
public:
  bool canPartition(vector<int> &nums) {
    int sum = 0;
    int n = nums.size();
    for (auto i : nums) {
      sum += i;
    }
    if ( sum % 2)
      return false;
 
    int half = sum / 2;
 
    vector<bool> memo(half + 1, false);
    for (int i = 0; i <= half; i++)
      memo[i] = nums[0] == i ? true : false;
 
    for (int i = 1; i < n; i++) {
      for (int j = half; j >= nums[i]; j--) {
        memo[j] = memo[j] || memo[j - nums[i]];
      }
    }
 
    return memo[half];
  }
};
 leetcode-509. 斐波那契数
 dp


int fib(int n){
    vector<int> dp(n+1, -1);
    dp[0] = 0; 
    dp[1] = 1;
    for(int i = 2; i < n; i++)
        dp[n] = dp[n - 1] + dp[n - 2];
    
    return dp[n];
}


模板元编程
template<int N>
struct Fibonacci
{
    enum{ Value = Fibonacci<N - 1>::Value + Fibonacci<N - 2>::Value };
};

template<> struct Fibonacci<0>
{
    enum{ Value = 0 };
};

template<> struct Fibonacci<1>
{
    enum{ Value = 1 };
};

#define __fib(...) Fibonacci<__VA_ARGS__>::Value

template<int N>
int _fibonacci(int i)
{
    if (i == N) return __fib(N);
    else return _fibonacci<(N < 30 ? N + 1 : 0)>(i);
}

int fibonacci(int i)
{
    return _fibonacci<0>(i);
}

class Solution
{
public:
    int fib(int N)
    {
        return fibonacci(N);
    }
};

leetcode-53. 最大子序和


//给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。 
//
// 
//
// 示例 1： 
//
// 
//输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
//输出：6
//解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
// 
//
// 示例 2： 
//
// 
//输入：nums = [1]
//输出：1
// 
//
// 示例 3： 
//
// 
//输入：nums = [0]
//输出：0
// 
//
// 示例 4： 
//
// 
//输入：nums = [-1]
//输出：-1
// 
//
// 示例 5： 
//
// 
//输入：nums = [-100000]
//输出：-100000
// 
//
// 
//
// 提示： 
//
// 
// 1 <= nums.length <= 3 * 104 
// -105 <= nums[i] <= 105 
// 
//
// 
//
// 进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。 
// Related Topics 数组 分治 动态规划 


贪心

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.size() == 1)
            return nums[0];
        
        int cur_sum = nums[0], max_sum = nums[0];

        for(int i = 1; i < nums.size(); i++){
            cur_sum = max(nums[i], nums[i] + cur_sum);
            max_sum = max(max_sum, cur_sum);
        }

        return max_sum;
    }
};


leetcode-221. 最大正方形

//在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。 
//
// 
//
// 示例 1： 
//
// 
//输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"]
//,["1","0","0","1","0"]]
//输出：4
// 
//
// 示例 2： 
//
// 
//输入：matrix = [["0","1"],["1","0"]]
//输出：1
// 
//
// 示例 3： 
//
// 
//输入：matrix = [["0"]]
//输出：0
// 
//
// 
//
// 提示： 
//
// 
// m == matrix.length 
// n == matrix[i].length 
// 1 <= m, n <= 300 
// matrix[i][j] 为 '0' 或 '1' 
// 
// Related Topics 数组 动态规划 矩阵 
// 👍 801 👎 0


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {

    }
};
//leetcode submit region end(Prohibit modification and deletion)

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int maximalSquare(vector<vector<char>> &matrix) {
    int m = matrix.size(), n = matrix[0].size();
    // 以i,j为右下角的 最大边长
    // dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
    vector<vector<int>> dp(m, vector<int>(n, 0));

    int max_side = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (matrix[i][j] == '1') {
          if (i == 0 || j == 0) {
            dp[i][j] = 1;
            max_side = max(max_side, 1);
          } else {
            dp[i][j] = min3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1;
            max_side = max(max_side, dp[i][j]);
          }
        }
      }
    }

    return max_side * max_side;
  }

private:
  int min3(int a, int b, int c) { return min(min(a, b), c); }
};

int main() {
  vector<vector<char>> nums{{'1', '0', '1', '0', '0'},
                            {'1', '0', '1', '1', '1'},
                            {'1', '1', '1', '1', '1'},
                            {'1', '0', '0', '1', '0'}};
  cout << Solution().maximalSquare(nums) << endl;

  return 0;
}
leetcode-53. 最大子序和


leetcode-1277. 统计全为 1 的正方形子矩阵



//给你一个 m * n 的矩阵，矩阵中的元素不是 0 就是 1，请你统计并返回其中完全由 1 组成的 正方形 子矩阵的个数。 
//
// 
//
// 示例 1： 
//
// 输入：matrix =
//[
//  [0,1,1,1],
//  [1,1,1,1],
//  [0,1,1,1]
//]
//输出：15
//解释： 
//边长为 1 的正方形有 10 个。
//边长为 2 的正方形有 4 个。
//边长为 3 的正方形有 1 个。
//正方形的总数 = 10 + 4 + 1 = 15.
// 
//
// 示例 2： 
//
// 输入：matrix = 
//[
//  [1,0,1],
//  [1,1,0],
//  [1,1,0]
//]
//输出：7
//解释：
//边长为 1 的正方形有 6 个。 
//边长为 2 的正方形有 1 个。
//正方形的总数 = 6 + 1 = 7.
// 
//
// 
//
// 提示： 
//
// 
// 1 <= arr.length <= 300 
// 1 <= arr[0].length <= 300 
// 0 <= arr[i][j] <= 1 
// 
// Related Topics 数组 动态规划 矩阵 
// 👍 160 👎 0


#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int countSquares(vector<vector<int>> &matrix) {
    int m = matrix.size(), n = matrix[0].size();
    // 以i,j为右下角的 最大边长
    // dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
    vector<vector<int>> dp(m, vector<int>(n, 0));

    int max_side = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (matrix[i][j] == 1) {
          if (i == 0 || j == 0) {
            dp[i][j] = 1;
            max_side = max(max_side, 1);
          } else {
            dp[i][j] = min3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1;
            max_side = max(max_side, dp[i][j]);
          }
        }
      }
    }
    int res = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        res += dp[i][j];
      }
    }

    return res;
  }

private:
  int min3(int a, int b, int c) { return min(min(a, b), c); }
};

int main() {
  vector<vector<int>> nums{
      {1, 0, 1, 0, 0}, {1, 0, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 1, 0}};
  cout << Solution().maximalSquare(nums) << endl;

  return 0;
}
圆环上随机取3点，求这3个点组成一个锐角三角形的概率

问题
在一个圆环上随机取3点，求这3个点组成一个锐角三角形的概率

题解
如下图所示：


取单位圆上任意不同两点A和B，A、B两点确定以后，点A、B、C三点要够成锐角三角形，点C必须在DE之间，否在将构成直角三角形（点C与点D或点E重合）或钝角三角形。设AB弧所对应的圆心角为θ,则当且仅当θ∈(0,π) 时有可能构成锐角三角形。θ 的概率密度是 1π，此时组成锐角三角形需要C点在AB对应的DE段间的概率是 θ2π。故在一个圆环上随机添加3点，三个点组成一个锐角三角形的概率为


Python 代码模拟
#! /usr/bin/env python3
# -*- coding: utf-8 -*-
 
# @Author: wzdnzd
 
import numpy as np
 
 
def simulate(n):
    # 圆心角θ所对应的弦长 l = 2 * R * sin(θ/2), R为圆的半径
    def compute(theta):
        if theta > np.pi:
            theta = 2 * np.pi - theta
 
        return 2 * np.sin(theta / 2)
 
    # 根据三角形三条边的平方关系判断是否是锐角、直角或钝角三角形
    def judge(array):
        if len(array) != 3:
            raise ValueError('len(array) must be 3.')
 
        if array[0] ** 2 + array[1] ** 2 > array[2] ** 2:
            return -1
        elif array[0] ** 2 + array[1] ** 2 == array[2] ** 2:
            return 0
        else:
            return 1
 
    acute, right, obtuse = 0, 0, 0
    for _ in range(n):
        angles = sorted(np.random.rand(3) * 2 * np.pi)
        chords = sorted([compute(angles[1] - angles[0]),
                         compute(angles[2] - angles[1]), 
                         compute(2 * np.pi + angles[0] - angles[2])])
 
        flag = judge(chords)
        if flag == -1:
            acute += 1
        elif flag == 0:
            right += 1
        else:
            obtuse += 1
 
    return [x / n for x in [acute, right, obtuse]]
 
 
if __name__ == "__main__":
    probabilities = simulate(100000)
    print('acute: {}\tright: {}\tobtuse: {}'.format(
        probabilities[0], probabilities[1], probabilities[2]))

运行结果如下：
acute: 0.25009  right: 0.0      obtuse: 0.74991







50 个红球与 50 个白球，放入两个盒子，要求每个盒子至少有一个球。拿的时候随
机在其中一个盒子内，随机拿出一个球。请问如何摆放这些球，让拿出的是红球的概
率最大？

答：一个盒子装一个红球，另一个盒子装剩下的球。

一个绳子随机剪成三段，求能让这三段组成三角形的概率

答：设线段长度为a，任意分成三段长分别为x，y和a-x-y，显然有x>0，y>0，a-x-y>0，将这三个约束条件画到(x,y)二维平面坐标系上，这三条直线围成了一个直角三角形即为可行域（图1），其面积为(1/2)a^2。

而这三段长能构成三角形的条件是：任意两边之和大于第三边，也就是下面三个不等式得同时成立：
x + y > a - x - y (x + y < a/2)
x + a - x - y > y (y < a/2)
y + a - x - y > x (x < a/2)

我们把上面三个不等式也画在平面直角坐标系中，可以看到可行域为图2中绿色的小三角形，其面积为:(1/8)a^2 ，占整个三角形的1/4。

故此三段能构成三角形的概率为1/4。






描述
在二维坐标系中，所有的值都是double类型，那么一个三角形可以由3个点来代表，给定3个点代表的三角形，再给定一个点(x, y)，判断(x, y)是否在三角形中

输入描述：
输入有四行，每行两个浮点数。

前三行的6个数分别代表三角形的三个顶点的坐标

最后两个数分别表示(x, y)
输出描述：
若(x, y)在三角形中，输出"Yes"

否则输出"No"
示例1
输入：
-1.00 0.00
1.50 3.50
2.73 -3.12
1.23 0.23
输出：
Yes
说明：
样例中的图形大致如下


示例2
输入：
-1.00 0.00
1.50 3.50
2.73 -3.12
2333.33 233333.33
输出：
No
备注：
−2∗1010⩽输入的所有数值⩽−2∗1010


向量叉乘

若点O在三角形内部，则沿着三角形的边逆时针走，点O一定保持在边的左侧。如图示，点在逆时针行走时，在AB，BC，CA的左侧。


如何判断点在一个边的左侧呢？

可以借助向量叉乘来判断O是否在向量AB的哪一侧。通过计算向量AO与向量AB的叉乘的值为正，则表示O在AB的左侧，反之为右侧。



本题的核心思路就是这样。如果要让手撕代码，题目可能没有说输入的3个点是逆时针顺序的。比如，上图中如果依次输入的是A,C,B的坐标，那就不行了。

怎么解决呢？假设依次输入的点分别是p1,p2,p3。




#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    double x;
    double y;
};
double product(Point p1,Point p2,Point p3) {
    //首先根据坐标计算p1p2和p1p3的向量，然后再计算叉乘
    //p1p2 向量表示为 (p2.x-p1.x,p2.y-p1.y)
    //p1p3 向量表示为 (p3.x-p1.x,p3.y-p1.y)
    return (p2.x-p1.x)*(p3.y-p1.y) - (p2.y-p1.y)*(p3.x-p1.x);
}
bool isInTriangle(Point p1,Point p2,Point p3,Point o) {
    //保证p1，p2，p3是逆时针顺序
    if(product(p1, p2, p3)<0) return isInTriangle(p1,p3,p2,o);
    if(product(p1, p2, o)>0 && product(p2, p3, o)>0 && product(p3, p1, o)>0)
        return true;
    return false;
int main() {
    Point p1,p2,p3,o;
    cin >> p1.x >> p1.y;
    cin >> p2.x >> p2.y;
    cin >> p3.x >> p3.y;
    cin >> o.x >> o.y;
    bool flag = isInTriangle(p1,p2,p3,o);
    if(flag) puts("Yes");
    else puts("No");
}
圆环上随机取3点，求这3个点组成一个锐角三角形的概率

问题
在一个圆环上随机取3点，求这3个点组成一个锐角三角形的概率

题解
如下图所示：


取单位圆上任意不同两点A和B，A、B两点确定以后，点A、B、C三点要够成锐角三角形，点C必须在DE之间，否在将构成直角三角形（点C与点D或点E重合）或钝角三角形。设AB弧所对应的圆心角为θ,则当且仅当θ∈(0,π) 时有可能构成锐角三角形。θ 的概率密度是 1π，此时组成锐角三角形需要C点在AB对应的DE段间的概率是 θ2π。故在一个圆环上随机添加3点，三个点组成一个锐角三角形的概率为


Python 代码模拟
#! /usr/bin/env python3
# -*- coding: utf-8 -*-
 
# @Author: wzdnzd
 
import numpy as np
 
 
def simulate(n):
    # 圆心角θ所对应的弦长 l = 2 * R * sin(θ/2), R为圆的半径
    def compute(theta):
        if theta > np.pi:
            theta = 2 * np.pi - theta
 
        return 2 * np.sin(theta / 2)
 
    # 根据三角形三条边的平方关系判断是否是锐角、直角或钝角三角形
    def judge(array):
        if len(array) != 3:
            raise ValueError('len(array) must be 3.')
 
        if array[0] ** 2 + array[1] ** 2 > array[2] ** 2:
            return -1
        elif array[0] ** 2 + array[1] ** 2 == array[2] ** 2:
            return 0
        else:
            return 1
 
    acute, right, obtuse = 0, 0, 0
    for _ in range(n):
        angles = sorted(np.random.rand(3) * 2 * np.pi)
        chords = sorted([compute(angles[1] - angles[0]),
                         compute(angles[2] - angles[1]), 
                         compute(2 * np.pi + angles[0] - angles[2])])
 
        flag = judge(chords)
        if flag == -1:
            acute += 1
        elif flag == 0:
            right += 1
        else:
            obtuse += 1
 
    return [x / n for x in [acute, right, obtuse]]
 
 
if __name__ == "__main__":
    probabilities = simulate(100000)
    print('acute: {}\tright: {}\tobtuse: {}'.format(
        probabilities[0], probabilities[1], probabilities[2]))

运行结果如下：
acute: 0.25009  right: 0.0      obtuse: 0.74991












描述
在二维坐标系中，所有的值都是double类型，那么一个三角形可以由3个点来代表，给定3个点代表的三角形，再给定一个点(x, y)，判断(x, y)是否在三角形中

输入描述：
输入有四行，每行两个浮点数。

前三行的6个数分别代表三角形的三个顶点的坐标

最后两个数分别表示(x, y)
输出描述：
若(x, y)在三角形中，输出"Yes"

否则输出"No"
示例1
输入：
-1.00 0.00
1.50 3.50
2.73 -3.12
1.23 0.23
输出：
Yes
说明：
样例中的图形大致如下


示例2
输入：
-1.00 0.00
1.50 3.50
2.73 -3.12
2333.33 233333.33
输出：
No
备注：
−2∗1010⩽输入的所有数值⩽−2∗1010


向量叉乘

若点O在三角形内部，则沿着三角形的边逆时针走，点O一定保持在边的左侧。如图示，点在逆时针行走时，在AB，BC，CA的左侧。


如何判断点在一个边的左侧呢？

可以借助向量叉乘来判断O是否在向量AB的哪一侧。通过计算向量AO与向量AB的叉乘的值为正，则表示O在AB的左侧，反之为右侧。



本题的核心思路就是这样。如果要让手撕代码，题目可能没有说输入的3个点是逆时针顺序的。比如，上图中如果依次输入的是A,C,B的坐标，那就不行了。

怎么解决呢？假设依次输入的点分别是p1,p2,p3。




#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    double x;
    double y;
};
double product(Point p1,Point p2,Point p3) {
    //首先根据坐标计算p1p2和p1p3的向量，然后再计算叉乘
    //p1p2 向量表示为 (p2.x-p1.x,p2.y-p1.y)
    //p1p3 向量表示为 (p3.x-p1.x,p3.y-p1.y)
    return (p2.x-p1.x)*(p3.y-p1.y) - (p2.y-p1.y)*(p3.x-p1.x);
}
bool isInTriangle(Point p1,Point p2,Point p3,Point o) {
    //保证p1，p2，p3是逆时针顺序
    if(product(p1, p2, p3)<0) return isInTriangle(p1,p3,p2,o);
    if(product(p1, p2, o)>0 && product(p2, p3, o)>0 && product(p3, p1, o)>0)
        return true;
    return false;
int main() {
    Point p1,p2,p3,o;
    cin >> p1.x >> p1.y;
    cin >> p2.x >> p2.y;
    cin >> p3.x >> p3.y;
    cin >> o.x >> o.y;
    bool flag = isInTriangle(p1,p2,p3,o);
    if(flag) puts("Yes");
    else puts("No");
}
给定一个有序（非降序）数组A，可含有重复元素，求最小的i使得A[i]等于target，不存在则返回-1。
#include <iostream>
#include <vector>

using namespace std;

int binary_search(int *arr, int n, int target) {
  int left = 0, right = n - 1;
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] < target)
      left = mid + 1;
    else
      right = mid;
  }
  if (arr[left] != target) {
    return -1;
  } // if
  else {
    return left;
  }
}
int main() {
  int A[] = {2, 3, 4, 4, 4, 4, 4, 5, 6, 7, 8};
  cout << binary_search(A, 11, 4) << endl;

  return 0;
}


//给你一个数组 points ，其中 points[i] = [xi, yi] 表示 X-Y 平面上的一个点。求最多有多少个点在同一条直线上。 
//
// 
//
// 示例 1： 
//
// 
//输入：points = [[1,1],[2,2],[3,3]]
//输出：3
// 
//
// 示例 2： 
//
// 
//输入：points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
//输出：4
// 
//
// 
//
// 提示： 
//
// 
// 1 <= points.length <= 300 
// points[i].length == 2 
// -104 <= xi, yi <= 104 
// points 中的所有点 互不相同 
// 
// Related Topics 几何 哈希表 数学 
// 👍 334 👎 0


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {

    }
};
//leetcode submit region end(Prohibit modification and deletion)


class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int len = points.size();
        // 点的数量不够
        if(len < 3) {
            return len;
        }
        int maxNum = 2;
        // 遍历每两个点
        for(int i = 0; i < len; i ++) {
            unordered_map<double, int> count;
            for(int j = 0; j < len; j ++) {
                if(i != j) {
                    long long dx = points[i][0] - points[j][0];
                    long long dy = points[i][1] - points[j][1];
                    double gradient = dy * 1.0 / dx;
                    if(count.count(gradient)) {
                        count[gradient] ++;
                    } else {
                        count[gradient] = 2;
                    }
                    maxNum = max(maxNum, count[gradient]);
                } 
            }  
        }
        return maxNum;
    }
};

哈希表常见的三个操作时put、get和containsKey，而且这三个操作的时间复杂度为O(1)。现在想加一个setAll功能，就是把所有记录value都设成统一的值。请设计并实现这种有setAll功能的哈希表，并且put、get、containsKey和setAll四个操作的时间复杂度都为O(1)。
[友情提示]: C++选手若有需要可以使用unordered_map替换map来将复杂度从O(log n)降为O(1)

输入描述:
第一行一个整数N表示操作数。
接下来N行，每行第一个数字opt代表操作类型
若opt=1，接下来有两个整数x, y表示设置key=x对应的value=y
若opt=2，接下来一个整数x，表示查询key=x对应的value，若key=x不存在输出-1
若opt=3，接下来一个整数x，表示把加入过的所有的key对应的value都设置为x


输出描述:
对于每个操作2，输出一个整数表示答案
示例1
输入
6
1 1 2
2 1
2 2
3 4
2 1
2 2
输出
2
-1
4
-1

备注:
1⩽N⩽105
−2∗109⩽x,y⩽2∗109


#include <bits/stdc++.h>
using namespace std;
 
class {
    unordered_map<int, int> M, U;
    int all;
    public:
    void put(int x, int y){
        auto it = M.find(x);
        if(it != M.end())
            M.erase(it);
        U[x] = y;
    }
    int get(int x){
        if(M.find(x) != M.end())
            return all;
        if(U.find(x)==U.end())
            return -1;
        else
            return U[x];
    }
    void setAll(int x){
        for(auto it:U)
            M[it.first] = 0;
        U.clear();
        all = x;
    }
}P;
 
int main(){
    int n, opt, x, y;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>opt>>x;
        if(opt==1){
            cin>>y;
            P.put(x, y);
        }else if(opt==2){
            cout<<P.get(x)<<endl;
        }else if(opt==3){
            P.setAll(x);
        }
    }
    return 0;
}


# ＃include<file.h> 与＃include "file.h"的区别

前者是从标准系统头文件路径寻找和引用file.h，而后者是从当前工作路径搜寻并引用file.h  
**cpp -v命令，可以查看标准系统头文件的路径**
蛇形矩阵

蛇形矩阵是由1开始的自然数依次排列成的一个矩阵上三角形。
例如，当输入5时，应该输出的三角形为：
1 3 6 10 15
2 5 9 14
4 8 13
7 12
11

请注意本题含有多组样例输入。

输入描述：
输入正整数N（N不大于100）
输出描述：
输出一个N行的蛇形矩阵。
示例1
输入：
4

输出：
1 3 6 10
2 5 9
4 8
7


#include<iostream>
#include<vector>
 
using namespace std;
 
int main()
{
    int n;
    while(cin >> n)
    {
        vector<vector<int>> nums(n, vector<int>(n));
        int t = 1;
        for(int index = 0;index < n;++index)
        {
            int i = index, j = 0;
            while(i >= 0 && j <= index)
                nums[i--][j++] = t++;
        }
        for(int i = 0;i < n;++i)
        {
            for(int j = 0;j < n - i;++j)
                cout << nums[i][j] << ' ';
            cout << endl;
        }
    }
    return 0;
}






#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
  /**
   * 最大数
   * @param nums int整型vector
   * @return string字符串
   */
  string solve(vector<int> &nums) {
    vector<string> ve;
    for (auto i : nums) {
      ve.push_back(to_string(i));
    }
    sort(ve.begin(), ve.end(),
         [](string a, string b) { return a + b > b + a; });
    //这个地方需要注意如果第一个字符串已经是0了，那么直接输出0
    if (ve[0] == "0")
      return "0";

    string res = "";
    for (int i = 0; i < ve.size(); i++) {
      res += ve[i];
    }
    return res;
  }
};

int main() {
  vector<int> nums{91, 92, 9, 90, 99, 100};
  cout << Solution().solve(nums) << endl;

  return 0;
}



//给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。 
//
// 
//
// 进阶： 
//
// 
// 尽可能想出更多的解决方案，至少有三种不同的方法可以解决这个问题。 
// 你可以使用空间复杂度为 O(1) 的 原地 算法解决这个问题吗？ 
// 
//
// 
//
// 示例 1: 
//
// 
//输入: nums = [1,2,3,4,5,6,7], k = 3
//输出: [5,6,7,1,2,3,4]
//解释:
//向右旋转 1 步: [7,1,2,3,4,5,6]
//向右旋转 2 步: [6,7,1,2,3,4,5]
//向右旋转 3 步: [5,6,7,1,2,3,4]
// 
//
// 示例 2: 
//
// 
//输入：nums = [-1,-100,3,99], k = 2
//输出：[3,99,-1,-100]
//解释: 
//向右旋转 1 步: [99,-1,-100,3]
//向右旋转 2 步: [3,99,-1,-100] 
//
// 
//
// 提示： 
//
// 
// 1 <= nums.length <= 2 * 104 
// -231 <= nums[i] <= 231 - 1 
// 0 <= k <= 105 
// 
//
// 
// 
// Related Topics 数组 数学 双指针 
// 👍 993 👎 0



#include <vector>
#include <algorithm>

using namespace std;
class Solution {
public:
  void rotate(vector<int> &nums, int k) {
    int n = nums.size();
    k %= n;
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
  }
};



给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
    int l = 0, r = -1, res = 0;
    vector<bool> vb(256, false);
    while (l < s.size()) {
      int next = r + 1;
      if (next < s.size())
        if (!vb[s[next]]) {
          vb[s[next]] = true;
          res = max(res, next - l + 1);
          r++;
        } else {
          while (s[l] != s[next]) {
            vb[s[l++]] = false;
          }
          l++;
          r++;
        }
      else
        break;
    }

    return res;
  }
    
};






快排

确定pos=k的位置，pos之前的数就是要求的结果
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> getLeastNumbers(vector<int> &arr, int k) {
    int n = arr.size();
    if (n == k)
      return arr;

    vector<int> res;
    int l = 0, r = n - 1;

    while (l <= r) {
      int pos = parttion(arr, l, r);
      if (pos == k) {
        res.assign(arr.begin(), arr.begin() + k);
        break;
      } else if (pos < k) {
        l = pos + 1;
      } else
        r = pos - 1;
    }

    return res;
  }

private:
  int parttion(vector<int> &arr, int l, int r) {
    int pos = l;
    for (int i = l + 1; i <= r; i++) {
      if (arr[i] < arr[l]) {
        swap(arr[i], arr[pos + 1]);
        pos++;
      }
    }

    swap(arr[pos], arr[l]);

    return pos;
  }
};

void print_vec(const vector<int> &vec) {
  for (auto e : vec)
    cout << e << " ";
  cout << endl;
}

int main() {
  vector<int> nums{0, 0, 1, 3, 4, 5, 0, 7, 6, 7};

  print_vec(Solution().getLeastNumbers(nums, 9));

  return 0;
}



大根堆

建立大根堆，依次弹出，直至数量为k 时间复杂度nlogn
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> getLeastNumbers(vector<int> &arr, int k) {
    int n = arr.size();
    if (n == k)
      return arr;

    make_heap(arr.begin(), arr.end());
    for (int i = n; i > k; i--) {
      pop_heap(arr.begin(), arr.end());
      arr.pop_back();
    }

    return arr;
  }
};

void print_vec(const vector<int> &vec) {
  for (auto e : vec)
    cout << e << " ";
  cout << endl;
}

int main() {
  vector<int> nums{0, 0, 1, 3, 4, 5, 0, 7, 6, 7};

  print_vec(Solution().getLeastNumbers(nums, 9));

  return 0;
}


建立大根堆（前k小），依次弹出，直至数量为k 时间复杂度nlogn

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> getLeastNumbers(vector<int> &arr, int k) {
    int n = arr.size();
    if (n == k)
      return arr;

    vector<int> res(arr.begin(), arr.begin() + k);
    make_heap(res.begin(), res.end());
    for (int i = k; i < n; i++) {
      res.push_back(arr[i]);
      push_heap(res.begin(), res.end());
      pop_heap(res.begin(), res.end());
      res.pop_back();
    }

    return res;
  }
};

void print_vec(const vector<int> &vec) {
  for (auto e : vec)
    cout << e << " ";
  cout << endl;
}

int main() {
  vector<int> nums{0, 1, 2, 1};

  print_vec(Solution().getLeastNumbers(nums, 1));

  return 0;
}



优先队列

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> getLeastNumbers(vector<int> &arr, int k) {
    int n = arr.size();
    if (k == n)
      return arr;

    priority_queue<int> pq(arr.begin(), arr.end());
    for (int i = 0; i < n - k; i++) {
      pq.pop();
    }

    vector<int> res;
    while (!pq.empty()) {
      res.push_back(pq.top());
      pq.pop();
    }

    return res;
  }
};

void print_vec(const vector<int> &vec) {
  for (auto e : vec)
    cout << e << " ";
  cout << endl;
}

int main() {
  vector<int> nums{0, 1, 2, 1};

  print_vec(Solution().getLeastNumbers(nums, 2));

  return 0;
}






求最大subarry其中所有元素max-min不大于一个giventhreshold


386

一面1黎寇梁柏2考察如何在两个BST里找到可以和为target的方法二面1一个数组有n个element有k次机会给数组内的数+1可重复+同一个数如何选出k次操作后在这个数组中出现最多的数以及它出现的次数

蠡口三菱久

1. 给定一个deque（大小1e5），每次pop头部两个element，大的push_back，小的push_front，问第m次(1e18)操作结果：【最多deque.size()次操作后，构成一个环】；
2. 在2-D plane，给定一堆点，找出三个点构成三角形（任意一组即可），其内部及边上不存在其它点：【先找一条边，再找第三个点】。


'''
二维平面上有N个点，每个点用二维坐标表示，找到三个点让他们组成三角形，使得其他所有的点都不在三角形内部，返回这样的三个点的坐标。
'''

###### 想了个Nlog（N）的，先对所有的点按照x轴坐标排序，然后连续的三个点就有可能是满足条件的点。但是需要判断一下多个点是否共线这种情况。
def func(points):
    points.sort(key=lambda x:x[0])
    for i in range(len(points)-2):
        j=i+1
        k=i+2
        xs=[p[0] for p in points[i:i+3]]
        ys=[p[1] for p in points[i:i+3]]
        if len(set(xs))==1:
            continue
        elif len(xs)==2:
            return points[i:i+3]
        if len(set(ys))==1 or (ys[1]-ys[0] )/(xs[1]-xs[0]) == (ys[2]-ys[0])/(xs[2]-xs[0]):
            continue
        else:
            return points[i:i+3]
    return []


# PS:面试官表示还有O(N)的做法，首先选三个不共线的点组成原始的三角形，然后依次扫描其他的点，如果他们是在三角形的外部则直接跳过，否则的话该点替换掉其中的一个点，最后所有的点都判断完毕之后得到的三角形上的三个点也满足题目要求。


'''
给定一个包含int数据的数组，和一个整数k。 每一次可以对数组中的一个数进行加一操作，最多可以做k次操作，k可以不用完。
希望能够使数组中相同的数字数目最多（也就是众数的数目最大），返回这个最大值

例如：
{1,2,4,4}  k=2 可以操作得到->{1,4,4,4}, 因此结果为3
'''


## 思路是先对数组排序，然后用一个左右指针表示的区间内的数字调整到区间内的最大值
# 如果区间内的和+k >= 区间最大值* 区间数目，则当前区间可以在不多于k次的操作下调整到相同的值，此时更新结果并，左移left指针
# 否则的话左移right指针
# 直到左指针小于0时终止循环。

def func(nums,k):
    nums.sort()

    pre_sum = [nums[0]]
    for i in range(1, len(nums)):
        cur_sum = pre_sum[-1] + nums[i]
        pre_sum.append(cur_sum)

    left = len(nums) - 1
    right = len(nums) - 1
    result = 1
    while left >= 0 and right >= 0:
        if right < result - 1:
            break
        t_sum = pre_sum[right] - pre_sum[left] + nums[left]  # why add nums[right]
        if t_sum + k >= (right - left + 1) * nums[right]:
            result = max(result, (right - left + 1))
            left -= 1
        else:
            right -= 1

    return result


'''
给定一个n*m的二维格点地图, 每个位置要么是字符’.’表示空地, 要么是’@’表示有敌人在这里. 规定给定一个d(1 <= d <= min(m, n)), 如果一个d*d的区域内没有任何敌人, 则认为这片区域是安全的.
问给定的地图中有多少个这样安全的区域.
'''

## 二维前缀和，将原始的地图转换成01矩阵，然后t_sum[i][j] 保存从（0,0） 到 （i，j）的矩形中所有元素的和
## 然后遍历二维矩阵 利用前缀和 计算以(i,j)作为左上角的d*d的区域内的元素和，如果是0，说明是安全区+1
## 总体时间复杂度 O(N*M)



## 二维前缀和，将原始的地图转换成01矩阵，然后t_sum[i][j] 保存从（0,0） 到 （i，j）的矩形中所有元素的和
## 然后遍历二维矩阵 利用前缀和 计算以(i,j)作为左上角的d*d的区域内的元素和，如果是0，说明是安全区+1
## 总体时间复杂度 O(N*M)

def convert(data): # 转换成01矩阵
    n=len(data)
    m=len(data[0])
    matrix=[[0]*m for i in range(n)]
    for i in range(n):
        for j in range(m):
            if data[i][j]=='@':
                matrix[i][j]=1
    return matrix


def func(matrix,d):
    n=len(matrix)
    m=len(matrix[0])

    t_sum=[[0]*m for i in range(n)]

    for j in range(m):
        t_sum[0][j]=t_sum[0][j-1]+matrix[0][j]

    for i in range(1,n):
        t_sum[i][0]=t_sum[i-1][0]+matrix[i][0]

    for i in range(1,n):
        for j in range(1,m):
            t_sum[i][j]=t_sum[i][j-1]+t_sum[i-1][j]-t_sum[i-1][j-1]+matrix[i][j]

    result=1
    for i in range(n):
        if i+d>=n:
            break
        for j in range(m):
            if j+d>=m:
                break
            ni=i+d
            nj=j+d
            if i==0 and j==0:
               	tmp=t_sum[ni][nj]
            elif i==0:
                tmp=t_sum[ni][nj]-t_sum[ni][j-1]
            elif j==0:
                tmp=t_sum[ni][nj] -t_sum[i-1][nj]
            else:
            	tmp=t_sum[ni][nj]-t_sum[ni][j-1]-t_sum[i-1][nj]+t_sum[i-1][j-1]

            if tmp==0:
                result+=1
    return result


segment fault 什么时候出现
Link
操作系统分段和分页有什么区别
为什么要分页，分页有哪些优点
分页会不会有内存碎片问题
进程和线程的区别
多线程能够共享进程的什么内部资源
多线程怎么调度
什么时候用多线程，什么时候用多进程
如何实现一个可以扩容的连续数据结构，也就是 c++里的 vector？
TCP 和 UDP 的区别，什么时候使用 UDP
HTTP 打开一个网页之后 TCP 连接会断开吗
动态链接库和静态链接库的区别
算法题如何找到一个数组中第 K 大的数
SVD 分解解释一下，有哪些应用场景？
数学题，掷一个 6 面的骰子 100 次，所以点数的和大于 400 的概率是多少
基于大数定理和中心极限定理
数学题，如何在一个单位圆里均匀采样
如何用两个栈实现一个队列

作者：Gensoul
链接：https://www.nowcoder.com/discuss/386084?type=0&order=0&pos=124&page=1
来源：牛客网

//Q1：完成如下函数，返回在pwd目录下执行“cd path”以后的路径
// pwd: current work dir, /home/pony/work
// path:  e.g. ../logs/./2020/
// 1. cd must succeed
// 2. path / pwd are in [a-z0-9./]
// 3. path / pwd are correct 
std::string my_cd(const std::string& pwd, const std::string& path)

给了一堆点的横纵坐标要求找到一个三角形这个三角形不包含任何其他的点

239

那个event可以专门用一个log给记录下来跟datalog分开然后这个log里面把timetag给加上以及event的种类比如左拐右拐刹车之类的之后应该就是看如何设计一个系统可以将文件上传到系统里方便resimulate（这里放到非汽车领域就当作是replay就好）其实在resimulate里面会有相当多的可以做的事情但是应该也跟这个题无关主要还是看如何把PB级的数据如何scale系统如何设计了加油加油


给N个数字a0a{n-1}和一个K允许最多执行K次操作每次把选择任何一个数字+1问如何操作使得最终重复数字最多


 析构函数出现异常怎么捕获
4. 构造函数出现异常怎么捕获
5. 子类如何捕捉父类异常，父类如何捕捉子类异常？


8. unique_ptr是如何保证严格拥有
   追问const的赋值怎么更改。


.多态是什么？静态多态和动态多态介绍一下？
多态：基类指针指向派生类，让同一指针可以指向不同类的相同方法实现不同功能，静态多态是重载编译时多态，动态多态是重写即虚函数是运行时多态。




2. 介绍下单例模式

答：局部静态变量实现单例模式，在C++11中静态局部变量是线程安全的。（面试官希望能答出：这里为什么采用静态局部变量，怎么保证线程安全的）

3. 不同进程访问静态变量是否是同一个实例？

答：全局变量不管是不是静态的，在多进程模型下都是每个子进程一份，互不影响，也就是说如果一个进程修改了这个变量的值，那只对该进程有效，其他子进程看不到修改后的值。（考察：进程的地址空间）

4. 基类中new一个子类，讲下构造函数和析构函数的顺序？

答：先调用基类的构造函数，再调用子类的构造函数，析构函数调用顺序相反。（考察的是C++基础）

5. 讲下内存泄漏

答：new和delete成对使用，malloc和free成对使用；（考察的是C++基础）

6. 讲下野指针

答：野指针指向一个已删除的对象或 申请访问受限内存区域 的指针。比如delete后没有置空，free后没有置空，此时指针指向的就是垃圾内存，该指针就是野指针。（考察的是C++基础）

7. 介绍下TCP快重传

答：发送方只要一连收到三个重复确认就应当立即重传对方尚未收到的报文段，而不必继续等待设置的重传计时器时间到期。（考察的是C++基础）

8. 讲下链表翻转

答：从原链表的头部一个一个取节点插入新链表的头部；

复制代码
ListNode* ReverseList(ListNode*pHead){
ListNode* prev=NULL;
while(pHead)
{
ListNode* next=p->next;
p->next= prev;
prev =p;
p= next;
}
return newh;
}
复制代码
9. 讲下红黑树

答：R-B Tree，全称是Red-Black Tree，又称为“红黑树”，它一种特殊的二叉查找树。红黑树的每个节点上都有存储位表示节点的颜色，可以是红(Red)或黑(Black)。

红黑树的特性:

（1）每个节点或者是黑色，或者是红色。

（2）根节点是黑色。

（3）每个叶子节点（NIL）是黑色。 [注意：这里叶子节点，是指为空(NIL或NULL)的叶子节点

（4）如果一个节点是红色的，则它的子节点必须是黑色的。

（5）从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点。

10. 红黑树左旋

答：红黑树的左旋操作

假设待左旋的结构中，P为父节点，S为孩子节点。左旋操作后，S节点代替P节点的位置，P节点成为S节点的左孩子，S节点的左孩子成为P节点的右孩子。

红黑树的右旋操作。

假设待右旋的结构中，P为父节点，S为孩子节点。右旋操作后，S节点代替P节点的位置，P节点成为S节点的右孩子，S节点的右孩子成为P节点的左孩子。

11. 讲下不同进程怎么访问共享内存的？

答：一个进程创建共享内存区域，然后把共享区域的地址链接到本进程的地址空间；其他进程若访问该共享内存，只需把共享内存区域的地址链接到进程的地址空间即可。

12. 假如进程A和进程B访问共享内存（包括信号量），如果进程A和进程B异常退出，信号量是否还在？

答：我理解的是还在，只要代码里没有调用信号量的销毁函数，那信号量就一直在。


如果有一个static对象，构造和析构函数在什么时候做

C++中类的封装讲一下

3.什么是内存泄漏，怎么检测，原理思路是啥，有什么后果，野指针有什么后果

为啥函数返回值类型不能作为函数重载的标准
# 什么是虚函数？什么是纯虚函数？
答：虚函数声明如下： virtual ReturnType FunctionName(Parameter)；引入虚函数是为了动态绑定。
纯虚函数声明如下：virtual ReturnType FunctionName()= 0；引入纯虚函数是为了派生接口。

# 基类为什么需要虚析构函数？
答：标准规定：当derived class经由一个base class指针被删除而该base class的析构函数为non-virtual时，将发生未定义行为。通常将发生资源泄漏。  

解决方法即为：为多态基类声明一个virtual 析构函数。

# 动态绑定和静态绑定的区别
对象的静态类型：对象在声明时采用的类型。是在编译期确定的。  
对象的动态类型：目前所指对象的类型。是在运行期决定的。对象的动态类型可以更改，但是静态类型无法更改。  
静态绑定：绑定的是对象的静态类型，某特性(比如函数)依赖于对象的静态类型，发生在编译期。  
动态绑定：绑定的是对象的动态类型，某特性(比如函数)依赖于对象的动态类型，发生在运行期。  

# 构造函数可以调用虚函数吗？语法上通过吗？语义上可以通过吗？
不能，语法上通过，语义上有问题。
derived class对象内的base class成分会在derived class自身构造之前构造完毕。因此，在base class的构造函数中执行的virtual函数将会是base class的版本，决不会是derived class的版本。
即使目前确实正在构造derived class。

# 拷贝构造函数作用及用途？什么时候需要自定义拷贝构造函数？
答：

在C++中，有下面三种对象需要拷贝的情况：

一个对象以值传递的方式传入函数体

一个对象以值传递的方式从函数返回

一个对象需要通过另外一个对象进行初始化
以上的情况就需要拷贝构造函数的调用。

当类中的数据成员需要动态分配存储空间时，不可以依赖default copy constructor。当default copy constructor被因编译器需要而合成时，将执行default memberwise copy语义。此时如果类中有动态分配的存储空间时，将会发生惨重的灾情。在需要时（包括这种对象要赋值、这种对象作为函数参数要传递、函数返回值为这种对象等情况），要考虑到自定义拷贝构造函数。

# C和C++的区别
标准：分别隶属于两个不同的标准委员会。C以C99标准为主流，C11已经发布；C++以C++98/03为主流，C++11/14也日趋流行。

语言本身：

C++是面向对象语言，C是面向过程语言。

结构：C以结构体struct为核心结构；C++以类class为核心结构。

多态：C可以以宏定义的方式“自定义”部分地支持多态；C++自身提供多态，并以模板templates支持编译期多态，以虚函数virtual function支持运行期多态。

头文件的调用：C++用< >代替" "代表系统头文件；且复用C的头文件时，去掉".h"在开头加上"C"。

输入输出：鉴于C++中以对象作为核心，输入和输出都是在流对象上的操作。

封装：C中的封装由于struct的特性全部为公有封装，C++中的封装由于class的特性更加完善、安全。

常见风格：C中常用宏定义来进行文本替换，不具有类型安全性；C++中常建议采用常量定义，具有类型安全性。

效率：常见的说法是同等目的C通常比C++更富有效率(这其实有一定的误解，主要在于C++代码更难于优化且少有人使用编译期求值的特性)。

常用语言/库特性：

数组：C中采用内建数组，C++中建议采用vector。相比之下vector的大小可以动态增长，且使用一些技巧后增长并不低效，且成员函数丰富。

字符串 C中采用C风格的string(实则为字符串数组)，C++中建议采用string，对比与上一条类似。

内存分配：C中使用malloc与free，它们是是C标准库函数，C++中建议使用new/delete代替前者，他们说是C++的运算符(这是笔试面试常考点)以C++中的new为例，new可分为operator new(new 操作)、new operator(new 操作符)和placement new(定位 new)。其中operator new执行和malloc相同的任务，即分配内存，但对构造函数一无所知；而 new operator则调用operator new，分配内存后再调用对象构造函数进行对象的构造。其中operator new是可以重载的。placement new，就是operator new的一个重载版本，允许你在一个已经分配好的内存中构造一个新的对象。

指针：C中通常使用的是原生指针(raw pointer)，由于常出现程序员在申请后忘记释放造成资源泄漏的问题，在C++98中加入了“第一代”基于引用计数的智能指针auto_ptr，由于初代的各种问题(主要是无法解决循环指针)，在03标准也就是TR1中引入了shared_ptr,weak_ptr和unique_ptr这三个功能各异的智能指针，并与11标准中正式确定，较好的解决了上述问题。

仅有C++才有的常用特性：

语言(范式)特性：

面向对象编程：C++中以关键字class和多态特性支持的一种编程范式；

泛型编程：C++中以关键字template支持的一种编程范式；

模板元编程 ：C++中以模板特化和模板递归调用机制支持的一种编程范式。

C++中以对象和类型作为整个程序的核心，在对象方面，时刻注意对象创建和析构的成本，例如有一个很常用的(具名)返回值优化((N)RVO);
在类型方面，有运行时类型信息(RTTI)等技术作为C++类型技术的支撑。

函数重载：C++允许拥有不同变量但具有相同函数名的函数(函数重载的编译器实现方式、函数重载和(主)模板特化的区别都曾考过)。

异常：以catch、throw、try等关键字支持的一种机制。

名字空间：namespace，可以避免和减少命名冲突且让代码具有更强的可读性。

谓词用法：通常以bool函数或仿函数(functor)或lambda函数的形式，出现在STL的大多数算法的第三个元素。

常见关键字(操作符)特性：

auto：在C中，auto代表自动类型通常都可省略；而在C++11新标准中，则起到一种“动态类型”的作用——通常在自动类型推导和decltype搭配使用。

空指针：在C中常以NULL代表空指针，在C++中根据新标准用nullptr来代表空指针。

&: 在C中仅代表取某个左值(lvalue)的地址，在C++中还可以表示引用(别名)。

&&：在C中仅能表示逻辑与，在C++中还可以表示右值引用。

[]：在C中仅能表示下标操作符，在C++中还可以表示lambda函数的捕捉列表。

{}：在C中仅能用于数组的初始化，在C++中由于引入了初始化列表(initializer_list)，可用于任何类型、容器等的初始化。

常量定义：C中常以define来定义常量，C++中用const来定义运行期常量，用constexpr来定义编译器常量。

常用新特性：

右值引用和move语义(太多内容，建议自查)。

基于范围的for循环(与python中的写法类似，常用于容器)。

基于auto——decltype的自动类型推导。

lambda函数(一种局部、匿名函数，高效方便地出现在需要局部、匿名语义的地方)。

标准规范后的多线程库。

# 如何确保对象在抛出异常时也能被删除？什么是RAII？
总的思想是RAII：设计一个class，令他的构造函数和析构函数分别获取和释放资源。
有两个方法：

利用“函数的局部对象无论函数以何种方式(包括因异常)结束都会被析构”这一特性，将“一定要释放的资源”放进局部对象的析构函数；

使用智能指针。


# 将“引用”作为函数参数有哪些特点？

（1）传递引用给函数与传递指针的效果是一样的。这时，被调函数的形参就成为原来主调函数中的实参变量或对象的一个别名来使用，所以在被调函数中对形参变量的操作就是对其相应的目标对象（在主调函数中）的操作。

（2）使用引用传递函数的参数，在内存中并没有产生实参的副本，它是直接对实参操作；而使用一般变量传递函数的参数，当发生函数调用时，需要给形参分配存储单元，形参变量是实参变量的副本；如果传递的是对象，还将调用拷贝构造函数。因此，当参数传递的数据较大时，用引用比用一般变量传递参数的效率和所占空间都好。

（3）使用指针作为函数的参数虽然也能达到与使用引用的效果，但是，在被调函数中同样要给形参分配存储单元，且需要重复使用"*指针变量名"的形式进行运算，这很容易产生错误且程序的阅读性较差；另一方面，在主调函数的调用点处，必须用变量的地址作为实参。而引用更容易使用，更清晰。

# 将“引用”作为函数返回值类型的格式、好处和需要遵守的规则?

格式：

类型标识符 &函数名（形参列表及类型说明）
{
//函数体
}
好处：在内存中不产生被返回值的副本；（注意：正是因为这点原因，所以返回一个局部变量的引用是不可取的。因为随着该局部变量生存期的结束，相应的引用也会失效，产生runtime error!

注意：

（1）不能返回局部变量的引用。这条可以参照Effective C++[1]的Item 31。主要原因是局部变量会在函数返回后被销毁，因此被返回的引用就成为了"无所指"的引用，程序会进入未知状态。

（2）不能返回函数内部new分配的内存的引用(这个要注意啦，很多人没意识到，哈哈。。。）。 这条可以参照Effective C++[1]的Item 31。虽然不存在局部变量的被动销毁问题，可对于这种情况（返回函数内部new分配内存的引用），又面临其它尴尬局面。例如，被函数返回的引用只是作为一个临时变量出现，而没有被赋予一个实际的变量，那么这个引用所指向的空间（由new分配）就无法释放，造成memory leak。

（3）可以返回类成员的引用，但最好是const。 这条原则可以参照Effective C++[1]的Item 30。主要原因是当对象的属性是与某种业务规则（business rule）相关联的时候，其赋值常常与某些其它属性或者对象的状态有关，因此有必要将赋值操作封装在一个业务规则当中。如果其它对象可以获得该属性的非常量引用（或指针），那么对该属性的单纯赋值就会破坏业务规则的完整性。

（4）流操作符重载返回值申明为“引用”的作用：

流操作符<<和>>，这两个操作符常常希望被连续使用，例如：cout <<"hello" << endl;　因此这两个操作符的返回值应该是一个仍然支持这两个操作符的流引用。可选的其它方案包括：返回一个流对象和返回一个流对象指针。但是对于返回一个流对象，程序必须重新（拷贝）构造一个新的流对象，也就是说，连续的两个<<操作符实际上是针对不同对象的！这无法让人接受。对于返回一个流指针则不能连续使用<<操作符。 因此，返回一个流对象引用是惟一选择。这个唯一选择很关键，它说明了引用的重要性以及无可替代性，也许这就是C++语言中引入引用这个概念的原因吧。 赋值操作符=。这个操作符象流操作符一样，是可以连续使用的，例如：x = j = 10;或者(x=10)=100;赋值操作符的返回值必须是一个左值，以便可以被继续赋值。因此引用成了这个操作符的惟一返回值选择。

5）在另外的一些操作符中，却千万不能返回引用：+-*/ 四则运算符。它们不能返回引用，Effective C++[1]的Item23详细的讨论了这个问题。主要原因是这四个操作符没有side effect，因此，它们必须构造一个对象作为返回值，可选的方案包括：返回一个对象、返回一个局部变量的引用，返回一个new分配的对象的引用、返回一 个静态对象引用。根据前面提到的引用作为返回值的三个规则，第2、3两个方案都被否决了。静态对象的引用又因为((a+b) == (c+d))会永远为true而导致错误。所以可选的只剩下返回一个对象了。

什么时候需要“引用”？

流操作符<<和>>、赋值操作符=的返回值、拷贝构造函数的参数、赋值操作符=的参数、其它情况都推荐使用引用。



# 多态的作用？

主要是两个：

1. 隐藏实现细节，使得代码能够模块化；扩展代码模块，实现代码重用；

2. 接口重用：为了类在继承和派生的时候，保证使用家族中任一类的实例的某一属性时的正确调用。


New delete 与mallocfree 的联系与区别?
答案：都是在堆(heap)上进行动态的内存操作。用malloc函数需要指定内存分配的字节数并且不能初始化对象，new 会自动调用对象的构造函数。delete 会调用对象的destructor，而free 不会调用对象的destructor.


struct 和 class 的区别

答案：struct 的成员默认是公有的，而类的成员默认是私有的。struct 和 class 在其他方面是功能相当的。



从感情上讲，大多数的开发者感到类和结构有很大的差别。感觉上结构仅仅象一堆缺乏封装和功能的开放的内存位，而类就象活的并且可靠的社会成员，它有智能服 务，有牢固的封装屏障和一个良好定义的接口。既然大多数人都这么认为，那么只有在你的类有很少的方法并且有公有数据（这种事情在良好设计的系统中是存在 的!）时，你也许应该使用 struct 关键字，否则，你应该使用 class 关键字。 

请说出const与#define 相比，有何优点？
1） const 常量有数据类型，而宏常量没有数据类型。编译器可以对前者进行类型安全检查。而对后者只进行字符替换，没有类型安全检查，并且在字符替换可能会产生意料不到的错误。
2） 有些集成化的调试工具可以对const 常量进行调试，但是不能对宏常量进行调试。


如何打印出当前源文件的文件名以及源文件的当前行号？
答案：
cout << __FILE__ ;
cout<<__LINE__ ;
__FILE__和__LINE__是系统预定义宏，这种宏并不是在某个文件中定义的，而是由编译器定义的


C++中有了malloc / free , 为什么还需要 new / delete

1,malloc与free是C++/C语言的标准库函数，new/delete是C++的运算符。它们都可用于申请动态内存和释放内存。
2,对于非内部数据类型的对象而言，光用maloc/free无法满足动态对象的要求。
对象在创建的同时要自动执行构造函数，对象在消亡之前要自动执行析构函数。
由于malloc/free是库函数而不是运算符，不在编译器控制权限之内，不能够把执行构造函数和析构函数的任务强加于malloc/free。
3,因此C++语言需要一个能完成动态内存分配和初始化工作的运算符new，以一个能完成清理与释放内存工作的运算符delete。注意new/delete不是库函数。


什么时候要用虚析构函数

       通过基类的指针来删除派生类的对象时，基类的析构函数应该是虚的。否则其删除效果将无法实现。

       一般情况下，这样的删除只能够删除基类对象，而不能删除子类对象，形成了删除一半形象，从而千万内存泄漏。

      原因：

              在公有继承中，基类对派生类及其对象的操作，只能影响到那些从基类继承下来的成员。

              如果想要用基类对非继承成员进行操作，则要把基类的这个操作（函数）定义为虚函数。
              那么，析构函数自然也应该如此：如果它想析构子类中的重新定义或新的成员及对象，当然也应该声明为虚的。

      注意：

      如果不需要基类对派生类及对象进行操作，则不能定义虚函数（包括虚析构函数），因为这样会增加内存开销。


面向过程和面向对象的区别

fread和read的区别

malloc底层的实现

介绍你对虚继承的理解（讲了菱形继承及其产生的问题，虚继承怎么解决这些问题）

C++中violate关键字有什么作用（表示可能被某些未知的因素更改，编译器对访问该变量的代码就不再进行优化；不从寄存器中读取，而是重新从内存读取）


sizeof()是在编译期间还是运行期间确定？sizeof指针是多大？

内存对齐

数组与指针区别

C++11原子库，cas操作，为什么cas能保证原子性

32位和64位操作系统编程的区别

讲讲虚函数表存了什么信息。
虚函数表存在哪里。
讲讲在出现菱形继承虚继承时C++对象内存布局。

执行main函数之前和之后做了哪些工作


作者：0x0offer的菜鸡
链接：https://www.nowcoder.com/discuss/222679
来源：牛客网

（1）C++ vector和list的区别？
vector是动态数组实现的，一说到动态那肯定是在堆上分配空间的。如果容量超出原先设定的值，会以2倍扩增。性能上：因为是数组实现的，所以访问起来肯定是O(1)时间内访问。
因为是vector,所以会经常有插入和删除的操作：
如果在结尾插入并且空间够的情况下，很快，如果空间不够，则首先要进行扩容，扩容的过程中完成内存拷贝。在中间拷贝也是一样，如果空间足够大，只需要完成插入位置后的元素拷贝就行了，如果内存不够则也需要先进行扩容，然后进行拷贝。
如果删除的是结尾的元素的话很快就可以完成，如果是中间的元素那就需要拷贝了。
总体而言由于vector的特性原因，所以它很适合随机访问，并且插入删除在结尾部。
list是双向链表实现的，由于是双向链表，所以肯定也是在堆上分配空间的。
那自然插入和删除都是很容易的，因为双向链表实现的原理就是为了插入和删除。
具体的区别和联系：
都是在堆上分配空间
vector是基于动态数组实现的，list基于双向链表实现的
vector不便于中间插入和删除，list支持随机插入和删除
（2）TCP三次握手的过程：
A:我要跟你建立连接
B:好的，我准备好了，我可以和你建立连接
A:那我们开始吧
第三次握手是为了防止发送的报文未能及时到达服务端引发的问题，如果只有两次握手则在这种情况下会建立两个连接。
四次挥手的过程：
A:我要跟你断开连接了
B:你等一下，我还有东西没处理完
B:我处理完了，可以断开连接了
A;我断开连接了
四次挥手的原因是TCP通信本身是全双工的，所以每一方都要确认断开连接，如果只有三次握手的话，那第三次握手完，服务器端就不知道客户端是否收到了第三次握手的消息，这也是为什么客户端在第三次握手后会等待一个2MSL时间的原因，防止第四次握手的消息服务器没收到，如果服务器端没收到第四次握手的消息，服务器就会以为客户端没有收到第三次握手的消息，这时，服务器会在此给客户端发送第三次握手的消息。
（3） 执行main函数之前和之后做了哪些工作？
main函数执行之前主要是系统的初始化资源：
在栈区：设置栈指针
在data段：初始化全局变量和静态变量
在bss段：对未初始化的全局变量进行赋初值，bool是false,short,int,long 是0，指针是NULL
将main函数的参数传到main函数里面
main函数执行完成之后并不一定意味着进程结束。
main函数执行完成之后：
全局对象的析构函数会在main函数的执行后执行
使用atexit注册的函数会在main函数执行之后执行

void fn1(void)
{
printf("next.\n");
}

void fn2(void)
{
printf("executed ");
}

void fn3(void)
{
printf("is ");
}

void fn4(void)
{
printf("This ");
}

int main(void)
{
// 注册需要在 main 函数结束后执行的函数.  
// 请注意它们的注册顺序和执行顺序
// 在 main 函数结束后被调用，调用顺序与注册顺序相反。 先注册后执行。

    atexit(fn1);
    atexit(fn2);
    atexit(fn3);
    atexit(fn4);
 
    // 这条输出语句具有参照性，它可不是最后一句输出. 
    puts("This is executed first.");
 
    // EXIT_SUCCESS 代表 0，它定义在 stdlib.h 中. 
    // 我只是顺便提一下，也许你知道，但我担心你不知道，呵呵. 
    return EXIT_SUCCESS;
}
参考：<a href="https://blog.csdn.net/huang_xw/article/details/8542105" target="_blank" from-niu="default">https://blog.csdn.net/huang_xw/article/details/8542105</a>
（4）你在写程序的时候如果程序出现了死循环你怎么找到这个死循环？
首先需要找可能出现死循环的进程，一个程序执行好久没有结果有可能有两个结果，第一：程序正在正常运行，但还没结果，第二：程序出现死循环
首先查看进程使用资源情况，如果内存占用正常，但是CPU占比接近100%,就说明可能出现死循环。
再使用pstack $pid查看进程栈，如果进程栈总是停留在一个位置，那这个位置就是死循环的位置，在文件里查看具体的代码就可以了。
（5）B+树的时间复杂度？为什么使用B+作为数据库的索引？
如果不考虑磁盘IO读取时间，M叉二叉树的时间复杂度是log(m,n);
因为B+树能够提供稳定高效的范围扫描，他的叶子节点是相互连接的，并且是排好序的，所以是为磁盘等外存设备设计的一种索引结构，而mysql的存储是存在外存上的。
B+树作为索引结构：还具有以下优点
只有叶子节点才记录数据，非叶子节点只包含索引；所有非叶子节点也就是内部节点都只保存叶子节点最小值作为索引，那么这种结构的设计意味着内存中索引节点越多，他的整个IO次数就会下降
（9）编程题：给你一个有序整数数组，数组中的数可以是正数、负数、零，请实现一个函数，这个函数返回一个整数：返回这个数组所有数的平方值中有多少种不同的取值：
思路：这个题其实是leetcode有序数组的平方变过来的https://leetcode-cn.com/problems/squares-of-a-sorted-array/
其实思路也很简单，首先找数组中平方和最大的数，然后找次大的，一直找直到遍历完数组；
int findNumOfSquare(vector<int> &nums) {
if (nums.size() < 2) { return nums.size(); }
int cnt = 0;
int i = 0, j = nums.size() - 1;

    while (i <= j) {
        int num1 = abs(nums[i]);
        int num2 = abs(nums[j]);
        if (num1 == num2) {//当前最大平方数为num1*num1或者num2*num2
            //去重
            while (i <= j && abs(nums[i]) == num1) { i++; }
            while (i <= j && abs(nums[j] == num2)) { j--; }
        }
        else if (num1 > num2) {//当前最大平方数为num1*num1
            //去重
            while (i <= j && abs(nums[i]) == num1) { i++; }
        }
        else {//当前最大平方数为num2*num2
            //去重
            while (i <= j && abs(nums[j]) == num2) { j--; }
        }
        cnt++;
    }
    return cnt;
}


C 与C语言内存分配的区别
C 使用new和delete操作符来完成内存的分配和释放，C语言使用malloc和free两个函数申请空间与释放。malloc只是向操作系统申请指定大小的堆空间，new操作符在申请适合对象大小的空间同时完成对象的初始化。同样free函数只是向操作系统归还指定空间，并不完成对象的析构，而delete操作符能正确调用对象的析构函数。

3. 智能指针的原理
   shared_ptr可以在多个对象之间共享一个原始指针，每个复制都会使其中的引用计数 1，而智能指针对象析构时，将会使引用计数-1，当引用计数从1变为0时，表示没有任何对象在使用该指针了，因此会调用delete释放相应的空间。引用计数可以是一个整数或者结构体，多个智能指针内部共享一个引用计数的指针变量，通过指针操作该变量的值，共同维护一个正确的引用数值。
   unique_ptr是唯一持有某一个原始指针，主要是通过禁止复制构造函数和使用移动构造函数实现的。移动构造函数是一个右值引用的形参，使用移动语义完成对象所有权的转移，其中并没有对原始对象进行拷贝，而只是将原始指针的所有权移动到另一个智能指针。


6. stl模板使用过哪些？挑几个聊聊原理?他们的优缺点是什么？
   vector，内部是连续空间，使用start，finish，end_of_storage几个成员变量来快速获得容量，使用大小，头元素、尾元素等信息。使用push_back、insert会造成扩容操作，具体为当前大小为n，新增大小为m，如果m n超过当前容量，就会进行扩容，扩容后大小为max(2*n, m n)。扩容的步骤为：分配新的空间、复制之前的元素、构造新的元素、释放之前的空间。同时使用vector::clear()不会释放空间，只是将其中的元素清空，若需要立即释放空间，不待变量过期，可以使用和一个空的vector进行swap操作，这样就可以将内存还给操作系统。vector优点在于能够自动申请堆空间，自动扩容，不需要手动操作，也可以保证内存的正确回收。但扩容的过程可能会导致元素大量的复制，造成效率低下，同时会使得迭代器失效，造成程序崩溃。

7. static的用法有哪些？
   （1）修饰局部变量。局部变量的生存期为声明之后，直至当前代码块结束。若使用static声明，该变量将变为静态持续性，存放在静态存储区，存在于整个程序运行周期。同时保证每个进入该代码块，变量保持上一次退出时的值。
   （2）修饰全局变量。会改变全局变量的链接性，使用static修饰后，全局变量由外部链接性变为内存链接性，这样其他源文件不能使用extern变量使用该变量，该变量只能在当前文件内共享访问。
   （3）修饰函数。函数默认具有外部链接性，同普通全局变量一样。使用static修饰后，其他源文件不能使用extern来使用该函数。该函数为内部链接性，当前文件可访问。
   （4）修饰成员变量。修饰成员变量后，该变量将不在类对象的内存布局当中，存在于静态存储区。该变量存在于类对象声明之前，即使没有任何一个类对象声明，该变量依然存在。所有的类对象共享一份实例。
   （5）修饰成员函数。静态成员函数不能访问普通成员变量，只能访问静态成员变量。同时不需要通过类实例进行调用。

C++是单继承还是多继承，菱形继承的问题，为什么虚继承能解决
RTTI的底层实现原理，如何动态获得类型，怎么判断指针对象的继承关系

vector push_back时间复杂度？
简单回答后被深入地问了，提示下扩容后均摊O(1)勉勉强强通过了..大概是这个文章说的这种
https://blog.csdn.net/mtt_sky/article/details/51425560


派生类里组合了其他类，构造顺序是啥？
先构造父类，再构造子类的其他类，最后构造子类

write和fwrite的区别
strcpy的安全性
c++的代码在内存哪个区域

使用strcpy()函数吗，该函数有哪些缺点，有什么可以替代的方法，当时只想到memcpy()，不知道对不对，好像还有strncpy()（当时没想到）；

.1malloc申请的空间是虚拟还是物理，两者什么关系，怎么转换，为什么要有虚拟地址

4.2malloc申请完空间是立即在堆区分配一块实际的物理空间吗？不是的话什么时候分配，怎么分配

debug与release的区别，未初始化的变量？
2、32位与64位的区别？X86框架？
3、CPU占用过高如何处理？
4、内存泄漏如何排查？
5、普通函数的调度过程？


class A类型的指针，此时通过dynamic_cast转换为class B类型的指针，会出现什么问题，是否能通过编译，或者是否能运行（说是不能，但是编译错误还是运行错误不确定）


说一说KMP算法

如何用C实现C++这三大特性？

lock-free的理解？cas为什么能够原子性？

4.如果很多个线程 都在并发cas 但是一直不成功，怎么办？（这个我没明白他的意思

5.内存屏障怎么理解？

6.互斥锁和自旋锁的区别？

7.互斥锁的底层原理？它不是busy-loop如何通知线程

8.自旋锁什么时候用？和cas有什么区别？

9.cas实现自旋锁


用过哪些stl，map底层了解吗（刚介绍完红黑树的五个特性就被打断了。。。下个问题）

在头文件里面声明一个static变量，在两个不同的cpp里面#include这个变量有没有问题

一个类同时继承多个类，这个类里面有几个指向虚函数表的指针

4.哈夫曼压缩（举了一个例子）

作者：静、静
链接：https://www.nowcoder.com/discuss/236936
来源：牛客网

今天在美团面试，有两道题目需要记录一下

实现一个c++中的getline(istream &in, string s)函数。面试官看我思路不太正确，就换成了下一题。下面的代码是回来之后查了资料之后写的。
参考了cplusplus.com的streambuf的用法http://www.cplusplus.com/reference/streambuf/streambuf/snextc/
do{
char ch = in.rdbuf().sgetc();
if(ch == '\n'){
break;
}else{
s += ch;
}
} while(in.rdbuf()->snextc() != EOF)
return ;
}
实现c++中的atol函数.现场写代码的时候忘记判断溢出，面试官提醒了让我再看看有哪些漏洞的时候，我依然没看出来，有点尴尬。
参考了cplusplus.com对atol的说明http://www.cplusplus.com/reference/cstdlib/atol/
long atol(const string &s) {
int i = 0;
long ans = 0;
int f = 1;
// skip white spaces
while(i < s.size() && isspace(s[i])) i++;
if(s[i] == '+' || s[i] == '-') {
f = (s[i] == '+' ? 1 : -1);
i++;
}
while(j < s.size() && isdigit(s[i])) {
if((ans * 10 + (s[i] - '0')) < ans) {
// 溢出
return -1;
}
ans = ans * 10 + (s[i] - '0');
i++;
}
return ans;
}

vector和list的区别和实现，vector和list的查找，插入删除的时间复杂度
STL包括几个部分：容器，算法（泛型算法），迭代器三个主要部分
vector插入效率On，查找效率O1，list插入效率O1，查找效率On
vector的底层数据结构为数组，list的底层数据结构为 双向链表 ，特点是支持快速的增删。
queue为单向队列，为先入先出原则。 deque为双向队列

、算法：有数组a，内部存n个数，每个数的范围为0-(n-1)，把非重复的数排在前面，重复的数排在后面，空间复杂度为O(1)。

定义一个struct，有int x，char c两个成员，这个结构体多大？为什么内存对齐？如果增加一个static int 这个结构体大小怎么变化？如果在结构体里定义一个虚函数，结构体大小怎么变化？

3.1 一个只有一个int成员变量，没有任何其他成员函数的类，问编译过程中会默认完成那些函数，并解释其作用

虚函数的执行和类成员函数的执行在汇编的级别差了哪些指令


12.makefile吗，一个文件依赖库a，库a依赖库b，写makefile的时候，a要放在b的前面还是后面
•  Makefile概述：
什么是makefile？或许很多Winodws的程序员都不知道这个东西，因为那些Windows的IDE都为你做了这个工作，但我觉得要作一个好的和professional的程序员，makefile还是要懂。这就好像现在有这么多的HTML的编辑器，但如果你想成为一个专业人士，你还是要了解HTML的标识的含义。特别在Unix下的软件编译，你就不能不自己写makefile了，会不会写makefile，从一个侧面说明了一个人是否具备完成大型工程的能力。
因为，makefile关系到了整个工程的编译规则。一个工程中的源文件不计数，其按类型、功能、模块分别放在若干个目录中，makefile定义了一系列的规则来指定，哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至于进行更复杂的功能操作，因为makefile就像一个Shell脚本一样，其中也可以执行操作系统的命令。
makefile带来的好处就是——“自动化编译”，一旦写好，只需要一个make命令，整个工程完全自动编译，极大的提高了软件开发的效率。make是一个命令工具，是一个解释makefile中指令的命令工具，一般来说，大多数的IDE都有这个命令，比如：Delphi的make，Visual C++的nmake，Linux下GNU的make。可见，makefile都成为了一种在工程方面的编译方法。
现在讲述如何写makefile的文章比较少，这是我想写这篇文章的原因。当然，不同产商的make各不相同，也有不同的语法，但其本质都是在“文件依赖性”上做文章，这里，我仅对GNU的make进行讲述，我的环境是RedHat Linux 8.0，make的版本是3.80。必竟，这个make是应用最为广泛的，也是用得最多的。而且其还是最遵循于IEEE 1003.2-1992 标准的（POSIX.2）。
在这篇文档中，将以C/C++的源码作为我们基础，所以必然涉及一些关于C/C++的编译的知识，相关于这方面的内容，还请各位查看相关的编译器的文档。这里所默认的编译器是UNIX下的GCC和CC。
•  编译和连接：
编译：
定义：一般来说，无论是C、C++、还是pas，首先要把源文件编译成中间代码文件，在Windows下也就是 .obj 文件，UNIX下是 .o 文件，即 Object File，这个动作叫做编译（compile）。
描述：编译时，编译器需要的是语法的正确，函数与变量的声明的正确。只要所有的语法正确，编译器就可以编译出中间目标文件。一般来说，每个源文件都应该对应于一个中间目标文件（O文件或是OBJ文件）。
连接：
定义：然后再把大量的Object File合成执行文件，这个动作叫作链接（link）。
描述：通常是你需要告诉编译器头文件的所在位置（头文件中应该只是声明，而定义应该放在C/C++文件中），链接时，主要是链接函数和全局变量，所以，我们可以使用这些中间目标文件（O文件或是OBJ文件）来链接我们的应用程序。链接器并不管函数所在的源文件，只管函数的中间目标文件（Object File），在大多数时候，由于源文件太多，编译生成的中间目标文件太多，而在链接时需要明显地指出中间目标文件名，这对于编译很不方便，所以，我们要给中间目标文件打个包，在Windows下这种包叫“库文件”（Library File)，也就是 .lib 文件，在UNIX下，是Archive File，也就是 .a 文件。
总结一下，源文件首先会生成中间目标文件，再由中间目标文件生成执行文件。在编译时，编译器只检测程序语法，和函数、变量是否被声明。如果函数未被声明，编译器会给出一个警告，但可以生成Object File。而在链接程序时，链接器会在所有的Object File中找寻函数的实现，如果找不到，那到就会报链接错误码（Linker Error），在VC下，这种错误一般是：Link 2001错误，意思说是说，链接器未能找到函数的实现。你需要指定函数的Object File.
•   Makefile
make命令执行时，需要一个 Makefile 文件，以告诉make命令需要怎么样的去编译和链接程序。

首先，我们用一个示例来说明Makefile的书写规则。我们的规则是：
1）如果这个工程没有编译过，那么我们的所有C文件都要编译并被链接。
2）如果这个工程的某几个C文件被修改，那么我们只编译被修改的C文件，并链接目标程序。
3）如果这个工程的头文件被改变了，那么我们需要编译引用了这几个头文件的C文件，并链接目标程序。

只要我们的Makefile写得够好，所有的这一切，我们只用一个make命令就可以完成，make命令会自动智能地根据当前的文件修改的情况来确定哪些文件需要重编译，从而自己编译所需要的文件和链接目标程序。

Makefile的规则：

target…：dependecies…

command
target也就是一个目标文件，可以是Object File，也可以是执行文件。还可以是一个标签（Label），对于标签这种特性，在后续的“伪目标”章节中会有叙述。
dependicies就是，要生成那个target所需要的文件或是目标。
command也就是make需要执行的命令。（任意的Shell命令）
这是一个文件的依赖关系，也就是说，target这一个或多个的目标文件依赖于dependicies中的文件，其生成规则定义在command中。说白一点就是说，dependicies中如果有一个以上的文件比target文件要新的话，command所定义的命令就会被执行。这就是Makefile的规则。也就是Makefile中最核心的内容。（深入探讨makefile）
注意事项：
1.命令要以[Tab]为开始
2.有clean


1.求下面函数的返回值（ 微软）

int func(x)
{
int countx =0;
while(x)
{
countx ++;
x = x&(x-1);
}
return countx;
}

假定x = 9999。 答案：8
思路：将x转化为2进制，看含有的1的个数

15.在C++程序中调用被C 编译器编译后的函数，为什么要加extern “C”？
首先，作为extern是C/C++语言中表明函数和全局变量作用范围（可见性）的关键字，该关键字告诉编译器，其声明的函数和变量可以在本模块或其它模块中使用。
通常，在模块的头文件中对本模块提供给其它模块引用的函数和全局变量以关键字extern声明。例如，如果模块B欲引用该模块A中定义的全局变量和函数时只需包含模块A的头文件即可。这样，模块B中调用模块A中的函数时，在编译阶段，模块B虽然找不到该函数，但是并不会报错；它会在连接阶段中从模块A编译生成的目标代码中找到此函数
extern "C"是连接申明(linkage declaration),被extern "C"修饰的变量和函数是按照C语言方式编译和连接的,来看看C++中对类似。

C的函数是怎样编译的：
作为一种面向对象的语言，C++支持函数重载，而过程式语言C则不支持。函数被C++编译后在符号库中的名字与C语言的不同。例如，假设某个函数的原型为：
void foo( int x, int y );
该函数被C编译器编译后在符号库中的名字为_foo，而C++编译器则会产生像_foo_int_int之类的名字（不同的编译器可能生成的名字不同，但是都采用了相同的机制，生成的新名字称为“mangled name”）。
_foo_int_int 这样的名字包含了函数名、函数参数数量及类型信息，C++就是靠这种机制来实现函数重载的。例如，在C++中，函数void foo( int x, int y )与void foo( int x, float y )编译生成的符号是不相同的，后者为_foo_int_float。
同 样地，C++中的变量除支持局部变量外，还支持类成员变量和全局变量。用户所编写程序的类成员变量可能与全局变量同名，我们以"."来区分。而本质上，编译器在进行编译时，与函数的处理相似，也为类中的变量取了一个独一无二的名字，这个名字与用户程序中同名的全局变量名字不同。
未加extern "C"声明时的连接方式
假设在C++中，模块A的头文件如下：
// 模块A头文件　moduleA.h
#ifndef MODULE_A_H
#define MODULE_A_H
int foo( int x, int y );
#endif　　

在模块B中引用该函数：
// 模块B实现文件　moduleB.cpp
＃include "moduleA.h"
foo(2,3);
实际上，在连接阶段，连接器会从模块A生成的目标文件moduleA.obj中寻找_foo_int_int这样的符号！

加extern "C"声明后的编译和连接方式
加extern "C"声明后，模块A的头文件变为：
// 模块A头文件　moduleA.h
#ifndef MODULE_A_H
#define MODULE_A_H
extern"C"int foo( int x, int y );
#endif　
在模块B的实现文件中仍然调用foo( 2,3 )，其结果是：
（1）模块A编译生成foo的目标代码时，没有对其名字进行特殊处理，采用了C语言的方式；
（2）连接器在为模块B的目标代码寻找foo(2,3)调用时，寻找的是未经修改的符号名_foo。
如果在模块A中函数声明了foo为extern "C"类型，而模块B中包含的是extern int foo( int x, int y ) ，则模块B找不到模块A中的函数；反之亦然。
所以，可以用一句话概括extern “C”这个声明的真实目的（任何语言中的任何语法特性的诞生都不是随意而为的，来源于真实世界的需求驱动。我们在思考问题时，不能只停留在这个语言是怎么做的，还要问一问它为什么要这么做，动机是什么，这样我们可以更深入地理解许多问题）：实现C++与C及其它语言的混合编程。
明白了C++中extern "C"的设立动机，我们下面来具体分析extern "C"通常的使用技巧：
extern "C"的惯用法

（1）在C++中引用C语言中的函数和变量，在包含C语言头文件（假设为cExample.h）时，需进行下列处理：
extern"C"
{
＃include"cExample.h"
}
而在C语言的头文件中，对其外部函数只能指定为extern类型，C语言中不支持extern "C"声明，在.c文件中包含了extern"C"时会出现编译语法错误。

C++引用C函数例子工程中包含的三个文件的源代码如下：
/* c语言头文件：cExample.h */
#ifndef C_EXAMPLE_H
#define C_EXAMPLE_H
externint add(int x, inty);
#endif

/* c语言实现文件：cExample.c */
#include "cExample.h"
int add( int x, int y )
{
return x + y;
}










// c++实现文件，调用add：cppFile.cpp
extern"C"
{
＃include"cExample.h"
}
int main(int argc, char* argv[])
{
add(2,3);
return0;
}




如果C++调用一个C语言编写的.DLL时，当包括.DLL的头文件或声明接口函数时，应加extern "C" {　}。

（2）在C中引用C++语言中的函数和变量时，C++的头文件需添加extern "C"，但是在C语言中不能直接引用声明了extern "C"的该头文件，应该仅将C文件中将C++中定义的extern"C"函数声明为extern类型。
C引用C++函数例子工程中包含的三个文件的源代码如下：
//C++头文件cppExample.h
#ifndef CPP_EXAMPLE_H
#define CPP_EXAMPLE_H
extern"C"int add( int x, int y );
#endif

//C++实现文件 cppExample.cpp
＃include"cppExample.h"
int add( int x, int y )
{
return x + y;
}


/* C实现文件 cFile.c
/* 这样会编译出错：＃i nclude "cExample.h" */
externint add( int x, int y );
int main( int argc, char* argv[] )
{
add( 2, 3 );
return0;
}




已知链表的头结点head,写一个函数把这个链表逆序 ( Intel)

Node * ReverseList(Node *head) //链表逆序
{
if ( head == NULL || head->next == NULL )
return head;
Node *p1 = head ;
Node *p2 = p1->next ;
Node *p3 = p2->next ;
p1->next = NULL ;
while ( p3 != NULL )
{
p2->next = p1 ;
p1 = p2 ;
p2 = p3 ;
p3 = p3->next ;
}
p2->next = p1 ;
head = p2 ;
return head ;
}


(2)已知两个链表head1 和head2 各自有序，请把它们合并成一个链表依然有序。(保留所有结点，即便大小相同）

Node * Merge(Node *head1 , Node *head2)
{
if ( head1 == NULL)
return head2 ;
if ( head2 == NULL)
return head1 ;
Node *head = NULL ;
Node *p1 = NULL;
Node *p2 = NULL;
if ( head1->data < head2->data )
{
head = head1 ;
p1 = head1->next;
p2 = head2 ;
}
else
{
head = head2 ;
p2 = head2->next ;
p1 = head1 ;
}
Node *pcurrent = head ;
while ( p1 != NULL && p2 != NULL)
{
if ( p1->data <= p2->data )
{
pcurrent->next = p1 ;
pcurrent = p1 ;
p1 = p1->next ;
}
else
{
pcurrent->next = p2 ;
pcurrent = p2 ;
p2 = p2->next ;
}
}
if ( p1 != NULL )
pcurrent->next = p1 ;
if ( p2 != NULL )
pcurrent->next = p2 ;
return head ;
}


(3)已知两个链表head1 和head2 各自有序，请把它们合并成一个链表依然有序，这次要求用递归方法进行。(Autodesk)
答案：

Node * MergeRecursive(Node *head1 , Node *head2)
{
if ( head1 == NULL )
return head2 ;
if ( head2 == NULL)
return head1 ;
Node *head = NULL ;
if ( head1->data < head2->data )
{
head = head1 ;
head->next = MergeRecursive(head1->next,head2);
}
else
{
head = head2 ;
head->next = MergeRecursive(head1,head2->next);
}
return head ;
}




写一个函数找出一个整数数组中，第二大的数（microsoft）
答案：

constint MINNUMBER =-32767 ;
int find_sec_max( int data[] , int count)
{
int maxnumber = data[0] ;
int sec_max = MINNUMBER ;
for ( int i =1 ; i < count ; i++)
{
if ( data[i] > maxnumber )
{
sec_max = maxnumber ;
maxnumber = data[i] ;
}
else
{
if ( data[i] > sec_max )
sec_max = data[i] ;
}
}
return sec_max ;
}



45. 如何判断一个单链表是有环的？（注意不能用标志位，最多只能用两个额外指针）









struct node { char val; node* next;}
bool check(const node* head) {} //return false : 无环；true: 有环一种O（n）的办法就是（搞两个指针，一个每次递增一步，一个每次递增两步，如果有环的话两者必然重合，反之亦然）：
bool check(const node* head)
{
if(head==NULL) returnfalse;
node *low=head, *fast=head->next;
while(fast!=NULL && fast->next!=NULL)
{
low=low->next;
fast=fast->next->next;
if(low==fast) returntrue;
}
returnfalse;
}
15. 两条相交的单向链表，如何求他们的第一个公共节点
    答：思想：

①如果两个链表相交，则从相交点开始，后面的节点都相同，即最后一个节点肯定相同；
②从头到尾遍历两个链表，并记录链表长度，当二者的尾节点不同，则二者肯定不相交；
③尾节点相同，如果A长为LA，B为LB，如果LA>LB,则A前LA-LB个先跳过；

——更多如链表相关经典问题：求单向局部循环链表的入、将两个有序链表合并合成一个有序链表、链表逆序、求倒数第K个节点，判断是否有环等。



16、求单向局部循环链表的环入口
答：思路：

假如有快慢指针判断一个链表有局部环，链表起点是A，环的入口是B，快慢指针在环中的相遇点是C。那么按照原来的运动方向，有AB=CB，这是可以证明的结论。具体如下图说明：


————————————————
版权声明：本文为CSDN博主「空山明月_Blog」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/Xiongchao99/article/details/74524807


力扣（LeetCode）

已认证的官方帐号
5,836 人赞同了该回答
这个问题，我应该是最有发言权的吧！首先，让我们回顾几个有意思的经典互联网公司的面试题目，热热身。
1. 给你一个长度为 n 的数组，其中只有一个数字出现了奇数次，其他均出现偶数次，问如何使用优秀的时空复杂度快速找到这个数字
136. 只出现一次的数字leetcode-cn.com
2. 给你一个长度为 n 的数组，其中只有一个数字出现了大于等于 n/2 次，问如何使用优秀的时空复杂度快速找到这个数字。
169. 求众数leetcode-cn.com
3. 给你一个 n*m 的二维数组，每行元素保证递增，每列元素保证递增，试问如何使用优秀的时间复杂度找到某个数字（或者判断不存在）。
240. 搜索二维矩阵 IIleetcode-cn.com
4. 给你两颗二叉搜索树，如何使用线性的时间复杂度，将它们合并成一颗二叉搜索树。
88. 合并两个有序数组leetcode-cn.com
5. 假设有 100 层的高楼，给你两个完全一样的鸡蛋。请你设计一种方法，能够试出来从第几层楼开始往下扔鸡蛋，鸡蛋会碎。 当然，这个问题还有推广版本，有兴趣的同学可以思考一下。 假设有 n 层楼，给你 k 个完全一样的鸡蛋，请问最坏情况下，至少需要试验多少次才能知道从第几层楼开始往下扔鸡蛋，鸡蛋会碎。
887. 鸡蛋掉落leetcode-cn.com

接下来，再认真回答一下这个问题。先划重点：面试 和 算法题。作为在电话 / 现场面试中短短不到一个小时时间内，提供给面试者白板编程解决的算法题目，它与笔试上机、编程竞赛中的题目在难度与形式上还是有一些不同的。
这里有一张互联网公司面试中经常考察的问题类型总结的思维导图，我们可以结合图片中的信息分析一下。

可以明确的一点是，面试算法题目在难度上（尤其是代码难度上）会略低一些，倾向于考察一些基础数据结构与算法，对于高级算法和奇技淫巧一般不作考察。
代码题主要考察编程语言的应用是否熟练，基础是否扎实，一般来会让面试者写出代码完成一些简单的需求或者使用递归实现某些功能，而数学题倾向于考察概率相关的问题。以上这两类问题，出现的频率不会很高，即使出现了也应该是面试中的简单部分，相信一定难不倒在座的各位。
算法与数据结构是面试考察的重中之重，也是大家日后刷题时需要着重训练的部分。简单的总结一下，大约有这些内容：
算法 - Algorithms
1. 排序算法：快速排序、归并排序、计数排序
2. 搜索算法：回溯、递归、剪枝技巧
3. 图论：最短路、最小生成树、网络流建模
4. 动态规划：背包问题、最长子序列、计数问题
5. 基础技巧：分治、倍增、二分、贪心
      数据结构 - Data Structures
1. 数组与链表：单 / 双向链表、跳舞链
2. 栈与队列
3. 树与图：最近公共祖先、并查集
4. 哈希表
5. 堆：大 / 小根堆、可并堆
6. 字符串：字典树、后缀树
      对于上面总结的这部分内容，力扣（LeetCode） 已经为大家准备好了相关专题，等待大家来练习啦。
      算法部分，我们开设了 初级算法 - 帮助入门、中级算法 - 巩固训练 、 高级算法 - 提升进阶 三个不同的栏目，包含：数组、字符串、搜索、排序、动态规划、数学、图论等许多内容。大家可以针对自己当前的基础与能力，选择相对应的栏目进行练习。为了能够达到较好的效果，建议小伙伴将所有题目都练习 2～3 遍，吃透每一道题目哦。
      数据结构部分，我们开设了一个 数据结构探索板块，其中包含：队列与栈、数组与字符串、链表、哈希表、二叉树等丰富的内容。每一个章节都包含文字讲解与生动的图片演示，同时配套相关题目。相信只要认真练习，一定能受益匪浅。
      力扣将 Top Interview Questions 里比较新的题目按照类别进行了整理，以供大家按模块练习。
      模拟
      •    134. 加油站
      •    146. LRU缓存机制
      •    202. 快乐数
      •    289. 生命游戏
      •    371. 两整数之和
      •    412. Fizz Buzz
      数组
      •    152. 乘积最大子序列
      •    169. 求众数
      •    189. 旋转数组
      •    217. 存在重复元素
      •    283. 移动零
      •    384. 打乱数组
      •    350. 两个数组的交集 II
      •    334. 递增的三元子序列
      •    240. 搜索二维矩阵 II
      •    238. 除自身以外数组的乘积
      链表
      •    138. 复制带随机指针的链表
      •    141. 环形链表
      •    148. 排序链表
      •    160. 相交链表
      •    206. 反转链表
      •    234. 回文链表
      •    237. 删除链表中的节点
      •    328. 奇偶链表
      堆
      •    155. 最小栈
      •    215. 数组中的第K个最大元素
      •    295. 数据流的中位数
      •    378. 有序矩阵中第K小的元素
      •    347. 前K个高频元素
      栈
      •    150. 逆波兰表达式求值
      •    227. 基本计算器 II
      •    341. 扁平化嵌套列表迭代器
      哈希 / Map
      •    171. Excel表列序号
      •    454. 四数相加 II
      •    380. 常数时间插入、删除和获取随机元素
      队列
      •    239. 滑动窗口最大值
      树
      •    230. 二叉搜索树中第K小的元素
      •    236. 二叉树的最近公共祖先
      •    297. 二叉树的序列化与反序列化
      线段树
      •    218. 天际线问题
      排序
      •    179. 最大数
      •    324. 摆动排序 II
      二分检索
      •    162. 寻找峰值
      •    287. 寻找重复数
      •    315. 计算右侧小于当前元素的个数
      滑动窗口
      •    395. 至少有K个重复字符的最长子串
      动态规划
      •    124. 二叉树中的最大路径和
      •    128. 最长连续序列
      •    198. 打家劫舍
      •    279. 完全平方数
      •    300. 最长上升子序列
      •    322. 零钱兑换
      •    329. 矩阵中的最长递增路径
      图论
      •    127. 单词接龙
      •    200. 岛屿的个数
      •    207. 课程表
      •    210. 课程表 II
      数学 & 位运算
      •    136. 只出现一次的数字
      •    149. 直线上最多的点数
      •    166. 分数到小数
      •    172. 阶乘后的零
      •    190. 颠倒二进制位
      •    191. 位1的个数
      •    204. 计数质数
      •    268. 缺失数字
      •    326. 3的幂
      字符串
      •    125. 验证回文串
      •    131. 分割回文串
      •    139. 单词拆分
      •    140. 单词拆分 II
      •    208. 实现 Trie (前缀树)
      •    212. 单词搜索 II
      •    242. 有效的字母异位词
      •    387. 字符串中的第一个唯一字符
      •    344. 反转字符串
      前方干货预警
      力扣君特别为大家总结了“高频算法面试题汇总”卡片，在力扣探索频就可以找到，希望对各位即将面试的程序员小伙伴有帮助。最后，祝各位刷题愉快，早日拿到属于自己的Dream Offer。
      探索算法面试题汇总 - 力扣 (LeetCode)leetcode-cn.com

欢迎各位知友关注力扣官方微信公众号：「LeetCode力扣」，更多关于程序员面试、技术干货的内容等你来啃！




9.函数调用和系统调用的区别。
什么是系统调用？（常见Linux及其分类表）
所谓系统调用就是用户在程序中调用操作系统所提供的一个子功能，也就是系统API，系统调用可以被看做特殊的公共子程序。系统中的各种共享资源都由操作系统统一掌管，因此在用户程序中，凡是与资源有关的操作（如存储分配、进行I/O传输及管理文件等），都必须通过系统调用方式向操作系统提出服务请求，并由操作系统代为完成。通常，一个操作系统提供的系统调用命令有几十个乃至上百个之多。这些系统调用按照功能大致可以分为以下几类：
•  设备管理：完成设备的请求或释放，以及设备启动等功能。
•  文件管理：完成文件的读、写、创建及删除等功能
•  进程控制：完成进程的创建、撤销、阻塞、及唤醒的功能
•  进程通信：完成进程之间的消息传递或信号的传递
•  内存管理：完成内存的分配、回收以及获取作业占用内存区大小及始址等功能。
显然，系统调用运行在系统的核心态。通过系统调用的方式来使用系统功能，可以保证系统的稳定性和安全性，防止用户随意更改或访问系统的数据或命令。系统调用命令式由操作系统提供的一个或多个子程序模块来实现的。
下图详细阐述了，Linux系统中系统调用的过程：（int 0x80中断向量是dos系统返回，int 3中断向量是断点指令——可以查中断向量表）


库是可重用的模块，处于用户态。
系统调用是操作系统提供的服务，处于内核态，不能直接调用，而要使用类似int 0x80的软中断陷入内核，所以库函数中有很大部分是对系统调用的封装。
既然如此，如何调用系统调用？
用户是处于用户态，具有的权限是非常有限，肯定是不能直接使用内核态的服务，只能间接通过有访问权限的API函数内嵌的系统调用函数来调用。
介绍下系统调用的过程：
首先将API函数参数压到栈上，然后将函数内调用系统调用的代码放入寄存器，通过陷入中断，进入内核将控制权交给操作系统，操作系统获得控制后，将系统调用代码拿出来，跟操作系统一直维护的一张系统调用表做比较，已找到该系统调用程序体的内存地址，接着访问该地址，执行系统调用。执行完毕后，返回用户程序

例子：
int main()
{
int fd = create("filename",0666);
exit(0);
}
在执行main函数时，是在user mode下执行，当遇到create函数时，继续在user mode下执行，然后将filename和0666两个参数压入栈中寄存器，接着调用库函数create，系统仍然处于user mode。这里的库函数create实际上调用了内核的系统调用create，执行到这里后，系统将create系统调用的unique number压入寄存器，然后执行指令trap使系统进入kernel mode(执行int $0x80产生中断)。这时系统意识到要进行系统调用的invoke，于是从刚才的寄存器中取出create系统调用的unique number，从系统调用表中得知要invoke的系统调用是create，然后执行。执行完毕返回库函数create的调用，库函数负责检查系统调用的执行情况(检查某些寄存器的值)，然后库函数create根据检查的结果返回响应的值。

这里trap指令类似于一个系统中断并且是软中断，而系统调用create类似于一个中断处理函数所有的系统调用都与上边的情况类似，靠中断机制切换到内核模式实现。
系统调用通常比库函数要慢，因为要把上下文环境切换到内核模式。
补充一下系统调用和库函数的区别：

系统调用：是操作系统为用户态运行的进程和硬件设备(如CPU、磁盘、打印机等)进行交互提供的一组接口，即就是设置在应用程序和硬件设备之间的一个接口层。可以说是操作系统留给用户程序的一个接口。再来说一下，linux内核是单内核，结构紧凑，执行速度快，各个模块之间是直接调用的关系。放眼望整个linux系统，从上到下依次是用户进程->linux内核->硬件。其中系统调用接口是位于Linux内核中的，如果再稍微细分一下的话，整个linux系统从上到下可以是：用户进程->系统调用接口->linux内核子系统->硬件，也就是说Linux内核包括了系统调用接口和内核子系统两部分；或者从下到上可以是：物理硬件->OS内核->OS服务->应用程序，其中操作系统起到“承上启下”的关键作用，向下管理物理硬件，向上为操作系服务和应用程序提供接口，这里的接口就是系统调用了。
一般地，操作系统为了考虑实现的难度和管理的方便，它只提供一少部分的系统调用，这些系统调用一般都是由C和汇编混合编写实现的，其接口用C来定义，而具体的实现则是汇编，这样的好处就是执行效率高，而且，极大的方便了上层调用。

库函数：顾名思义是把函数放到库里。是把一些常用到的函数编完放到一个文件里，供别人用。别人用的时候把它所在的文件名用#include<>加到里面就可以了。一般是放到lib文件里的。一般是指编译器提供的可在c源程序中调用的函数。可分为两类，一类是c语言标准规定的库函数，一类是编译器特定的库函数。(由于版权原因，库函数的源代码一般是不可见的，但在头文件中你可以看到它对外的接口)
libc中就是一个C标准库，里面存放一些基本函数，这些基本函数都是被标准化了的，而且这些函数通常都是用汇编直接实现的。
库函数一般可以概括的分为两类，一类是随着操作系统提供的，另一类是由第三方提供的。随着系统提供的这些库函数把系统调用进行封装或者组合，可以实现更多的功能，这样的库函数能够实现一些对内核来说比较复杂的操作。比如，read()函数根据参数，直接就能读文件，而背后隐藏的比如文件在硬盘的哪个磁道，哪个扇区，加载到内存的哪个位置等等这些操作，程序员是不必关心的，这些操作里面自然也包含了系统调用。而对于第三方的库，它其实和系统库一样，只是它直接利用系统调用的可能性要小一些，而是利用系统提供的API接口来实现功能(API的接口是开放的)。部分Libc库中的函数的功能的实现还是借助了系统掉调用，比如printf的实现最终还是调用了write这样的系统调用；而另一些则不会使用系统调用，比如strlen, strcat, memcpy等。

实时上，系统调用所提供给用户的是直接而纯粹的高级服务，如果想要更人性化，具有更符合特定情况的功能，那么就要我们用户自己来定义，因此就衍生了库函数，它把部分系统调用包装起来，一方面把系统调用抽象了，一方面方便了用户级的调用。系统调用和库函数在执行的效果上很相似（当然库函数会更符合需求），但是系统调用是运行于内核状态；而库函数由用户调用，运行于用户态。

系统调用是为了方便使用操作系统的接口，而库函数则是为了人们编程的方便。



10.线程和进程，线程可以共享进程里的哪些东西。 知道协程是什么吗
进程，是并发执行的程序在执行过程中分配和管理资源的基本单位，每一个进程都有一个自己的地址空间，即进程空间或（虚空间）。进程空间的大小 只与处理机的位数有关，一个 16 位长处理机的进程空间大小为 216 ，而 32 位处理机的进程空间大小为 232 。进程至少有 5 种基本状态，它们是：初始态，执行态，等待状态，就绪状态，终止状态。

线程，在网络或多用户环境下，一个服务器通常需要接收大量且不确定数量用户的并发请求，为每一个请求都创建一个进程显然是行不通的，——无论是从系统资源开销方面或是响应用户请求的效率方面来看。因此，操作系统中线程的概念便被引进了。线程，是进程的一部分，一个没有线程的进程可以被看作是单线程的。线程有时又被称为轻权进程或轻量级进程，也是 CPU 调度的一个基本单位。
共享进程的地址空间，全局变量（数据和堆）。在一个进程中，各个线程共享堆区，而进程中的线程各自维持自己的栈。

Each thread has its own:
•  栈区和栈指针（Stack area and stack pointer）
•  寄存器（Registers）
•  调度优先级Scheduling properties (such as policy or priority)
•  信号（阻塞和悬挂）Signals (pending and blocked signals)
•  普通变量Thread specific data ( automatic variables )

线程是指进程内的一个执行单元,也是进程内的可调度实体.
与进程的区别:
(1)地址空间:进程内的一个执行单元;进程至少有一个线程;它们共享进程的地址空间;而进程有自己独立的地址空间;
(2)资源拥有:进程是资源分配和拥有的单位,同一个进程内的线程共享进程的资源
(3)线程是处理器调度的基本单位,但进程不是.
4)二者均可并发执行.

进程和线程都是由操作系统所体会的程序运行的基本单元，系统利用该基本单元实现系统对应用的并发性。进程和线程的区别在于：

简而言之,一个程序至少有一个进程,一个进程至少有一个线程.
线程的划分尺度小于进程，使得多线程程序的并发性高。
另外，进程在执行过程中拥有独立的内存单元，而多个线程共享内存，从而极大地提高了程序的运行效率。
线程在执行过程中与进程还是有区别的。每个独立的线程有一个程序运行的入口、顺序执行序列和程序的出口。但是线程不能够独立执行，必须依存在应用程序中，由应用程序提供多个线程执行控制。
从逻辑角度来看，多线程的意义在于一个应用程序中，有多个执行部分可以同时执行。但操作系统并没有将多个线程看做多个独立的应用，来实现进程的调度和管理以及资源分配。这就是进程和线程的重要区别。

进程是具有一定独立功能的程序关于某个数据集合上的一次运行活动,进程是系统进行资源分配和调度的一个独立单位.
线程是进程的一个实体,是CPU调度和分派的基本单位,它是比进程更小的能独立运行的基本单位.线程自己基本上不拥有系统资源,只拥有一点在运行中必不可少的资源(如程序计数器,一组寄存器和栈),但是它可与同属一个进程的其他的线程共享进程所拥有的全部资源.
一个线程可以创建和撤销另一个线程;同一个进程中的多个线程之间可以并发执行.

协程：
定义：协程其实可以认为是比线程更小的执行单元。为啥说他是一个执行单元，因为他自带CPU上下文。
协程切换：协程拥有自己的寄存器上下文和栈。协程调度切换时，将寄存器上下文和栈保存到其他地方，在切回来的时候，恢复先前保存的寄存器上下文和栈。
（我们在自己在进程里面完成逻辑流调度，碰着i\o我就用非阻塞式的。那么我们即可以利用到异步优势，又可以避免反复系统调用，还有进程切换造成的开销，分分钟给你上几千个　　　　逻辑流不费力。这就是协程。）
协程的调度完全由用户控制，一个线程可以有多个协程，用户创建了几个线程，然后每个线程都是循环按照指定的任务清单顺序完成不同的任务，当任务被堵塞的时候执行下一个任务，当恢复的时候再回来执行这个任务，任务之间的切换只需要保存每个任务的上下文内容，就像直接操作栈一样的，这样就完全没有内核切换的开销，可以不加锁的访问全局变量，所以上下文的切换非常快；另外协程还需要保证是非堵塞的且没有相互依赖，协程基本上不能同步通讯，多采用一步的消息通讯，效率比较高。
多线程和多进程的优劣：

多线程还是多进程的争执由来已久，这种争执最常见到在B/S通讯中服务端并发技术的选型上，比如WEB服务器技术中，Apache是采用多进程的（perfork模式，每客户连接对应一个进程，每进程中只存在唯一一个执行线程），Java的Web容器Tomcat、Websphere等都是多线程的（每客户连接对应一个线程，所有线程都在一个进程中）。



多进程：fork
多线程：pthread_create




4.什么是多态，多态有什么用途。
1. 定义：“一个接口，多种方法”，程序在运行时才决定调用的函数。
2. 实现：C++多态性主要是通过虚函数实现的，虚函数允许子类重写override(注意和overload的区别，overload是重载，是允许同名函数的表现，这些函数参数列表/类型不同）。
      多态与非多态的实质区别就是函数地址是早绑定还是晚绑定。如果函数的调用，在编译器编译期间就可以确定函数的调用地址，并生产代码，是静态的，就是说地址是早绑定的。而如果函数调用的地址不能在编译器期间确定，需要在运行时才确定，这就属于晚绑定。
      3.目的：接口重用。封装可以使得代码模块化，继承可以扩展已存在的代码，他们的目的都是为了代码重用。而多态的目的则是为了接口重用。
      4.用法：声明基类的指针，利用该指针指向任意一个子类对象，调用相应的虚函数，可以根据指向的子类的不同而实现不同的方法。
      补充一下关于重载、重写、隐藏（总是不记得）的区别：

Overload(重载)：在C++程序中，可以将语义、功能相似的几个函数用同一个名字表示，但参数或返回值不同（包括类型、顺序不同），即函数重载。
（1）相同的范围（在同一个类中）；
（2）函数名字相同；
（3）参数不同；
（4）virtual 关键字可有可无。
Override(重写)：是指派生类函数覆盖基类函数，特征是：
（1）不同的范围（分别位于派生类与基类）；
（2）函数名字相同；
（3）参数相同；
（4）基类函数必须有virtual 关键字。
注：重写基类虚函数的时候，会自动转换这个函数为virtual函数，不管有没有加virtual，因此重写的时候不加virtual也是可以的，不过为了易读性，还是加上比较好。
Overwrite(隐藏)：隐藏，是指派生类的函数屏蔽了与其同名的基类函数，规则如下：
（1）如果派生类的函数与基类的函数同名，但是参数不同。此时，不论有无virtual关键字，基类的函数将被隐藏（注意别与重载混淆）。
（2）如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有virtual关键字。此时，基类的函数被隐藏（注意别与覆盖混淆）。

补充一下虚函数表：
多态是由虚函数实现的，而虚函数主要是通过虚函数表（V-Table）来实现的。
如果一个类中包含虚函数（virtual修饰的函数），那么这个类就会包含一张虚函数表，虚函数表存储的每一项是一个虚函数的地址。如下图：

这个类的每一个对象都会包含一个虚指针（虚指针存在于对象实例地址的最前面，保证虚函数表有最高的性能），这个虚指针指向虚函数表。
注：对象不包含虚函数表，只有虚指针，类才包含虚函数表，派生类会生成一个兼容基类的虚函数表。
•  原始基类的虚函数表
下图是原始基类的对象，可以看到虚指针在地址的最前面，指向基类的虚函数表（假设基类定义了3个虚函数）

•  单继承时的虚函数（无重写基类虚函数）
假设现在派生类继承基类，并且重新定义了3个虚函数，派生类会自己产生一个兼容基类虚函数表的属于自己的虚函数表。

Derive class 继承了 Base class 中的三个虚函数，准确的说，是该函数实体的地址被拷贝到 Derive类的虚函数表，派生类新增的虚函数置于虚函数表的后面，并按声明顺序存放。
•  单继承时的虚函数（重写基类虚函数）
现在派生类重写基类的x函数，可以看到这个派生类构建自己的虚函数表的时候，修改了base::x()这一项，指向了自己的虚函数。

•  多重继承时的虚函数（Derived ::public Base1,public Base2）
这个派生类多重继承了两个基类base1，base2，因此它有两个虚函数表。

它的对象会有多个虚指针（据说和编译器相关），指向不同的虚函数表。
多重继承时指针的调整：
Derive b;
Base1* ptr1 = &b;   // 指向 b 的初始地址
Base2* ptr2 = &b;   // 指向 b 的第二个子对象
因为 Base1 是第一个基类，所以 ptr1 指向的是 Derive 对象的起始地址，不需要调整指针（偏移）。
因为 Base2 是第二个基类，所以必须对指针进行调整，即加上一个 offset，让 ptr2 指向 Base2 子对象。
当然，上述过程是由编译器完成的。
Base1* b1 = (Base1*)ptr2;
b1->y();                   // 输出 Base2::y()
Base2* b2 = (Base2*)ptr1;
b2->y();                   // 输出 Base1::y()
其实，通过某个类型的指针访问某个成员时，编译器只是根据类型的定义查找这个成员所在偏移量，用这个偏移量获取成员。由于 ptr2 本来就指向 Base2 子对象的起始地址，所以b1->y()调用到的是Base2::y()，而 ptr1 本来就指向 Base1 子对象的起始地址（即 Derive对象的起始地址），所以b2->y()调用到的是Base1::y()。
•  虚继承时的虚函数表
虚继承的引入把对象的模型变得十分复杂，除了每个基类（MyClassA和MyClassB）和公共基类（MyClass）的虚函数表指针需要记录外，每个虚拟继承了MyClass的父类还需要记录一个虚基类表vbtable的指针vbptr。MyClassC的对象模型如图4所示。

虚基类表每项记录了被继承的虚基类子对象相对于虚基类表指针的偏移量。比如MyClassA的虚基类表第二项记录值为24，正是MyClass::vfptr相对于MyClassA::vbptr的偏移量，同理MyClassB的虚基类表第二项记录值12也正是MyClass::vfptr相对于MyClassA::vbptr的偏移量。（虚函数与虚继承深入探讨）
对象模型探讨：

1.没有继承情况,vptr存放在对象的开始位置,以下是Base1的内存布局
m_iData :100

2.单继承的情况下,对象只有一个vptr,它存放在对象的开始位置,派生类子对象在父类子对象的最后面,以下是D1的内存布局
B1:: m_iData : 100
B1::vptr : 4294800
B2::vptr : 4294776
D::m_iData :300

4. 虚拟继承情况下,虚父类子对象会放在派生类子对象之后,派生类子对象的第一个位置存放着一个vptr,虚拟子类子对象也会保存一个vptr,以下是VD1的内存布局

Unknown : 4294888
B1::vptr :4294864
VD1::vptr :        4294944
VD1::m_iData :  200
VD2::Unknown : 4294952
VD::m_iData : 500
B1::m_iData :  100
5. 棱形继承的情况下,非虚基类子对象在派生类子对象前面,并按照声明顺序排列,虚基类子对象在派生类子对象后面
   VD1::Unknown : 4294968
   VD2::vptr :    4   294932
   VD2::m_iData : 300
   B1::vptr :       4294920
   B1::m_iData :  100

补充一下纯虚函数：
•  定义： 在很多情况下，基类本身生成对象是不合情理的。为了解决这个问题，方便使用类的多态性，引入了纯虚函数的概念，将函数定义为纯虚函数（方法：virtual ReturnType Function()= 0;）纯虚函数不能再在基类中实现，编译器要求在派生类中必须予以重写以实现多态性。同时含有纯虚拟函数的类称为抽象类，它不能生成对象。
•  特点：
1，当想在基类中抽象出一个方法，且该基类只做能被继承，而不能被实例化；（避免类被实例化且在编译时候被发现，可以采用此方法）
2，这个方法必须在派生类(derived class)中被实现；
•  目的：使派生类仅仅只是继承函数的接口。
补充一下纯虚函数：
•  定义：称带有纯虚函数的类为抽象类。
•  作用：为一个继承体系提供一个公共的根，为派生类提供操作接口的通用语义。
•  特点：1.抽象类只能作为基类来使用，而继承了抽象类的派生类如果没有实现纯虚函数，而只是继承纯虚函数，那么该类仍旧是一个抽象类，如果实现了纯虚函数，就不再是抽象类。
2.抽象类不可以定义对象。
补充一下多重继承和虚继承：
多重继承：
定义：派生类继承多个基类，派生类为每个基类（显式或隐式地）指定了访问级别——public、protected 或 private。
class Panda : public Bear, public Endangered {
}
构造：
1.
1. 派生类的对象包含每个基类的基类子对象。
2. 派生类构造函数初始化所有基类（多重继承中若没有显式调用某个基类的构造函数，则编译器会调用该基类默认构造函数），派生类只能初始化自己的基类，并不需要考虑基类的基类怎么初始化。
3. 多重继承时，基类构造函数按照基类构造函数在类派生列表中的出现次序调用。
      析构：总是按构造函数运行的逆序调用析构函数。（基类的析构函数最好写成virtual，否则再子类对象销毁的时候，无法销毁子类对象部分资源。）假定所有根基类都将它们的析构函数适当定义为虚函数，那么，无论通过哪种指针类型删除对象，虚析构函数的处理都是一致的。

拷贝构造/赋值：如果要为派生类编写拷贝构造函数，则需要为调用基类相应拷贝构造函数并为其传递参数，否则只会拷贝派生类部分。
深拷贝与浅拷贝：
浅拷贝：默认的复制构造函数只是完成了对象之间的位拷贝，也就是把对象里的值完全复制给另一个对象，如A=B。这时，如果B中有一个成员变量指针已经申请了内存，那A中的那个成员变量也指向同一块内存。
这就出现了问题：当B把内存释放了（如：析构），这时A内的指针就是野指针了，出现运行错误。
深拷贝：自定义复制构造函数需要注意，对象之间发生复制，资源重新分配，即A有5个空间，B也应该有5个空间，而不是指向A的5个空间。
虚继承与虚基类：
定义：在多重继承下，一个基类可以在派生层次中出现多次。（派生类对象中可能出现多个基类对象）在 C++ 中，通过使用虚继承解决这类问题。虚继承是一种机制，类通过虚继承指出它希望共享其虚基类的状态。在虚继承下，对给定虚基类，无论该类在派生层次中作为虚基类出现多少次，只继承一个共享的基类子对象。共享的基类子对象称为虚基类。
用法：istream 和 ostream 类对它们的基类进行虚继承。通过使基类成为虚基类，istream 和 ostream 指定，如果其他类（如 iostream 同时继承它们两个，则派生类中只出现它们的公共基类ios的一个副本。通过在派生列表中包含关键字 virtual 设置虚基类：
class istream : public virtual ios { ... };
class ostream : virtual public ios { ... };
// iostream inherits only one copy of its ios base class
class iostream: public istream, public ostream { ... };




为什么要字节对齐？

（1）有些特殊的CPU只能处理4倍开始的内存地址

（2）如果不是整倍数读取会导致读取多次

（3）数据总线为读取数据提供了基础

在成员函数中调用delete this会出现什么问题？对象还可以使用吗？

如果当前内存空间真正被释放了再次调用成员函数会报错，调用成员变量好像没有问题。

如果在构造函数中调用memset(this, 0, sizeof(*this))来初始化内存空间，有什么问题吗？

对于有虚函数和虚表存在的类，在进行memset后不能调用虚函数和虚基表继承而来的数据和函数


模板和实现可不可以不写在一个文件里面？为什么？

只能写在一个一个头文件中。

原因：多文件处理变为一个文件其实是通过链接器来实现的，所以如果用源文件来处理模板实现，会导致链接失效，最主要的原因还是在编译，编译器会暂时不处理模板类只有在实例化对象时才去处理，但是这就需要实现的代码了，如果放在其他文件的话，就会无法形成相应的类。

什么是RAII资源管理？

即资源获取就是初始化，利用对象生命周期来控制程序资源，简单来说就是通过局部对象来处理一些资源问题



构造函数能不能虚函数？为什么？那拷贝构造函数能不能为虚函数？为什么？

不可以为虚函数，因为在调用构造函数时，虚表指针并没有在对象的内存空间中，必须要构造函数调用完成后才会形成虚表指针。

拷贝构造函数是构造函数所以理由同上。


如果用map删除了一个元素，迭代器还能用吗？为什么？怎样做可以接着用？

能用，a.erase(it ++)；因为是直接申请的内存，所以可以直接通过获取后续节点来处理


出现异常时，try和catch做了什么？

Catch(Ep a)发生异常-》建立一个异常对象-》拷贝一个异常对象-》catch处理

Catch(Ep &a)发生异常-》建立一个异常对象-》引用异常对象-》catch处理

异常对象通常建立在全局或者堆中【需要在函数外进行捕捉】

Catch捕捉异常的转换：异常处理时，如果用基类的处理派生类的对象会导致派生类完全当做基类来使用，即便有虚函数也没用，所以派生类必须放在基类前处理。

C++如何处理多个异常的？

多次catch处理

常对象的成员变量一定不可以修改吗？为什么？

可以修改，用mutable来修饰，可以突破const的限制。


__stdcall和__cdecl的区别？

__stdcall：

从右往左压栈，堆栈参数数据由函数本身清除，一般是通过汇编指令ret x,x表示弹出x个字节，参数必须是确定，必须为函数本身知晓，所以此关键字不能用于有可变参数应用的函数声明。

__cdecl：

从右往左压栈，由调用者来对堆栈数据进行清除，步骤：调用方调用函数-》函数执行-》函数结果返回-》调用方清除堆栈参数，主要针对可变参数


linux内部提供了那些调试宏？

__FILE__：表示在哪个文件

__LINE__：表示在当前多少行

__FUNCTION__：表示在执行在哪个函数



free一个数组时如何知道要释放多大的内存呢？

一般在数组前面几个字节中存在某一个结构体来保存当前申请的数组大小。


olatile表示什么？有什么作用？

易变的，不会被编译器进行优化，让程序取数据直接去内存中的



menset()函数
答：Memset用来将buffer开始的长为size的内存空间全部设置为字符c，一般用在对定义的字符串进行初始化为''或'/0'；这个函数在socket中多用于清空数组。参见：http://blog.csdn.net/xiongchao99/article/details/64441017#t124
————————————————




中变量的存储类型有哪些？


答：c语言中的存储类型有auto, extern, register, static 四种；




在函数内定义一个字符数组，用gets函数输入字符串的时候，如果输入越界，为什么程序会崩溃？
答：因为gets无法截断数组越界部分，会将所有输入都写入内存，这样越界部分就可能覆盖其他内容，造成程序崩溃。




问9：类的static变量在什么时候初始化？函数的static变量在什么时候初始化？

答：类的静态成员变量在类实例化之前就已经存在了，并且分配了内存。函数的static变量在执行此函数时进行初始化。



请用简单的语言告诉我C++ 是什么？

答：C++是在C语言的基础上开发的一种面向对象编程语言，应用广泛。C++支持多种编程范式 －－面向对象编程、泛型编程和过程化编程。 其编程领域众广，常用于系统开发，引擎开发等应用领域，是最受广大程序员受用的最强大编程语言之一,支持类：类、封装、重载等特性!



问3：什么是面向对象（OOP）？

答：面向对象是一种对现实世界理解和抽象的方法、思想，通过将需求要素转化为对象进行问题处理的一种思想。

问4：什么是多态？

答：多态是指相同的操作或函数、过程可作用于多种类型的对象上并获得不同的结果。不同的对象，收到同一消息可以产生不同的结果，这种现象称为多态




设计模式懂嘛，简单举个例子？

答：设计模式（Design pattern）是一套被反复使用、多数人知晓的、经过分类编目的、代码设计经验的总结。

比如单例模式，保证一个类仅有一个实例，并提供一个访问它的全局访问点。

适用于：当类只能有一个实例而且客户可以从一个众所周知的访问点访问它时；当这个唯一实例应该是通过子类化可扩展的，并且客户应该无需更改代码就能使用一个扩展的实例时。

比如工厂模式，定义一个用于创建对象的接口，让子类决定实例化哪一个类。Factory Method 使一个类的实例化延迟到其子类。

适用于：当一个类不知道它所必须创建的对象的类的时候；当一个类希望由它的子类来指定它所创建的对象的时候；当类将创建对象的职责委托给多个帮助子类中的某一个，并且你希望将哪一个帮助子类是代理者这一信息局部化的时候。



c++怎样让返回对象的函数不调用拷贝构造函数

    拷贝构造函数前加 “explicit” 关键字



11. 关键字static的作用

   1.  函数体内 static 变量的作用范围为该函数体，不同于 auto 变量， 该变量的内存只被分配一次，因此其值在下次调用时仍维持上次的值

   2.  在模块内的 static 全局变量可以被模块内所有函数访问，但不能被模块外其他函数访问

   3.  在模块内的static 函数只可被这一模块内的其他函数调用，这个函数的使用范围被限制在声明它的模块内

   4.  在类的static 成员变量属于整个类所拥有，对类的所以对象只有一份拷贝

   5.  在类中的 static 成员函数属于整个类所拥有，这个函数不接收 this 指针，因而只能访问类的 static 成员变量



     介绍它最重要的一条：隐藏。（static函数，static变量均可） --> 对应上面的2、3项
        当同时编译多个文件时，所有未加static前缀的全局变量和函数都具有全局可见性。
        举例来说明。同时编译两个源文件，一个是a.c，另一个是main.c。

//a.c
char a = 'A';               // global variable
void msg()
{
printf("Hello\n");
}
复制代码
//main.c
int main()
{
extern char a;       // extern variable must be declared before use
printf("%c ", a);
(void)msg();
return 0;
}
复制代码
程序的运行结果是：

     A Hello

 

 

      为什么在a.c中定义的全局变量a和函数msg能在main.c中使用？

      前面说过，所有未加static前缀的全局变量和函数都具有全局可见性，其它的源文件也能访问。此例中，a是全局变量，msg是函数，并且都没有加static前缀，

        因此对于另外的源文件main.c是可见的。

     如果加了static，就会对其它源文件隐藏。例如在a和msg的定义前加上static，main.c就看不到它们了。

     利用这一特性可以在不同的文件中定义同名函数和同名变量，而不必担心命名冲突。static可以用作函数和变量的前缀，对于函数来讲，static的作用仅限于隐藏




描述内存分配方式以及它们的区别?
1） 从静态存储区域分配。内存在程序编译的时候就已经分配好，这块内存在程序的整个运行期间都存在。例如全局变量，static 变量。
2） 在栈上创建。在执行函数时，函数内局部变量的存储单元都可以在栈上创建，函数执行结束时这些存储单元自动被释放。栈内存分配运算内置于处理器的指令集。
3） 从堆上分配，亦称动态内存分配。程序在运行的时候用malloc 或new 申请任意多少的内存，程序员自己负责在何时用free 或delete 释放内存。动态内存的生存期由程序员决定，使用非常灵活，但问题也最多。

4) 代码区。




C++是不是类型安全的？
答案：不是。两个不同类型的指针之间可以强制转换（用reinterpret cast)。C#是类型安全的。






2.makefile吗，一个文件依赖库a，库a依赖库b，写makefile的时候，a要放在b的前面还是后面

Makefile概述：
什么是makefile？或许很多Winodws的程序员都不知道这个东西，因为那些Windows的IDE都为你做了这个工作，但我觉得要作一个好的和professional的程序员，makefile还是要懂。这就好像现在有这么多的HTML的编辑器，但如果你想成为一个专业人士，你还是要了解HTML的标识的含义。特别在Unix下的软件编译，你就不能不自己写makefile了，会不会写makefile，从一个侧面说明了一个人是否具备完成大型工程的能力。

因为，makefile关系到了整个工程的编译规则。一个工程中的源文件不计数，其按类型、功能、模块分别放在若干个目录中，makefile定义了一系列的规则来指定，哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至于进行更复杂的功能操作，因为makefile就像一个Shell脚本一样，其中也可以执行操作系统的命令。

makefile带来的好处就是——“自动化编译”，一旦写好，只需要一个make命令，整个工程完全自动编译，极大的提高了软件开发的效率。make是一个命令工具，是一个解释makefile中指令的命令工具，一般来说，大多数的IDE都有这个命令，比如：Delphi的make，Visual C++的nmake，Linux下GNU的make。可见，makefile都成为了一种在工程方面的编译方法。

现在讲述如何写makefile的文章比较少，这是我想写这篇文章的原因。当然，不同产商的make各不相同，也有不同的语法，但其本质都是在“文件依赖性”上做文章，这里，我仅对GNU的make进行讲述，我的环境是RedHat Linux 8.0，make的版本是3.80。必竟，这个make是应用最为广泛的，也是用得最多的。而且其还是最遵循于IEEE 1003.2-1992 标准的（POSIX.2）。

在这篇文档中，将以C/C++的源码作为我们基础，所以必然涉及一些关于C/C++的编译的知识，相关于这方面的内容，还请各位查看相关的编译器的文档。这里所默认的编译器是UNIX下的GCC和CC。

编译和连接：
编译：

定义：一般来说，无论是C、C++、还是pas，首先要把源文件编译成中间代码文件，在Windows下也就是 .obj 文件，UNIX下是 .o 文件，即 Object File，这个动作叫做编译（compile）。

描述：编译时，编译器需要的是语法的正确，函数与变量的声明的正确。只要所有的语法正确，编译器就可以编译出中间目标文件。一般来说，每个源文件都应该对应于一个中间目标文件（O文件或是OBJ文件）。

连接：

定义：然后再把大量的Object File合成执行文件，这个动作叫作链接（link）。

描述：通常是你需要告诉编译器头文件的所在位置（头文件中应该只是声明，而定义应该放在C/C++文件中），链接时，主要是链接函数和全局变量，所以，我们可以使用这些中间目标文件（O文件或是OBJ文件）来链接我们的应用程序。链接器并不管函数所在的源文件，只管函数的中间目标文件（Object File），在大多数时候，由于源文件太多，编译生成的中间目标文件太多，而在链接时需要明显地指出中间目标文件名，这对于编译很不方便，所以，我们要给中间目标文件打个包，在Windows下这种包叫“库文件”（Library File)，也就是 .lib 文件，在UNIX下，是Archive File，也就是 .a 文件。

总结一下，源文件首先会生成中间目标文件，再由中间目标文件生成执行文件。在编译时，编译器只检测程序语法，和函数、变量是否被声明。如果函数未被声明，编译器会给出一个警告，但可以生成Object File。而在链接程序时，链接器会在所有的Object File中找寻函数的实现，如果找不到，那到就会报链接错误码（Linker Error），在VC下，这种错误一般是：Link 2001错误，意思说是说，链接器未能找到函数的实现。你需要指定函数的Object File.

Makefile
make命令执行时，需要一个 Makefile 文件，以告诉make命令需要怎么样的去编译和链接程序。

首先，我们用一个示例来说明Makefile的书写规则。我们的规则是：
1）如果这个工程没有编译过，那么我们的所有C文件都要编译并被链接。
2）如果这个工程的某几个C文件被修改，那么我们只编译被修改的C文件，并链接目标程序。
3）如果这个工程的头文件被改变了，那么我们需要编译引用了这几个头文件的C文件，并链接目标程序。

只要我们的Makefile写得够好，所有的这一切，我们只用一个make命令就可以完成，make命令会自动智能地根据当前的文件修改的情况来确定哪些文件需要重编译，从而自己编译所需要的文件和链接目标程序。



Makefile的规则：

target…：dependecies…

    command
target也就是一个目标文件，可以是Object File，也可以是执行文件。还可以是一个标签（Label），对于标签这种特性，在后续的“伪目标”章节中会有叙述。
dependicies就是，要生成那个target所需要的文件或是目标。
command也就是make需要执行的命令。（任意的Shell命令）
这是一个文件的依赖关系，也就是说，target这一个或多个的目标文件依赖于dependicies中的文件，其生成规则定义在command中。说白一点就是说，dependicies中如果有一个以上的文件比target文件要新的话，command所定义的命令就会被执行。这就是Makefile的规则。也就是Makefile中最核心的内容。（深入探讨makefile）

注意事项：

1.命令要以[Tab]为开始

2.有clean





4.什么是多态，多态有什么用途。

定义：“一个接口，多种方法”，程序在运行时才决定调用的函数。
实现：C++多态性主要是通过虚函数实现的，虚函数允许子类重写override(注意和overload的区别，overload是重载，是允许同名函数的表现，这些函数参数列表/类型不同）。
多态与非多态的实质区别就是函数地址是早绑定还是晚绑定。如果函数的调用，在编译器编译期间就可以确定函数的调用地址，并生产代码，是静态的，就是说地址是早绑定的。而如果函数调用的地址不能在编译器期间确定，需要在运行时才确定，这就属于晚绑定。
3.目的：接口重用。封装可以使得代码模块化，继承可以扩展已存在的代码，他们的目的都是为了代码重用。而多态的目的则是为了接口重用。

4.用法：声明基类的指针，利用该指针指向任意一个子类对象，调用相应的虚函数，可以根据指向的子类的不同而实现不同的方法。

补充一下关于重载、重写、隐藏（总是不记得）的区别：

复制代码
Overload(重载)：在C++程序中，可以将语义、功能相似的几个函数用同一个名字表示，但参数或返回值不同（包括类型、顺序不同），即函数重载。
（1）相同的范围（在同一个类中）；
（2）函数名字相同；
（3）参数不同；
（4）virtual 关键字可有可无。
Override(重写)：是指派生类函数覆盖基类函数，特征是：
（1）不同的范围（分别位于派生类与基类）；
（2）函数名字相同；
（3）参数相同；
（4）基类函数必须有virtual 关键字。
注：重写基类虚函数的时候，会自动转换这个函数为virtual函数，不管有没有加virtual，因此重写的时候不加virtual也是可以的，不过为了易读性，还是加上比较好。
Overwrite(隐藏)：隐藏，是指派生类的函数屏蔽了与其同名的基类函数，规则如下：
（1）如果派生类的函数与基类的函数同名，但是参数不同。此时，不论有无virtual关键字，基类的函数将被隐藏（注意别与重载混淆）。
（2）如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有virtual关键字。此时，基类的函数被隐藏（注意别与覆盖混淆）。
复制代码
补充一下虚函数表：

多态是由虚函数实现的，而虚函数主要是通过虚函数表（V-Table）来实现的。

如果一个类中包含虚函数（virtual修饰的函数），那么这个类就会包含一张虚函数表，虚函数表存储的每一项是一个虚函数的地址。如下图：



这个类的每一个对象都会包含一个虚指针（虚指针存在于对象实例地址的最前面，保证虚函数表有最高的性能），这个虚指针指向虚函数表。

注：对象不包含虚函数表，只有虚指针，类才包含虚函数表，派生类会生成一个兼容基类的虚函数表。

原始基类的虚函数表
下图是原始基类的对象，可以看到虚指针在地址的最前面，指向基类的虚函数表（假设基类定义了3个虚函数）



单继承时的虚函数（无重写基类虚函数）
假设现在派生类继承基类，并且重新定义了3个虚函数，派生类会自己产生一个兼容基类虚函数表的属于自己的虚函数表。



Derive class 继承了 Base class 中的三个虚函数，准确的说，是该函数实体的地址被拷贝到 Derive类的虚函数表，派生类新增的虚函数置于虚函数表的后面，并按声明顺序存放。

单继承时的虚函数（重写基类虚函数）
现在派生类重写基类的x函数，可以看到这个派生类构建自己的虚函数表的时候，修改了base::x()这一项，指向了自己的虚函数。



多重继承时的虚函数（Derived ::public Base1,public Base2）
这个派生类多重继承了两个基类base1，base2，因此它有两个虚函数表。



它的对象会有多个虚指针（据说和编译器相关），指向不同的虚函数表。

多重继承时指针的调整：

Derive b;
Base1* ptr1 = &b;   // 指向 b 的初始地址
Base2* ptr2 = &b;   // 指向 b 的第二个子对象
因为 Base1 是第一个基类，所以 ptr1 指向的是 Derive 对象的起始地址，不需要调整指针（偏移）。

因为 Base2 是第二个基类，所以必须对指针进行调整，即加上一个 offset，让 ptr2 指向 Base2 子对象。

当然，上述过程是由编译器完成的。

Base1* b1 = (Base1*)ptr2;
b1->y();                   // 输出 Base2::y()
Base2* b2 = (Base2*)ptr1;
b2->y();                   // 输出 Base1::y()
其实，通过某个类型的指针访问某个成员时，编译器只是根据类型的定义查找这个成员所在偏移量，用这个偏移量获取成员。由于 ptr2 本来就指向 Base2 子对象的起始地址，所以b1->y()调用到的是Base2::y()，而 ptr1 本来就指向 Base1 子对象的起始地址（即 Derive对象的起始地址），所以b2->y()调用到的是Base1::y()。

虚继承时的虚函数表
虚继承的引入把对象的模型变得十分复杂，除了每个基类（MyClassA和MyClassB）和公共基类（MyClass）的虚函数表指针需要记录外，每个虚拟继承了MyClass的父类还需要记录一个虚基类表vbtable的指针vbptr。MyClassC的对象模型如图4所示。



虚基类表每项记录了被继承的虚基类子对象相对于虚基类表指针的偏移量。比如MyClassA的虚基类表第二项记录值为24，正是MyClass::vfptr相对于MyClassA::vbptr的偏移量，同理MyClassB的虚基类表第二项记录值12也正是MyClass::vfptr相对于MyClassA::vbptr的偏移量。（虚函数与虚继承深入探讨）

对象模型探讨：



1.没有继承情况,vptr存放在对象的开始位置,以下是Base1的内存布局

m_iData :100


2.单继承的情况下,对象只有一个vptr,它存放在对象的开始位置,派生类子对象在父类子对象的最后面,以下是D1的内存布局
B1:: m_iData : 100

B1::vptr : 4294800

B2::vptr : 4294776

D::m_iData :300


4. 虚拟继承情况下,虚父类子对象会放在派生类子对象之后,派生类子对象的第一个位置存放着一个vptr,虚拟子类子对象也会保存一个vptr,以下是VD1的内存布局



Unknown : 4294888

B1::vptr :4294864

VD1::vptr :        4294944

VD1::m_iData :  200

VD2::Unknown : 4294952

VD::m_iData : 500

B1::m_iData :  100

5. 棱形继承的情况下,非虚基类子对象在派生类子对象前面,并按照声明顺序排列,虚基类子对象在派生类子对象后面

VD1::Unknown : 4294968

VD2::vptr :    4   294932

VD2::m_iData : 300

B1::vptr :       4294920

B1::m_iData :  100



补充一下纯虚函数：

定义： 在很多情况下，基类本身生成对象是不合情理的。为了解决这个问题，方便使用类的多态性，引入了纯虚函数的概念，将函数定义为纯虚函数（方法：virtual ReturnType Function()= 0;）纯虚函数不能再在基类中实现，编译器要求在派生类中必须予以重写以实现多态性。同时含有纯虚拟函数的类称为抽象类，它不能生成对象。
特点：
1，当想在基类中抽象出一个方法，且该基类只做能被继承，而不能被实例化；（避免类被实例化且在编译时候被发现，可以采用此方法）

2，这个方法必须在派生类(derived class)中被实现；

目的：使派生类仅仅只是继承函数的接口。
补充一下纯虚函数：
定义：称带有纯虚函数的类为抽象类。
作用：为一个继承体系提供一个公共的根，为派生类提供操作接口的通用语义。
特点：1.抽象类只能作为基类来使用，而继承了抽象类的派生类如果没有实现纯虚函数，而只是继承纯虚函数，那么该类仍旧是一个抽象类，如果实现了纯虚函数，就不再是抽象类。
2.抽象类不可以定义对象。
补充一下多重继承和虚继承：
多重继承：
定义：派生类继承多个基类，派生类为每个基类（显式或隐式地）指定了访问级别——public、protected 或 private。
class Panda : public Bear, public Endangered {
}
构造：

派生类的对象包含每个基类的基类子对象。
派生类构造函数初始化所有基类（多重继承中若没有显式调用某个基类的构造函数，则编译器会调用该基类默认构造函数），派生类只能初始化自己的基类，并不需要考虑基类的基类怎么初始化。
多重继承时，基类构造函数按照基类构造函数在类派生列表中的出现次序调用。
析构：总是按构造函数运行的逆序调用析构函数。（基类的析构函数最好写成virtual，否则再子类对象销毁的时候，无法销毁子类对象部分资源。）假定所有根基类都将它们的析构函数适当定义为虚函数，那么，无论通过哪种指针类型删除对象，虚析构函数的处理都是一致的。

拷贝构造/赋值：如果要为派生类编写拷贝构造函数，则需要为调用基类相应拷贝构造函数并为其传递参数，否则只会拷贝派生类部分。
深拷贝与浅拷贝：
浅拷贝：默认的复制构造函数只是完成了对象之间的位拷贝，也就是把对象里的值完全复制给另一个对象，如A=B。这时，如果B中有一个成员变量指针已经申请了内存，那A中的那个成员变量也指向同一块内存。
这就出现了问题：当B把内存释放了（如：析构），这时A内的指针就是野指针了，出现运行错误。
深拷贝：自定义复制构造函数需要注意，对象之间发生复制，资源重新分配，即A有5个空间，B也应该有5个空间，而不是指向A的5个空间。
虚继承与虚基类：

定义：在多重继承下，一个基类可以在派生层次中出现多次。（派生类对象中可能出现多个基类对象）在 C++ 中，通过使用虚继承解决这类问题。虚继承是一种机制，类通过虚继承指出它希望共享其虚基类的状态。在虚继承下，对给定虚基类，无论该类在派生层次中作为虚基类出现多少次，只继承一个共享的基类子对象。共享的基类子对象称为虚基类。

用法：istream 和 ostream 类对它们的基类进行虚继承。通过使基类成为虚基类，istream 和 ostream 指定，如果其他类（如 iostream 同时继承它们两个，则派生类中只出现它们的公共基类ios的一个副本。通过在派生列表中包含关键字 virtual 设置虚基类：
class istream : public virtual ios { ... };
class ostream : virtual public ios { ... };
// iostream inherits only one copy of its ios base class
class iostream: public istream, public ostream { ... };




2.static 和const分别怎么用，类里面static和const可以同时修饰成员函数吗。

static的作用：

对变量：

1.局部变量：

在局部变量之前加上关键字static，局部变量就被定义成为一个局部静态变量。

1）内存中的位置：静态存储区

2）初始化：局部的静态变量只能被初始化一次，且C中不可以用变量对其初始化，而C++可以用变量对其初始化。（详见：http://www.cnblogs.com/novice-dxx/p/7094690.html）

3）作用域：作用域仍为局部作用域，当定义它的函数或者语句块结束的时候，作用域随之结束。

注：当static用来修饰局部变量的时候，它就改变了局部变量的存储位置（从原来的栈中存放改为静态存储区）及其生命周期（局部静态变量在离开作用域之后，并没有被销毁，而是仍然驻留在内存当中，直到程序结束，只不过我们不能再对他进行访问），但未改变其作用域。

2.全局变量

在全局变量之前加上关键字static，全局变量就被定义成为一个全局静态变量。

1）内存中的位置：静态存储区（静态存储区在整个程序运行期间都存在）

2）初始化：未经初始化的全局静态变量会被程序自动初始化为0（自动对象的值是任意的，除非他被显示初始化）

3）作用域：全局静态变量在声明他的文件之外是不可见的。准确地讲从定义之处开始到文件结尾。

注：static修饰全局变量，并未改变其存储位置及生命周期，而是改变了其作用域，使当前文件外的源文件无法访问该变量，好处如下：（1）不会被其他文件所访问，修改（2）其他文件中可以使用相同名字的变量，不会发生冲突。对全局函数也是有隐藏作用。而普通全局变量只要定义了，任何地方都能使用，使用前需要声明所有的.c文件，只能定义一次普通全局变量，但是可以声明多次（外部链接）。注意：全局变量的作用域是全局范围，但是在某个文件中使用时，必须先声明。

对类中的：

    1.成员变量

    用static修饰类的数据成员实际使其成为类的全局变量，会被类的所有对象共享，包括派生类的对象。因此，static成员必须在类外进行初始化(初始化格式： int base::var=10;)，而不能在构造函数内进行初始化，不过也可以用const修饰static数据成员在类内初始化 。

    特点：

不要试图在头文件中定义(初始化)静态数据成员。在大多数的情况下，这样做会引起重复定义这样的错误。即使加上#ifndef #define #endif或者#pragma once也不行。
静态数据成员可以成为成员函数的可选参数，而普通数据成员则不可以。
静态数据成员的类型可以是所属类的类型，而普通数据成员则不可以。普通数据成员的只能声明为 所属类类型的指针或引用。
2.成员函数

用static修饰成员函数，使这个类只存在这一份函数，所有对象共享该函数，不含this指针。
静态成员是可以独立访问的，也就是说，无须创建任何对象实例就可以访问。base::func(5,3);当static成员函数在类外定义时不需要加static修饰符。
在静态成员函数的实现中不能直接引用类中说明的非静态成员，可以引用类中说明的静态成员。因为静态成员函数不含this指针。
不可以同时用const和static修饰成员函数。

C++编译器在实现const的成员函数的时候为了确保该函数不能修改类的实例的状态，会在函数中添加一个隐式的参数const this*。但当一个成员为static的时候，该函数是没有this指针的。也就是说此时const的用法和static是冲突的。

我们也可以这样理解：两者的语意是矛盾的。static的作用是表示该函数只作用在类型的静态变量上，与类的实例没有关系；而const的作用是确保函数不能修改类的实例的状态，与类型的静态变量没有关系。因此不能同时用它们。

const的作用：

1.限定变量为不可修改。

2.限定成员函数不可以修改任何数据成员。

3.const与指针：

const char *p 表示 指向的内容不能改变。

char * const p，就是将P声明为常指针，它的地址不能改变，是固定的，但是它的内容可以改变



当i是一个整数的时候++i和i++那个更快一点？i++和++i的区别是什么？
答：理论上++i更快，实际与编译器优化有关，通常几乎无差别。
i++实现的代码为：

//i++实现代码为：                                    
int operator++(int)                                  
{
int temp = *this;                                     
++*this;                                             
return temp;                                    
}//返回一个int型的对象本身
++i的实现代码：

// ++i实现代码为：
int& operator++()
{
*this += 1;
return *this;
}//返回一个int型的对象引用
i++和++i的考点比较多，简单来说，就是i++返回的是i的值，而++i返回的是i+1的值。也就是++i是一个确定的值，是一个可修改的左值，如下使用：

    cout << ++(++(++i)) << endl;
    cout << ++ ++i << endl;
可以不停的嵌套++i。
这里有很多的经典笔试题，一起来观摩下：

int main()
{

    int i = 1;
    printf("%d,%d\n", ++i, ++i);    //3,3
    printf("%d,%d\n", ++i, i++);    //5,3
    printf("%d,%d\n", i++, i++);    //6,5
    printf("%d,%d\n", i++, ++i);    //8,9
    system("pause");
    return 0;
}
首先是函数的入栈顺序从右向左入栈的，计算顺序也是从右往左计算的，不过都是计算完以后在进行的压栈操作：
对于第5行代码，首先执行++i，返回值是i，这时i的值是2，再次执行++i，返回值是i，得到i=3，将i压入栈中，此时i为3，也就是压入3，3；
对于第6行代码，首先执行i++，返回值是原来的i，也就是3，再执行++i，返回值是i，依次将3，5压入栈中得到输出结果
对于第7行代码，首先执行i++，返回值是5，再执行i++返回值是6，依次将5，6压入栈中得到输出结果
对于第8行代码，首先执行++i，返回i，此时i为8，再执行i++，返回值是8，此时i为9，依次将i，8也就是9，8压入栈中，得到输出结果。
上面的分析也是基于vs搞的，不过准确来说函数多个参数的计算顺序是未定义的(the order of evaluation of function arguments are undefined)。笔试题目的运行结果随不同的编译器而异。
参考：http://www.stroustrup.com/bs_faq2.html#evaluation-order
下面是使用其他编译器输出的结果：

//------ C++ version ------
#include <cstdio>
int main()
{
int i = 1;
printf("%d %d\n", ++i, ++i);
printf("%d %d\n", ++i, i++);
printf("%d %d\n", i++, i++);
printf("%d %d\n", i++, ++i);
return 0;
}

//------ C version ------
#include <stdio.h>
int main()
{
int i = 1;
printf("%d %d\n", ++i, ++i);
printf("%d %d\n", ++i, i++);
printf("%d %d\n", i++, i++);
printf("%d %d\n", i++, ++i);
return 0;
}
上面是参考的执行代码。
gcc-5.1(C++) gcc-5.1(C++14) gcc-5.1(C) 的执行结果：

3 3
5 3
6 5
8 9
gcc-4.3.2(C++) clang-3.7(C++) clang-3.7(C) 的执行结果

2 3
4 4
5 6
7 9
gcc-5.1(C99 strict) 的编译结果：编译不通过。

C99 strict prog.c: In function 'main':
prog.c:6:28: error: operation on 'i' may be undefined [-Werror=sequence-point]
printf("%d %d\n", ++i, ++i);
^
prog.c:7:29: error: operation on 'i' may be undefined [-Werror=sequence-point]
printf("%d %d\n", ++i, i++);
^
prog.c:8:29: error: operation on 'i' may be undefined [-Werror=sequence-point]
printf("%d %d\n", i++, i++);
^
prog.c:9:28: error: operation on 'i' may be undefined [-Werror=sequence-point]
printf("%d %d\n", i++, ++i);
^
cc1: all warnings being treated as errors
由上可见，这种比较毫无意义。



如何初始化const和static数据成员？
答：通常在类外初始化static数据成员，但是 static const 的整型(bool，char，int，long)可以再类声明中初始化，static const的其他类型也必须在类外初始化(包括整型的数组)。




如何实现单例模式？如何避免发生对象的用户复制行为？如何实现线程安全的单例模式？DCLP是什么，有什么问题？
答：
(1)、将构造函数、析构函数、复制构造函数、赋值操作符声明为私有，即可实现单例模式
单例模式实现代码通常为：

class Singleton
{
public:
static Singleton* Instance();
protected:
Singleton();
private:
static Singleton* _instance;
};
Singleton::Singleton(){}
Singleton* Singleton::_instance = nullptr;
Singleton* Singleton::Instance()
{
if(_instance == nullptr)
_instance = new Singleton;
return _instance;
}
(2)、避免用户的复制行为，可以将复制构造函数声明为private或者使用C++11中的delete语法。
(3)、实现线程安全的单例模式：上面实现中的GetInstance()不是线程安全的，因为在单例的静态初始化中存在竞争条件。如果碰巧有多个线程在同时调用该方法，那么就有可能被构造多次。
比较简单的做法是在存在竞争条件的地方加上互斥锁。这样做的代价是开销比较高。因为每次方法调用时都需要加锁。
比较常用的做法是使用双重检查锁定模式(DCLP)。但是DCLP并不能保证在所有编译器和处理器内存模型下都能正常工作。如，共享内存的对称多处理器通常突发式提交内存写操作，这会造成不同线程的写操作重新排序。这种情况通常可以采用volatile解决，他能将读写操作同步到易变数据中，但这样在多线程环境下仍旧存在问题。



如果在构造函数和析构函数中抛出异常会发生什么？什么是栈展开？
答： (1)、构造函数抛异常：不会发生资源泄漏。假设在operator new()时抛出异常，那么将会因异常而结束此次调用，内存分配失败，不可能存在内存泄露。假设在别处(operator new() )执行之后抛出异常，此时析构函数调用，已构造的对象将得以正确释放，且自动调用operator delete()释放内存
析构函数抛异常：
可以抛出异常，但该异常必须留在析构函数；若析构函数因异常退出，情况会很糟糕(all kinds of bad things are likely to happen)
a、可能使得已分配的对象未能正常析构，造成内存泄露；
b、例如在对像数组的析构时，如果对象的析构函数抛出异常，释放代码将引发未定义行为。考虑一个对象数组的中间部分在析构时抛出异常，它无法传播，因为传播的话将使得后续部分不能正常释放；它也无法吸收，因为这违反了”异常中立“原则(异常中立，就是指任何底层的异常都会抛出到上层，也就相当于是异常透明的)。
(2)、抛出异常时，将暂停当前函数的执行，开始查找匹配的catch子句。首先检查throw本身是否在try块内部如果是，检查与该try相关的catch子句，看是否可以处理该异常。如果不能处理，就退出当前函数，并且释放当前函数的内存并销毁局部对象，继续到上层的调用函数中查找，直到找到一个可以处理该异常的catch。


相等和等价的区别？哪些类型的容器使用相等或等价？
答： 相等(equality)是以operator==为基础，如果x==y为真，则判定x和y相等。
等价(equavalence)是以operator<为基础，如果!(x < y) && !(y <




如何在const成员函数中赋值？
答：使用mutable去掉const的成员函数的const性质
const_cast和mutable的比较
const_cast:
1) 强制去掉对象的const属性。
2) 缺点：对const对象，调用包含const_cast的const成员函数，属于未定义行为。
   mutable:
1) 使用场景：对可能要发生变化的成员前，加上存储描述符mutable。
2) 实质：对加了mutable的成员，无视所有const声明。
   为什么要有这种去除常量标志的需求？
   答：两个概念：物理常量性和逻辑常量性
   物理常量性：实际上就是常量。
   逻辑常量性：对用户而言是常量，但在用户不能访问的细节上不是常量。





两种常用的实现隐式类类型转换的方式是什么？如何避免隐式类型转换？
答：(1)、
a、使用单参数的构造函数或N个参数中有N-1个是默认参数的构造函数，如：

class A
{
public：
A(stirng s);
A(string s,int a = 0);
};
b、使用operator what_you_want_to_convert_type() const

        class A
        {
        public:
                operator char*() const
                {
                    return data;//当从其他类型转换到char*时自动调用
                }
        private:
                char* data;
        };
(2)、在单参数的构造函数或N个参数中有N-1个是默认参数的构造函数声明之前加上explicit。


STL中的vector：增减元素对迭代器的影响
解答：这个问题主要是针对连续内存容器和非连续内存容器。
a、对于连续内存容器，如vector、deque等，增减元素均会使得当前之后的所有迭代器失效。因此，以删除元素为例：由于erase()总是指向被删除元素的下一个元素的有效迭代器，因此，可以利用该连续内存容器的成员erase()函数的返回值。常见的编程写法为：

    for(auto iter = myvec.begin(); iter != myvec.end())  //另外注意这里用 "!=" 而非 "<"
    {
        if(delete iter)
            iter = myvec.erase(iter);
        else ++iter;
    }
还有两种极端的情况是：
(1)、vector插入元素时位置过于靠前，导致需要后移的元素太多，因此vector增加元素建议使用push_back而非insert；
(2)、当增加元素后整个vector的大小超过了预设，这时会导致vector重新分分配内存，效率极低。因此习惯的编程方法为：在声明了一个vector后，立即调用reserve函数，令vector可以动态扩容。通常vector是按照之前大小的2倍来增长的。
b、对于非连续内存容器，如set、map等。增减元素只会使得当前迭代器无效。仍以删除元素为例，由于删除元素后，erase()返回的迭代器将是无效的迭代器。因此，需要在调用erase()之前，就使得迭代器指向删除元素的下一个元素。常见的编程写法为：

    for(auto iter = myset.begin(); iter != myset.end())  //另外注意这里用 "!=" 而非 "<"
    {
        if(delete iter)
            myset.erase(iter++);  //使用一个后置自增就OK了
        else ++iter;
    }
其实在C++11中erase的返回值就是下一个节点，也可以利用函数的返回值。




New和malloc的区别
解答：这个问题答案过于复杂，建议直接百度这个问题，网上的说法已经足够完善。
不过针对网上的一些说法补充并且纠正一下。网上在回答这个问题的时候没有对new操作符进行深入的解释，在这里大致说一下。
new可分为operator new(new 操作)、new operator(new 操作符)和placement new(定位 new)。其中operator new执行和malloc相同的任务，即分配内存，但对构造函数一无所知；而 new operator则调用operator new，分配内存后再调用对象构造函数进行对象的构造。
其中operator new是可以重载的。placement new，就是operator new的一个重载版本，允许你在一个已经分配好的内存中构造一个新的对象。而网上对new说法，大多针对operator new而言，因此说new是带有类型的(以为调用了类的构造函数)，不过如果直接就说new是带有类型的话，明显是不合适的，比如原生的operator new。可以参考我的一个程序，这个程序是用代理模式实现一个自定义二维数组，在第二个维度拷贝构造的时候， 拷贝构造需要深拷贝(当然第一个维度也需要)，执行深拷贝时代码大致如下：

    class Array2D    //二维数组模板
    {
    private:
            size_t length2,length1; //数组各个维的大小
            Array1D<T>* data;
    }
    void* raw  =::operator new[](length2*sizeof(Array1D<T>));
        data = static_cast<Array1D<T>*>(raw);
可见执行operator new的时候申请的原生内存是可以不带有类型的。
1) malloc()分配指定字节数的未经初始化的内存空间，返回的是void指针；new操作符为一个指定类型的对象分配空能，并调用其构造函数初始化，返回的是该对象的指针。
2) malloc()必须要做初始化，以及将void指针转换成合适类型的指针。同时要考虑到分配的内存大小正好是你所需要的大小。当new操作符使用"(value)" notation，即可得到值为value的初始化。如果考虑上初始化的开销，malloc()和new没有性能上的差别。



C++如何避免内存泄漏
解答：这其实可以看做是一个编程风格的问题。
a、使用RAII(Resource Acquisition Is Initialization,资源获取即初始化)技法，以构造函数获取资源(内存),析构函数释放。
b、相比于使用原生指针，更建议使用智能指针，尤其是C++11标准化后的智能指针。
c、注意delete和delete[]的使用方法。
d、这是很复杂的一种情况，是关于类的copy constructor的。首先先介绍一些概念。
同default constructor一样，标准保证，如果类作者没有为class声明一个copy constructor，那么编译器会在需要的时候产生出来(这也是一个常考点：问道"如果类作者未定义出default/copy constructor，编译器会自动产生一个吗？"答案是否定的)
不过请注意！！这里编译器即使产生出来，也是为满足它的需求，而非类作者的需求！！
而什么时候是编译器"需要"的时候呢？是在当这个class 【不表现出】bitwise copy semantics(位逐次拷贝，即浅拷贝)的时候。
在4中情况下class【不表现出】bitwise copy semantics
(1)、当class内含一个member object且该member object声明了一个copy constructor(无论该copy ctor是类作者自己生明的还是编译器合成的)；
(2)、当class继承自一个base class且该base class有一个copy constructor(无论该copy ctor是类作者自己生明的还是编译器合成的)；
(3)、当class声明了virtual function；
(4)、当class派生自一个继承链，且该链中存在virtual base class时。
言归正传，如果class中仅仅是一些普通资源，那么default memberwise copy是完全够用的；然而，挡在该class中存在了一块动态分配的内存，并且在之后执行了bitwise copy semantics后，将会有一个按位拷贝的对象和原来class中的某个成员指向同一块heap空间，当执行它们的析构函数后，该内存将被释放两次，这是未定义的行为。因此，在必要的时候需要使用user-defined explicit copy constructor，来避免内存泄露。



指针数组和数组指针的区别
顾名思义，数组指针应该是指向数组的指针，而指针数组则是指该数组的元素均为指针。
数组指针，是指向数组的指针，其本质为指针，形如int (*p)[10]，p即为指向数组的指针；数组指针是指向数组首元素的地址的指针，其本质为指针，可以看成是二级指针

指针数组，在C语言和C++中，数组元素全为指针的数组称为指针数组，其中一维指针数组的定义形式为：
类型名 *数组标识符[数组长度]
指针数组中每一个元素均为指针，其本质为数组，例如我们经常使用的动态数组的就是基于此的使用，如下示例：

size_t row,col;
//输入row和col的数值
int **MathTable = new int*[row];
for( int i = 0 ; i < row ; i++ )
MathTable[i] = new int[col];
//code
for( int i = 0 ; i < row ; i++ )
delete [] MathTable[i];
delete []MathTable;
也就是形如int p[10]这样的声明，就是我们这里的指针数组，从声明形态上来讲，是由于[]的优先级高于，又有诸如下面的指针：

*ptr_arry[i]
指针数组中的元素可以表示为：

*(*(ptr_arry+i))
()的优先级较高，又由于又结合的原因，可以化简为：

**(ptr_arry+i)
由于数组元素均为指针，因此prt_array[i]是指第i+1个元素的指针。



指针函数和函数指针
此处还有两个需要区分的概念，就是函数指针和指针函数。
函数指针
函数指针：指向函数的指针变量，在C编译时，每一个函数都有一个入口地址，那么指向这个函数的函数指针便是指向这个地址。函数指针主要有两个作用：用作调用函数和做函数的参数。
int (*func)(int x);
诸如上面的代码这是申明了一个函数指针，代码(*func)中括号是必须的，这会告诉编译器这是一个函数指针而不是声明一个具有返回类型为指针的函数，后面的形参要是这个函数所指向的函数形参而定。使用如下面的代码：

#include <iostream>

using namespace std;

int(*func)(int a, int b);
int bar(int a, int b)
{
return a + b;
}



int foo(int a, int b)
{
return a;
}
int _tmain(int argc, _TCHAR* argv[])
{
func = bar;
cout << func(12, 34) << endl;
system("pause");
func = foo;
cout << func(12, 34) << endl;
system("pause");
return 0;
}
这样的声明有些繁琐，其实可以使用typedef来进行简化：

#include <iostream>

using namespace std;

typedef int(*PF)(int, int);
//int(*func)(int a, int b);
int bar(int a, int b)
{
return a + b;
}



int foo(int a, int b)
{
return a;
}
int _tmain(int argc, _TCHAR* argv[])
{
PF func;
func = bar;
cout << func(12, 34) << endl;
system("pause");
func = foo;
cout << func(12, 34) << endl;
system("pause");
return 0;
}
函数指针的另一个作用就是作为函数的参数，可以在一个函数的形参列表中传入函数指针，然后边可以在这个函数中使用这个函数指针所指向的函数，这样边可以使程序变得更加清晰和简洁。

#include <iostream>

using namespace std;

typedef int(*PF)(int, int);
//int(*func)(int a, int b);
int bar(int a, int b)
{
return a + b;
}



int foo(int a, int b)
{
return a;
}


void func(int a, int b, PF ptr)
{
cout << ptr(a, b) << endl;
return;
}
int _tmain(int argc, _TCHAR* argv[])
{
PF ptr;
ptr = bar;
func(12, 34, ptr);
system("pause");
ptr = foo;
func(12, 34, ptr);
system("pause");
return 0;
}
一旦知道函数指针是如何工作的，我们就可以构建一些复杂的定义，例如：

void *(*(*fp1)(int))[10];
fp1是一个指向函数的指针，该函数接受一个整型参数，并且返回类型是一个指向包含了10个void指针数组的指针。是不是很绕？

float (*((*fp2)(int,int,float)))(int);
fp2是一个指向函数的指针，该函数接受三个参数(int,int,float)，返回值是一个指向函数的指针，该函数接受一个整型参数并返回一个float。

typedef doubele (*(*(*fp3)())[10])();
fp3是一个函数指针，该函数无参数，且返回一个指向含有10个指向函数指针指针数组的指针，这些函数不接收参数，且返回值是double值

int (*(*fp4())[10])();
fp4是一个返回指针的函数，该指针指向含有10个函数指针的数组，这些函数的返回值是整型。

指针函数
与函数指针相区别的定义应该就是指针函数，指针函数本质上是一个函数，是指函数的返回值为指针的函数，一般是形如下的函数：
int* func(int x,int y);
如上就是一个返回值是指针的函数，很常见。
函数对象
上面谈到了函数指针以及应用，这里涉猎下函数对象。从一般函数回调意义上来说，函数对象和函数指针是相同的，但是函数对象却具有许多函数指针不具有的优点，函数对象使程序设计更加灵活，而且能够实现函数的内联（inline）调用，使整个程序实现性能加速。


关于shared_ptr使用需要记住什么？
总结下来需要注意的大概有下面几点：
1）、尽量避免使用raw pointer构建shared_ptr，至于原因此处不便于多讲，后续还有讲解
2）、shared_ptr使得依据共享生命周期而经行地资源管理进行垃圾回收更为方便
3）、shared_ptr对象的大小通常是unique_ptr的两倍，这个差异是由于Control Block导致的，并且shared_ptr的引用计数的操作是原子的，这里的分析也会在后续看到
4）、默认的资源销毁是采用delete，但是shared_ptr也支持用户提供deleter，与unique_ptr不同，不同类型的deleter对shared_ptr的类型没有影响。



26、C++的内存对齐
为什么要内存对齐？这个网上讲得更全面，就不再多说了。简而言之，为了速度和正确性。详见网页：http://blog.csdn.net/lgouc/article/details/8235471，英文原版：（http://www.ibm.com/developerworks/library/pa-dalign/）

C/C++中的内存对齐之基础篇
这里主要以【不带有】虚继承链和虚函数的struct/class为例,【注意：所有的空间均需要为最大类型大小的整数倍】

这里有一个C和C++不同的情况：在C中，空struct/class不占有内存，在C++中，空struct/class通常占有1byte的空间，原因是编译器强行在里面放入了一个char，这样可以使得这个class的不同实例化在内存中分配到独一无二的地址。

最基本的内存对齐情况(其中注释代表该类型实际大小)

        struct A
        {
                char   c; //1byte
                double d; //8byte
                int i;       //4byte
        };
在64位g++和vs2013下运行sizeof(A)结果均为24。这种情况下的计算都比较简单，首先确定最大类型的大小，这里是double，因此Max = 8，因此占据的空间就应该是8的倍数(相应的，若struct内最大的类型为int，那么占据的空间就应该是4的倍数)。补齐的大小就根据最大类型的长度来确定。通常在内存中按照变量声明的顺序来分配空间，先为char分配，占据1byte， 8 - 1 = 7，剩余空间小于下一个变量double的需要空间，因此另外开辟一个8byte用于安放double，紧接着安放int，它占据另一个8byte空间的4个byte。而char后面的7byte、int后面的4byte都用于内存对齐。
因此总大小为8+8+8 = 24(可以看成1+7 + 8 + 4+4)。

        struct A
        {
                double d; //8byte
                char   c; //1byte
                int i; //4byte
        };
在64位g++和vs2013下运行sizeof(A)结果均为16。根据上述说明，很容易得到 8 + 1+4+3 = 16，其中3为char、int之后的补齐。

稍复杂一点的内存对其情况

        class A
        {
        public:
                static double dd;
                char   c; //1byte
                double d; //8byte
                static A a;
                int i; //4byte
        };
在64位g++和vs2013下运行sizeof(A)结果均为24。这里只需要注意一下，static data member会被放在class object之外。因此sizeof(A)时，不会计算他们的大小在内。其余计算同 2 中的第一个例子相同。

只有一种类型时的情况：如一个struct中仅有一个char或int等，由于“所有的空间均需要为最大类型大小的整数倍”这个原则，struct的空间大小就是这些类型各自的大小，而不用再进行补齐。
C/C++中的内存对齐之深入篇——虚继承和虚函数

        class A
        {
        public:
                virtual ~A();
                char   c; //1byte
                double d; //8byte
                int i; //4byte
        };
在32位g++下运行sizeof(A)结果为24，在64位g++下运行sizeof(A)结果为32，在vs2013下运行sizeof(A)结果为32。
32位g++下：通常将vptr放在object的最前面，可以确定该内存空间与data member的内存空间不需要独立。也就是说，该例中，无论虚析构函数被声明在哪里，都会在分配空间时最先给一个vptr分配4byte的空间，且该空间后是可以紧接着分配char的1byte的空间。以此类推，结合上面的例子，可以得出4(vptr)+1(char)+3(补齐) + 8 + 4+4 = 24
64位g++下：通常将vptr放在object的最前面，无法确定该内存空间与data member的内存空间是否需要独立。也就是说，该例中，无论虚析构函数被声明在哪里，都会在分配空间时最先给一个vptr分配8byte的空间，且不清楚该空间后是否可以紧接着分配char的1byte的空间(由于该vptr占据8byte，无论是否需要间隔，效果都一样)，以此类推，结合上面的例子，可以得出

8(vptr)+ 1(char)+7(补齐) + 8 + 4+4 = 32
在vs2013下：通常将vptr放在object的最前面，vptr的大小与实际最大类型的大小相关。也就说说，该例中，无论虚析构函数被声明
在哪里，都会在分配空间时最先给一个vptr分配4byte的空间，由于后面存在double类型，需要将vptr补齐。结合上面的例子，可以得出

4(vptr)+4(补齐) + 1+7 + 8 +4+4 = 32
2、带有普通继承的class的内存对齐情况

        class A
        {
                int i;    //4byte
                char c1;//1byte
        };
        class B :  public A
        {
                char c2;//1byte
        };
        class C :  public B
        {
             char c3;//1byte
        };
在64位g++下，调用sizeof(A)、sizeof(B)、sizeof(C)后的结果均为8；在vs2013下分别为8,12,16

g++下：普通继承时，派生类和基类的内存空间没有间隔。
A：4+1+3(补齐) = 8
B：4+1+1(c2)+2(补齐) = 8
C：4+1+1(c2)+1(c3)+1(补齐) = 8
注意这里所有成员均为私有成员，如果改成public或protected则大小会有变化
vs2013下：普通继承时，派生类和基类的内存空间需要独立，即先补齐基类，再分配派生类。
A：4+1+3(补齐) = 8
B：4+1+3(补齐) + 1(c2)+3(补齐) = 12
C：4+1+3(补齐) + 1(c2)+3(补齐) + 1(c3)+3(补齐) = 16
3、带有虚拟继承链的class的内存对齐情况

        class A
        {
                int i;    //4byte
                char c1;//1byte
        };
        class B : virtual public A
        {
                char c2;//1byte
        };
        class C : virtual public B
        {
             char c3;//1byte
        };
调用sizeof(A)、sizeof(B)、sizeof(C)后，32位g++下，分别为8,16,24；64位g++下，分别为：8,24,40；vs2013下分别为8,16,24

32位g++下：
A：仍然是4+1+3(补齐) = 8
B：4+1+3 + 4(vptr)+1(c2)+3(补齐) = 16
C；4+1+3 + 4(vptr)+1(c2)+3(补齐) + 4(vptr)+1(c3)+3(补齐) = 24
64位g++下：
A：仍然是4+1+3(补齐) = 8
B：4+1+3 + 8(vptr)+1(c2)+7(补齐) = 24
C；4+1+3 + 8(vptr)+1(c2)+7(补齐) + 8(vptr)+1(c3)+7(补齐) = 40
vs2013下：
A：仍然是4+1+3(补齐) = 8
B：4+1+3 + 4(vptr)+1(c2)+3(补齐) = 16
C；4+1+3 + 4(vptr)+1(c2)+3(补齐) + 4(vptr)+1(c3)+3(补齐) = 24
注意这里vs2013的情况表面看上去和32位g++相同，实则不然。例如去掉class B对于A的虚拟继承性
class A
{
int i;    //4byte
char c1;//1byte
};
class B :  public A    /*注意这里跟上面相比不是虚拟继承了*/
{
char c2;//1byte
};
class C : virtual public B
{
char c3;//1byte
};
调用sizeof(A)、sizeof(B)、sizeof(C)后，32位g++下：分别为8,8,16；vs2013下分别为8,12,20

32位g++下：
A：仍然是4+1+3(补齐) = 8
B：B：4+1+1(c2)+2(补齐) = 8(因为不是虚拟继承)
C；4+1+1(c2)+2(补齐) + 4(vptr)+1(c3)+3(补齐) = 16
vs2013下：
A：仍然是4+1+3(补齐) = 8
B：4+1+3(补齐) + 1(c2)+3(补齐) = 12
C；4+1+3(补齐) + 1(c2)+3(补齐) + 4(vptr)+1(c3)+3(补齐) = 20
虚基类的继承是C++中为了多重继承而产生的，但是虚基类的继承有带来了新的问题，如何能够实现这种动态绑定呢？



C++中的转化机制？各适用于什么环境？dynamic_cast转换失败时，会出现什么情况？
对指针，返回NULL.对引用，抛出bad_cast异常more Effective C++
C++引入了4种类型转化操作符（cast operator）：static_cast，const_cast，dynamic_cast和reinterpret_cast，使用方法与C语言中略有不同：

(type)expression; //这是C语言的
然后引入C++的：

static_cast<type>(expression);//这是C++的
然后看一下各自的适用范围：
static_cast：static_cast基本上拥有与C旧式转型相同的威力和意义，以及相同的限制。但是，该类型转换操作符不能移除常量性，因为有一个专门的操作符用来移除常量性。
const_cast：用来改变表达式中的常量性（constness）或者易变形（volatileness），只能用于此功能。
dynamic_cast：将指向基类basic class object的pointer或者reference转型为指向派生类derived（或这sibling base）class object的pointer或者reference中，并且可以获知是否转型成功：如果转型失败，当转型对象是指针的时候会返回一个null指针；当转型对象是reference会抛出一个异常exception。dynamic_cast无法应用在缺乏虚函数的类型上，也不能改变类型的常量性。
此外，dynamic_cast还有一个用途就是找出被对象占用的内存的起始点。
reinterpret_cast：这个操作符的转换结果几乎总是和编译器平台相关，所以不具有移植性。reinterpret_cast的最常用用途是转换“函数指针”类型，如下：

typedef void(*FuncPtr)();
int doSomething();
int main()
{
FuncPtr funcPtrArray[10];
funcPtrArray[0] = reinterpret_cast<FuncPtr>(&doSomething);
return 0;
}
通过reinterpret_cast强迫编译器了，并成功的将不同的类型的函数&doSomething转换为需要的类型。不过这个操作符进行的转换动作不具有移植性（C++不保证所有的函数指针都能以此方式重新呈现），某些情况下这样的转型可能会导致不正确的结果，所以这种操作不到万不得已不要使用。





深拷贝和浅拷贝的区别
答：浅拷贝：如果在类中没有显式地声明一个拷贝构造函数，那么，编译器将会根据需要生成一个默认的拷贝构造函数，完成对象之间的位拷贝。default memberwise copy即称为浅拷贝。
此处需要注意，并非像大多数人认为的“如果class未定义出copy constructor，那么编译器就会为之合成一个执行default memberwise copy语义的copy constructor”。
通常情况下，只有在default copy constructor被视为trivial时，才会发生上述情况。一个class，如果既没有任何base/member class含有copy constructor，也没有任何virtual base class或 virtual functions，
它就会被视为trivial。
通常情况下，浅拷贝是够用的。
深拷贝：然而在某些状况下，类内成员变量需要动态开辟堆内存，如果实行位拷贝，也就是把对象里的值完全复制给另一个对象，如A=B。
这时，如果B中有一个成员变量指针已经申请了内存，那A中的那个成员变量也指向同一块内存。如果此时B中执行析构函数释放掉指向那一块堆的指针，这时A内的指针就将成为悬挂指针。
因此，这种情况下不能简单地复制指针，而应该复制“资源”，也就是再重新开辟一块同样大小的内存空间。



virtual函数能声明为内联吗？为什么？
答：通常情况下是不能的
原因：inline是编译期决定，他意味着在执行前就将调用动作替换为被调用函数的本体；
virtual是运行期决定，他意味着直道运行期才决定调用哪个函数。
这两者之间通常是冲突的。
然而也有特例，就是当编译阶段就已经知道调用虚函数的指针为多态指针。这里就不再敖述了。


哪些类型的对象不可以作为union的成员？为什么有这种限制？
答： 标准规定，凡是具有non-trivial constructor、non-trivial destructor、non-trivial copy constructor、non-trivial assignment operator的class对象都不能作为union的成员。
即是说，这个class的以上四种成员必须均经由编译器合成且该class无虚函数和虚基类。
有这种限制是为了兼容C。


# 作用

1. 修饰变量，说明该变量不可以被改变；
2. 修饰指针，分为指向常量的指针（pointer to const）和自身是常量的指针（常量指针，const pointer）；
3. 修饰引用，指向常量的引用（reference to const），用于形参类型，即避免了拷贝，又避免了函数对值的修改；
4. 修饰成员函数，说明该成员函数内不能修改成员变量。

## const 的指针与引用

* 指针
    * 指向常量的指针（pointer to const）
    * 自身是常量的指针（常量指针，const pointer）
* 引用
    * 指向常量的引用（reference to const）
    * 没有 const reference，因为引用只是对象的别名，引用不是对象，不能用 const 修饰

## 使用

const 使用

```cpp
// 类
class A
{
private:
    const int a;                // 常对象成员，可以使用初始化列表或者类内初始化

public:
    // 构造函数
    A() : a(0) { };
    A(int x) : a(x) { };        // 初始化列表

    // const可用于对重载函数的区分
    int getValue();             // 普通成员函数
    int getValue() const;       // 常成员函数，不得修改类中的任何数据成员的值
};

void function()
{
    // 对象
    A b;                        // 普通对象，可以调用全部成员函数
    const A a;                  // 常对象，只能调用常成员函数
    const A *p = &a;            // 指针变量，指向常对象
    const A &q = a;             // 指向常对象的引用

    // 指针
    char greeting[] = "Hello";
    char* p1 = greeting;                // 指针变量，指向字符数组变量
    const char* p2 = greeting;          // 指针变量，指向字符数组常量（const 后面是 char，说明指向的字符（char）不可改变）
    char* const p3 = greeting;          // 自身是常量的指针，指向字符数组变量（const 后面是 p3，说明 p3 指针自身不可改变）
    const char* const p4 = greeting;    // 自身是常量的指针，指向字符数组常量
}

// 函数
void function1(const int Var);           // 传递过来的参数在函数内不可变
void function2(const char* Var);         // 参数指针所指内容为常量
void function3(char* const Var);         // 参数指针为常量
void function4(const int& Var);          // 引用参数在函数内为常量

// 函数返回值
const int function5();      // 返回一个常数
const int* function6();     // 返回一个指向常量的指针变量，使用：const int *p = function6();
int* const function7();     // 返回一个指向变量的常指针，使用：int* const p = function7();
```




c++11

使用c++11 让程序更简洁 更现代
类型推导
auto
decltype
返回类型后置语法：auto和decltype结合使用
模板的细节改进
列表初始化
基于范围的for循环


==============================================================
可调用对象
==============================================================

C++中，存在“可调用对象（Callable Objects）”这么一个概念。准确来说，可调用对象有如下几种定义[1]：
）是一个函数指针。
）是一个具有operator（）成员函数的类对象（仿函数）。
）是一个可被转换为函数指针的类对象。
）是一个类成员（函数）指针。
void func() {
}

struct Foo {
void operator()() {}
};

struct Bar {
using fr_t = void (*)();
static void func() {
}

    operator fr_t() {
        return func;
    }
};

struct A {
int a_;
void mem_func() {
}
};
int main() {
void (*func_ptr)() = func;
func_ptr();

    Foo foo;
    foo();

    Bar bar;
    bar();

    void (A::*mem_func_ptr)() = &A::mem_func;
    int A::*mem_obj_ptr = &A::a_;
    A a;
    (a.*mem_func_ptr)();
    std::cout << a.*mem_obj_ptr << std::endl;

    return 0;
}
从上述可以看到，除了类成员指针之外，上面定义涉及的对象均可以像一个函数那样做调用操作。
在C++11中，像上面例子中的这些对象（func_ptr、foo、bar、mem_func_ptr、mem_obj_ptr）都被称做可调用对象。
相对应的，这些对象的类型被统称为“可调用类型”。
上面对可调用类型的定义里并没有包括函数类型或者函数引用（只有函数指针）。
这是因为函数类型并不能直接用来定义对象；而函数引用从某种意义上来说，可以看做一个const的函数指针。
C++中的可调用对象虽然具有比较统一的操作形式（除了类成员指针之外，都是后面加括号进行调用），但定义方法五花八门。
这样在我们试图使用统一的方式保存，或传递一个可调用对象时，会十分烦琐。现在，C++11通过提供std：：function和std：：bind统一了可调用对象的各种操作。

==============================================================
可调用对象包装器->std::function
==============================================================

std::function是可调用对象的包装器。
它是一个类模板，可以容纳除了类成员（函数）指针之外的所有可调用对象。
通过指定它的模板参数，它可以用统一的方式处理函数、函数对象、函数指针，并允许保存和延迟执行它们。
当我们给std：：function填入合适的函数签名（即一个函数类型，只需要包括返回值和参数表）之后，它就变成了一个可以容纳所有这一类调用方式的“函数包装器”。
当std：：function和std：：bind配合起来使用时，所有的可调用对象（包括类成员函数指针和类成员指针）都将具有统一的调用方式。

==============================================================
std::bind 绑定器
==============================================================

std：：bind用来将可调用对象与其参数一起进行绑定。绑定后的结果可以使用std::function进行保存，并延迟调用到任何我们需要的时候。
通俗来讲，它主要有两大作用：
1）将可调用对象与其参数一起绑定成一个仿函数。
2）将多元（参数个数为n，n>1）可调用对象转成一元或者（n-1）元可调用对象，即只绑定部分参数。

使用auto fr保存std：：bind的返回结果，是因为我们并不关心std::bind真正的返回类型
实际上std：：bind的返回类型是一个stl内部定义的仿函数类型），只需要知道它是一个仿函数，可以直接赋值给一个std::function.

在绑定部分参数的时候，通过使用std：：placeholders，来决定空位参数将会属于调用发生时的第几个参数
std：：placeholders：：_1是一个占位符，代表这个位置将在函数调用时，被传入的第一个参数所替代。

class A {
public:
int i_ = 0;
void output(int x, int y) {
std::cout << x << " " << y << std::endl;
}
};
A a;
std::function<void(int, int)> fr =
std::bind(&A::output, &a, std::placeholders::_1, std::placeholders::_2);
fr(1, 2);// 输出: 1 2
std::function<int &()> fr_i = std::bind(&A::i_, &a);
fr_i() = 123;
std::cout << a.i_ << std::endl;// 输出: 123
}

fr的类型是std：：function<void（int，int）>。
我们通过使用std：：bind，将A的成员函数output的指针和a绑定，并转换为一个仿函数放入fr中存储。
之后，std：：bind将A的成员i_的指针和a绑定，返回的结果被放入std：：function<int&（void）>中存储，并可以在需要时修改访问这个成员。

现在，通过std：：function和std：：bind的配合，所有的可调用对象均有了统一的操作方法。
std::bind 组合多个函数：5<x<=10
auto func = std::bind(std::logical_and<bool>(), std::bind(std::greater<int>(), std::placeholders::_1, 5),
std::bind(std::less_equal<int>(), std::placeholders::_1, 10));
std::vector<int> vi{1, 11, 10};
int count = std::count_if(vi.cbegin(), vi.cend(), func);

std::cout << count << std::endl;

********************** lambda 表达式******************************

lambda来源于函数式编程的概念，也是现代编程语言的一个特点
lambda表达式有如下优点：
·声明式编程风格：就地匿名定义目标函数或函数对象，不需要额外写一个命名函数或者函数对象。以更直接的方式去写程序，好的可读性和可维护性
·简洁：不需要额外再写一个函数或者函数对象，避免了代码膨胀和功能分散，让开发者更加集中精力在手边的问题，同时也获取了更高的生产率。
·在需要的时间和地点实现功能闭包，使程序更灵活

[ capture ] ( params ) opt -> ret { body; };

允许省略lambda表达式的返回值定义, 这样编译器就会根据return语句自动推导出返回值类型。需要注意的是，初始化列表不能用于返回值的自动推导
auto x1 = [](int i){ return i; };         // OK: return type is int
auto x2 = [](){ return { 1, 2 }; };           // error: 无法推导出返回值类型, 需要显式给出具体的返回值类型

lambda表达式在没有参数列表时，参数列表是可以省略的

[]不捕获任何变量。
[&]捕获外部作用域中所有变量，并作为引用在函数体中使用（按引用捕获）。
[=]捕获外部作用域中所有变量，并作为副本在函数体中使用（按值捕获）。
[=，&foo]按值捕获外部作用域中所有变量，并按引用捕获foo变量。
[bar]按值捕获bar变量，同时不捕获其他变量。
[this]捕获当前类中的this指针，让lambda表达式拥有和当前类成员函数同样的访问权限。如果已经使用了&或者=，就默认添加此选项。
捕获this的目的是可以在lamda中使用当前类的成员函数和成员变量。
按值捕获得到的外部变量值是在lambda表达式定义时的值。此时所有外部变量均被复制了一份存储在lambda表达式变量中。
此时虽然修改lambda表达式中的这些外部变量并不会真正影响到外部.如果希望去修改按值捕获的外部变量需要显式指明lambda表达式为mutable：
int a = 0;
auto f1 = [=]{ return a++; };            // error， 修改按值捕获的外部变量
auto f2 = [=]() mutable { return a++; }; // OK， mutable
需要注意的一点是，被mutable修饰的lambda表达式就算没有参数也要写明参数列表。

可以认为lambda是一个带有operator（）的类，即仿函数。可以使用std::和std::bind来存储和操作lambda表达式：
std::function<int(int)>  f1 = [](int a){ return a; };
std::function<int(void)> f2 = std::bind([](int a){ return a; },123);

对于没有捕获任何变量的lambda表达式，还可以被转换成一个普通的函数指针：
using func_t = int(*)(int);
func_t f = [](int a){ return a; };
f(123);
lambda表达式可以说是就地定义仿函数闭包的“语法糖”。 它的捕获列表捕获住的任何外部变量，最终均会变为闭包类型的成员变量。
而一个用了成员变量的类的operator（），如果能直接被转换为普通的函数指针，那么lambda表达式本身的this指针就丢失掉了。
而没有捕获任何外部变量的lambda表达式则不存在这个问题。
这里也可以很自然地解释为何按值捕获无法修改捕获的外部变量。因为按照C++标准，lambda表达式的operator（）默认是const的。
一个const成员函数是无法修改成员变量的值的。而mutable的作用，就在于取消operator（）的const。


********************** tuple 元组******************************


使用c++11 改进程序性能

**********************  右值引用 ******************************



// C++11增加了无序容器unordered_map/unordered_multimap和unordered_set/unordered_multiset
// 由于这些容器中的元素是不排序的，因此，比有序容器map/multimap和set/multiset效率更高。
// map和set内部是红黑树，在插入元素时会自动排序，而无序容器内部是散列表（Hash Table），通过哈希（Hash），而不是排序来快速操作元素，使得效率更高。
// 由于无序容器内部是散列表，因此无序容器的key需要提供hash_value函数，其他用法和map/set的用法是一样的。不过对于自定义的key，需要提供Hash函数和比较函数。



使用c++11 消除重复， 提高代码质量



使用c++11 解决内存泄漏的问题

智能指针是存储指向动态分配（堆）对象指针的类，用于生存期控制，能够确保在离开指针所在作用域时，自动正确地销毁动态分配的对象，防止内存泄露。
它的一种通用实现技术是使用引用计数。每使用它一次，内部的引用计数加1，每析构一次，内部引用计数减1，减为0时，删除所指向的堆内存。
C++11提供了3种智能指针：std：：shared_ptr、std：：unique_ptr和std：：weak_ptr，使用时需要引用头文件<memory>

*********************** shared_ptr ******************************

#include <iostream>
#include <memory>

using namespace std;

void DeleteIntPtr(int *p) {
    delete p;
}

int main() {
    /**
     * 初始化
     */
    shared_ptr<int> p(new int(1));
    // shared_ptr<int> p = new int(1); error 不允许直接赋值

    shared_ptr<int> p1 = p;

    shared_ptr<int> p2;// 对于一个未初始化的智能指针，可以通过reset方法来初始化，当智能指针中有值的时候，调用reset会使引用计数减1
    p2.reset(new int(1));
    if (p2)
        cout << "p2 is not null" << endl;

    shared_ptr<int> p3 = make_shared<int>(1);

    /**
     * 获取原始指针
     */

    int *op = p3.get();

    /**
     * 指定删除器
     */

    shared_ptr<int> p4(new int, DeleteIntPtr);
    shared_ptr<int> p5(new int, [](int *p) {
        delete p;
    });

    // shared_ptr的默认删除器不支持数组对象
    shared_ptr<int> p6(new int[10], [](int *p) {
        delete[] p;
    });
    // 可以将std：：default_delete作为删除器。default_delete的内部是通过调用delete来实现功能的
    std::shared_ptr<int> p7(new int[10], std::default_delete<int[]>());

    /**
     * 常见问题
     */
    // 不要用一个原始指针初始化多个shared_ptr

    // 不要在函数实参中创建shared_ptr。对于下面的用写法：
    // function (shared_ptr<int>(new int), g( ) ); // 有缺陷
    // 因为C++的函数参数的计算顺序在不同的编译器不同的调用约定下可能是不一样的
    // 所以，可能的过程是先new int，然后调g（），如果恰好g（）发生异常，而shared_ptr<int>还没有创建，则int内存泄露了
    // 正确的写法应该是先创建智能指针


    // 通过shared_from_this（）返回this指针。
    // 不要将this指针作为shared_ptr返回出来，因为this指针本质上是一个裸指针，因此这样可能会导致重复析构
    struct A {
        shared_ptr<A> GetSelf() {
            return shared_ptr<A>(this);// don't do this!
        }
    };
    shared_ptr<A> sp1(new A);
    shared_ptr<A> sp2 = sp1->GetSelf();
    // 在这个例子中，由于用同一个指针（this）构造了两个智能指针sp1和sp2，而它们之间是没有任何关系的
    // 在离开作用域之后this将会被构造的两个智能指针各自析构，导致重复析构的错误。

    // 要避免循环引用。智能指针最大的一个陷阱是循环引用，循环引用会导致内存泄露。下例是一个典型的循环引用的场景。
    // struct A;
    // struct B;
    // struct A {
    //     std::shared_ptr<B> bptr;
    //     ~A() { cout << "A is deleted!" << endl; }
    // };
    // struct B {
    //     std::shared_ptr<A> aptr;
    //     ~B() { cout << "B is deleted!" << endl; }
    // };
    // void TestPtr() {
    //     {
    //         std::shared_ptr<A> ap(new A);
    //         std::shared_ptr<B> bp(new B);
    //         ap->bptr = bp;
    //         bp->aptr = ap;
    //     }// Objects should be destroyed.
    // }
    // 测试结果是两个指针A和B都不会被删除，存在内存泄露。
    // 循环引用导致ap和bp的引用计数为2，在离开作用域之后，ap和bp的引用计数减为1，并不会减为0，导致两个指针都不会被析构，产生了内存泄露。
    // 解决办法是把A和B任何一个成员变量改为weak_ptr

    return 0;
}

*********************** unique_ptr ******************************

#include <iostream>
#include <memory>

using namespace std;

int main() {
    // unique_ptr是一个独占型的智能指针，它不允许其他的智能指针共享其内部的指针，不允许通过赋值将一个unique_ptr赋值给另外一个unique_ptr
    // unique_ptr不允许复制，但可以通过函数返回给其他的unique_ptr，还可以通过std：：move来转移到其他的unique_ptr，这样它本身就不再拥有原来指针的所有权了
    // unique_ptr不像shared_ptr可以通过make_shared方法来创建智能指针，C++11目前还没有提供make_unique方法，在C++14中会提供和make_shared类似的make_unique来创建unique_ptr。

    // unique_ptr<T> myPtr(new T);                  // Okay
    // unique_ptr<T> myOtherPtr = std::move(myPtr); // Okay,
    // unique_ptr<T> ptr = myPtr;                   // 错误，只能移动，不可复制

    // unique_ptr和shared_ptr相比，unique_ptr除了独占性这个特点之外，还可以指向一个数组，代码如下：
    std::unique_ptr<int []> ptr(new int[10]);
    ptr[9] = 9;                                                     // 设置最后一个元素值为9
    // 而std：：shared_ptr<int[]>ptr（new int[10]）；是不合法的。

    // unique_ptr指定删除器和std：：shared_ptr是有差别的，比如下面的写法：
    // std::shared_ptr<int> ptr(new int(1), [](int*p){delete p;});  // 正确
    // std::unique_ptr<int> ptr(new int(1), [](int*p){delete p;});       // 错误
    // std：：unique_ptr指定删除器的时候需要确定删除器的类型，所以不能像shared_ptr那样直接指定删除器，可以这样写：
    // std::unique_ptr<int, void(*)(int*)> ptr(new int(1), [](int*p){delete p;});
    // 上面这种写法在lambda没有捕获变量的情况下是正确的，如果捕获了变量，则会编译报错：
    // std::unique_ptr<int, void(*)(int*)> ptr(new int(1), [&](int*p){delete p;}); // 错误，捕获了变量
    // 这是因为lambda在没有捕获变量的情况下是可以直接转换为函数指针的，一旦捕获了就无法转换了。
    // 如果希望unique_ptr的删除器支持lambda，可以这样写：
    // std::unique_ptr<int, std::function<void(int*)>> ptr(new int(1),[&](int*p){delete p;});
    // 关于shared_ptr和unique_ptr的使用场景要根据实际应用需求来选
    // 如果希望只有一个智能指针管理资源或者管理数组就用unique_ptr，如果希望多个智能指针管理同一个资源就用shared_ptr。

        return 0;
}

*********************** weak_ptr ******************************

#include <iostream>
#include <memory>

using namespace std;

int main() {
    // 弱引用指针weak_ptr是用来监视shared_ptr的，不会使引用计数加1，它不管理shared_ptr内部的指针，主要是为了监视shared_ptr的生命周期，更像是shared_ptr的一个助手。
    // weak_ptr没有重载操作符*和->，因为它不共享指针，不能操作资源，主要是为了通过shared_ptr获得资源的监测权，它的构造不会增加引用计数，它的析构也不会减少引用计数，纯粹只是作为一个旁观者来监视shared_ptr中管理的资源是否存在。
    // weak_ptr还可以用来返回this指针和解决循环引用的问题。

    shared_ptr<int> sp(new int(10));
    weak_ptr<int> wp(sp);

    //通过use_count（）方法来获得当前观测资源的引用计数，代码如下：
    cout << wp.use_count() << endl;// 结果将输出1

    // 通过expired（）方法来判断所观测的资源是否已经被释放，代码如下：
    if (wp.expired())
        std::cout << "weak_ptr无效，所监视的智能指针已被释放\n";
    else
        std::cout << "weak_ptr有效\n";
    // 结果将输出:weak_ptr有效

    // 通过lock方法来获取所监视的shared_ptr

    // 不能直接将this指针返回为shared_ptr，需要通过派生std：：enable_shared_from_this类，并通过其方法shared_from_this来返回智能指针，
    // 原因是std：：enable_shared_from_this类中有一个weak_ptr，这个weak_ptr用来观测this智能指针，调用shared_from_this（）方法时，会调用内部这个weak_ptr的lock（）方法，将所观测的shared_ptr返回
    // struct A : public std::enable_shared_from_this<A> {
    // std::shared_ptr<A> GetSelf() {
    //     return shared_from_this();
    // }
    // ~A() {
    //     cout << "A is deleted" << endl;
    // }
    // };
    // std::shared_ptr<A> spy(newA);
    // std::shared_ptr<A> p = spy->GetSelf();// OK
    // 在外面创建A对象的智能指针和通过该对象返回this的智能指针都是安全的，因为shared_from_this（）是内部的weak_ptr调用lock（）方法之后返回的智能指针，在离开作用域之后，spy的引用计数减为0，A对象会被析构，不会出现A对象被析构两次的问题。
    // 需要注意的是，获取自身智能指针的函数仅在shared_ptr<T>的构造函数被调用之后才能使用，因为enable_shared_from_this内部的weak_ptr只有通过shared_ptr才能构造。
    //
    // weak_ptr解决循环引用问题
    struct A;
    struct B;
    struct A {
        std::shared_ptr<B> bptr;
        ~A() { cout << "A is deleted!" << endl; }
    };
    struct B {
        std::weak_ptr<A> aptr;// 改为weak_ptr
        ~B() { cout << "B is deleted!" << endl; }
    };
    void TestPtr() {
        {
            std::shared_ptr<A> ap(new A);
            std::shared_ptr<B> bp(new B);
            ap->bptr = bp;
            bp->aptr = ap;
        }// Objects should be destroyed.
    }
    // 执行bp->aptr = ap；时，由于aptr是weak_ptr，它并不会增加引用计数，所以ap的引用计数仍然会是1，在离开作用域之后，ap的引用计数会减为0，A指针会被析构，析构后其内部的bptr的引用计数会减为1，然后在离开作用域后bp引用计数又从1减为0，B对象也将被析构，不会发生内存泄露。

    return 0;
}

*********************** 通过智能指针管理第三库分配的内存 ******************************

void *p = GetHandle()->create();
shared_ptr<void> sp(p, [this](void *p){
    GetHandle()->release();
});




使用c++11 让多线程开发变得更简单

*********************** 线程 ******************************

// 通过detach，线程就和线程对象分离了，让线程作为后台线程去执行，当前线程也不会阻塞了。但需要注意的是，detach之后就无法再和线程发生联系了，比如detach之后就不能再通过join来等待线程执行完，线程何时执行完我们也无法控制了。
// thread t(func);
// t.detach();

// std：：thread出了作用域之后将会析构，这时如果线程函数还没有执行完则会发生错误，因此，需要保证线程函数的生命周期在线程变量std：：thread的生命周期之内,使用join或者detach

// 线程不能复制，但可以移动

// 1.获取当前信息 线程可以获取当前线程的ID，还可以获取CPU核心数量，例如：
std::thread t(func);
cout << t.get_id() << endl;// 获取当前线程ID
cout << this_thread::get_id() << endl;
// 获取CPU核数，如果获取失败则返回0
cout << std::thread::hardware_concurrency() << endl;
t.join();

// 2. 线程休眠 std::this_thread::sleep_for(std::chrono::seconds(3));


*********************** 互斥量 ******************************

互斥量是一种同步原语，是一种线程同步的手段，用来保护多线程同时访问的共享数据。
C++11中提供了如下4种语义的互斥量（mutex）：
std：：mutex：独占的互斥量，不能递归使用。
std：：timed_mutex：带超时的独占互斥量，不能递归使用。
std：：recursive_mutex：递归互斥量，不带超时功能。
std：：recursive_timed_mutex：带超时的递归互斥量。

std::mutex
这些互斥量的基本接口很相似，一般用法是通过lock（）方法来阻塞线程，直到获得互斥量的所有权为止。
在线程获得互斥量并完成任务之后，就必须使用unlock（）来解除对互斥量的占用，lock（）和unlock（）必须成对出现。
try_lock（）尝试锁定互斥量，如果成功则返回true，如果失败则返回false，它是非阻塞的。

使用lock_guard可以简化lock/unlock的写法，同时也更安全
因为lock_guard在构造时会自动锁定互斥量，而在退出作用域后进行析构时就会自动解锁，从而保证了互斥量的正确操作，避免忘记unlock操作
因此，应尽量用lock_guard。lock_guard用到了RAII技术，这种技术在类的构造函数中分配资源，在析构函数中释放资源，保证资源在出了作用域之后就释放。

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex g_lock;

// void func() {
//     g_lock.lock();
//     std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
//     g_lock.unlock();
// }

void func() {
    std::lock_guard<std::mutex> locker(g_lock);// 出作用域之后自动解锁
    std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::thread t1(func);
    std::thread t2(func);
    std::thread t3(func);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

std::recursive_mutex
递归锁允许同一线程多次获得该互斥锁，可以用来解决同一线程需要多次获取互斥量时死锁的问题。
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

struct Complex {
    std::mutex mutex;
    int i;
    Complex() : i(0) {}
    void mul(int x) {
        std::lock_guard<std::mutex> lock(mutex);
        i *= x;
    }
    void div(int x) {
        std::lock_guard<std::mutex> lock(mutex);
        i /= x;
    }
    void both(int x, int y) {
        std::lock_guard<std::mutex> lock(mutex);
        mul(x);
        div(y);
    }
};

int main() {
    Complex complex;
    complex.both(32, 23);
    return 0;
}

要解决这个死锁的问题，一个简单的办法就是用递归锁：std：：recursive_mutex，它允许同一线程多次获得互斥量
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

struct Complex {
    std::recursive_mutex mutex;
    int i;
    Complex() : i(0) {}
    void mul(int x) {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        i *= x;
    }
    void div(int x) {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        i /= x;
    }
    void both(int x, int y) {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        mul(x);
        div(y);
    }
};

int main() {
    Complex complex;
    complex.both(32, 23);
    return 0;
}

需要注意的是尽量不要使用递归锁好，主要原因如下：
1）需要用到递归锁定的多线程互斥处理往往本身就是可以简化的，允许递归互斥很容易放纵复杂逻辑的产生，从而导致一些多线程同步引起的晦涩问题。
2）递归锁比起非递归锁，效率会低一些。
3）递归锁虽然允许同一个线程多次获得同一个互斥量，可重复获得的最大次数并未具体说明，一旦超过一定次数，再对lock进行调用就会抛出std：：system错误。



std::timed_mutex
std：：timed_mutex是超时的独占锁，std：：recursive_timed_mutex是超时的递归锁，主要用在获取锁时增加超时等待功能，因为有时不知道获取锁需要多久，为了不至于一直在等待获取互斥量，就设置一个等待超时时间，在超时后还可以做其他的事情。
std：：timed_mutex比std：：mutex多了两个超时获取锁的接口：try_lock_for和try_lock_until，这两个接口是用来设置获取互斥量的超时时间，使用时可以用一个while循环去不断地获取互斥量。
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::timed_mutex mutex;

void work() {
    std::chrono::milliseconds timeout(100);
    while (true) {
        if (mutex.try_lock_for(timeout)) {
            std::cout << std::this_thread::get_id() << ": do work with the mutex"
                      << std::endl;
            std::chrono::milliseconds sleepDuration(250);
            std::this_thread::sleep_for(sleepDuration);
            mutex.unlock();
            std::this_thread::sleep_for(sleepDuration);
        } else {
            std::cout << std::this_thread::get_id() << ": do work without mutex"
                      << std::endl;
            std::chrono::milliseconds sleepDuration(100);
            std::this_thread::sleep_for(sleepDuration);
        }
    }
}

int main() {
    std::thread t1(work);
    std::thread t2(work);
    t1.join();
    t2.join();
    return 0;
}

在上面的例子中，通过一个while循环不断地去获取超时锁，如果超时还没有获取到锁时就休眠100毫秒，再继续获取超时锁。
相比std：：timed_mutex，std：：recursive_timed_mutex多了递归锁的功能，允许同一线程多次获得互斥量。std：：recursive_timed_mutex和std：：recursive_mutex的用法类似，可以看作在std：：recursive_mutex的基础上加了超时功能。

*********************** 条件变量 ******************************

条件变量是C++11提供的另外一种用于等待的同步机制，它能阻塞一个或多个线程，直到收到另外一个线程发出的通知或者超时，才会唤醒当前阻塞的线程。条件变量需要和互斥量配合起来用。

C++11提供了两种条件变量：
·condition_variable，配合std：：unique_lock进行wait操作。
·condition_variable_any，和任意带有lock、unlock语义的mutex搭配使用，比较灵活，但效率比condition_variable差一些。
可以看到condition_variable_any比condition_variable更灵活，因为
它更通用，对所有的锁都适用，而condition_variable性能更好。我们应该根据具体应用场景来选择条件变量。

条件变量的使用过程如下：
1）拥有条件变量的线程获取互斥量。
2）循环检查某个条件，如果条件不满足，则阻塞直到条件满足；如果条件满足，则向下执行。
3）某个线程满足条件执行完之后调用notify_one或notify_all唤醒一个或者所有的等待线程。
可以用条件变量来实现一个同步队列，同步队列作为一个线程安全的数据共享区，经常用于线程之间数据读取，比如半同步半异步线程池的同步队列。

#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

using namespace std;

template<typename T>
class SyncQueue {
    bool IsFull() const {
        return m_queue.size() == m_maxSize;
    }
    bool IsEmpty() const {
        return m_queue.empty();
    }

public:
    SyncQueue(int maxSize) : m_maxSize(maxSize) {
    }

    void Show() {
        for (auto i : m_queue)
            std::cout << i << " ";
        std::cout << std::endl;
    }

    void Put(const T &x) {
        std::lock_guard<std::mutex> locker(m_mutex);
        while (IsFull()) {
            cout << "缓冲区满了，需要等待..." << endl;
            m_notFull.wait(m_mutex);
        }
        m_queue.push_back(x);
        m_notEmpty.notify_one();
    }

    void Take(T &x) {
        std::lock_guard<std::mutex> locker(m_mutex);
        while (IsEmpty()) {
            cout << "缓冲区空了，需要等待..." << endl;
            m_notEmpty.wait(m_mutex);
        }
        x = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }

    bool Empty() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }

    bool Full() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size() == m_maxSize;
    }

    size_t Size() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size();
    }
    int Count() {
        return m_queue.size();
    }

private:
    std::list<T> m_queue;                  // 缓冲区
    std::mutex m_mutex;                    // 互斥量和条件变量结合起来使用
    std::condition_variable_any m_notEmpty;// 不为空的条件变量
    std::condition_variable_any m_notFull; // 没有满的条件变量
    int m_maxSize;                         // 同步队列最大的size
};

int main() {
    SyncQueue<int> sq{10};
    int num = 1;
    thread t([&] {
        while (true) {
            this_thread::sleep_for(chrono::seconds(1));
            std::cout << "m_queuq is: ";
            sq.Show();
        }
    });

    thread t1([&] {
        while (true) {
            this_thread::sleep_for(chrono::seconds(3));
            sq.Put(num++);
        }
    });

    thread t2([&] {
        while (true) {
            this_thread::sleep_for(chrono::seconds(10));
            int res;
            sq.Take(res);
            std::cout << "take from m_queue is: " << res << std::endl;
        }
    });

    t.join();
    t1.join();
    t2.join();

    return 0;
}
这个同步队列在没有满的情况下可以插入数据，如果满了，则会调用m_notFull阻塞等待，待消费线程取出数据之后发一个未满的通知，然后前面阻塞的线程就会被唤醒继续往下执行；如果队列为空，就不能取数据，会调用m_notempty条件变量阻塞，等待插入数据的线程发出不为空的通知时，才能继续往下执行。以上过程是同步队列的工作过程。
代码清单5-5用到了std：：lock_guard，它利用了RAII机制可以保证安全释放mutex。从代码清单5-5中还可以看到，std：：unique_lock
和std：：lock_guard的差别在于前者可以自由地释放mutex，而后者则需要等到std：：lock_guard变量生命周期结束时才能释放。条件变量的wait还有一个重载方法，可以接受一个条件。比如下面的代码：
std::lock_guard<std::mutex> locker(m_mutex);
while(IsFull())
{
        m_notFull.wait(m_mutex);
}
可以改为这样：
std::lock_guard<std::mutex> locker(m_mutex);
m_notFull.wait(locker, [this]{return !IsFull();});
两种写法效果是一样的，但是后者更简洁，条件变量会先检查判断式是否满足条件，如果满足条件，则重新获取mutex，然后结束wait，继续往下
这里需要注意的是，wait函数中会释放mutex，而lock_guard这时还拥有mutex，它只会在出了作用域之后才会释放mutex，所以，这时它并不会释放，但执行wait时会提前释放mutex。从语义上看这里使用lock_guard会产生矛盾，但是实际上并不会出问题，因为wait提前释放锁之后会处于等待状态，在被notify_one或者notify_all唤醒之后会先获取mutex，这相当于lock_guard的mutex在释放之后又获取到了，因此，在出了作用域之后lock_guard自动释放mutex不会有问题。这里应该用unique_lock，因
为unique_lock不像lock_guard一样只能在析构时才释放锁，它可以随时释放锁，因此，在wait时让unique_lock释放锁从语义上看更加准确。
std：：lock_guard改成std：：unique_lock，把std：：condition_variable_any改为std：：condition_variable，并且用等待一个判断式的方法来实现一个简单的线程池，

include<thread>
#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
        using namespace std;
template<typename T>
class SimpleSyncQueue {
public:
    SimpleSyncQueue() {
    }
    void Put(const T &x) {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_queue.push_back(x);
        m_notEmpty.notify_one();
    }
    void Take(T &x) {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this] { return !m_queue.empty(); });
        x = m_queue.front();
        m_queue.pop_front();
    }

    bool Empty() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }

    size_t Size() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size();
    }

private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_notEmpty;
};

*********************** 原子变量 ******************************
C++11提供了一个原子类型std：：atomic<T>，可以使用任意类型作为模板参数，C++11内置了整型的原子变量，可以更方便地使用原子变量，使用原子变量就不需要使用互斥量来保护该变量了，用起来更简洁。


*********************** call_once once_flag ******************************

#include <iostream>
#include <thread>

using namespace std;

once_flag flg;

void func() {
    call_once(flg, [] {
        cout << "call once" << endl;
    });
}

int main() {
    thread t1(func);
    thread t2(func);
    thread t3(func);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

*********************** 异步操作******************************
C++11提供了异步操作相关的类，主要有std：：future、std：：promise和std：：package_task。std：：future作为异步结果的传输通道，可以很方便地获取线程函数的返回值；std：：promise用来包装一个值，将数据和future绑定起来，方便线程赋值；std：：package_task用来包装一个可调用对象，将函数和future绑定起来，以便异步调用。

获取线程函数返回值的类std：：future
C++11中增加的线程，使得我们可以非常方便地创建和使用线程，但有时会有些不便，比如希望获取线程函数的返回结果，就不能直接通过thread
join（）得到结果，这时就必须定义一个变量，在线程函数中去给这个变量赋值，然后执行join（），最后得到结果，这个过程是比较烦琐的。thread库提供了future用来访问异步操作的结果，因为一个异步操作的结果不能马上获取，只能在未来某个时候从某个地方获取，这个异步操作的结果是一个未来的期待值，所以被称为future，future提供了获取异步操作结果的通道。我们可以以同步等待的方式来获取结果，可以通过查询future的状态（future_status）来获取异步操作的结果。future_status有如下3种状态：
·Deferred，异步操作还没开始
·Ready，异步操作已经完成。
·Timeout，异步操作超时。
我们可以查询future的状态，通过它内部的状态可以知道异步任务的执行情况，比如下面的代码将不断查询future的状态，直到任务完成为止。
获取future结果有3种方式：get、wait、wait_for，其中get等待异步操作结束并返回结果，wait只是等待异步操作完成，没有返回值，wait_for是超时等待返回结果。

协助线程赋值的类std：：promise
std：：promise将数据和future绑定起来，为获取线程函数中的某个值提供便利，在线程函数中为外面传进来的promise赋值，在线程函数执行完成之后就可以通过promis的future获取该值了。值得注意的是，取值是间接地通过promise内部提供的future来获取的。std：：promise的基本用法如下：
　可调用对象的包装类std：：package_task
std：：packaged_task包装了一个可调用对象的包装类（如function、lambda expression、bind expression和another function object），将函数和future绑定起来，以便异步调用，它和std：：promise在某种程度上有点像，promise保存了一个共享状态的值，而packaged_task保存的是一个函数。

std：：promise、std：：packaged_task和std：：future三者之间的关系
std：：future提供了一个访问异步操作结果的机制，它和线程是一个级别的，属于低层次的对象。在std：：future之上的高一层是std：：packaged_task和std：：promise，它们内部都有future以便访问异步操作结果，std：：packaged_task包装的是一个异步操作，而std：：promise包装的是一个值，都是为了方便异步操作，因为有时需要获取线程中的某个值，这时就用std：：promise，而有时需要获一个异步操作的返回值，这时就用std：：packaged_task。那么std：：promise和std：
：packaged_task之间又是什么关系呢？可以将一个异步操作的结果保存到std：：promise中。
future被promise和package_task用来作为异步操作或者异步结果的连接通道，用std：：future和std：：shared_future来获取异步调用的结果。future是不可拷贝的，只能移动，shared_future是可以拷贝的，当需要将future放到容器中则需要用shared_future。

std：：async比std：：promise、std：：packaged_task和std：：thread更高一层，它可以用来直接创建异步的task，异步任务返回的结果也保存在future中，当需要获取异步任务的结果时，只需要调用future.get（）方法即可，如果不关注异步任务的结果，只是简单地等待任务完成的话，则调用future.wait（）方法。



使用C++11中便利的工具

*********************** 处理日期和时间的chrono库 ******************************
chrono库主要包含3种类型：时间间隔duration、时钟clocks和时间点time point。

*********************** 数值类型和字符串的相互转换 ******************************

C++11提供了to_string方法，可以方便地将各种数值类型转换为字符串类型

C++11还提供了字符串转换为整型和浮点型的方法：
·atoi：将字符串转换为int类型。
·atol：将字符串转换为long类型。
·atoll：将字符串转换为long long类型。
·atof：将字符串转换为浮点型。
如果需要转换的字符串前面部分不是数字，会返回0；如果字符串的前面部分有空格和数字，转换时会忽略空格并获得前面部分的数字。

*********************** 宽窄字符转换 ******************************



c++11的其他特性
delete function
*********************** 类内初始值/就地初始化 ******************************

在 C++11 之前，只能对结构体或类的静态常量成员进行就地初始化，其他的不行。
class C
{
private:
static const int a=10; // yes
int a=10;           // no
}
在 C++11 中，结构体或类的数据成员在申明时可以直接赋予一个默认值，初始化的方式有两种，一是使用等号 =，二是使用大括号列表初始化的方式
class C
{
private:
int a=7;   // C++11 only
int b{7};  // or int b={7}; C++11 only
int c(7);  // error
};
注意，小括号初始化方式不能用于就地初始化。

就地初始化与初始化列表的先后顺序
C++11 支持了就地初始化非静态数据成员的同时，初始化列表的方式也被保留下来，也就是说既可以使用就地初始化，也可以使用初始化列表来完成数据成员的初始化工作。当二者同时使用时并不冲突，初始化列表发生在就地初始化之后，即最终的初始化结果以初始化列表为准
class Mem
{
public:
Mem(int i,int j):m1(i),m2(j) {}

    int m1 = 1;
    int m2 = {2};
};

Mem mem(11,22);
cout<<"m1="<< mem.m1<<" m2="<<mem.m2<<endl;
程序输出结果： m1=11 m2=22

*********************** 委托构造函数 和 using声明函数 ******************************

委托构造函数允许在同一个类中一个构造函数可以调用另外一个构造函数，从而可以在初始化时简化变量的初始化
使用委托构造函数时需要注意：使用了代理构造函数就不能用类成员初始化了

派生类隐藏基类同名成员：名字查找优于类型检查
using声明
#include <iostream>
#include <string>

using namespace std;

struct Base {
    int x;
    int y;
    Base() {}
    Base(int x_, int y_) : x(x_), y(y_) {}
    void Fun() {
        cout << "call in Base" << endl;
    }
};
struct Derived : Base {
    using Base::Base;
    using Base::Fun;
    Derived() {}
    void Fun(int a) {
        cout << "call in Derived" << endl;
    }
};
int main() {
    Derived d;
    d.Fun();// 编译报错，找不到合适的函数

    Derived d1(1, 2);
    return 0;
}
*********************** 原始字符串 ******************************

原始字符串字面量的定义是R“xxx（raw string）xxx”，其中原始字符串必须用括号（）括起来，括号的前后可以加其他字符串，所加的字符串是会被忽略的，而且加的字符串必须在括号两边同时出现。

*********************** final override ******************************
C++11中增加了final关键字来限制某个类不能被继承，或者某个虚函数不能被重写.如果修饰函数，final只能修饰虚函数，并且要放到类或者函数的后面
override关键字确保在派生类中声明的重写函数与基类的虚函数有相同的签名，同时也明确表明将会重写基类的虚函数，还可以防止因疏忽把本来想重写基类的虚函数声明成重载。这样，既可以保证重写虚函数的正确性，又可以提高代码的可读性。

*********************** 内存对齐 ******************************

*********************** C++11新增的便利算法 ******************************
·all_of检查区间[first，last）中是否所有的元素都满足一元判断式p，所有的元素都满足条件返回true，否则返回false。
·any_of检查区间[first，last）中是否至少有一个元素都满足一元判断式p，只要有一个元素满足条件就返回true，否则返回false。
·none_of检查区间[first，last）中是否所有的元素都不满足一元判断式p，所有的元素都不满足条件返回true，否则返回false
.算法库的查找算法新增了一个find_if_not，它的含义和find_if是相反的，即查找不符合某个条件的元素，find_if也可以实现find_if_not的功能，只需要将判断式改为否定的判断式即可，现在新增了find_if_not之后，就不需要再写否定的判断式了，可读性也变得更好
.copy_if算法
.算法库新增了iota算法，用来方便地生成有序序列。比如，需要一个定长数组，这个数组中的元素都是在某一个数值的基础之上递增的，用iota就可以很方便地生成这个数组了。
.算法库还新增了一个同时获取最大值和最小值的算法minmax_element，这样在想获取最大值和最小值的时候就不用分别调用max_element和max_element算法了，用起来会更方便，minmax_element会将最小值和最大值的迭代器放到一个pair中返回
.算法库新增了is_sorted和is_sorted_until算法，其中is_sort用来判断某个序列是否是排好序的，is_sort_until则用来返回序列中前面已经排好序的部分序列。
多线程

说说C++多线程主要用在什么场景下？

线程必然不是越多越好，线程切换也是要开销的，当你增加一个线程的时候，增加的额外开销要小于该线程能够消除的阻塞时间，这才叫物有所值。

什么时候该使用多线程呢？这要分四种情况讨论：

1. 多核CPU——计算密集型任务。此时要尽量使用多线程，可以提高任务执行效率，例如加密解密，数据压缩解压缩（视频、音频、普通数据），否则只能使一个核心满载，而其他核心闲置
2. 单核CPU——计算密集型任务。此时的任务已经把CPU资源100%消耗了，就没必要也不可能使用多线程来提高计算效率了
3. 单核CPU——IO密集型任务，使用多线程还是为了人机交互方便；
4. 多核CPU——IO密集型任务，这就更不用说了，跟单核时候原因一样。

知道什么情况下不使用并发同样重要。从根本上来说，不使用并发的唯一原因就是并发带来的效益小于它带来的代价。

在许多情况下，使用并发会使代码难以理解，编写、维护并发代码需要更多的脑力成本，并发带来的复杂性可能会增加bug。除非并发带来性能的提升足够打，或者模块划分足够清楚，否则不要使用并发。

使用并发带来性能上的提升可能不如预期。并发编程也需要额外的开销，在创建一个线程时，系统要分配内核资源、栈空间，然后把新线程加入到任务队列。如果线程运行时间小于线程的创建时间，这时使用多线程可能会使性能变差。进一步来说，线程资源是有限的。如果同时有太多线程，会占用太多系统资源，会使整个系统变慢。使用太多线程会消耗尽内存或处理器的地址空间，因为线程需要独立的栈空间。

在C/S架构下，如果为每个连接创建一个线程，在连接比较少时性能很好，但是如果要同时处理太多连接的话会创建太多线程。这时使用线程池（thread pools）可以提高性能。在Linux下可以使用I/O多路复用：select、poll、epoll。

C++多线程有哪些锁？分别讲讲

互斥量是一种同步原语，是一种线程同步的手段，用来保护多线程同时访问的共享数据。

C++11中提供了如下4种语义的互斥量（mutex）：
std：：mutex：独占的互斥量，不能递归使用。
std：：timed_mutex：带超时的独占互斥量，不能递归使用。
std：：recursive_mutex：递归互斥量，不带超时功能。
std：：recursive_timed_mutex：带超时的递归互斥量。

std::mutex
这些互斥量的基本接口很相似，一般用法是通过lock（）方法来阻塞线程，直到获得互斥量的所有权为止。
在线程获得互斥量并完成任务之后，就必须使用unlock（）来解除对互斥量的占用，lock（）和unlock（）必须成对出现。
try_lock（）尝试锁定互斥量，如果成功则返回true，如果失败则返回false，它是非阻塞的。

使用lock_guard可以简化lock/unlock的写法，同时也更安全
因为lock_guard在构造时会自动锁定互斥量，而在退出作用域后进行析构时就会自动解锁，从而保证了互斥量的正确操作，避免忘记unlock操作
因此，应尽量用lock_guard。lock_guard用到了RAII技术，这种技术在类的构造函数中分配资源，在析构函数中释放资源，保证资源在出了作用域之后就释放。

std::recursive_mutex
递归锁允许同一线程多次获得该互斥锁，可以用来解决同一线程需要多次获取互斥量时死锁的问题。
递归锁虽然允许同一个线程多次获得同一个互斥量，可重复获得的最大次数并未具体说明，一旦超过一定次数，再对lock进行调用就会抛出std：：system错误。

需要注意的是尽量不要使用递归锁好，主要原因如下：
递归锁比起非递归锁，效率会低一些。
需要用到递归锁定的多线程互斥处理往往本身就是可以简化的，允许递归互斥很容易放纵复杂逻辑的产生，从而导致一些多线程同步引起的晦涩问题。

std::timed_mutex std：：recursive_timed_mutex

std：：timed_mutex比std：：mutex多了两个超时获取锁的接口：try_lock_for和try_lock_until，这两个接口是用来设置获取互斥量的超时时间，使用时可以用一个while循环去不断地获取互斥量。
std：：timed_mutex是超时的独占锁，std：：recursive_timed_mutex是超时的递归锁，主要用在获取锁时增加超时等待功能，因为有时不知道获取锁需要多久，为了不至于一直在等待获取互斥量，就设置一个等待超时时间，在超时后还可以做其他的事情。
相比std：：timed_mutex，std：：recursive_timed_mutex多了递归锁的功能，允许同一线程多次获得互斥量。std：：recursive_timed_mutex和std：：recursive_mutex的用法类似，可以看作在std：：recursive_mutex的基础上加了超时功能。




双指针

















用数组存储是因为 ： 堆是完全二叉树





c++ 只规定了语言层面的东西， 而对二进制级别没有任何规定
循环结构程序设计最常见的两个问题：算术运算溢出和程序效率低下

for循环

for(初始化；条件；调整）

do while循环

do{ 循环体} while( 条件判断);

基于range的for循环

for(int i: {1,2,3,4,5})
    std::cout << i << std::endl;




C++标准并没有规定编译器如何实现C++的各种特性，所以不同编译器实现方法一般不同。
在上世纪90年代，GCC使用“setjmp”和“longjmp”实现异常处理。当Intel制造Itanium处理器时，Intel想让Intel Compiler和GCC可以一定程度互操作，当然包括互抛异常。于是Intel和GCC组织了一个工作组来设计新的ABI，即Itanium ABI。随后GCC开发者将该ABI扩展到了其他的处理器和操作系统。由于该ABI设计良好，LLVM也选择使用它。微软的MSVC编译器使用自己的ABI实现。

bilibili: stld

c++ primer: 模板

strcpy strncpy
snprintf

try catch

static_cast

stoi stoll

vector: front back capacity size

std::find std::bsearch

iterator

list: max_size size push_back front back 
forward_list: size max_size push_front front

snprintf

int arr[] =  {1 , 2, 3, 5};   &arr ???

定义有分配空间的含义，因此引用 通常说是 声明引用 必须初始化

指针：合法性测试
四年一闰，百年不闰，四百年再闰

double 类型的范围 以及 精确到多少位
todo:
比较大的数组应尽量声明在main函数外，否则程序可能无法运行

结束输入

linux: Ctrl + d
windows:  ???

文件比较 windows : fc, linux:diff

inlint static inline extern inline

main函数返回值

结构体定义

初始化


uva 1339 4.2.6
4.3.4 
习题2-6
例题3-2























一 字符串字面值

C++11后，字符串就不能像之前或者C语言中一样赋值给char *，下面的代码将会报warning或报错
char *s = "abc";
warning: ISO C++ forbids converting a string constant to ‘char*’

字符串字面值应该被当作const char*类型，因为它们不可以被改变，任何尝试改变字面值的操作都会导致错误

因此解决的方法就是
const char *s = "abc";
char const *s = "abc";

或者直接cast也可以
char *s = (char *)"abc"; // 任何改变的尝试仍然会导致错误



一 malloc 和 free
stdlib.h
void * malloc(unsigned int size)
void * calloc(unsigned int n, unsigned int size)
void free(void *p)

malloc和calloc: 如果函数没有成功执行，返回值为空指针， NULL
free: p是调用malloc或者calloc的返回值

二 memset

memory.h
void * memset(void * buf, int ch, size_t count)

memset 用于内存空间初始化，如数组或者字符串；也用来清空一个结构类型的变量或数组
int arr[100];
memset(arr, 0, 100);

char str[] = "hello world";
memset(str, '\0', sizeof(str));

三 memmove memcpy

memory.h
void * memcpy(void *dst, void *src, size_t count)

memcpy：内存拷贝，src和dst所指内存区域不能重叠， 返回指向dst的指针

两者的唯一区别就是在对待重叠区域的时候，memmove可以正确的完成对应的拷贝，而memcpy不能。

内存覆盖的情形有以下两种：


先看memcpy()和memmove()这两个函数的实现：

void* my_memcpy(void* dst, const void* src, size_t n)
{
    char *tmp = (char*)dst;
    char *s_src = (char*)src;
 
    while(n--) {
        *tmp++ = *s_src++;
    }
    return dst;
}
从实现中可以看出memcpy()是从内存左侧一个字节一个字节地将src中的内容拷贝到dest的内存中，这种实现方式导致了对于图中第二种内存重叠情形下，最后两个字节的拷贝值明显不是原先的值了，新的值是变成了src的最开始的2个字节了。

而对于第一种内存覆盖情况，memcpy的这种拷贝方式是可以的。

而memmove就是针对第二种内存覆盖情形，对memcpy进行了改进，改进代码如下：

void* my_memmove(void* dst, const void* src, size_t n)
{
    char* s_dst;
    char* s_src;
    s_dst = (char*)dst;
    s_src = (char*)src;
    if(s_dst>s_src && (s_src+n>s_dst)) {  //第二种内存覆盖的情形
        s_dst = s_dst+n-1;
        s_src = s_src+n-1;
        while(n--) {
            *s_dst-- = *s_src--;
        }
    }else {
        while(n--) {
            *s_dst++ = *s_src++;
        }
    }
    return dst;
}


stringstream 位于头文件sstream string很慢 sstream 更慢

algorithm : swap lower_bound unique

struc 和class: 默认访问权限和继承方式不同

vector: size resize push_back pop_back clear empty 可以直接赋值

输入的数据中每行包含若干个（至少一个) 空格隔开的整数，输出每行所有整数之和。
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
  string line;
  while (getline(cin, line)) {
    int sum = 0, x;
    stringstream ss(line);
    while (ss >> x)
      sum += x;
    cout << sum << endl;
  }

  return 0;
}


目前为止，我们用过的所有引用都是左值引用——对左值的引用。lvalue这个词来自于C语言，指的是可以放在赋 值表达式左边的事物——在栈上或堆上分配的命名对象，或者其他对象成员——有明确的内存地址。rvalue这个 词也来源于C语言，指的是可以出现在赋值表达式右侧的对象——例如字面值常量和临时变量。因此，左值引用只能被绑定在左值上，而不是右值。

int &i = 2; // 错误
const int &i = 2; // 正确 右值绑定到const左值引用


// 对左值的const引用创建临时性对象，作为参数传递给函数
void print(const string &s);
print("hello"); // 允许隐式转换


C++11标准介绍了右值引用(rvalue reference)，这种方式只能绑定右值，不能绑定左值，其通过两个 && 来进行 声明:

int &&i = 42;
int j = 1;
int &&k = j; // 错误


移动语义

右值通常都是临时的，所以可以随意修改;如果知道函数的某个参数是一个右值，就可以将其看作为一个临时存 储或“窃取”内容，也不影响程序的正确性。这就意味着，比起拷贝右值参数的内容，不如移动其内容。动态数 组比较大的时候，这样能节省很多内存分配，提供更多的优化空间。试想，一个函数以 std::vector<int> 作为一 个参数，就需要将其拷贝进来，而不对原始的数据做任何操作。C++03/98的办法是，将这个参数作为一个左值的c onst引用传入，然后做内部拷贝:

void process_copy(std::vector<int> const& vec_) {
    std::vector<int> vec(vec_);
    vec.push_back(42);
}


这就允许函数能以左值或右值的形式进行传递，不过任何情况下都是通过拷贝来完成的。如果使用右值引用版本 的函数来重载这个函数，就能避免在传入右值的时候，函数会进行内部拷贝的过程，因为可以任意的对原始值进 行修改:

void process_copy(std::vector<int> const&& vec) {
    vec.push_back(42);
}


class X {
public:
  X() : data(new int[10000]) {}
  X(const X &other) : data(new int[10000]) {
    std::copy(other.data, other.data + 10000, data);
  }
  X(X &&other) : data(other.data) { other.data = nullptr; }

  ~X() { delete[] data; }

private:
  int *data;
};

有些类型的构造函数只支持移动构造函 数，而不支持拷贝构造函数。例如，智能指针 std::unique_ptr<> 的非空实例中，只允许这个指针指向其对象，所 以拷贝函数在这里就不能用了(如果使用拷贝函数，就会有两个 std::unique_ptr<> 指向该对象，不满足 que_ptr<> 定义)。不过，移动构造函数允许对指针的所有权，在实例之间进行传递，并且允许 std::unique_pt r<> 像一个带有返回值的函数一样使用——指针的转移是通过移动，而非拷贝。

如果你已经知道，某个变量在之后就不会在用到了，这时候可以选择显式的移动，你可以使用 static_cas t<X&&> 将对应变量转换为右值，或者通过调用 std::move() 函数来做这件事:

X x1;
X x2 = std::move(x1);
X x3 = static_cast<X&&>(x1);

移动语义在线程库中用的比较广泛，无拷贝操作对数据进行转移可以作为一种优化方式，避免对将要被销毁的变 量进行额外的拷贝。在2.2节中看到，在线程中使用 std::move() 转移 std::unique_ptr<> 得到一个新实例;在2.3 节中，了解了在 std:thread 的实例间使用移动语义，用来转移线程的所有权。
std::thread 、 std::unique_lock<> 、 std::future<> 、 std::promise<> 和 std::packaged_task<> 都不能拷 贝，不过这些类都有移动构造函数，能让相关资源在实例中进行传递，并且支持用一个函数将值进行返回。 st d::string 和 std::vector<> 也可以拷贝，不过它们也有移动构造函数和移动赋值操作符，就是为了避免拷贝拷贝 大量数据。
C++标准库不会将一个对象显式的转移到另一个对象中，除非将其销毁的时候或对其赋值的时候(拷贝和移动的操 作很相似)。不过，实践中移动能保证类中的所有状态保持不变，表现良好。一个 std::thread 实例可以作为移动 源，转移到新(以默认构造方式)的 std::thread 实例中。还有， std::string 可以通过移动原始数据进行构 造，并且保留原始数据的状态，不过不能保证的是原始数据中该状态是否正确(根据字符串长度或字符数量决 定)。


右值引用和函数模板

在使用右值引用作为函数模板的参数时，与之前的用法有些不同:如果函数模板参数以右值引用作为一个模板参 数，当对应位置提供左值的时候，模板会自动将其类型认定为左值引用;当提供右值的时候，会当做普通数据使 用。可能有些口语化，来看几个例子吧。
考虑一下下面的函数模板:

template<typename T>
void foo(T&& t)
{}

随后传入一个右值，T的类型将被推导为:

foo(42); // foo<int>(42)
foo(3.14159); // foo<double><3.14159> 
foo(std::string()); // foo<std::string>(std::string())

不过，向foo传入左值的时候，T会比推导为一个左值引用:
int i = 42;
foo(i); // foo<int&>(i)

因为函数参数声明为 T&& ，所以就是引用的引用，可以视为是原始的引用类型。那么foo<int&>()就相当于:

foo<int&>(); // void foo<int&>(int& t);

这就允许一个函数模板可以即接受左值，又可以接受右值参数;这种方式已经被 std::thread 的构造函数所使 用(2.1节和2.2节)，所以能够将可调用对象移动到内部存储，而非当参数是右值的时候进行拷贝。


















一、概述
为了实现 C++ 的多态，C++ 使用了一种动态绑定的技术。这个技术的核心是虚函数表（下文简称虚表）。本文介绍虚函数表是如何实现动态绑定的。
二、类的虚表
每个包含了虚函数的类都包含一个虚表。
我们知道，当一个类（A）继承另一个类（B）时，类 A 会继承类 B 的函数的调用权。所以如果一个基类包含了虚函数，那么其继承类也可调用这些虚函数，换句话说，一个类继承了包含虚函数的基类，那么这个类也拥有自己的虚表。
我们来看以下的代码。类 A 包含虚函数vfunc1，vfunc2，由于类 A 包含虚函数，故类 A 拥有一个虚表。
class A {
public:
    virtual void vfunc1();
    virtual void vfunc2();
    void func1();
    void func2();
private:
    int m_data1, m_data2;
};

1
2
3
4
5
6
7
8
9
类 A 的虚表如图 1 所示。

图 1：类 A 的虚表示意图
虚表是一个指针数组，其元素是虚函数的指针，每个元素对应一个虚函数的函数指针。需要指出的是，普通的函数即非虚函数，其调用并不需要经过虚表，所以虚表的元素并不包括普通函数的函数指针。
虚表内的条目，即虚函数指针的赋值发生在编译器的编译阶段，也就是说在代码的编译阶段，虚表就可以构造出来了。
三、虚表指针
虚表是属于类的，而不是属于某个具体的对象，一个类只需要一个虚表即可。同一个类的所有对象都使用同一个虚表。
为了指定对象的虚表，对象内部包含一个虚表的指针，来指向自己所使用的虚表。为了让每个包含虚表的类的对象都拥有一个虚表指针，编译器在类中添加了一个指针，*__vptr，用来指向虚表。这样，当类的对象在创建时便拥有了这个指针，且这个指针的值会自动被设置为指向类的虚表。

图 2：对象与它的虚表
上面指出，一个继承类的基类如果包含虚函数，那个这个继承类也有拥有自己的虚表，故这个继承类的对象也包含一个虚表指针，用来指向它的虚表。
四、动态绑定
说到这里，大家一定会好奇 C++ 是如何利用虚表和虚表指针来实现动态绑定的。我们先看下面的代码。
class A {
public:
    virtual void vfunc1();
    virtual void vfunc2();
    void func1();
    void func2();
private:
    int m_data1, m_data2;
};

class B : public A {
public:
    virtual void vfunc1();
    void func1();
private:
    int m_data3;
};

class C: public B {
public:
    virtual void vfunc2();
    void func2();
private:
    int m_data1, m_data4;
};

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
类 A 是基类，类 B 继承类 A，类 C 又继承类 B。类 A，类 B，类 C，其对象模型如下图 3 所示。

图 3：类 A，类 B，类 C 的对象模型
由于这三个类都有虚函数，故编译器为每个类都创建了一个虚表，即类 A 的虚表（A vtbl），类 B 的虚表（B vtbl），类 C 的虚表（C vtbl）。类 A，类 B，类 C 的对象都拥有一个虚表指针，*__vptr，用来指向自己所属类的虚表。
类 A 包括两个虚函数，故 A vtbl 包含两个指针，分别指向A::vfunc1()和A::vfunc2()。
类 B 继承于类 A，故类 B 可以调用类 A 的函数，但由于类 B 重写了B::vfunc1()函数，故 B vtbl 的两个指针分别指向B::vfunc1()和A::vfunc2()。
类 C 继承于类 B，故类 C 可以调用类 B 的函数，但由于类 C 重写了C::vfunc2()函数，故 C vtbl 的两个指针分别指向B::vfunc1()（指向继承的最近的一个类的函数）和C::vfunc2()。
虽然图 3 看起来有点复杂，但是只要抓住“对象的虚表指针用来指向自己所属类的虚表，虚表中的指针会指向其继承的最近的一个类的虚函数”这个特点，便可以快速将这几个类的对象模型在自己的脑海中描绘出来。
非虚函数的调用不用经过虚表，故不需要虚表中的指针指向这些函数。
假设我们定义一个类 B 的对象。由于 bObject是类 B 的一个对象，故bObject包含一个虚表指针，指向类 B 的虚表。
int main() 
{
    B bObject;
}

1
2
3
4
现在，我们声明一个类 A 的指针p来指向对象bObject。虽然p是基类的指针只能指向基类的部分，但是虚表指针亦属于基类部分，所以p可以访问到对象bObject的虚表指针。bObject的虚表指针指向类 B 的虚表，所以p可以访问到 B vtbl。如图 3 所示。
int main() 
{
    B bObject;
    A *p = & bObject;
}

1
2
3
4
5
当我们使用p来调用vfunc1()函数时，会发生什么现象？
int main() 
{
    B bObject;
    A *p = & bObject;
    p->vfunc1();
}

1
2
3
4
5
6
程序在执行p->vfunc1()时，会发现p是个指针，且调用的函数是虚函数，接下来便会进行以下的步骤。
首先，根据虚表指针p->__vptr来访问对象bObject对应的虚表。虽然指针p是基类A*类型，但是*__vptr也是基类的一部分，所以可以通过p->__vptr可以访问到对象对应的虚表。
然后，在虚表中查找所调用的函数对应的条目。由于虚表在编译阶段就可以构造出来了，所以可以根据所调用的函数定位到虚表中的对应条目。对于 p->vfunc1()的调用，B vtbl 的第一项即是vfunc1对应的条目。
最后，根据虚表中找到的函数指针，调用函数。从图 3 可以看到，B vtbl 的第一项指向B::vfunc1()，所以 p->vfunc1()实质会调用B::vfunc1() 函数。
如果p指向类 A 的对象，情况又是怎么样？
int main() 
{
    A aObject;
    A *p = &aObject;
    p->vfunc1();
}

1
2
3
4
5
6
当aObject在创建时，它的虚表指针__vptr已设置为指向 A vtbl，这样p->__vptr就指向 A vtbl。vfunc1在 A vtbl 对应在条目指向了A::vfunc1()函数，所以 p->vfunc1()实质会调用A::vfunc1()函数。
可以把以上三个调用函数的步骤用以下表达式来表示：
(*(p->__vptr)[n])(p)

1
可以看到，通过使用这些虚函数表，即使使用的是基类的指针来调用函数，也可以达到正确调用运行中实际对象的虚函数。
我们把经过虚表调用虚函数的过程称为动态绑定，其表现出来的现象称为运行时多态。动态绑定区别于传统的函数调用，传统的函数调用我们称之为静态绑定，即函数的调用在编译阶段就可以确定下来了。
那么，什么时候会执行函数的动态绑定？这需要符合以下三个条件。
通过指针来调用函数
指针 upcast 向上转型（继承类向基类的转换称为 upcast，关于什么是 upcast，可以参考本文的参考资料）
调用的是虚函数
如果一个函数调用符合以上三个条件，编译器就会把该函数调用编译成动态绑定，其函数的调用过程走的是上述通过虚表的机制。
五、总结
封装，继承，多态是面向对象设计的三个特征，而多态可以说是面向对象设计的关键。C++ 通过虚函数表，实现了虚函数与对象的动态绑定，从而构建了 C++ 面向对象程序设计的基石。
参考资料
《C++ Primer》第三版，中文版，潘爱民等译
http://www.learncpp.com/cpp-tutorial/125-the-virtual-table/
侯捷《C++最佳编程实践》视频，极客班，2015
Upcasting and Downcasting, http://www.bogotobogo.com/cplusplus/upcasting_downcasting.php
附：源代码
https://github.com/haozlee/vtable/blob/master/main.cpp


递归

c语言支持递归，即函数可以直接或间接的调用自己。

由于使用了调用栈， c语言自然支持了递归。在c语言的函数中，调用自己和其它函数没有本质的区别，都是建立新栈帧，传递参数并修改当前代码行。在函数体执行完毕后删除栈帧，处理返回值并修改当前代码行。




- 对链表进行排序 归并
- 数组中的逆序对：表示数组有序程度
- 数组中第n大的元素
- 索引堆 用swap max min

# 字符串转化为数字；(注意细节处理)

# 数据流的中位数；(两个堆)

# 二叉树的直径；(递归)

# 双向链表的插入；
# 手撕快速排序；

# 手撕：字符串中回文子串的数目；(dp)
# 手撕：给你一个字符串，返回所有它能表示的IP地址；(回溯)
# 有10亿个数，如何找出其中最小的100个数；(堆)


剪绳子；(dp或者贪心)

# 找出两个序列中的最长公共子序列；(dp)

# 括号生成；(回溯)
# 两个并发线程T1和T2，分别只能打印A和B，要求写一段代码，可以一直打印序列"AABBAABB..."(不会)

# 二叉树的后序遍历，递归和非递归；

# 手撕冒泡排序，并分析时间复杂度；

# 查找二叉树中第k小的元素

# LRU算法的实现

# 给定n个正整数，如何找出最小的K个正整数
# 给定一组整数1000以内，如何高效去除重复的数

中序遍历

单链表中的中间节点

每次走一楼或者两楼，到n楼有几种方法。

10万以内的素数，选取某个子集，子集之和也是素数的有多少种

桶排序和跳跃表排序

二叉树中两个节点的最近公共父节点

手写单例模式、写代码判断内存大端小端


写代码，对于一个无序单链表，分别将其中的奇数和偶数取出存成两个有序链表


写二叉树的前序遍历代码，递归和非递归形式

写堆、快速排序代码

手撕二分查找，完了写旋转数组的二分查找，要用上面一个函数

什么是平衡二叉树

写代码，判断一棵树是不是平衡二叉树

，给出一个n * m的矩阵，请输出它逆时针旋转90度之后的矩阵


算法：删除链表指定元素

最长无重复字符子串

std::weak_ptr如何转std::shared_ptr
std::weak_ptr::lock存在的意义是什么
C++反射有了解过吗，标准有吗，第三方库呢，说说看
内存拷贝函数memcpy函数实现

有序链表查找某个元素 （顺序查找 O(N)，建立跳跃表查找 O(logN)）

11. 动态规划和贪心算法有啥区别，分别举个栗子

手撕代码题：给一个 N+1个数的数组，满足 A[0]>A[1],A[N]>A[N-1]。最快的办法找到一个 i， 满足 A[i-1] ≥ A[i] ≤ A[i+1]

4.手撕代码：自己实现链表，无序链表，对链表值奇偶分离并排序，空间复杂度 O(1)
5.手撕代码：给定一个数字 N（ N 是平方数），打印输出螺旋矩阵

4.手撕代码：判断在旋转后数组是否是严格递增
5.手撕代码：严格递增旋转数组的最小值的下标

Hash的底层实现
6. Hash怎么解决碰撞冲突


手撕代码，给定一个无序整数数组，输出排序后每个元素对应的下标。 注意：元素可能存在重复，如果重复则下标相同。（血崩，本以为这个题肯定有巧妙办法去实现，再就是着急写完，因为深信服约的面试时间就开始了，不可能直接进行sort，想用bitmap去写，写完之后，发现思路根本不对，当时就崩了，脑子蒙了）

9.设计一个 hashtable

两个数组，存的是长整型，现在交换数组元素，是一个数组的所有元素都大于另一个数组的元素，并且保证两个数组的原始长度不变，怎么设计，算法复杂度多少

手撕代码：利用无序数组非递归方式建立 BST，并迭代中序遍历输出

手撕代码：1）给定一个数字数组，返回哈夫曼树的头指针。2）最长公共连续子序列

写代码，去掉字符串中的空格空格



如何判断一个图是否连同？

DFS、BFS、并查集


1、53个人中，任选3个人至少有两个人生日相同的概率。

2、旋转数组找最小值？(手撕)

3、10亿个IP，取出频次出现最多的TOP10个IP？(思路题)

https://www.nowcoder.com/practice/e19927a8fd5d477794dac67096862042?tpId=117

手撕代码：
* 二叉搜索树转双向链表

作者：逝者如斯夫~不舍昼夜
链接：https://www.nowcoder.com/discuss/330950
来源：牛客网

实现一个堆，包括插入和删除元素函数的实现
* 字符串按空格反转（I LOVE SHOPEE => I EVOL EEPOHS）
* 链表按空格反转（I->' '->L->O->V->E->' '->S->H->O->P->E->E => I->' 'E->V->O->L->' 'E->E->P->O->H->S）

手撕代码：
* 使用堆实现TOP K问题
* 二叉树的层次遍历

* 字符串转int
* 二叉树转换为单链表

手撕代码：
* 求A^B的后三位数
* 有一个日志系统，统计在某一段时间内某个IP出现的次数

手撕代码：
* 最长连续子串
* 基于快排的思想实现TOP K

用数组实现一个栈，并在O(1)时间复杂度内获取最小值，如果是队列该怎么做
作者：逝者如斯夫~不舍昼夜
链接：https://www.nowcoder.com/discuss/330950
来源：牛客网

手撕代码：
* XML格式解析
* 有序数组找到第一个小于0的数和第一个大于0的数
* fork和循环结合后打印多少个字符
* 实现一个string类
* 矩阵左上角到右下角的最短路径和
* 实现一个智能指针
* 合并两个排序数组并去重
* 最长无重复子串
* 两个排序数组找中位数
  先序+中序怎么建二叉树
* string转float
  一个不用交换的排序算法
  作者：空大老石头
  链接：https://www.nowcoder.com/discuss/203548
  来源：牛客网
  手写tcp服务端客户端接口
7. 什么是平衡二叉数
   答：我先讲了一下排序二叉树，有什么缺点，然后讲什么是平衡二叉树
   再问：给了个具体例子:
   10
   8  16
   6 9
   这颗二叉树要新插入一个5怎么做？
   答：5成为6的左孩子导致二叉树不平衡，要进行右旋转。
   问：具体怎么旋转的，给你15分钟，代码实现一下
   答：？？？？？
8. 算法题：k个有序链表合并。要求讲一下时间复杂度。

作者：SFINEA
链接：https://www.nowcoder.com/discuss/207322
来源：牛客网

11. 编程题1： 吃豆子（二维表中最多每个格子一个豆子，从左上角开始，只能左右下的走，问吃完所有豆子需要的最短步数）
12. 编程题2： 集合S中为string，问S中哪个字符串和指定串T的距离最短（距离：就是两个字符串变换的距离，这个题是Trie树或者AC自动机做）
13. 编程题3： 两个字符串变换的最短距离（二维dp，可优化到一维，后来面试官说最优解用状压dp做


作者：hajimei
链接：https://www.nowcoder.com/discuss/207096
来源：牛客网

.怎么实现一个先进先出的队列。
一开始说记录好第一个进去的值的index就好了。
后来问如果有大的数据量了怎么办。
想了半天才想到链表。
然后就是链表的时间复杂度。
然后问试过按照优先度输出怎么做。
我回答可以用TreeMap来装在链表，key是优先度。
然后追问TreeMap怎么来的。 红黑树。
红黑树怎么回事？ 因为我上数据结构课的时候老师光讲AVL树了，我只知道红黑树是基于AVL树的。
然后面试官估计看我这么菜，也不接着问了，直接跳过。


作者：hajimei
链接：https://www.nowcoder.com/discuss/207096
来源：牛客网

如何找到第K个最大的数值。
想到了排序。然后追问用什么排序，我就说快排。
然后问了快排怎么实现的，时间复杂度。
时间复杂度我巴拉巴拉说了一堆，为什么是T(n) = 2*T(n/2) + n,然后根据主定理得出nlogn。
然后。。。问我为什么？我真的一脸懵，是要我解这个式子吗。。。
然后继续追问有没有别的方法。。。更懵了，想了半天估计看我太菜直接跳过了。


作者：犇渣渣
链接：https://www.nowcoder.com/discuss/213481
来源：牛客网

假设，已知一个出栈的序列，求所有可能的入栈序列
给一个数组里面有q个待查询节点，节点都是在一颗节点数为n的二叉树上的，问它们的最小公共祖先是谁
给定一个单向链表，节点数据结构如下，除了包含一个next指针，还有一个rand指针，随机指向链表中的某一元素，或者为空指针。实现一个函数，深复制这个链表。


判断两个链表是否相交。讲思路和复杂度，也很简单。

编程题：一个数组，将大于0的数字排在数组前面，相对顺序不要求

编程题：实现一个队列，大小定长



作者：bieliwoen
链接：https://www.nowcoder.com/discuss/213405
来源：牛客网

实现memcpy。写了十分钟，面试官提示指针有问题。又改了几分钟，还是没改对。。。
最后还是在面试官的提示下才明白问题在哪，最后才改对了，最后还问了一个问题：一个一个字节拷贝比较慢，有没有快一点的办法。。。我太菜了orz，这还只是噩梦的开始

再写到题吧，每隔k个元素反转链表，例如 1->2->3->4->5->6->7->8->NULL 变为 3->2->1->6->5->4->8->7->NULL。
链表的题真的头疼。写了二十多分钟还没写完，面试官提示有个地方没写对，然后又改了几分钟。
然后面试官又说还是有问题，改了几分钟还没改出来，面试官说换道题吧。。。我等这句话等了好久。。。

面试官说了句你这指针学的不好啊。

64匹马，8个赛道，最少要比多少次？这道题之前看过，不过讲的有点不太流畅。

作者：bieliwoen
链接：https://www.nowcoder.com/discuss/213405
来源：牛客网

出道代码题吧：

1
2
3
给定m个可以重复的字符 [a, b, c, c]，以及一个长度为n的字符串tbcacbdata，
问能否在这个字符串中找到一个长度为m的连续子串，使得这个子串刚好由上面m个字符组成，顺序无所谓，
返回任意满足条件的一个子串的起始位置，未找到返回-1。比如上面这个例子，3。
写了十五分钟，思路应该没什么问题


1.手撸有序数组合并

2.手撸汉诺塔

3.手撸反转字符串


编程：一个字符串数组，各字符串元素无重复，找出成分相同的，如abc和cba

写了个判回文链表

1.判断两个二叉树是否相等

2.翻转数组中给定一个数字求出他所在位置的下标

3.给一个字符串，求所有可能的ip地址

作者：瓜大疯
链接：https://www.nowcoder.com/discuss/211943
来源：牛客网

一面 逆序对
二面 判断回文字符串；两个字符串的最长公共子串；KMP
三面 topk问题以及分析时间复杂度；通过调用一个没有形参的函数，去改变调用函数里面的参数（涉及到函数压栈和ebp的问题）；集合的子集

1.链表对折，要求O(1)空间，例如：
将1->2->3->4....->n-1->n->null 对折成 1->n->2->n-1->3->n-2....->null
提问：有什么想问的？

逆时针打印矩阵，例如：
1 2 3
4 5 6 => 147896325
7 8 9
提问：有什么想问的？

作者：瓜大疯
链接：https://www.nowcoder.com/discuss/211943
来源：牛客网

1.已知f()函数以概率p输出1，以概率1-P输出0。然后实现g()等概率的输出1和0:
int g()
{
}
进一步通过刚实现的g()，实现等概率输出0-n的函数int h(int n):
int h(int n)
{
}
2.实现Linux命令tail -f filename的函数？（需要检查参数和文件类型是否合格）
int main(int argc, char* argv[])
{
}
提问：有什么想问的

1.二叉树的右视角，例如：
8
5 15 => 8,15,6,7
3 6
7


稳定的排序算法有哪些

递归的优缺点，项目中用到没有

string 转 int 异常情况很多 要考虑全啊 我就没考虑溢出 考虑全确实挺难的

算法题：二叉树中任意两个节点距离的最大值
什么是内存栅栏
volatile关键字的作用


讲一下二叉搜索树，写节点的删除代码
代码：实现lru

讲讲红黑树、平衡二叉树、二叉搜索树

调整数组左边奇数右边偶数

一个房间里面有三盏灯，外面有三个开关，只进去一次怎么确定哪个开关对应那盏灯。

对一个乱序的单链表进行排序，要求是空间复杂度O(1)，时间复杂度O(nlogn)（实现）


作者：火的意志
链接：https://www.nowcoder.com/discuss/217106
来源：牛客网

消消乐，给定一个数字序列，将连续的数字全部消除，比如1,2,3,3,3,2,3，返回1,2,2,3（用栈做）
消消乐升级，只要有相同连续数字，全部消除，如1,2,3,3,3,2,3，返回1,3（用栈做，上一题代码上再加判断）

作者：火的意志
链接：https://www.nowcoder.com/discuss/217106
来源：牛客网

实现一个能解决冲突的hashmap（用的链表解决冲突，感觉手写代码没有键盘写方便，越写越乱）
如何实现这个hashmap的线程安全。这里在写的时候加锁，读的时候，面试官说，“读的时候用吗”，口气就是“我觉得不用吧。”于是就说不加。但是面试结束后，想想，如果读写同时进行，而且都是同一块目标区域。。。觉得应该用读写锁，多个线程可以同时读，但是只要有一个在写，其他都不能读。


算法题，很简单判断链表是否相交，求交点

关于11中的完美转发怎样理解的，解决什么问题，它为什么会存在

是否了解匿名函数，也就是lamda表达式？闭包怎样理解？

作者：EthanHunt
链接：https://www.nowcoder.com/discuss/216828
来源：牛客网

1. 给一组日志文件，包含用户id，登陆时间，登出时间，假定时间范围一天之内，求出一天之内在线用户数量的峰值，并给出时间区间（多个相等区间都输出，可以假设登录登出时间为整数）：
   最开始想用pair存登陆登出时间，想排序如何排的时候一拍脑壳我管你是张三李四干什么，直接把登陆时间和登出时间分别当做两个向量分别排序，然后从小到大扫描，类似归并排序的merge操作，先判断下一次操作登陆在前还是登出在前，登陆加一登出减一，得到当前时刻的在线人数，至于怎么得到最大值，怎么存储时间区间，诸君随意，方便就好～
2. 给一个01矩阵，计算1被0分割成了几块（参考围棋规则，上下左右相邻算作一块，否则为不同块）：
   简单的深度优先搜索，回溯算法5分钟搞定～

作者：EthanHunt
链接：https://www.nowcoder.com/discuss/216828
来源：牛客网

用简单数据结构实现一个符合LRU算法的缓存队列（要求 put 和 get 操作的时间复杂度均为 O(1) ）：
两个map加一个链表即可，一个map存key和value，一个map存key和链表指针，链表存LRU队列，get() 的时候利用存指针的map更新链表队列，put() 简单实现就可以。这个题问的时候脑子已经累了，答出了框架但细节没描述清楚，不过细节其实挺简单的～有更好的方法还请不吝赐教


判断链表是否有环、LRU的实现

给定一个二叉树，再给定二叉树上的两个结点，求这两个结点的LCA。
链表快排。

不用加减乘除求一个数的7倍
6.A B两个文件 各有50亿个url，每个url 64K，怎么找出相同的url
7.10亿个数求topk

编程题： 给你一个有序整数数组，数组中的数可以是正数、负数、零，请实现一个函数，这个函数返回一个整数：返回这个数组所有数的平方值中有多少种不同的取值。

作者：The_Rolling_D20
链接：https://www.nowcoder.com/discuss/219392
来源：牛客网

算法：
有一个长度为 n 的数组，存储 0-100 范围内的数据，找出其中每一个数字出现的次数。
有一个 n*m 的二维矩阵，矩阵中每行每列的元素都是有序的，从左到有依次增大，从上到下依次增大。给定一个值，找到它在矩阵中对应的位置

剑指offer中的替换字符串中的空格
求一个二叉树的最小高度

2.动态链接库和静态链接库的区别。
数组里查找，三数求和为零的所有组合，有个博客总结的很全

完全二叉树的第六层有10个叶子节点，该二叉树最多有多少个节点

算法，无序数组, i和j表示数组下标，在i<=j的情况下，求A[i]-A[j]的最大值.

线性时间得到栈中的最小元素

给一个链表，一个target，把比target小的放在前面，大于target的放在后面。
条件：空间O(1)，不能再链表前加空节点，不适用额外数组啊之内，不能改变节点存储的地址即不能swap。

给定一个数组，找出最长子序列的长度，子序列满足：递增-递减-递增波动变化。。。我用动态规划写的，写完才发现有不少小问题。。。

手撕代码，给定一个无序整数数组，输出排序后每个元素对应的下标。 注意：元素可能存在重复，如果重复则下标相同。


8.哈希表解决冲突的方法
打印二叉树每一层最左侧的节点

两个队列实现一个栈


将一个长度为n的数组A的元素循环右移k位,比如
数组 1, 2, 3, 4, 5循环右移3位之后变成3, 4, 5, 1, 2

给一串数字，返回所有可能的IP地址，比如给 12101101，返回1.210.110.1、121.0.1.101等。

翻转链表、二叉排序树转双向链表、求一个数的平方根

手撕代码\a\b\..\.\,输出\a

实现斐波那契数列，非递归方法

编程题二:给一颗二叉树，要求打印出每一层的结点，奇数层的结点从左至右打印，偶数层的结点从右至左打印（利用两个栈

给一颗二叉树，每个结点是0或者1值，要求删除叶节点是0的值，既删完后所有叶节点都不是0。

实现shared_ptr
③实现vector的push_back

判断一个数是不是回文数
判断一个二叉树是不是平衡二叉树
指出代码中的问题（一个单例模式）需要考虑线程安全 饿汉、懒汉

有哪些数据结构，图是如何深度搜索，树和图的深度搜索有什么区别。

如何用vector实现栈

扫雷，写一个随机埋n个雷的算法(面试官想考察shuffle算法的原理)

知道跳表吗

实现memmove函数
判断一棵树是不是二叉搜索树

判断两个链表是否交叉

.算法题一，长度为n的数组，有一个长度为k的滑动窗口，询问各个滑动窗口内的中位数。
11.算法题二，二维数组从上到下从左到右单调递增，要求O(n)复杂度数量级内查找出二维数组内是否存在该数

大端小端，实现一下怎么确定所用编译平台的大小端(

最长公共子数组

给一个数组，实现最小堆；
24、编程题：逆时针顺序打印一个二维数组

手撕：数组中连续子数组的最大和；(dp)
字符串转化为数字；(注意细节处理)

手撕：堆排序，并分析时间复杂度；
手撕：链表中环的入口节点，并解释原因；
二叉搜索树的特征，查找和插入的时间复杂度；
为什么说二叉搜索树有时会不稳定，如何改进？(可能会退化为链表；改进为平衡二叉查找树)
AVL树大概的调整过程；(左旋右旋)
红黑树的特征以及大概的调整过程；



数据结构方面我是跟着学堂在线上邓俊辉的课来学。邓的课非常精巧，获誉无数，六纬空间可以下载。数据结构总结来看，包括栈，队列，链表，向量，堆，树，图，集合(并查集)，哈希表等。其中链表，堆，树(重中之重)，哈希表是重点。图虽然经典，但是个人感觉考察的不多，知道最短路径基本就可以了。这部分题目看《剑指offer》。但相比题目，面试官更喜欢考察某种数据结构的实现，如用数组实现链表，写二叉树的接口，用数组实现堆，并查集等。比较有挑战性的是实现红黑树，B+树等，但属于极少数。
数据结构与算法：

两个队列实现一个栈；
最长回文子串；(dp)


class A {
public:
     template<typename T>
     virtual T fun(T t){return t;}
}



nposerasefindbegin endappendsubstr

# C++中如何将string类型转换为int类型？

首先提出解决方案：

- atoi
- strtol
- stoi

这几个有什么不同呢？下面测试对比。

> C语言风格函数

atoi与strtol对比：

```cpp
string str = "16s";
int a = atoi(str.c_str());
int b = strtol(str.c_str(), nullptr, 10);
```

输出：

```
atoi的结果为:16
strtol的结果为:16
```

这两个函数都是从字符串开始寻找数字或者正负号或者小数点,遇到非法字符终止。

所以到上述s字符就不输出了，提前结束，也就是说当你的字符串不是数字的时候，或者小数点等非数字，不会报异常！直接输出0.

例如：

```cpp
string str = "asdsa";
int a = atoi(str.c_str());
int b = strtol(str.c_str(), nullptr, 10);
```

输出：

```
0
0
```

strtol相比与atoi来说，支持多种进制转换,例如8进制等

例如：

```
int b = strtol(str.c_str(), nullptr, 8);
```

> C++风格

在C++中可以使用stoi来转int，这个函数相比于前两个一个最大特点是：异常！

我们知道C++相比于C语言多了异常，这也是这个函数在C++中具有的最显著功能。

例如：

```cpp
string str1 = "asq,";
//    int c = stoi(str1);    // 报异常
string str2 = "12312";
int c = stoi(str2);     // ok
cout << c << endl;
```

异常如下：

```
terminate called after throwing an instance of 'std::invalid_argument'
what():  stoi
```

> 自定义

也就是自己写呗，如下：

```cpp
int stringToInt(const string &s) {
    int v;
    stringstream ss;
    ss << s;
    ss >> v;
    return v;
}
int main() {
    int i = stringToInt("2.3");
    cout<<i<<endl;
}
```## do{...}while(0)的使用

### 避免语义曲解

例如：

```
#define fun() f1();f2();
if(a>0)
   fun()
```

这个宏被展开后就是：

```
if(a>0)
   f1();
   f2();
```

本意是a>0执行f1 f2，而实际是f2每次都会执行，所以就错误了。

为了解决这种问题，在写代码的时候，通常可以采用`{}`块。

如：

```c++
#define fun() {f1();f2();}
if(a>0)
   fun();
// 宏展开
if(a>0)
{
    f1();
    f2();
};
```

但是会发现上述宏展开后多了一个分号，实际语法不太对。(虽然编译运行没问题，正常没分号)。

### 2.2避免使用goto控制流

在一些函数中，我们可能需要在return语句之前做一些清理工作，比如释放在函数开始处由malloc申请的内存空间，使用goto总是一种简单的方法：

```c++
int f() {
    int *p = (int *)malloc(sizeof(int));
    *p = 10; 
    cout<<*p<<endl;
#ifndef DEBUG
    int error=1;
#endif
    if(error)
        goto END;
    // dosomething
END:
    cout<<"free"<<endl;
    free(p);
    return 0;
}
```

但由于goto不符合软件工程的结构化，而且有可能使得代码难懂，所以很多人都不倡导使用，这个时候我们可以使用do{...}while(0)来做同样的事情：

```c++
int ff() {
    int *p = (int *)malloc(sizeof(int));
    *p = 10; 
    cout<<*p<<endl;
    do{ 
#ifndef DEBUG
        int error=1;
#endif
        if(error)
            break;
        //dosomething
    }while(0);
    cout<<"free"<<endl;
    free(p);
    return 0;
}
```

这里将函数主体部分使用do{...}while(0)包含起来，使用break来代替goto，后续的清理工作在while之后，现在既能达到同样的效果，而且代码的可读性、可维护性都要比上面的goto代码好的多了。

### 2.3 避免由宏引起的警告

内核中由于不同架构的限制，很多时候会用到空宏，。在编译的时候，这些空宏会给出warning，为了避免这样的warning，我们可以使用do{...}while(0)来定义空宏：

```
#define EMPTYMICRO do{}while(0)
```

### 2.4 **定义单一的函数块来完成复杂的操作**

如果你有一个复杂的函数，变量很多，而且你不想要增加新的函数，可以使用do{...}while(0)，将你的代码写在里面，里面可以定义变量而不用考虑变量名会同函数之前或者之后的重复。
这种情况应该是指一个变量多处使用（但每处的意义还不同），我们可以在每个do-while中缩小作用域，比如：

```c++
int fc()
{
    int k1 = 10;
    cout<<k1<<endl;
    do{
        int k1 = 100;
        cout<<k1<<endl;
    }while(0);
    cout<<k1<<endl;
}
```函数重载和函数匹配

const




问一个结构体占的内存大小,地址对齐 struct A{ char a;int b;char c} struct B{int a;char b,c;} 如何让这两个结构体占的内存一样大? 不能移动成员定义顺序

#pragma pack(1)     // 设定为 1 字节对齐



string BigNumAdd(const string& strNum1, const string& strNum2)
{
    string strSum;
    int len1 = strNum1.size()-1;
    int len2 = strNum2.size()-1;
    int bit = 0;                //保存进位

    //从结尾开始每位相加 
    while (len1>=0 && len2>=0)
    {
        //求每位的和(要把进位也加上) 
        int tmpSum = strNum1[len1]-'0' + strNum2[len2]-'0' + bit;
        //保存进结果 
        strSum += tmpSum % 10 + '0';
        //求进位 
        bit = tmpSum / 10;
        --len1;
        --len2; 
    }

    //两个整数长度不相等(肯定有一个已经加完了,不需要再额外加if来判断，因为while就可以判断)
    while (len1 >= 0)
    {
        //和上个while循环一样
        int tmpSum = strNum1[len1]-'0' + bit;
        strSum += tmpSum % 10 + '0';
        bit = tmpSum / 10;
        --len1; 
    }
    while (len2 >= 0) 
    {
        //和上个while循环一样
        int tmpSum = strNum2[len2]-'0' + bit;
        strSum += tmpSum % 10 + '0';
        bit = tmpSum / 10;
        --len2; 
    }

    //最高位有进位
    if (bit != 0)
        strSum += bit + '0'; 

    //反转
    reverse(strSum.begin(), strSum.end()); 

    return strSum;
}# 宏那些事

## 1.宏中包含特殊符号

分为几种：`#`，`##`，`\`

### 1.1 字符串化操作符（#）

**在一个宏中的参数前面使用一个#,预处理器会把这个参数转换为一个字符数组**，换言之就是：**#是“字符串化”的意思，出现在宏定义中的#是把跟在后面的参数转换成一个字符串**。

**注意：其只能用于有传入参数的宏定义中，且必须置于宏定义体中的参数名前。**

例如：

```c++
#define exp(s) printf("test s is:%s\n",s)
#define exp1(s) printf("test s is:%s\n",#s)
#define exp2(s) #s 
int main() {
    exp("hello");
    exp1(hello);

    string str = exp2(   bac );
    cout<<str<<" "<<str.size()<<endl;
    /**
     * 忽略传入参数名前面和后面的空格。
     */
    string str1 = exp2( asda  bac );
    /**
     * 当传入参数名间存在空格时，编译器将会自动连接各个子字符串，
     * 用每个子字符串之间以一个空格连接，忽略剩余空格。
     */
    cout<<str1<<" "<<str1.size()<<endl;
    return 0;
}
```

上述代码给出了基本的使用与空格处理规则，空格处理规则如下：

- 忽略传入参数名前面和后面的空格。

```c++
string str = exp2(   bac );
cout<<str<<" "<<str.size()<<endl;
```

输出：

```
bac 3
```

- 当传入参数名间存在空格时，编译器将会自动连接各个子字符串，用每个子字符串之间以一个空格连接，忽略剩余空格。

```c++
string str1 = exp2( asda  bac );
cout<<str1<<" "<<str1.size()<<endl;
```

输出：

```
asda bac 8
```

### 1.2 符号连接操作符（##）

**“##”是一种分隔连接方式，它的作用是先分隔，然后进行强制连接。将宏定义的多个形参转换成一个实际参数名。**

注意事项：

**（1）当用##连接形参时，##前后的空格可有可无。**

**（2）连接后的实际参数名，必须为实际存在的参数名或是编译器已知的宏定义。**

**（3）如果##后的参数本身也是一个宏的话，##会阻止这个宏的展开。**

示例：

```c++

#define expA(s) printf("前缀加上后的字符串为:%s\n",gc_##s)  //gc_s必须存在
// 注意事项2
#define expB(s) printf("前缀加上后的字符串为:%s\n",gc_  ##  s)  //gc_s必须存在
// 注意事项1
#define gc_hello1 "I am gc_hello1"
int main() {
    // 注意事项1
    const char * gc_hello = "I am gc_hello";
    expA(hello);
    expB(hello1);
}
```

### 1.3 续行操作符（\）

**当定义的宏不能用一行表达完整时，可以用”\”表示下一行继续此宏的定义。**

**注意 \ 前留空格。**

```c++
#define MAX(a,b) ((a)>(b) ? (a) \
   :(b))  
int main() {
    int max_val = MAX(3,6);
    cout<<max_val<<endl;
}
```## do{...}while(0)的使用

### 避免语义曲解

例如：

```
#define fun() f1();f2();
if(a>0)
   fun()
```

这个宏被展开后就是：

```
if(a>0)
   f1();
   f2();
```

本意是a>0执行f1 f2，而实际是f2每次都会执行，所以就错误了。

为了解决这种问题，在写代码的时候，通常可以采用`{}`块。

如：

```c++
#define fun() {f1();f2();}
if(a>0)
   fun();
// 宏展开
if(a>0)
{
    f1();
    f2();
};
```

但是会发现上述宏展开后多了一个分号，实际语法不太对。(虽然编译运行没问题，正常没分号)。

### 2.2避免使用goto控制流

在一些函数中，我们可能需要在return语句之前做一些清理工作，比如释放在函数开始处由malloc申请的内存空间，使用goto总是一种简单的方法：

```c++
int f() {
    int *p = (int *)malloc(sizeof(int));
    *p = 10; 
    cout<<*p<<endl;
#ifndef DEBUG
    int error=1;
#endif
    if(error)
        goto END;
    // dosomething
END:
    cout<<"free"<<endl;
    free(p);
    return 0;
}
```

但由于goto不符合软件工程的结构化，而且有可能使得代码难懂，所以很多人都不倡导使用，这个时候我们可以使用do{...}while(0)来做同样的事情：

```c++
int ff() {
    int *p = (int *)malloc(sizeof(int));
    *p = 10; 
    cout<<*p<<endl;
    do{ 
#ifndef DEBUG
        int error=1;
#endif
        if(error)
            break;
        //dosomething
    }while(0);
    cout<<"free"<<endl;
    free(p);
    return 0;
}
```

这里将函数主体部分使用do{...}while(0)包含起来，使用break来代替goto，后续的清理工作在while之后，现在既能达到同样的效果，而且代码的可读性、可维护性都要比上面的goto代码好的多了。

### 2.3 避免由宏引起的警告

内核中由于不同架构的限制，很多时候会用到空宏，。在编译的时候，这些空宏会给出warning，为了避免这样的warning，我们可以使用do{...}while(0)来定义空宏：

```
#define EMPTYMICRO do{}while(0)
```

### 2.4 **定义单一的函数块来完成复杂的操作**

如果你有一个复杂的函数，变量很多，而且你不想要增加新的函数，可以使用do{...}while(0)，将你的代码写在里面，里面可以定义变量而不用考虑变量名会同函数之前或者之后的重复。
这种情况应该是指一个变量多处使用（但每处的意义还不同），我们可以在每个do-while中缩小作用域，比如：

```c++
int fc()
{
    int k1 = 10;
    cout<<k1<<endl;
    do{
        int k1 = 100;
        cout<<k1<<endl;
    }while(0);
    cout<<k1<<endl;
}
```函数重载和函数匹配

const




问一个结构体占的内存大小,地址对齐 struct A{ char a;int b;char c} struct B{int a;char b,c;} 如何让这两个结构体占的内存一样大? 不能移动成员定义顺序

#pragma pack(1)     // 设定为 1 字节对齐



string BigNumAdd(const string& strNum1, const string& strNum2)
{
    string strSum;
    int len1 = strNum1.size()-1;
    int len2 = strNum2.size()-1;
    int bit = 0;                //保存进位

    //从结尾开始每位相加 
    while (len1>=0 && len2>=0)
    {
        //求每位的和(要把进位也加上) 
        int tmpSum = strNum1[len1]-'0' + strNum2[len2]-'0' + bit;
        //保存进结果 
        strSum += tmpSum % 10 + '0';
        //求进位 
        bit = tmpSum / 10;
        --len1;
        --len2; 
    }

    //两个整数长度不相等(肯定有一个已经加完了,不需要再额外加if来判断，因为while就可以判断)
    while (len1 >= 0)
    {
        //和上个while循环一样
        int tmpSum = strNum1[len1]-'0' + bit;
        strSum += tmpSum % 10 + '0';
        bit = tmpSum / 10;
        --len1; 
    }
    while (len2 >= 0) 
    {
        //和上个while循环一样
        int tmpSum = strNum2[len2]-'0' + bit;
        strSum += tmpSum % 10 + '0';
        bit = tmpSum / 10;
        --len2; 
    }

    //最高位有进位
    if (bit != 0)
        strSum += bit + '0'; 

    //反转
    reverse(strSum.begin(), strSum.end()); 

    return strSum;
}# 友元函数与友元类

## 0.概述

友元提供了一种 普通函数或者类成员函数 访问另一个类中的私有或保护成员 的机制。也就是说有两种形式的友元：

（1）友元函数：普通函数对一个访问某个类中的私有或保护成员。

（2）友元类：类A中的成员函数访问类B中的私有或保护成员

优点：提高了程序的运行效率。

缺点：破坏了类的封装性和数据的透明性。

总结：
- 能访问私有成员
- 破坏封装性
- 友元关系不可传递
- 友元关系的单向性
- 友元声明的形式及数量不受限制

## 1.友元函数

在类声明的任何区域中声明，而定义则在类的外部。

```
friend <类型><友元函数名>(<参数表>);
```

注意，友元函数只是一个普通函数，并不是该类的类成员函数，它可以在任何地方调用，友元函数中通过对象名来访问该类的私有或保护成员。

具体代码见：[friend_func.cpp](friend_func.cpp)

```c++
#include <iostream>

using namespace std;

class A
{
public:
    A(int _a):a(_a){};
    friend int geta(A &ca);  ///< 友元函数
private:
    int a;
};

int geta(A &ca) 
{
    return ca.a;
}

int main()
{
    A a(3);    
    cout<<geta(a)<<endl;

    return 0;
}
```

## 2.友元类
友元类的声明在该类的声明中，而实现在该类外。

```
friend class <友元类名>;
```

类B是类A的友元，那么类B可以直接访问A的私有成员。

具体代码见：[friend_class.cpp](friend_class.cpp)
```c++
#include <iostream>

using namespace std;

class A
{
public:
    A(int _a):a(_a){};
    friend class B;
private:
    int a;
};

class B
{
public:
    int getb(A ca) {
        return  ca.a; 
    };
};

int main() 
{
    A a(3);
    B b;
    cout<<b.getb(a)<<endl;
    return 0;
}
```


## 3.注意
- 友元关系没有继承性
  假如类B是类A的友元，类C继承于类A，那么友元类B是没办法直接访问类C的私有或保护成员。

- 友元关系没有传递性
  假如类B是类A的友元，类C是类B的友元，那么友元类C是没办法直接访问类A的私有或保护成员，也就是不存在“友元的友元”这种关系。堆和栈的区别?栈多大?

NUll nullptr区别

预处理阶段做什么

多线程共享内容线程间怎么共享资源

stl内存配置器

开头撸一段代码，用两个栈去实现一个队列，楼主写出来后面试官又让实现模板（平时模板用的少，没写出来），还问了模板的底层实现（orz）

# vector的push_back()方法的实现

# map, unordered_map的区别

# 左值与右值分别指什么

# malloc(0)会怎么样？(脑子有坑？正常人都不会这样做吧？)

# C++中哪些函数不能被声明为虚函数？(普通、内联、构造、友元、静态)

# 友元函数可以被声明为虚函数吗？为什么？(不能，友元函数不是成员函数，不能被继承，不支持运行时多态)

# vector和list中，删除末尾的元素，其指针和迭代器如何变化？若删除的是中间的元素呢？

# c/c++程序如何控制执行到某个特定内存地址

# C++对象内存布局

# C++模板方面的问题，先给了三个重载函数（普通函数、函数模板、特例化的函数模板），根据入参确定调用的函数。接着又问了类型萃取的问题，如何使用模板来判断入参是一个类对象指针，还是一个内置类型指针

# C中inline的作用

# STL中Vector、List、Map底层实现

类A空，类B继承A，B中有一个虚函数，sizeof大小

类A空，类B中有一个虚函数和一个类A对象，sizeof大小
Vector的扩容，如果数据量很多扩容会怎么样，怎么设计更好的

用define写一个结构体类型的偏移地址

怎么让Vector<int> 在栈中分配内存

STL的线程安全

举例多线程可能的问题

进程调度算法，举例LRU，用STL实现LRU

写代码求虚函数表地址

调用函数时栈的操作

多线程单例模式

继承有几种方式？
12. 多态两种讲一下

么从控制台读入多行？
8.成员函数存在一个隐藏变量，是啥，怎么工作的？（ this指针）

常量函数成员为什么无法调用非常量数据成员？（底层 const的 this指针，无法传参拷贝给非底层 const的指针对象）

想要阻止继承怎么办 （ final）
15. 还有别的方式吗 （ emmmmm，构造析构仍在 private里面，被怼了，那怎么实例化啊）

智能指针 shared_ptr、 unique_ptr应用场景
8. shared_ptr的内部的 count计数是否是线程安全的
   9.那调用 shared_ptr指向的对象的方法是否是线程安全的
10. 如何解决线程安全
11. 上题自己挖坑，讲到了一种硬件方式实现原子化。面试官 :atomic这个了解吗？面试官详细的给我讲解了这个 atomic类，学到了。


12. sizeof计算给定 struct，为什么
13. 如何压缩 struct，不会产生内存对齐（不会 …….）
14. 函数指针和指针函数区别
15. 那为什么要进行内存对齐


class A类型的指针，此时通过 dynamic_cast转换为 class B类型的指针，会出现什么问题，是否能通过编译，或者是否能运行（说是不能，但是编译错误还是运行错误不确定）








# cache一致性；
# 虚拟内存与物理内存的区别；
# 死锁
# 线程与进程的区别？
# 进程什么时候由用户态转化为内核态？(系统调用、中断、陷入)
# 内核态与用户态的区别？(安全性)

多线程如何进行线程选择

2.多线程
3.多进程
4.多线程编程需要注意什么问题？（线程安全问题）
5.怎样解决线程安全？ （加锁）
6.讲一下锁？（悲观锁，乐观锁）
7.加锁会出现什么问题？ （死锁）
8.介绍一下死锁（死锁的定义，条件）
9.进程间通信方式（ IPC）有哪几种？

内存模型了解吗（请问是不是问内存置换算法？）不是（那是不是问的虚拟内存概念）不是，你知道的 zero copy吗（懵逼，不知道）
操作系统出现死锁的条件
3、滑动窗口协议
4、内存置换的集中常见策略
5、LRU的命中率计算方法
6、说一下IO多路复用

进程和线程，为什么要有线程

线程在什么场景下才要使用

1、和进程相比，它是一种非常"节俭"的多任务操作方式。在linux系统下，启动一个新的进程必须分配给它独立的地址空间，建立众多的数据表来维护它的代码段、堆栈段和数据段，这是一种"昂贵"的多任务工作方式。（资源）

2、运行于一个进程中的多个线程，它们之间使用相同的地址空间，而且线程间彼此切换所需时间也远远小于进程间切换所需要的时间。据统计，一个进程的开销大约是一个线程开销的30倍左右。（切换效率）

3、线程间方便的通信机制。对不同进程来说，它们具有独立的数据空间，要进行数据的传递只能通过进程间通信的方式进行，这种方式不仅费时，而且很不方便。线程则不然，由于同一进城下的线程之间贡献数据空间，所以一个线程的数据可以直接为其他线程所用，这不仅快捷，而且方便。（通信）

除以上优点外，多线程程序作为一种多任务、并发的工作方式，还有如下优点：
1、使多CPU系统更加有效。操作系统会保证当线程数不大于CPU数目时，不同的线程运行于不同的CPU上。(CPU设计保证）
2、改善程序结构。一个既长又复杂的进程可以考虑分为多个线程，成为几个独立或半独立的运行部分，这样的程序才会利于理解和修改。（代码易维护）


ubuntu开机的时候系统做了什么

1）加载BIOS

BIOS程序首先检查，计算机硬件能否满足运行的基本条件，这叫做”硬件自检”。硬件自检完成后，BIOS把控制权转交给下一阶段的启动程序。

2）读取MBR

计算机读取该设备的第一个扇区，也就是读取最前面的512个字节。如果这512个字节的最后两个字节是0x55和0xAA，表明这个设备可以用于启动；如果不是，表明设备不能用于启动，控制权于是被转交给”启动顺序”中的下一个设备。

3）Bootloader
在这种情况下，计算机读取”主引导记录”前面446字节的机器码之后，不再把控制权转交给某一个分区，而是运行事先安装的”启动管理器”（boot loader），由用户选择启动哪一个操作系统。
Boot Loader 就是在操作系统内核运行之前运行的一段小程序。通过这段小程序，我们可以初始化硬件设备、建立内存空间的映射图，从而将系统的软硬件环境带到一个合适的状态，以便为最终调用操作系统内核做好一切准备。
Boot Loader有若干种，其中Grub、Lilo和spfdisk是常见的Loader。Linux环境中，目前最流行的启动管理器是Grub。

4）加载内核
内核的加载，内核加载后，接开始操作系统初始化，根据进程的优先级启动进程。

子网掩码、CIDR的作用

进程的地址空间

线程和协程的区别，线程池的设计要注意什么？


作者：银联蛋蛋
链接：https://www.nowcoder.com/discuss/213870
来源：牛客网

总面试时间34分钟，8成凉面
1.项目问题：令牌桶添加令牌怎么实现的？
2.多线程实际问题：线程怎么创建需要传入什么参数，线程怎么退出，主线程如何等待子线程退出，可以顺便思考一下：进程怎么创建传参，进程怎么退出，主进程怎样等待子进程退出？
线程创建方式及传参：pthread_create是UNIX环境创建线程函数
头文件 #include<pthread.h>
函数声明 int pthread_create(pthread_t  *restrict tidp, const  pthread_attr_t  *restrict_attr,   void*（*start_rtn)(void*),   void   *restrict   arg);
返回值 若成功则返回0，否则返回出错编号
参数 1. 第一个参数为指向线程 标识符 的指针 2.第二个参数用来设置线程属性 3. 第三个参数是线程运行函数的地址。 4.最后一个参数是运行函数的参数。
在编译时注意加上-lpthread参数，以调用静态链接库。因为pthread并非Linux系统的默认库。
线程的几种状态： 1）就绪：参与调度，等待被执行，一旦被调度选中，立即开始执行
2）运行：占用CPU，正在运行中
3）休眠：暂不参与调度，等待特定事件发生
4）中止：已经运行完毕，等待回收线程资源
进程内典型全局资源如下：
1）代码区：这意味着当前进程空间内所有的可见的函数代码，对于每个线程来说，也是可见的
2）静态存储区：全局变量，静态空间
3）动态存储区：堆空间
主线程等待子线程退出：当thread::join()函数被调用后，调用它的线程会被block，join的作用是让主线程等待直到线程的执行被完成。基本上，这是一种可以用来知道一个线程已结束的机制。main是等待子线程结束才继续执行。当thread::join()返回时，OS的执行的线程已经完成，C++线程对象可以被销毁。
线程的锁：1. mutex是用来保证线程同步的，防止不同的线程同时操作同一个共享数据。
2. 使用lock_guard则相对安全，它是基于作用域的，能够自解锁，当该对象创建时，它会像m.lock()一样获得互斥锁，当生命周期结束时，它会自动析构(unlock)，不会因为某个线程异常退出而影响其他线程。
   sleep_until: 线程休眠至某个指定的时刻(time point)，该线程才被重新唤醒。

sleep_for: 线程休眠某个指定的时间片(time span)，该线程才被重新唤醒，不过由于线程调度等原因，实际休眠时间可能比sleep_duration 所表示的时间片更长。

线程怎么退出：
1.线程函数返回（最好使用该方法）。
2.同一个进程或另一个进程中的线程调用TerminateThread函数（应避免使用该方法）。
3.通过调用ExitThread函数，线程将自行撤消（最好不使用该方法）。
4.ExitProcess和TerminateProcess函数也可以用来终止线程的运行（导致该进程中的所有线程全部终止）。
进程的创建：fork()。
进程的退出：exit()或main函数return。
主进程等待子进程：waitpad()用于防止孤儿进程。
3.同步和异步的区别？epoll是同步还是异步？这个问题到目前网上好像还在争论，我给他分析了一波我觉得异步的原因epoll回调函数
epoll是同步IO，我理解是同步阻塞，因为所谓同步就是没有信号通知，epoll虽然用了回调函数，但本质上还是让线程或进程等着回调函数通知，并没有在内核中设置信号来通知
epoll有消息返回了。从操作系统层面来讲，一个进程去做另外一件事，然后内核通过信号量来通知进程，任务已经完成，这种行为可以称为异步，但epoll是回调函数所以是同步。



作者：银联蛋蛋
链接：https://www.nowcoder.com/discuss/213870
来源：牛客网

.栈是否有大小？
栈有大小的，linux下进程栈的默认大小是10M，可以通过ulimit-s来查看并修改默认栈的大小，默认一个线程要预留1M左右的栈的大小，所以一个进程拥有多个线程，堆的大小理论上近似等于进程虚拟空间的大小，linux下，进程虚拟空间一般为4G，进程的高位1G留给内核，低位3G留给用户，所以进程堆大小小于3G，32位linux下，进程4G空间，内核1G，用户3G，线程默认8M，所以最多380个线程。
Windows下进程栈默认1M，32位系统下一个进程空间4G，内核2G，用户2G，座椅最多开2048个线程。
8.哲学家进餐问题
解决死锁问题的办法就是同时只允许四位哲学家同时拿起同一边的筷子，这样就能保证一定会有一位哲学家能够拿起两根筷子完成进食并释放资源，供其他哲学家使用，从而实现永动，避免了死锁。举个最简单的栗子，假定 0~3 号哲学家已经拿起了他左边的筷子，然后当 4 号哲学家企图去拿他左边的筷子的时候，将该哲学家的线程锁住，使其拿不到其左边的筷子，然后其左边的筷子就可以被 3 号哲学家拿到，然后 3 号哲学家进餐，释放筷子，然后更多的哲学家拿到筷子并进餐。
如何才能实现当 4 号哲学家企图拿起其左边的筷子的时候将该哲学家的线程阻塞？这个时候就要用到该问题的提出者迪杰斯特拉（这货还提出了迪杰斯特拉最短路径算法，著名的银行家算法也是他发明的）提出的信号量机制。因为同时只允许有四位哲学家同时拿起左筷子，因此我们可以设置一个信号量 r ，使其初始值为 4 ，然后每当一位哲学家企图去拿起他左边的筷子的时候，先对信号量做一次 P 操作，从而当第五位哲学家企图去拿做筷子的时候，对 r 做一次 P 操作， r = -1 ，由 r < 0 得第五位哲学家的线程被阻塞，从而不能拿起左筷子，因此也就避免了死锁问题。然后当哲学家放下他左边的筷子的时候，就对 r 做一次 V 操作 。


TCP拥塞控制和流量控制

怎么测量栈的大小

栈与堆的分配速度

说说虚拟内存地址

进程通信方式？哪个最快？我说共享内存

什么是僵尸进程

kill用过吗？有哪几种参数

如何后台运行程序 &

如何选择多线程实现、多进程实现

进程的调度算法
协程和线程
LRU算法

同进程下的线程共享哪些资源，独有哪些资源

- 如何创建一个常驻进程

虚拟内存和物理内存

为什么线程切换代价比进程小

4.内存对齐的原因
5.内存对齐的原则，struct{char a;char b;int c};sizeof结果

内存泄漏平时用什么方法检测
CRT库是怎么知道有内存泄漏的，怎么定位到具体哪个文件哪一行代码

作者：幽癫怪逸
链接：https://www.nowcoder.com/discuss/227715
来源：牛客网

17.给你一片英文文章，如何从中找出出现次数前十的单词？（当时很懵逼）
18.给你两个字符串，如何检测一个字符串是不是另一个字符串的子序列，子序列是啥你知道吧？（KMP。。。说让我自己写会怎么写代码）

手写了两道代码题，一道二分查找，一道判断两个二叉树是否相等

二分查找原理以及适用条件
变长结构体（全脸懵逼）

查看一块共享内存被哪些进程持有，用什么命令？查看一个进程持有了哪些共享内存呢

动态库和静态库

C++函数参数入栈顺序

作者：tvyvnjs
链接：https://www.nowcoder.com/discuss/239726
来源：牛客网

现在有一个vector和一个list，分别有两个容器的迭代器，现在删除vector和list进行插入删除操作，问迭代器是否还有效，为什么
两个算法题：
第一个比较复杂，不好描述，讲了好久都没懂面试官的意思
第二题是给定一个无序的列表，要从列表中找出前K个最大的值,解释快排思想求topk的时间复杂度

空类默认有哪些函数

作者：LastDanceee
链接：https://www.nowcoder.com/discuss/241129
来源：牛客网

1. 介绍实习和项目
2. TIMEWAIT解释一下？为什么需要这个状态？
3. 如果在TIMEWAIT期间收到了数据包，会出现什么情况？（这个不会。。。
4. shutdown和close区别？
5. 介绍一下页表？
6. 页表的数据结构？除了有地址相关的参数还有什么？（我只说了多级页表，其他没说了，后来意识到他可能再说TLB？自闭了。。
7. 伙伴系统了解吗？介绍一下？
8. 分段和分页有什么区别？各自适合什么场景？
9. 伙伴算法晓得吗？介绍一下
10. 进程调度算法了解什么？介绍一下O(1)和CFS？

网络的惊群问题
进程间如何传递文件描述符呢

如何查看内存空间？如何查看磁盘空间？(free; df -h)
如何查看进程？(ps aux)




IO模型——IO多路复用机制
答：预备知识介绍：

IO模型有4中：同步阻塞IO、同步非阻塞IO、异步阻塞IO、异步非阻塞IO；IO多路复用属于IO模型中的异步阻塞IO模型，在服务器高性能IO构建中常常用到。

上述几个模型原理如下图：

同步阻塞IO：                                                           同步非阻塞IO：                                            IO多路复用（异步阻塞IO）：



如上：同步异步是表示服务端的，阻塞非阻塞是表示用户端，所以可解释为什么IO多路复用（异步阻塞）常用于服务器端的原因；

文件描述符（FD，又叫文件句柄）：描述符就是一个数字，它指向内核中的一个结构体(文件路径，数据区等属性)。具体来源：Linux内核将所有外部设备都看作一个文件来操作，对文件的操作都会调用内核提供的系统命令，返回一个fd(文件描述符)。



下面开始介绍IO多路复用：

（1）I/O多路复用技术通过把多个I/O的阻塞复用到同一个select、poll或epoll的阻塞上，从而使得系统在单线程的情况下可以同时处理多个客户端请求。与传统的多线程/多进程模型比，I/O多路复用的最大优势是系统开销小，系统不需要创建新的额外进程或者线程。

（2）select，poll，epoll本质上都是同步I/O，因为他们都需要在读写事件就绪后自己负责进行读写，也就是说这个读写过程是阻塞的，而异步I/O则无需自己负责进行读写，异步I/O的实现会负责把数据从内核拷贝到用户空间。

（3）I/O多路复用的主要应用场景如下：

服务器需要同时处理多个处于监听状态或者多个连接状态的套接字；
服务器需要同时处理多种网络协议的套接字；

（4）目前支持I/O多路复用的系统调用有 select，poll，epoll，epoll与select的原理比较类似，但epoll作了很多重大改进，现总结如下：

①支持一个进程打开的文件句柄FD个数不受限制（为什么select的句柄数量受限制：select使用位域的方式来传递关心的文件描述符，因为位域就有最大长度，在Linux下是1024，所以有数量限制）；

②I/O效率不会随着FD数目的增加而线性下降；

③epoll的API更加简单；

（5）三种接口调用介绍：

①select函数调用格式：

#include <sys/select.h>
#include <sys/time.h>
int select(int maxfdp1,fd_set *readset,fd_set *writeset,fd_set *exceptset,const struct timeval *timeout)
//返回值：就绪描述符的数目，超时返回0，出错返回-1
②poll函数调用格式：

# include <poll.h>
int poll ( struct pollfd * fds, unsigned int nfds, int timeout);
③epoll函数格式（操作过程包括三个函数）：

#include <sys/epoll.h>
int epoll_create(int size);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
（6）作用：一定程度上替代多线程/多进程，减少资源占用，保证系统运行的高效率；




进程间的通信方式

     管道、有名管道、信号、共享内存、消息队列、信号量、套接字、文件.



假如开辟了一块共享内存，如何通知使用共享内存的进程
共享内存如何创建的/在哪创建的？








 














# DNS的查询方式；(递归和迭代)
# HTTP与HTTPS的区别；(加密与否)
# HTTPS如何实现加密传输；(非对称加密机制)
# HTTPS的认证过程；
# TTL指的是什么？(Time To Live，生存时间，也是跳数限制)
# ARP协议；
# traceroute的过程；
# TCP、UDP的区别；
# TCP如何实现可靠连接；
# socket编程；
# 在浏览器中输入一个网址，服务器是如何找到你的主机的
# TCP连接断开时为什么需要一个timewait状态

TCP三次握手四次挥手状态图，对应的POSIX API，为什么要三次握手，两次可以吗？
TIME_WAIT的作用
TCP和UDP区别，TCP如何保证可靠性，对方是否存活(心跳检测)
流量控制，拥塞控制
SYN Flood攻击
HTTP状态码
Libevent如何处理IO事件，信号事件，和定时事件

11. nagle 算法介绍， nagle 算法有什么问题（说了 TCP粘包问题，面试官补充了一下时延问题）

TCP流量控制发送端和接收端的窗口大小是怎么确定的

UDP一对多怎么实现呢？

TCP三次握手为什么不可以用两次？我扯了扯可能是安全问题，又浪费了十多分钟

作者：bieliwoen
链接：https://www.nowcoder.com/discuss/213405
来源：牛客网

TCP一次能多少数据？说了滑动窗口和拥塞窗口的限制。。。为什么要慢启动？拥塞避免窗口的阀值怎么确定？
滑动窗口怎么移动？

说说快速重传和快速恢复。

客户端连接服务端，服务端创建socket失败，有哪些原因，怎么解决？瞎扯。。。面试从这里就开始崩盘了。。。

伪代码写select之后的操作。。。大部分都忘了。。。

作者：瓜大疯
链接：https://www.nowcoder.com/discuss/211943
来源：牛客网

2.http服务，接收方如何判断数据接受完毕？
3.浏览器输入 www.baidu.com的过程？
4.分别说说ARP、ICMP、TCP协议的理解？
5.路由器属哪一层？IP包经过路由器后发生了什么变化？

怎么设计一个udp让他像tcp一样可靠，我回答就像tcp一样加入确认应答balabala，


TCP流量控制和拥塞控制的区别

TCP如何保证可靠性
5、在TCP连接中，如果突然有多个连接，服务端会发生什么（我说的SYN Flood，应该会缓冲池慢了而暂时阻塞，但是面试官否认了，我当时有点懵）
6、应用层对应的协议

第一题是BST找第K大值，第二题是行和列都是有序的二维矩阵找一个target值


OSI七层模型
ARP协议
TCP和UDP的区别
ICMP协议
HTTP和HTTPS的区别
非对称加密与对称加密
证书和公钥的关系

数据链路层的协议

tcp四次挥手，为什么四次挥手，为什么先断开的一方需要time_wait
感觉每次面试都有问的问题

作者：大胖熊666
链接：https://www.nowcoder.com/discuss/230192
来源：牛客网

3、阻塞和非阻塞的区别，如果阻塞模式下开多线程，那么它的性能与非阻塞对比
4、vector扩容机制，一个vector初始容量为1。扩到N的时间复杂度，估算往一个 vector 插入N个元素的时间复杂度。
5、vector要想释放一段内存用什么，resize会不会释放内存
6、new和malloc 的区别，要想new不抛出异常怎么办。
7、new[]不配合delete[]使用会发生什么情况，为什么

k路链表归并



IO模型——IO多路复用机制

IO模型有4中：同步阻塞IO、同步非阻塞IO、异步阻塞IO、异步非阻塞IO；IO多路复用属于IO模型中的异步阻塞IO模型，在服务器高性能IO构建中常常用到。

上述几个模型原理如下图：

同步阻塞IO：                                                           同步非阻塞IO：                                            IO多路复用（异步阻塞IO）：



如上：同步异步是表示服务端的，阻塞非阻塞是表示用户端，所以可解释为什么IO多路复用（异步阻塞）常用于服务器端的原因；

文件描述符（FD，又叫文件句柄）：描述符就是一个数字，它指向内核中的一个结构体(文件路径，数据区等属性)。具体来源：Linux内核将所有外部设备都看作一个文件来操作，对文件的操作都会调用内核提供的系统命令，返回一个fd(文件描述符)。



下面开始介绍IO多路复用：

（1）I/O多路复用技术通过把多个I/O的阻塞复用到同一个select、poll或epoll的阻塞上，从而使得系统在单线程的情况下可以同时处理多个客户端请求。与传统的多线程/多进程模型比，I/O多路复用的最大优势是系统开销小，系统不需要创建新的额外进程或者线程。

（2）select，poll，epoll本质上都是同步I/O，因为他们都需要在读写事件就绪后自己负责进行读写，也就是说这个读写过程是阻塞的，而异步I/O则无需自己负责进行读写，异步I/O的实现会负责把数据从内核拷贝到用户空间。

（3）I/O多路复用的主要应用场景如下：

服务器需要同时处理多个处于监听状态或者多个连接状态的套接字；
服务器需要同时处理多种网络协议的套接字；

（4）目前支持I/O多路复用的系统调用有 select，poll，epoll，epoll与select的原理比较类似，但epoll作了很多重大改进，现总结如下：

①支持一个进程打开的文件句柄FD个数不受限制（为什么select的句柄数量受限制：select使用位域的方式来传递关心的文件描述符，因为位域就有最大长度，在Linux下是1024，所以有数量限制）；

②I/O效率不会随着FD数目的增加而线性下降；

③epoll的API更加简单；

（5）三种接口调用介绍：

①select函数调用格式：

#include <sys/select.h>
#include <sys/time.h>
int select(int maxfdp1,fd_set *readset,fd_set *writeset,fd_set *exceptset,const struct timeval *timeout)
//返回值：就绪描述符的数目，超时返回0，出错返回-1
②poll函数调用格式：

# include <poll.h>
int poll ( struct pollfd * fds, unsigned int nfds, int timeout);
③epoll函数格式（操作过程包括三个函数）：

#include <sys/epoll.h>
int epoll_create(int size);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
（6）作用：一定程度上替代多线程/多进程，减少资源占用，保证系统运行的高效率；




网络分层

为什么TCP/IP去除了表示层和会话层？

先有了tcpip协议栈的实现，并应用在Unix系统中。之后才有了osi七层模型，才提出的会话层，表示层等概念。
七层模型是专家讨论出的理想模型，tcpip实现模型流行起来后，已有的系统就很难在去修改模型了。但是tcpip确实是缺失了那几层，所以后来就出现了各种各样的"补丁"协议来弥补空缺，例如ssl可以看作是表示层。IPsec也可以认为是对tcpip的一种补充。

应用层

DNS的查询方式

(递归和迭代)

HTTP与HTTPS的区别；(加密与否)
HTTPS如何实现加密传输；(非对称加密机制)
HTTPS的认证过程；
TTL指的是什么？(Time To Live，生存时间，也是跳数限制)
ARP协议；
traceroute的过程；

传输层


TCP与UDP的区别；(TCP实现了可靠传输；UDP不保证可靠传输；)
TCP如何实现可靠传输；(超时重传)
TCP的发送窗口大小如何确定？(拥塞避免)


web页面请求过程：在浏览器中输入一个网址到获得一个页面，这个过程中有用到哪些协议？(DNS + HTTP + TCP + IP + ARP；这个问题基本上可以将所有的网络协议串起来，是一个很好的问题，值得注意)
HTTP报文格式；
访问一个网址和提交一段代码到网上有何区别？(GET和POST的区别)


MSS和MTU的区别与联系

tcp为什么要三次握手，tcp为什么可靠。
为什么不能两次握手：（防止已失效的连接请求又传送到服务器端，因而产生错误）
假设改为两次握手，client端发送的一个连接请求在服务器滞留了，这个连接请求是无效的，client已经是closed的状态了，而服务器认为client想要建立
一个新的连接，于是向client发送确认报文段，而client端是closed状态，无论收到什么报文都会丢弃。而如果是两次握手的话，此时就已经建立连接了。
服务器此时会一直等到client端发来数据，这样就浪费掉很多server端的资源。
（校注：此时因为client没有发起建立连接请求，所以client处于CLOSED状态，接受到任何包都会丢弃，谢希仁举的例子就是这种场景。但是如果服务器发送对这个延误的旧连接报文的确认的同时，客户端调用connect函数发起了连接，就会使客户端进入SYN_SEND状态，当服务器那个对延误旧连接报文的确认传到客户端时，因为客户端已经处于SYN_SEND状态，所以就会使客户端进入ESTABLISHED状态，此时服务器端反而丢弃了这个重复的通过connect函数发送的SYN包，见第三个图。而连接建立之后，发送包由于SEQ是以被丢弃的SYN包的序号为准，而服务器接收序号是以那个延误旧连接SYN报文序号为准，导致服务器丢弃后续发送的数据包）
三次握手的最主要目的是保证连接是双工的，可靠更多的是通过重传机制来保证的。
TCP可靠传输的实现：
TCP 连接的每一端都必须设有两个窗口——一个发送窗口和一个接收窗口。TCP 的可靠传输机制用字节的序号进行控制。TCP 所有的确认都是基于序号而不是基于报文段。
发送过的数据未收到确认之前必须保留，以便超时重传时使用。发送窗口没收到确认不动，和收到新的确认后前移。
发送缓存用来暂时存放： 发送应用程序传送给发送方 TCP 准备发送的数据；TCP 已发送出但尚未收到确认的数据。
接收缓存用来暂时存放：按序到达的、但尚未被接收应用程序读取的数据； 不按序到达的数据。
必须强调三点：
1>   A 的发送窗口并不总是和 B 的接收窗口一样大（因为有一定的时间滞后）。
2>   TCP 标准没有规定对不按序到达的数据应如何处理。通常是先临时存放在接收窗口中，等到字节流中所缺少的字节收到后，再按序交付上层的应用进程。
3>   TCP 要求接收方必须有累积确认的功能，这样可以减小传输开销（累积确认：一般地讲，如果发送方发了包1，包2，包3，包4；接受方成功收到包1，包2，包3。
那么接受方可以发回一个确认包，序号为4(4表示期望下一个收到的包的序号；当然你约定好用3表示也可以)，那么发送方就知道包1到包3都发送接收成功，必要时重发包4。一个确认包确认了累积到某一序号的所有包。而不是对没个序号都发确认包。）
•  TCP报文格式

（1）序号：Seq序号，占32位，用来标识从TCP源端向目的端发送的字节流，发起方发送数据时对此进行标记。
（2）确认序号：Ack序号，占32位，只有ACK标志位为1时，确认序号字段才有效，Ack=Seq+1。
（3）标志位：共6个，即URG、ACK、PSH、RST、SYN、FIN等，具体含义如下：
（A）URG：紧急指针（urgent pointer）有效。
（B）ACK：确认序号有效。
（C）PSH：接收方应该尽快将这个报文交给应用层。
（D）RST：重置连接。
（E）SYN：发起一个新连接。
（F）FIN：释放一个连接。
需要注意的是：
（A）不要将确认序号Ack与标志位中的ACK搞混了。
（B）确认方Ack=发起方Req+1，两端配对。
•  三次握手
TCP三次即建立TCP连接，指建立一个TCP连接时，需要客户端服务端总共发送3 个包以确认连接的建立。在socket编程中，这一过程中由客户端执行connect来触发，流程如下：

（1）第一次握手：Client将标志位SYN置为1（表示要发起一个连接），随机产生一个值seq=J，并将该数据包发送给Server，Client进入SYN_SENT状态，等待Server确认。
（2）第二次握手：Server收到数据包后由标志位SYN=1知道Client请求建立连接，Server将标志位SYN和ACK都置为1，ack=J+1，随机产生一个值seq=K，并将该数据包发送给Client以确认连接请求，Server进入SYN_RCVD状态。
（3）第三次握手：Client收到确认后，检查ack是否为J+1，ACK是否为1，如果正确则将标志位ACK置为1，ack=K+1，并将该数据包发送给Server，Server检查ack是否为K+1，ACK是否为1，如果正确则连接建立成功，Client和Server进入ESTABLISHED状态，完成三次握手，随后Client与Server之间可以开始传输数据了。

SYN攻击：
在三次握手过程中，Server发送SYN-ACK之后，收到Client的ACK之前的TCP连接称为半连接（half-open connect），此时Server处于SYN_RCVD状态，当收到ACK后，Server转入ESTABLISHED状态。SYN攻击就是Client在短时间内伪造大量不存在的IP地址，并向Server不断地发送SYN包，Server回复确认包，并等待Client的确认，由于源地址是不存在的，因此，Server需要不断重发直至超时，这些伪造的SYN包将产时间占用未连接队列，导致正常的SYN请求因为队列满而被丢弃，从而引起网络堵塞甚至系统瘫痪。SYN攻击时一种典型的DDOS攻击，检测SYN攻击的方式非常简单，即当Server上有大量半连接状态且源IP地址是随机的，则可以断定遭到SYN攻击了，使用如下命令可以让之现行：
#netstat -nap | grep SYN_RECV
ddos攻击：
分布式拒绝服务(DDoS:Distributed Denial of Service)攻击指借助于客户/服务器技术，将多个计算机联合起来作为攻击平台，对一个或多个目标发动DDoS攻击，从而成倍地提高拒绝服务攻击的威力。通常，攻击者使用一个偷窃帐号将DDoS主控程序安装在一个计算机上，在一个设定的时间主控程序将与大量代理程序通讯，代理程序已经被安装在网络上的许多计算机上。代理程序收到指令时就发动攻击。利用客户/服务器技术，主控程序能在几秒钟内激活成百上千次代理程序的运行。

•  四次挥手
所谓四次挥手（Four-Way Wavehand）即终止TCP连接，就是指断开一个TCP连接时，需要客户端和服务端总共发送4个包以确认连接的断开。在socket编程中，这一过程由客户端或服务端任一方执行close来触发，整个流程如下图所示：

由于TCP连接时全双工的，因此，每个方向都必须要单独进行关闭，这一原则是当一方完成数据发送任务后，发送一个FIN来终止这一方向的连接，收到一个FIN只是意味着这一方向上没有数据流动了，即不会再收到数据了，但是在这个TCP连接上仍然能够发送数据，直到这一方向也发送了FIN。首先进行关闭的一方将执行主动关闭，而另一方则执行被动关闭，上图描述的即是如此。
（1）第一次挥手：Client发送一个FIN，用来关闭Client到Server的数据传送，Client进入FIN_WAIT_1状态。
（2）第二次挥手：Server收到FIN后，发送一个ACK给Client，确认序号为收到序号+1（与SYN相同，一个FIN占用一个序号），Server进入CLOSE_WAIT状态。
（3）第三次挥手：Server发送一个FIN，用来关闭Server到Client的数据传送，Server进入LAST_ACK状态。
（4）第四次挥手：Client收到FIN后，Client进入TIME_WAIT状态，接着发送一个ACK给Server，确认序号为收到序号+1，Server进入CLOSED状态，完成四次挥手。
为什么需要TIME_WAIT
TIMEWAIT状态也称为2MSL等待状态。
1）为实现TCP这种全双工（full-duplex）连接的可靠释放
这样可让TCP再次发送最后的ACK以防这个ACK丢失(另一端超时并重发最后的FIN)。这种2MSL等待的另一个结果是这个TCP连接在2MSL等待期间，定义这个连接的插口(客户的IP地址和端口号，服务器的IP地址和端口号)不能再被使用。这个连接只能在2MSL结束后才能再被使用。
2）为使旧的数据包在网络因过期而消失
每个具体TCP实现必须选择一个报文段最大生存时间MSL(Maximum Segment Lifetime)。它是任何报文段被丢弃前在网络内的最长时间。
为什么建立连接是三次握手，而关闭连接却是四次挥手呢？
这是因为服务端在LISTEN状态下，收到建立连接请求的SYN报文后，把ACK和SYN放在一个报文里发送给客户端。而关闭连接时，当收到对方的FIN报文时，仅仅表示对方不再发送数据了但是还能接收数据，我们也未必全部数据都发送给对方了，所以我们不可以立即close，也可以发送一些数据给对方后，再发送FIN报文给对方来表示同意现在关闭连接，因此，我们的ACK和FIN一般都会分开发送。


20. TCP和UDP有什么区别
    TCP---传输控制协议,提供的是面向连接、可靠的字节流服务。
    当客户和服务器彼此交换数据前，必须先在双方之间建立一个TCP连接，之后才能传输数据。
    TCP提供超时重发，丢弃重复数据，检验数据，流量控制等功能，保证数据能从一端传到另一端。
    UDP---用户数据报协议，是一个简单的面向数据报的运输层协议。
    UDP不提供可靠性，它只是把应用程序传给IP层的数据报发送出去，但是并不能保证它们能到达目的地。
    由于UDP在传输数据报前不用在客户和服务器之间建立一个连接，且没有超时重发等机制，故而传输速度很快

21. 编写socket套接字的步骤

22. TCP三次握手和四次挥手, 以及各个状态的作用
    http://hi.baidu.com/suxinpingtao51/item/be5f71b3a907dbef4ec7fd0e?qq-pf-to=pcqq.c2c

23. HTTP协议
    http（超文本传输协议）是一个基于请求与响应模式的、无状态的、应用层的协议，常基于TCP的连接方式，
    HTTP1.1版本中给出一种持续连接的机制，绝大多数的Web开发，都是构建在HTTP协议之上的Web应用。
    TCP 和 HTTP区别： http://blog.csdn.net/lemonxuexue/article/details/4485877







强制类型转换
显式转换 cast

虽然有时不得不使用强制类型转换，但这种转换本质上是十分危险的。


命名的强制类型转换

cast-name<type>(expression)
如果type是引用类型，则结果是左值。

static_cast

const_cast



reinterpret_cast

dynamic_cast







旧式强制类型转换




# 引用与指针那些事

## 1.引用与指针

总论：

| 引用         | 指针         |
| ------------ | ------------ |
| 必须初始化   | 可以不初始化 |
| 不能为空     | 可以为空     |
| 不能更换目标 | 可以更换目标 |

> 引用必须初始化，而指针可以不初始化。

我们在定义一个引用的时候必须为其指定一个初始值，但是指针却不需要。

```c++
int &r;    //不合法，没有初始化引用
int *p;    //合法，但p为野指针，使用需要小心
```

> 引用不能为空，而指针可以为空。

由于引用不能为空，所以我们在使用引用的时候不需要测试其合法性，而在使用指针的时候需要首先判断指针是否为空指针，否则可能会引起程序崩溃。

```c++
void test_p(int* p)
{
   if(p != null_ptr)    //对p所指对象赋值时需先判断p是否为空指针
       *p = 3;
    return;
}
void test_r(int& r)
{
    r = 3;    //由于引用不能为空，所以此处无需判断r的有效性就可以对r直接赋值
    return;
}
```

> 引用不能更换目标

指针可以随时改变指向，但是引用只能指向初始化时指向的对象，无法改变。

```
int a = 1;
int b = 2;

int &r = a;    //初始化引用r指向变量a
int *p = &a;   //初始化指针p指向变量a

p = &b;        //指针p指向了变量b
r = b;         //引用r依然指向a，但a的值变成了b
```

## 2.引用

#### 左值引用

常规引用，一般表示对象的身份。

#### 右值引用

右值引用就是必须绑定到右值（一个临时对象、将要销毁的对象）的引用，一般表示对象的值。

右值引用可实现转移语义（Move Sementics）和精确传递（Perfect Forwarding），它的主要目的有两个方面：

- 消除两个对象交互时不必要的对象拷贝，节省运算存储资源，提高效率。
- 能够更简洁明确地定义泛型函数。

#### 引用折叠

- `X& &`、`X& &&`、`X&& &` 可折叠成 `X&`
- `X&& &&` 可折叠成 `X&&`

C++的引用**在减少了程序员自由度的同时提升了内存操作的安全性和语义的优美性**。比如引用强制要求必须初始化，可以让我们在使用引用的时候不用再去判断引用是否为空，让代码更加简洁优美，避免了指针满天飞的情形。除了这种场景之外引用还用于如下两个场景：

> 引用型参数

一般我们使用const reference参数作为只读形参，这种情况下既可以避免参数拷贝还可以获得与传值参数一样的调用方式。

```c++
void test(const vector<int> &data)
{
    //...
}
int main()
{
   vector<int> data{1,2,3,4,5,6,7,8};
    test(data);
}
```

> 引用型返回值

C++提供了重载运算符的功能，我们在重载某些操作符的时候，使用引用型返回值可以获得跟该操作符原来语法相同的调用方式，保持了操作符语义的一致性。一个例子就是operator []操作符，这个操作符一般需要返回一个引用对象，才能正确的被修改。

```c++
vector<int> v(10);
v[5] = 10;    //[]操作符返回引用，然后vector对应元素才能被修改
              //如果[]操作符不返回引用而是指针的话，赋值语句则需要这样写
*v[5] = 10;   //这种书写方式，完全不符合我们对[]调用的认知，容易产生误解
```

## 3.指针与引用的性能差距

指针与引用之间有没有性能差距呢？这种问题就需要进入汇编层面去看一下。我们先写一个test1函数，参数传递使用指针：

```c++
void test1(int* p)
{
    *p = 3;    //此处应该首先判断p是否为空，为了测试的需要，此处我们没加。
    return;
}
```

该代码段对应的汇编代码如下：

```c++
(gdb) disassemble 
Dump of assembler code for function test1(int*):
   0x0000000000400886 <+0>:  push   %rbp
   0x0000000000400887 <+1>:  mov    %rsp,%rbp
   0x000000000040088a <+4>:  mov    %rdi,-0x8(%rbp)
=> 0x000000000040088e <+8>:  mov    -0x8(%rbp),%rax
   0x0000000000400892 <+12>: movl   $0x3,(%rax)
   0x0000000000400898 <+18>: nop
   0x0000000000400899 <+19>: pop    %rbp
   0x000000000040089a <+20>: retq   
End of assembler dump.

```

上述代码1、2行是参数调用保存现场操作；第3行是参数传递，函数调用第一个参数一般放在rdi寄存器，此行代码把rdi寄存器值（指针p的值）写入栈中；第4行是把栈中p的值写入rax寄存器；第5行是把立即数3写入到**rax寄存器值所指向的内存**中，此处要注意(%rax)两边的括号，这个括号并并不是可有可无的，(%rax)和%rax完全是两种意义，(%rax)代表rax寄存器中值所代表地址部分的内存，即相当于C++代码中的*p，而%rax代表rax寄存器，相当于C++代码中的p值，所以汇编这里使用了(%rax)而不是%rax。

我们再写出参数传递使用引用的C++代码段test2：

```c++
void test2(int& r)
{
    r = 3;    //赋值前无需判断reference是否为空
    return;
}
```

这段代码对应的汇编代码如下：

```c++
(gdb) disassemble 
Dump of assembler code for function test2(int&):
   0x000000000040089b <+0>:  push   %rbp
   0x000000000040089c <+1>:  mov    %rsp,%rbp
   0x000000000040089f <+4>:  mov    %rdi,-0x8(%rbp)
=> 0x00000000004008a3 <+8>:  mov    -0x8(%rbp),%rax
   0x00000000004008a7 <+12>: movl   $0x3,(%rax)
   0x00000000004008ad <+18>: nop
   0x00000000004008ae <+19>: pop    %rbp
   0x00000000004008af <+20>: retq   
End of assembler dump.

```

我们发现test2对应的汇编代码和test1对应的汇编代码完全相同，这说明C++编译器在编译程序的时候将指针和引用编译成了完全一样的机器码。所以C++中的引用只是C++对指针操作的一个“语法糖”，在底层实现时C++编译器实现这两种操作的方法完全相同。

## 3.总结

C++中引入了引用操作，在对引用的使用加了更多限制条件的情况下，保证了引用使用的安全性和便捷性，还可以保持代码的优雅性。在适合的情况使用适合的操作，引用的使用可以一定程度避免“指针满天飞”的情况，对于提升程序稳定性也有一定的积极意义。最后，指针与引用底层实现都是一样的，不用担心两者的性能差距。



一个C++源文件从文本到可执行文件经历的过程

对于C/C++编写的程序，从源代码到可执行文件，一般经过下面四个步骤：

1).预处理，产生.i文件

2).编译，产生汇编文件(.s文件)

3).汇编，产生目标文件(.o或.obj文件)

4).链接,产生可执行文件(.out或.exe文件)


项目发布Debug和Release版的区别

 一、Debug和Release的区别

　　Debug：调试版本，包含调试信息，所以容量比Release大很多，并且不进行任何优化（优化会使调试复杂化，因为源代码和生成的指令间关系会更复杂），便于程序员调试。Debug模式下生成两个文件，除了.exe或.dll文件外，还有一个.pdb文件，该文件记录了代码中断点等调试信息 
　　Release：发布版本，不对源代码进行调试，编译时对应用程序的速度进行优化，使得程序在代码大小和运行速度上都是最优的。（调试信息可在单独的PDB文件中生成）。Release模式下生成一个文件.exe或.dll文件
 
二、Obj文件夹的作用
　　obj目录中也有debug和release两个子目录，obj目录是项目生成dll的源目录，然后将生成好的dll复制到bin目录下。obj用于存放编译过程中生成的中间临时文件。在.Net中，编译时分模块进行的，每个模块的编译结果都保存在obj目录下，最后会合并为一个.exe或则.dll文件保存到bin目录下。
　　因为每次编译都是增量编译，也就是只重新编译改变了的模块，所以这个obj目录的作用就是保存这些小块的编译结果，加快编译速度。
 
三、Debug 和 Release 编译方式的本质区别

Debug 通常称为调试版本，它包含调试信息，并且不作任何优化，便于程序员调试程序。Release 称为发布版本，它往往是进行了各种优化，使得程序在代码大小和运行速度上都是最优的，以便用户很好地使用。
Debug 和 Release 的真正秘密，在于一组编译选项。下面列出了分别针对二者的选项（当然除此之外还有其他一些，如/Fd /Fo，但区别并不重要，通常他们也不会引起 Release 版错误，在此不讨论）

Debug 版本：
/MDd /MLd 或 /MTd 使用 Debug runtime library(调试版本的运行时刻函数库)
/Od 关闭优化开关
/D "_DEBUG" 相当于 #define _DEBUG,打开编译调试代码开关(主要针对assert函数)
/ZI 创建 Edit and continue(编辑继续)数据库，这样在调试过程中如果修改了源代码不需重新编译
/GZ 可以帮助捕获内存错误
/Gm 打开最小化重链接开关，减少链接时间

Release 版本：
/MD /ML 或 /MT 使用发布版本的运行时刻函数库
/O1 或 /O2 优化开关，使程序最小或最快
/D "NDEBUG" 关闭条件编译调试代码开关(即不编译assert函数)
/GF 合并重复的字符串，并将字符串常量放到只读内存，防止被修改

实际上，Debug 和 Release 并没有本质的界限，它们只是一组编译选项的集合，编译器只是按照预定的选项行动。事实上，我们甚至可以修改这些选项，从而得到优化过的调试版本或是带跟踪语句的发布版本。


main函数执行之前都做了什么

先来理解以下代码：

#include <stdio.h>
 void init(void) __attribute__((constructor));
 void init(void){
     printf(“before enter main!\n”);
 }
 void exit_func(void){
     printf(“after leave main!\n”);
 }
 int main(void){
     int *m = malloc(5, sizeof(int));
     atexit(exit_fun);
     printf(“hello world!\n”);
 }
 
 before enter main!
 hello world!
 after leave main!
 

运行时库概述

任何一个C/C++程序，它的背后都有一套庞大的代码来进行支撑，以使得该程序能够正常运行。这套代码至少包括入口函数，及其依赖的函数所构成的函数集合。当然，它还应该包括各种标准函数（如字符串，数学运算等）的实现。

一般的程序运行过程如下：
1.操作系统创建进程后，把控制权交给程序的入口函数（gcc –e (_startEntryPoint)）,   这个函数往往是运行时库的某个入口函数。  glibc 的入口函数是_start,msvc(vc6.0)是mainCRTStartup。
2. 入口函数对运行库和程序运行环境进行初始化，包括堆，I/O，线程，全局变量构造等。
3. 调用main函数，正式开始执行程序主体。
4. 执行main完毕，返回入口函数，进行清理工作，包括全局变量析构，堆销毁，关闭I/O等，然后进行系统调用j结束进程

运行时库主要功能模块
1.启动与退出，包括入口函数及其依赖函数
2.标准函数，C语言标准规定的标准函数
3.I/O，I/O功能的封装和实现，如提供printf
4.堆，堆的封装和实现
5.调试支持等

程序详细运行过程

以下分析默认为WINDOWS静态链接过程。
1. 程序执行前装载器把用户参数和环境变量压入栈，接着操作系统把控制权交给mainCRTStartup入口函数。
用户的参数：对应 int main(int argc,char *argv[])
环境变量：系统公用数据，系统搜索路径等等。
程序需要获取用户参数和环境变量均是 从栈上获取，需要理解栈帧的概念。

2. 初始化和OS版本相关的全局变量

3. 初始化堆，每个进程都有属于自己的堆。它是一次性从系统中申请一块比较大的虚拟空间（实际需要时（如malloc）才会映射到物理页），以后在进程中由库的堆管理算法来维护这个堆。当堆不够用时再继续申请一块大的虚拟空间继续分配。 可见，并非程序每次malloc都会调用系统API（API调用比较耗时，涉及到用户态到内核态的上下文切换），效率比较高.

4. I/O初始化，继承父进程打开文件表。可见，子进程是可以访问父进程打开的文件。 如果父进程没有打开标准的输入输出，该进程会初始化标准输入输出。即初始化以下指针变量： stdin,stdout,stderr. 它们都是FILE类型指针。 在linux和windows中，打开文件对应于操作一个内核对象，其处于内核态，因此用户态是不能直接操作该内核对象的。用户只能操作与内核对象相关联的FILE结构指针。

5. 获取命令行参数和环境变量

6.  初始化C库的一些数据

7. 全局变量构造，如各个全局类对象的构造函数调用和标记 __attribute__((constructor))属性的各个函数。它们都应该在进入main前进行调用。

8. 注册析构函数
为了支持C++类的析构函数，和标记 __attribute__((deconstructor))属性的各个函数在main之后会被调用，而且是按构造的相反顺序进行调用，同样需要编译器和链接器以及运行时库的支持，原理跟构造相仿。只是为了逆序，使用了atexit注册各个虚构函数，注册时在链表头插入链接，main退出以后也从链表头开始获取链表函数，并进行调用。

9. 执行函数主体。
调用main函数执行，等待返回。 在这里可以用到之前已经初始化的各种资源，如I/O, 堆申请释放等等

10. 调用析构函数

11. 释放堆
12. 释放其他资源

C 语言运行库（CRT）

大致包含如下功能：
启动与退出：包括入口函数及入口函数所依赖的其他函数等。
标准函数：有 C 语言标准规定的C语言标准库所拥有的函数实现。
I/O：I/O 功能的封装和实现。
堆：堆的封装和实现。
语言实现：语言中一些特殊功能的实现。
调试：实现调试功能的代码。

C语言标准库（ANSI C）
包含：
标准输入输出（stdio.h）
文件操作（stdio.h）
字符操作（ctype.h）
字符串操作（string.h）
数学函数（math.h）
资源管理（stdlib.h）
格式转换（stdlib.h）
时间/日期（time.h）
断言（assert.h）
各种类型上的常数（limits.h & float.h）
变长参数（stdarg.h）
非局部跳转（setjmp.h）

平时如何调试程序？断点的原理是什么？

比较简单的程序的话，会通过输出一些重要变量来进行比较，然后根据代码流程查看错误的变量值是如何产生的。
比较复杂的大型程序，会通过打断点的方式。平时主要使用的IDE为vs xcode 和clion,它们也都集成了调试器，可以在重要位置处设置断点，来逐步去执行查看问题。如果是多进程程序的话，还需要进行进程附加；需要注意的是，如果程序是时间敏感的话，断点方式会影响程序的正确流程。
通过查看日志的方式，大型程序一般都使用日志库实现日志功能，通过跟踪日志来进行调试。

断点原理：
1)获取对进程的调试权限
调试器如果要调试进程，就需要获取对应进程的访问权限。而调试器获取进程调试权限的方式主要有两种：
通过创建可调试进程来获取对进程的调试权限
通过附加方式获取进程可调试权限
上述两种方式均是通过操作系统提供的进程调试接口实现
2)中断
对于调试器来说，最重要的功能就是可以在指定地址处设置中断，以使得我们可以更好的控制进程的行为，根据需求快速定位进程代码中的主要功能点。
中断重要有三种类型：软中断，硬中断，内存中断。

软中断是通过修改指定地址处指令执行代码的方式实现。
假设我们想要在 0x0041397B 处设置中断

则调试器会将该位置的指令代码0x8BC7的第一个字节0x8B修改为0xCC( int 3中断的机器代码)，具体如下，

并存储原来的指令代码0x8B。一旦指令执行到0x0041397B位置时，即会执行机器指令0xCC引发一个int 3中断。而调试器则根据中断的类型来做出相应的处理。
另外，要注意，这种中断实现方式修改了内存空间的代码，对于某些恶意病毒来说，可能会通过对内存空间的代码进行完整性校验来检查设置软中断的行为，以阻止病毒分析人员对病毒的分析，加大分析难度。

硬中断的实现方式则与调试寄存器DR0~7有关，也即是说硬中断的实现不影响内存空间的代码完整性。因为寄存器的值和执行流程相关，而线程才是代码执行的主体，所以硬中断的实现虽然不修改进程空间代码，但是需要修改线程执行的上下文信息。但是注意，因为一个进程可以有多个线程，所以当设置一个硬中断时，要设置进程中所有线程执行的上下文信息

内存中断的实现方式和系统对内存页的保护机制有关。其实现的原理是通过设置内存页的访问权限来使得对内存的某些访问会引发冲突，调试器捕获这些冲突并执行相应的操作。
以Windows系统为例，操作系统对一个页(操作系统分配内存的最小单位)的权限设置包括：
可执行页 Page execution：当进程尝试对该页进程读写操作时会引发一个访问异常。
可读页 Page read：当进程尝试对该页进程执行和写操作时会引发一个访问异常。
可写页 Page write：当进程尝试对该页进程执行和读操作时会引发一个访问异常。
守护页 Guard page: 进程对该页的任何访问都会引发一个异常，之后，该页变为普通页。
也即是说，通过对指定内存设置不同的访问权限，即可对内存设置不同类型的断点(内存访问断点、内存读断点、内存写断点等)。

调试器的实现都是通过对进程或线程中某些数据的修改实现对进程执行过程中的控制，或者说劫持。



为什么构造函数不能是虚函数？

从vptr角度解释
虚函数的调用是通过虚函数表来查找的，而虚函数表由类的实例化对象的vptr指针指向，该指针存放在对象的内部空间中，需要调用构造函数完成初始化。如果构造函数是虚函数，那么调用构造函数就需要去找vptr，但此时vptr还没有初始化！

从多态角度解释
1.虚函数主要是实现多态，在运行时才可以明确调用对象，根据传入的对象类型来调用函数;
2.构造函数是在创建对象时自己主动调用的，不可能通过父类的指针或者引用去调用,那使用虚函数也没有实际意义;
3.调用构造函数时还不能确定对象的真实类型（由于子类会调父类的构造函数）;
4.构造函数的作用是提供初始化，在对象生命期仅仅运行一次，不是对象的动态行为，没有必要成为虚函数


class A是一个空类，它里面有什么方法？大小是多少

要计算一个类对象的大小，要知道这么几点：

类大小是非静态数据成员的类型大小之和
若类中定义了虚函数，需要考虑到虚表指针也占用类对象的内存空间（32位机器下占用四字节）
编译器为了提高存取效率，类大小往往会被调整为系统的整数倍，和结构体中的内存对齐类似（结构体内存对齐详情戳这里为什么要进行结构体内存对齐）
类大小与类的构造函数、析构函数和其他成员函数无关。

基于以上这些，理论上空类的大小应该是0，但是通过测试发现空类的大小为0。

C++标准规定类的大小不能为0，空类的大小为1，当类中不包含非静态成员变量和虚函数时，该类对象的大小也为1.

原因如下：
类的实例化是在内存中分配一块空间，每个对象在在内存中都有独一无二的地址，空类也能实例化，而空类实例化出的对象也需要一块独立空间，所以编译器会为空类隐含加一个字节，就能保证两个不同对象的地址不同。所以空类大小为1，而不是0.

空类中真的什么都没有吗？？

并不见得，任何一个类中都有六个默认的成员函数，空类也不例外
六大默认成员函数分别是：

构造函数
拷贝构造函数
析构函数
赋值运算符重载
取地址操作符重载
被const修饰的取地址操作符重载


在C++标准中，一个类中即使不显示给出以上这六个成员函数，编译器也会自动合成，但是由于不同的编译器都会有不同程度的优化，他们不一定在任何情况下都会合成这些成员函数，若对于一个构造函数，它既没有参数，在函数内部也不进行任何操作，合成也无任何意义，因此编译器就只会在需要的时候来合成。

以构造函数为例，编译器在那些情况下才会合成默认的构造函数
有四种情况：
1.第一种
类A中有自己的默认构造函数，类B中没有，但是类B中包含了类A的对象，这种情况下，为了初始化B类中的A对象，编译器会为B类合成一个默认的构造函数。

2.第二种
若基类定义了构造函数，而派生类未定义构造函数，在创建派生类对象时，编译器会自动合成派生类的构造函数，目的是为了调用基类的构造函数。

这里顺便说一下继承体系下基类和派生类的构造函数/析构函数的调用次序：
1.先调用派生类构造函数，再调基类构造函数；但是执行顺序相反，先执行基类的，再执行派生类的，即先构造基类的所有成员，再构造派生类成员。
2.析构函数是先调派生类的，再调基类的，后构造出来的先销毁，先销毁派生类成员，再销毁基类成员(相当于栈)。

3.第三种
在虚拟继承体系中，编译器为了将虚基表指针（基类成员变量偏移量表指针）放入派生类对象的前四个字节中，会合成构造函数。（虚拟继承了解一下）

4.第四种
若基类定义了虚函数，编译器会为其派生类合成构造函数，目的是将虚表指针放入派生类对象的前四个字节。

拷贝构造函数
是特殊的构造函数，创建对象时使用已存在的同类对象进行初始化编译器自动调用。

若未显示定义，系统会自动合成默认拷贝构造函数，它会依次拷贝原对象的成员来初始化新对象。
何时会用到拷贝构造函数？？
用一个已存在类对象来实例化另一个同类对象
作为函数参数（传值方式）
作为函数返回值(值返回方式)
深拷贝和浅拷贝

赋值运算符重载
赋值运算符函数在定义时注意几点：
1.参数最好传引用（const修饰），可以少创建一个临时变量
2.返回值也返回引用，返回值的生命周期比函数要长
返回值不能为空，有可能还会连续赋值
3.一定要检查是否是自己给自己赋值，因为接下来的操作可能会释放空间，程序出错。

赋值运算符函数若未显示定义，系统会自动合成一个默认的赋值运算符函数，一般情况下都可以使用，但在有些情况下会出错，只要涉及资源，采用系统提供的就会有问题。即所谓的深浅拷贝

取址运算符重载（&）
对该对象取地址，也就是this指针

类名* operator&()
{
    return this;
}


const修饰的取址运算符重载（&）
不能修改原对象
此时的this指针类型为 const 类名* const

const 类名* operator&()const
{
    return this;
}



vector和list有什么区别？分别在什么场景下应用？

Vector:顺序表

优点：和数组类似开辟一段连续的空间，并且支持随机访问，所以它的查找效率高其时间复杂度O(1)。
缺点：由于开辟一段连续的空间，所以插入删除会需要对数据进行移动比较麻烦，时间复杂度O（n），另外当空间不足时还需要进行扩容。

List：链表

优点：底层实现是循环双链表，当对大量数据进行插入删除时，其时间复杂度O(1)
缺点：底层没有连续的空间，只能通过指针来访问，所以查找数据需要遍历其时间复杂度O（n），没有提供[]操作符的重载。

应用场景

vector拥有一段连续的内存空间，因此支持随机访问，如果需要高效的随即访问，而不在乎插入和删除的效率，使用vector。

list拥有一段不连续的内存空间，如果需要高效的插入和删除，而不关心随机访问，则应使用list。vector和list有什么区别？分别在什么场景下应用？

Vector:顺序表

优点：和数组类似开辟一段连续的空间，并且支持随机访问，所以它的查找效率高其时间复杂度O(1)。
缺点：由于开辟一段连续的空间，所以插入删除会需要对数据进行移动比较麻烦，时间复杂度O（n），另外当空间不足时还需要进行扩容。

List：链表

优点：底层实现是循环双链表，当对大量数据进行插入删除时，其时间复杂度O(1)
缺点：底层没有连续的空间，只能通过指针来访问，所以查找数据需要遍历其时间复杂度O（n），没有提供[]操作符的重载。

应用场景

vector拥有一段连续的内存空间，因此支持随机访问，如果需要高效的随即访问，而不在乎插入和删除的效率，使用vector。

list拥有一段不连续的内存空间，如果需要高效的插入和删除，而不关心随机访问，则应使用list。




宏定义MIN

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

#include 的顺序以及尖括号和双引号的区别

1. #include的顺序的区别：

头文件的引用顺序对于程序的编译还是有一定影响的。如果要在文件a.h中声明一个在文件b.h中定义的变量，而不引用b.h。那么要在a.c文件中引用b.h文件，并且要先引用b.h，后引用a.h,否则汇报变量类型未声明错误，也就是常见的某行少个“；”符号。

2. #include尖括号和双引号的区别：

1）#include  <> ，认为该头文件是标准头文件。编译器将会在预定义的位置集查找该头文件，这些预定义的位置可以通过设置查找路径环境变量或者通过命令行选项来修改。使用的查找方式因编译器的不同而差别迥异。

2）#include ""，认为它是非系统头文件，非系统头文件的查找通常开始于源文件所在的路径。查找范围大于<>。




写一个函数，在多个程序中均有使用，只在第一次调用时执行一次，后面调用直接返回值

#include <iostream>
#include <thread>

using namespace std;

once_flag flg;

void func() {
  call_once(flg, [] { cout << "call once" << endl; });
}

int main() {
  thread t1(func);
  thread t2(func);
  thread t3(func);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}

free()一个指针两次，会出现什么问题

将一个指针释放两次确实是非常危险的行为，它可以造成任意代码执行。如果赋值为 NULL 则不会出现这个问题，释放空指针是安全的行为。

将指针设置为NULL还有另一个好处。释放指针后，该内存可通过再次调用malloc进行重新分配。如果仍然有原始指针，则可能会遇到一个错误，即在释放并破坏其他变量后尝试使用该指针，然后程序进入未知状态，并且可能发生各种不良情况。

出于两个原因，在free（）之后将指针设置为NULL是一个好主意。不过，这并不总是必要的。例如，如果指针变量在free（）之后立即超出范围，则没有太多理由将其设置为NULL。

C++的内存管理方式

在c++中内存主要分为5个存储区：

栈（Stack）：局部变量，函数参数等存储在该区，由编译器自动分配和释放.栈属于计算机系统的数据结构，进栈出栈有相应的计算机指令支持，而且分配专门的寄存器存储栈的地址，效率高，内存空间是连续的，但栈的内存空间有限。

堆(Heap)：需要程序员手动分配和释放（new,delete），属于动态分配方式。内存空间几乎没有限制，内存空间不连续，因此会产生内存碎片。操作系统有一个记录空间内存的链表，当收到内存申请时遍历链表，找到第一个空间大于申请空间的堆节点，将该节点分配给程序，并将该节点从链表中删除。一般系统会在该内存空间的首地址处记录本次分配的内存大小，用于delete释放该内存空间。

全局/静态存储区:全局变量，静态变量分配到该区，到程序结束时自动释放，包括DATA段（全局初始化区）与BSS段（全局未初始化段）。其中，初始化的全局变量和静态变量存放在DATA段，未初始化的全局变量和静态变量存放在BSS段。
BSS段特点：在程序执行前BSS段自动清零，所以未初始化的全局变量和静态变量在程序执行前已经成为0.

文字常量区：存放常量，而且不允许修改。程序结束后由系统释放。

程序代码区：存放程序的二进制代码

malloc的原理，brk系统调用干什么的，mmap呢

malloc的实现方案：

1）malloc 函数的实质是它有一个将可用的内存块连接为一个长长的列表的所谓空闲链表。

2）调用 malloc（）函数时，它沿着连接表寻找一个大到足以满足用户请求所需要的内存块。 然后，将该内存块一分为二（一块的大小与用户申请的大小相等，另一块的大小就是剩下来的字节）。 接下来，将分配给用户的那块内存存储区域传给用户，并将剩下的那块（如果有的话）返回到连接表上。

3）调用 free 函数时，它将用户释放的内存块连接到空闲链表上。

4）到最后，空闲链会被切成很多的小内存片段，如果这时用户申请一个大的内存片段， 那么空闲链表上可能没有可以满足用户要求的片段了。于是，malloc（）函数请求延时，并开始在空闲链表上检查各内存片段，对它们进行内存整理，将相邻的小空闲块合并成较大的内存块。

brk和mmap：

从操作系统角度来看，进程分配内存有两种方式，分别由两个系统调用完成：brk和mmap（不考虑共享内存）.

这两种方式分配的都是虚拟内存，没有分配物理内存。在第一次访问已分配的虚拟地址空间的时候，发生缺页中断，操作系统负责分配物理内存，然后建立虚拟内存和物理内存之间的映射关系。

在标准C库中，提供了malloc/free函数分配释放内存，这两个函数底层是由brk，mmap，munmap这些系统调用实现的。

malloc最多能开多少

限制因素：
1. Lib C库的实现
2. 操作系统
3. 硬件
4. 当前内存的使用状况。

具体不同Lib C库实现方式才是最主要的因素。
其次就是操作系统，操作系统的地址空间分布决定了用户可用的最大地址空间，比如32位Windows是用户2G+内核2G的地址空间分配方式，32位Linux是用户3G+内核1G，不同操作系统的实现方式，对malloc也是有影响的。
然后就是硬件，32位和64位的硬件限制肯定是不一样的，页表的支持情况（巨型页）也会对malloc有限制。
最后是当前内存使用情况，比如剩余内存，虚地址空间的碎片情况等等。

free()函数入参是一个void*指针，它是如何知道被指向的大小的

假设你用malloc需要申请100字节，实际是申请了104个字节。把前4字节存成该块内存的实际大小，并把前4字节后的地址返回给你。 free释放的时候会根据传入的地址向前偏移4个字节 从这4字节获取具体的内存块大小并释放。（实际上的实现很可能使用8字节做为头部：其中每四个字节分别标记大小和是否正在使用）
实际的内存管理比这个要复杂的多，但一般手段都是如上通过记录头或者叫做cookie来存储大小以及是否正在使用来确定以后到底要回收多少和是否可以复用。
内存管理比较复杂的主要原因是内存管理程序会缓存和合并已经申请的内存块并且去复用，或者申请超大的一个块，自己省着点用 ，这样不必每次都向操纵系统要

memcpy与memmove的区别

memcpy和memmove都是C语言的库函数，相比于strcpy和strncpy只能拷贝字符数组，memcpy与memmove可以拷贝其它类型的数组，但是为什么要同时提供两种方法呢？

首先来看函数原型：

void *memcpy(void *restrict s1, const void *restrict s2, size_t n);
void *memmove(void *s1, const void *s2, size_t n);

这两个函数都是将s2指向位置的n字节数据拷贝到s1指向的位置，区别就在于关键字restrict, memcpy假定两块内存区域没有数据重叠，而memmove没有这个前提条件。如果复制的两个区域存在重叠时使用memcpy，其结果是不可预知的，有可能成功也有可能失败的，所以如果使用了memcpy,程序员自身必须确保两块内存没有重叠部分。

我们来看一组示例:

正常的拷贝


正常情况下，即使内容有重叠，src的内容也可以正确地被拷贝到了dest指向的空间。

内存重叠的拷贝

这种情况下，src的地址小于dest的地址，拷贝前3个字节没问题，但是拷贝第4，5个字节时，原有的内容已经被src拷贝过来的字符覆盖了，所以已经丢失原来src的内容，这很明显就是问题所在。

memcpy的实现
一般来说，memcpy的实现非常简单，只需要顺序的循环，把字节一个一个从src拷贝到dest就行：

#include <stddef.h> /* size_t */
void *memcpy(void *dest, const void *src, size_t n)
{
    char *dp = dest;
    const char *sp = src;
    while (n--)
        *dp++ = *sp++;
    return dest;
}
memmove的实现
memmove会对拷贝的数据作检查，确保内存没有覆盖，如果发现会覆盖数据，简单的实现是调转开始拷贝的位置，从尾部开始拷贝:

#include <stddef.h> /* for size_t */
void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char *pd = dest;
    const unsigned char *ps = src;
    if (__np_anyptrlt(ps, pd))
        for (pd += n, ps += n; n--;)
            *--pd = *--ps;
    else
        while(n--)
            *pd++ = *ps++;
    return dest;
}
这里__np_anyptrlt是一个简单的宏，用于结合拷贝的长度检测dest与src的位置，如果dest和src指向同样的对象，且src比dest地址小，就需要从尾部开始拷贝。否则就和memcpy处理相同
。
但是实际在C99实现中，是将内容拷贝到临时空间，再拷贝到目标地址中：

#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for memcpy */

void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char tmp[n];
    memcpy(tmp,src,n);
    memcpy(dest,tmp,n);
    return dest;
}

由此可见memcpy的速度比memmove快一点，如果使用者可以确定内存不会重叠，则可以选用memcpy，否则memmove更安全一些。另外一个提示是第三个参数是拷贝的长度，如果你是拷贝10个double类型的数值，要写成sizeof(double)*10,而不仅仅是10。

怎么检测内存泄露，怎么定位内存泄露？

内存泄漏也称作“存储渗漏”，用动态存储分配函数动态开辟的空间，在使用完毕后未释放，结果导致一直占据该内存单元，直到程序结束。

内存泄漏形象的比喻是“操作系统可提供给所有进程的存储空间正在被某个进程榨干”，最终结果是程序运行时间越长，占用存储空间越来越多，最终用尽全部存储空间，整个系统崩溃。

内存增长过程如下：



检测方法

检查容器

在实际项目中，程序运行过程内存消耗不断增加，并不一定是内存泄露造成的。如果代码量并不是特别大，应该先通读程序，查找代码逻辑上是否造成内存问题，特别是STL容器是否clear。

在多线程中，部分容器经常作为全局变量使用，建议仔细检查相关容器是否需要clear。可以使用.size()函数来检查容器大小，打印或写入日志，查看大小是否持续增加。
map<int, int> Intmap;
std::cout << Intmap.size();

检查new、malloc

最好先不要直接使用内存工具进行对位，而是按模块阅读代码，检查所有new、malloc所分配出来的内存，是否都正确释放。

按模块检查代码的好处是能够让你自己更理解代码，特别是你维护的代码经常是由别人开发实现的。

使用库

启用内存检测

Visual Studio 调试器和 C 运行时 (CRT) 库为我们提供了检测和识别内存泄漏的有效方法
原理大致如下：内存分配要通过CRT在运行时实现，只要在分配内存和释放内存时分别做好记录，程序结束时对比分配内存和释放内存的记录就可以确定是不是有内存泄漏。

在vs中启用内存检测的方法如下：
STEP1，在程序中包括以下语句：（#include 语句必须采用下文所示顺序。如果更改了顺序，所使用的函数可能无法正常工作。）

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

通过包括 crtdbg.h，将 malloc 和 free 函数映射到它们的调试版本，即 _malloc_dbg 和 _free_dbg，这两个函数将跟踪内存分配和释放。此映射只在调试版本（在其中定义了_DEBUG）中发生。发布版本使用普通的 malloc 和 free 函数。

#define 语句将 CRT 堆函数的基版本映射到对应的“Debug”版本。并非绝对需要该语句；但如果没有该语句，内存泄漏转储包含的有用信息将较少。

STEP2，在添加了上述语句之后，可以通过在程序中包括以下语句（通常应恰好放在程序退出位置之前）来转储内存泄漏信息：

_CrtDumpMemoryLeaks();

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
 
#include <iostream>
using namespace std;
 
void GetMemory(char *p, int num)
{
    p = (char*)malloc(sizeof(char) * num);
}
 
int main(int argc,char** argv)
{
    char *str = NULL;
    GetMemory(str, 100);
    cout<<"Memory leak test!"<<endl;
    _CrtDumpMemoryLeaks();
    return 0;
}

当在调试器下运行程序时，_CrtDumpMemoryLeaks 将在“输出”窗口中显示内存泄漏信息。内存泄漏信息如下所示：
Detected memory leaks!
Dumping objects ->
C:\Users\wangwang\Desktop\ConsoleApplication\ConsoleApplication.cpp(10) : {150} normal block at 0x00A2FC80, 100 bytes long.
 Data: <                > CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD 
Object dump complete.

内存分配编号（在大括号内）
块类型（普通、客户端或 CRT）
“普通块”是由程序分配的普通内存
“客户端块”是由 MFC 程序用于需要析构函数的对象的特殊类型内存块。 MFC new 操作根据正在创建的对象的需要创建普通块或客户端块。
“CRT 块”是由 CRT 库为自己使用而分配的内存块。 CRT 库处理这些块的释放，因此不大可能在内存泄漏报告中看到这些块，除非出现严重错误（例如 CRT 库损坏）。

以字节为单位的块大小
前 16 字节的内容（亦为十六进制）。

定义了 _CRTDBG_MAP_ALLOC 时，还会显示在其中分配泄漏的内存的文件。文件名后括号中的数字（本示例中为 10）是该文件中的行号。

注意：如果程序总是在同一位置退出，调用 _CrtDumpMemoryLeaks 将非常容易。如果程序从多个位置退出，则无需在每个可能退出的位置放置对_CrtDumpMemoryLeaks 的调用，而可以在程序开始处包含以下调用：

_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

该语句在程序退出时自动调用 _CrtDumpMemoryLeaks。


对应用程序的内存状态拍快照。

CRT 库提供一种结构类型 _CrtMemState，您可用它存储内存状态的快照.
若要在给定点对内存状态拍快照，请向 _CrtMemCheckpoint 函数传递 _CrtMemState 结构。该函数用当前内存状态的快照填充此结构.
通过向 _CrtMemDumpStatistics 函数传递 _CrtMemState 结构，可以在任意点转储该结构的内容
若要确定代码中某一部分是否发生了内存泄漏，可以在该部分之前和之后对内存状态拍快照，然后使用_CrtMemDifference 比较这两个状态：


顾名思义，_CrtMemDifference 比较两个内存状态（s1 和 s2），生成这两个状态之间差异的结果（s3）。在程序的开始和结尾放置 _CrtMemCheckpoint 调用，并使用_CrtMemDifference 比较结果，是检查内存泄漏的另一种方法。如果检测到泄漏，则可以使用 _CrtMemCheckpoint 调用通过二进制搜索技术来划分程序和定位泄漏。
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
using namespace std;
_CrtMemState s1, s2, s3;
void GetMemory(char *p, int num)
{
    p = (char*)malloc(sizeof(char) * num);
}
int main(int argc,char** argv)
{
    _CrtMemCheckpoint( &s1 );
    char *str = NULL;
    GetMemory(str, 100);
    _CrtMemCheckpoint( &s2 );
    if ( _CrtMemDifference( &s3, &s1, &s2) )
        _CrtMemDumpStatistics( &s3 );
    cout<<"Memory leak test!"<<endl;
    _CrtDumpMemoryLeaks();
    return 0;
}


使用工具

Windows下：Visual Leak Detector

打开Visual C++ IDE的"工具"→"选项"→"项目和解决方案"→"VC++ 目录"，在"包含文件"中增加VLD的头文件路径"\include"路径，在"库文件"增加VLD库文件的"\lib\Win32"路径，此外动态库的"\bin\Win32"路径在安装时已经添加到环境变量里面了，若是未添加，则需要手动拷贝"\bin\Win32"下的文件到可执行文件所在的目录中（拷贝的文件有dbghelp.dll/Microsoft.DTfW.DHL.manifest/vld_x86.dll/vld.ini）。


接下来需要将VLD加入到自己的代码中。
方法很简单，只要在包含入口函数的.cpp文件中包含vld.h就可以。如果这个cpp文件中包含了stdafx.h，则将包含vld.h的语句放在stdafx.h的包含语句之后，否则放在最前面。

#include<vld.h>                 // 包含VLD的头文件
#include<stdlib.h>
#include<stdio.h>
void f()
{
    int *p = new int(0x12345678);
    printf("p=%08x, ", p);
}
int main()
{
    f();
    return 0;
}
    
注：VLD只能在Windows下使用，在包含vld.h头文件时增加预编译选项。
注：在Release模式下，不会链接VisualLeak Detector。
注：Visual LeakDetector有一些配置项，可以设置内存泄露报告的保存地（文件、调试器），拷贝"\Visual Leak Detector"路径下的vld.ini文件到执行文件所在的目录下（在IDE运行的话，则需要拷贝到工程目录下），修改以下项：
ReportFile =.\memory_leak_report.txt
ReportTo = both


Linux下：valgrind

命令：yum install valgrind进行安装。

命令：valgrind --tool=memcheck ./TestPRTI即可对TestPRTI程序进行内存检测。


如上图所示知道：
==6118== 100 bytes in 1 blocks are definitely lost in loss record 1 of 1
==6118==    at 0x4024F20: malloc (vg_replace_malloc.c:236)
==6118==    by 0x8048724: GetMemory(char*, int) (in /home/netsky/workspace/a.out)
==6118==    by 0x804874E: main (in /home/netsky/workspace/a.out)
是在main中调用了GetMemory导致的内存泄漏，GetMemory中是调用了malloc导致泄漏了100字节的内存。
详细内容请参考
http://blog.csdn.net/dndxhej/article/details/7855520
http://www.linuxidc.com/Linux/2014-10/108087.htm
   
智能指针

智能指针可以有效缓解这类问题，但并不意味着使用智能指针就不再会产生内存泄露问题。
 
 
#include <iostream>
#include <map>

namespace detail_range {
template <class T> class iterator {
public:
  using value_type = T;
  using size_type = size_t;
  value_type operator*() const { return value_; };
  iterator &operator++() {
    value_ += step_;
    ++cursor_;
    return *this;
  };
  bool operator!=(const iterator &rhs) const { return cursor_ != rhs.cursor_; };
  iterator(size_type cur_start, value_type begin_val, value_type step_val)
      : cursor_(cur_start), value_(begin_val), step_(step_val){};

private:
  size_type cursor_;
  value_type value_;
  const value_type step_;
};

template <class T> class impl {
public:
  using value_type = T;
  using reference = const value_type &;
  using const_reference = const value_type &;
  using iterator = const detail_range::iterator<value_type>;
  using const_iterator = const detail_range::iterator<value_type>;
  // 无论何时，如果使用了一个依赖于模板参数的类型时（如vector<T>），而且想使用这个类型的成员函数（如size_type）本身就是一个类型，就必须在整个名字前加上typename
  using size_type = typename iterator::size_type;

private:
  const value_type begin_;
  const value_type end_;
  const value_type step_;
  const size_type max_count_;
  size_type get_adjusted_count() const {
    if (step_ > 0 && begin_ >= end_)
      throw std::logic_error("End value must be greater than begin value.");
    else if (step_ < 0 && begin_ <= end_)
      throw std::logic_error("End value must be less than begin value.");
    size_type x = static_cast<size_type>((end_ - begin_) / step_);
    if (begin_ + (step_ * x) != end_)
      ++x;
    return x;
  }

public:
  impl(value_type begin_val, value_type end_val, value_type step_val)
      : begin_(begin_val), end_(end_val), step_(step_val),
        max_count_(get_adjusted_count()) {}
  size_type size() const { return max_count_; }
  const_iterator begin() { return {0, begin_, step_}; }
  const_iterator end() { return {max_count_, begin_, step_}; }
};
} // namespace detail_range
template <class T> detail_range::impl<T> range(T end) { return {{}, end, 1}; }
template <class T> detail_range::impl<T> range(T begin, T end) {
  return {begin, end, 1};
}
template <class T, class U>
auto range(T begin, T end, U step)
    -> detail_range::impl<decltype(begin + step)> {
  // may be narrowing
  using r_t = detail_range::impl<decltype(begin + step)>;
  return r_t(begin, end, step);
}
int main() {
  for (auto i : range(2, 10, 3))
    std::cout << i << " ";

  return 0;
}

# 多进程

JS 是单线程执行的，但是我们可以启动多个进程来执行，nodejs 中**子进程管理以及进程守候**是非常重要的知识点。

## 为何要启用多进程

第一，现在的服务器都是多核 CPU ，**启动多进程可以有效提高 CPU 利用率**，否则 CPU 资源就白白浪费了。一般会根据 CPU 的核数，启动数量相同的进程数。

第二，受到 v8 引擎的垃圾回收算法的限制，**nodejs 能使用的系统内存是受限制的**（64 位最多使用 1.4GB ，32 位最多使用 0.7GB）。**如何突破这种限制呢？—— 多进程**。因为每个进程都是一个新的 v8 实例，都有权利重新分配、调度资源。

## child_process

[child_process](http://nodejs.cn/api/child_process.html) 提供了创建子进程的方法

-   `spawn`
-   `exec`
-   `execFile`
-   `fork`

```js
var cp = require('child_process');
cp.spawn('node', ['worker.js']);
cp.exec('node worker.js', function (err, stdout, stderr) {
    // todo
});
cp.execFile('worker.js', function (err, stdout, stderr) {
    // todo
});
cp.fork('./worker.js');
```

进程之间的通讯，代码如下。跟前端`WebWorker`类似，使用`on`监听，使用`send`发送。

```js
// parent.js
var cp = require('child_process');
var n = cp.fork('./sub.js');
n.on('message', function (m) {
    console.log('PARENT got message: ' + m);
});
n.send({ hello: 'workd' });

// sub.js
process.on('message', function (m) {
    console.log('CHILD got message: ' + m);
});
process.send({ foo: 'bar' });
```

## cluster

cluster 模块允许设立一个主进程和若干个 worker 进程，由主进程监控和协调 worker 进程的运行。worker 之间采用进程间通信交换消息，**cluster 模块内置一个负载均衡器，采用 Round-robin 算法协调各个 worker 进程之间的负载**。运行时，所有新建立的链接都由主进程完成，然后主进程再把 TCP 连接分配给指定的 worker 进程。

```js
const cluster = require('cluster');
const os = require('os');
const http = require('http');

if (cluster.isMaster) {
    console.log('是主进程');
    const cpus = os.cpus(); // cpu 信息
    const cpusLength = cpus.length; // cpu 核数
    for (let i = 0; i < cpusLength; i++) {
        // fork() 方法用于新建一个 worker 进程，上下文都复制主进程。只有主进程才能调用这个方法
        // 该方法返回一个 worker 对象。
        cluster.fork();
    }
} else {
    console.log('不是主进程');
    // 运行该 demo 之后，可以运行 top 命令看下 node 的进程数量
    // 如果电脑是 4 核 CPU ，会生成 4 个子进程，另外还有 1 个主进程，一共 5 个 node 进程
    // 其中， 4 个子进程受理 http-server
    http.createServer((req, res) => {
        res.writeHead(200);
        res.end('hello world');
    }).listen(8000); // 注意，这里就不会有端口冲突的问题了！！！
}
```

维护进程健壮性，**通过 Cluster 能监听到进程退出，然后自动重启，即自动容错**，这就是进程守候。

```js
if (cluster.isMaster) {
    const num = os.cpus().length;
    console.log('Master cluster setting up ' + num + ' workers...');
    for (let i = 0; i < num; i++) {
        // 按照 CPU 核数，创建 N 个子进程
        cluster.fork();
    }
    cluster.on('online', (worker) => {
        // 监听 workder 进程上线（启动）
        console.log('worker ' + worker.process.pid + ' is online');
    });
    cluster.on('exit', (worker, code, signal) => {
        // 兼容 workder 进程退出
        console.log('worker ' + worker.process.pid + ' exited with code: ' + code + ' and signal: ' + signal);
        // 退出一个，即可立即重启一个
        console.log('starting a new workder');
        cluster.fork();
    });
}
```

示例看似简单，但是实际应用还是尽量使用成熟的工具，例如 [pm2](https://www.npmjs.com/package/pm2)，可以自己去看文档使用。

# 异步 IO

### 单线程

JS 为何非得要单线程呢，像 java 那样做成多线程的不行吗？答案是不行。

在浏览器环境中，JS 是可以操作 DOM 结构的，而 DOM 只有一份。如果两段 JS 能同时执行的话，那么它们都同时操作同一个 DOM 节点，不就发生冲突了吗？因此，**为了避免 DOM 操作的冲突，JS 不能同时执行，只能单线程执行。另外，不光 JS 是单线程，而且 JS 和浏览器渲染公用一个线程，即 JS 执行时，浏览器渲染会等待、卡顿。**

最后，单线程使得 JS 入门简单使用方便，也不会出现线程死锁、状态同步的琐碎问题，简单才容易做大、做广，**大道至简**。

### 延伸到 nodejs 中

nodejs 借用了 Chrome 浏览器中的 v8 引擎来解析 JS ，因此就将其单线程的特性保留了下来。

### 解决单线程 - 异步

上文那 100000000 次循环纯粹为了演示，实际项目中不会存在这样的场景 —— 即不会存在 CPU 计算成为速度上的瓶颈，而是网络或者文件读写成为速度上的瓶颈。

网络请求和文件读写遇到性能瓶颈这是很正常的，那对于 JS 这种单线程的语言，该怎么办呢？—— 难道执行一次网络请求，就要一直等到网络请求结束（可能花费 1s 5s 甚至 10s）之后才能继续执行下去？—— 当然不是，JS 解决这个问题就是用了异步。

好了，讲到这里讲出了异步，就不在继续了，再将就是异步的语法了。

---

## 什么是 IO

无论针对哪个语言、哪个框架、哪个操作系统，**IO 都有一个不变的特点 —— 慢** 。现在 CPU 的计算速度是非常快的，相比之下，读取硬盘和等待网络请求就变的非常缓慢。大家应该也能经常听到“IO 瓶颈”之类的词，这就表示其他地方很快，就卡在 IO 这块了，因此叫做“瓶颈”。

### 多线程 web server

PHP 也没法创建线程，即也是单线程执行的，而且 PHP 也没有 JS 一样的异步，遇到 IO 的时候只能等待完成之后再继续下一步的执行。但是 PHP 作为世界上最好的语言，肯定有解决方案。

这个解决方案不是 PHP 搞定的，而是 web server 服务器搞定的，例如 Apache 。Apache 服务器每接收一个 http 请求都会新建一个线程，在该线程这个封闭的环境下执行 PHP 代码。

-   **好处**：就是处理各个 http 请求在每个独立的线程中，上下文相互独立，不相互影响，独立性好。
-   **坏处**：就是 http 并发量大了之后，创建如此多线程内存吃不消

### 异步 IO

相比上文 Apache 多线程的方式，nodejs 针对所有 http 请求，都只有一个线程。

-   **好处**：减少线程开销，能承受更多的 http 的并发请求。著名的 nginx 也是用类似的方式做到高性能的。
-   **坏处**：所有 http 请求公用一个线程，一个上下文，一点崩溃即全线崩溃，对于程序的稳定性要求高

到这里就接上了本文一开始将的话题 —— 单线程的解决方案就是异步，IO 是瓶颈，那就用异步处理 IO，即 **异步 IO** ，即 nodejs **用单线程、异步的方式处理 IO 时能支持更多的并发请求**。

# Stream 和 Buffer

本节解决 [web 应用](./02-web-应用.md) 这一节最后的遗留问题“**这里的`data`和`end`是特定的吗？**”

```js
req.on('data', function (chunk) {
    // “一点一点”接收内容
    data += chunk.toString();
});
req.on('end', function () {});
```

另外，本文不会非常全面的介绍 Stream ，只会从 web server 的角度讲解最常用、最容易理解的 Stream 的功能。**全面了解 Stream 欢迎移步 stream-handbook 这篇经典博客**，[英文原文](https://github.com/substack/stream-handbook) [中文翻译](https://github.com/jabez128/stream-handbook)。

## 为何要“一点一点”的？

你去视频网站看电影，去下载比较大的软件安装包，或者上传电影、软件包到云盘，这些文件都是动辄几个 G 大小，对吧？然而，我们的内存、网络、硬盘读写都是有速度或者大小的限制的，不可能随便的“生吞活剥”任何大文件，于是不得不“一点一点”的。

就像我们吃东西。我们牙齿的咀嚼食物的速度是有限制的，食道和食管也是有限制的，这种情况下，我们吃任何大小的东西，都得“一点一点”的来，无论是大馒头还是小包子。

专业一点说：**一次性读取、操作大文件，内存和网络是“吃不消”的**。

---

## 如何才能“一点一点”的？

```js
req.on('data', function (chunk) {
    // “一点一点”接收内容
    data += chunk.toString();
});
req.on('end', function () {});
```

如上代码，我们已经知道了`on`是监听事件的触发，分别监听`data`和`end`两个事件。顾名思义，`data`就是有数据传递过来的事件，`end`就是结束的事件。那就可以通过这段代码回答这个问题。

如何做到“一点一点”的？—— **有数据传递过来就触发`data`事件，接收到这段数据，暂存下来，最后待数据全部传递完了触发`end`事件**。为何要在上一节先把事件机制给讲了？因为这儿就是一句事件机制才能实现。

---

## 流

上面说的这种“一点一点”的操作方式，就是“流”，Stream 。它并不是 nodejs 独有的，而是系统级别的，linux 命令的`|`就是 Stream ，因此所有 server 端语言都应该实现 Stream 的 API 。

---

## 从哪里来

数据从一个地方“流”向另一个地方，那先看看数据的来源。大家先想一下，作为一个 server 端的程序，我们一般能从哪些地方能接受到数据，或者数据能从哪些地方“流”出来？

-   http 请求，上文代码的`req`
-   控制台，标准输入 stdin
-   文件，读取文件内容

其实，所有的数据来源，都可以用 Stream 来实现。

### http req

再次回顾上文代码，看 Stream 是如何“一点一点”获取 req 数据的

```js
req.on('data', function (chunk) {
    // “一点一点”接收内容
    data += chunk.toString();
});
req.on('end', function () {});
```

### 控制台输入

nodejs 作为 web server ，基本不会用到控制台输入的功能，但是为了验证 Stream 的使用，这里就简单弄个 demo 演示一下：

```js
process.stdin.on('data', function (chunk) {
    console.log(chunk.toString());
});
```

自己去运行一下看看结果，每输入一行就会输出相同内容。这就证明每次输入之后，都会触发`data`事件，用到了 Stream 。

### 读取文件

为何使用 Stream 的道理，上文讲的很清楚了，因此在读取文件中就直接使用了，不再解释。

```js
var fs = require('fs');
var readStream = fs.createReadStream('./file1.txt'); // 读取文件的 Stream

var length = 0;
readStream.on('data', function (chunk) {
    length += chunk.toString().length;
});
readStream.on('end', function () {
    console.log(length);
});
```

如上代码，要用 Stream 那就肯定不能直接使用`fs.readFile`了，而是使用`fs.createReadStream` 。它返回的是一个 Stream 对象，通过监听其`data`和`end`来处理相关操作。

### Readable Stream

以上提到的所有能产出数据的 Stream 对象，都叫做 Readable Stream ，即可以从中读取数据的 Stream 对象。Readable Stream 对象可以监听`data` `end`事件，还有一个`pipe` API（下文会重点介绍）。你可以通过 [构造函数](http://nodejs.cn/api/stream.html#stream_implementing_a_readable_stream) 来实现一个自定义的 Readable Stream （上文三个也不过是继承、实现了这个构造函数而已）。

---

## 到哪里去

知道了从哪里来，就得知道往哪里去。还是同样的思考方法，想一下一个 server 端程序，数据通常会“流”向何方？

-   控制台，标准输出
-   文件，写入文件内容
-   http 请求，res

同理，涉及到数据“流”入的程序，也都可以用 Stream 来操作，而且要介绍一个新的 API —— **`pipe` ，它会自动将数据从 srouce 导流向 dest.**

### 控制台，标准输出

```js
process.stdin.pipe(process.stdout);
```

有了`pipe`我们就不用去关心下面代码中的`chunk`了（关于`chunk`是什么，下文会详细介绍，暂时先不管），也不用去手动监听`data` `end`事件了。

```js
process.stdin.on('data', function (chunk) {
    console.log(chunk.toString());
});
```

### 写入文件

```js
var fs = require('fs');
var readStream = fs.createReadStream('./file1.txt');
var writeStream = fs.createWriteStream('./file2.txt');
readStream.pipe(writeStream);
```

`fs.createReadStream`可以创建一个文件的可读流，对应的`fs.createWriteStream`可以创建一个可写流，通过`pipe`将他们联通。这样它们就能像上文图中那样，数据从`file1.txt`通过一根管子一点一点的流向了`file2.txt`。

这就是复制大文件的方式，**不是先读后写，而是边读边写……**

### http res

根据上面两个 demo 下面的代码应该也比较好理解了，下面的代码写的就是读取`file1.txt`内容然后通过 http 协议返回。浏览器访问`http://localhost:8080/`即可看到效果，很简单。

```js
var http = require('http');
var fs = require('fs');
function serverCallback(req, res) {
    var readStream = fs.createReadStream('./file1.txt');
    res.writeHead(200, { 'Content-type': 'text/html' });
    readStream.pipe(res);
}
http.createServer(serverCallback).listen(8080);
```

我们来将这段代码和 [web 应用](./02-web-应用.md) 这一节中的 demo ，关键代码对比一下

```js
// 之前的 demo
res.writeHead(200, { 'Content-type': 'text/html' });
res.write('hello nodejs');
res.end();

// 这里的代码
var readStream = fs.createReadStream('./file1.txt');
res.writeHead(200, { 'Content-type': 'text/html' });
readStream.pipe(res);
```

对比看来，`res.writeHead`该怎么写还是怎么写，不受影响。主要的就是之前的`res.write('hello nodejs')`换成了`readStream.pipe(res)`，之前是一次性输出内容，现在是通过 Stream 一点一点输出内容。

最后，之前的`res.end()`在当前的代码中没写，不过不会影响我们代码的运行，因为`readStream.pipe(res)`执行的时候，会自动监听到`end`事件然后执行`res.end()`，因此不需要我们手动再写一遍。

### Writable Stream

对比上文的 Readable Stream ，这里能接收数据“流”入的对象，都称为 Writable Stream 。Writable Stream 对象能作为参数传递给`pipe`方法，能接收数据。你可以通过 [构造函数](http://nodejs.cn/api/stream.html#stream_implementing_a_writable_stream) 实现自己的 Writable Stream 对象，上面讲到的三个也都是继承、实现构造函数.

### 再看`pipe`

`pipe`的使用有严格要求。例如`a.pipe(b)`时，`a`必须是一个可读流，即 Readable Stream 对象（或具有相同功能的对象），而`b`必须是一个可写流，即 Writable Stream 对象（或者有相同功能的对象），否则会报错。

---

## 有没有中转站？

数据从来源流出来，然后直奔目的地而去，这种直来直去的模式肯定是不能满足所有应用场景的。就像上文图中，水从 source 直接流向 dest 其实是没有意义的，如果中间再能加一些东西（如过滤杂质、增加微量元素、高温杀菌等）那就有意义了。

### 既可读又可写

上文提到，Readable Stream 对象是可读流，数据能从其中“流”出，Writable Stream 对象是可写流，数据能“流”向其中。**其实，还有一种类型的流，具备两者的功能 —— Duplex Stream ，双工流，既可读又可写。这样说来，Duplex Stream 对象既可以有`pipe`接口，又可以作为`pipe`方法的参数**。即：

```js
// 其中 b c d 是 Duplex Stream 对象，双工流
process.stdin.pipe(b);
b.pipe(c);
c.pipe(d);
d.pipe(process.stdout);

// 也可以写成
process.stdin.pipe(b).pipe(c).pipe(d).pipe(process.stdout);
```

如上代码，这样`b` `c` `d`其实就是一个一个的“中转站”、“过滤器”，这样数据就真的“流”起来了，像水一样。

### Duplex Stream

Duplex Stream 在实际应用不多，被举例最多的就是`gzip`压缩的功能，即读取一个文件，然后压缩保存为另一个文件。其中的`zlib.createGzip()`返回的就是一个 Duplex Stream 对象。

```js
var fs = require('fs');
var zlib = require('zlib');
var readStream = fs.createReadStream('./file1.txt');
var writeStream = fs.createWriteStream('./file1.txt.gz');
readStream.pipe(zlib.createGzip()).pipe(writeStream);
```

同理，你可以根据 [构造函数](http://nodejs.cn/api/stream.html#stream_an_example_duplex_stream) 实现自己的 Duplex Stream 对象，不再赘述。

最后，简单实现一个能在线压缩、下载的 web server

```js
var http = require('http');
var fs = require('fs');
var zlib = require('zlib');

function serverCallback(req, res) {
    var readStream = fs.createReadStream('./file1.txt');
    res.writeHead(200, { 'Content-type': 'application/x-gzip' }); // 注意这里返回的 MIME 类型
    readStream
        .pipe(zlib.createGzip()) // 一行代码搞定压缩功能
        .pipe(res);
}
http.createServer(serverCallback).listen(8080);
```

> 其实还有一种类型的流 —— Transform Stream, 不常用。

---

## 是什么在流动

上文一直说数据在流动，从哪里来，到哪里去，中间经历了什么，就是没有说这个在流动的数据，到底是什么，即代码中的`chunk`是什么？

```js
req.on('data', function (chunk) {
    // “一点一点”接收内容
    data += chunk.toString();
});
```

运行代码，打印`chunk`得到的结果是`<Buffer 61 61 61 0a 62 62 62 0 ... >`，看前面`<Buffer`就知道，它是 Buffer 类型的数据。打印`chunk instanceof Buffer`即可得到`true`。

### Buffer 是什么

Buffer 对象就是二进制在 JS 中的表述形式，即 Buffer 对象就是二进制类型的数据。上文`<Buffer 61 61 61 0a 62 62 62 0 ... >`看起来像是数组的形式，但是它却不是数组，因为它的每个元素只能是一个 16 进制的两位数（换算成 10 进制即 0-255 之间的数字），就是一个字节。

### Buffer 和字符串的关系

Buffer 是二进制，和字符串完全是两码事儿，但是他们可以相互转换 —— 前提是规定好用哪个编码规范。

```js
var str = '深入浅出nodejs';
var buf = new Buffer(str, 'utf-8');
console.log(buf); // <Buffer e6 b7 b1 e5 85 a5 e6 b5 85 e5 87 ba 6e 6f 64 65 6a 73>
console.log(buf.toString('utf-8')); // 深入浅出nodejs
```

以上代码使用`utf-8`编码对二进制和字符串进行了转换，不过其实 JS 默认就是`utf-8`编码。

### 为何流动的数据是 Buffer 类型？

计算机真正能识别的就是二进制数据。我们在程序中使用字符串、数字、数组等都是有特定的语言和环境的，是一个封闭的开发环境。代码真正执行的时候还需要这个环境做很多其他底层的工作，并不是说计算机底层就认识字符串、数字和数组。

但是“流”动的数据却可能会跑出这个环境，它会涉及到网络 IO 和文件 IO 等其他环境。即，程序从 http 请求读取数据、或者发送数据给 http 请求，得用一个两者都认识的格式才行，那就只能是二进制了。

**另外，反过来思考，不用二进制用什么呢？用字符串？那流动的数据还可能是视频和图片呢，字符串表述不了。**

### Buffer 的好处

**Buffer 能提高 http 请求的性能，《深入浅出 nodejs》书中提到，使用`stream.pipe(res)`在特定情况下，QPS 能从 2k+ 提升到 4k+**

```js
// 不使用 Stream
res.write('hello nodejs');
res.end();

// 使用 Stream
var readStream = fs.createReadStream('./file1.txt');
readStream.pipe(res);
```

---

## 总结

其实洋洋洒洒这么多，主要就是解决开头提到的“一点一点”的从 req 中接收传递来的数据，从而引申出 Stream 这个概念，并且介绍了 Stream 中比较重要的内容。以后只要遇到`data` `end`事件，或者遇到大数据内容处理，或者遇到 IO 的性能问题等，都可以考虑到 Stream 。Stream 是 server 端比较重要的概念，其基础知识必须全面了解。

**【扩展】**

其实用 Stream 读取文件内容，无法确保是一行一行读取的，但是 nodejs 有 [readline](http://nodejs.cn/api/readline.html) 可以让你轻松实现一行一行读取文件。

# 事件

本节解决上一节遗留的第一个问题 —— “`req.on`这里的`on`是特定的吗？”

```js
req.on('data', function (chunk) {});
req.on('end', function () {});
```

以上代码的格式其实应该比较熟悉的，和前端用 jQuery 绑定事件类似

```js
$('#btn1').on('click', function (event) {});
```

这两点能对应起来，就好说了。

## 观察者模式

作为程序猿多少要了解 23 种设计模式，其中观察者模式是非常重要的一个。简单说来，就是定义好监听的操作，然后等待事件的触发。前端开发中，有不少地方能体现观察者模式。最简单的例如绑定事件：

```js
$('#btn1').on('click', function (event) {
    alert(1);
});
$('#btn1').on('click', function (event) {
    alert(2);
});
```

比较复杂的例如 vue 中，修改`data`之后，会立刻出发视图重新渲染，这也是观察者模式的应用。

---

## EventEmitter 基本使用

**nodejs 中的自定义事件也是观察者模式的一种体现，而且自定义事件常见于 nodejs 的各个地方**。先看一个简单示例

```js
const EventEmitter = require('events').EventEmitter;

const emitter1 = new EventEmitter();
emitter1.on('some', () => {
    // 监听 some 事件
    console.log('some event is occured 1');
});
emitter1.on('some', () => {
    // 监听 some 事件
    console.log('some event is occured 2');
});
// 触发 some 事件
emitter1.emit('some');
```

以上代码中，先引入 nodejs 提供的`EventEmitter`构造函数，然后初始化一个实例`emitter1`。实例通过`on`可监听事件，`emit`可以触发事件，事件名称可以自定义，如`some`。

自定义事件触发的时候还可传递参数，例如

```js
const emitter = new EventEmitter();
emitter.on('sbowName', (name) => {
    console.log('event occured ', name);
});
emitter.emit('sbowName', 'zhangsan'); // emit 时候可以传递参数过去
```

还有自定义事件的异常捕获，如下形式：

```js
// 例四
const emitter1 = new EventEmitter();
emitter1.on('some', () => {
    console.log('11111');
});
emitter1.on('some', () => {
    console.log('22222');
    throw new Error('自定义错误'); // 触发过程中抛出错误
});
emitter1.on('some', () => {
    console.log('33333');
});
try {
    emitter1.emit('some');
} catch (ex) {
    console.log(ex.stack); // 可以捕获到事件执行过程中的错误
}
console.log('after emit');
```

再次回顾上一节的`req.on('data' ...`和`req.on('end', ...`，和这里是一样的，就是监听`data`和`end`两个事件。但是，上文是`EventEmitter`实例才有这样的功能，`req`并没有看到是`EventEmitter`的实例 —— 下文解惑。

---

## EventEmitter 继承

上文说到`EventEmitter`实例有`on`和`emit`接口，其实自定义 class 的实例也可以有，只不过需要继承`EventEmitter`。使用 ES6 的继承语法很容易实现

```js
// 任何构造函数都可以继承 EventEmitter 的方法 on emit
class Dog extends EventEmitter {
    constructor(name) {
        super();
        this.name = name;
    }
}
var simon = new Dog('simon');
simon.on('bark', function () {
    console.log(this.name, ' barked');
});
setInterval(() => {
    simon.emit('bark');
}, 500);
```

**`req.on('data' ...`和`req.on('end',...`中，其实`req`的构造函数已经继承了`EventEmitter`，因此`req`才会有`on`接口。**

# web 应用

## 基本使用

### 从 demo 到 http 协议

```js
var http = require('http');

function serverCallback(req, res) {
    res.writeHead(200, { 'Content-type': 'text/html' });
    res.write('<h1>hello nodejs</h1>');
    res.end();
}
http.createServer(serverCallback).listen(8080);
```

命令行运行`node demo1.js`，然后浏览器访问`http://localhost:8080/`（或者命令行`curl http://localhost:8080/`）即可看到结果。这一般是介绍 nodejs 入门的常用 demo ，熟悉 http 协议的同学都知道，这其实就是一个简单的 http 请求处理。

`req`即 request 即请求内容，`req.method`可以获取请求的方法（如`GET` `POST`等），`req.headers`可获取请求的头，如`accept` `host` `user-agent`等。

`res`即 response 即返回内容，这是 http 请求最基本的内容。`res.writeHead`定义返回的头，包括返回状态码和头信息。`res.write`定义返回的内容，最后`res.end()`表示 server 端处理请求结束。

### POST 请求

```js
var http = require('http');

function serverCallback(req, res) {
    var method = req.method.toLowerCase(); // 获取请求的方法
    if (method === 'get') {
        // 省略 3 行，上文代码示例中处理 GET 请求的代码
    }
    if (method === 'post') {
        // 接收 post 请求的内容
        var data = '';
        req.on('data', function (chunk) {
            // “一点一点”接收内容
            data += chunk.toString();
        });
        req.on('end', function () {
            // 接收完毕，将内容输出
            res.writeHead(200, { 'Content-type': 'text/html' });
            res.write(data);
            res.end();
        });
    }
}
http.createServer(serverCallback).listen(8080);
```

以上代码即可接收和处理 post 请求，代码中`req.on('data' ...`和`req.on('end', ...`这里，我们作为遗留问题，后面会详细重点的讲解，因为这些也是 nodejs 的重要知识，必须学会的。这里你看下代码注释，只要先知道，post 过来的内容是“一点一点”接收的，然后待接受完再做处理，这样即可。

可以命令行运行`curl -d "a=100&b=200" "http://localhost:8080/"`发起一个 post 请求，其中`a=100&b=200`是请求的主体内容。

### querystring 处理

以上 post 请求的内容格式是 querystring 形式的，即`key1=value1&key2=value2&key3=value3`这种，可以对代码进行改造，将这些数据结构化。

第一，代码最上面加`var querystring = require('querystring')`，引入`querystring`模块，nodejs 自带的。第二，对`req.on('end', ...`的内容做如下修改：

```js
req.on('end', function () {
    // res.writeHead(200, {'Content-type': 'text/html'})
    // res.write(data)
    data = querystring.parse(data); // 结构化为 JSON 格式
    res.writeHead(200, { 'Content-type': 'application/json' }); // 返回头，改为 JSON 格式
    res.write(JSON.stringify(data)); // res 只能输出字符串或者 Buffer 类型，因此这里只能 JSON.stringify 之后再输出
    res.end();
});
```

### post 内容为 JSON 格式

以上 post 请求的内容格式是 querystring 形式，一般用于网页的`<form>`提交，打印`req.headers['content-type']`的值是`application/x-www-form-urlencoded`，即是`<form>`提交的方式 —— 虽然是用`curl`模拟的。

而现在网页中数据提交大部分使用 ajax ，数据格式也改为了 JSON 格式，且看 nodejs 如何处理

```js
var http = require('http');

function serverCallback(req, res) {
    var method = req.method.toLowerCase();
    var contentType = req.headers['content-type'];
    if (method === 'post') {
        if (contentType === 'application/x-www-form-urlencoded') {
            // 省略 N 行
        }
        if (contentType === 'application/json') {
            var data = '';
            req.on('data', function (chunk) {
                data += chunk.toString();
            });
            req.on('end', function () {
                data = JSON.parse(data); // post 的数据为 JSON 格式，因此直接可以转换为 JS 对象
                res.writeHead(200, { 'Content-type': 'application/json' });
                res.write(JSON.stringify(data)); // res 只能输出字符串或者 Buffer 类型，因此这里只能 JSON.stringify 之后再输出
                res.end();
            });
        }
    }
}
http.createServer(serverCallback).listen(8080);
```

可以使用`curl -H "Content-type: application/json" -X POST -d '{"name":"zhangsan","age":25}' http://localhost:8080/`发起 post 请求，并且规定格式为 JSON，内容即`{"name":"zhangsan","age":25}`

### 总结

之前学习其他后端语言可能没这么费劲，接触不到这么底层的 http 协议的操作，那是因为它们都已经做好了框架的封装，并不是它们真的不需要。通过 nodejs 学习一下 http 协议的具体操作也绝对是好事一桩，不要抱怨。

另外，nodejs 虽然没有提供官方的 web 框架，但是也不会傻乎乎的在项目中直接写这么底层的代码，下文会介绍 nodejs 社区中非常成熟的 web 框架，到时候这些 http 协议的操作，也都有简单的 API 可使用。

---

## url 参数处理

通过`req.url`可以获得请求网址的完整内容，其中比较重要的就是：路由和参数。路由下文讲，先说参数的处理。

完整的 url 肯定是字符串形式的，是**非结构化**的，要想结构化需要引入 nodejs 提供的`url`模块，即`var url = require('url')`，然后通过`var urlData = url.parse(req.url)`进行结构化。

从结构化之后的数据中，通过`urlData.query`即可轻松拿到 url 参数。代码示例如下：

```js
var http = require('http');
var url = require('url');

// 处理 url 参数
function serverCallback(req, res) {
    var urlData = url.parse(req.url); // 结构化 url 内容，变为 JS 对象
    var query = urlData.query;
    console.log(query);

    // ……
}
http.createServer(serverCallback).listen(8080);
```

但是得到的 url 参数还是字符串，非结构化的，不好处理。这里引用`var querystring = require('querystring')`，然后`query = querystring.parse(query)`即可了。完整代码如下：

```js
var http = require('http');
var url = require('url');
var querystring = require('querystring');

// 处理 url 参数
function serverCallback(req, res) {
    var urlData = url.parse(req.url); // 结构化 url 内容，变为 JS 对象
    var query = urlData.query;
    query = querystring.parse(query); // 结构化 query 内容，变为 JS 对象

    res.writeHead(200, { 'Content-type': 'text/html' });
    res.write(JSON.stringify(query));
    res.end();
}
http.createServer(serverCallback).listen(8080);
```

使用`curl http://127.0.0.1:8080/?a=1&b=2`即可看到结果。

---

## 路由

通过`urlData.query`可以获取 url 参数，通过`urlData.pathname`可以获取路由，代码如下

```js
var http = require('http');
var url = require('url');

function serverCallback(req, res) {
    var urlData = url.parse(req.url);
    var pathname = urlData.pathname; // 获取 url 路由

    res.writeHead(200, { 'Content-type': 'text/html' });
    res.write(pathname);
    res.end();
}
http.createServer(serverCallback).listen(8080);
```

这里演示比较简单，但是路由处理却是 web server 中非常重要而且应用场景非常复杂的模块，而且路由如何设计也非常重要。其复杂性可以总结以下几点）：

-   **不同的 method**：如针对`/api/getname`，get 方法请求和 post 方法请求，要能区分开来
-   **不同的参数规则**：如`/api/getname/:id`表示必须有`id`参数，`/api/getname(/:id)`表示`id`可有可无
-   **层级关系**：如`/api/getname`和`/api/setname`都有`api`这个层级，要能支持两者共享流程
-   ……

一般路由的处理，都会根据一个 web 框架选择比较成熟的路由库，如 [koa-router](https://www.npmjs.com/package/koa-router) 。

## cookie

```js
var http = require('http');

function serverCallback(req, res) {
    res.writeHead(200, {
        'Content-type': 'text/html',
        // 'Set-Cookie': 'a=100'           // 设置单个值
        'Set-Cookie': ['a=100', 'b=200'], // 这是多个值
    });
    res.write('hello nodejs');
    res.end();
}
http.createServer(serverCallback).listen(8080);
```

以上代码演示了如何`Set-Cookie`，浏览器访问`http://localhost:8080/`之后，前端即存储了 cookie 。然后再次访问，看通过`req.headers.cookie`获取到 cookie 内容。

**【扩展】**

cookie 应用比较典型的场景是 —— 登录。而且，cookie 要结合 server 端的 session 才能完成整个登录的功能。

简单描述一下。前端通过登录表单将用户名和密码发送到 server 端，server 端如果验证成功，即通过`Set-Cookie`设置一个`cookie`值，如`session_id=xxxx`，并且设置 20 分钟 有效期，以及`httpOnly`（前端 JS 不能访问）。以后每次网络请求，server 端都通过判断是否有`session_id`来确定用户是否登录，以及通过`session_id`的值，对应到内存中的一些数据，这些数据即 server 端未用户存储的信息。

针对登录场景操作 cookie 和 session ，针对 web 框架有专门的工具供使用，不用自己手动写。例如 [koa-session](https://www.npmjs.com/package/koa-session)

---

## 上传文件

HTML 中普通表单和特殊表单的区别就在于是否有`<file>`标签。如果需要有`<file>`标签，就需要指定表单需求 **`enctype`为`multipart/form-data`**

```html
<form action="/upload" method="post" enctype="multipart/form-data">
    <input ... >
    <file ... >
</form>
```

nodejs 可判断`Content-type`值为`multipart/form-data`来确定是文件上传的请求。这是一个比较特殊的场景，特别是在互联网 web server 中，nodejs 用来做上传文件的接口是否合适还需论证。如果真的有地方需要用，推荐使用 [formidable](https://www.npmjs.com/package/formidable) 工具，比较简单。

---

## 框架

nodejs 的 web server 框架，比较常用的有 [express](http://www.expressjs.com.cn/) 和 [koa](https://koa.bootcss.com/) ，两者使用起来差别不是特别大 —— 因为两者的作者是同一个人（或者同一个团队）。两者的不同如下：

-   **异步**：koa 支持最新的 ES7 草案中`async/await`语法，express 还是用的 callback 形式
-   **社区**：express 社区更加完善，插件更多；koa

---

## 中间件

框架提供给开发者的便利的地方有：

-   封装`req`和`res`接口
-   封装路由处理
-   提供中间件机制

其中，中间件对于我们前端开发者来说，算是一个比较新的概念（虽然它早就存在）。简单说来，中间件就是将一次请求的处理拆分成许多小部分，分而治之。这样做完全符合开放封闭原则，可以复用也可以扩展。例如 express 的代码示例

```js
var app = express();

// 没有挂载路径的中间件，应用的每个请求都会执行该中间件
app.use(function (req, res, next) {
    console.log('Time:', Date.now());
    next();
});

// 挂载至 /user/:id 的中间件，任何指向 /user/:id 的请求都会执行它
app.use('/user/:id', function (req, res, next) {
    console.log('Request Type:', req.method);
    next();
});

// 路由和句柄函数(中间件系统)，处理指向 /user/:id 的 GET 请求
app.get('/user/:id', function (req, res, next) {
    res.send('USER');
});
```

express 中间件有以下几种：

-   **应用级中间件** 公共功能的中间件，例如日志记录、获取公共数据
-   **路由级中间件** 针对路由不同功能的中间件，用于业务处理
-   **错误处理中间件** 用于捕获异常
-   **内置中间件** 最常用的中间件，例如`express.static`是 express 内置的中间件，用于返回静态文件
-   **第三方中间件** 一个框架要保证扩展性，肯定得支持第三方开发者贡献自己的代码

---

## 页面渲染

nodejs 没有御用的模板引擎，这一点不像 php asp jsp 等，需要自己去选择，例如 artTemplate 。书中也简单讲解了实现一个模板引擎的逻辑，我之前了解过 vue 中模板的解析，因此对这块逻辑也不算陌生。另外，模板解析的逻辑，大概了解即可，也无需详细深入，毕竟是工具性的东西.

---

## 遗留问题

上文中，有一段`req.on('data' ...`和`req.on('end', ...`代码没有详细介绍，现在关注两点：

-   `req.on`这里的`on`是特定的吗？
-   这里的`data`和`end`是特定的吗？

下面将用两节内容讲解这两个疑问。

# nodejs 语法特性

---

## 目录

-   和浏览器 JS 的不同
-   模块化
-   异步

---

## 和浏览器 JS 的不同

前端说的 JS ，即浏览器端运行的 JS 其实是两个标准的合并。只有这俩合起来，在实际开发中才能使用，否则：例如只讲第一个标准的话，那只能写 demo 演示一下，没法实际用。

-   **ECMA 262 标准** —— 即 JS 的基本语法，如何定义变量、变量类型、原型、作用域、异步等
-   **W3C 的 Web-API 标准** —— 包括 BOM DOM 操作、ajax 、存储等

而在 **nodejs 中，第一个标准，即 ECMA 262 标准继续使用，也就是 JS 基本语法继续使用**，JS 原型、异步、闭包等特性也继续保持。但是第二个标准就没法继续使用过了，例如`window` `document` `location` `getElementById`等，这些就都没有了，因为 nodejs 是 server 端的，根本没有浏览器的那些特性。但是 **nodejs 中定义了自己在 server 端特有的 API**，例如`http` `fs` `Stream` `os`等，这些都是 server 端才有的特性。

总结一下，就两点

-   继续使用 ECMA 262 标准，即 JS 的基本语法
-   定义了 server 端特性的 API ，如`http` `fs`等

---

## 模块化

nodejs 使用 CommonJS 模块化规范，其中会用到`require` `module.exports`关键字。归总一下，一共有三种引用场景：

### 引用核心模块

比较简单，即引用 nodejs 默认提供的核心 API 。例如:

```js
var http = require('http');
var fs = require('fs');
var os = require('os');
```

### 引用 npm 安装的模块

npm 安装第三发模块时，可通过加入`--save`或`--save-dev`，这样安装之后模块名称会保存在`package.json`中。然后即可根据模块名称引用刚刚安装的模块，常见的有：

```js
var lodash = require('lodash');
var React = require('react');
var webpack = require('webpack');
```

### 引用自定义的模块

以上`require`的时候都是输入名称，也可以输入相对路径来引用自己定义的模块。自己新建一个文件`a.js`，内容为

```js
module.exports = function (info) {
    console.log(info);
};
```

然后新建一个文件`b.js`（和`a.js`同目录），内容为

```js
var a = require('./a.js'); // 引用自定义模块 a.js
a('hello world');
```

`node b.js`，即可看到效果。

### 附：解答一个疑问

这里有一个问题，按照 JS 语法来说，以上代码中 `require` `module.exports` 都是未定义的变量，应该会报错的。其实，**在编译过程中，nodejs 会获取这段代码，然后进行一个函数封装**，然后变成这样，问题就解决了。

```js
// 上面提出的未定义的变量，都是函数的参数，是执行时被传入的
// 同理的还是 __filename, __dirname
(function (exports, require, module, __filename, __dirname) {
    var fs = requre('fs');
    module.exports = function () {
        console.log(__dirname);
        console.log(__filename);
    };
});
```

---

## 异步

这里提出“异步”，并不是要讲什么新内容，而是着重提示：接下来的讲解，会用到很多异步的知识，因此异步必须要掌握全面。提醒一下，还不了解的同学尽快去补充学习：

-   异步和同步的区别
-   异步和单线程
-   event loop
-   callback 方式
-   Promise
-   async/await

背景
一个C++程序想要运行起来，除了离不开C++编译器，还离不开C++的标准库。我们写的C++程序要想被Linux等操作系统运行起来，必须符合一定的规范。以Linux为例，这种规范在基于X86-64处理器的Linux上称之为：System V AMD64 ABI。只有符合这个ABI规范的文件，你的程序才能被Linux的系统调用加载并成为一个进程。

众所周知，我们写的C++程序只是符合C++规范，和System V AMD64 ABI规范之间还有很远的距离。这个距离又是怎么消弭的呢？答案就是C++编译器（含链接器，以下Gemfield所说的“编译”可能包含了“链接”过程，请自行甄别）和标准C++库（当然必须还有标准C库）。

本文中，Gemfield将描述C++的标准库。并主要讨论如下的问题：

C++标准库是什么？
C++标准库如何被使用？
C++标准库的内容有哪些？
C++标准库是什么？
ISO 14882标准中，在条款20到33和附加章节D中定义的C++应该实现的内容。

这部分内容是C++标准库应该要实现的内容。有了这个标准定义，世界上各个组织才能实现具体的C++标准库。这其中，有影响力的组织及其实现有3个：GNU的libstdc++、LLVM的libc++、我不想提。一般来说：

在GNU/Linux上，我们使用的C++库都是GNU实现的libstdc++（/usr/lib/gcc/x86_64-linux-gnu/9/libstdc++.so、/usr/lib/gcc/x86_64-linux-gnu/9/libstdc++.a）；
在MacOS、iOS上，我们使用的C++库都是LLVM项目实现的libc++（/usr/lib/libc++.dylib）；
在Android上，我们使用的C++库为LLVM的libc++（NDK r18以前还是支持GNU的libstdc++的，在r18上被完全去除）；注意这可不是系统库，你需要将库文件包含在apk中（Android上的系统库是/system/lib/libstdc++.so，这不是GNU的那个，只包含了最小的C++ runtime实现，如new delete等）；
在Windows上，我们使用的C++库......算了，谁在乎呢，这年头谁还用windows呀。
C++库如何被使用
你可能在阅读Gemfield本文的时候察觉到了，在我们平常编译C++程序的时候，并没有显式的去链接标准C++库呀。这是因为编译器自动帮你做了这个事情。如果在g++编译C++源文件的时候加上-v参数：

g++ -v gemfield.cpp -o gemfield
那么日志就会清楚的显示编译的时候默认使用了什么库。

1，编译时依赖

Gemfield把加上-v参数之后的编译日志摘要如下：

 -m elf_x86_64
 -dynamic-linker /lib64/ld-linux-x86-64.so.2
 -pie
 /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/Scrt1.o
 /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crti.o
 /usr/lib/gcc/x86_64-linux-gnu/9/crtbeginS.o
 -lstdc++
 -lm
 -lgcc_s
 -lgcc
 -lc
 /usr/lib/gcc/x86_64-linux-gnu/9/crtendS.o
 /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crtn.o
关键的地方有：

编译的是elf_x86_64，也就是x86-64上的ELF格式，ELF格式是System V AMD64 ABI中的一部分，讲的是可执行文件的格式，详细内容请参考专栏libGemfield的其它文章；
使用的dynamic linker是/lib64/ld-linux-x86-64.so.2，这是ELF格式的一部分；
pie，这是ASLR的前提；
编译时链接了libstdc++、libm、libgcc_s、libgcc、libc库；
编译时链接了Scrt1.o、crti.o、crtbeginS.o、crtendS.o、crtn.o。
可以看到g++在背后自动链接了标准C++库、标准C库。这其中：

头文件<cstdio>、<cstdlib>（或者C中的stdlib.h和stdio.h）中声明的函数就实现在了上面的libc库中；
头文件<cmath>（或者C中的math.h）声明的函数就实现在了上面的libm库中；
而libstdc++.so依赖libm.so，因此编译C++程序的时候g++也自动链接了libm.so；
libgcc和libgcc_s库包含了一些底层的函数，g++编译的时候生成的一些函数调用依赖该库；
Scrt1.o、crti.o、crtbeginS.o、crtendS.o、crtn.o这些文件帮助编译器生成了最终的ELF文件，更详细解释如下：
crt0.o
  Older style of the initial runtime code ?  Usually not generated anymore
  with Linux toolchains, but often found in bare metal toolchains.  Serves
  same purpose as crt1.o (see below).
crt1.o
  Newer style of the initial runtime code.  Contains the _start symbol which
  sets up the env with argc/argv/libc _init/libc _fini before jumping to the
  libc main.  glibc calls this file 'start.S'.
crti.o
  Defines the function prolog; _init in the .init section and _fini in the
  .fini section.  glibc calls this 'initfini.c'.
crtn.o
  Defines the function epilog.  glibc calls this 'initfini.c'.
Scrt1.o
  Used in place of crt1.o when generating PIEs.
gcrt1.o
  Used in place of crt1.o when generating code with profiling information.
  Compile with -pg.  Produces output suitable for the gprof util.
Mcrt1.o
  Like gcrt1.o, but is used with the prof utility.  glibc installs this as
  a dummy file as it's useless on linux systems.
crtbegin.o
  GCC uses this to find the start of the constructors.
crtbeginS.o
  Used in place of crtbegin.o when generating shared objects/PIEs.
crtbeginT.o
  Used in place of crtbegin.o when generating static executables.
crtend.o
  GCC uses this to find the start of the destructors.
crtendS.o
  Used in place of crtend.o when generating shared objects/PIEs.
2，运行时依赖

程序编译完成之后已经成为了ELF文件，这个时候它就可以在Linux上被执行了：

gemfield@CivilNet:~$ ./gemfield
但由于我们的程序默认链接的是动态库，因此在运行时会对包括C++标准库在内的一些动态库产生依赖，使用ldd命令可以看到这些依赖：

gemfield@CivilNet:~$ ldd gemfield
        linux-vdso.so.1 (0x00007ffc33380000)
        libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f7193c31000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f7193c16000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f7193a24000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f71938d5000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f7193e3c000)
linux-vdso.so.1，这是Linux virtual Dynamic Shared Object (vDSO)，是个虚拟共享库，在文件系统上并不存在。Linux vDSO把kernel中的代码通过共享库的形式映射到用户的进程地址空间上。这就实现了一些原本频繁的系统调用可以直接在用户空间完成，加快了速度。内核代码在arch/x86/vdso/vdso.lds.S文件中定义了vDSO中export的函数，共4个（比如常说的gettimeofday系统调用）：
/*
 * This controls what userland symbols we export from the vDSO.
 */
VERSION {
        LINUX_2.6 {
        global:
                clock_gettime;
                __vdso_clock_gettime;
                gettimeofday;
                __vdso_gettimeofday;
                getcpu;
                __vdso_getcpu;
                time;
                __vdso_time;
        local: *;
        };
}
/lib64/ld-linux-x86-64.so.2用来动态加载程序依赖的共享库。这是个特殊的库，其路径会直接写在可执行文件的相关字段中。而程序所依赖的其它共享库则是由ld-linux-x86-64.so.2加载进来的；
剩下的就是编译时链接的库中的那四个，不再赘述。
如果不想让程序在运行时还有依赖的动态库，则可以使用静态编译。

3，静态编译

一个C++程序，如果想静态链接的话，加上-static关键字：

g++ -v -static gemfield.cpp -o gemfield
如此一来，这个库在运行的时候就不依赖任何库了。但是我们不推荐这么做，原因有多个。

C++库的bug fix，动态编译的程序只需要更新一个C++库就行了，静态编译的则要分别更新每个可执行文件；
一些安全相关的功能将无法被使用，比库文件的随机内存地址加载；静态编译也无法产生PIE的代码；
使用动态库可以节约物理内存的使用（当多个程序依赖同一个共享库的话）；
libc库中的某些功能 (locale (through iconv), NSS, IDN, ...)需要动态链接来加载相应的外部代码，静态编译对此支持有限；
一些debug工具对动态库加载机制有依赖，静态编译对debug不友好；
版权问题，不过听说标准C++库的GPL有个例外？
当然任何事情都不是绝对的，考虑好后想用就用呗。

C++标准库的内容有哪些？
首先，标准C++库的头文件把标准C的头文件也纳入进来作为了一个子集，如下所示：

<cassert>
<cctype>
<cerrno>
<cfenv>
<cfloat>
<cinttypes>
<ciso646>
<climits>
<clocale>
<cmath>
<csetjmp>
<csignal>
<cstdarg>
<cstdbool>
<cstddef>
<cstdint>
<cstdio>
<cstdlib>
<cstring>
<ctgmath>
<ctime>
<cuchar>
<cwchar>
<cwctype>
这些c开头的c++头文件都直接include了标准C库的头文件，比如<clocale>包含了#include <locale.h>，只不过是把符号放到了std命名空间下。在C++程序中，当然是推荐include这些标准C的头文件，而不是*.h这样的。

其次，按照不同的功能，C++的标准库包含了如下内容：

1，Concepts

C++20新增的。

<concepts>
2，Coroutines

C++20新增的。

<coroutine>
3，Ranges

C++20新增的。

<ranges>
4，工具类

C++17新增了<any> 、<optional>、 <variant>，C++20新增了<compare>、<version>、<source_location>。

<cstdlib>
<csignal>
<csetjmp>
<cstdarg>
<typeinfo>
<typeindex>
<type_traits>
<bitset>
<functional>
<utility>
<ctime>
<chrono>
<cstddef>
<initializer_list>
<tuple>
<any>
<optional>
<variant>
<compare>
<version>
<source_location>
5，容器部分

C++20新增了<span>。

<array>
<vector>
<deque>
<list>
<forward_list>
<set>
<map>
<unordered_set>
<unordered_map>
<stack>
<queue>
<span>
6，iterator

C++20增添了很多iterator类。

<iterator>
7，线程支持

C++20新增了<stop_token>、<semaphore>、<latch>、 <barrier>。

<thread>
<stop_token>
<mutex>
<shared_mutex>
<future>
<condition_variable>
<semaphore>
<latch>
<barrier>
<atomic>
8，通用算法

C++17新增了<execution>。

<algorithm>
<execution>
<algorithm>中包含的算法有：all_of、any_of、none_of、for_each、find、find_if、find_if_not、find_end、find_first_of、adjacent_find、count、count_if、mismatch、equal、is_permutation、search、search_n、copy、copy_n、copy_if、copy_backward、move、move_backward、swap、swap_ranges、iter_swap、transform、replace、replace_if、replace_copy、replace_copy_if、fill、fill_n、generate、generate_n、remove、remove_if、remove_copy、remove_copy_if、unique、unique_copy、reverse、reverse_copy、rotate、rotate_copy、random_shuffle、shuffle、is_partitioned、partition、stable_partition、partition_copy、partition_point、sort、stable_sort、partial_sort、partial_sort_copy、is_sorted、is_sorted_until、nth_element、lower_bound、upper_bound、equal_range、binary_search、merge、inplace_merge、includes、set_union、set_intersection、set_difference、set_symmetric_difference、push_heap、pop_heap、make_heap、sort_heap、is_heap、is_heap_until、min、max、minmax、min_element、max_element、minmax_element、lexicographical_compare、next_permutation、prev_permutation。

9，动态内存和智能指针

C++17新增了memory_resource。

<new>
<memory>
<scoped_allocator>
<memory_resource>
10，字符串

C++17新增了<string_view>、<charconv>，C++20新增了<format>。

<cctype>
<cwctype>
<cstring>
<cwchar>
<cuchar>
<string>
<string_view>
<charconv>
<format>
<regex>
11，本地化

<codecvt>在C++17废弃。

<locale>
<clocale>
<codecvt>
12，stream和io

C++20新增了<syncstream>。

<iosfwd>
<ios>
<istream>
<ostream>
<iostream>
<fstream>
<sstream>
<syncstream>
<strstream>
<iomanip>
<streambuf>
<cstdio>
13，文件系统

C++17新增的。

<filesystem>
14，数值库

C++20新增了<bit>、<numbers>。

<climits>
<cfloat>
<cstdint>
<cinttypes>
<limits>
<cmath>
<complex>
<valarray>
<random>
<numeric>
<ratio>
<cfenv>
<bit>
<numbers>
15，语言特性支持

<exception>
<limits>
<new>
<typeinfo>
16，时间

<chrono>
17，错误和异常处理

<exception>
<stdexcept>
<cassert>
<system_error>
<cerrno>
最后，不是每个系统上的C++编译都使用了标准的C++特性。这里的系统主要是手机操作系统，比如Android。ndk-build可能默认将异常、RTTI等功能停用。





Algorithm
前序 + 中序
https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

分割等和子集
https://github.com/youngyangyang04/leetcode-master/blob/master/problems/0416.%E5%88%86%E5%89%B2%E7%AD%89%E5%92%8C%E5%AD%90%E9%9B%86.md
两个栈模拟队列

class CQueue {
public:
    stack<int> stack1;
    stack<int> stack2;
    CQueue() {}
    
    void appendTail(int value) {
        stack1.push(value);
    }
    
    int deleteHead() {
        if (stack1.empty()) return -1;
        
        while (!stack1.empty()){ // 1 -> 2
            int tmp = stack1.top();
            stack1.pop();
            stack2.push(tmp);
        }
        // delete head
        int res = stack2.top();
        stack2.pop();
        while (!stack2.empty()){ // 1 <- 2
            int temp = stack2.top();
            stack2.pop();
            stack1.push(temp);
        }
        return res;
    }
};



Network
Keep-Alive

HTTP Keep-Alive
在HTTP 1.0以前，每个http请求都要求打开一个TCP socket连接，并且使用一次之后就断开这个TCP连接，这会导致频繁地创建和销毁TCP。HTTP 1.1通过使用keep-alive可以改善这种状态，即在一次TCP连接中可以持续发送多份数据而不会断开连接。

TCP KEEPALIVE
这是TCP协议栈为了检测连接状况的保活机制，当TCP空闲一定时间后会发送心跳包给对方，
如果对端回复ACK后，就认为对端是存活的，重置定时器；
如果对端回复RST应答（对端崩溃或者其他原因，导致的复位），那就关闭该连接；
如果对端无任何回应，那就会出发超时重传，直到达到重传的次数，如果对端依然没有回复，那么就关闭该连接。

HTTP位于网络协议栈的应用层，而TCP位于网络协议栈的传输层，两者的KEEP-ALIVE虽然名称相同，但是作用不同。HTTP是为了重用TCP，避免每次请求，都重复创建TCP；而TCP的KEEP-ALIVE是一种保活机制，检测对端是否依然存


 
说下ARP 协议的工作过程？
ARP 协议协议，Address Resolution Protocol，地址解析协议，它是用于实现IP地址到MAC地址的映射。

首先，每台主机都会在自己的ARP缓冲区中建立一个ARP列表，以表示IP地址和MAC地址的对应关系。
当源主机需要将一个数据包要发送到目的主机时，会首先检查自己的ARP列表，是否存在该IP地址对应的MAC地址；如果有﹐就直接将数据包发送到这个MAC地址；如果没有，就向本地网段发起一个ARP请求的广播包，查询此目的主机对应的MAC地址。此ARP请求的数据包里，包括源主机的IP地址、硬件地址、以及目的主机的IP地址。
网络中所有的主机收到这个ARP请求后，会检查数据包中的目的IP是否和自己的IP地址一致。如果不相同，就会忽略此数据包；如果相同，该主机首先将发送端的MAC地址和IP地址添加到自己的ARP列表中，如果ARP表中已经存在该IP的信息，则将其覆盖，然后给源主机发送一个 ARP响应数据包，告诉对方自己是它需要查找的MAC地址。
源主机收到这个ARP响应数据包后，将得到的目的主机的IP地址和MAC地址添加到自己的ARP列表中，并利用此信息开始数据的传输。如果源主机一直没有收到ARP响应数据包，表示ARP查询失败。
Shadowsocks
说下ping的原理
ping，Packet Internet Groper，是一种因特网包探索器，用于测试网络连接量的程序。Ping是工作在TCP/IP网络体系结构中应用层的一个服务命令， 主要是向特定的目的主机发送ICMP（Internet Control Message Protocol 因特网报文控制协议） 请求报文，测试目的站是否可达及了解其有关状态”
一般来说，ping可以用来检测网络通不通。它是基于ICMP协议工作的。假设机器A ping机器B，工作过程如下：
ping通知系统，新建一个固定格式的ICMP请求数据包
ICMP协议，将该数据包和目标机器B的IP地址打包，一起转交给IP协议层
IP层协议将本机IP地址为源地址，机器B的IP地址为目标地址，加上一些其他的控制信息，构建一个IP数据包
先获取目标机器B的MAC地址。
数据链路层构建一个数据帧，目的地址是IP层传过来的MAC地址，源地址是本机的MAC地址
机器B收到后，对比目标地址，和自己本机的MAC地址是否一致，符合就处理返回，不符合就丢弃。
根据目的主机返回的ICMP回送回答报文中的时间戳，从而计算出往返时间
最终显示结果有这几项：发送到目的主机的IP地址、发送 & 收到 & 丢失的分组数、往返时间的最小、最大& 平均值


OS

进程什么时候由用户态转化为内核态？

(系统调用、中断、陷入)

线程和进程，线程可以共享进程里的哪些东西。 知道协程是什么吗

进程，是并发执行的程序在执行过程中分配和管理资源的基本单位，每一个进程都有一个自己的地址空间，即进程空间或（虚空间）。进程空间的大小 只与处理机的位数有关，一个 16 位长处理机的进程空间大小为 216 ，而 32 位处理机的进程空间大小为 232 。进程至少有 5 种基本状态，它们是：初始态，执行态，等待状态，就绪状态，终止状态。

线程，在网络或多用户环境下，一个服务器通常需要接收大量且不确定数量用户的并发请求，为每一个请求都创建一个进程显然是行不通的，——无论是从系统资源开销方面或是响应用户请求的效率方面来看。因此，操作系统中线程的概念便被引进了。线程，是进程的一部分，一个没有线程的进程可以被看作是单线程的。线程有时又被称为轻权进程或轻量级进程，也是 CPU 调度的一个基本单位。
共享进程的地址空间，全局变量（数据和堆）。在一个进程中，各个线程共享堆区，而进程中的线程各自维持自己的栈。

Each thread has its own:
•  栈区和栈指针（Stack area and stack pointer）
•  寄存器（Registers）
•  调度优先级Scheduling properties (such as policy or priority)
•  信号（阻塞和悬挂）Signals (pending and blocked signals)
•  普通变量Thread specific data ( automatic variables )

线程是指进程内的一个执行单元,也是进程内的可调度实体.
与进程的区别:
(1)地址空间:进程内的一个执行单元;进程至少有一个线程;它们共享进程的地址空间;而进程有自己独立的地址空间;
(2)资源拥有:进程是资源分配和拥有的单位,同一个进程内的线程共享进程的资源
(3)线程是处理器调度的基本单位,但进程不是.
4)二者均可并发执行.

进程和线程都是由操作系统所体会的程序运行的基本单元，系统利用该基本单元实现系统对应用的并发性。进程和线程的区别在于：

简而言之,一个程序至少有一个进程,一个进程至少有一个线程.
线程的划分尺度小于进程，使得多线程程序的并发性高。
另外，进程在执行过程中拥有独立的内存单元，而多个线程共享内存，从而极大地提高了程序的运行效率。
线程在执行过程中与进程还是有区别的。每个独立的线程有一个程序运行的入口、顺序执行序列和程序的出口。但是线程不能够独立执行，必须依存在应用程序中，由应用程序提供多个线程执行控制。
从逻辑角度来看，多线程的意义在于一个应用程序中，有多个执行部分可以同时执行。但操作系统并没有将多个线程看做多个独立的应用，来实现进程的调度和管理以及资源分配。这就是进程和线程的重要区别。

进程是具有一定独立功能的程序关于某个数据集合上的一次运行活动,进程是系统进行资源分配和调度的一个独立单位.
线程是进程的一个实体,是CPU调度和分派的基本单位,它是比进程更小的能独立运行的基本单位.线程自己基本上不拥有系统资源,只拥有一点在运行中必不可少的资源(如程序计数器,一组寄存器和栈),但是它可与同属一个进程的其他的线程共享进程所拥有的全部资源.
一个线程可以创建和撤销另一个线程;同一个进程中的多个线程之间可以并发执行.

协程：
定义：协程其实可以认为是比线程更小的执行单元。为啥说他是一个执行单元，因为他自带CPU上下文。
协程切换：协程拥有自己的寄存器上下文和栈。协程调度切换时，将寄存器上下文和栈保存到其他地方，在切回来的时候，恢复先前保存的寄存器上下文和栈。
（我们在自己在进程里面完成逻辑流调度，碰着i\o我就用非阻塞式的。那么我们即可以利用到异步优势，又可以避免反复系统调用，还有进程切换造成的开销，分分钟给你上几千个　　　　逻辑流不费力。这就是协程。）
协程的调度完全由用户控制，一个线程可以有多个协程，用户创建了几个线程，然后每个线程都是循环按照指定的任务清单顺序完成不同的任务，当任务被堵塞的时候执行下一个任务，当恢复的时候再回来执行这个任务，任务之间的切换只需要保存每个任务的上下文内容，就像直接操作栈一样的，这样就完全没有内核切换的开销，可以不加锁的访问全局变量，所以上下文的切换非常快；另外协程还需要保证是非堵塞的且没有相互依赖，协程基本上不能同步通讯，多采用一步的消息通讯，效率比较高。
多线程和多进程的优劣：

多线程还是多进程的争执由来已久，这种争执最常见到在B/S通讯中服务端并发技术的选型上，比如WEB服务器技术中，Apache是采用多进程的（perfork模式，每客户连接对应一个进程，每进程中只存在唯一一个执行线程），Java的Web容器Tomcat、Websphere等都是多线程的（每客户连接对应一个线程，所有线程都在一个进程中）
c/c++
一个C++源文件从文本到可执行文件经历的过程

对于C/C++编写的程序，从源代码到可执行文件，一般经过下面四个步骤：

1).预处理，产生.i文件

2).编译，产生汇编文件(.s文件)

3).汇编，产生目标文件(.o或.obj文件)

4).链接,产生可执行文件(.out或.exe文件)

动态链接库和静态链接库的区别


执行main函数之前和之后做了哪些工作？
main函数执行之前主要是系统的初始化资源：
在栈区：设置栈指针
在data段：初始化全局变量和静态变量
在bss段：对未初始化的全局变量进行赋初值，bool是false,short,int,long 是0，指针是NULL
将main函数的参数传到main函数里面
main函数执行完成之后并不一定意味着进程结束。
main函数执行完成之后：
全局对象的析构函数会在main函数的执行后执行
使用atexit注册的函数会在main函数执行之后执行


为什么构造函数不能是虚函数？

从vptr角度解释
虚函数的调用是通过虚函数表来查找的，而虚函数表由类的实例化对象的vptr指针指向，该指针存放在对象的内部空间中，需要调用构造函数完成初始化。如果构造函数是虚函数，那么调用构造函数就需要去找vptr，但此时vptr还没有初始化！

从多态角度解释
1.虚函数主要是实现多态，在运行时才可以明确调用对象，根据传入的对象类型来调用函数;
2.构造函数是在创建对象时自己主动调用的，不可能通过父类的指针或者引用去调用,那使用虚函数也没有实际意义;
3.调用构造函数时还不能确定对象的真实类型（由于子类会调父类的构造函数）;
4.构造函数的作用是提供初始化，在对象生命期仅仅运行一次，不是对象的动态行为，没有必要成为虚函数

memcpy与memmove的区别

memcpy和memmove都是C语言的库函数，相比于strcpy和strncpy只能拷贝字符数组，memcpy与memmove可以拷贝其它类型的数组，但是为什么要同时提供两种方法呢？

首先来看函数原型：

void *memcpy(void *restrict s1, const void *restrict s2, size_t n);
void *memmove(void *s1, const void *s2, size_t n);

这两个函数都是将s2指向位置的n字节数据拷贝到s1指向的位置，区别就在于关键字restrict, memcpy假定两块内存区域没有数据重叠，而memmove没有这个前提条件。如果复制的两个区域存在重叠时使用memcpy，其结果是不可预知的，有可能成功也有可能失败的，所以如果使用了memcpy,程序员自身必须确保两块内存没有重叠部分。


写一个函数，在多个线程中均有使用，只在第一次调用时执行一次，后面调用直接返回值

#include <iostream>
#include <thread>

using namespace std;

once_flag flg;

void func() {
 call_once(flg, [] { cout << "call once" << endl; });
}

int main() {
 thread t1(func);
 thread t2(func);
 thread t3(func);

 t1.join();
 t2.join();
 t3.join();

 return 0;
}



虚函数表：
多态是由虚函数实现的，而虚函数主要是通过虚函数表（V-Table）来实现的。
如果一个类中包含虚函数（virtual修饰的函数），那么这个类就会包含一张虚函数表，虚函数表存储的每一项是一个虚函数的地址。如下图：

这个类的每一个对象都会包含一个虚指针（虚指针存在于对象实例地址的最前面，保证虚函数表有最高的性能），这个虚指针指向虚函数表。
注：对象不包含虚函数表，只有虚指针，类才包含虚函数表，派生类会生成一个兼容基类的虚函



C++ vector和list的区别？

vector是动态数组实现的，一说到动态那肯定是在堆上分配空间的。如果容量超出原先设定的值，会以2倍扩增。性能上：因为是数组实现的，所以访问起来肯定是O(1)时间内访问。
因为是vector,所以会经常有插入和删除的操作：
如果在结尾插入并且空间够的情况下，很快，如果空间不够，则首先要进行扩容，扩容的过程中完成内存拷贝。在中间拷贝也是一样，如果空间足够大，只需要完成插入位置后的元素拷贝就行了，如果内存不够则也需要先进行扩容，然后进行拷贝。
如果删除的是结尾的元素的话很快就可以完成，如果是中间的元素那就需要拷贝了。
总体而言由于vector的特性原因，所以它很适合随机访问，并且插入删除在结尾部。
list是双向链表实现的，由于是双向链表，所以肯定也是在堆上分配空间的。
那自然插入和删除都是很容易的，因为双向链表实现的原理就是为了插入和删除。
具体的区别和联系：
都是在堆上分配空间
vector是基于动态数组实现的，list基于双向链表实现的
vector不便于中间插入和删除，list支持随机插入和删除

Lock-free 原子类型 内存序的理解

