#include "cau_truc_du_lieu.h"
#include "giao_dien.h"
#include "dieu_khien.h"
#include "logic_game.h"
#include "ngan_xep.h"
#include "luu_tai_game.h"
#include "bang_xep_hang.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

ThongTinNguoiChoi nguoi1, nguoi2;
BanCo banCoChoi;
NguoiChoiHienTai luotHienTai;
NganXep lichSuNuocDi;

void thietLapNguoiChoi() {
    xoaManHinh();
    inHieuUngTieuDe();
    
    char p[] = "          "; // GOC_TRAI
    
    printf("\n%s" MAU_DAM MAU_XANH_NGOC "=== NHAP THONG TIN NGUOI CHOI ===\n" DAT_LAI_MAU, p);
    
    printf("\n%s" MAU_DO "Ten nguoi choi X: " DAT_LAI_MAU, p);
    if (scanf(" %49[^\n]", nguoi1.ten) != 1) strcpy(nguoi1.ten, "Nguoi choi X");
    while(getchar() != '\n'); // Xoa bo dem vung nho dem
    
    printf("%s" MAU_XANH_LA "Ten nguoi choi O: " DAT_LAI_MAU, p);
    if (scanf(" %49[^\n]", nguoi2.ten) != 1) strcpy(nguoi2.ten, "Nguoi choi O");
    while(getchar() != '\n'); // Xoa bo dem vung nho dem
    
    printf("\n%s-------------------------------------------\n", p);
    printf("%s" MAU_DAM "QUYET DAU: %s (X) vs %s (O)\n", p, nguoi1.ten, nguoi2.ten);
    printf("%sChuc cac ban choi vui ve!\n", p);
    printf("%sNhan phim Enter de bat dau...", p);
    while(getchar() != '\n');
    getchar();
}

