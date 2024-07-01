#include <stdio.h>
#include <string.h>

#define SOBANMAX 100

typedef struct {
    int soban;
    char tenkhach[100];
} Ban;

typedef struct {
    Ban ban[SOBANMAX];
    int soluongban;
} Quanlydatban;

void hienthi(Ban ban) {
    printf("-----------------------------------------------------\n");
    printf("Ban so %d da duoc dat boi %s\n", ban.soban, ban.tenkhach);
}

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
        }
    }

    printf("\nKhong tim thay ban quy khach da dat!\n");
}

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

void sobanconlai(Quanlydatban *qldb) {
    printf("So luong ban con lai cua nha hang: %d\n", SOBANMAX - qldb->soluongban);
}

void menu() {
    printf("\nQUAN LY BAN CUA NHA HANG\n");
    printf("1. Dat ban\n");
    printf("2. Huy ban\n");
    printf("3. Tim kiem ban\n");
    printf("4. Danh sach ban va khach hang\n");
    printf("5. So luong ban con lai\n");
    printf("6. Thoat\n");
    printf("Vui long chon muc tu 1->6: ");
}

int main() {
    Quanlydatban qldb;
    qldb.soluongban = 0;
    int choice;

    do {
        menu();
        scanf("%d", &choice);
        switch (choice) {
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
    } while (choice != 6);

    return 0;
}

