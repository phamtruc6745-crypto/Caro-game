#ifndef CAUTRUC_H
#define CAUTRUC_H

#define KICH_THUOC_TOI_DA 15

// Màu sắc ANSI
#define MAU_DO     "\x1b[31m"
#define MAU_XANH_LA   "\x1b[32m"
#define MAU_VANG  "\x1b[33m"
#define MAU_XANH_DUONG    "\x1b[34m"
#define MAU_HONG "\x1b[35m"
#define MAU_XANH_NGOC    "\x1b[36m"
#define MAU_NEN_XANH "\x1b[44m"
#define MAU_DAM       "\x1b[1m"
#define DAT_LAI_MAU   "\x1b[0m"

#define GOC_TRAI "          "
#define TOA_DO_Y_BAT_DAU 9
#define TOA_DO_X_BAT_DAU 14

typedef enum {
    O_TRONG = 0,
    NGUOI_X = 1,
    NGUOI_O = 2
} NguoiChoiHienTai;

typedef struct {
    char ten[50];
    int thang;
    int thua;
    int hoa;
} ThongTinNguoiChoi;

typedef struct {
    int x;
    int y;
    NguoiChoiHienTai nguoiDanh;
} NuocDi;

typedef struct {
    NguoiChoiHienTai luoi[KICH_THUOC_TOI_DA][KICH_THUOC_TOI_DA];
    int soNuocDaDanh;
    int kichThuoc;          
    int dieuKienThang;  
} BanCo;

typedef enum {
    DANG_CHOI,
    X_THANG,
    O_THANG,
    HOA_NHAU,
    X_DAU_HANG,
    O_DAU_HANG
} TrangThaiGame;

#endif // CAUTRUC_H
