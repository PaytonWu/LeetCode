// Palindrome Partitioning II.cpp : Defines the entry point for the console application.
//
/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
 Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/
#include <cstdio>
#include <string>

using namespace std;

class Solution
{
public:
    int minCut(string s)
    {
        size_t len = s.size();
        
        size_t** dp = new size_t*[len];
        unsigned char** plindrome = new unsigned char*[len];
        for (size_t i = 0; i < len; ++i)
        {
            dp[i] = new size_t[len];
            plindrome[i] = new unsigned char[len];

            memset(dp[i], static_cast<size_t>(-1), sizeof(size_t) * len);
            memset(plindrome[i], static_cast<size_t>(-1), sizeof(unsigned char) * len);
            dp[i][i] = 0;
        }
        
        int result = static_cast<int>(minCut(s.c_str(), 0, len, dp, plindrome));
        
        for (size_t i = 0; i < len; ++i)
        {
            delete[] dp[i];
            delete[] plindrome[i];
        }
        
        delete[] dp;
        delete[] plindrome;
        
        return result;
    }

private:
    bool IsPlindrome(const char* str, int s, int e, unsigned char** plindrome)
    {
        if (static_cast<unsigned char>(-1) != plindrome[s][e-1])
        {
            return static_cast<bool>(plindrome[s][e-1]);
        }

        int start = s, end = e;
        while (s < e)
        {
            if (str[s++] != str[--e])
            {
                plindrome[start][end-1] = static_cast<unsigned char>(false);
                return false;
            }
        }
        plindrome[start][end-1] = static_cast<unsigned char>(true);
        return true;
    }

    size_t minCut(const char* str, size_t s, size_t e, size_t** dp, unsigned char** plindrome)
    {
        if (static_cast<size_t>(-1) != dp[s][e-1])
        {
            return dp[s][e-1];
        }

        if (IsPlindrome(str, s, e, plindrome))
        {
            dp[s][e-1] = 0;
            return 0;
        }

        size_t mincut = static_cast<size_t>(-1);
        for (size_t k = 1; k < e - s; ++k)
        {
            unsigned candidate = minCut(str, s, s+k, dp, plindrome) + minCut(str, s+k, e, dp, plindrome) + 1;
            if (candidate < mincut)
            {
                mincut = candidate;
            }
        }

        dp[s][e-1] = mincut;
        return mincut;
    }
};

//             +--  0   // str[i, j+1) is plindrome
//             |
// cut[i][j] = +
//             |
//             +--  min(cut[i][k] + cut[k+1][j]) where i <= k < j
class Solution2
{
public:
    int minCut(string s)
    {
        size_t len = s.length();

        if (s.length() <= 1)
        {
            return 0;
        }

        size_t** dp = new size_t*[len];
        for (size_t i = 0; i < len; ++i)
        {
            dp[i] = new size_t[len];
            for (size_t j = 0; j < len; ++j)
            {
                dp[i][j] = len - 1;
            }
            dp[i][i] = 0;
        }

        for (size_t k = 2; k <= len; ++k)   // bottom-up, substring length.
        {
            for (size_t i = 0; i + k <= len; ++i)
            {
                int j = i + k;
                if (isPlindrome(s, i, j))
                {
                    dp[i][j-1] = 0;
                    continue;
                }

                for (size_t x = i + 1; x < j; ++x)
                {
                    size_t candidation = dp[i][x - 1] + dp[x][j-1] + 1;
                    if (candidation < dp[i][j-1])
                    {
                        dp[i][j-1] = candidation;
                    }
                }
            }
        }

        size_t res = dp[0][len - 1];

        for (size_t i = 0; i < len; ++i)
        {
            delete[] dp[i];
        }

        delete [] dp;

        return res;
    }

private:
    bool isPlindrome(const string& str, int s, int e)
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

// min[0,j):
//  a: [0,j)是回文 返回0
//  b: [0,j)非回文 min([0, k), [k, j)) + 1, where 0 < k < j, 
class Solution3
{
public:
    int minCut(const string& s)
    {
        size_t len =s.size();

        if (len <= 1)
        {
            return 0;
        }

        size_t* dp = new size_t[len];
        for (size_t i = 0; i < len; ++i)
        {
            dp[i] = len - 1;
        }

        unsigned char** plindrome = new unsigned char*[len];
        for (size_t i = 0; i < len; ++i)
        {
            plindrome[i] = new unsigned char[len];
            memset(plindrome[i], static_cast<size_t>(-1), sizeof(unsigned char) * len);
        }

        for (size_t subStringLen = 1; subStringLen <= len; ++subStringLen)
        {
            if (isPlindrome2(s, 0, subStringLen, plindrome))
            {
                dp[subStringLen - 1] = 0;
                continue;
            }

            size_t least = static_cast<size_t>(-1);
            for (size_t k = 0; k + 1 < subStringLen; ++k)
            {
                size_t tmp = len - 1;
                if (isPlindrome2(s, k + 1, subStringLen, plindrome))
                {
                    tmp = dp[k] + 1;
                }
                else
                {
                    tmp = dp[k] + subStringLen - k;
                }

                if (tmp < least)
                {
                    least = tmp;
                }
            }
            dp[subStringLen - 1] = least;
        }

        size_t result = dp[len - 1];

        delete dp;
        for (size_t i = 0; i < len; ++i)
        {
            delete[] plindrome[i];
        }
        delete[] plindrome;

        return result;
    }

private:
    bool isPlindrome2(const string& str, size_t s, size_t e, unsigned char** plindrome)
    {
        if (static_cast<unsigned char>(-1) != plindrome[s][e-1])
        {
            return static_cast<bool>(plindrome[s][e-1]);
        }

        size_t start = s, end = e;
        while (s < e)
        {
            if (str[s++] != str[--e])
            {
                for (size_t i = start; i < s; ++i)
                {
                    plindrome[i][--end] = static_cast<unsigned char>(false);
                }
                // plindrome[start][end-1] = static_cast<unsigned char>(false);
                return false;
            }
        }
        for (size_t i = start; i < s; ++i)
        {
            plindrome[i][--end] = static_cast<unsigned char>(true);
        }
        return true;
    }

    bool isPlindrome(const string& str, size_t s, size_t e, unsigned char** plindrome)
    {
        if (e < s) return false;

        if (static_cast<unsigned char>(-1) != plindrome[s][e-1])
        {
            return static_cast<bool>(plindrome[s][e-1]);
        }

        if (1 == e - s)
        {
            plindrome[s][e-1] = static_cast<unsigned char>(true);
            return true;
        }

        if (str[s] != str[e-1])
        {
            plindrome[s][e-1] = static_cast<unsigned char>(false);
            return false;
        }

        if (s == e)
        {
            return true;
        }

        plindrome[s][e-1] = isPlindrome(str, s+1, e-1, plindrome);
        return plindrome[s][e-1];
        //int start = s, end = e;
        //while (s < e)
        //{
        //    if (str[s++] != str[--e])
        //    {
        //        plindrome[start][end-1] = static_cast<unsigned char>(false);
        //        return false;
        //    }
        //}
        //plindrome[start][end-1] = static_cast<unsigned char>(true);
        //return true;
    }
};


int main()
{
    char str[4096];
    while (EOF != scanf("%s", str))
    {
        Solution3 s;

        printf("%u\n", s.minCut(str));
    }
	return 0;
}

