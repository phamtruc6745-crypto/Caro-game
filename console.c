#include "../include/game.h"
#include <windows.h> 
#include <stdio.h>
#include <string.h>
#include <conio.h> // Thu vien bat buoc phai co cho _getch()

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
// day la ham giup console hieu duoc cac ma dieu khien nhu ma mau sac, di chuyen con tro,....
void setupWindowsConsole() {
    SetConsoleOutputCP(CP_UTF8); 
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// day la chia khoa de mo ra quyen can thiep vao console
    if (hOut != INVALID_HANDLE_VALUE) { // kiem tra xem co du dieu kien de cap chia khoa chua 
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) { // ktr xem he thong da cho phep doc cau hinh hien tai cua console 
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
// thêm hàm hiển thị thanh trạng thái ( ý tưởng mới cho giao diện đỡ trống trải)
// Ham di chuyen con tro (gotoXY) va doi mau (setTextColor) giu nguyen nhu cu
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
    int consoleWidth = 80;  // Chieu ngang console
    int consoleHeight = 26; // Dong duoi cung

    // Luu lai vi tri con tro hien tai (de sau khi ve xong status bar, tra con tro ve cho cu)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int oldX = csbi.dwCursorPosition.X;
    int oldY = csbi.dwCursorPosition.Y;

    // Di chuyen xuong dong cuoi cung de ve
    gotoXY(0, consoleHeight);
    setTextColor(240); // Mau nen noi bat (Vi du: Nen trang, chu den)

    // Tao mang ky tu de chua chuoi da ghep thong so
    char statusText[100];
    
    // Ghep thong tin dong vao chuoi
    // %02d giup in so luon co 2 chu so (VD: 05, 12) cho dep mat
    sprintf(statusText, " GVHD: Th.s Tran Thi Dung | Nhom nhung con bo | Toa do: (%02d, %02d) | Thoi gian: %02ds ", 
            cursorX, cursorY, timeRemaining);

    // In chuoi ra man hinh
    printf("%s", statusText);

    // Xoa/phu mau nen cho phan khoang trong con lai ben phai
    for (int i = strlen(statusText); i < consoleWidth; i++) {
        printf(" ");
    }

    // Reset mau va tra con tro ve vi tri cu tren ban co
    setTextColor(7); 
    gotoXY(oldX, oldY);
    fflush(stdout); // lenh ep console hien thi ngay lap tuc ham vua in
}
