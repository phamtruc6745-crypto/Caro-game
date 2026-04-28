#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "cau_truc_du_lieu.h" // Ket noi voi he thong du lieu chuan

/* ================================================================
 * game.h
 * Chuc nang: Luu tru cac hang so giao dien (UI) va khai bao
 * nguyen mau ham cho Console, Ban co, va Logic game.
 * ================================================================ */

// --- CHUOI THOAT ANSI (Dung de to mau tren Console) ---
#define ANSI_RESET   "\x1B[0m"
#define ANSI_CLEAR   "\x1B[2J\x1B[H"
#define ANSI_RED     "\x1B[91m"
#define ANSI_CYAN    "\x1B[96m"
#define ANSI_GRAY    "\x1B[90m"
#define ANSI_YELLOW  "\x1B[93m" 
#define ANSI_BG_DARK "\x1B[100m"

// --- KY TU VE HOP (Ve ban co) ---
#define H_LINE "\xE2\x94\x80"
#define V_LINE "\xE2\x94\x82"
#define CROSS  "\xE2\x94\xBC"

// --- KHAI BAO NGUYEN MAU HAM (API) ---

/* === Giao dien Console (console.c) === */
void setupWindowsConsole();
int showSplashScreen(); 
void drawStatusBar(int cursorX, int cursorY, int timeRemaining); 

/* === Quan ly Ban co (board.c) === */
void initBoard(char ban_co[KICH_THUOC_BAN_CO][KICH_THUOC_BAN_CO], int size);
void displayBoard(char ban_co[KICH_THUOC_BAN_CO][KICH_THUOC_BAN_CO], int size, int cursorRow, int cursorCol);

/* === Logic Game (logic.c) === */
int countDirection(char ban_co[KICH_THUOC_BAN_CO][KICH_THUOC_BAN_CO], int size, int r, int c, int dr, int dc, char player);
bool checkWinner(char ban_co[KICH_THUOC_BAN_CO][KICH_THUOC_BAN_CO], int size, int lastRow, int lastCol, char player);

#endif /* GAME_H */
