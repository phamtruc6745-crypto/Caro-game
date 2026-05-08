#include "bang_xep_hang.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

float tinhTiLeThang(ThongTinNguoiChoi p) {
    int tong = p.thang + p.thua + p.hoa;
    if (tong == 0) return 0.0f;
    return ((float)p.thang / tong) * 100.0f;
}

void sapXepDanhSach(ThongTinNguoiChoi ds[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            float tiLe1 = tinhTiLeThang(ds[i]);
            float tiLe2 = tinhTiLeThang(ds[j]);
            
            if (tiLe2 > tiLe1 || (tiLe2 == tiLe1 && ds[j].thang > ds[i].thang)) {
                ThongTinNguoiChoi tam = ds[i];
                ds[i] = ds[j];
                ds[j] = tam;
            }
        }
    }
}

void capNhatBangXepHang(ThongTinNguoiChoi ng) {
    FILE* tep = fopen(TEP_BANG_XEP_HANG, "a+");
    if(!tep) {
        tep = fopen(TEP_BANG_XEP_HANG, "w");
        if(!tep) return;
    }
    
    fseek(tep, 0, SEEK_SET);
    ThongTinNguoiChoi danhSach[100];
    int tongSo = 0;
    while(fscanf(tep, " %49[^|]|%d|%d|%d", danhSach[tongSo].ten, &danhSach[tongSo].thang, &danhSach[tongSo].thua, &danhSach[tongSo].hoa) == 4) {
        tongSo++;
    }
    
    fclose(tep);
    
    bool daTimThay = false;
    for(int i = 0; i < tongSo; i++) {
        if(strcmp(danhSach[i].ten, ng.ten) == 0) {
            danhSach[i].thang += ng.thang;
            danhSach[i].thua += ng.thua;
            danhSach[i].hoa += ng.hoa;
            daTimThay = true;
            break;
        }
    }
    
    if(!daTimThay && tongSo < 100) {
        danhSach[tongSo++] = ng;
    }
    
    sapXepDanhSach(danhSach, tongSo);
    
    tep = fopen(TEP_BANG_XEP_HANG, "w");
    for(int i = 0; i < tongSo; i++) {
        fprintf(tep, "%s|%d|%d|%d\n", danhSach[i].ten, danhSach[i].thang, danhSach[i].thua, danhSach[i].hoa);
    }
    fclose(tep);
}

void hienThiBangXepHang() {
    FILE* tep = fopen(TEP_BANG_XEP_HANG, "r");
    if (!tep) {
        printf("Chua co du lieu bang xep hang.\n");
        return;
    }

    ThongTinNguoiChoi danhSach[100];
    int tongSo = 0;
    int maxNameLen = 20; // Độ dài tối thiểu cho cột tên

    while (fscanf(tep, " %49[^|]|%d|%d|%d", danhSach[tongSo].ten, &danhSach[tongSo].thang, &danhSach[tongSo].thua, &danhSach[tongSo].hoa) == 4) {
        int currentLen = strlen(danhSach[tongSo].ten);
        if (currentLen > maxNameLen) maxNameLen = currentLen;
        tongSo++;
        if (tongSo >= 100) break;
    }
    fclose(tep);

    if (tongSo == 0) {
        printf("Chua co du lieu bang xep hang.\n");
        return;
    }

    // Sắp xếp lại trước khi hiển thị để đảm bảo thứ tự đúng nhất
    sapXepDanhSach(danhSach, tongSo);

    printf("\n" GOC_TRAI MAU_DAM MAU_XANH_NGOC "=== BANG XEP HANG ===\n" DAT_LAI_MAU);
    
    // In tiêu đề với độ rộng cột tên linh hoạt
    printf(GOC_TRAI "%-*s | %-5s | %-5s | %-5s | %-10s\n", maxNameLen, "Ten Nguoi Choi", "Thang", "Thua", "Hoa", "Ty le thang");
    
    // In đường kẻ phân cách
    printf(GOC_TRAI);
    for (int i = 0; i < maxNameLen + 40; i++) printf("-");
    printf("\n");

    for (int i = 0; i < tongSo; i++) {
        float tiLe = tinhTiLeThang(danhSach[i]);
        printf(GOC_TRAI "%-*s | %-5d | %-5d | %-5d | %.2f%%\n", 
               maxNameLen, danhSach[i].ten, danhSach[i].thang, danhSach[i].thua, danhSach[i].hoa, tiLe);
    }
}
