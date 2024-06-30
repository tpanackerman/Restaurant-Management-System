#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream file("hoa_don.txt");
    if (!file) {
        cerr << "\nLỗi khi mở file!";
        return 1;
    }
    double tong = 0.0;
    file >> tong;
    cout << "\nDoanh thu là: " << tong << endl;
    file.close();
    return 0;
}
