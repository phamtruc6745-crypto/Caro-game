/* ================================================================
 * kiem_thu.c — Kiểm thử toàn bộ code Thành viên B
 * Chạy: gcc kiem_thu.c luu_tai_game.c bang_xep_hang.c -o kiem_thu && ./kiem_thu
 * ================================================================ */

#include <stdio.h>
#include "cau_truc_du_lieu.h"
#include "luu_tai_game.h"
#include "bang_xep_hang.h"

// Tạo một ván cờ giả để kiểm thử
static TrangThaiVanCo tao_van_co_gia(void) {
    TrangThaiVanCo van_co;
    memset(&van_co, 0, sizeof(TrangThaiVanCo));

    strncpy(van_co.nguoi_choi_1.ten, "Alice", DO_DAI_TEN_TOI_DA - 1);
    van_co.nguoi_choi_1.ky_hieu = 'X';
    strncpy(van_co.nguoi_choi_2.ten, "Bob", DO_DAI_TEN_TOI_DA - 1);
    van_co.nguoi_choi_2.ky_hieu = 'O';
    van_co.luot_hien_tai = 'X';

    // Làm trống bàn cờ
    for (int i = 0; i < KICH_THUOC_BAN_CO; i++)
        for (int j = 0; j < KICH_THUOC_BAN_CO; j++)
            van_co.ban_co[i][j] = ' ';

    // Giả lập 3 nước đi
    van_co.lich_su_nuoc_di[0] = (MotNuocDi){7, 7, 'X'};
    van_co.lich_su_nuoc_di[1] = (MotNuocDi){7, 8, 'O'};
    van_co.lich_su_nuoc_di[2] = (MotNuocDi){6, 7, 'X'};
    van_co.ban_co[7][7] = 'X';
    van_co.ban_co[7][8] = 'O';
    van_co.ban_co[6][7] = 'X';
    van_co.so_nuoc_da_di = 3;

    return van_co;
}

int main(void) {
    printf("===== KIEM THU THANH VIEN B =====\n\n");

    /* --- Kiểm thử lưu game --- */
    printf("--- Kiem thu 1: Luu van co ---\n");
    TrangThaiVanCo van_co_goc = tao_van_co_gia();
    int ket_qua = luu_van_co(&van_co_goc, "test_luu.bin");
    printf("Luu game: %s\n\n", ket_qua ? "PASS" : "FAIL");

    /* --- Kiểm thử in thông tin file lưu --- */
    printf("--- Kiem thu 2: Xem thong tin file luu ---\n");
    in_thong_tin_file_luu("test_luu.bin");
    printf("\n");

    /* --- Kiểm thử tải game --- */
    printf("--- Kiem thu 3: Tai lai van co ---\n");
    TrangThaiVanCo van_co_tai_lai;
    ket_qua = tai_van_co(&van_co_tai_lai, "test_luu.bin");
    printf("Tai game: %s\n", ket_qua ? "PASS" : "FAIL");
    if (ket_qua) {
        printf("  Nguoi choi 1: %s\n", van_co_tai_lai.nguoi_choi_1.ten);
        printf("  Nguoi choi 2: %s\n", van_co_tai_lai.nguoi_choi_2.ten);
        printf("  So nuoc da di: %d\n", van_co_tai_lai.so_nuoc_da_di);
    }
    printf("\n");

    /* --- Kiểm thử tải file không tồn tại --- */
    printf("--- Kiem thu 4: Tai file khong ton tai ---\n");
    TrangThaiVanCo van_co_rong;
    ket_qua = tai_van_co(&van_co_rong, "khong_co_file_nay.bin");
    printf("Phai bao loi (FAIL = dung): %s\n\n", !ket_qua ? "DUNG" : "SAI");

    /* --- Kiểm thử bảng xếp hạng --- */
    printf("--- Kiem thu 5: Bang xep hang ---\n");
    remove("bang_xep_hang.txt");    // xóa file cũ trước khi test

    cap_nhat_ket_qua("Alice", "Bob",   NULL,    NULL,    0);
    cap_nhat_ket_qua("Alice", "Carol", NULL,    NULL,    0);
    cap_nhat_ket_qua("Bob",   "Carol", NULL,    NULL,    0);
    cap_nhat_ket_qua(NULL,    NULL,    "Alice", "Bob",   1); // hòa
    cap_nhat_ket_qua("Carol", "Alice", NULL,    NULL,    0);

    hien_thi_bang_xep_hang();

    /* --- Kiểm thử tìm người chơi --- */
    printf("--- Kiem thu 6: Tim nguoi choi ---\n");
    HoSoNguoiChoi ho_so;
    if (tim_nguoi_choi("Alice", &ho_so)) {
        printf("Alice: %d thang / %d thua / %d hoa / %.1f%%\n",
               ho_so.so_van_thang,
               ho_so.so_van_thua,
               ho_so.so_van_hoa,
               ho_so.ty_le_thang);
    }

    /* Dọn dẹp file test */
    remove("test_luu.bin");
    remove("bang_xep_hang.txt");

    printf("\n===== XONG =====\n");
    return 0;
}
