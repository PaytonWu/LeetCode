// Sudoku Solver.cpp : Defines the entry point for the console application.
//

#include <vector>

using namespace std;

class Solution {
public:
    bool solveSudoku(vector<vector<char> >& board, int idx)
    {
        if (idx == 81)
        {
            return true;
        }

        int row = idx / 9;
        int col = idx % 9;

        if ('.' != board[row][col])
        {
            if (solveSudoku(board, idx + 1))
            {
                return true;
            }
        }
        else
        {
            vector<bool> validValues(9, true);
            for (int i = 0; i < 9; ++i)
            {
                if ('.' != board[row][i])
                {
                    validValues[board[row][i] - '1'] = false;
                }

                if ('.' != board[i][col])
                {
                    validValues[board[i][col] - '1'] = false;
                }
            }

            int row_range_begin = row / 3 * 3;
            int col_range_begin = col / 3 * 3;

            for (int j = row_range_begin; j < row_range_begin + 3; ++j)
            {
                for (int k = col_range_begin; k < col_range_begin + 3; ++k)
                {
                    if ('.' != board[j][k])
                    {
                        validValues[board[j][k] - '1'] = false;
                    }
                }
            }

            for (size_t i = 0; i < validValues.size(); ++i)
            {
                if (validValues[i])
                {
                    board[row][col] = static_cast<char>('1' + i);
                    if (solveSudoku(board, idx + 1))
                    {
                        return true;
                    }
                }
            }
            board[row][col] = '.';
        }

        return false;
    }
    void solveSudoku(vector<vector<char> > &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        solveSudoku(board, 0);
    }
};

int main()
{
	return 0;
}

