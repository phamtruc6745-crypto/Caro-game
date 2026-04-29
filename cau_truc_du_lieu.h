#ifndef CAU_TRUC_DU_LIEU_H
#define CAU_TRUC_DU_LIEU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define KICH_THUOC_TOI_DA     15
#define DO_DAI_TEN_TOI_DA     50
#define SO_NUOC_DI_TOI_DA     (KICH_THUOC_TOI_DA * KICH_THUOC_TOI_DA)
#define FILE_LUU_GAME         "van_co_da_luu.bin"
#define FILE_BANG_XEP_HANG    "bang_xep_hang.txt"
#define SO_NGUOI_CHOI_TOI_DA  100

typedef struct {
    int  hang;
    int  cot;
    char nguoi_danh;
} MotNuocDi;

typedef struct {
    char ten[DO_DAI_TEN_TOI_DA];
    char ky_hieu;
} NguoiChoi;

typedef struct {
    char  chu_nhan_dien[4];
    int   phien_ban;
    time_t thoi_gian_luu;
    NguoiChoi nguoi_choi_1;
    NguoiChoi nguoi_choi_2;
    char      luot_hien_tai;
    
    int   kich_thuoc;      
    int   so_quan_thang;   

    char ban_co[KICH_THUOC_TOI_DA][KICH_THUOC_TOI_DA];
    MotNuocDi lich_su_nuoc_di[SO_NUOC_DI_TOI_DA];
    int       so_nuoc_da_di;
    int  game_da_ket_thuc;
    char nguoi_thang;
} TrangThaiVanCo;

typedef struct {
    char  ten[DO_DAI_TEN_TOI_DA];
    int   so_van_thang;
    int   so_van_thua;
    int   so_van_hoa;
    int   tong_so_van;
    float ty_le_thang;
} HoSoNguoiChoi;

#endif
