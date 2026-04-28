#include "../include/game.h"
#include <conio.h>

int main() {
    setupWindowsConsole();
    
    // 1. Load bảng điểm từ file 
    ScoreBoard globalScore = {0, 0, 0}; 
    // loadScore(&globalScore); // Bỏ comment khi bạn đã sửa xong file luu_tai_game.c

    int currentSize = showSplashScreen();
    
    Stone board[BOARD_SIZE][BOARD_SIZE];
    initBoard(board, currentSize);
    
    Stack history;
    initStack(&history);
    
    int moveCount = 0;
    int maxMoves = currentSize * currentSize;
    Stone currentPlayer = STONE_X;
    int cursorRow = currentSize / 2, cursorCol = currentSize / 2;
    bool gameRunning = true;

    while (gameRunning && moveCount < maxMoves) {
        printf("%s", ANSI_CLEAR);
        printf("=== CARO %dx%d | X: %d - O: %d ===\n", currentSize, currentSize, globalScore.blackWins, globalScore.whiteWins);
        displayBoard(board, currentSize, cursorRow, cursorCol);
        drawStatusBar(cursorCol, cursorRow, 0);

        printf("\n[S]: Luu Game | [U]: Hoan tac | [Space]: Danh");

        int ch = _getch();
        if (ch == 224) { 
            ch = _getch();
            if (ch == 72 && cursorRow > 0) cursorRow--;
            if (ch == 80 && cursorRow < currentSize - 1) cursorRow++;
            if (ch == 75 && cursorCol > 0) cursorCol--;
            if (ch == 77 && cursorCol < currentSize - 1) cursorCol++;
        } 
        else if (ch == 's' || ch == 'S') {
            // Gọi hàm luu_game 
            printf("\nDang luu game...");
            // luu_van_co(...); 
            _getch();
        }
        else if (ch == 'u' || ch == 'U') {
            Move m;
            if (popMove(&history, &m)) {
                board[m.row][m.col] = STONE_NA;
                moveCount--;
                currentPlayer = m.player;
                cursorRow = m.row; cursorCol = m.col;
            }
        }
        else if (ch == 13 || ch == 32) { 
            if (board[cursorRow][cursorCol] == STONE_NA) {
                board[cursorRow][cursorCol] = currentPlayer;
                Move m = {cursorRow, cursorCol, currentPlayer};
                pushMove(&history, m);
                moveCount++;

                if (checkWinner(board, currentSize, cursorRow, cursorCol, currentPlayer)) {
                    printf("%s", ANSI_CLEAR);
                    displayBoard(board, currentSize, cursorRow, cursorCol);
                    printf("\nCHUC MUNG %s [%c] THANG!\n", (currentPlayer == STONE_X) ? "RED" : "CYAN", currentPlayer);
                    
                    // Cập nhật bảng điểm
                    if (currentPlayer == STONE_X) globalScore.blackWins++;
                    else globalScore.whiteWins++;
                    // saveScore(globalScore);

                    gameRunning = false;
                }
                currentPlayer = (currentPlayer == STONE_X) ? STONE_O : STONE_X;
            }
        }
    }
    printf("\nNhan phim bat ky de ket thuc...");
    _getch();
    return 0;
}