void vaoGame(bool daTaiGame, int kichThuoc, int dkThang) {
    // RESET & KHÓA CỨNG: Đảm bảo sạch bóng ma trước khi đánh nước đầu tiên
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int width = 120;
    int height = 45;
    COORD bufferSize = { (short)width, (short)height };
    SetConsoleScreenBufferSize(hOut, bufferSize);
    SMALL_RECT windowRect = {0, 0, (short)(width-1), (short)(height-1)};
    SetConsoleWindowInfo(hOut, TRUE, &windowRect);
#endif
    xoaManHinh();
    Sleep(50);
    
    khoiTaoDieuKhien();
    if (!daTaiGame) {
        khoiTaoBanCo(&banCoChoi, kichThuoc, dkThang);
        khoiTaoNganXep(&lichSuNuocDi);
        luotHienTai = NGUOI_X;
    }
    
    int toaDoX = banCoChoi.kichThuoc / 2;
    int toaDoY = banCoChoi.kichThuoc / 2;
    TrangThaiGame trangThai = DANG_CHOI;
    NuocDi nuocCuoi = {-1, -1, O_TRONG};
    
    if (!nganXepRong(&lichSuNuocDi)) {
        NodeNuocDi* dinh = lichSuNuocDi.dinh;
        if (dinh) nuocCuoi = dinh->nuocDi;
    }
    
    xoaManHinh(); 
    Sleep(10);
    printf("\x1b[?25l"); 

    while (trangThai == DANG_CHOI) {
        veBanCo(&banCoChoi, toaDoX, toaDoY, nuocCuoi, 
               (luotHienTai == NGUOI_X) ? nguoi1.ten : nguoi2.ten, luotHienTai);
        // Không dùng printf ở đây để tránh làm trôi màn hình
        
        SuKienNhap sk = layLenhDieuKhien();
        

        
        if (sk.phim == PHIM_LEN && toaDoY > 0) toaDoY--;
        else if (sk.phim == PHIM_XUONG && toaDoY < banCoChoi.kichThuoc - 1) toaDoY++;
        else if (sk.phim == PHIM_TRAI && toaDoX > 0) toaDoX--;
        else if (sk.phim == PHIM_PHAI && toaDoX < banCoChoi.kichThuoc - 1) toaDoX++;
        else if ((sk.phim == PHIM_ENTER || sk.phim == PHIM_SPACE) && nuocDiHopLe(&banCoChoi, toaDoX, toaDoY)) {
            nuocCuoi.x = toaDoX;
            nuocCuoi.y = toaDoY;
            nuocCuoi.nguoiDanh = luotHienTai;
            
            danhCo(&banCoChoi, nuocCuoi);
            themVaoNganXep(&lichSuNuocDi, nuocCuoi);
            
            trangThai = kiemTraThangThua(&banCoChoi, nuocCuoi);
            luotHienTai = (luotHienTai == NGUOI_X) ? NGUOI_O : NGUOI_X;
        }
        else if (sk.phim == PHIM_UNDO) {
            NuocDi nuoc;
            if (layKhoiNganXep(&lichSuNuocDi, &nuoc)) {
                hoanTacNuocDi(&banCoChoi, nuoc);
                luotHienTai = nuoc.nguoiDanh;
                toaDoX = nuoc.x;
                toaDoY = nuoc.y;
                
                if (!nganXepRong(&lichSuNuocDi)) {
                    nuocCuoi = lichSuNuocDi.dinh->nuocDi;
                } else {
                    nuocCuoi.x = -1; nuocCuoi.y = -1;
                }
            }
        }
        else if (sk.phim == PHIM_SAVE) {
            if (luuTrangThaiGame(TEP_LUU_GAME, &banCoChoi, &nguoi1, &nguoi2, luotHienTai, &lichSuNuocDi)) {
                printf("\nDa luu game thanh cong! Nhan Space de tiep tuc...");
                while(layLenhDieuKhien().phim != PHIM_SPACE);
            } else {
                printf("\nLoi luu game! Nhan Space de tiep tuc...");
                while(layLenhDieuKhien().phim != PHIM_SPACE);
            }
        }
        else if (sk.phim == PHIM_DAU_HANG) {
            printf("\n%s muon dau hang? (Y: Co / N: Khong): ", (luotHienTai == NGUOI_X) ? nguoi1.ten : nguoi2.ten);
            if (layLenhDieuKhien().phim == PHIM_Y) {
                trangThai = (luotHienTai == NGUOI_X) ? X_DAU_HANG : O_DAU_HANG;
            } else {
                gotoXY(0, 44);
                printf("%s" MAU_XANH_LA "Khong dau hang. Tran dau tiep tuc! Nhan Space...", GOC_TRAI);
                while(layLenhDieuKhien().phim != PHIM_SPACE);
                xoaManHinh();
            }
        }
        else if (sk.phim == PHIM_XIN_HOA) {
            gotoXY(0, 44);
            printf("%s xin hoa. %s co dong y khong? (Y: Co / N: Khong): ", 
                (luotHienTai == NGUOI_X) ? nguoi1.ten : nguoi2.ten,
                (luotHienTai == NGUOI_X) ? nguoi2.ten : nguoi1.ten);
            if (layLenhDieuKhien().phim == PHIM_Y) {
                trangThai = HOA_NHAU;
            } else {
                gotoXY(0, 44);
                printf("%s" MAU_DAM MAU_DO "Loi de nghi bi tu choi. Tiep tuc chien dau! Nhan Space..." DAT_LAI_MAU "          ", GOC_TRAI);
                while(layLenhDieuKhien().phim != PHIM_SPACE);
                xoaManHinh();
            }
        }
        else if (sk.phim == PHIM_ESC) {
            break;
        }
    }
    
    printf("\x1b[?25h"); // Hiện lại con trỏ console
    if (trangThai != DANG_CHOI) {
        veBanCo(&banCoChoi, -1, -1, nuocCuoi, 
               (luotHienTai == NGUOI_X) ? nguoi1.ten : nguoi2.ten, luotHienTai);
        if (trangThai == X_THANG) {
            printf("\n%s" MAU_DAM MAU_VANG "Nguoi choi %s (X) DA CHIEN THANG!\n" DAT_LAI_MAU, GOC_TRAI, nguoi1.ten);
            nguoi1.thang++; nguoi2.thua++;
        } else if (trangThai == O_THANG) {
            printf("\n%s" MAU_DAM MAU_VANG "Nguoi choi %s (O) DA CHIEN THANG!\n" DAT_LAI_MAU, GOC_TRAI, nguoi2.ten);
            nguoi2.thang++; nguoi1.thua++;
        } else if (trangThai == X_DAU_HANG) {
            printf("\n%s" MAU_DAM MAU_DO "Nguoi choi %s (X) DA DAU HANG! %s (O) THANG!\n" DAT_LAI_MAU, GOC_TRAI, nguoi1.ten, nguoi2.ten);
            nguoi2.thang++; nguoi1.thua++;
        } else if (trangThai == O_DAU_HANG) {
            printf("\n%s" MAU_DAM MAU_DO "Nguoi choi %s (O) DA DAU HANG! %s (X) THANG!\n" DAT_LAI_MAU, GOC_TRAI, nguoi2.ten, nguoi1.ten);
            nguoi1.thang++; nguoi2.thua++;
        } else if (trangThai == HOA_NHAU) {
            printf("\n%s" MAU_DAM MAU_XANH_NGOC "HAI BEN HOA NHAU!\n" DAT_LAI_MAU, GOC_TRAI);
            nguoi1.hoa++; nguoi2.hoa++;
        }
        capNhatBangXepHang(nguoi1);
        capNhatBangXepHang(nguoi2);
        
        printf("\n%sNhan Space de ve Menu...", GOC_TRAI);
        while(layLenhDieuKhien().phim != PHIM_SPACE);
    }
}

