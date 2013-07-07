// Pow(x, n).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Solution {
public:
    double pow(double x, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (1 == n)
        {
            return x;
        }

        if (0 == n)
        {
            return 1.0;
        }
        
        if (n < 0)
        {
            x = 1 / x;
            n = -n;
        }
        
        if (n & 1)
        {
            return x * this->pow(x * x, n / 2);
        }
        else
        {
            return this->pow(x * x, n / 2);
        }
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

