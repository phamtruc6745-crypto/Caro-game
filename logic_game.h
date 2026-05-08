#ifndef LUATCHOI_H
#define LUATCHOI_H

#include "cau_truc_du_lieu.h"
#include <stdbool.h>

void khoiTaoBanCo(BanCo* banCo, int kichThuoc, int dkThang);
bool nuocDiHopLe(BanCo* banCo, int x, int y);
void danhCo(BanCo* banCo, NuocDi nuoc);
void hoanTacNuocDi(BanCo* banCo, NuocDi nuoc);
TrangThaiGame kiemTraThangThua(BanCo* banCo, NuocDi nuocCuoi);

#endif // LUATCHOI_H
