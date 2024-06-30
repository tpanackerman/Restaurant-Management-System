#include <iostream>
#include <fstream>
#include <cstring>
#define MAX_ITEMS 100
#define VAT_RATE 0.1

using namespace std;

struct SanPham {
    char tenSanPham[50];
    double gia;
    int soLuong;
};

enum PhuongThucThanhToan {
    TIEN_MAT,
    THE_TIN_DUNG,
    CHUYEN_KHOAN,
    VI_DIEN_TU
};

void inHoaDon(SanPham sanPhams[], int soLuongSanPham, PhuongThucThanhToan phuongThucThanhToan, char tenKH[]);

void inhoa(char name[]) {
        for(int i=0; i<strlen(name); i++){
            if(i==0|| (i>0 && name[i-1]==' ')){ 
                if(name[i]>='a' && name[i]<='z')
                    name[i]=name[i]-32;    
            }else{
                if(name[i]>='A' && name[i]<='Z'){
                    name[i]=name[i]+32;    
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
    cout << "Hoa don thanh toan\n";
    cout << "-----------------------------------\n";
    cout << "Nhap ten khach hang: ";
    cin.getline(tenKH, 50);
    inhoa(tenKH);
    do {
        cout << "Nhap ten san pham: ";
        cin.getline(sanPhams[soLuongSanPham].tenSanPham, 50);
        cout << "Nhap gia san pham: ";
        cin >> sanPhams[soLuongSanPham].gia;
        cout << "Nhap so luong san pham: ";
        cin >> sanPhams[soLuongSanPham].soLuong;
        soLuongSanPham++;

        cout << "Ban co muon nhap them san pham khong? (y/n): ";
        cin >> nhapThem;
        cin.ignore(); 

    } while (nhapThem == 'y' && soLuongSanPham < MAX_ITEMS);

    int luaChonThanhToan;
    do {
        cout << "Chon phuong thuc thanh toan:\n";
        cout << "1. Tien mat\n";
        cout << "2. The tin dung\n";
        cout << "3. Chuyen khoan ngan hang\n";
        cout << "4. Vi dien tu\n";
        cout << "Lua chon cua ban la: ";
        cin >> luaChonThanhToan;
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
                cout << "Phuong thuc thanh toan khong hop le! Vui long nhap lai.\n";
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

    // Tinh thue VAT va tong tien sau thue
    double thueVAT = tongTien * VAT_RATE;
    double tongTienSauThue = tongTien + thueVAT;

    cout << "\nHOA DON THANH TOAN\n";
    cout << "Ho va ten khach hang: " << tenKH << endl;
        
    cout << "---------------------------------------------------------------------\n";
    cout << "STT | Ten san pham            | Gia          | So luong | Thanh tien\n";
    cout << "----|-------------------------|--------------|----------|------------\n";
    for (int i = 0; i < soLuongSanPham; i++) {
        double thanhTien = sanPhams[i].gia * sanPhams[i].soLuong;
        printf("%-3d | %-23s | %-12.0lf | %-8d | %-12.0lf\n", i + 1, sanPhams[i].tenSanPham, sanPhams[i].gia, sanPhams[i].soLuong, thanhTien);
    }

    cout << "---------------------------------------------------------------------\n";
    cout << "Tong cong: " << tongTien << " dong\n";
    cout << "Thue VAT (10%): " << thueVAT << " dong\n";
    cout << "Tong tien sau thue: " << tongTienSauThue << " dong\n";
    cout << "\nPhuong thuc thanh toan: ";
    double tienKhachDua;
    switch (phuongThucThanhToan) {
        case TIEN_MAT: 
            cout << "Tien mat\n";
            do{
                cout << "Tien khach dua: ";
                cin >> tienKhachDua;
                if (tienKhachDua >= tongTienSauThue) {
                    double tienThua = tienKhachDua - tongTienSauThue;
                    cout << "Tien tra lai: " << tienThua << " dong\n";
                } else {
                    cout << "So tien khong du\n";
                }
            }while(tienKhachDua<tongTienSauThue);
            
            break;
        
        case THE_TIN_DUNG:
            cout << "The tin dung\n";
            break;
        case CHUYEN_KHOAN:
            cout << "Chuyen khoan ngan hang\n";
            break;
        case VI_DIEN_TU:
            cout << "Vi dien tu\n";
            break;
    }
    cout << "=================================================\n";
    cout << "Cam on quy khach! Hen gap lai!\n";
    cout << "=================================================\n";
    ifstream inFile("hoa_don.txt");
    
        double temp = 0;
        inFile >> temp;
        tongTienSauThue += temp;
        inFile.close();
    

    ofstream outFile("hoa_don.txt");
    outFile << tongTienSauThue << endl;
    outFile.close();

}
