// String to Integer (atoi).cpp : Defines the entry point for the console application.
//

#include <cstring>
#include <cctype>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int atoi(const char *str) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int i = 0;
        for (; i < strlen(str); ++i)
        {
            if (!isspace(str[i]))
            {
                break;
            }
        }

        bool negtive = false;
        if ('-' == str[i])
        {
            negtive = true;
        }

        if (negtive || '+' == str[i])
        {
            ++i;
        }

        int maxval = INT_MAX / 10;

        int result = 0;
        for (; i < strlen(str); ++i)
        {
            if (isdigit(str[i]))
            {
                if (result < maxval || (result == maxval && str[i] - '0' <= INT_MAX % 10))
                {
                    result *= 10;
                    result += str[i] - '0';
                }
                else
                {
                    return negtive ? INT_MIN : INT_MAX;
                }
            }
            else
            {
                break;
            }
        }

        return negtive ? -result : result;
    }
};

int main()
{
    Solution s;
    int result = s.atoi("2147483648");
	return 0;
}

