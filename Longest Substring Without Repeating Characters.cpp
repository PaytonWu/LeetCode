// Longest Substring Without Repeating Characters.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>

using namespace std;

// 还可以把dp数组也去掉
class Solution {
public:
    int lengthOfLongestSubstring(const string& s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (0 == s.size())
        {
            return 0;
        }

        size_t* dp = new size_t[s.size()];
        dp[0] = 1;

        for (size_t i = 1; i < s.size(); ++i)
        {
            size_t cnt = exist(s[i], s, i-1, dp[i-1]);
            dp[i] = cnt + 1;
        }

        size_t longest = 1;
        for (size_t i = 0; i < s.size(); ++i)
        {
            if (longest < dp[i])
            {
                longest = dp[i];
            }
        }

        delete[] dp;
        return static_cast<int>(longest);
    }

private:
    size_t exist(char target, const string& s, size_t index, size_t cnt)
    {
        size_t orig_cnt = cnt;
        while (cnt--)
        {
            if (s[index--] == target)
            {
                return orig_cnt - cnt - 1;
            }
        }

        return orig_cnt;
    }
};

int main()
{
    Solution s;
    cout << s.lengthOfLongestSubstring("wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco");
	return 0;
}

