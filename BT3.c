#include <stdio.h>
#include <string.h>

#define MAX_VE 100

struct VeMayBay {
    char maVe[15];
    char tenHanhKhach[50];
    char hangVe[20];
    float canNangHanhLy;
    float cuocHanhLy;
};

int main() {
    int n, i;
    float tongCuoc = 0;
    struct VeMayBay danhSachVe[MAX_VE];

    printf("Nhap so luong ve may bay: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
        printf("So luong ve khong hop le!\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);
        printf("Ma ve PNR: ");
        scanf("%s", danhSachVe[i].maVe);

        while (getchar() != '\n');

        printf("Ho ten hanh khach: ");
        fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin);
        danhSachVe[i].tenHanhKhach[strcspn(danhSachVe[i].tenHanhKhach, "\n")] = 0;

        printf("Hang ve (Business/Deluxe/Eco): ");
        scanf("%s", danhSachVe[i].hangVe);

        do {
            printf("Khoi luong hanh ly ky gui (kg): ");
            scanf("%f", &danhSachVe[i].canNangHanhLy);
            if (danhSachVe[i].canNangHanhLy < 0) {
                printf("Khoi luong hanh ly khong duoc am! Vui long nhap lai.\n");
            }
        } while (danhSachVe[i].canNangHanhLy < 0);

        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= 20) {
                danhSachVe[i].cuocHanhLy = 0;
            } else {
                danhSachVe[i].cuocHanhLy = (danhSachVe[i].canNangHanhLy - 20) * 50000;
            }
        } else {
            danhSachVe[i].cuocHanhLy = danhSachVe[i].canNangHanhLy * 50000;
        }
    }

    int maxIndex = 0;
    for (i = 1; i < n; i++) {
        if (danhSachVe[i].canNangHanhLy > danhSachVe[maxIndex].canNangHanhLy) {
            maxIndex = i;
        }
    }

    printf("\n================================== DANH SÁCH VÉ MÁY BAY CHUYẾN BAY ==================================\n");
    printf("%-5s %-12s %-25s %-12s %12s %15s\n", "STT", "MÃ VÉ", "HỌ TÊN HÀNH KHÁCH", "HẠNG VÉ", "HÀNH LÝ (KG)", "CƯỚC PHÍ (VNĐ)");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        tongCuoc += danhSachVe[i].cuocHanhLy;
        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
               i + 1,
               danhSachVe[i].maVe,
               danhSachVe[i].tenHanhKhach,
               danhSachVe[i].hangVe,
               danhSachVe[i].canNangHanhLy,
               danhSachVe[i].cuocHanhLy);
    }

    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Tổng tiền cước hành lý toàn chuyến: %.0f VNĐ\n", tongCuoc);
    printf("Vé có hành lý ký gửi nặng nhất: %s - %s (%.1f kg)\n",
           danhSachVe[maxIndex].maVe,
           danhSachVe[maxIndex].tenHanhKhach,
           danhSachVe[maxIndex].canNangHanhLy);

    char searchPNR[15];
    printf("\n--- CẬP NHẬT THÔNG TIN HÀNH LÝ ---\n");
    printf("Nhập mã vé PNR cần cập nhật hành lý: ");
    scanf("%s", searchPNR);

    int foundIndex = -1;
    for (i = 0; i < n; i++) {
        if (strcmp(danhSachVe[i].maVe, searchPNR) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("Tìm thấy mã vé %s. ", danhSachVe[foundIndex].maVe);
        do {
            printf("Nhập cân nặng hành lý ký gửi mới (kg): ");
            scanf("%f", &danhSachVe[foundIndex].canNangHanhLy);
            if (danhSachVe[foundIndex].canNangHanhLy < 0) {
                printf("Khoi luong hanh ly khong duoc am! Vui long nhap lai.\n");
            }
        } while (danhSachVe[foundIndex].canNangHanhLy < 0);

        if (strcmp(danhSachVe[foundIndex].hangVe, "Business") == 0) {
            if (danhSachVe[foundIndex].canNangHanhLy <= 20) {
                danhSachVe[foundIndex].cuocHanhLy = 0;
            } else {
                danhSachVe[foundIndex].cuocHanhLy = (danhSachVe[foundIndex].canNangHanhLy - 20) * 50000;
            }
        } else {
            danhSachVe[foundIndex].cuocHanhLy = danhSachVe[foundIndex].canNangHanhLy * 50000;
        }

        printf("Đã cập nhật cước hành lý mới: %.0f VNĐ.\n\n", danhSachVe[foundIndex].cuocHanhLy);

        printf("================================ DANH SÁCH VÉ MÁY BAY SAU CẬP NHẬT ================================\n");
        printf("%-5s %-12s %-25s %-12s %12s %15s\n", "STT", "MÃ VÉ", "HỌ TÊN HÀNH KHÁCH", "HẠNG VÉ", "HÀNH LÝ (KG)", "CƯỚC PHÍ (VNĐ)");
        printf("----------------------------------------------------------------------------------------------------\n");

        for (i = 0; i < n; i++) {
            printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
                   i + 1,
                   danhSachVe[i].maVe,
                   danhSachVe[i].tenHanhKhach,
                   danhSachVe[i].hangVe,
                   danhSachVe[i].canNangHanhLy,
                   danhSachVe[i].cuocHanhLy);
        }
        printf("----------------------------------------------------------------------------------------------------\n");
    } else {
        printf("Không tìm thấy mã vé PNR này trong hệ thống!\n");
    }

    return 0;
}