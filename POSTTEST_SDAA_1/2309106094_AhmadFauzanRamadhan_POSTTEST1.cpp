#include <iostream>
using namespace std;

int segitiga_pascal(int row, int col) {
    if (col == 0 || col == row) {
        return 1;
    }
    return segitiga_pascal(row - 1, col - 1) + segitiga_pascal(row - 1, col);
}

void printPascalTriangle(int n) {
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col <= row; ++col) {
            cout << segitiga_pascal(row, col) << " ";
        }
        cout << endl;
    }
}

int main() {
    int n = 3;
    printPascalTriangle(n);
    return 0;
}
