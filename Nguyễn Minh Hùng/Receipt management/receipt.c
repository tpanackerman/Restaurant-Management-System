#include <stdio.h>
#include <string.h>

#define MAX_MENU_ITEMS 50

typedef struct {
    char dish_name[30];
    float price;
} MenuItem;

MenuItem menu[MAX_MENU_ITEMS];
int menu_count = 0;

void clearBuffer() {
    while (getchar() != '\n');
}

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

    menu[menu_count++] = m;
    printf("Mon an da duoc them vao thuc don!\n");
}

void displayDish() {
    char dish_name[30];
    printf("Nhap ten mon: ");
    clearBuffer();
    fgets(dish_name, sizeof(dish_name), stdin);
    dish_name[strcspn(dish_name, "\n")] = '\0';

    for (int i = 0; i < menu_count; i++) {
        if (strcmp(menu[i].dish_name, dish_name) == 0) {
            printf("\nThong tin mon an:\n");
            printf("Ten mon: %s\n", menu[i].dish_name);
            printf("Gia thanh: %.0f\n", menu[i].price);
            return;
        }
    }
    printf("Khong tim thay mon an!\n");
}

void displayAllDishes() {
    printf("\nThuc don:\n");
    printf("-----------------------------------------------------\n");
    printf("Ten mon             | Gia thanh \n");
    printf("--------------------|--------------------------------\n");
    for (int i = 0; i < menu_count; i++) {
        printf("%-20s|%-10.0f\n", menu[i].dish_name, menu[i].price);
    }
}

void editDish() {
    char dish_name[30];
    printf("Nhap ten mon can cap nhat: ");
    clearBuffer();
    fgets(dish_name, sizeof(dish_name), stdin);
    dish_name[strcspn(dish_name, "\n")] = '\0';

    for (int i = 0; i < menu_count; i++) {
        if (strcmp(menu[i].dish_name, dish_name) == 0) {
            printf("Cap nhat ten mon an: ");
            fgets(menu[i].dish_name, sizeof(menu[i].dish_name), stdin);
            menu[i].dish_name[strcspn(menu[i].dish_name, "\n")] = '\0';
            printf("Cap nhat muc gia moi: ");
            scanf("%f", &menu[i].price);

            printf("Cap nhat thong tin thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay mon an!\n");
}

void deleteDish() {
    char dish_name[30];
    printf("Nhap ten mon an can xoa: ");
    clearBuffer();
    fgets(dish_name, sizeof(dish_name), stdin);
    dish_name[strcspn(dish_name, "\n")] = '\0';

    for (int i = 0; i < menu_count; i++) {
        if (strcmp(menu[i].dish_name, dish_name) == 0) {
            for (int j = i; j < menu_count - 1; j++) {
                menu[j] = menu[j + 1];
            }
            menu_count--;
            printf("Da xoa mon an khoi thuc don!\n");
            return;
        }
    }
    printf("Khong tim thay mon an!\n");
}

int main() {
    int choice;
    do {
        printf("\nQuan ly thuc don");
        printf("\n1. Them mon an");
        printf("\n2. Tim kiem mon an");
        printf("\n3. Hien thi tat ca mon an");
        printf("\n4. Cap nhat thong tin mon an");
        printf("\n5. Xoa mon an khoi thuc don");
        printf("\n6. Thoat chuong trinh");
        printf("\nNhap so de tiep tuc: ");
        scanf("%d", &choice);

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
            default: printf("Lua chon khong hop le, vui long chon lai!\n");
        }
    } while (choice != 6);

    return 0;
}
