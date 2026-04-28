#include <stdio.h>
#include "../include/game.h"

// Khoi tao mang theo kich thuoc thuc te duoc chon
void initBoard(Stone board[BOARD_SIZE][BOARD_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}

// Ve ban co theo kich thuoc thuc te
void displayBoard(Stone board[BOARD_SIZE][BOARD_SIZE], int size, int cursorRow, int cursorCol) {
    printf("     ");
    for (int j = 0; j < size; j++) printf("%2d  ", j);
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf(" %2d  ", i);
        for (int j = 0; j < size; j++) {
            
            bool isCursor = (i == cursorRow && j == cursorCol);
            
            if (board[i][j] == ' ') {
                if (isCursor) printf("\x1B[100m   \x1B[0m"); 
                else printf("   ");
            } 
            else if (board[i][j] == 'X') {
                if (isCursor) printf("\x1B[100;91m X \x1B[0m"); 
                else printf(" \x1B[91mX\x1B[0m ");
            } 
            else { // WHITE
                if (isCursor) printf("\x1B[100;96m O \x1B[0m"); 
                else printf(" \x1B[96mO\x1B[0m ");
            }
            
            if (j < size - 1) printf("%s%s%s", ANSI_GRAY, V_LINE, ANSI_RESET);
        }
        printf("\n");
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
