// Balanced Binary Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

class Solution {
public:
    bool heightBalanced(TreeNode* root)
    {
        if (NULL == root)
        {
            return true;
        }

        TreeNode* left = root->left;
        TreeNode* right = root->right;

        bool leftBalnced   = heightBalanced(left);
        bool rightBalanced = heightBalanced(right);

        int leftHight = 0;
        int rightHeight = 0;

        if (left && right)
        {
            leftHight = left->val;
            rightHeight = right->val;

            root->val = max(leftHight, rightHeight) + 1;
        }
        else if (left)
        {
            leftHight = left->val;

            root->val = leftHight + 1;
        }
        else if (right)
        {
            rightHeight = right->val;

            root->val = rightHeight + 1;
        }
        else
        {
            root->val = 1;
        }

        return leftBalnced && rightBalanced && abs(leftHight - rightHeight) <= 1;
    }

    bool isBalanced(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return heightBalanced(root);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

