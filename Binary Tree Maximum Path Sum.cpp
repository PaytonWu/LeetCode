// Binary Tree Maximum Path Sum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <climits>
#include <algorithm>

using namespace std;

/**
 * Definition for binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 这道题的意思是：
// 在树中找两个顶点，使得连接这两个顶点的路径上的所有树节点的和最大
// 所以：
//  1. 这两个顶点都在左子树或者右子树
//  2. 其中一个顶点在左子树或者右子树，另一个顶点是当前的树根
//  3. 一个点在左子树，另一个点在右子树，路径通过当前的树根连起来
class Solution {
public:
    // 返回值是包含root的最大路径和。
    int maxPathSum(TreeNode* root, int& ans)
    {
        if (NULL == root)
        {
            return 0;
        }

        TreeNode* left = root->left;
        TreeNode* right = root->right;

        int leftSum = maxPathSum(left, ans);
        int rightSum = maxPathSum(right, ans);

        int leftSumWithRoot = leftSum + root->val;
        int rightSumWithRoot = rightSum + root->val;
        int leftRightSumWithRoot = leftSum + rightSum + root->val;

        if (left)
        {
            ans = max(ans, leftSum);
        }
        if (right)
        {
            ans = max(ans, rightSum);
        }

        ans = max(ans, max(max(leftSumWithRoot, rightSumWithRoot), max(leftRightSumWithRoot, root->val)));

        return max(root->val, max(leftSumWithRoot, rightSumWithRoot));
    }

    int maxPathSum(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int ans = INT_MIN;
        maxPathSum(root, ans);

        return ans;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

