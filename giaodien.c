#include "giaodien.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

int g_hangBatDauBanCo = 11;
int g_toaDoY_Prompt = -1;

void xoaManHinh() {
    // \x1b[2J xoa man hinh hien tai
    // \x1b[3J xoa scrollback buffer (lich su cuon man hinh)
    // \x1b[H dua con tro ve goc 0,0
    printf("\x1b[2J\x1b[3J\x1b[H");
    fflush(stdout);
}

void inHieuUngTieuDe() {
    printf(MAU_DAM);
    printf(MAU_NHAP_NHAY MAU_VANG "         *       +       *       +       *       +       *   \n" DAT_LAI_MAU MAU_DAM);
    printf(MAU_XANH_NGOC "       ██████╗ ██████╗     ██████╗ █████╗ ██████╗ ██████╗\n");
    printf(MAU_XANH_NGOC "      ██╔════╝██╔═══██╗   ██╔════╝██╔══██╗██╔══██╗██╔═══██╗\n");
    printf(MAU_XANH_DUONG "      ██║     ██║   ██║   ██║     ███████║██████╔╝██║   ██║\n");
    printf(MAU_XANH_DUONG "      ██║     ██║   ██║   ██║     ██╔══██║██╔══██╗██║   ██║\n");
    printf(MAU_HONG "      ╚██████╗╚██████╔╝   ╚██████╗██║  ██║██║  ██║╚██████╔╝\n");
    printf(MAU_HONG "       ╚═════╝ ╚═════╝     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝\n");
    printf(MAU_NHAP_NHAY MAU_VANG "             +       *       +       *       +       *       \n" DAT_LAI_MAU);
}

void capNhatOCo(BanCo* banCo, int cot, int hang, bool laConTro, bool laNuocCuoi) {
    int consoleX = TOA_DO_X_BAT_DAU + cot * 4;
    int consoleY = g_hangBatDauBanCo + hang * 2;
#ifdef _WIN32
    COORD coord = {consoleX, consoleY};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("\x1b[%d;%dH", consoleY + 1, consoleX + 1);
#endif

    char mauNen[20] = "";
    if (laConTro) sprintf(mauNen, "%s", "\x1b[46m"); 
    else if (laNuocCuoi) sprintf(mauNen, "%s", "\x1b[43m"); 
    
    printf("%s", mauNen);
    
    if (banCo->luoi[hang][cot] == NGUOI_X) {
        printf(MAU_DAM MAU_DO " X " DAT_LAI_MAU);
    } else if (banCo->luoi[hang][cot] == NGUOI_O) {
        printf(MAU_DAM MAU_XANH_LA " O " DAT_LAI_MAU);
    } else {
        printf("   " DAT_LAI_MAU);
    }
}

void veBanCo(BanCo* banCo, int conTroX, int conTroY, NuocDi nuocCuoi, bool veDayDu) {
    if (!veDayDu) {
        for (int i = 0; i < banCo->kichThuoc; i++) {
            for (int j = 0; j < banCo->kichThuoc; j++) {
                capNhatOCo(banCo, j, i, (i == conTroY && j == conTroX), (nuocCuoi.x == j && nuocCuoi.y == i));
            }
        }
        fflush(stdout);
        return;
    }

    xoaManHinh();
    inHieuUngTieuDe(); 
    printf("\n"); 
    
    printf("%s    ", GOC_TRAI);
    for (int i = 0; i < banCo->kichThuoc; i++) {
        printf(MAU_VANG "%2d  " DAT_LAI_MAU, i); 
    }
    printf("\n");
    
    printf("%s   " MAU_XANH_NGOC "\xE2\x95\x94", GOC_TRAI); 
    for (int i = 0; i < banCo->kichThuoc - 1; i++) printf("\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\xA6"); 
    printf("\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\x97\n" DAT_LAI_MAU); 

    for (int i = 0; i < banCo->kichThuoc; i++) {
        printf("%s" MAU_VANG "%2d " MAU_XANH_NGOC "\xE2\x95\x91" DAT_LAI_MAU, GOC_TRAI, i); 
        for (int j = 0; j < banCo->kichThuoc; j++) {
            bool laConTro = (i == conTroY && j == conTroX);
            bool laNuocCuoi = (nuocCuoi.x == j && nuocCuoi.y == i);
            
            char mauNen[20] = "";
            if (laConTro) sprintf(mauNen, "%s", "\x1b[46m"); 
            else if (laNuocCuoi) sprintf(mauNen, "%s", "\x1b[43m"); 
            
            printf("%s", mauNen);
            
            if (banCo->luoi[i][j] == NGUOI_X) {
                printf(MAU_DAM MAU_DO " X " DAT_LAI_MAU);
            } else if (banCo->luoi[i][j] == NGUOI_O) {
                printf(MAU_DAM MAU_XANH_LA " O " DAT_LAI_MAU);
            } else {
                printf("   " DAT_LAI_MAU);
            }
            printf(MAU_XANH_NGOC "\xE2\x95\x91" DAT_LAI_MAU); 
        }
        printf("\n");
        
        if (i < banCo->kichThuoc - 1) {
            printf("%s   " MAU_XANH_NGOC "\xE2\x95\xA0", GOC_TRAI); 
            for (int j = 0; j < banCo->kichThuoc - 1; j++) printf("\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\xAC"); 
            printf("\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\xA3\n" DAT_LAI_MAU); 
        }
    }
    
    printf("%s   " MAU_XANH_NGOC "\xE2\x95\x9A", GOC_TRAI); 
    for (int i = 0; i < banCo->kichThuoc - 1; i++) printf("\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\xA9"); 
    printf("\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\x9D\n" DAT_LAI_MAU); 
    
    printf("\n%s" MAU_DAM "Phim tat:\n" DAT_LAI_MAU, GOC_TRAI);
    printf("%s[Mui ten/Click] Di chuyen & Danh\n", GOC_TRAI);
    printf("%s[U] Hoan tac | [S] Luu Game | [ESC] Thoat\n", GOC_TRAI);
    printf("%s" MAU_VANG "[R] Dau hang | [D] Xin hoa\n" DAT_LAI_MAU, GOC_TRAI);

#ifdef _WIN32
    // Đã dời xuống cuối cùng và dùng công thức toán học lùi lại.
    // Tránh hoàn toàn lỗi bị trễ tọa độ do buffer scroll khi in quá nhiều dòng!
    if (veDayDu) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            g_hangBatDauBanCo = csbi.dwCursorPosition.Y - (banCo->kichThuoc * 2 + 5);
        }
    }
