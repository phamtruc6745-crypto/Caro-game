#include "giao_dien (1).h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void xoaManHinh() {
    system("cls");
}

void inHieuUngTieuDe() {
    printf(MAU_DAM MAU_XANH_NGOC "       ██████╗ ██████╗     ██████╗ █████╗ ██████╗ ██████╗\n");
    printf(MAU_XANH_NGOC "      ██╔════╝██╔═══██╗   ██╔════╝██╔══██╗██╔══██╗██╔═══██╗\n");
    printf(MAU_XANH_DUONG "      ██║     ██║   ██║   ██║     ███████║██████╔╝██║   ██║\n");
    printf(MAU_XANH_DUONG "      ██║     ██║   ██║   ██║     ██╔══██║██╔══██╗██║   ██║\n");
    printf(MAU_HONG "      ╚██████╗╚██████╔╝   ╚██████╗██║  ██║██║  ██║╚██████╔╝\n");
    printf(MAU_HONG "       ╚═════╝ ╚═════╝     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝\n" DAT_LAI_MAU);
}

void veBanCo(BanCo* banCo, int conTroX, int conTroY, NuocDi nuocCuoi, const char* tenHienTai, NguoiChoiHienTai luot) {
    // Reset về góc (0,0)
    gotoXY(0, 0);
    inHieuUngTieuDe(); 
    
    printf("\n%s    ", GOC_TRAI);
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
            
            if (laConTro) printf("\x1b[46m"); 
            else if (laNuocCuoi) printf("\x1b[43m"); 
            
            if (banCo->luoi[i][j] == NGUOI_X) printf(MAU_DAM MAU_DO " X " DAT_LAI_MAU);
            else if (banCo->luoi[i][j] == NGUOI_O) printf(MAU_DAM MAU_XANH_LA " O " DAT_LAI_MAU);
            else printf("   " DAT_LAI_MAU);
            
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
    
    if (luot == NGUOI_X)
        printf("%s" MAU_DAM MAU_DO ">> DEN LUOT: %s (X) <<\x1b[K" DAT_LAI_MAU "\n", GOC_TRAI, tenHienTai);
    else
        printf("%s" MAU_DAM MAU_XANH_LA ">> DEN LUOT: %s (O) <<\x1b[K" DAT_LAI_MAU "\n", GOC_TRAI, tenHienTai);

    printf("%s" MAU_DAM "DIEU KHIEN: [Mui ten] Di chuyen | [Enter/Space] Danh co", GOC_TRAI);
    printf("\n%s" MAU_DAM "CHUC NANG: [U] Hoan tac | [S] Luu game | [ESC] Thoat", GOC_TRAI);
    printf("\n%s" MAU_VANG "HE THONG : [R] Dau hang | [D] Xin hoa" DAT_LAI_MAU, GOC_TRAI);
}

void inMenuChinh() {
    xoaManHinh();
    inHieuUngTieuDe();
    
    char p[] = "               "; 
    
    printf("%s" MAU_VANG "\xE2\x95\x94", p);
    for(int i=0; i<32; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x97\n" DAT_LAI_MAU);
    
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU MAU_DAM MAU_XANH_LA "         CHON CHE DO CHOI       " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    
    printf("%s" MAU_VANG "\xE2\x95\xA0", p);
    for(int i=0; i<32; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\xA3\n" DAT_LAI_MAU);
    
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_DUONG MAU_DAM "[1]" DAT_LAI_MAU " Choi Moi (Kich thuoc)      " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_DUONG MAU_DAM "[2]" DAT_LAI_MAU " Tiep tuc (Load Game)       " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_DUONG MAU_DAM "[3]" DAT_LAI_MAU " Xem lai (Replay)           " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_DUONG MAU_DAM "[4]" DAT_LAI_MAU " Bang xep hang              " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_VANG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_DO        MAU_DAM "[5]" DAT_LAI_MAU " Thoat                      " MAU_VANG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    
    printf("%s" MAU_VANG "\xE2\x95\x9A", p);
    for(int i=0; i<32; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x9D\n" DAT_LAI_MAU);
    
    printf("\n%s" MAU_DAM MAU_XANH_NGOC "Moi ban lua chon (1-5): " DAT_LAI_MAU, p);
}

void inMenuChonKichThuoc() {
    xoaManHinh();
    printf("\n");
    inHieuUngTieuDe();
    printf("\n");
    
    char p[] = "               "; 
    
    printf("%s" MAU_XANH_DUONG "\xE2\x95\x94", p);
    for(int i=0; i<36; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x97\n" DAT_LAI_MAU);
    
    printf("%s" MAU_XANH_DUONG "\xE2\x95\x91" DAT_LAI_MAU MAU_DAM MAU_VANG "       CHON KICH THUOC BAN CO       " MAU_XANH_DUONG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    
    printf("%s" MAU_XANH_DUONG "\xE2\x95\xA0", p);
    for(int i=0; i<36; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\xA3\n" DAT_LAI_MAU);
    
    printf("%s" MAU_XANH_DUONG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_LA  MAU_DAM "[1]" DAT_LAI_MAU " 3x3   (Thang khi 3 quan)     " MAU_XANH_DUONG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_XANH_DUONG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_XANH_DUONG MAU_DAM "[2]" DAT_LAI_MAU " 5x5   (Thang khi 4 quan)     " MAU_XANH_DUONG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    printf("%s" MAU_XANH_DUONG "\xE2\x95\x91" DAT_LAI_MAU " " MAU_DO        MAU_DAM "[3]" DAT_LAI_MAU " 15x15 (Thang khi 5 quan)     " MAU_XANH_DUONG "\xE2\x95\x91\n" DAT_LAI_MAU, p);
    
    printf("%s" MAU_XANH_DUONG "\xE2\x95\x9A", p);
    for(int i=0; i<36; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x9D\n" DAT_LAI_MAU);
    
    printf("\n%s" MAU_DAM MAU_XANH_NGOC "Moi ban lua chon (1-3): " DAT_LAI_MAU, p);
}

void inThongBao(const char* thongBao) {
    printf("%s%s\n", GOC_TRAI, thongBao);
}

