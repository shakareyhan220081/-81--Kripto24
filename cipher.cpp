#include <iostream>
#include <string>

using namespace std;

// Fungsi untuk mengenkripsi dengan Shift Cipher
string enkripsiShiftCipher(string teks, int k) {
    string hasil = "";
    for (int i = 0; i < teks.length(); i++) {
        // Enkripsi hanya huruf besar (A-Z)
        if (isupper(teks[i])) {
            hasil += char(int(teks[i] + k - 65) % 26 + 65);
        } else {
            hasil += teks[i];
        }
    }
    return hasil;
}

// Fungsi untuk mendekripsi dengan Shift Cipher
string dekripsiShiftCipher(string teks, int k) {
    string hasil = "";
    for (int i = 0; i < teks.length(); i++) {
        // Dekripsi hanya huruf besar (A-Z)
        if (isupper(teks[i])) {
            hasil += char(int(teks[i] - k - 65 + 26) % 26 + 65);
        } else {
            hasil += teks[i];
        }
    }
    return hasil;
}

int main() {
    string teks1 = "HASKELL";
    int k1 = 20;
    cout << "Enkripsi '" << teks1 << "' dengan k = " << k1 << ": " << enkripsiShiftCipher(teks1, k1) << endl;

    string teks2 = "ETURF";
    int k2 = 12;
    cout << "Dekripsi '" << teks2 << "' dengan k = " << k2 << ": " << dekripsiShiftCipher(teks2, k2) << endl;

    return 0;
}
