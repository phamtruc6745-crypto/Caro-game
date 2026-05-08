#include "luu_tai_game.h"
#include <stdio.h>
#include <stdlib.h>

bool luuTrangThaiGame(const char* tenTep, BanCo* banCo, ThongTinNguoiChoi* ng1, ThongTinNguoiChoi* ng2, NguoiChoiHienTai luotHienTai, NganXep* lichSu) {
    FILE* tep = fopen(tenTep, "wb");
    if (!tep) return false;
    
    fwrite(banCo, sizeof(BanCo), 1, tep);
    fwrite(ng1, sizeof(ThongTinNguoiChoi), 1, tep);
    fwrite(ng2, sizeof(ThongTinNguoiChoi), 1, tep);
    fwrite(&luotHienTai, sizeof(NguoiChoiHienTai), 1, tep);
    
    int soLuong = 0;
    NodeNuocDi* hienTai = lichSu->dinh;
    while(hienTai) {
        soLuong++;
        hienTai = hienTai->tiepTheo;
    }
    fwrite(&soLuong, sizeof(int), 1, tep);
    
    if (soLuong > 0) {
        NuocDi* mangTam = (NuocDi*)malloc(soLuong * sizeof(NuocDi));
        if (mangTam) {
            hienTai = lichSu->dinh;
            for(int i = soLuong - 1; i >= 0; i--) {
                mangTam[i] = hienTai->nuocDi;
                hienTai = hienTai->tiepTheo;
            }
            fwrite(mangTam, sizeof(NuocDi), soLuong, tep);
            free(mangTam);
        }
    }
    
    fclose(tep);
    return true;
}

bool taiTrangThaiGame(const char* tenTep, BanCo* banCo, ThongTinNguoiChoi* ng1, ThongTinNguoiChoi* ng2, NguoiChoiHienTai* luotHienTai, NganXep* lichSu) {
    FILE* tep = fopen(tenTep, "rb");
    if (!tep) return false;
    
    fread(banCo, sizeof(BanCo), 1, tep);
    fread(ng1, sizeof(ThongTinNguoiChoi), 1, tep);
    fread(ng2, sizeof(ThongTinNguoiChoi), 1, tep);
    fread(luotHienTai, sizeof(NguoiChoiHienTai), 1, tep);
    
    int soLuong = 0;
    if (fread(&soLuong, sizeof(int), 1, tep) != 1) soLuong = 0;
    if (soLuong < 0 || soLuong > 1000) soLuong = 0; // Sanity check
    
    xoaNganXep(lichSu); 
    khoiTaoNganXep(lichSu);
    
    for(int i = 0; i < soLuong; i++) {
        NuocDi nuoc;
        fread(&nuoc, sizeof(NuocDi), 1, tep);
        themVaoNganXep(lichSu, nuoc);
    }
    
    fclose(tep);
    return true;
}
