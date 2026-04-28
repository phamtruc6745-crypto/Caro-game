#ifndef CAU_TRUC_DU_LIEU_H
#define CAU_TRUC_DU_LIEU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ===================== HẰNG SỐ ===================== */
#define KICH_THUOC_BAN_CO     15
#define SO_QUAN_DE_THANG       5
#define DO_DAI_TEN_TOI_DA     50
#define SO_NUOC_DI_TOI_DA     (KICH_THUOC_BAN_CO * KICH_THUOC_BAN_CO)
#define FILE_LUU_GAME         "van_co_da_luu.bin"
#define FILE_BANG_XEP_HANG    "bang_xep_hang.txt"
#define SO_NGUOI_CHOI_TOI_DA  100

/* ===================== KIỂU DỮ LIỆU ===================== */

// Một nước đi trên bàn cờ
typedef struct {
    int  hang;          // hàng (0 đến 14)
    int  cot;           // cột (0 đến 14)
    char nguoi_danh;    // 'X' hoặc 'O'
} MotNuocDi;

// Thông tin một người chơi
typedef struct {
    char ten[DO_DAI_TEN_TOI_DA];
    char ky_hieu;       // 'X' hoặc 'O'
} NguoiChoi;

// Toàn bộ trạng thái ván cờ (dùng để lưu/tải)
typedef struct {
    // Nhận diện file
    char  chu_nhan_dien[4];     // "CARO" — xác nhận file hợp lệ
    int   phien_ban;            // phiên bản format (hiện tại = 1)
    time_t thoi_gian_luu;       // thời điểm bấm lưu

    // Người chơi
    NguoiChoi nguoi_choi_1;
    NguoiChoi nguoi_choi_2;
    char      luot_hien_tai;    // 'X' hoặc 'O'

    // Bàn cờ
    char ban_co[KICH_THUOC_BAN_CO][KICH_THUOC_BAN_CO]; // ' ', 'X', 'O'

    // Lịch sử nước đi
    MotNuocDi lich_su_nuoc_di[SO_NUOC_DI_TOI_DA];
    int       so_nuoc_da_di;

    // Kết quả
    int  game_da_ket_thuc;      // 0 = đang chơi, 1 = kết thúc
    char nguoi_thang;           // 'X', 'O', hoặc 'H' (hòa)
} TrangThaiVanCo;

// Hồ sơ người chơi trong bảng xếp hạng
typedef struct {
    char  ten[DO_DAI_TEN_TOI_DA];
    int   so_van_thang;
    int   so_van_thua;
    int   so_van_hoa;
    int   tong_so_van;
    float ty_le_thang;          // tính bằng %
} HoSoNguoiChoi;

#endif /* CAU_TRUC_DU_LIEU_H */
