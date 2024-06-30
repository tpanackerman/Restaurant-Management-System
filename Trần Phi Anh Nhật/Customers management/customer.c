#include <stdio.h>
#include <string.h>

#define MAX_CUSTOMER 100

typedef struct {
    char name[30];
    char address[50];
    char phone[15];
} khachhang;

khachhang customers[MAX_CUSTOMER];
int demkhach = 0;

// In hoa chu cai dau tien
void inhoa(char str[]) {
    int inWord = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != ' ') {
            if (inWord == 0) {
                if (str[i] >= 'a' && str[i] <= 'z') {
                    str[i] = str[i] - 32;
                }
                inWord = 1;
            } else {
                if (str[i] >= 'A' && str[i] <= 'Z') {
                    str[i] = str[i] + 32;
                }
            }
        } else {
            inWord = 0;
        }
    }
}

//Lay chu cai dau trong ten
char chudau(char name[]) {
    inhoa(name);
    for (int i = strlen(name) - 1; i >= 0; i--) {
        if (i == 0 || (i > 0 && name[i-1] == ' ')) {
            return name[i];
        }
    }
    return '\0';
}

//Hien thi thong tin khach hang
void hienThi(const khachhang* kh){
    printf("|%25s|%25s|%15s|\n", kh->name, kh->address, kh->phone);
    printf("|-------------------------|-------------------------|---------------|\n");
}

// Hien thi tat ca khach hang
void sapXepKhachHang() {
    for (int i = 0; i < demkhach - 1; i++) {
        for (int j = i + 1; j < demkhach; j++) {
            if (chudau(customers[i].name)> chudau(customers[j].name)) {
                khachhang temp = customers[i];
                customers[i] = customers[j];
                customers[j] = temp;
            }
        }
    }
}

void hienThiTatCa() {
    sapXepKhachHang();
    printf("\n----------Thong tin khach hang----------\n");
    printf("|-------------------------|-------------------------|---------------|\n");
    printf("|           Ten khach hang|                  Dia chi|  So dien thoai|\n");
    printf("|-------------------------|-------------------------|---------------|\n");
    for (int i = 0; i < demkhach; i++) {
        hienThi(&customers[i]);
    }
}

// Ham them khach hang
void nhapThongTin(khachhang* kh) {
    if (demkhach >= MAX_CUSTOMER) {
        printf("Danh sach khach hang da day!\n");
        return;
    }
    
    printf("Nhap ten: ");
    fgets(customers[demkhach].name, 30, stdin);
    customers[demkhach].name[strcspn(customers[demkhach].name, "\n")] = 0;
    inhoa(customers[demkhach].name);

    printf("\nNhap dia chi: ");
    fgets(customers[demkhach].address, 50, stdin);
    customers[demkhach].address[strcspn(customers[demkhach].address, "\n")] = 0;
    inhoa(customers[demkhach].address);

    printf("\nNhap so dien thoai: ");
    fgets(customers[demkhach].phone, 15, stdin);
    customers[demkhach].phone[strcspn(customers[demkhach].phone, "\n")] = 0;

    demkhach++;
    printf("Khach hang da duoc them thanh cong!\n");
}

// Hien thi menu de lua chon
void menu() {
    printf("\nQuan ly khach hang");
    printf("\n1. Them khach hang");
    printf("\n2. Tim kiem khach hang");
    printf("\n3. Hien thi tat ca khach hang");
    printf("\n4. Cap nhat thong tin khach hang");
    printf("\n5. Xoa khach hang");
    printf("\n6. Thoat chuong trinh");
}

// Tim khach hang
void timKH(khachhang khang[], int n) {
    char ttin[30];
    int found = 0;
    printf("\nNhap ten khach hang: ");
    fgets(ttin, 30, stdin);
    ttin[strcspn(ttin, "\n")] = 0;
    inhoa(ttin);
    printf("-----Thong tin khach hang------\n");

    for (int i = 0; i < n; i++) {
        if (strstr(khang[i].name, ttin) != NULL) {
            found = 1;
            hienThi(&khang[i]);
            printf("|-------------------------|-------------------------|---------------|\n");
        }
    }
    if (!found) {
        printf("\nKhong tim thay thong tin khach hang!\n");
    }
}

// Xoa khach hang
void xoaKH(khachhang khang[], int& n) {
    char ttin[30];
    int found = 0;
    int dlt = 0;
    printf("\nNhap ten khach hang can xoa:   ");
    fgets(ttin, 29, stdin);
    ttin[strcspn(ttin, "\n")] = 0;
    inhoa(ttin);

    for(int i = 0; i<n; i++){
        if(strcmp(khang[i].name, ttin) == 0){
            found = 1;
            dlt = i;
        }
    }
    if(found){
        for(int i = dlt; i<n-1; i++){
            khang[i] = khang[i+1];
        }
        n--;
        printf("\nKhach hang da duoc xoa thanh cong!");
    }
    else{
        printf("\nKhong tim thay khach hang can xoa!");
    }
}

// Cap nhat thong tin khach hang
void capNhat(khachhang khang[], int n) {
    char ttin[30];
    int found = 0;
    printf("\nNhap ten khach hang: ");
    fgets(ttin, 30, stdin);
    ttin[strcspn(ttin, "\n")] = 0;
    inhoa(ttin);

    for (int i = 0; i < n; i++) {
        char ten[30];
        strcpy(ten, khang[i].name);
        inhoa(ten);
        if (strstr(ten, ttin) != NULL) {
            found = 1;
            printf("\nNhap thong tin cap nhat cho khach hang: \n");
            printf("Nhap ten: ");
            fgets(khang[i].name, 30, stdin);
            khang[i].name[strcspn(khang[i].name, "\n")] = 0;
            inhoa(khang[i].name);

            printf("Nhap dia chi: ");
            fgets(khang[i].address, 50, stdin);
            khang[i].address[strcspn(khang[i].address, "\n")] = 0;
            inhoa(khang[i].address);

            printf("Nhap so dien thoai: ");
            fgets(khang[i].phone, 15, stdin);
            khang[i].phone[strcspn(khang[i].phone, "\n")] = 0;
            break;
        }
    }
    if (found) {
        printf("\nThong tin khach hang da duoc cap nhat!\n");
    } else {
        printf("\nKhong tim thay khach hang!\n");
    }
}

int main() {
    int luachon;
    do {
        menu();
        printf("\nNhap so de tiep tuc: ");
        scanf("%d", &luachon);
        getchar(); // Loại bỏ ký tự '\n' trong buffer

        switch (luachon) {
            case 1:
                nhapThongTin(customers);
                break;
            case 2:
                timKH(customers, demkhach);
                break;
            case 3:
                hienThiTatCa();
                break;
            case 4:
                capNhat(customers, demkhach);
                break;
            case 5:
                xoaKH(customers, demkhach);
                break;
            case 6:
                printf("Thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le, vui long chon lai!\n");
                break;
        }
    } while (luachon != 6);

    return 0;
}

