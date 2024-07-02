#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#define MAX_ITEMS 100
#define VAT_RATE 0.1
#define MAX_MENU_ITEMS 50
#define MAX_CUSTOMER 100

using namespace std;
struct NhanVien{
    char id[10];
    char name[100];
    char gender[10];
    int age;
    char phonenumber[11];
    char position[100];
};
enum PhuongThucThanhToan {
    TIEN_MAT,
    THE_TIN_DUNG,
    CHUYEN_KHOAN,
    VI_DIEN_TU
};

typedef struct {
    char tenSanPham[50];
    int gia;
    int soLuong;
} SanPham;

//ĐẶT BÀN
const int sobanmax = 100;
struct Ban { 
    int soban;
    char tenkhach[100];
};
// In hoa chữ cái đầu tiên
    void inhoa(char name[]) {
        for(int i = 0; i < strlen(name); i++) {
            if(i == 0 || (i > 0 && name[i - 1] == ' ')) { 
                if(name[i] >= 'a' && name[i] <= 'z')
                    name[i] = name[i] - 32;    
            } else {
                if(name[i] >= 'A' && name[i] <= 'Z') {
                    name[i] = name[i] + 32;    
                }    
            }
        }
    }
class Quanlydatban {
public:
    Ban bans[sobanmax];
    int soluongban = 0;
    
    // hiển thị bàn đã được đặt bởi khách
    void hienthi(Ban ban) {
        cout << "Ban so " << ban.soban << " da duoc dat boi " << ban.tenkhach << endl;
        cout << "---------------------------------------------------------" << endl;
    }

    // nhập thông tin khách đặt bàn
    void nhap() {
        cout << "Nhap ten khach hang: ";
        cin.getline(bans[soluongban].tenkhach, 100);
        inhoa(bans[soluongban].tenkhach);
        cout << "Nhap so ban: ";
        cin >> bans[soluongban].soban;
        cin.ignore();
        soluongban++;
    }

    // đặt bàn
    void datban() {
        if (soluongban >= sobanmax) {
            cout << "Da het ban" << endl;
            return;
        }

        int sobandat;
        int ktra;
        do {
            ktra = 1;
            cout << "So ban muon dat: ";
            cin >> sobandat;
            cin.ignore();
            if (sobandat <= 0 || sobandat > sobanmax) {
                cout << "Vui long nhap so tu 1 den " << sobanmax << endl;
            }

            for (int i = 0; i < soluongban; i++) {
                if (bans[i].soban == sobandat) {
                    cout << "Ban da co nguoi dat, vui long chon ban khac" << endl;
                    ktra = 0;
                }
            }
        } while(sobandat <= 0 || sobandat > sobanmax || ktra == 0);
        

        Ban newBan;
        newBan.soban = sobandat;
        cout << "Nhap ten khach hang: ";
        cin.getline(newBan.tenkhach, 100);
        inhoa(newBan.tenkhach);
        bans[soluongban++] = newBan;

        cout << "Dat ban thanh cong" << endl;
    }

    // hủy bàn
    void huyban() {
        int soban;
        cout << "So ban muon huy: ";
        cin >> soban;
        cin.ignore();

        if (soban <= 0 || soban > sobanmax) {
            cout << "So ban khong hop le" << endl;
            return;
        }

        for (int i = 0; i < soluongban; i++) {
            if (bans[i].soban == soban) {
                for (int j = i; j < soluongban - 1; j++) {
                    bans[j] = bans[j + 1];
                }
                soluongban--;
                cout << "Huy ban thanh cong" << endl;
                return;
            }
        }

        cout << "Khong tim thay ban can huy" << endl;
    }

    // tìm kiếm bàn
    void timkiem() {
        char ten[100];
        cout << "Nhap ten khach hang: ";
        cin.getline(ten, 100);
        inhoa(ten);
        int kt = 0;

        for (int i = 0; i < soluongban; i++) {
            if (strstr(bans[i].tenkhach, ten) != NULL) {
            	kt=1;
                hienthi(bans[i]);
            }
        }
        if(kt==0) cout<<"\nKhong tim thay khach hang\n";
    }

