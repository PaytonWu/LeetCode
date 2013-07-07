// Permutations.cpp : Defines the entry point for the console application.
//

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        for (vector<vector<int> >::iterator i = result.begin(); i != result.end(); ++i)
        {
            i->clear();
        }
        result.clear();
        
        permute(num, 0);
        
        return result;
    }
private:
    vector<vector<int> > result;
    
    void permute(vector<int>& n, int idx)
    {
        if (idx == n.size())
        {
            result.push_back(n);
            return;
        }
        
        for (int i = idx; i < n.size(); ++i)
        {
            swap(n[i], n[idx]);
            permute(n, idx + 1);
            swap(n[i], n[idx]);
        }
    }
};

int main()
{
	return 0;
}

