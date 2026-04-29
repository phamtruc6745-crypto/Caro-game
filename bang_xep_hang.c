#include "bang_xep_hang.h"

static int doc_ho_so(HoSoNguoiChoi ds[], int max_p) {
    FILE *f = fopen(FILE_BANG_XEP_HANG, "r");
    if (!f) return 0;
    int n = 0;
    while (n < max_p && fscanf(f, "%[^,],%d,%d,%d\n", ds[n].ten, &ds[n].so_van_thang, &ds[n].so_van_thua, &ds[n].so_van_hoa) == 4) {
        ds[n].tong_so_van = ds[n].so_van_thang + ds[n].so_van_thua + ds[n].so_van_hoa;
        ds[n].ty_le_thang = ds[n].tong_so_van ? (float)ds[n].so_van_thang/ds[n].tong_so_van*100 : 0;
        n++;
    }
    fclose(f);
    return n;
}

static void ghi_ho_so(const HoSoNguoiChoi ds[], int n) {
    FILE *f = fopen(FILE_BANG_XEP_HANG, "w");
    if (!f) return;
    for (int i = 0; i < n; i++) fprintf(f, "%s,%d,%d,%d\n", ds[i].ten, ds[i].so_van_thang, ds[i].so_van_thua, ds[i].so_van_hoa);
    fclose(f);
}

static int tim_vt(HoSoNguoiChoi ds[], int n, const char *t) {
    for (int i = 0; i < n; i++) if (!strcmp(ds[i].ten, t)) return i;
    return -1;
}

void cap_nhat_ket_qua(const char *t_thang, const char *t_thua, const char *p1, const char *p2, int hoa) {
    HoSoNguoiChoi ds[SO_NGUOI_CHOI_TOI_DA];
    int n = doc_ho_so(ds, SO_NGUOI_CHOI_TOI_DA);

    if (hoa) {
        const char *p[2] = {p1, p2};
        for (int i=0; i<2; i++) {
            int vt = tim_vt(ds, n, p[i]);
            if (vt == -1 && n < SO_NGUOI_CHOI_TOI_DA) {
                strcpy(ds[n].ten, p[i]); ds[n].so_van_thang=0; ds[n].so_van_thua=0; ds[n].so_van_hoa=1; n++;
            } else if (vt != -1) ds[vt].so_van_hoa++;
        }
    } else {
        const char *p[2] = {t_thang, t_thua};
        for (int i=0; i<2; i++) {
            int vt = tim_vt(ds, n, p[i]);
            if (vt == -1 && n < SO_NGUOI_CHOI_TOI_DA) {
                strcpy(ds[n].ten, p[i]); ds[n].so_van_thang = (i==0); ds[n].so_van_thua = (i==1); ds[n].so_van_hoa=0; n++;
            } else if (vt != -1) { if (i==0) ds[vt].so_van_thang++; else ds[vt].so_van_thua++; }
        }
    }
    ghi_ho_so(ds, n);
}

void hien_thi_bang_xep_hang(void) {
    HoSoNguoiChoi ds[SO_NGUOI_CHOI_TOI_DA];
    int n = doc_ho_so(ds, SO_NGUOI_CHOI_TOI_DA);
    if (!n) { printf("\nChua co du lieu.\n"); return; }
    printf("\n+====+========================+=======+=======+=======+=========+\n");
    printf("| #  | Ten nguoi choi         | Thang | Thua  |  Hoa  | Ti le   |\n");
    printf("+====+========================+=======+=======+=======+=========+\n");
    for (int i = 0; i < n; i++) printf("| %-2d | %-22s | %-5d | %-5d | %-5d | %6.1f%% |\n", i+1, ds[i].ten, ds[i].so_van_thang, ds[i].so_van_thua, ds[i].so_van_hoa, ds[i].ty_le_thang);
    printf("+----+------------------------+-------+-------+-------+---------+\n");
}
