// Sum Root to Leaf Numbers.cpp : Defines the entry point for the console application.
//

#include <iostream>
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
    void dfs(TreeNode* tree, int num, int& result)
    {
        if (NULL == tree)
        {
            return;
        }

        if (NULL == tree->left && NULL == tree->right)
        {
            result += num * 10 + tree->val;
            return;
        }

        dfs(tree->left, num*10+tree->val, result);
        dfs(tree->right, num*10+tree->val, result);
    }
public:

    int sumNumbers(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int result = 0;
        dfs(root, 0, result);

        return result;
    }
};

int main()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(0);

    Solution s;
    cout << s.sumNumbers(root) << endl;
	return 0;
}

