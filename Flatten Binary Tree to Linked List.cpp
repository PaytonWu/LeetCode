// Flatten Binary Tree to Linked List.cpp : Defines the entry point for the console application.
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
    void flatten(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (NULL == root)
        {
            return;
        }
        
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        
        flatten(left);
        flatten(right);
        
        root->right = left;
        root->left = NULL;

        // the performance here is a little low...
        TreeNode* traversal = root;
        while (traversal->right)
        {
            traversal = traversal->right;
        }
        traversal->right = right;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

