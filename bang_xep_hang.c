#include "bang_xep_hang.h"

/* ================================================================
 * bang_xep_hang.c — Thành viên B
 * Chức năng: Quản lý bảng xếp hạng người chơi
 *
 * File lưu dạng TEXT, mỗi dòng một người:
 *   Alice 10 3 2
 *   Bob    5 8 1
 *   (tên — số ván thắng — số ván thua — số ván hòa)
 * ================================================================ */

/* ---------- HÀM NỘI BỘ ---------- */

// Đọc toàn bộ file bảng xếp hạng vào mảng
static int doc_tat_ca_ho_so(HoSoNguoiChoi danh_sach[], int so_phan_tu_toi_da) {
    FILE *file = fopen(FILE_BANG_XEP_HANG, "r");
    if (file == NULL) return 0;     // file chưa có → 0 người chơi

    int so_nguoi = 0;

    // Đọc từng dòng: tên, thắng, thua, hòa
    while (so_nguoi < so_phan_tu_toi_da &&
           fscanf(file, "%49s %d %d %d",
                  danh_sach[so_nguoi].ten,
                  &danh_sach[so_nguoi].so_van_thang,
                  &danh_sach[so_nguoi].so_van_thua,
                  &danh_sach[so_nguoi].so_van_hoa) == 4) {

        // Tính tổng số ván và tỷ lệ thắng
        danh_sach[so_nguoi].tong_so_van =
            danh_sach[so_nguoi].so_van_thang +
            danh_sach[so_nguoi].so_van_thua  +
            danh_sach[so_nguoi].so_van_hoa;

        if (danh_sach[so_nguoi].tong_so_van > 0)
            danh_sach[so_nguoi].ty_le_thang =
                (float)danh_sach[so_nguoi].so_van_thang
                / danh_sach[so_nguoi].tong_so_van * 100.0f;
        else
            danh_sach[so_nguoi].ty_le_thang = 0.0f;

        so_nguoi++;
    }

    fclose(file);
    return so_nguoi;
}

// Ghi toàn bộ mảng vào file (ghi đè)
static int ghi_tat_ca_ho_so(const HoSoNguoiChoi danh_sach[], int so_nguoi) {
    FILE *file = fopen(FILE_BANG_XEP_HANG, "w");    // "w" = ghi đè
    if (file == NULL) {
        fprintf(stderr, "[Bang xep hang] Loi: khong mo duoc file\n");
        return 0;
    }

    for (int i = 0; i < so_nguoi; i++) {
        fprintf(file, "%s %d %d %d\n",
                danh_sach[i].ten,
                danh_sach[i].so_van_thang,
                danh_sach[i].so_van_thua,
                danh_sach[i].so_van_hoa);
    }

    fclose(file);
    return 1;
}

// Sắp xếp giảm dần theo tỷ lệ thắng (Bubble Sort)
static void sap_xep_theo_ty_le_thang(HoSoNguoiChoi danh_sach[], int so_nguoi) {
    for (int luot = 0; luot < so_nguoi - 1; luot++) {
        for (int vi_tri = 0; vi_tri < so_nguoi - 1 - luot; vi_tri++) {

            int can_doi_cho = 0;

            // Tỷ lệ thắng thấp hơn → đổi chỗ
            if (danh_sach[vi_tri].ty_le_thang < danh_sach[vi_tri+1].ty_le_thang) {
                can_doi_cho = 1;
            }
            // Tỷ lệ bằng nhau → người thắng nhiều hơn lên trước
            else if (danh_sach[vi_tri].ty_le_thang == danh_sach[vi_tri+1].ty_le_thang &&
                     danh_sach[vi_tri].so_van_thang  < danh_sach[vi_tri+1].so_van_thang) {
                can_doi_cho = 1;
            }

            if (can_doi_cho) {
                HoSoNguoiChoi tam      = danh_sach[vi_tri];
                danh_sach[vi_tri]      = danh_sach[vi_tri+1];
                danh_sach[vi_tri+1]    = tam;
            }
        }
    }
}

// Tìm vị trí người chơi trong mảng theo tên (-1 nếu không có)
static int tim_vi_tri_trong_mang(HoSoNguoiChoi danh_sach[], int so_nguoi, const char *ten) {
    for (int i = 0; i < so_nguoi; i++) {
        if (strcmp(danh_sach[i].ten, ten) == 0)
            return i;
    }
    return -1;
}

/* ---------- HÀM CÔNG KHAI ---------- */

/*
 * cap_nhat_ket_qua — Cập nhật kết quả sau mỗi ván cờ
 *
 * Luồng xử lý:
 *   1. Đọc file vào mảng
 *   2. Tìm người thắng/thua (thêm mới nếu chưa có)
 *   3. Cộng thắng/thua/hòa
 *   4. Ghi lại mảng vào file
 */