    // danh sách bàn được đặt
    void danhsachban() {
        for(int i = 0; i < soluongban - 1; i++) {
            for(int j = i + 1; j < soluongban; j++) {
                if(bans[i].soban > bans[j].soban) {
                    Ban temp = bans[i];
                    bans[i] = bans[j];
                    bans[j] = temp;
                }
            }
        }
        cout << "DANH SACH BAN DA DUOC DAT BOI KHACH HANG" << endl;
        for (int i = 0; i < soluongban; i++) {
            hienthi(bans[i]);
        }
    }

    // số lượng bàn còn lại
    void sobanconlai() {
        cout << "So luong ban con lai cua nha hang: " << (sobanmax - soluongban) << endl;
    }

    // chọn chức năng
    void tableBooking() {
        int choice;
        Quanlydatban qldb;
        do {
            cout << "\nQUAN LY BAN CUA NHA HANG\n";
            cout << "1. Dat ban\n";
            cout << "2. Huy ban\n";
            cout << "3. Tim kiem ban\n";
            cout << "4. Danh sach ban va khach hang\n";
            cout << "5. So luong ban con lai\n";
            cout << "6. Thoat\n";
            cout << "Vui long chon muc tu 1->6: ";
            cin >> choice;
            cin.ignore();
            switch (choice) {
                case 1:
                    qldb.datban();
                    break;
                case 2:
                    qldb.huyban();
                    break;
                case 3:
                    qldb.timkiem();
                    break;
                case 4:
                    qldb.danhsachban();
                    break;
                case 5:
                    qldb.sobanconlai();
                    break;
                case 6:
                    cout << "Thoat khoi chuc nang" << endl;
                    break;
                default:
                    cout << "Khong hop le, vui long nhap lai" << endl;
            }
        } while (choice != 6);
    }
};

//MENU
class MenuItem {
public:
    string dish_name;
    float price;
};

vector<MenuItem> menu;

void clearBuffer() {
    cin.ignore(); 
}

void addDish() {
    if (menu.size() >= MAX_MENU_ITEMS) {
        cout << "Thuc đon đa đay!\n";
        return;
    }

    MenuItem m;
    clearBuffer();
    cout << "Nhap ten mon: ";
    getline(cin, m.dish_name);
    cout << "Nhap gia mon: ";
    cin >> m.price;

    menu.push_back(m);
    cout << "Mon an đa đuoc them vao thuc đon!\n";
}

void displayDish() {
    string dish_name;
    cout << "Nhập ten mon: ";
    clearBuffer();
    getline(cin, dish_name);

    for (const auto& item : menu) {
        if (item.dish_name == dish_name) {
            cout << "\nThong tin mon an:\n";
            cout << "Ten mon: " << item.dish_name << "\n";
            cout << "Gia thanh: " << item.price << "\n";
            return;
        }
    }
    cout << "Khong tim thay mon an!\n";
}

void displayAllDishes() {
    cout << "\nThuc đon:\n";
    cout << "-----------------------------------------------------\n";
    cout << "Ten mon             | Gia thanh \n";
    cout << "--------------------|--------------------------------\n";
    for (const auto& item : menu) {
        cout << item.dish_name << " | " << item.price << "\n";
    }
}

void editDish() {
    string dish_name;
    cout << "Nhap ten mon can cap nhat: ";
    clearBuffer();
    getline(cin, dish_name);

    for (auto& item : menu) {
        if (item.dish_name == dish_name) {
            cout << "Cap nhat ten mon an: ";
            getline(cin, item.dish_name);
            cout << "Cap nhat muc gia moi: ";
            cin >> item.price;

            cout << "Cap nhat thong tin thanh cong!\n";
            return;
        }
    }
    cout << "Khong tim thay mon an!\n";
}

void deleteDish() {
    string dish_name;
    cout << "Nhap ten mon an can xoa: ";
    clearBuffer();
    getline(cin, dish_name);

    for (auto it = menu.begin(); it != menu.end(); ++it) {
        if (it->dish_name == dish_name) {
            menu.erase(it);
            cout << "Da xoa mon an khoi thuc don!\n";
            return;
        }
    }
    cout << "Khong tim thay mon an!\n";
}

