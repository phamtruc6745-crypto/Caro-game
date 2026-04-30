#include <stdio.h>
#include <stdbool.h>
#include "../include/cau_truc_du_lieu.h"
#include "../include/game.h"

/* ================================================================
 * board.c
 * Chuc nang: Khoi tao va ve ban co giao dien Console
 * ================================================================ */

// Khoi tao mang theo kich thuoc thuc te duoc chon
void initBoard(char ban_co[KICH_THUOC_BAN_CO][KICH_THUOC_BAN_CO], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ban_co[i][j] = ' '; // Gan ky tu khoang trang cho tat ca cac o
        }
    }
}

// Ve ban co theo kich thuoc thuc te, kem theo mau sac va highlight con tro
void displayBoard(char ban_co[KICH_THUOC_BAN_CO][KICH_THUOC_BAN_CO], int size, int cursorRow, int cursorCol) {
    // 1. Ve thu tu cot o tren cung
    printf("     ");
    for (int j = 0; j < size; j++) {
        printf("%2d  ", j);
    }
    printf("\n");

    // 2. Ve tung hang cua ban co
    for (int i = 0; i < size; i++) {
        // In thu tu hang o dau moi dong
        printf(" %2d  ", i);
        
        for (int j = 0; j < size; j++) {
            // Kiem tra xem o hien tai co phai la noi con tro dang dung khong
            bool isCursor = (i == cursorRow && j == cursorCol);
            
            // In ky tu tai o do (Khoang trang, X, hoac O) kem highlight
            if (ban_co[i][j] == ' ') {
                if (isCursor) printf("\x1B[100m   \x1B[0m"); 
                else printf("   ");
            } 
            else if (ban_co[i][j] == 'X') {
                if (isCursor) printf("\x1B[100;91m X \x1B[0m"); 
                else printf(" \x1B[91mX\x1B[0m ");
            } 
            else if (ban_co[i][j] == 'O') { 
                if (isCursor) printf("\x1B[100;96m O \x1B[0m"); 
                else printf(" \x1B[96mO\x1B[0m ");
            }
            
            // Ve duong ke doc (V_LINE) giua cac o
            if (j < size - 1) printf("%s%s%s", ANSI_GRAY, V_LINE, ANSI_RESET);
        }
        printf("\n");
        
        // 3. Ve duong ke ngang giua cac hang
        if (i < size - 1) {
            printf("     ");
            for (int j = 0; j < size; j++) {
                printf("%s%s%s%s%s", ANSI_GRAY, H_LINE, H_LINE, H_LINE, ANSI_RESET);
                if (j < size - 1) printf("%s%s%s", ANSI_GRAY, CROSS, ANSI_RESET);
            }
            printf("\n");
        }
    }
}
