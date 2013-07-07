// Path Sum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/**
 * Definition for binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum, int tmp)
    {
        if (NULL == root->right && NULL == root->left)
        {
            return sum == tmp + root->val;
        }

        if (NULL != root->right)
        {
            if (hasPathSum(root->right, sum, tmp + root->val))
            {
                return true;
            }
        }

        if (NULL != root->left)
        {
            if (hasPathSum(root->left, sum, tmp + root->val))
            {
                return true;
            }
        }

        return false;
    }
    bool hasPathSum(TreeNode *root, int sum) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (NULL == root)
        {
            return false;
        }

        return hasPathSum(root, sum, 0);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

