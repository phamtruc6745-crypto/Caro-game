#include "luu_tai_game.h"

int luu_van_co(const TrangThaiVanCo *t, const char *ten_f) {
    FILE *f = fopen(ten_f, "wb");
    if (!f) return 0;
    TrangThaiVanCo s = *t;
    memcpy(s.chu_nhan_dien, "CARO", 4); s.phien_ban = 1; s.thoi_gian_luu = time(NULL);
    size_t r = fwrite(&s, sizeof(TrangThaiVanCo), 1, f);
    fclose(f);
    return r == 1;
}

int tai_van_co(TrangThaiVanCo *t, const char *ten_f) {
    FILE *f = fopen(ten_f, "rb");
    if (!f) return 0;
    TrangThaiVanCo d;
    size_t r = fread(&d, sizeof(TrangThaiVanCo), 1, f);
    fclose(f);
    if (r != 1 || memcmp(d.chu_nhan_dien, "CARO", 4) || d.phien_ban != 1) return 0;
    *t = d; return 1;
}

int kiem_tra_co_file_luu(const char *f) {
    FILE *file = fopen(f, "rb");
    if (!file) return 0;
    fclose(file); return 1;
}

void in_thong_tin_file_luu(const char *f) {
    TrangThaiVanCo d;
    FILE *file = fopen(f, "rb");
    if (fread(&d, sizeof(TrangThaiVanCo), 1, file) == 1) {
        printf("Van co: %s vs %s (%d nuoc)\n", d.nguoi_choi_1.ten, d.nguoi_choi_2.ten, d.so_nuoc_da_di);
    }
    fclose(file);
}
