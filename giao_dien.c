#include "giao_dien.h"
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif 

#ifdef _WIN32
#include <windows.h>
#endif

void dat_con_tro_ve_dau(void) {
    // Dung ANSI de co dinh ban co, chong troi lech toa do chuot
    printf("%s", ANSI_HOME);
}

void thiet_lap_console(void) {
#ifdef _WIN32
    system("mode con cols=95 lines=45");
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwModeOut = 0;
    GetConsoleMode(hOut, &dwModeOut);
    dwModeOut |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwModeOut);

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD dwModeIn = 0;
    GetConsoleMode(hIn, &dwModeIn);
    dwModeIn |= ENABLE_MOUSE_INPUT;
    dwModeIn &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(hIn, dwModeIn);
#endif
}

void chon_che_do_choi(int *kich_thuoc, int *so_quan_thang) {
    printf("%s", ANSI_CLEAR);
    printf("%s\n", ANSI_CYAN);
    printf("   ____    _    ____   ___    ____  ____   ___  \n");
    printf("  / ___|  / \\  |  _ \\ / _ \\  |  _ \\|  _ \\ / _ \\ \n");
    printf(" | |     / _ \\ | |_) | | | | | |_) | |_) | | | |\n");
    printf(" | |___ / ___ \\|  _ <| |_| | |  __/|  _ <| |_| |\n");
    printf("  \\____/_/   \\_\\_| \\_\\\\___/  |_|   |_| \\_\\\\___/ \n");
    printf("%s", ANSI_RESET);
    
    // DA FIX: Dung ky tu ASCII de dam bao can le thang tap tuyet doi
    printf("\n%s+==============================================+%s\n", ANSI_YELLOW, ANSI_RESET);
    printf("%s|%s           CHON CHE DO CHOI                   %s|\n", ANSI_YELLOW, ANSI_WHITE_BOLD, ANSI_YELLOW);
    printf("+==============================================+\n");
    printf("|%s 1. Co Tic-Tac-Toe (3x3)   - Thang 3        %s|\n", ANSI_WHITE_BOLD, ANSI_YELLOW);
    printf("|%s 2. Co Caro Mini   (5x5)   - Thang 4        %s|\n", ANSI_WHITE_BOLD, ANSI_YELLOW);
    printf("|%s 3. Co Caro Chuan  (15x15) - Thang 5        %s|\n", ANSI_WHITE_BOLD, ANSI_YELLOW);
    printf("+==============================================+%s\n", ANSI_RESET);
    printf(" Nhap lua chon (1-3): ");
    
    int lc;
    scanf("%d", &lc);
    while(getchar() != '\n');
    if (lc == 1) { *kich_thuoc = 3; *so_quan_thang = 3; }
    else if (lc == 2) { *kich_thuoc = 5; *so_quan_thang = 4; }
    else { *kich_thuoc = 15; *so_quan_thang = 5; }
}
void ve_thanh_trang_thai(int cot_con_tro, int hang_con_tro, char luot) {
    // Tao thanh HUD hien thi thong tin duoi ban co bang nen mau
    printf("\n%s%s  [ Luot danh: %c ] | [ Vi tri hien tai: Hang %-2d, Cot %-2d ]          %s\n", ANSI_BG_BLUE, ANSI_WHITE_BOLD, luot, hang_con_tro, cot_con_tro, ANSI_RESET);
    printf("%s%s  Phim: [Chuot trai/Enter] Danh | [U] Hoan tac | [S] Luu game       %s\n", ANSI_BG_BLUE, ANSI_WHITE_BOLD, ANSI_RESET);
    printf("                                                                        \n");
}

void khoi_tao_ban_co(char ban_co[KICH_THUOC_TOI_DA][KICH_THUOC_TOI_DA], int kich_thuoc) {
    for (int i = 0; i < kich_thuoc; i++)
        for (int j = 0; j < kich_thuoc; j++)
            ban_co[i][j] = ' ';
}

void hien_thi_ban_co(char ban_co[KICH_THUOC_TOI_DA][KICH_THUOC_TOI_DA], int kich_thuoc, int hang_con_tro, int cot_con_tro, int hang_cuoi, int cot_cuoi) {
    // Hang chi so cot
    printf("\n     ");
    for (int j = 0; j < kich_thuoc; j++) printf("%s%2d  %s", ANSI_MAGENTA, j, ANSI_RESET);
    printf("\n");

    for (int i = 0; i < kich_thuoc; i++) {
        // Chi so hang
        printf(" %s%2d%s  ", ANSI_MAGENTA, i, ANSI_RESET);
        
        for (int j = 0; j < kich_thuoc; j++) {
            bool la_con_tro = (i == hang_con_tro && j == cot_con_tro);
            bool la_nuoc_cuoi = (i == hang_cuoi && j == cot_cuoi);

            char *mau_nen = la_con_tro ? "\x1B[100m" : (la_nuoc_cuoi ? ANSI_BG_YELLOW : "");
            char *mau_chu = (la_nuoc_cuoi && !la_con_tro) ? ANSI_BLACK : (ban_co[i][j] == 'X' ? ANSI_RED : ANSI_CYAN);

            // Dam bao toa do van khop voi logic tinh toan chuot
            if (ban_co[i][j] == ' ') printf("%s   %s", mau_nen, ANSI_RESET);
            else printf("%s %s%c %s", mau_nen, mau_chu, ban_co[i][j], ANSI_RESET);

            if (j < kich_thuoc - 1) printf("%s", V_LINE);
        }
        printf("\n");
        
        // Ve duong ke ngang giua cac o
        if (i < kich_thuoc - 1) {
            printf("     ");
            for (int j = 0; j < kich_thuoc; j++) {
                printf("%s", H_LINE);
                if (j < kich_thuoc - 1) printf("%s", CROSS);
            }
            printf("\n");
        }
    }
}
