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

// ��������˼�ǣ�
// ���������������㣬ʹ�����������������·���ϵ��������ڵ�ĺ����
// ���ԣ�
//  1. ���������㶼������������������
//  2. ����һ����������������������������һ�������ǵ�ǰ������
//  3. һ����������������һ��������������·��ͨ����ǰ������������
class Solution {
public:
    // ����ֵ�ǰ���root�����·���͡�
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

