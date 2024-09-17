#include <iostream>
#include <vector>
using namespace std;

// Fungsi untuk mengalikan matriks
vector<int> multiplyMatrix(vector<vector<int>>& K, vector<int>& P) {
    vector<int> result(2);
    result[0] = (K[0][0] * P[0] + K[0][1] * P[1]) % 26;
    result[1] = (K[1][0] * P[0] + K[1][1] * P[1]) % 26;

    // Jika hasil negatif, tambahkan 26 untuk memastikan dalam rentang 0-25
    if (result[0] < 0) result[0] += 26;
    if (result[1] < 0) result[1] += 26;

    return result;
}

// Fungsi untuk mendapatkan invers dari bilangan modulo 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Fungsi untuk mencari invers matriks
vector<vector<int>> inverseMatrix(vector<vector<int>>& K) {
    int determinant = (K[0][0] * K[1][1] - K[0][1] * K[1][0]) % 26;
    if (determinant < 0) determinant += 26;  // Pastikan determinan positif

    int invDet = modInverse(determinant, 26);

    if (invDet == -1) {
        cout << "Invers matriks tidak ditemukan!" << endl;
        exit(1);
    }

    vector<vector<int>> K_inv(2, vector<int>(2));
    K_inv[0][0] = (K[1][1] * invDet) % 26;
    K_inv[0][1] = (-K[0][1] * invDet + 26) % 26;
    K_inv[1][0] = (-K[1][0] * invDet + 26) % 26;
    K_inv[1][1] = (K[0][0] * invDet) % 26;

    // Jika ada elemen negatif, tambahkan 26
    if (K_inv[0][0] < 0) K_inv[0][0] += 26;
    if (K_inv[0][1] < 0) K_inv[0][1] += 26;
    if (K_inv[1][0] < 0) K_inv[1][0] += 26;
    if (K_inv[1][1] < 0) K_inv[1][1] += 26;

    return K_inv;
}

// Fungsi Enkripsi
string encrypt(string text, vector<vector<int>>& K) {
    string ciphertext = "";
    for (int i = 0; i < text.length(); i += 2) {
        vector<int> P = {text[i] - 'A', text[i + 1] - 'A'};
        vector<int> C = multiplyMatrix(K, P);
        ciphertext += char(C[0] + 'A');
        ciphertext += char(C[1] + 'A');
    }
    return ciphertext;
}

// Fungsi Dekripsi
string decrypt(string ciphertext, vector<vector<int>>& K_inv) {
    string plaintext = "";
    for (int i = 0; i < ciphertext.length(); i += 2) {
        vector<int> C = {ciphertext[i] - 'A', ciphertext[i + 1] - 'A'};
        vector<int> P = multiplyMatrix(K_inv, C);
        plaintext += char(P[0] + 'A');
        plaintext += char(P[1] + 'A');
    }
    return plaintext;
}

int main() {
    // Input dari pengguna
    string plaintext;
    cout << "Masukkan plaintext (harus genap jumlah huruf, tanpa spasi): ";
    cin >> plaintext;
    
    // Pastikan panjang plaintext genap
    if (plaintext.length() % 2 != 0) {
        cout << "Plaintext harus memiliki jumlah huruf genap!" << endl;
        return 1;
    }

    // Matriks kunci 2x2 dari pengguna
    vector<vector<int>> K(2, vector<int>(2));
    cout << "Masukkan elemen matriks kunci 2x2:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> K[i][j];
        }
    }

    // Enkripsi
    string ciphertext = encrypt(plaintext, K);
    cout << "Ciphertext: " << ciphertext << endl;

    // Cari invers matriks
    vector<vector<int>> K_inv = inverseMatrix(K);

    // Dekripsi
    string decryptedText = decrypt(ciphertext, K_inv);
    cout << "Plaintext setelah dekripsi: " << decryptedText << endl;

    return 0;
}
