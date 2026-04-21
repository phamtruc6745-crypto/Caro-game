#include <stdio.h>
#include <string.h>
#include "cautruc.h"

// Sap xep danh sach nguoi choi theo so tran thang giam dan
void sap_xep_nguoi_choi(NguoiChoi ds[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ds[i].so_tran_thang < ds[j].so_tran_thang) {
                NguoiChoi tam = ds[i];
                ds[i] = ds[j];
                ds[j] = tam;
            }
        }
    }
}

// Ghi ket qua vao file log (Text file)
void ghi_lich_su(char *ten, int ket_qua) {
    FILE *f = fopen("lichsu.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s %d\n", ten, ket_qua);
        fclose(f);
    }
}

// Hien thi bang xep hang
void hien_thi_leaderboard() {
    FILE *f = fopen("lichsu.txt", "r");
    if (f == NULL) return;

    NguoiChoi ds[100];
    int n = 0;
    
    // Doc du lieu va tinh toan (Logic mau)
    while (fscanf(f, "%s %d", ds[n].ten_nguoi_choi, &ds[n].so_tran_thang) != EOF) {
        n++;
    }
    fclose(f);

    sap_xep_nguoi_choi(ds, n);

    printf("\n--- BANG XEP HANG ---\n");
    for (int i = 0; i < n && i < 10; i++) {
        printf("%d. %s - Thang: %d\n", i + 1, ds[i].ten_nguoi_choi, ds[i].so_tran_thang);
    }
}
