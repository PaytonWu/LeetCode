// Valid Palindrome.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <cctype>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s.length() == 0)
        {
            return true;
        }

        size_t i = 0, j = s.length() -1;
        while (i < j)
        {
            if (!isalnum(s[i]))
            {
                ++i;
                continue;
            }

            if (!isalnum(s[j]))
            {
                --j;
                continue;
            }

            if (tolower(s[i++]) != tolower(s[j--]))
            {
                return false;
            }
        }

        return true;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

