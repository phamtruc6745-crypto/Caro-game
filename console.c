#include "game.h" 
#include <windows.h> 
#include <stdio.h>
#include <string.h>
#include <conio.h> 

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

// day la ham giup console hieu duoc cac ma dieu khien nhu ma mau sac, di chuyen con tro,....
void setupWindowsConsole() {
    // Ép console mở rộng ra 90 cột x 40 dòng
    system("mode con cols=90 lines=40");

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
        
        // 1. IN LOGO NGAY LAP TUC 
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
            if (ch == 72 && choice > 0) choice--;    
            if (ch == 80 && choice < 2) choice++;    
        } else if (ch == 13 || ch == 32) {           
            return options[choice]; 
        }
    }
}

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Nang cap: Them tham so toa do X, Y va thoi gian
void drawStatusBar(int cursorX, int cursorY, int timeRemaining) {
    int consoleWidth = 85;  // FIX: Tăng chiều ngang một chút cho cân đối
    int consoleHeight = 35; // FIX LỖI NHẢY Ô: Đẩy thanh trạng thái xuống dòng 35

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int oldX = csbi.dwCursorPosition.X;
    int oldY = csbi.dwCursorPosition.Y;

    gotoXY(0, consoleHeight);
    setTextColor(240); 

    char statusText[100];
    
    
    sprintf(statusText, " GVHD: Th.s Tran Thi Dung | Nhom nhung con bo | Toa do: (%02d, %02d) | [S] Luu - [U] Undo ", 
            cursorX, cursorY);

    printf("%s", statusText);

    for (int i = strlen(statusText); i < consoleWidth; i++) {
        printf(" ");
    }

    setTextColor(7); 
    gotoXY(oldX, oldY);
    fflush(stdout); 
}
