#include "logic_game.h"

int dem_huong(char ban_co[KICH_THUOC_TOI_DA][KICH_THUOC_TOI_DA], int kich_thuoc, int hang, int cot, int delta_hang, int delta_cot, char nguoi_choi) {
    int dem = 0, r = hang + delta_hang, c = cot + delta_cot;
    while (r >= 0 && r < kich_thuoc && c >= 0 && c < kich_thuoc && ban_co[r][c] == nguoi_choi) {
        dem++; r += delta_hang; c += delta_cot;
    }
    return dem;
}

bool kiem_tra_thang(char ban_co[KICH_THUOC_TOI_DA][KICH_THUOC_TOI_DA], int kich_thuoc, int hang_cuoi, int cot_cuoi, char nguoi_choi, int so_quan_thang) {
    if (hang_cuoi == -1 || cot_cuoi == -1) return false;
    int dr[] = {0, 1, 1, 1}, dc[] = {1, 0, 1, -1};
    for (int i = 0; i < 4; i++) {
        if (1 + dem_huong(ban_co, kich_thuoc, hang_cuoi, cot_cuoi, dr[i], dc[i], nguoi_choi) +
            dem_huong(ban_co, kich_thuoc, hang_cuoi, cot_cuoi, -dr[i], -dc[i], nguoi_choi) >= so_quan_thang)
            return true;
    }
    return false;
}

bool thuc_hien_hoan_tac(TrangThaiVanCo *van_co, int *hang_con_tro, int *cot_con_tro) {
    if (van_co->so_nuoc_da_di <= 0) return false;
    van_co->so_nuoc_da_di--;
    MotNuocDi n = van_co->lich_su_nuoc_di[van_co->so_nuoc_da_di];
    van_co->ban_co[n.hang][n.cot] = ' ';
    van_co->luot_hien_tai = n.nguoi_danh;
    *hang_con_tro = n.hang; *cot_con_tro = n.cot;
    return true;
}
