#include "ai.h"
#include <stdlib.h>
#include <time.h>

// Điểm số cho các tình huống
const int DIEM_TAN_CONG[] = {0, 4, 25, 200, 3000, 100000};
const int DIEM_PHONG_THU[] = {0, 2, 18, 150, 1500, 80000};

// Hàm lượng giá cho một ô cờ cụ thể
long long luongGiaO(BanCo* banCo, int x, int y, NguoiChoiHienTai nguoiTa, NguoiChoiHienTai nguoiMinh) {
    long long tongDiem = 0;
    int huongX[] = {1, 0, 1, 1};
    int huongY[] = {0, 1, 1, -1};

    for (int h = 0; h < 4; h++) {
        int ta = 0, minh = 0;

        // Kiểm tra theo hướng h và hướng ngược lại
        for (int i = 1; i <= 4; i++) {
            int nx = x + i * huongX[h];
            int ny = y + i * huongY[h];
            if (nx >= 0 && nx < banCo->kichThuoc && ny >= 0 && ny < banCo->kichThuoc) {
                if (banCo->luoi[ny][nx] == nguoiMinh) minh++;
                else if (banCo->luoi[ny][nx] == nguoiTa) { ta++; break; }
                else break;
            } else { ta++; break; }
        }

        for (int i = 1; i <= 4; i++) {
            int nx = x - i * huongX[h];
            int ny = y - i * huongY[h];
            if (nx >= 0 && nx < banCo->kichThuoc && ny >= 0 && ny < banCo->kichThuoc) {
                if (banCo->luoi[ny][nx] == nguoiMinh) minh++;
                else if (banCo->luoi[ny][nx] == nguoiTa) { ta++; break; }
                else break;
            } else { ta++; break; }
        }

        tongDiem += DIEM_TAN_CONG[minh];
        
        // Xét phòng thủ
        int ta_thu = 0, minh_thu = 0;
        for (int i = 1; i <= 4; i++) {
            int nx = x + i * huongX[h];
            int ny = y + i * huongY[h];
            if (nx >= 0 && nx < banCo->kichThuoc && ny >= 0 && ny < banCo->kichThuoc) {
                if (banCo->luoi[ny][nx] == nguoiTa) ta_thu++;
                else if (banCo->luoi[ny][nx] == nguoiMinh) { minh_thu++; break; }
                else break;
            } else { minh_thu++; break; }
        }
        for (int i = 1; i <= 4; i++) {
            int nx = x - i * huongX[h];
            int ny = y - i * huongY[h];
            if (nx >= 0 && nx < banCo->kichThuoc && ny >= 0 && ny < banCo->kichThuoc) {
                if (banCo->luoi[ny][nx] == nguoiTa) ta_thu++;
                else if (banCo->luoi[ny][nx] == nguoiMinh) { minh_thu++; break; }
                else break;
            } else { minh_thu++; break; }
        }
        tongDiem += DIEM_PHONG_THU[ta_thu];
    }
    return tongDiem;
}

NuocDi timNuocDiMay(BanCo* banCo, NguoiChoiHienTai nguoiMay) {
    NuocDi nuocTotNhat = {-1, -1, nguoiMay};
    long long diemCaoNhat = -1;
    NguoiChoiHienTai nguoiChoi = (nguoiMay == NGUOI_X) ? NGUOI_O : NGUOI_X;

    // Cấp độ Dễ: 40% đánh ngẫu nhiên một ô trống bất kỳ
    if (capDoHienTai == DE) {
        if (rand() % 100 < 40) {
            int attempts = 0;
            while (attempts < 100) {
                int rx = rand() % banCo->kichThuoc;
                int ry = rand() % banCo->kichThuoc;
                if (banCo->luoi[ry][rx] == O_TRONG) {
                    nuocTotNhat.x = rx;
                    nuocTotNhat.y = ry;
                    return nuocTotNhat;
                }
                attempts++;
            }
        }
    }

    // Nếu là nước đầu tiên của máy và bàn cờ trống (hoặc chỉ 1 nước), đánh ở giữa
    if (banCo->soNuocDaDanh == 0 || (banCo->soNuocDaDanh == 1 && banCo->luoi[banCo->kichThuoc/2][banCo->kichThuoc/2] == O_TRONG)) {
        nuocTotNhat.x = banCo->kichThuoc / 2;
        nuocTotNhat.y = banCo->kichThuoc / 2;
        return nuocTotNhat;
    }

    // Tìm nước đi tốt nhất dựa trên điểm lượng giá
    for (int i = 0; i < banCo->kichThuoc; i++) {
        for (int j = 0; j < banCo->kichThuoc; j++) {
            if (banCo->luoi[i][j] == O_TRONG) {
                long long diem = luongGiaO(banCo, j, i, nguoiChoi, nguoiMay);
                
                // Cấp độ Khó: Ưu tiên thêm các ô gần trung tâm hơn nếu điểm bằng nhau
                if (capDoHienTai == KHO) {
                    int dx = j - banCo->kichThuoc/2;
                    int dy = i - banCo->kichThuoc/2;
                    diem += (banCo->kichThuoc - abs(dx) - abs(dy)); 
                }

                if (diem > diemCaoNhat) {
                    diemCaoNhat = diem;
                    nuocTotNhat.x = j;
                    nuocTotNhat.y = i;
                } else if (diem == diemCaoNhat) {
                    // Nếu điểm bằng nhau, chọn ngẫu nhiên để tránh máy đánh quá máy móc
                    if (rand() % 2 == 0) {
                        nuocTotNhat.x = j;
                        nuocTotNhat.y = i;
                    }
                }
            }
        }
    }

    return nuocTotNhat;
}