void menuManagement() {
    int choice;
    do {
        cout << "\nQuan ly thuc don";
        cout << "\n1. Them mon an";
        cout << "\n2. Tim kiem mon an";
        cout << "\n3. Hien thi tat ca mon an";
        cout << "\n4. Cap nhat thong tin mon an";
        cout << "\n5. Xoa mon an khoi thuc don";
        cout << "\n6. Thoat chuong trinh";
        cout << "\nNhap so de tiep tuc: ";
        cin >> choice;
        switch (choice) {
            case 1: 
                addDish(); 
                break;
            case 2: 
                displayDish(); 
                break;
            case 3: 
                displayAllDishes(); 
                break;
            case 4: 
                editDish(); 
                break;
            case 5: 
                deleteDish(); 
                break;
            case 6: 
                break;
            default: 
                cout << "Lua chon khong hop le, vui long chon lai!\n";        }
    } while (choice != 6);
}

//HOÁ ĐƠN
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
    double temp = 0;
    ifstream fileIn("hoa_don.txt");
    if (fileIn) {
        fileIn >> temp;
        fileIn.close();
    }
    tongTienSauThue += temp;
    
    ofstream fileOut("hoa_don.txt");
    fileOut << tongTienSauThue;
    fileOut.close();
}

void hienThiDoanhThu() {
    ifstream file("hoa_don.txt");
    double tong = 0.0;
    file >> tong;
    cout << "\nDoanh thu la: " << tong << endl;
    file.close();
}

// NHÂN VIÊN
class quanly{    
public:
    // In hoa chu cai dau tien
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

    // Lay chu cai dau tien trong ten
    char chudau(char name[]) {
        inhoa(name);
        for (int i = strlen(name) - 1; i >= 0; i--) {
            if (i == 0 || (i > 0 && isspace(name[i - 1]))) {
                return name[i];
            }
        }
        return '\0';
    }

    // Hien thi thong tin cua nhan vien
    void hienThi(const NhanVien& nv) {
        printf("| ID: %5s | Name: %20s | Gender: %5s | Age: %3d | Phone Number: %11s | Position: %15s |", 
        nv.id, nv.name, nv.gender, nv.age, nv.phonenumber, nv.position);
        printf ("\n|-----------|----------------------------|---------------|----------|---------------------------|---------------------------|\n");
    }

    // Nhap thong tin cua nhan vien
    void nhapThongTin(NhanVien& nv) {
        cout << "\nNhap ID: ";
        cin >> nv.id;
        cin.ignore();
        cout << "Nhap ten nhan vien: ";
        cin.getline(nv.name, 100);
        cout << "Nhap gioi tinh: ";
        cin >> nv.gender;
        cout << "Nhap tuoi: ";
        cin >> nv.age;
        cin.ignore();
        cout << "Nhap so dien thoai: ";
        cin >> nv.phonenumber;
        cin.ignore();
        cout << "Nhap chuc vu: ";
        cin.getline(nv.position, 100);
        inhoa(nv.name);
        inhoa(nv.gender);
        inhoa(nv.position);
    }

    // Nhap danh sach nhan vien
    void nhapDS(NhanVien nvien[], int& n) {
        for (int i = 0; i < n; i++) {
            bool ktraID;
            do {
                ktraID = true;
                cout << "\nNhap thong tin nhan vien thu " << i + 1 << ": ";
                nhapThongTin(nvien[i]);
                for (int j = 0; j < i; j++) {
                    if (strcmp(nvien[j].id, nvien[i].id) == 0) {
                        cout << "\nID da ton tai, vui long nhap lai: ";
                        ktraID = false;
                        break;
                    }
                }
            } while (!ktraID);
        }
    }

