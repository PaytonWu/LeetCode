// Reverse Integer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Solution {
public:
    int reverse(int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        bool negtive = (x < 0);
        if (negtive)
        {
            x = -x;
        }

        int result = 0;
        for (; x > 0; x /= 10)
        {
            result *= 10;
            result += x % 10;
        }

        return negtive ? -result : result;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