void cap_nhat_ket_qua(const char *ten_nguoi_thang,
                      const char *ten_nguoi_thua,
                      const char *ten_nguoi_choi_1,
                      const char *ten_nguoi_choi_2,
                      int la_hoa) {

    HoSoNguoiChoi danh_sach[SO_NGUOI_CHOI_TOI_DA];
    int so_nguoi = doc_tat_ca_ho_so(danh_sach, SO_NGUOI_CHOI_TOI_DA);

    if (la_hoa) {
        // Ván hòa — cả hai người chơi +1 hòa
        const char *hai_nguoi[2] = { ten_nguoi_choi_1, ten_nguoi_choi_2 };

        for (int n = 0; n < 2; n++) {
            if (hai_nguoi[n] == NULL) continue;

            int vi_tri = tim_vi_tri_trong_mang(danh_sach, so_nguoi, hai_nguoi[n]);
            if (vi_tri == -1) {
                // Người mới — thêm vào cuối mảng
                if (so_nguoi >= SO_NGUOI_CHOI_TOI_DA) continue;
                strncpy(danh_sach[so_nguoi].ten, hai_nguoi[n], DO_DAI_TEN_TOI_DA - 1);
                danh_sach[so_nguoi].so_van_thang = 0;
                danh_sach[so_nguoi].so_van_thua  = 0;
                danh_sach[so_nguoi].so_van_hoa   = 1;
                so_nguoi++;
            } else {
                danh_sach[vi_tri].so_van_hoa++;
            }
        }

    } else {
        // Có người thắng/thua
        const char *hai_nguoi[2]   = { ten_nguoi_thang, ten_nguoi_thua };
        int         la_nguoi_thang[2] = { 1, 0 };   // 1=thắng, 0=thua

        for (int n = 0; n < 2; n++) {
            if (hai_nguoi[n] == NULL) continue;

            int vi_tri = tim_vi_tri_trong_mang(danh_sach, so_nguoi, hai_nguoi[n]);
            if (vi_tri == -1) {
                if (so_nguoi >= SO_NGUOI_CHOI_TOI_DA) continue;
                strncpy(danh_sach[so_nguoi].ten, hai_nguoi[n], DO_DAI_TEN_TOI_DA - 1);
                danh_sach[so_nguoi].so_van_thang = 0;
                danh_sach[so_nguoi].so_van_thua  = 0;
                danh_sach[so_nguoi].so_van_hoa   = 0;

                if (la_nguoi_thang[n]) danh_sach[so_nguoi].so_van_thang++;
                else                   danh_sach[so_nguoi].so_van_thua++;

                so_nguoi++;
            } else {
                if (la_nguoi_thang[n]) danh_sach[vi_tri].so_van_thang++;
                else                   danh_sach[vi_tri].so_van_thua++;
            }
        }
    }

    // Tính lại tỷ lệ thắng cho tất cả
    for (int i = 0; i < so_nguoi; i++) {
        danh_sach[i].tong_so_van = danh_sach[i].so_van_thang
                                 + danh_sach[i].so_van_thua
                                 + danh_sach[i].so_van_hoa;
        if (danh_sach[i].tong_so_van > 0)
            danh_sach[i].ty_le_thang =
                (float)danh_sach[i].so_van_thang / danh_sach[i].tong_so_van * 100.0f;
        else
            danh_sach[i].ty_le_thang = 0.0f;
    }

    ghi_tat_ca_ho_so(danh_sach, so_nguoi);
}

/*
 * hien_thi_bang_xep_hang — In bảng xếp hạng ra màn hình
 */
void hien_thi_bang_xep_hang(void) {
    HoSoNguoiChoi danh_sach[SO_NGUOI_CHOI_TOI_DA];
    int so_nguoi = doc_tat_ca_ho_so(danh_sach, SO_NGUOI_CHOI_TOI_DA);

    if (so_nguoi == 0) {
        printf("\n  Chua co du lieu bang xep hang.\n\n");
        return;
    }

    sap_xep_theo_ty_le_thang(danh_sach, so_nguoi);

    printf("\n");
    printf("+====+========================+=======+=======+=======+=========+\n");
    printf("| #  | Ten nguoi choi         | Thang | Thua  |  Hoa  | Ti le   |\n");
    printf("+====+========================+=======+=======+=======+=========+\n");

    for (int i = 0; i < so_nguoi; i++) {
        printf("| %-2d | %-22s | %-5d | %-5d | %-5d | %6.1f%% |\n",
               i + 1,
               danh_sach[i].ten,
               danh_sach[i].so_van_thang,
               danh_sach[i].so_van_thua,
               danh_sach[i].so_van_hoa,
               danh_sach[i].ty_le_thang);
    }

    printf("+----+------------------------+-------+-------+-------+---------+\n\n");
}

/*
 * tim_nguoi_choi — Tìm hồ sơ một người chơi theo tên
 */
int tim_nguoi_choi(const char *ten, HoSoNguoiChoi *ket_qua) {
    HoSoNguoiChoi danh_sach[SO_NGUOI_CHOI_TOI_DA];
    int so_nguoi = doc_tat_ca_ho_so(danh_sach, SO_NGUOI_CHOI_TOI_DA);

    int vi_tri = tim_vi_tri_trong_mang(danh_sach, so_nguoi, ten);
    if (vi_tri == -1) return 0;

    if (ket_qua != NULL) *ket_qua = danh_sach[vi_tri];
    return 1;
}

/*
 * xoa_bang_xep_hang — Xóa toàn bộ bảng xếp hạng
 */
int xoa_bang_xep_hang(void) {
    if (remove(FILE_BANG_XEP_HANG) == 0) {
        printf("[Bang xep hang] Da xoa toan bo du lieu.\n");
        return 1;
    }
    fprintf(stderr, "[Bang xep hang] Loi: khong xoa duoc file.\n");
    return 0;
}
