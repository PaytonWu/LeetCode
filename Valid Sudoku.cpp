// Valid Sudoku.cpp : Defines the entry point for the console application.
//

#include <vector>
using namespace std;


class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        for (int i = 0; i < 81; ++i)
        {
            int row = i / 9;
            int col = i % 9;

            if (board[row][col] != '.')
            {
                continue;
            }

            vector<short> valid(9);
            
            // using i as row num;
            for (int j = 0; j < 9; ++j)
            {
                if (board[row][j] != '.')
                {
                    if (++valid[board[row][j] - '1'] > 1)
                    {
                        return false;
                    }
                }
            }

            for (int j = 0; j < 9; ++j)
            {
                valid[j] = 0;
            }

            // using i as col num;
            for (int j = 0; j < 9; ++j)
            {
                if (board[j][col] != '.')
                {
                    if (++valid[board[j][col] - '1'] > 1)
                    {
                        return false;
                    }
                }
            }

            for (int j = 0; j < 9; ++j)
            {
                valid[j] = 0;
            }

            int row_range_start = row / 3 * 3;
            int col_range_start = col / 3 * 3;
            
            for (int j = row_range_start; j < row_range_start + 3; ++j)
            {
                for (int k = col_range_start; k < col_range_start + 3; ++k)
                {
                    if (board[j][k] != '.')
                    {
                        if (++valid[board[j][k] - '1'] > 1)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};

int main()
{
    //    012345678
    //0: "53..7....",
    //1: "6..195...",
    //2: ".98....6.",
    //3: "8...6...3",
    //4: "4..8.3..1",
    //5: "7...2...6",
    //6: ".6....28.",
    //7: "...419..5",
    //8: "....8..79"]
    vector<vector<char>> board(9, vector<char>(9, '.'));
    board[0][0] = '5', board[0][1] = '3', board[0][4] = '7';
    board[1][0] = '6', board[1][3] = '1', board[1][4] = '9', board[1][5] = '5';
    board[2][1] = '9', board[2][2] = '8', board[2][7] = '6';
    board[3][0] = '8', board[3][4] = '6', board[3][8] = '3';
    board[4][0] = '4', board[4][3] = '8', board[4][5] = '3', board[4][8] = '1';
    board[5][0] = '7', board[5][4] = '2', board[5][8] = '6';
    board[6][1] = '6', board[6][6] = '2', board[6][7] = '8';
    board[7][3] = '4', board[7][4] = '1', board[7][5] = '9', board[7][8] = '5';
    board[8][4] = '8', board[8][7] = '7', board[8][8] = '9';
    Solution s;
    bool b = s.isValidSudoku(board);
	return 0;
}