    // Sap xep nhan vien
    void sapxep(NhanVien nvien[], int n) {
        for (int i = 0; i < n - 1; i++) {
            for(int j = i+1; j<n; j++){
                if (chudau(nvien[i].name) > chudau(nvien[j].name)) {
                    NhanVien temp = nvien[i];
                    nvien[i] = nvien[j];
                    nvien[j] = temp;
                }
            }
        }
    }

    // Hien thi menu de lua chon
    void menu() {
        cout << "\n\n\n========= Menu Quan Ly Nhan Vien ==========";
        cout << "\n| 1 | Hien thi danh sach nhan vien";
        cout << "\n| 2 | Them nhan vien";
        cout << "\n| 3 | Tim kiem nhan vien";
        cout << "\n| 4 | Xoa nhan vien";
        cout << "\n| 5 | Cap nhat thong tin nhan vien";
        cout << "\n| 0 | Thoat";
    }

    // Hien thi danh sach nhan vien
    void hienThiDS(NhanVien nvien[], int n) {
        cout << "\n------------- Danh Sach Nhan Vien ------------\n";
        cout << "\n|-----------|----------------------------|---------------|----------|---------------------------|---------------------------|\n";
        sapxep(nvien, n);
        for (int i = 0; i < n; i++) {
            hienThi(nvien[i]);
        }
    }

    // Them nhan vien
    void themNV(NhanVien nvien[], int& n, int t) {
        for (int i = n; i < n + t; i++) {
            bool ktraID;
            do {
                ktraID = true;
                cout << "\nNhap thong tin nhan vien thu " << i + 1 << ": ";
                nhapThongTin(nvien[i]);
                for (int j = 0; j < i; j++) {
                    if (strcmp(nvien[j].id, nvien[i].id) == 0) {
                        cout << "\nID da ton tai, vui long nhap lai: ";
                        ktraID = false;
                        break;
                    }
                }
            } while (!ktraID);
        }
        n += t;
    }

    // Tim kiem nhan vien
    void timNV(NhanVien nvien[], int n) {
        char ttin[100];
        bool found = false;
        cout << "\nNhap ten cua nhan vien muon tim kiem: ";
        cin.getline(ttin, 100);
        inhoa(ttin);
        
        for (int i = 0; i < n; i++) {
            if (strstr(nvien[i].name, ttin) != NULL) {
                found = true;
                hienThi(nvien[i]);
            }
        }
        if (!found) {
            cout << "\nKhong tim thay nhan vien can tim! ";
        }
    }

    // Xoa nhan vien
    void xoaNV(NhanVien nvien[], int& n) {
        char ttin[100];
        bool found = false;
        int dlt = 0;

        cout << "\nNhap ten cua nhan vien muon xoa: ";
        cin.getline(ttin, 100);

        for (int i = 0; i < n; i++) {
            inhoa(ttin);

            if (strstr(nvien[i].name, ttin) != NULL) {
                found = true;
                dlt = i;
                break;
            }
        }

        if (found) {
            for (int i = dlt; i < n - 1; i++) {
                nvien[i] = nvien[i + 1];
            }
            n--;
            cout << "\nNhan vien da duoc xoa thanh cong! \n";
        } else {
            cout << "\nKhong tim thay nhan vien can tim! \n";
        }
    }

    // Cap nhat thong tin cho nhan vien
    void capNhat(NhanVien nvien[], int n) {
        char ttin[100];
        bool found = false;
        cout << "\nNhap ten cua nhan vien muon cap nhat: ";
        cin.getline(ttin, 100);

        for (int i = 0; i < n; i++) {
            inhoa(ttin);

            if (strstr(nvien[i].name, ttin) != NULL) {
                found = true;
                cout << "\nNhap thong tin cap nhat cho nhan vien: \n";
                nhapThongTin(nvien[i]);
                break;
            }
        }
        if (found) {
            cout << "\nNhan vien da duoc cap nhat!";
        } else {
            cout << "\nKhong tim thay nhan vien can tim!";
        }
    }

};


