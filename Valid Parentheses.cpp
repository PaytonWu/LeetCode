// Valid Parentheses.cpp : Defines the entry point for the console application.
//

#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        stack<char> validatingStack;
        for (string::const_iterator i = s.begin(); i != s.end(); ++i)
        {
            switch (*i)
            {
            case ')':
                if (validatingStack.empty())
                {
                    return false;
                }
                
                if (validatingStack.top() != '(')
                {
                    return false;
                }
                
                validatingStack.pop();
                break;
                
            case '}':
                if (validatingStack.empty())
                {
                    return false;
                }
                
                if (validatingStack.top() != '{')
                {
                    return false;
                }
                
                validatingStack.pop();
                break;

            case ']':
                if (validatingStack.empty())
                {
                    return false;
                }
                
                if (validatingStack.top() != '[')
                {
                    return false;
                }
                
                validatingStack.pop();
                break;

            default:
                validatingStack.push(*i);
                break;
            }
        }
        
        return validatingStack.empty();
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

