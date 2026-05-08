#ifndef GIAODIEN_H
#define GIAODIEN_H

#include "cau_truc_du_lieu.h"
#include <stdbool.h>

void gotoXY(int x, int y);
void xoaManHinh();
void inHieuUngTieuDe();
void veBanCo(BanCo* banCo, int conTroX, int conTroY, NuocDi nuocCuoi, const char* tenHienTai, NguoiChoiHienTai luot);
void inMenuChinh();
void inMenuChonKichThuoc();
void inThongBao(const char* thongBao);

#endif // GIAODIEN_H
