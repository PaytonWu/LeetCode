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
            // ÿ����һ��')'����ʼһ��ƥ��Ĳ���
            if (')' == *i)
            {
                // ���ַ�����ǰ��')'ȥ��
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

                // �����'('���ɹ�������һ��ƥ��
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
                        // �ڰ�ƥ����ѹջǰ���ж���ջ�������ջ�������֣���ô��ǰƥ���ǰһ��ƥ�������ϵ��һ��
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

