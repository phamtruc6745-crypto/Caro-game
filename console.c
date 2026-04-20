#include "../include/game.h"
#include <windows.h> 
#include <stdio.h>
#include <string.h>
#include <conio.h> // Thu vien bat buoc phai co cho _getch()

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void setupWindowsConsole() {
    SetConsoleOutputCP(CP_UTF8); 
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode); 
        }
    }
}

// Ham hien thi Man hinh chao mung tich hop MENU
int showSplashScreen() {
    int choice = 0; // 0: 3x3, 1: 5x5, 2: 15x15
    int options[] = {3, 5, 15};
    
    while(1) {
        printf("%s", ANSI_CLEAR);
        
        // 1. IN LOGO NGAY LAP TUC (Khong dung Sleep de menu khong bi giat)
        printf("%s", ANSI_CYAN);
        printf("  \\   /       ____    _    ____   ___         ___  \n"); 
        printf("   \\ /       / ___|  / \\  |  _ \\ / _ \\       /   \\ \n"); 
        printf("    X       | |     / _ \\ | |_) | | | |     |     |\n"); 
        printf("   / \\      | |___ / ___ \\|  _ <| |_| |      \\___/ \n"); 
        printf("  /   \\      \\____/_/   \\_\\_| \\_\\\\___/             \n"); 
        printf("%s\n", ANSI_RESET);

        printf("%s        --- SAN PHAM CUA NHOM NHUNG CON BO ---%s\n\n\n", ANSI_YELLOW, ANSI_RESET);
        
        // 2. IN MENU LUA CHON KICH THUOC
        printf("        --- LUA CHON KICH THUOC BAN CO ---\n\n");
        
        for(int i = 0; i < 3; i++) {
            if(i == choice) {
                // To mau vang cho muc dang duoc chon
                printf("    %s > BAN CO %dx%d <%s\n", ANSI_YELLOW, options[i], options[i], ANSI_RESET);
            } else {
                printf("      BAN CO %dx%d\n", options[i], options[i]);
            }
        }
        
        printf("\n   (Dung MUI TEN de chon, ENTER de xac nhan)\n");

        // 3. XU LY PHIM BAM MENU
        int ch = _getch();
        if (ch == 224 || ch == 0) {
            ch = _getch();
            if (ch == 72 && choice > 0) choice--;    // Mui ten Len
            if (ch == 80 && choice < 2) choice++;    // Mui ten Xuong
        } else if (ch == 13 || ch == 32) {           // Phim Enter hoac Space
            return options[choice]; // Tra ve ket qua 3, 5 hoac 15 cho ham main
        }
    }
}
