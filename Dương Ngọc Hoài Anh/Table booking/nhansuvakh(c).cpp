#include<stdio.h>
#include<string.h>
 
#define MAX_CUSTOMER 100

//struct nhan vien
typedef struct{
    char id[10];
    char name[100];
    char gender[10];
    int age;
    char phonenumber[11];
    char position[100];
} nhanvien;

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
void menuKH() {
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


//Hien thi thong tin cua nhan vien
void hienThi(const nhanvien* nv){
    printf("| ID: %5s | Name: %20s | Gender: %5s | Age: %3d | Phone Number: %11s | Position: %15s |", 
    nv->id, nv->name, nv->gender, nv->age, nv->phonenumber, nv->position);
    printf("\n|-----------|----------------------------|---------------|----------|---------------------------|---------------------------|\n");
}

//Nhap thong tin cua nhan vien
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
void sapxep(nhanvien nvien[], int n){
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
void menu(){
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
    sapxep(nvien, n);
    for(int i = 0; i<n; i++){
        hienThi(&nvien[i]);
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
            hienThi(&nvien[i]);
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
void capNhat(nhanvien nvien[], int n){
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

void pronumber()
{
	printf("\n*********PHAN MEM QUAN LY NHAN SU VA KHACH HANG*********");
	printf("\n1. Nhan vien");
	printf("\n2. Khach hang");
	printf("\n3. Thoat chuong trinh\n");
}
int main(){
	int choice;
	int n = 0;
	do{
		pronumber();
		printf("Nhap lua chon cua ban ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				int luachon;
                nhanvien nvien[100];
                printf("\nNhap so luong nhan vien: ");
                scanf("%d", &n);
                nhapDS(nvien, n);
                do{
                    menu();
                    printf("\nNhap lua chon cua ban: ");
                    scanf("%d", &luachon);
                    getchar();

                    switch (luachon) {
                        case 1:
                            hienThiDS(nvien, n);
                            break;
                        case 2:{
                            int t;
                            printf("\nNhap so luong nhan vien tang them: ");
                            scanf("%d", &t);
                            themNV(nvien, n, t);
                            break;
                        }
                        case 3:
                            timNV(nvien, n);
                            break;
                        case 4:
                            xoaNV(nvien, n);
                            break;
                        case 5:
                            capNhat(nvien, n);
                            break;
                        case 0:
                            printf("Thoat chuong trinh\n");
                            break;
                        default:
                            printf("Lua chon khong hop le, vui long chon lai!\n");
                            break;
                    }
                } while (luachon != 0);
            case 2:
            	int chon;
                do {
                menuKH();
                printf("\nNhap so de tiep tuc: ");
                scanf("%d", &chon);
                getchar(); 

                switch (chon) {
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
            } while (chon != 6);
            case 3:
            	printf("\nBan da thoat khoi chuong trinh");
            	return 0;
            default:
            	printf("Lua chon khong hop le, vui long chon lai!\n");
            	break;
		}
	}while(choice!= 0);
	return 0;
	
}


