#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution3 {
public:

    int length;
    void dfs(const string& start, const string& end, unordered_set<string>& dict, int level)
    {
        if (start == end)
        {
            if (level + 1 < length)
            {
                length = level + 1;
            }
            return;
        }

        if (dict.size() == 0)
        {
            return;
        }

        string tmp = start;
        for (size_t i = 0; i < tmp.length(); ++i)
        {
            for (char ch = 'a'; ch <= 'z'; ++ch)
            {
                if (tmp[i] == ch)
                {
                    continue;
                }

                char backup = tmp[i];
                tmp[i] = ch;
                if (dict.find(tmp) != dict.end())
                {
                    dict.erase(tmp);
                    dfs(tmp, end, dict, level + 1);
                    dict.insert(tmp);
                }
                tmp[i] = backup;
            }
        }
    }

    int ladderLength(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        // initGraph(dict, start, end);
        length = INT_MAX;
        dfs(start, end, dict, 0);
        return length == INT_MAX ? 0 : length;
    }
};