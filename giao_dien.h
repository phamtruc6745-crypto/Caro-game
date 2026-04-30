#ifndef GIAO_DIEN_H
#define GIAO_DIEN_H

#include "cau_truc_du_lieu.h"

// Dinh nghia cac ma mau ANSI de lam giao dien dep hon
#define ANSI_RESET      "\x1B[0m"
#define ANSI_CLEAR      "\x1B[2J\x1B[H"
#define ANSI_HOME       "\x1B[H"         
#define ANSI_RED        "\x1B[91;1m"   // Do sang cho X
#define ANSI_CYAN       "\x1B[96;1m"   // Xanh sang cho O
#define ANSI_GREEN      "\x1B[92;1m"
#define ANSI_YELLOW     "\x1B[93;1m"
#define ANSI_MAGENTA    "\x1B[95;1m"
#define ANSI_BG_YELLOW  "\x1B[43m"
#define ANSI_BG_BLUE    "\x1B[44m"     // Nen xanh cho thanh trang thai
#define ANSI_BLACK      "\x1B[30m"
#define ANSI_WHITE_BOLD "\x1B[97;1m"

// Su dung ky tu UTF-8 ve vien bang co cho dep va lien mach
#define H_LINE "\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80" // ---
#define V_LINE "\xE2\x94\x82"                         // |
#define CROSS  "\xE2\x94\xBC"                         // +

void thiet_lap_console(void);
void dat_con_tro_ve_dau(void);
void chon_che_do_choi(int *kich_thuoc, int *so_quan_thang);
void ve_thanh_trang_thai(int cot_con_tro, int hang_con_tro, char luot);
void khoi_tao_ban_co(char ban_co[KICH_THUOC_TOI_DA][KICH_THUOC_TOI_DA], int kich_thuoc);
void hien_thi_ban_co(char ban_co[KICH_THUOC_TOI_DA][KICH_THUOC_TOI_DA], int kich_thuoc, int hang_con_tro, int cot_con_tro, int hang_cuoi, int cot_cuoi);

#endif
