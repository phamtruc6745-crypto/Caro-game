#ifndef CAUTRUC_H
#define CAUTRUC_H

#define KICH_THUOC 15 // Kich thuoc ban co 15x15

typedef struct {
    char ten_nguoi_choi[50];
    int so_tran_thang;
    float ty_le_thang;
} NguoiChoi;

typedef struct {
    char ban_co[KICH_THUOC][KICH_THUOC];
    char luot_di; // 'X' hoac 'O'
    char ten_p1[50];
    char ten_p2[50];
} TrangThaiGame;

#endif
