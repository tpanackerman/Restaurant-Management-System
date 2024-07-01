#include<iostream>
#include <cstring>
#include <string>

#define MAX_CUSTOMERS 100

using namespace std;

struct NhanVien{
    char id[10];
    char name[100];
    char gender[10];
    int age;
    char phonenumber[11];
    char position[100];
};


class khachhang {
public:
    string name;
    string address;
    string phone;
};

khachhang customers[MAX_CUSTOMERS];
int demkhach = 0;

// In hoa chu cai dau tien
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
    if (demkhach >= MAX_CUSTOMERS) {
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

// Hien thi menu de lua chon
void menuKH() {
    cout << "\nQuan ly khach hang";
    cout << "\n1. Them khach hang";
    cout << "\n2. Tim kiem khach hang";
    cout << "\n3. Hien thi tat ca khach hang";
    cout << "\n4. Cap nhat thong tin khach hang";
    cout << "\n5. Xoa khach hang";
    cout << "\n6. Thoat chuong trinh";
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

class quanlynhanvien{    
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
            if (i == 0 || (i > 0 && name[i - 1]==' ')) {
                return name[i];
            }
        }
        return '\0';
    }

    // Hien thi thong tin cua nhan vien
    void hienThi(const NhanVien& nv) {
        printf("| ID: %5s | Name: %20s | Gender: %5s | Age: %3d | Phone Number: %11s | Position: %15s |", 
        nv.id, nv.name, nv.gender, nv.age, nv.phonenumber, nv.position);
        printf("\n|-----------|----------------------------|---------------|----------|---------------------------|---------------------------|\n");
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

void pronumber(){
	cout<<"\n*********PHAN MEM QUAN LY NHAN SU VA KHACH HANG*********";
	cout<<"\n1. Nhan vien";
	cout<<"\n2. Khach hang";
	cout<<"\n3. Thoat chuong trinh\n";
}
int main(){
	quanlynhanvien qlnv; 
    int luachon;
    int chon;
    do {
    	pronumber();
        cout<<"Nhap lua chon cua ban\n";
        cin>>chon;
        cin.ignore();
        switch(chon) {
            case 1: {
                int n = 0;
                NhanVien nvien[100];
                cout << "\nNhap so luong nhan vien: ";
                cin >> n;
                cin.ignore();
                qlnv.nhapDS(nvien, n);
                do {
                	qlnv.menu();
                    cout<<"\nLua chon trong menu nhan vien cua ban la\n";
                    cin>>luachon;
                    cin.ignore();
                    switch (luachon) {
                        case 1:
                            qlnv.hienThiDS(nvien, n);
                            break;
                        case 2: {
                            int t;
                            cout<<"\nNhap so luong nhan vien tang them: ";
                            cin>>t;
                            qlnv.themNV(nvien, n, t);
                            break;
                        }
                        case 3:
                            qlnv.timNV(nvien, n);
                            break;
                        case 4:
                            qlnv.xoaNV(nvien, n);
                            break;
                        case 5:
                            qlnv.capNhat(nvien, n);
                            break;
                        case 0:
                            cout<<"Thoat chuong trinh\n";
                            break;
                        default:
                            cout<<"Lua chon khong hop le, vui long chon lai!\n";
                            break;
                    }
                } while (luachon != 0);
                break;
            }
            case 2:
            	int luachon;
                do {
                    menuKH();
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
                break;
            case 3:
                cout<<"\nBan da thoat khoi chuong trinh";
                return 0;
            default:
                cout<<"Lua chon khong hop le, vui long chon lai!\n";
                break;
        }
    } while (chon != 0);

    return 0; 
}


