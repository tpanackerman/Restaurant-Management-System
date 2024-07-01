#include <iostream>
#include <cstring>
#include <string>

using namespace std;

const int sobanmax = 100;

struct Ban { 
    int soban;
    char tenkhach[100];
};

class Quanlydatban {
public:
    Ban bans[sobanmax];
    int soluongban = 0;
    
    // hien thi ban da duoc dat boi khach
    void hienthi(Ban ban) {
        cout << "Ban so " << ban.soban << " da duoc dat boi " << ban.tenkhach << endl;
        cout << "---------------------------------------------------------" << endl;
    }

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

    // dat ban
    void datban() {
        if (soluongban >= sobanmax) {
            cout << "Da het ban" << endl;
            return;
        }

        int sobandat;
        int ktra;
        do{
            ktra = 1;
            cout << "So ban muon dat: ";
            cin >> sobandat;
            cin.ignore();
            if (sobandat <= 0 || sobandat > sobanmax) {
                cout << "Vui long nhap so ban tu 1 den " << sobanmax << endl;
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

    // huy ban
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

    // tim kiem ban
    void timkiem() {
        char ten[100];
        cout << "Nhap ten khach hang: ";
        cin.getline(ten, 100);
        inhoa(ten);
        int kt=0;

        for (int i = 0; i < soluongban; i++) {
            if (strstr(bans[i].tenkhach, ten) != NULL) {
            	kt=1;
                hienthi(bans[i]);
            }
        }
        if(kt==0) cout<<"\nKhong tim thay khach hang\n";
		
    }

    // danh sach ban duoc dat
    void danhsachban() {
        for(int i = 0; i<soluongban-1; i++){
            for(int j = i+1; j<soluongban; j++){
                if(bans[i].soban > bans[j].soban){
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

    // so luong ban con lai
    void sobanconlai() {
        cout << "So luong ban con lai cua nha hang: " << (sobanmax - soluongban) << endl;
    }

    // chon chuc nang
    void menu() {
        cout << "\nQUAN LY BAN CUA NHA HANG\n";
        cout << "1. Dat ban\n";
        cout << "2. Huy ban\n";
        cout << "3. Tim kiem ban\n";
        cout << "4. Danh sach ban va khach hang\n";
        cout << "5. So luong ban con lai\n";
        cout << "6. Thoat\n";
        cout << "Vui long chon muc tu 1->6: ";
    }
};

int main() {
    Quanlydatban qldb;
    int choice;

    do {
        qldb.menu();
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

    return 0;
}
