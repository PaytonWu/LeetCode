// Letter Combinations of a Phone Number.cpp : Defines the entry point for the console application.
//

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        result.clear();
        string res;
        generate(digits, 0, res);
        
        return result;
    }
private:
    vector<string> result;
    
        const char* dig2char[10] =
        {
            "",
            "",
            "abc",
            "def",
            "ghi",
            "jkl",
            "mno",
            "pqrs",
            "tuv",
            "wxyz"
        };
        
    void generate(const string& str, size_t idx, string& res)
    {
        if (idx == str.size())
        {
            result.push_back(res);
            return;
        }
        
        for (int i = 0; i < strlen(dig2char[str[idx] - '0']); ++i)
        {
            res.push_back(dig2char[str[idx] - '0'][i]);
            generate(str, idx + 1, res);
            res.pop_back();
        }
    }
};


int main()
{
	return 0;
}

