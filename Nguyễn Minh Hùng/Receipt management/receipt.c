#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define VAT_RATE 0.1

typedef struct {
    char tenSanPham[50];
    double gia;
    int soLuong;
} SanPham;

typedef enum {
    TIEN_MAT,
    THE_TIN_DUNG,
    CHUYEN_KHOAN,
    VI_DIEN_TU
} PhuongThucThanhToan;

void inHoaDon(SanPham sanPhams[], int soLuongSanPham, PhuongThucThanhToan phuongThucThanhToan, char tenKH[]);
void inHoa(char name[]) {
    for(int i = 0; i < strlen(name); i++){
        if(i == 0 || (i > 0 && name[i - 1] == ' ')){ 
            if(name[i] >= 'a' && name[i] <= 'z')
                name[i] = name[i] - 32;    
        } else {
            if(name[i] >= 'A' && name[i] <= 'Z'){
                name[i] = name[i] + 32;    
            }    
        }
    }
}


int main() {
    SanPham sanPhams[MAX_ITEMS];
    int soLuongSanPham = 0;
    char nhapThem;
    PhuongThucThanhToan phuongThucThanhToan;
    char tenKH[50];
    printf("Hóa đơn thanh toán\n");
    printf("-----------------------------------\n");
    printf("Nhập tên khách hàng: ");
    scanf(" %[^\n]", tenKH);
    inHoa(tenKH);
    do {
        printf("Nhập tên sản phẩm: ");
        scanf(" %[^\n]", sanPhams[soLuongSanPham].tenSanPham);
        printf("Nhập giá sản phẩm: ");
        scanf("%lf", &sanPhams[soLuongSanPham].gia);
        printf("Nhập số lượng sản phẩm: ");
        scanf("%d", &sanPhams[soLuongSanPham].soLuong);
        soLuongSanPham++;

        printf("Bạn có muốn nhập thêm sản phẩm không? (y/n): ");
        scanf(" %c", &nhapThem);

    } while (nhapThem == 'y' && soLuongSanPham < MAX_ITEMS);

    int luaChonThanhToan;
    do {
        printf("Chọn phương thức thanh toán:\n");
        printf("1. Tiền mặt\n");
        printf("2. Thẻ tín dụng\n");
        printf("3. Chuyển khoản ngân hàng\n");
        printf("4. Ví điện tử\n");
        printf("Lựa chọn của bạn là: ");
        scanf("%d", &luaChonThanhToan);
        switch (luaChonThanhToan) {
            case 1:
                phuongThucThanhToan = TIEN_MAT;
                break;
            case 2:
                phuongThucThanhToan = THE_TIN_DUNG;
                break;
            case 3:
                phuongThucThanhToan = CHUYEN_KHOAN;
                break;
            case 4:
                phuongThucThanhToan = VI_DIEN_TU;    
                break;
            default:
                printf("Phương thức thanh toán không hợp lệ! Vui lòng nhập lại.\n");
        }
    } while (luaChonThanhToan < 1 || luaChonThanhToan > 4);

    inHoaDon(sanPhams, soLuongSanPham, phuongThucThanhToan, tenKH);
    return 0;
}

void inHoaDon(SanPham sanPhams[], int soLuongSanPham, PhuongThucThanhToan phuongThucThanhToan, char tenKH[]) {
    double tongTien = 0;
    for (int i = 0; i < soLuongSanPham; i++) {
        tongTien += sanPhams[i].gia * sanPhams[i].soLuong;
    }

    // Tính thuế VAT và tổng tiền sau thuế
    double thueVAT = tongTien * VAT_RATE;
    double tongTienSauThue = tongTien + thueVAT;

    printf("\nHÓA ĐƠN THANH TOÁN\n");
    printf("Họ và tên khách hàng: %s\n", tenKH);
    
    printf("---------------------------------------------------------------------\n");
    printf("STT | Tên sản phẩm            | Giá          | Số lượng | Thành tiền\n");
    printf("----|-------------------------|--------------|----------|------------\n");
    for (int i = 0; i < soLuongSanPham; i++) {
        double thanhTien = sanPhams[i].gia * sanPhams[i].soLuong;

        // In ra số thứ tự và các cột
        printf("%-3d | %-23s | %-12.0lf | %-8d | %-12.0lf\n", i + 1, sanPhams[i].tenSanPham, sanPhams[i].gia, sanPhams[i].soLuong, thanhTien);
    }

    printf("---------------------------------------------------------------------\n");
    printf("Tổng cộng: %53.0lf đ\n", tongTien);
    printf("Thuế VAT (10%%): %48.0lf đ\n", thueVAT);
    printf("==================================================================\n");
    printf("Tổng tiền sau thuế: %44.0lf đ\n", tongTienSauThue);
    printf("\nPhương thức thanh toán: ");
    double tienKhachDua;
    switch (phuongThucThanhToan) {
        case TIEN_MAT: 
            printf("Tiền mặt\n");
            do{
                printf("Tiền khách đưa: ");
                scanf("%lf", &tienKhachDua);
                if (tienKhachDua >= tongTienSauThue) {
                    double tienThua = tienKhachDua - tongTienSauThue;
                    printf("Tiền trả lại: %.0lf đ\n", tienThua);
                } else {
                    printf("Số tiền không đủ\n");
                }
            }while(tienKhachDua < tongTienSauThue);
            break;
        case THE_TIN_DUNG:
            printf("Thẻ tín dụng\n");
            break;
        case CHUYEN_KHOAN:
            printf("Chuyển khoản ngân hàng\n");
            break;
        case VI_DIEN_TU:
            printf("Ví điện tử\n");
            break;
    }
    printf("=================================================\n");
    printf("Cảm ơn quý khách! Hẹn gặp lại!\n");
    printf("=================================================\n");
    FILE *file = fopen("hoa_don.txt", "r");
    
        double temp = 0;
        fscanf(file, "%lf", &temp);
        tongTienSauThue += temp;
        fclose(file);

    file = fopen("hoa_don.txt", "w");
    
    fprintf(file, "%.0lf\n", tongTienSauThue);
    fclose(file);
}