void xemLaiGame() {
    khoiTaoDieuKhien();
    if (nganXepRong(&lichSuNuocDi)) {
        printf("Khong co lich su tran dau gan nhat.\n");
        printf("Nhan Space de ve Menu...");
        while(layLenhDieuKhien().phim != PHIM_SPACE);
        return;
    }
    
    BanCo banCoXemLai;
    khoiTaoBanCo(&banCoXemLai, banCoChoi.kichThuoc, banCoChoi.dieuKienThang);
    
    NganXep nganXepTam;
    daoNguocNganXep(&nganXepTam, &lichSuNuocDi);
    
    xoaManHinh();
    NuocDi nuoc;
    int yThongBao = banCoChoi.kichThuoc * 2 + 12; // Vị trí dưới bàn cờ
    NguoiChoiHienTai luotXemLai = NGUOI_X; // Mặc định quân X đi trước

    while(layKhoiNganXep(&nganXepTam, &nuoc)) {
        danhCo(&banCoXemLai, nuoc);
        veBanCo(&banCoXemLai, -1, -1, nuoc, 
               (luotXemLai == NGUOI_X) ? nguoi1.ten : nguoi2.ten, luotXemLai);
        
        // Đổi lượt cho nước tiếp theo trong Replay
        luotXemLai = (luotXemLai == NGUOI_X) ? NGUOI_O : NGUOI_X;
        
        gotoXY(0, yThongBao);
        printf(MAU_XANH_DUONG MAU_DAM "DANG XEM LAI... [Space]: Tiep tuc | [ESC]: Thoat ve Menu" DAT_LAI_MAU "          ");
        
        SuKienNhap sk = layLenhDieuKhien();
        if (sk.phim == PHIM_ESC) {
            xoaNganXep(&nganXepTam);
            break;
        }
    }
}

void khoiPhucConsole() {
    printf("\x1b[?25h"); // Hiện con trỏ
}

int main() {
    atexit(khoiPhucConsole);
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int width = 120, height = 45;
    char modeCmd[50];
    sprintf(modeCmd, "mode con cols=%d lines=%d", width, height);
    system(modeCmd);
    Sleep(50);

    // 3. KHÓA CỨNG: Ép bộ đệm bằng đúng kích thước cửa sổ (TRIỆT TIÊU THANH CUỘN)
    COORD bufferSize = { (short)width, (short)height };
    SetConsoleScreenBufferSize(hOut, bufferSize);

    // 4. Ghim tầm nhìn vào góc (0,0)
    SMALL_RECT windowRect = {0, 0, (short)(width-1), (short)(height-1)};
    SetConsoleWindowInfo(hOut, TRUE, &windowRect);

    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    SetConsoleOutputCP(CP_UTF8);
#endif

    khoiTaoNganXep(&lichSuNuocDi);
    int luaChon = 0;
    khoiTaoDieuKhien();

    while(1) {
        inMenuChinh();
        if (scanf("%d", &luaChon) != 1) {
            while(getchar() != '\n'); 
            continue;
        }
        
        if (luaChon == 1) {
            thietLapNguoiChoi();
            int chonKichThuoc = 0;
            int size = 15;
            int cond = 5;
            
            while(1) {
                inMenuChonKichThuoc();
                if (scanf("%d", &chonKichThuoc) == 1 && chonKichThuoc >= 1 && chonKichThuoc <= 3) {
                    break;
                }
                while(getchar() != '\n');
            }
            
            size = (chonKichThuoc == 1) ? 3 : (chonKichThuoc == 2) ? 5 : 15;
            cond = (chonKichThuoc == 1) ? 3 : (chonKichThuoc == 2) ? 4 : 5;
            
            while(getchar() != '\n'); // Dọn dẹp sạch phím Enter thừa
            xoaManHinh(); 
            vaoGame(false, size, cond);
            
        } else if (luaChon == 2) {
            if (taiTrangThaiGame(TEP_LUU_GAME, &banCoChoi, &nguoi1, &nguoi2, &luotHienTai, &lichSuNuocDi)) {
                xoaManHinh();
                vaoGame(true, banCoChoi.kichThuoc, banCoChoi.dieuKienThang);
            } else {
                printf("\n%sKhong tim thay file save. Nhan Space...", GOC_TRAI);
                while(layLenhDieuKhien().phim != PHIM_SPACE);
            }
        } else if (luaChon == 3) {
            xoaManHinh();
            xemLaiGame();
        } else if (luaChon == 4) {
            xoaManHinh();
            hienThiBangXepHang();
            printf("\n%sNhan Space de ve Menu...", GOC_TRAI);
            while(layLenhDieuKhien().phim != PHIM_SPACE);
        } else if (luaChon == 5) {
            break;
        }
    }
    
    xoaNganXep(&lichSuNuocDi);
    return 0;
}
