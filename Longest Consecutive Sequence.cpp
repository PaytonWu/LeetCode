// Longest Consecutive Sequence.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        unordered_set<int>  set;
        for (auto i = num.begin(); i != num.end(); ++i)
        {
            set.insert(*i);

        }

        int cnt = 1;
        for (auto i = num.begin(); i != num.end(); ++i)
        {
            int tmp = 1;
            if (set.find(*i) != set.end())
            {
                set.erase(*i);

                int j = *i;
                while (set.find(++j) != set.end())
                {
                    ++tmp;
                    set.erase(j);
                }
                j = *i;
                while (set.find(--j) != set.end())
                {
                    ++tmp;
                    set.erase(j);
                }

                if (tmp > cnt)
                {
                    cnt = tmp;
                }
            }
        }

        return cnt;
    }
};

int main()
{
    Solution s;
    vector<int> num;
    num.push_back(100);
    num.push_back(1);
    num.push_back(4);
    num.push_back(200);
    num.push_back(3);
    num.push_back(2);

    cout << s.longestConsecutive(num);
	return 0;
}

