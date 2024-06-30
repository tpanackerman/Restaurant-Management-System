#include <iostream>
#include <string>
#include <vector>

#define MAX_MENU_ITEMS 50

using namespace std;

class MenuItem {
public:
    string dish_name;
    float price;
};

vector<MenuItem> menu;

void clearBuffer() {
    cin.ignore(); // Đọc bỏ một ký tự dư thừa trong bộ đệm
}

void addDish() {
    if (menu.size() >= MAX_MENU_ITEMS) {
        cout << "Thuc don da day!\n";
        return;
    }

    MenuItem m;
    clearBuffer();
    cout << "Nhap ten mon: ";
    getline(cin, m.dish_name);
    cout << "Nhap gia mon: ";
    cin >> m.price;

    menu.push_back(m);
    cout << "Mon an da duoc them vao thuc don!\n";
}

void displayDish() {
    string dish_name;
    cout << "Nhap ten mon: ";
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
    cout << "\nThuc don:\n";
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

int main() {
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
                cout << "Lua chon khong hop le, vui long chon lai!\n";
        }
    } while (choice != 6);

    return 0;
}
