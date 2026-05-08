#ifndef DIEUKHIEN_H
#define DIEUKHIEN_H

#include <stdbool.h>

typedef enum {
    PHIM_LEN,
    PHIM_XUONG,
    PHIM_TRAI,
    PHIM_PHAI,
    PHIM_ENTER,
    PHIM_SPACE,
    PHIM_UNDO,
    PHIM_SAVE,
    PHIM_ESC,
    PHIM_DAU_HANG,
    PHIM_XIN_HOA,
    PHIM_Y,
    PHIM_N,
    PHIM_KHAC
} LoaiPhim;

typedef struct {
    LoaiPhim phim;
    bool laChuot;
    int toaDoX;
    int toaDoY;
} SuKienNhap;

void khoiTaoDieuKhien();
SuKienNhap layLenhDieuKhien();

#endif // DIEUKHIEN_H
