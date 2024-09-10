#include <iostream>
#include <string>

using namespace std;


int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}


string enkripsiAffine(string teks, int a, int b) {
    string hasil = "";
    for (char &c : teks) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = ((a * (c - base) + b) % 26) + base;
        }
        hasil += c;
    }
    return hasil;
}


string dekripsiAffine(string teks, int a, int b) {
    string hasil = "";
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        return "Invers dari a tidak ditemukan!";
    }
    for (char &c : teks) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (a_inv * ((c - base) - b + 26) % 26) + base;
        }
        hasil += c;
    }
    return hasil;
}

int main() {
    string nama = "shaka reyhan saputra";  
    int a = 9;                             
    int b = 81 % 26;                       

    cout << "Nama asli: " << nama << endl;

    // Proses enkripsi
    string terenkripsi = enkripsiAffine(nama, a, b);
    cout << "Nama terenkripsi: " << terenkripsi << endl;

    // Proses dekripsi
    string terdekripsi = dekripsiAffine(terenkripsi, a, b);
    cout << "Nama terdekripsi: " << terdekripsi << endl;

    return 0;
}
