#include <iostream>
#include <cstring>
#include <string>

#define MAX_CUSTOMER 100

using namespace std;

class khachhang {
public:
    string name;
    string address;
    string phone;
};

khachhang customers[MAX_CUSTOMER];
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

// Hien thi menu de lua chon
void menu() {
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

int main() {
    int luachon;
    do {
        menu();
        cout << "\nNhap so de tiep tuc: ";
        cin >> luachon;
        cin.ignore(); // Loại bỏ ký tự '\n' trong buffer

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

    return 0;
}