void nhanVien(){
        quanly ql;
        int luachon;
        int n = 0;
        NhanVien nvien[100];
        cout << "\nNhap so luong nhan vien: ";
        cin >> n;
        cin.ignore();
        ql.nhapDS(nvien, n);
        do{
            cout << "\n\n\n========= Menu Quan Ly Nhan Vien ==========";
            cout << "\n| 1 | Hien thi danh sach nhan vien";
            cout << "\n| 2 | Them nhan vien";
            cout << "\n| 3 | Tim kiem nhan vien";
            cout << "\n| 4 | Xoa nhan vien";
            cout << "\n| 5 | Cap nhat thong tin nhan vien";
            cout << "\n| 0 | Thoat";
            cout << "\nNhap lua chon cua ban: ";
            cin >> luachon;
            cin.ignore();
        
        
        switch (luachon) {
            case 1:
                ql.hienThiDS(nvien, n);
                break;
            case 2: {
                int t;
                cout << "\nNhap so luong nhan vien tang them: ";
                cin >> t;
                cin.ignore();
                ql.themNV(nvien, n, t);
                break;
            }
            case 3:
                ql.timNV(nvien, n);
                break;
            case 4:
                ql.xoaNV(nvien, n);
                break;
            case 5:
                ql.capNhat(nvien, n);
                break;
            case 0:
                cout << "Thoat chuong trinh\n";
                break;
            default:
                cout << "Lua chon khong hop le, vui long chon lai!\n";
                break;
        }
    } while (luachon != 0);
}

//KHÁCH HÀNG
class khachhang {
public:
    string name;
    string address;
    string phone;
};

khachhang customers[MAX_CUSTOMER];
int demkhach = 0;
void inhoa(string &str) {
    int len = str.length();
    bool inWord = false;
    for (int i = 0; i < len; i++) {
        if (str[i] != ' ') {
            if (!inWord) {
                if (str[i] >= 'a' && str[i] <= 'z') {
                    str[i] = str[i] - 'a' + 'A';
                }
                inWord = true;
            } else {
                if (str[i] >= 'A' && str[i] <= 'Z') {
                    str[i] = str[i] - 'A' + 'a';
                }
            }
        } else {
            inWord = false;
        }
    }
}


// Hien thi tat ca khach hang
void sapXepKhachHang() {
    for (int i = 0; i < demkhach - 1; i++) {
        for (int j = i + 1; j < demkhach; j++) {
            if (customers[i].name.compare(customers[j].name) > 0) {
                swap(customers[i], customers[j]);
            }
        }
    }
}

void hienThiTatCa() {
    sapXepKhachHang();
    printf("\nThong tin khach hang:\n");
    printf("---------------------------------------------------------------------------------------\n");
    printf("Ten khach hang           | Dia chi                 | So dien thoai                     \n");
    printf("-------------------------|-------------------------|-----------------------------------\n");
    for (int i = 0; i < demkhach; i++) {
        printf("%-25s|%-25s|%-35s\n", customers[i].name.c_str(), customers[i].address.c_str(), customers[i].phone.c_str());
    }
}

// Ham them khach hang
void nhapThongTin() {
    if (demkhach >= MAX_CUSTOMER) {
        cout << "Danh sach khach hang da day!\n";
        return;
    }
    
    khachhang kh;
    cout << "Nhap ten: ";
    getline(cin, kh.name);
    inhoa(kh.name);
    
    cout << "Nhap dia chi: ";
    getline(cin, kh.address);
    inhoa(kh.address);

    cout << "Nhap so dien thoai: ";
    getline(cin, kh.phone);

    customers[demkhach++] = kh;
    cout << "Khach hang da duoc them thanh cong!\n";
}

// Tim khach hang
void timKH() {
    string ttin;
    bool found = false;
    cout << "\nNhap ten khach hang: ";
    getline(cin, ttin);
    inhoa(ttin);

    for (int i = 0; i < demkhach; i++) {
        string ten = customers[i].name;
        inhoa(ten);
        if (ten.find(ttin) != string::npos) {
            found = true;
            cout << "Thong tin khach hang:\n";
            printf("Ten: %s, Dia chi: %s, So dien thoai: %s\n", customers[i].name.c_str(), customers[i].address.c_str(), customers[i].phone.c_str());
        }
    }
    if (!found) {
        cout << "\nKhong tim thay thong tin khach hang!\n";
    }
}

