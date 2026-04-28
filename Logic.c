#include "../include/game.h"

bool checkWinner(Stone board[BOARD_SIZE][BOARD_SIZE], int size, int row, int col, Stone player) {
    int directions[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
    
    for (int d = 0; d < 4; d++) {
        int count = 1;
        int dr = directions[d][0];
        int dc = directions[d][1];

        // Kiem tra 2 huong doi nghich
        for (int i = 1; i < 5; i++) {
            int r = row + dr * i, c = col + dc * i;
            if (r >= 0 && r < size && c >= 0 && c < size && board[r][c] == player) count++;
            else break;
        }
        for (int i = 1; i < 5; i++) {
            int r = row - dr * i, c = col - dc * i;
            if (r >= 0 && r < size && c >= 0 && c < size && board[r][c] == player) count++;
            else break;
        }
        if (count >= WIN_COUNT) return true;
    }
    return false;
}
