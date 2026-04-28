#include "game.h"
#include "luu_tai_game.h"
#include "bang_xep_hang.h"
#include <conio.h>

int main() {
    setupWindowsConsole();
    
    // ================= MỤC 2: NHẬP TÊN NGƯỜI CHƠI =================
    char player1[50], player2[50];
    printf("%s", ANSI_CLEAR);
    printf("        --- CHAO MUNG DEN VOI CARO ---\n\n");
    printf(" Nhap ten Nguoi choi 1 (Quan X): ");
    scanf("%49s", player1);
    printf(" Nhap ten Nguoi choi 2 (Quan O): ");
    scanf("%49s", player2);

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
        printf("=== CARO %dx%d | %s (X) vs %s (O) ===\n", currentSize, currentSize, player1, player2);
        displayBoard(board, currentSize, cursorRow, cursorCol);
        drawStatusBar(cursorCol, cursorRow, 0);

        printf("\n[S]: Luu Game | [U]: Hoan tac | [Space/Enter]: Danh");

        int ch = _getch();
        if (ch == 224) { 
            ch = _getch();
            if (ch == 72 && cursorRow > 0) cursorRow--;
            if (ch == 80 && cursorRow < currentSize - 1) cursorRow++;
            if (ch == 75 && cursorCol > 0) cursorCol--;
            if (ch == 77 && cursorCol < currentSize - 1) cursorCol++;
        } 
        else if (ch == 's' || ch == 'S') {
            // ================= TÍCH HỢP LƯU GAME =================
            TrangThaiVanCo data;
            strcpy(data.nguoi_choi_1.ten, player1);
            strcpy(data.nguoi_choi_2.ten, player2);
            data.kich_thuoc_thuc_te = currentSize; 
            data.luot_hien_tai = currentPlayer;
            data.so_nuoc_da_di = history.top + 1;
            
            for(int i = 0; i < BOARD_SIZE; i++)
                for(int j = 0; j < BOARD_SIZE; j++)
                    data.ban_co[i][j] = board[i][j];
                    
            for(int i = 0; i <= history.top; i++)
                data.lich_su_nuoc_di[i] = history.data[i];

            if(luu_van_co(&data, FILE_LUU_GAME)) {
                printf("\nDa luu game thanh cong! Nhan phim bat ky de tiep tuc...");
                _getch();
            }
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
                    
                    // Xác định ai là người thắng
                    char* winnerName = (currentPlayer == STONE_X) ? player1 : player2;
                    char* loserName = (currentPlayer == STONE_X) ? player2 : player1;
                    
                    printf("\nCHUC MUNG %s [%c] THANG!\n", winnerName, currentPlayer);
                    
                    // ================= TÍCH HỢP BẢNG XẾP HẠNG =================
                    cap_nhat_ket_qua(winnerName, loserName, NULL, NULL, 0);

                    gameRunning = false;
                }
                currentPlayer = (currentPlayer == STONE_X) ? STONE_O : STONE_X;
            }
        }
    }
    
    printf("\nNhan phim bat ky de xem Bang Xep Hang...");
    _getch();
    printf("%s", ANSI_CLEAR);
    hien_thi_bang_xep_hang(); // In bảng xếp hạng ra
    
    printf("\nNhan phim bat ky de thoat...");
    _getch();
    return 0;
}
