#ifndef GIAODIEN_H
#define GIAODIEN_H

#include "cautruc.h"
#include <stdbool.h>

// Toa do dong bat dau cua hang 0 tren ban co (duoc do dong sau moi lan ve)
// Dung thay cho TOA_DO_Y_BAT_DAU de tranh loi lech do man hinh scroll
extern int g_hangBatDauBanCo;
extern int g_toaDoY_Prompt;

void xoaManHinh();
void veBanCo(BanCo* banCo, int conTroX, int conTroY, NuocDi nuocCuoi, bool veDayDu);
void inMenuChinh();
void inMenuKichThuoc();
void inThongBao(const char* thongBao);

#endif // GIAODIEN_H