// Xoa khach hang
void xoaKH() {
    string ttin;
    bool found = false;
    int dlt = 0;

    cout << "\nNhap ten khach hang can xoa: ";
    getline(cin, ttin);
    inhoa(ttin);

    for (int i = 0; i < demkhach; i++) {
        string ten = customers[i].name;
        inhoa(ten);
        if (ten.find(ttin) != string::npos) {
            found = true;
            dlt = i;
            break;
        }
    }

    if (found) {
        for (int i = dlt; i < demkhach - 1; i++) {
            customers[i] = customers[i + 1];
        }
        demkhach--;
        cout << "\nKhach hang da duoc xoa thanh cong!\n";
    } else {
        cout << "\nKhong tim thay khach hang!\n";
    }
}

// Cap nhat thong tin khach hang
void capNhat() {
    string ttin;
    bool found = false;
    cout << "\nNhap ten khach hang: ";
    getline(cin, ttin);
    inhoa(ttin);

    for (int i = 0; i < demkhach; i++) {
        string ten = customers[i].name;
        inhoa(ten);
        if (ten.find(ttin) != string::npos) {
            found = true;
            cout << "\nNhap thong tin cap nhat cho khach hang: \n";
            cout << "Nhap ten: ";
            getline(cin, customers[i].name);
            inhoa(customers[i].name);

            cout << "Nhap dia chi: ";
            getline(cin, customers[i].address);
            inhoa(customers[i].address);

            cout << "Nhap so dien thoai: ";
            getline(cin, customers[i].phone);
            break;
        }
    }
    if (found) {
        cout << "\nThong tin khach hang da duoc cap nhat!\n";
    } else {
        cout << "\nKhong tim thay khach hang!\n";
    }
}

void khachHang(){
    int luachon;
    do {
        cout << "\nQuan ly khach hang";
        cout << "\n1. Them khach hang";
        cout << "\n2. Tim kiem khach hang";
        cout << "\n3. Hien thi tat ca khach hang";
        cout << "\n4. Cap nhat thong tin khach hang";
        cout << "\n5. Xoa khach hang";
        cout << "\n6. Thoat chuong trinh";
        cout << "\nNhap so de tiep tuc: ";
        cin >> luachon;
        cin.ignore();

        switch (luachon) {
            case 1:
                nhapThongTin();
                break;
            case 2:
                timKH();
                break;
            case 3:
                hienThiTatCa();
                break;
            case 4:
                capNhat();
                break;
            case 5:
                xoaKH();
                break;
            case 6:
                cout << "Thoat chuong trinh\n";
                break;
            default:
                cout << "Lua chon khong hop le, vui long chon lai!\n";
                break;
        }
    } while (luachon != 6);
}

int main() {
    int choice;
    SanPham sanPhams[MAX_ITEMS];
    int soLuongSanPham = 0;
    char nhapThem;
    PhuongThucThanhToan phuongThucThanhToan;
    char tenKH[50];
    int n = 0;
    Quanlydatban qldb;
    do {
        cout << "\n==========CHUONG TRINH QUAN LY NHA HANG==========\n";
        cout << "1. Quan ly dat ban\n";
        cout << "2. Quan ly thuc don\n";
        cout << "3. Hoa don thanh toan\n";
        cout << "4. Hien thi doanh thu\n";
        cout << "5. Quan li nhan vien\n";
        cout << "6. Quan li khach hang\n";
        cout << "7. Thoat\n";
        cout << "Vui lòng chọn mục từ 1->6: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                qldb.tableBooking();
                break;
            case 2:
                menuManagement();
                break;
            case 3:
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
                break;   
            case 4:
                hienThiDoanhThu();
                break;
            case 5:
                nhanVien();
                break;
            case 6:
                khachHang();
                break;
            case 7:
                cout << "Thoát khỏi chương trình" << endl;
                break;
            default:
                cout << "Không hợp lệ, vui lòng nhập lại" << endl;
        }
    } while (choice != 7);

    return 0;
}