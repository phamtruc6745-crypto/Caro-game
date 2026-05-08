#include "logic_game.h"
#include <stdio.h>

void khoiTaoBanCo(BanCo* banCo, int kichThuoc, int dkThang) {
    banCo->kichThuoc = kichThuoc;
    banCo->dieuKienThang = dkThang;
    for (int i = 0; i < KICH_THUOC_TOI_DA; i++) {
        for (int j = 0; j < KICH_THUOC_TOI_DA; j++) {
            banCo->luoi[i][j] = O_TRONG;
        }
    }
    banCo->soNuocDaDanh = 0;
}

bool nuocDiHopLe(BanCo* banCo, int x, int y) {
    if (x < 0 || x >= banCo->kichThuoc || y < 0 || y >= banCo->kichThuoc) return false;
    if (banCo->luoi[y][x] != O_TRONG) return false;
    return true;
}

void danhCo(BanCo* banCo, NuocDi nuoc) {
    if (nuocDiHopLe(banCo, nuoc.x, nuoc.y)) {
        banCo->luoi[nuoc.y][nuoc.x] = nuoc.nguoiDanh;
        banCo->soNuocDaDanh++;
    }
}

void hoanTacNuocDi(BanCo* banCo, NuocDi nuoc) {
    if (nuoc.x >= 0 && nuoc.x < banCo->kichThuoc && nuoc.y >= 0 && nuoc.y < banCo->kichThuoc) {
        banCo->luoi[nuoc.y][nuoc.x] = O_TRONG;
        banCo->soNuocDaDanh--;
    }
}

int demTheoHuong(BanCo* banCo, NuocDi nuocCuoi, int dx, int dy) {
    int dem = 0;
    int x = nuocCuoi.x + dx;
    int y = nuocCuoi.y + dy;
    NguoiChoiHienTai nguoi = nuocCuoi.nguoiDanh;
    
    while (x >= 0 && x < banCo->kichThuoc && y >= 0 && y < banCo->kichThuoc && banCo->luoi[y][x] == nguoi) {
        dem++;
        x += dx;
        y += dy;
    }
    return dem;
}

TrangThaiGame kiemTraThangThua(BanCo* banCo, NuocDi nuocCuoi) {
    if (nuocCuoi.x < 0 || nuocCuoi.y < 0) return DANG_CHOI;
    
    int cacHuong[4][2] = {
        {1, 0},  // Ngang
        {0, 1},  // Dọc
        {1, 1},  // Chéo \ .
        {1, -1}  // Chéo /
    };
    
    for (int i = 0; i < 4; i++) {
        int dx = cacHuong[i][0];
        int dy = cacHuong[i][1];
        
        int dem = 1 + demTheoHuong(banCo, nuocCuoi, dx, dy) + demTheoHuong(banCo, nuocCuoi, -dx, -dy);
        
        if (dem >= banCo->dieuKienThang) {
            return (nuocCuoi.nguoiDanh == NGUOI_X) ? X_THANG : O_THANG;
        }
    }
    
    if (banCo->soNuocDaDanh >= banCo->kichThuoc * banCo->kichThuoc) {
        return HOA_NHAU;
    }
    
    return DANG_CHOI;
}
