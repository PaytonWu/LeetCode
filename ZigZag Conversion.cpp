// ZigZag Conversion.cpp : Defines the entry point for the console application.
//

#include <string>
#include <vector>

using namespace std;

/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

ZigZag就是N字型的意思
*/

class Solution {
public:
    string convert(string s, int nRows) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function    

        //string result(s.length(), '\0');
        //int x = 0;

        //for (int r = 0; r < nRows; ++r)
        //{

        //    if (0 == r)
        //    {
        //        for (size_t i = 0; i < s.length(); ++i)
        //        {
        //            size_t index = (2 * nRows - 2) * i;
        //            if (index >= s.length())
        //            {
        //                break;
        //            }

        //            result[x++] = s[index];
        //        }
        //    }
        //    else if (nRows - 1 == r)
        //    {
        //        for (size_t i = 0; i < s.length(); ++i)
        //        {
        //            size_t index = 2 * i * (nRows - 1) + nRows - 1;
        //            if (index >= s.length())
        //            {
        //                break;
        //            }

        //            result[x++] = s[index];
        //        }
        //    }
        //    else
        //    {
        //        for (size_t i = 0; i < s.length(); ++i)
        //        {
        //            size_t index = i * (nRows - 1) + r;
        //            if (index >= s.length())
        //            {
        //                break;
        //            }

        //            result[x++] = s[index];
        //        }
        //    }
        //}
        //return result;

        vector<string> rowVec(nRows);
        for (size_t i = 0; i < s.length();)
        {
            for (int j = 0; j < nRows && i < s.length(); ++j, ++i)
            {
                rowVec[j].push_back(s[i]);
            }

            for (int j = nRows - 2; j > 0 && i < s.length(); --j, ++i)
            {
                rowVec[j].push_back(s[i]);
            }
        }

        string res;
        for (size_t i = 0; i < rowVec.size(); ++i)
        {
            res += rowVec[i];
        }

        return res;
    }
};

int main()
{
    Solution s;
    printf("%s\n", s.convert("PAYPALISHIRING", 2).c_str());

	return 0;
}

