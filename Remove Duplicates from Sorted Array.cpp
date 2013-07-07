// Remove Duplicates from Sorted Array.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Solution {
public:
    int removeDuplicates(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n <= 1)
        {
            return n;
        }
        
        int i = 0;
        for (; i < n; ++i)
        {
            int j = i + 1;
            int gap = j - i;
            
            for (; j < n; ++j)
            {
                if (A[i] == A[j])
                {
                    continue;
                }
                
                gap = j - i;
                if (gap == 1)
                {
                    break;
                }

                // move elements forward...
                for (; j < n; ++j)
                {
                    A[j - gap + 1] = A[j];
                }
                
                // narrow the upper bound after eniminateing the duplicates.
                n -= gap - 1;
            }
            
            // special case: duplicates appear at the tail of the array.
            if (j == n)
            {
                break;
            }
        }

        // i is the index of last unique element, thus returns plus one.
        return i+1;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

