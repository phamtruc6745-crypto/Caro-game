#ifndef LOGIC_GAME_H
#define LOGIC_GAME_H

#include "cau_truc_du_lieu.h"

int dem_huong(char ban_co[KICH_THUOC_TOI_DA][KICH_THUOC_TOI_DA], int kich_thuoc, int hang, int cot, int delta_hang, int delta_cot, char nguoi_choi);
bool kiem_tra_thang(char ban_co[KICH_THUOC_TOI_DA][KICH_THUOC_TOI_DA], int kich_thuoc, int hang_cuoi, int cot_cuoi, char nguoi_choi, int so_quan_thang);
bool thuc_hien_hoan_tac(TrangThaiVanCo *van_co, int *hang_con_tro, int *cot_con_tro);

#endif
