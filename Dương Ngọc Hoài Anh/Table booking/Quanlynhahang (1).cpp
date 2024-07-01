#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SOBANMAX 100
#define MAX_ITEMS 100
#define VAT_RATE 0.1
#define MAX_MENU_ITEMS 50
#define MAX_CUSTOMER 100

typedef struct {
    int soban;
    char tenkhach[100];
} Ban;

typedef struct {
    Ban ban[SOBANMAX];
    int soluongban;
} Quanlydatban;

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

typedef struct {
    char dish_name[30];
    float price;
} MenuItem;

typedef struct {
    char name[30];
    char address[50];
    char phone[15];
} khachhang;

typedef struct{
    char id[10];
    char name[100];
    char gender[10];
    int age;
    char phonenumber[11];
    char position[100];
} nhanvien;

MenuItem ThucDon[MAX_MENU_ITEMS];
int menu_count = 0;

khachhang customers[MAX_CUSTOMER];
int demkhach = 0;

//Ham in hoa chu cai dau tien trong ten
void inhoa(char name[]) {
        for(int i=0; i < strlen(name); i++){
            if(i == 0 || ( i > 0 && name[i - 1] == ' ')){ 
                if(name[i] >= 'a' && name[i] <= 'z')
                    name[i] = name[i] - 32;    
            }else{
                if(name[i] >= 'A' && name[i] <= 'Z'){
                    name[i] = name[i] + 32;    
                }    
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

//
//Chuong trinh quan ly dat ban
//

//Ham hien thi ban da duoc dat
void hienthi(Ban ban) {
    printf("-----------------------------------------------------\n");
    printf("Ban so %d da duoc dat boi %s\n", ban.soban, ban.tenkhach);
}

//Ham thuc hien dat ban
void datban(Quanlydatban *qldb) {
    if (qldb->soluongban >= SOBANMAX) {
        printf("Da het ban\n");
        return;
    }
    int sobandat;
    int db;
    do{
        db = 1;
        printf("So ban muon dat: ");
        scanf("%d", &sobandat);
        getchar(); 
        if (sobandat <= 0 || sobandat > SOBANMAX) {
            printf("Vui long nhap so ban tu 1 den %d\n", SOBANMAX);
        }
        
        for (int i = 0; i < qldb->soluongban; i++) {
            if (qldb->ban[i].soban == sobandat) {
                printf("Ban da co nguoi dat, vui long chon ban khac\n");
                db = 0;
            }
        }
    }while(sobandat <= 0 || sobandat > SOBANMAX || db == 0);
    
    Ban newBan;
    newBan.soban = sobandat;
    printf("Nhap ten khach hang: ");
    fgets(newBan.tenkhach, 100, stdin);
    newBan.tenkhach[strcspn(newBan.tenkhach, "\n")] = 0; 
    inhoa(newBan.tenkhach);

    qldb->ban[qldb->soluongban++] = newBan;
    printf("Dat ban thanh cong\n");
    
}

//Ham huy ban
void huyban(Quanlydatban *qldb) {
    int soban;
    printf("So ban muon huy: ");
    scanf("%d", &soban);
    getchar();

    if (soban <= 0 || soban > SOBANMAX) {
        printf("So ban khong hop le\n");
        return;
    }

    for (int i = 0; i < qldb->soluongban; i++) {
        if (qldb->ban[i].soban == soban) {
            for (int j = i; j < qldb->soluongban - 1; j++) {
                qldb->ban[j] = qldb->ban[j + 1];
            }
            qldb->soluongban--;
            printf("Huy ban thanh cong\n");
            return;
        }
    }

    printf("Khong tim thay ban can huy\n");
}

//Ham tim kiem ban da dat
void timkiem(Quanlydatban *qldb) {
    char ten[100];
    printf("\nNhap ten khach hang: ");
    getchar(); 
    fgets(ten, 100, stdin);
    ten[strcspn(ten, "\n")] = 0; 
    inhoa(ten);

    for (int i = 0; i < qldb->soluongban; i++) {
        if (strstr(qldb->ban[i].tenkhach, ten) != NULL) {
            hienthi(qldb->ban[i]);
            return;
        }
    }

    printf("\nKhong tim thay ban quy khach da dat!\n");
}

//Ham hien thi danh sach dat ban theo thu tu tang dan cua so ban
void danhsachban(Quanlydatban *qldb) {
    for(int i = 0; i<qldb->soluongban-1; i++){
        for(int j = i+1; j<qldb->soluongban; j++){
            if(qldb->ban[i].soban > qldb->ban[j].soban){
                Ban temp = qldb->ban[i];
                qldb->ban[i] = qldb->ban[j];
                qldb->ban[j] = temp;
            }
        }
    }
    printf("DANH SACH BAN DA DUOC DAT BOI KHACH HANG\n");
    for (int i = 0; i < qldb->soluongban; i++) {
        hienthi(qldb->ban[i]);
    }
}

//Ham hien thi so ban con lai
void sobanconlai(Quanlydatban *qldb) {
    printf("So luong ban con lai cua nha hang: %d\n", SOBANMAX - qldb->soluongban);
}

//Ham hien thi menu cua dat ban
void menuDB() {
    printf("\nQUAN LY BAN CUA NHA HANG\n");
    printf("1. Dat ban\n");
    printf("2. Huy ban\n");
    printf("3. Tim kiem ban\n");
    printf("4. Danh sach ban va khach hang\n");
    printf("5. So luong ban con lai\n");
    printf("6. Thoat\n");
    printf("Vui long chon muc tu 1->6: ");
}

//
// Chuong trinh in hoa don
//

// Ham in hoa don
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

//
// Chuong trinh quan ly thuc don
//

// Ham xoa cac ky tu thua trong bo nho dem
void clearBuffer() {
    while (getchar() != '\n');
}

// Ham them mon an vao trong thuc don
void addDish() {
    if (menu_count >= MAX_MENU_ITEMS) {
        printf("Thuc don da day!\n");
        return;
    }

    MenuItem m;
    clearBuffer();
    printf("Nhap ten mon: ");
    fgets(m.dish_name, sizeof(m.dish_name), stdin);
    m.dish_name[strcspn(m.dish_name, "\n")] = '\0';
    printf("Nhap gia mon: ");
    scanf("%f", &m.price);

    ThucDon[menu_count++] = m;
    printf("Mon an da duoc them vao thuc don!\n");
}

// Ham tim kiem mon an
void displayDish() {
    char dish_name[30];
    printf("Nhap ten mon: ");
    clearBuffer();
    fgets(dish_name, sizeof(dish_name), stdin);
    dish_name[strcspn(dish_name, "\n")] = '\0';

    for (int i = 0; i < menu_count; i++) {
        if (strcmp(ThucDon[i].dish_name, dish_name) == 0) {
            printf("\nThong tin mon an:\n");
            printf("Ten mon: %s\n", ThucDon[i].dish_name);
            printf("Gia thanh: %.0f\n", ThucDon[i].price);
            return;
        }
    }
    printf("Khong tim thay mon an!\n");
}

// Ham hien thi danh sach mon an
void displayAllDishes() {
    printf("\nThuc don:\n");
    printf("-----------------------------------------------------\n");
    printf("Ten mon             | Gia thanh \n");
    printf("--------------------|--------------------------------\n");
    for (int i = 0; i < menu_count; i++) {
        printf("%-20s|%-10.0f\n", ThucDon[i].dish_name, ThucDon[i].price);
    }
}

// Ham chinh sua thong tin mon an
void editDish() {
    char dish_name[30];
    printf("Nhap ten mon can cap nhat: ");
    clearBuffer();
    fgets(dish_name, sizeof(dish_name), stdin);
    dish_name[strcspn(dish_name, "\n")] = '\0';

    for (int i = 0; i < menu_count; i++) {
        if (strcmp(ThucDon[i].dish_name, dish_name) == 0) {
            printf("Cap nhat ten mon an: ");
            fgets(ThucDon[i].dish_name, sizeof(ThucDon[i].dish_name), stdin);
            ThucDon[i].dish_name[strcspn(ThucDon[i].dish_name, "\n")] = '\0';
            printf("Cap nhat muc gia moi: ");
            scanf("%f", &ThucDon[i].price);

            printf("Cap nhat thong tin thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay mon an!\n");
}

// Ham xoa mon an ra khoi thuc don
void deleteDish() {
    char dish_name[30];
    printf("Nhap ten mon an can xoa: ");
    clearBuffer();
    fgets(dish_name, sizeof(dish_name), stdin);
    dish_name[strcspn(dish_name, "\n")] = '\0';

    for (int i = 0; i < menu_count; i++) {
        if (strcmp(ThucDon[i].dish_name, dish_name) == 0) {
            for (int j = i; j < menu_count - 1; j++) {
                ThucDon[j] = ThucDon[j + 1];
            }
            menu_count--;
            printf("Da xoa mon an khoi thuc don!\n");
            return;
        }
    }
    printf("Khong tim thay mon an!\n");
}

//
// Chuong trinh quan ly khach hang
//

// Ham hien thi thong tin khach hang
void hienThiKH(const khachhang* kh){
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

// Ham hien thi danh sach khach hang
void hienThiTatCa() {
    sapXepKhachHang();
    printf("\n----------Thong tin khach hang----------\n");
    printf("|-------------------------|-------------------------|---------------|\n");
    printf("|           Ten khach hang|                  Dia chi|  So dien thoai|\n");
    printf("|-------------------------|-------------------------|---------------|\n");
    for (int i = 0; i < demkhach; i++) {
        hienThiKH(&customers[i]);
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
void menuKH() {
    printf("\nQuan ly khach hang");
    printf("\n1. Them khach hang");
    printf("\n2. Tim kiem khach hang");
    printf("\n3. Hien thi tat ca khach hang");
    printf("\n4. Cap nhat thong tin khach hang");
    printf("\n5. Xoa khach hang");
    printf("\n6. Thoat chuong trinh");
}

// Ham tim kiem khach hang
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
            hienThiKH(&khang[i]);
        }
    }
    if (!found) {
        printf("\nKhong tim thay thong tin khach hang!\n");
    }
}

// Ham xoa thong tin khach hang
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
void capNhatKH(khachhang khang[], int n) {
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


//
// Chuong trinh quan ly nhan vien
//

// Ham hien thi thong tin cua nhan vien
void hienThiNV(const nhanvien* nv){
    printf("| ID: %5s | Name: %20s | Gender: %5s | Age: %3d | Phone Number: %11s | Position: %15s |", 
    nv->id, nv->name, nv->gender, nv->age, nv->phonenumber, nv->position);
    printf("\n|-----------|----------------------------|---------------|----------|---------------------------|---------------------------|\n");
}

// Ham nhap thong tin cua nhan vien
void nhapThongTin(nhanvien* nv){
    printf("\nNhap ID: ");
    scanf("%s", nv->id);
    getchar();
    printf("Nhap ten nhan vien: ");
    fgets(nv->name, 100, stdin);
    nv->name[strcspn(nv->name, "\n")] = 0;
    printf("Nhap gioi tinh: ");
    scanf("%s", nv->gender);
    printf("Nhap tuoi: ");
    scanf("%d", &nv->age);
    getchar();
    printf("Nhap so dien thoai: ");
    scanf("%s", nv->phonenumber);
    getchar();
    printf("Nhap chuc vu: ");
    fgets(nv->position, 100, stdin);
    nv->position[strcspn(nv->position, "\n")] = 0;
    inhoa(nv->name);
    inhoa(nv->gender);
    inhoa(nv->position);
}

//Nhap danh sach nhan vien
void nhapDS(nhanvien nvien[], int n){
    for(int i = 0; i<n; i++){
        int gtri;
        do{
            gtri = 1;
            printf("\nNhap thong tin nhan vien thu %d: ", i+1);
            nhapThongTin(&nvien[i]);
            for(int j = 0; j<i; j++){
                if(strcmp(nvien[j].id, nvien[i].id) == 0){
                    printf("\nID da ton tai, vui long nhap lai: ");
                    gtri = 0;
                    break;
                }
            }
        } while (!gtri);
    }
}

//Sap xep nhan vien
void sapxepNV(nhanvien nvien[], int n){
    for(int i = 0; i<n-1; i++){
        for(int j = i+1; j<n; j++){
            if(chudau(nvien[i].name) > chudau(nvien[j].name)){
                nhanvien temp = nvien[i];
                nvien[i] = nvien[j];
                nvien[j] = temp;
            }
        }
    }
}

//Hien thi menu de lua chon
void menuNV(){
    printf("\n\n\n========= Menu Quan Ly Nhan Vien ==========");
    printf("\n| 1 | Hien thi danh sach nhan vien");
    printf("\n| 2 | Them nhan vien");
    printf("\n| 3 | Tim kiem nhan vien");
    printf("\n| 4 | Xoa nhan vien");
    printf("\n| 5 | Cap nhat thong tin nhan vien");
    printf("\n| 0 | Thoat");
}

//Hien thi danh sach nhan vien
void hienThiDS(nhanvien nvien[], int n){
    printf("\n------------- Danh Sach Nhan Vien ------------\n");
    printf("\n|-----------|----------------------------|---------------|----------|---------------------------|---------------------------|\n");
    sapxepNV(nvien, n);
    for(int i = 0; i<n; i++){
        hienThiNV(&nvien[i]);
    }
}

//Them nhan vien
void themNV(nhanvien nvien[], int &n, int t){
    for(int i = n; i<n+t; i++){
        int gtri;
        do{
            gtri = 1;
            printf("\nNhap thong tin nhan vien thu %d", i+1);
            nhapThongTin(&nvien[i]);
            for(int j = 0; j<i; j++){
                if(strcmp(nvien[j].id, nvien[i].id) == 0){
                    printf("\nID da ton tai, vui long nhap lai: ");
                    gtri = 0;
                    break;
                }
            }
        } while(!gtri);
    }
    n += t;
}

//Tim kiem nhan vien
void timNV(nhanvien nvien[], int n){
    char ttin[100];
    int found = 0;
    printf("\nNhap ten cua nhan vien muon tim kiem: ");
    fgets(ttin, 100, stdin);
    ttin[strcspn(ttin, "\n")] = 0;
    inhoa(ttin);
    
    for (int i = 0; i < n; i++) {
        if (strstr(nvien[i].name, ttin) != NULL) {
            found = 1;
            hienThiNV(&nvien[i]);
        }
    }
    if(!found){
        printf("\nKhong tim thay nhan vien can tim! ");
    }
}

//Xoa nhan vien
void xoaNV(nhanvien nvien[], int& n){
    char ttin[100];
    int found = 0;
    int dlt = 0;

    printf("\nNhap ten cua nhan vien muon xoa: ");
    fgets(ttin, 100, stdin);
    ttin[strcspn(ttin, "\n")] = 0;
    inhoa(ttin);

    for (int i = 0; i < n; i++) {
        if (strstr(nvien[i].name, ttin) != NULL) {
            found = 1;
            dlt = i;
            break;
        }
    }

    if (found) {
        for (int i = dlt; i < n - 1; i++) {
            nvien[i] = nvien[i + 1];
        }
        n--;
        printf("\nNhan vien da duoc xoa thanh cong! \n");
    } else {
        printf("\nKhong tim thay nhan vien can tim! \n");
    }
}

//Cap nhat thong tin cho nhan vien
void capNhatNV(nhanvien nvien[], int n){
    char ttin[100];
    int found = 0;
    printf("\nNhap ten cua nhan vien muon xoa: ");
    fgets(ttin, 100, stdin);
    ttin[strcspn(ttin, "\n")] = 0;

    for(int i = 0; i<n; i++){
        inhoa(ttin);

        if(strstr(nvien[i].name, ttin) != NULL){
            found = 1;
            printf("\nNhap thong tin cap nhat cho nhan vien: \n");
            nhapThongTin(&nvien[i]);
            break;
        }
    }
    if(found){
        printf("\nNhan vien da duoc cap nhat!");
    }
    else{
        printf("\nKhong tim thay nhan vien can tim!");
    }
}



// Ham hien thi menu chuong trinh
void menu(){
    printf("\n-------- HE THONG QUAN LY NHA HANG ------------\n");
    printf("1. Quan ly dat ban\n");
    printf("2. In hoa don\n");
    printf("3. Quan ly thuc don\n");
    printf("4. Quan ly khach hang\n");
    printf("5. Quan ly nhan vien\n");
    printf("6. Doanh thu\n");
    printf("0. Thoat chuong trinh\n");
    printf("Vui long nhap lua chon cua ban: ");
}

int main() {
    Quanlydatban qldb;
    qldb.soluongban = 0;
    SanPham sanPhams[MAX_ITEMS];
    int soLuongSanPham = 0;
    char nhapThem;
    PhuongThucThanhToan phuongThucThanhToan;
    char tenKH[50];
    int n = 0;
    nhanvien nvien[100];
    int choice, choice1, choice2, choice3, choice4, choice5;
    do{
        menu();
        scanf("%d", &choice);
        switch(choice){
            case 1:
                do {
                    menuDB();
                    scanf("%d", &choice1);
                    switch (choice1) {
                    case 1:
                        datban(&qldb);
                        break;
                    case 2:
                        huyban(&qldb);
                        break;
                    case 3:
                        timkiem(&qldb);
                        break;
                    case 4:
                        danhsachban(&qldb);
                        break;
                    case 5:
                        sobanconlai(&qldb);
                        break;
                    case 6:
                        printf("Thoat khoi chuc nang\n");
                        break;
                    default:
                        printf("Khong hop le, vui long nhap lai\n");
                    }
                } while (choice1 != 6);
                break;
            case 2: 
                printf("Hóa đơn thanh toán\n");
                printf("-----------------------------------\n");
                printf("Nhập tên khách hàng: ");
                scanf(" %[^\n]", tenKH);
                inhoa(tenKH);
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
                do {
                    printf("Chọn phương thức thanh toán:\n");
                    printf("1. Tiền mặt\n");
                    printf("2. Thẻ tín dụng\n");
                    printf("3. Chuyển khoản ngân hàng\n");
                    printf("4. Ví điện tử\n");
                    printf("Lựa chọn của bạn là: ");
                    scanf("%d", &choice2);
                    switch (choice2) {
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
                } while (choice2 < 1 || choice2 > 4);

                inHoaDon(sanPhams, soLuongSanPham, phuongThucThanhToan, tenKH);
                break;
            case 3:
                do {
                    printf("\nQuan ly thuc don");
                    printf("\n1. Them mon an");
                    printf("\n2. Tim kiem mon an");
                    printf("\n3. Hien thi tat ca mon an");
                    printf("\n4. Cap nhat thong tin mon an");
                    printf("\n5. Xoa mon an khoi thuc don");
                    printf("\n6. Thoat chuong trinh");
                    printf("\nNhap so de tiep tuc: ");
                    scanf("%d", &choice3);

                    switch (choice3) {
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
                        default: printf("Lua chon khong hop le, vui long chon lai!\n");
                    }
                } while (choice3 != 6);
                break;
            case 4:
                do {
                    menuKH();
                    printf("\nNhap so de tiep tuc: ");
                    scanf("%d", &choice4);
                    getchar(); // Loại bỏ ký tự '\n' trong buffer

                    switch (choice4) {
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
                            capNhatKH(customers, demkhach);
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
                } while (choice4 != 6);
                break;
            case 5:
                printf("\nNhap so luong nhan vien: ");
                scanf("%d", &n);
                nhapDS(nvien, n);
                do{
                    menuNV();
                    printf("\nNhap lua chon cua ban: ");
                    scanf("%d", &choice5);
                    getchar();

                    switch (choice5) {
                        case 1:
                            hienThiDS(nvien, n);
                            break;
                        case 2:
                            int t;
                            printf("\nNhap so luong nhan vien tang them: ");
                            scanf("%d", &t);
                            themNV(nvien, n, t);
                            break;
                        case 3:
                            timNV(nvien, n);
                            break;
                        case 4:
                            xoaNV(nvien, n);
                            break;
                        case 5:
                            capNhatNV(nvien, n);
                            break;
                        case 0:
                            printf("Thoat chuong trinh\n");
                            break;
                        default:
                            printf("Lua chon khong hop le, vui long chon lai!\n");
                            break;
                    }
                } while (choice5 != 0);
                break;
            case 6:{
                FILE *f;
                f = fopen ("hoa_don.txt", "r");
                if(f == NULL){
                    printf("\nLoi tao mo file!");
                    break;
                }
                double temp = 0.0;
                fscanf(f, "%lf", &temp);
                printf("\nDoanh thu la: %.0lf \n", temp);
                fclose(f);
                break;
            }   
            case 0:
                printf("Thoat chuong trinh!");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai!");
                break;
        }
    }while(choice != 0);

    return 0;
}