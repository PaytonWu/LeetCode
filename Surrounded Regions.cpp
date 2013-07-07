// Surrounded Regions.cpp : Defines the entry point for the console application.
//

#include <vector>

using namespace std;

class Solution {
public:
    bool is_o_valid(size_t r, size_t c, size_t row_count, size_t col_count)
    {
        if (0 == r || 0 == c || row_count == r + 1 || row_count == c + 1)
        {
            return false;
        }

        return true;
    }

    bool continueSearch(size_t row, size_t col, char ch, vector<pair<int, int>>& index, vector<pair<int, int>>& collection, vector<vector<bool>>& used)
    {
        if (used[row][col] || 'X' == ch)
        {
            return false;
        }

        index.push_back(make_pair(row, col));
        collection.push_back(make_pair(row, col));
        used[row][col] = true;

        return true;
    }

    bool collect_o(vector<vector<char>>& board, int r, int c, vector<vector<bool>>& used, vector<pair<int, int>>& all)
    {
        if (used[r][c])
        {
            return false;
        }

        all.clear();
        bool shouldFillX = true;

        vector<pair<int, int>> index;

        index.push_back(make_pair(r, c));
        all.push_back(make_pair(r, c));
        used[r][c] = true;

        while (!index.empty())
        {
            pair<int, int> cell = index.back();
            index.pop_back();

            if (shouldFillX && !is_o_valid(cell.first, cell.second, board.size(), board[cell.first].size()))
            {
                shouldFillX = false;
            }

            // search up
            for (int row = cell.first - 1; row >= 0; --row)
            {
                if (!continueSearch(row, cell.second, board[row][cell.second], index, all, used))
                {
                    break;
                }
            }

            // search down
            for (size_t row = cell.first + 1; row < board.size(); ++row)
            {
                if (!continueSearch(row, cell.second, board[row][cell.second], index, all, used))
                {
                    break;
                }
            }

            // search left
            for (int col = cell.second - 1; col >= 0; --col)
            {
                if (!continueSearch(cell.first, col, board[cell.first][col], index, all, used))
                {
                    break;
                }
            }

            // search right
            for (size_t col = cell.second + 1; col < board[cell.first].size(); ++col)
            {
                if (!continueSearch(cell.first, col, board[cell.first][col], index, all, used))
                {
                    break;
                }
            }
        }

        return shouldFillX;
    }

    void fill(vector<vector<char>>& board, const vector<pair<int, int>>& collection)
    {
        for (auto i = collection.begin(); i != collection.end(); ++i)
        {
            board[i->first][i->second] = 'X';
        }
    }

    void solve(vector<vector<char>> &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<bool>> used(board.size());
        auto vi = used.begin();
        for (auto i = board.begin(); i != board.end() && vi != used.end(); ++i, ++vi)
        {
            vi->resize(i->size());
        }

        size_t rowSize = board.size();
        if (rowSize < 3)
        {
            return;
        }

        vector<pair<int, int>> T;
        for (size_t i = 1; i < rowSize; ++i)
        {
            for (size_t j = 1; j < board[i].size(); ++j)
            {
                if (board[i][j] == 'O')
                {
                    if (collect_o(board, i, j, used, T))
                    {
                        fill(board, T);
                    }
                }
            }
        }
    }
};

int main()
{
    vector<vector<char>> board(5, vector<char>(5, 'X'));
    board[0][0] = board[0][3] = 'O';
    board[1][1] = board[1][2] = board[1][4] = 'O';
    board[2][1] = board[2][3] = 'O';
    board[3][0] = board[3][2] = board[3][3] = board[3][4] = 'O';
    board[4][2] = board[4][4] = 'O';

    Solution s;
    s.solve(board);
	return 0;
}

