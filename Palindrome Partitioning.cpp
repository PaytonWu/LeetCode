// Palindrome Partitioning.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <string>

using namespace std;

/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

  [
    ["aa","b"],
    ["a","a","b"]
  ]
*/

class Solution {
public:
    vector<vector<string>> partition(const string& s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<string>> result;
        vector<string> curResult;

        size_t len = s.size();
        char** dp = new char*[len];
        for (size_t i = 0; i < len; ++i)
        {
            dp[i] = new char[len];
            memset(dp[i], -1, sizeof(char)*len);
            dp[i][i] = static_cast<char>(1);
        }

        partition(s.c_str(), 0, s.length(), dp, result, curResult);

        for (size_t i = 0; i < len; ++i)
        {
            delete[] dp[i];
        }

        delete[] dp;

        return result;
    }

private:
    void partition(const char* str, size_t s, size_t e, char** dp, vector<vector<string>>& result, vector<string>& curResult)
    {
        if (s == e)
        {
            result.push_back(curResult);
        }
        else
        {
            for (size_t i = 1; s + i <= e; ++i)
            {
                if (static_cast<char>(-1) != dp[s][s+i-1] && dp[s][s+i-1])
                {
                    curResult.push_back(string(&str[s], &str[s+i]));
                    partition(str, s+i, e, dp, result, curResult);
                    curResult.pop_back();
                }
                else if (isPalindrome(str, s, s + i))
                {
                    dp[s][s+i-1] = static_cast<char>(1);
                    curResult.push_back(string(&str[s], &str[s+i]));
                    partition(str, s+i, e, dp, result, curResult);
                    curResult.pop_back();
                }
            }
        }
    }

    bool isPalindrome(const char* str, int s, int e)
    {
        while (s < e)
        {
            if (str[s++] != str[--e])
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    Solution s;
    char str[1024];
    while (EOF != scanf("%s", str))
    {
        const vector<vector<string>>& result = s.partition(str);
        for (auto iter = result.begin(); iter != result.end(); ++iter)
        {
            for (auto i = iter->begin(); i != iter->end(); ++i)
            {
                printf("%s,", i->c_str());
            }
            printf("\n");
        }
    }

	return 0;
}

