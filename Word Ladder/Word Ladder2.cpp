#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <deque>

using namespace std;

class Solution2 {
public:
    static inline int getDistance(const string& w1, const string& w2)
    {
        int distance = 0;
        for (size_t i = 0; i < w1.length(); ++i)
        {
            if (w1[i] != w2[i])
            {
                if (++distance == 2)
                {
                    break;
                }
            }
        }

        return distance;
    }

    typedef string                                      vertex;
    typedef vector<vertex>                              vertex_collection;

    int bfs(const string& start, const string& end, unordered_set<string>& dict)
    {
        unordered_set<string> unused;
        vector<vertex> level;
        vector<vertex> nextlevel;

        level.push_back(start);
        int length = 0;
        while (!level.empty())
        {
            ++length;
            for (auto i = level.begin(); i != level.end(); ++i)
            {
                vertex v = *i;

                if (v == end)
                {
                    return length;
                }

                for (auto j = dict.begin(); j != dict.end(); ++j)
                {
                    const vertex& c = *j;
                    if (1 == getDistance(v, c) && unused.find(c) == unused.end())
                    {
                        nextlevel.push_back(c);
                        unused.insert(c);
                    }
                }
            }

            swap(level, nextlevel);
            nextlevel.erase(nextlevel.begin(), nextlevel.end());
        }

        return 0;
    }

    int ladderLength(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        return bfs(start, end, dict);
    }
};
