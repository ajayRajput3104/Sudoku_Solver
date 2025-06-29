#include <vector>

class SudokuSolver {
public:
    bool isValid(std::vector<std::vector<char>>& board, int row, int col, char ch) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == ch || 
                board[i][col] == ch || 
                board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == ch) {
                return false;
            }
        }
        return true;
    }

    bool solve(std::vector<std::vector<char>>& board, int row, int col) {
        if (row == 8 && col == 9)
            return true;

        if (col == 9) {
            row++;
            col = 0;
        }

        if (board[row][col] != '.')
            return solve(board, row, col + 1);

        for (char ch = '1'; ch <= '9'; ch++) {
            if (isValid(board, row, col, ch)) {
                board[row][col] = ch;

                if (solve(board, row, col + 1))
                    return true;

                board[row][col] = '.'; // Backtrack
            }
        }

        return false;
    }

    bool solveSudoku(std::vector<std::vector<char>>& board) {
        return solve(board, 0, 0);
    }
};