#endif
}

void inMenuChinh() {
    xoaManHinh();
    printf("\n");
    inHieuUngTieuDe();
    printf("\n");
    
    char p[] = "               "; // 15 spaces
    
    printf("%s" MAU_VANG "\xE2\x95\x94", p);
    for(int i=0; i<32; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x97\n" DAT_LAI_MAU);
    
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU MAU_DAM MAU_XANH_LA "         CHON CHE DO CHOI       " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    
    printf("%s" MAU_VANG "\xE2\x95\xA0", p);
    for(int i=0; i<32; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\xA3\n" DAT_LAI_MAU);
    
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_DUONG MAU_DAM "[1]" DAT_LAI_MAU " Choi Moi (Chon kich thuoc) " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_DUONG MAU_DAM "[2]" DAT_LAI_MAU " Tiep tuc (Load Game)       " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_DUONG MAU_DAM "[3]" DAT_LAI_MAU " Xem lai (Replay)           " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_DUONG MAU_DAM "[4]" DAT_LAI_MAU " Bang xep hang              " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_DO       MAU_DAM "[5]" DAT_LAI_MAU " Thoat                      " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    
    printf("%s" MAU_VANG "\xE2\x95\x9A", p);
    for(int i=0; i<32; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x9D\n" DAT_LAI_MAU);
    
    printf("\n%s" MAU_DAM MAU_XANH_NGOC "Moi ban lua chon (1-5): " DAT_LAI_MAU, p);
}

void inMenuKichThuoc() {
    xoaManHinh();
    printf("\n");
    inHieuUngTieuDe();
    printf("\n");
    
    char p[] = "           "; // 11 spaces for a slightly wider menu
    
    printf("%s" MAU_VANG "\xE2\x95\x94", p);
    for(int i=0; i<40; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x97\n" DAT_LAI_MAU);
    
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU MAU_DAM MAU_HONG "        CHON KICH THUOC BAN CO          " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    
    printf("%s" MAU_VANG "\xE2\x95\xA0", p);
    for(int i=0; i<40; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\xA3\n" DAT_LAI_MAU);
    
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_NGOC MAU_DAM "[1]" DAT_LAI_MAU " 3x3   (Thang khi 3 quan lien tiep) " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_NGOC MAU_DAM "[2]" DAT_LAI_MAU " 5x5   (Thang khi 4 quan lien tiep) " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_NGOC MAU_DAM "[3]" DAT_LAI_MAU " 15x15 (Thang khi 5 quan lien tiep) " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    
    printf("%s" MAU_VANG "\xE2\x95\x9A", p);
    for(int i=0; i<40; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x9D\n" DAT_LAI_MAU);
    
    printf("\n%s" MAU_DAM MAU_XANH_DUONG "Moi ban lua chon (1-3): " DAT_LAI_MAU, p);
}

void inThongBao(const char* thongBao) {
    printf("%s%s\n", GOC_TRAI, thongBao);
    }
}
