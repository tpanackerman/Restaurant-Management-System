#include<stdio.h>

int main(){
    FILE *f;
    f = fopen ("hoa_don.txt", "r");
    if(f == NULL){
        printf("\nLoi tao mo file!");
        return 1;
    }
    double tong = 0.0;
    fscanf(f, "%lf", &tong);
    printf("\nDoanh thu la: %.0lf", tong);
    fclose(f);
    return 0;
}
