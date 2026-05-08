#ifndef LUU_TAI_GAME_H
#define LUU_TAI_GAME_H

#include "cau_truc_du_lieu.h"
#include "ngan_xep.h"
#include <stdbool.h>

#define TEP_LUU_GAME "luu_game.bin"

bool luuTrangThaiGame(const char* tenTep, BanCo* banCo, ThongTinNguoiChoi* ng1, ThongTinNguoiChoi* ng2, NguoiChoiHienTai luotHienTai, NganXep* lichSu);
bool taiTrangThaiGame(const char* tenTep, BanCo* banCo, ThongTinNguoiChoi* ng1, ThongTinNguoiChoi* ng2, NguoiChoiHienTai* luotHienTai, NganXep* lichSu);

#endif // LUU_TAI_GAME_H
