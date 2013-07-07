// Best Time to Buy and Sell Stock II.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

using namespace std;

// this problem is interesting.  when we buy a stock on day i and sell it on day j, the profit we
// got is prices[j] - prices[i].  asume that there a n days betwee day i and day j, then we see that
// if we buy on day i and sell it on day (i + 1) meanwhile we buy one stock on day (i + 1), and repeat
// the behavour day by day till day j.  This logical means we by a stock each day and sell it in the
// next day.  In this way, the profile we got is:
// (prices[i + 1] - price[i]) + (prices[i + 2] - prices[i + 1] + ... + (prices[j - 1] - prices[j - 2]) + (prices[j] - prices[j - 1])
// which equals: prices[j] - prices[i].
// so the profit we got by buying on day i and selling on day j is equal to that we buy and sell on each day with continous actions.
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int result = 0;
        for (size_t i = 0; i + 1 < prices.size(); ++i)
        {
            int diff = prices[i + 1] - prices[i];
            if (diff > 0)
            {
                result += diff;
            }
        }

        return result;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

