#include <stdio.h>
#include "cautruc.h"

// Ham luu vao file nhi phan
void luu_game(TrangThaiGame g, char *ten_file) {
    FILE *f = fopen(ten_file, "wb");
    if (f == NULL) {
        printf("Loi: Khong the mo file de luu!\n");
        return;
    }
    fwrite(&g, sizeof(TrangThaiGame), 1, f);
    fclose(f);
    printf("Da luu vao file: %s\n", ten_file);
}

// Ham doc tu file nhi phan
int tai_game(TrangThaiGame *g, char *ten_file) {
    FILE *f = fopen(ten_file, "rb");
    if (f == NULL) {
        printf("Loi: Khong tim thay file save!\n");
        return 0;
    }
    fread(g, sizeof(TrangThaiGame), 1, f);
    fclose(f);
    return 1;
}
