// Minimum Depth of Binary Tree.cpp : Defines the entry point for the console application.
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
    int minDepth(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (NULL == root)
        {
            return 0;
        }
        
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        
        if (left && right)
        {
            return min(minDepth(left), minDepth(right)) + 1;
        }
        
        if (left)
        {
            return minDepth(left) + 1;
        }
        else
        {
            return minDepth(right) + 1;
        }
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

