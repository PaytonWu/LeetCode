// Best Time to Buy and Sell Stock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>

using namespace std;

// 这道题的意思是，只做一次买卖，使得差价最大。
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (prices.size() == 0)
        {
            return 0;
        }

        int result = 0;
        int buy_price = prices[0];
        for (size_t i = 0; i < prices.size(); ++i)
        {
            if (prices[i] < buy_price)
            {
                buy_price = prices[i];
            }

            result = max(result, prices[i] - buy_price);
        }

        return result;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

