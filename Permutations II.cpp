// Permutations II.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        for (vector<vector<int> >::iterator i = result.begin(); i != result.end(); ++i)
        {
            i->clear();
        }
        result.clear();
        sort(num.begin(), num.end());

        map<int, map<int, bool>> bits;
        permute(num, 0, bits);
        
        return result;
    }
private:
    vector<vector<int> > result;
    
    void permute(vector<int>& n, int idx, map<int, map<int, bool>>& bits)
    {
        if (idx == n.size())
        {
            result.push_back(n);
            return;
        }
        
        for (int i = idx; i < n.size(); ++i)
        {
            if (bits[idx][n[i]])
            {
                continue;
            }

            bits[idx][n[i]] = true;

            swap(n[i], n[idx]);
            permute(n, idx + 1, bits);
            swap(n[i], n[idx]);
        }

        bits[idx].clear();
    }
};

int main()
{
    vector<int> v;
    v.push_back(-1);
    v.push_back(2);
    v.push_back(-1);
    v.push_back(2);
    v.push_back(1);


    Solution s;
    const vector<vector<int>>& res = s.permuteUnique(v);
    for (auto i = res.begin(); i != res.end(); ++i)
    {
        for (auto j = i->begin(); j != i->end(); ++j)
        {
            printf("%d,", *j);
        }
        printf("\n");
    }
	return 0;
}

