#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "giao_dien.h"
#include "logic_game.h"
#include "luu_tai_game.h"
#include "bang_xep_hang.h"

int main() {
    thiet_lap_console();
    TrangThaiVanCo van_co;
    memset(&van_co, 0, sizeof(TrangThaiVanCo));

    if (kiem_tra_co_file_luu(FILE_LUU_GAME)) {
        in_thong_tin_file_luu(FILE_LUU_GAME);
        printf("Tiep tuc? (Y/N): ");
        char c = _getch();
        if (c == 'y' || c == 'Y') tai_van_co(&van_co, FILE_LUU_GAME);
        else goto thiet_lap_moi;
    } else {
    thiet_lap_moi:
        printf("Ten Nguoi 1 (X): "); scanf(" %[^\n]", van_co.nguoi_choi_1.ten);
        printf("Ten Nguoi 2 (O): "); scanf(" %[^\n]", van_co.nguoi_choi_2.ten);
        van_co.nguoi_choi_1.ky_hieu = 'X'; van_co.nguoi_choi_2.ky_hieu = 'O'; van_co.luot_hien_tai = 'X';
        chon_che_do_choi(&van_co.kich_thuoc, &van_co.so_quan_thang);
        khoi_tao_ban_co(van_co.ban_co, van_co.kich_thuoc);
    }

    int hct = van_co.kich_thuoc/2, cct = van_co.kich_thuoc/2;
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    bool can_ve_lai = true; 
    printf("%s", ANSI_CLEAR); // Don sach man hinh 1 lan duy nhat

    while (!van_co.game_da_ket_thuc) {
        if (can_ve_lai) {
            int hc = -1, cc = -1;
            if (van_co.so_nuoc_da_di > 0) {
                hc = van_co.lich_su_nuoc_di[van_co.so_nuoc_da_di-1].hang;
                cc = van_co.lich_su_nuoc_di[van_co.so_nuoc_da_di-1].cot;
            }

            // [SUA LOI CHINH]: Dung ham nay de dua con tro ve goc (0,0) tuyet doi cua Buffer
            // Ban co se bi "dong dinh", khong bao gio bi truot toa do nua
            dat_con_tro_ve_dau(); 
            hien_thi_ban_co(van_co.ban_co, van_co.kich_thuoc, hct, cct, hc, cc);
            ve_thanh_trang_thai(cct, hct, van_co.luot_hien_tai);
            
            can_ve_lai = false; 
        }

        INPUT_RECORD sk; DWORD nDoc;
        ReadConsoleInput(hIn, &sk, 1, &nDoc);
        if (nDoc == 0) continue;

        bool danh = false;

        // XU LY PHIM & ENTER
        if (sk.EventType == KEY_EVENT && sk.Event.KeyEvent.bKeyDown) {
            int p = sk.Event.KeyEvent.wVirtualKeyCode;
            char k = sk.Event.KeyEvent.uChar.AsciiChar;
            
            if (p == VK_UP) hct = (hct - 1 + van_co.kich_thuoc) % van_co.kich_thuoc;
            else if (p == VK_DOWN) hct = (hct + 1) % van_co.kich_thuoc;
            else if (p == VK_LEFT) cct = (cct - 1 + van_co.kich_thuoc) % van_co.kich_thuoc;
            else if (p == VK_RIGHT) cct = (cct + 1) % van_co.kich_thuoc;
            else if (k == 'u' || k == 'U') thuc_hien_hoan_tac(&van_co, &hct, &cct);
            else if (k == 's' || k == 'S') { 
                luu_van_co(&van_co, FILE_LUU_GAME); 
                
                // Doi \n thanh \r de in de tai cho
                // Giai phap nay ngan chan hoan toan viec man hinh Terminal bi cuon xuong
                printf("\rDa luu thanh cong!      "); 
                
                Sleep(800); 
                printf("%s", ANSI_CLEAR); 
            }
            // Nhan dien danh co bang Enter (VK_RETURN), Phim cach (Space), hoac go X/O
            else if (p == VK_RETURN || k == 32 || k == 'x' || k == 'X' || k == 'o' || k == 'O') danh = true;
            
            can_ve_lai = true; 
        }
        // XU LY CHUOT
        else if (sk.EventType == MOUSE_EVENT) {
            if (sk.Event.MouseEvent.dwEventFlags == 0 || sk.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK) {
                if (sk.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    
                    // [SUA LOI CHINH]: Vi ban co bat dau chinh xac tu goc Buffer
                    // Lay thang toa do tuyet doi dwMousePosition, loai bo bu tru sai lech
                    int mx = sk.Event.MouseEvent.dwMousePosition.X;
                    int my = sk.Event.MouseEvent.dwMousePosition.Y;

                    // Cong thuc chuan khop voi ban co co duong ke ngang
                    if (mx >= 5 && my >= 1) {
                        int c_clk = (mx - 5) / 4;
                        int h_clk = (my - 1) / 2;
                        
                        // Neu bam hop le, di chuyen con tro va danh ngay lap tuc
                        if (h_clk >= 0 && h_clk < van_co.kich_thuoc && c_clk >= 0 && c_clk < van_co.kich_thuoc) { 
                            hct = h_clk; 
                            cct = c_clk; 
                            danh = true; 
                        }
                    }
                    can_ve_lai = true; 
                }
            }
        }

        // LOGIC KIEM TRA DANH CO
        if (danh && van_co.ban_co[hct][cct] == ' ') {
            van_co.ban_co[hct][cct] = van_co.luot_hien_tai;
            van_co.lich_su_nuoc_di[van_co.so_nuoc_da_di++] = (MotNuocDi){hct, cct, van_co.luot_hien_tai};
            
            if (kiem_tra_thang(van_co.ban_co, van_co.kich_thuoc, hct, cct, van_co.luot_hien_tai, van_co.so_quan_thang)) {
                van_co.game_da_ket_thuc = 1; van_co.nguoi_thang = van_co.luot_hien_tai;
            } else if (van_co.so_nuoc_da_di >= van_co.kich_thuoc * van_co.kich_thuoc) {
                van_co.game_da_ket_thuc = 1; van_co.nguoi_thang = 'H';
            } else {
                van_co.luot_hien_tai = (van_co.luot_hien_tai == 'X') ? 'O' : 'X';
            }
            can_ve_lai = true; 
        }
    }

    // Ket thuc game
    printf("%s", ANSI_CLEAR);
    hien_thi_ban_co(van_co.ban_co, van_co.kich_thuoc, hct, cct, -1, -1);
    if (van_co.nguoi_thang == 'H') cap_nhat_ket_qua(NULL, NULL, van_co.nguoi_choi_1.ten, van_co.nguoi_choi_2.ten, 1);
    else {
        char *th = (van_co.nguoi_thang == 'X') ? van_co.nguoi_choi_1.ten : van_co.nguoi_choi_2.ten;
        char *tu = (van_co.nguoi_thang == 'X') ? van_co.nguoi_choi_2.ten : van_co.nguoi_choi_1.ten;
        printf("\n %s THANG!\n", th);
        cap_nhat_ket_qua(th, tu, NULL, NULL, 0);
    }
    remove(FILE_LUU_GAME); 
    hien_thi_bang_xep_hang();
    printf(" Bam phim bat ky de thoat..."); _getch();
    return 0;
}
