#include<stdio.h>
#include<string.h>

//struct nhan vien
typedef struct{
    char id[10];
    char name[100];
    char gender[10];
    int age;
    char phonenumber[11];
    char position[100];
} nhanvien;

//In hoa chu cai dau tien
void inhoa(char name[]){
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

int main(){
    int luachon;
    int n = 0;
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

    
    return 0;
}
