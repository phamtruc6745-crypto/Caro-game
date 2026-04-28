#include <stdio.h>
#include <string.h>
#include <conio.h> 
#include "../include/game.h"
#include "../include/luu_tai_game.h"
#include "../include/bang_xep_hang.h"

/* ================================================================
 * main.c
 * Chuc nang: Vong lap game chinh, dieu phoi giao dien va logic.
 * ================================================================ */

int main() {
    setupWindowsConsole(); 
    
    // --- 1. KHOI TAO "TRAI TIM" CUA GAME ---
    TrangThaiVanCo van_co;
    memset(&van_co, 0, sizeof(TrangThaiVanCo)); 
    
    // Thiet lap ten mac dinh cho 2 nguoi choi (Co the nang cap cho phep nhap ten sau)
    strncpy(van_co.nguoi_choi_1.ten, "Nguoi Choi 1", DO_DAI_TEN_TOI_DA - 1);
    van_co.nguoi_choi_1.ky_hieu = 'X';
    strncpy(van_co.nguoi_choi_2.ten, "Nguoi Choi 2", DO_DAI_TEN_TOI_DA - 1);
    van_co.nguoi_choi_2.ky_hieu = 'O';
    
    // --- 2. HIEN THI MENU VA LAY KICH THUOC DA CHON ---
    int currentSize = showSplashScreen(); // Tra ve 3, 5, hoac 15
    
    // Khai bao ban co va cac thong so co ban
    initBoard(van_co.ban_co, currentSize);
    van_co.luot_hien_tai = 'X'; // X luon di truoc
    van_co.so_nuoc_da_di = 0;
    van_co.game_da_ket_thuc = 0;
    
    int maxMoves = currentSize * currentSize; 
    bool gameRunning = true;
    
    // Dat con tro o giua ban co hien tai
    int cursorRow = currentSize / 2;
    int cursorCol = currentSize / 2;
    int timeLeft = 0; // Thoi gian hien thi tam thoi
    
    // --- 3. VONG LAP GAME CHINH ---
    while (gameRunning && van_co.so_nuoc_da_di < maxMoves) {
        
        // Render Giao Dien
        printf("%s", ANSI_CLEAR);
        printf("=== GAME CO CARO %dx%d (DIEU KHIEN MUI TEN) ===\n\n", currentSize, currentSize);
        
        displayBoard(van_co.ban_co, currentSize, cursorRow, cursorCol);
        
        char playerChar = van_co.luot_hien_tai;
        const char *playerColor = (playerChar == 'X') ? ANSI_RED : ANSI_CYAN;
               
        printf("\n%s[Thong tin]%s So nuoc da di: %d/%d\n", ANSI_YELLOW, ANSI_RESET, van_co.so_nuoc_da_di, maxMoves);
        printf("Luot cua quan %s[%c]%s. Dung MUI TEN di chuyen, SPACE hoac ENTER de danh, 'U' hoan tac.\n", playerColor, playerChar, ANSI_RESET);
        
        drawStatusBar(cursorCol, cursorRow, timeLeft); 
        
        // Xu ly Input (Ban Phim)
        int ch = _getch(); 
        
        if (ch == 224 || ch == 0) { 
            // Dieu khien con tro khong vuot qua currentSize
            ch = _getch();
            if (ch == 72 && cursorRow > 0) cursorRow--;          
            else if (ch == 80 && cursorRow < currentSize - 1) cursorRow++;   
            else if (ch == 75 && cursorCol > 0) cursorCol--;          
            else if (ch == 77 && cursorCol < currentSize - 1) cursorCol++;   
            continue; 
        } 
        else if (ch == 'u' || ch == 'U') {
            // Tinh nang Undo (Hoan tac nuoc di)
            if (van_co.so_nuoc_da_di > 0) {
                van_co.so_nuoc_da_di--; 
                MotNuocDi lastMove = van_co.lich_su_nuoc_di[van_co.so_nuoc_da_di];
                
                // Xoa quan co tren ban co va doi lai luot
                van_co.ban_co[lastMove.hang][lastMove.cot] = ' '; 
                van_co.luot_hien_tai = lastMove.nguoi_danh;
                
                // Dua con tro ve dung vi tri vua Undo
                cursorRow = lastMove.hang;
                cursorCol = lastMove.cot;
            }
            continue;
        }
        else if (ch == 13 || ch == 32) { // Ph
