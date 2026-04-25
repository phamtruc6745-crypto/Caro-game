#include <string.h>
#include <conio.h> 
#include "../include/game.h"

int main() {
    setupWindowsConsole(); 
    
    ScoreBoard globalScore;
    loadScore(&globalScore);
    
    // --- 1. HIEN THI MENU VA LAY KICH THUOC DA CHON ---
    int currentSize = showSplashScreen(); // Se nhan ve 3, 5, hoac 15
    
    // --- 2. KHOI TAO BAN CO ---
    // Khai bao mang voi kich thuoc toi da la BOARD_SIZE (15) de tranh loi bo nho
    Stone board[BOARD_SIZE][BOARD_SIZE]; 
    initBoard(board, currentSize); // Truyen currentSize vao de chi khoi tao vung choi
        
    Move history[BOARD_SIZE * BOARD_SIZE];
    int moveCount = 0; 
    // So nuoc di toi da bay gio phu thuoc vao kich thuoc ban co da chon
    int maxMoves = currentSize * currentSize; 
    
    Stone currentPlayer = BLACK; 
    bool gameRunning = true;
    
    // Dat con tro o giua ban co hien tai
    int cursorRow = currentSize / 2;
    int cursorCol = currentSize / 2;
    
    // Khai bao bien thoi gian tam thoi de chuan bi cho ham thanh trang thai
    int timeLeft = 0;
    
    while (gameRunning && moveCount < maxMoves) {
        // --- RENDER ---
        printf("%s", ANSI_CLEAR);
        printf("=== GAME CO CARO %dx%d (DIEU KHIEN MUI TEN) ===\n\n", currentSize, currentSize);
        
        // Truyen currentSize de chi ve dung kich thuoc can thiet
        displayBoard(board, currentSize, cursorRow, cursorCol);
        
        char playerChar = (currentPlayer == BLACK) ? 'X' : 'O';
        const char *playerColor = (currentPlayer == BLACK) ? ANSI_RED : ANSI_CYAN;
        
        printf("\n%s[BANG DIEM]%s Den (X): %d  |  Trang (O): %d  |  Hoa: %d\n", 
               ANSI_YELLOW, ANSI_RESET, 
               globalScore.blackWins, globalScore.whiteWins, globalScore.draws);
               
        printf("%s[Thong tin]%s So nuoc da di: %d/%d\n", ANSI_YELLOW, ANSI_RESET, moveCount, maxMoves);
        printf("Luot cua quan %s[%c]%s. Dung MUI TEN di chuyen, SPACE hoac ENTER de danh, 'U' hoan tac.\n", playerColor, playerChar, ANSI_RESET);
        
        // B2 cua ham thanh trang thai 
        drawStatusBar(cursorCol, cursorRow, timeLeft); // Luu y: cursorCol la X, cursorRow la Y
        
        // --- INPUT ---
        int ch = _getch(); 
        
        if (ch == 224 || ch == 0) { 
            ch = _getch();
            // Ngan khong cho con tro chay ra khoi currentSize
            if (ch == 72 && cursorRow > 0) cursorRow--;          
            else if (ch == 80 && cursorRow < currentSize - 1) cursorRow++;   
            else if (ch == 75 && cursorCol > 0) cursorCol--;          
            else if (ch == 77 && cursorCol < currentSize - 1) cursorCol++;   
            continue; 
        } 
        else if (ch == 'u' || ch == 'U') {
            if (moveCount > 0) {
                moveCount--; 
                Move lastMove = history[moveCount];
                board[lastMove.row][lastMove.col] = NA; 
                currentPlayer = lastMove.player;
                
                cursorRow = lastMove.row;
                cursorCol = lastMove.col;
            }
            continue;
        }
        else if (ch == 13 || ch == 32) { 
            if (board[cursorRow][cursorCol] != NA) {
                continue; 
            }
            
            // --- UPDATE LOGIC ---
            board[cursorRow][cursorCol] = currentPlayer;
            
            history[moveCount].row = cursorRow;
            history[moveCount].col = cursorCol;
            history[moveCount].player = currentPlayer;
            moveCount++;
            
            // Truyen currentSize vao de ham checkWinner kiem tra dieu kien thang phu hop
            if (checkWinner(board, currentSize, cursorRow, cursorCol, currentPlayer)) {
                printf("%s", ANSI_CLEAR);
                printf("=== GAME CO CARO %dx%d (DIEU KHIEN MUI TEN) ===\n\n", currentSize, currentSize);
                displayBoard(board, currentSize, cursorRow, cursorCol);
                printf("\nCHUC MUNG! Quan %s[%c]%s da gianh chien thang!\n", playerColor, playerChar, ANSI_RESET);
                // ve lai thanh trang thai da bi xoa o truoc
                drawStatusBar(cursorCol, cursorRow, timeLeft);
                
                updateScore(&globalScore, currentPlayer);
                gameRunning = false; 
                continue;
            }

            currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
        }
    }
    
    if (moveCount == maxMoves && gameRunning == true) {
        printf("%s", ANSI_CLEAR);
        displayBoard(board, currentSize, cursorRow, cursorCol);
        printf("\nBan co da kin, Tran dau Hoa!\n");
        
        // ve lai thanh trang thai da bi xoa o truoc
        drawStatusBar(cursorCol, cursorRow, timeLeft);
        
        updateScore(&globalScore, NA);
    }
    
    printf("\nTro choi ket thuc. Cam on ban da choi!\n");
    return 0;
}
