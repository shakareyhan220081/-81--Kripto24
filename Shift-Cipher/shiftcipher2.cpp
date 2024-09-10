#include <iostream>
#include <string>

using namespace std;


string terapkanROT13(const string& teks) {
    string hasil = teks;
    for (size_t i = 0; i < teks.length(); ++i) {
        char c = teks[i];
        if (c >= 'A' && c <= 'Z') {
            hasil[i] = (c - 'A' + 13) % 26 + 'A'; 
        } else if (c >= 'a' && c <= 'z') {
            hasil[i] = (c - 'a' + 13) % 26 + 'a'; 
        }
    }
    return hasil;
}

int main() {
    string inputTeks;
    
    // Input dari pengguna
    cout << "Masukkan teks untuk mengenkripsi dengan ROT13: ";
    getline(cin, inputTeks);
    
    // Menerapkan ROT13
    string teksTerenkripsi = terapkanROT13(inputTeks);
    
    // Menampilkan hasil enkripsi
    cout << "Teks terenkripsi dengan ROT13: " << teksTerenkripsi << endl;
    
    return 0;
}
