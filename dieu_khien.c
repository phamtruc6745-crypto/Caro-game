#include "dieu_khien.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>

#ifndef ENABLE_QUICK_EDIT_MODE
#define ENABLE_QUICK_EDIT_MODE 0x0040
#endif

HANDLE hDauVao;
DWORD cheDoCu;

void khoiTaoDieuKhien() {
    hDauVao = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hDauVao, &cheDoCu);
    DWORD cheDoMoi = cheDoCu;
    cheDoMoi &= ~ENABLE_QUICK_EDIT_MODE;
    cheDoMoi |= ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS;
    cheDoMoi &= ~ENABLE_MOUSE_INPUT;
    SetConsoleMode(hDauVao, cheDoMoi);
}

SuKienNhap layLenhDieuKhien() {
    hDauVao = GetStdHandle(STD_INPUT_HANDLE);
    SuKienNhap suKien = {PHIM_KHAC, false, -1, -1};
    INPUT_RECORD boDem[128];
    DWORD soLuongDocDuoc;
    
    while (1) {
        ReadConsoleInput(hDauVao, boDem, 128, &soLuongDocDuoc);
        for (DWORD i = 0; i < soLuongDocDuoc; i++) {
            if (boDem[i].EventType == KEY_EVENT && boDem[i].Event.KeyEvent.bKeyDown) {
                WORD maPhim = boDem[i].Event.KeyEvent.wVirtualKeyCode;
                char kyTu = boDem[i].Event.KeyEvent.uChar.AsciiChar;
                
                switch(maPhim) {
                    case VK_UP: suKien.phim = PHIM_LEN; return suKien;
                    case VK_DOWN: suKien.phim = PHIM_XUONG; return suKien;
                    case VK_LEFT: suKien.phim = PHIM_TRAI; return suKien;
                    case VK_RIGHT: suKien.phim = PHIM_PHAI; return suKien;
                    case VK_RETURN: suKien.phim = PHIM_ENTER; return suKien;
                    case VK_SPACE: suKien.phim = PHIM_SPACE; return suKien;
                    case VK_ESCAPE: suKien.phim = PHIM_ESC; return suKien;
                }
                
                if (kyTu == 'u' || kyTu == 'U') { suKien.phim = PHIM_UNDO; return suKien; }
                if (kyTu == 's' || kyTu == 'S') { suKien.phim = PHIM_SAVE; return suKien; }
                if (kyTu == 'r' || kyTu == 'R') { suKien.phim = PHIM_DAU_HANG; return suKien; }
                if (kyTu == 'd' || kyTu == 'D') { suKien.phim = PHIM_XIN_HOA; return suKien; }
                if (kyTu == 'y' || kyTu == 'Y') { suKien.phim = PHIM_Y; return suKien; }
                if (kyTu == 'n' || kyTu == 'N') { suKien.phim = PHIM_N; return suKien; }
            }
        }
    }
    return suKien;
}
#else
void khoiTaoDieuKhien() {}
SuKienNhap layLenhDieuKhien() {
    SuKienNhap suKien = {PHIM_KHAC, false, -1, -1};
    return suKien;
}
#endif
