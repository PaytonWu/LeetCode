// Longest Valid Parentheses.cpp : Defines the entry point for the console application.
//

#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        const int LEFT_PARENTHE = INT_MAX;
        const int RIGHT_PARENTHE = INT_MIN;

        stack<int> stack;
        int largest = 0;
        int tmp_largest = 0;
        int tmp = 0;

        for (string::const_iterator i = s.begin(); i != s.end(); ++i)
        {
            // 每遇到一个')'都开始一次匹配的操作
            if (')' == *i)
            {
                // 把字符串的前导')'去掉
                if (stack.empty())
                {
                    continue;
                }

                int matchCntOrParenthe = stack.top();
                bool isMatchCount = false;

                if (LEFT_PARENTHE != matchCntOrParenthe && RIGHT_PARENTHE != matchCntOrParenthe)
                {
                    isMatchCount = true;
                    stack.pop();

                    if (stack.empty())
                    {
                        stack.push(matchCntOrParenthe);
                        stack.push(RIGHT_PARENTHE);
                        continue;
                    }
                }

                // 如果是'('，成功进行了一次匹配
                if (LEFT_PARENTHE == stack.top())
                {
                    stack.pop();

                    if (isMatchCount)
                    {
                        ++matchCntOrParenthe;
                    }
                    else
                    {
                        matchCntOrParenthe = 1;
                    }

                    if (!stack.empty())
                    {
                        // 在吧匹配数压栈前，判断下栈顶。如果栈顶是数字，那么当前匹配和前一次匹配可以联系在一起
                        int prevMatchCnt = stack.top();
                        if (LEFT_PARENTHE != prevMatchCnt && RIGHT_PARENTHE != prevMatchCnt)
                        {
                            stack.pop();
                            stack.push(prevMatchCnt + matchCntOrParenthe);
                        }
                        else
                        {
                            stack.push(matchCntOrParenthe);
                        }
                    }
                    else
                    {
                        stack.push(matchCntOrParenthe);
                    }
                }
                else
                {
                    stack.push(matchCntOrParenthe);
                    stack.push(RIGHT_PARENTHE);
                }
            }
            else
            {
                stack.push(LEFT_PARENTHE);
            }
        }

        while (!stack.empty())
        {
            int topValue = stack.top();
            if (LEFT_PARENTHE != topValue && RIGHT_PARENTHE != topValue)
            {
                if (largest < topValue)
                {
                    largest = topValue;
                }
            }

            stack.pop();
        }

        return largest * 2;
    }
};

int main()
{
    return 0;
}

