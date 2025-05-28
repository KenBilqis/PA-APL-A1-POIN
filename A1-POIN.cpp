#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

const int maksimalPesanan = 100;
const int maksimalProduk = 100;

// Struct data pesanan
struct Pesanan {
    string namaPemesan;
    string namaItem;
    string ukuranPesanan;
    int jumlah;
    int totalHarga;
};

// Struct data produk
struct Produk {
    string nama;
    string harga;
};

// Struct data akun
struct Akun {
    string username;
    string password;
    bool isAdmin = false;
    Pesanan daftarPesanan[maksimalPesanan]; // Nested struct untuk menyimpan pesanan
    int itemPesanan = 0;
    Pesanan keranjang[maksimalPesanan];  // Menambah keranjang for user
    int itemKeranjang = 0;               // Menghitung isi keranjang
};

// Mendeklarasikan fungsi dan prosedur dengan pointer
void tampilkanMenuAwal();
bool UsernameAda(const Akun* daftarAkun, int totalAkun, const string& username);
bool ValidasiUsername(const string& username);
void prosesRegistrasi(Akun* daftarAkun, int* totalAkun); // Menggunakan pointer
bool prosesLogin(Akun* daftarAkun, int totalAkun, int* indeksPenggunaAktif, int* kesempatanLogin, bool* isAdmin); // Menggunakan pointer
void tampilkanMenuUser();
void tampilkanKeranjang(const Akun* akunPengguna);
void tambahKeKeranjang(Akun* akunPengguna, Produk* daftarProduk, int jumlahProduk);
void ubahItemKeranjang(Akun* akunPengguna, Produk* daftarProduk, int jumlahProduk);
void hapusItemKeranjang(Akun* akunPengguna, Produk* daftarProduk, int jumlahProduk);
void checkout(Akun* akunPengguna);
void tampilkanMenuAdmin();
void tampilkanInformasiMerchandise(Produk* daftarProduk, int jumlahProduk);
void tampilkanPesanKeluar();
void tampilkanPesanError();
int hitungTotalPesananRekursif(const Akun* akunPengguna, int indeks); // Menggunakan pointer
void tampilkanPesanan(const Pesanan* pesanan); // Menggunakan pointer (dereference)
void tampilkanPesanan(const Pesanan* pesanan, int nomor); // Overloading dengan pointer
void lihatSemuaPesanan(Akun* daftarAkun, int totalAkun);
void tambahProduk(Produk* daftarProduk, int* jumlahProduk);
void MenuSorting(Pesanan* semuaPesanan, int totalSemuaPesanan);
void tampilkanDaftarPesanan(Pesanan* pesanan, int jumlah);
void urutkanNamaPemesanQuickSort(Pesanan* pesanan, int low, int high); // Quick Sort
void urutkanNamaItemSelectionSort(Pesanan* pesanan, int jumlah);
void urutkanJumlahInsertionSort(Pesanan* pesanan, int jumlah);
void urutkanTotalHargaBubbleSort(Pesanan* pesanan, int jumlahPesanan);
int konversiHarga(string hargaStr);
void menuSearching(Pesanan* semuaPesanan, int totalSemuaPesanan);
void tampilkanHasilSearching(Pesanan* hasil[], int jumlah);
int binarySearchNamaPemesan(Pesanan* pesanan, int jumlah, string keyword, Pesanan** hasil);
int jumpSearchNamaItem(Pesanan* pesanan, int jumlah, string keyword, Pesanan** hasil);
int linearSearchUkuran(Pesanan* pesanan, int jumlah, string keyword, Pesanan** hasil);
int validasiInputPilihan(int min, int max, const string& pesan);
void ubahProduk(Produk* daftarProduk, int *jumlahProduk);
void hapusProduk(Produk* daftarProduk, int* jumlahProduk);
void hapusAkunUser(Akun* daftarAkun, int* totalAkun);

// Prosedur menampilkan menu awal
void tampilkanMenuAwal() {
    cout << "\n==========================================" << endl;
    cout << "==  SELAMAT DATANG DI PROGRAM PREORDER  ==" << endl;
    cout << "==     MERCHANDISE BAND THE JANSEN      ==" << endl;
    cout << "==========================================" << endl;
    cout << "\nSilahkan pilih menu:" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Keluar" << endl;
}

// Fungsi untuk memeriksa apakah username sudah ada
bool UsernameAda(const Akun* daftarAkun, int totalAkun, const string& username) {
    for (int i = 0; i < totalAkun; i++) {
        if (daftarAkun[i].username == username) {
            return true;
        }
    }
    return false;
}

// Fungsi untuk memvalidasi username
bool ValidasiUsername(const string& username) {
    // Panjang username harus antara 2-10 karakter
    if (username.length() < 2 || username.length() > 10) {
        return false;
    }
    
    // Username harus terdiri dari huruf saja (tidak boleh angka atau karakter khusus)
    for (char c : username) {
        if (!isalpha(c)) {
            return false;
        }
    }
    
    return true;
}

// Prosedur proses registrasi (menggunakan pointer)
void prosesRegistrasi(Akun* daftarAkun, int* totalAkun) {
    if (*totalAkun >= maksimalPesanan) {
        cout << "\n===============================" << endl;
        cout << "==  Kuota akun sudah penuh!  ==" << endl;
        cout << "===============================" << endl;
        return;
    }

    string username;
    bool usernameValid = false;
    
    do {
        cout << "\nMasukkan Username (2-10 huruf, tidak boleh angka/karakter): ";
        getline(cin, username);
        
        // Validasi username
        if (UsernameAda(daftarAkun, *totalAkun, username)) {
            cout << "Username sudah digunakan. Silakan pilih username lain.\n";
        } else if (!ValidasiUsername(username)) {
            cout << "Username tidak valid. Harus 2-10 huruf dan tidak mengandung angka/karakter.\n";
        } else {
            usernameValid = true;
        }
    } while (!usernameValid);

    string password;
    do {
        cout << "Masukkan Password: ";
        getline(cin, password);
        if (password.empty()) {
            cout << "Password tidak boleh kosong!" << endl;
        }
    } while (password.empty());
    
    daftarAkun[*totalAkun].username = username;
    daftarAkun[*totalAkun].password = password;
    daftarAkun[*totalAkun].isAdmin = false;
    (*totalAkun)++;
    
    cout << "\n=================================" << endl;
    cout << "==  Akun berhasil didaftarkan  ==" << endl;
    cout << "=================================" << endl;
}

// Fungsi proses login (menggunakan pointer)
bool prosesLogin(Akun* daftarAkun, int totalAkun, int* indeksPenggunaAktif, int* kesempatanLogin, bool* isAdmin) {
    string username, password;
    cout << "\nMasukkan Username: ";
    getline(cin, username);
    cout << "Masukkan Password: ";
    getline(cin, password);
    
    for (int i = 0; i < totalAkun; i++) {
        if (daftarAkun[i].username == username && daftarAkun[i].password == password) {
            *indeksPenggunaAktif = i;
            *isAdmin = daftarAkun[i].isAdmin;   // Set status admin atau user
            cout << "\n=======================" << endl;
            cout << "=  Login berhasil :D  =" << endl;
            cout << "=======================" << endl;
            return true;
        }
    }
    
    cout << "\n==========================================================" << endl;
    cout << "==  !!!Username atau Password yang dimasukkan salah!!!  ==" << endl;
    cout << "==========================================================" << endl;
    (*kesempatanLogin)++;
    
    if (*kesempatanLogin == 3) {
        cout << "\n===========================================" << endl;
        cout << "==  Maaf kesempatan login anda habis :(  ==" << endl;
        cout << "===========================================" << endl;
        exit(0);
    }
    
    return false;
}

// Prosedur menampilkan menu admin
void tampilkanMenuAdmin() {
    cout << "\n================================" << endl;
    cout << "==     MENU UTAMA ADMIN       ==" << endl;
    cout << "==  1. Tambah Produk          ==" << endl;
    cout << "==  2. Informasi Merchandise  ==" << endl;
    cout << "==  3. Lihat Semua Pesanan    ==" << endl;
    cout << "==  4. Ubah Produk            ==" << endl;
    cout << "==  5. Hapus Produk           ==" << endl;
    cout << "==  6. Hapus Akun             ==" << endl;
    cout << "==  7. Logout                 ==" << endl;
    cout << "================================" << endl;
}

// Prosedur menampilkan informasi merchandise
void tampilkanInformasiMerchandise(Produk* daftarProduk, int jumlahProduk) {
    try {
        if (daftarProduk == nullptr) {
            throw runtime_error("Data produk tidak ditemukan.");
        }
        if (jumlahProduk <= 0) {
            throw runtime_error("Belum ada produk yang ditambahkan.");
        }

        cout << "\n==   Informasi Merchandise   ==" << endl;
        cout << "\n" << setw(5) << "No" << setw(15) << "Item" << setw(20) << "Harga\n";
        
        for (int i = 0; i < jumlahProduk; i++) {
        cout << setw(5) << i+1 
             << setw(15) << daftarProduk[i].nama 
             << "   Rp" << setw(17) << daftarProduk[i].harga << "\n";
        }
        cout << "\n== Ukuran Tersedia: S/M/L/XL ==\n";
    }
    catch (const exception& e) {
        cerr << "\nTerjadi kesalahan: " << e.what() << endl;
    }   
    
}

// Prosedur admin untuk menambah produk
void tambahProduk(Produk* daftarProduk, int* jumlahProduk) {
    if (*jumlahProduk < maksimalProduk) {
        cout << "\n==   Tambah Produk   ==" << endl;


        // Validasi nama produk
        string namaProduk;
        bool namaValid = false;

        while (!namaValid) {
            cout << "\nMasukkan Nama Produk: ";
            getline(cin, namaProduk);

            namaProduk.erase(0, namaProduk.find_first_not_of(" \t"));
            namaProduk.erase(namaProduk.find_last_not_of(" \t") + 1);

            if (namaProduk.empty()) {
                cout << "Nama produk tidak boleh kosong atau hanya spasi!\n";
            } else {
                namaValid = true;
                daftarProduk[*jumlahProduk].nama = namaProduk;
            }
        }

        // Validasi harga produk
        string hargaInput;
        bool hargaValid = false;

        while (!hargaValid) {
            try {
                cout << "Masukkan Harga Produk: ";
                getline(cin, hargaInput);

                hargaInput.erase(0, hargaInput.find_first_not_of(" \t"));
                hargaInput.erase(hargaInput.find_last_not_of(" \t") + 1);

                if (hargaInput.empty()) {
                    throw runtime_error("Harga tidak boleh kosong atau hanya spasi!");
                }

                // Cek apakah hanya terdiri dari digit
                for (char c : hargaInput) {
                    if (!isdigit(c)) {
                        throw runtime_error("Harga hanya boleh terdiri dari angka.");
                    }
                }

                // Coba konversi ke integer (untuk memastikan inputnya valid)
                int harga = stoi(hargaInput);
                if (harga <= 0) {
                    throw runtime_error("Harga harus lebih dari 0");
                }
                // Harga valid
                daftarProduk[*jumlahProduk].harga = hargaInput;
                hargaValid = true;
            }
            catch (invalid_argument&) {
                cout << "Input harga tidak valid.\n";
            }
            catch (runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
            catch (...) {
                cout << "Terjadi kesalahan tak terduga saat input harga.\n";
            }
        }
        
        (*jumlahProduk)++;
        cout << "\n=================================" << endl;
        cout << "== Produk berhasil ditambahkan ==" << endl;
        cout << "=================================" << endl;
    } else {
        cout << "\n===============================" << endl;
        cout << "== Kuota produk sudah penuh! ==" << endl;
        cout << "===============================" << endl;
    }
}

// Menu sorting pesanan
void MenuSorting(Pesanan* semuaPesanan, int totalSemuaPesanan) {
    if (semuaPesanan == nullptr || totalSemuaPesanan <= 0) {
            throw runtime_error("Tidak ada data pesanan untuk disortir.");
            return;
    }

    int pilihan;
    do {
        cout << "\n========== MENU SORTING PESANAN ==========\n";
        cout << "1. Urutkan berdasarkan Nama Pemesan (Ascending - Quick Sort)\n";
        cout << "2. Urutkan berdasarkan Nama Item (Ascending - Selection Sort)\n";
        cout << "3. Urutkan berdasarkan Jumlah Pesanan (Descending - Insertion Sort)\n";
        cout << "4. Urutkan berdasarkan Total Harga (Descending - Bubble Sort)\n";
        cout << "5. Kembali\n";

        pilihan = validasiInputPilihan(1, 5, "Masukkan pilihan [1-5]: ");

        // Buat salinan untuk sorting
        Pesanan tempPesanan[maksimalPesanan];
        for (int i = 0; i < totalSemuaPesanan; i++) {
            tempPesanan[i] = semuaPesanan[i];
        }

        switch (pilihan) {
            case 1:
                urutkanNamaPemesanQuickSort(tempPesanan, 0, totalSemuaPesanan - 1);
                tampilkanDaftarPesanan(tempPesanan, totalSemuaPesanan);
                break;
            case 2:
                urutkanNamaItemSelectionSort(tempPesanan, totalSemuaPesanan);
                tampilkanDaftarPesanan(tempPesanan, totalSemuaPesanan);
                break;
            case 3:
                urutkanJumlahInsertionSort(tempPesanan, totalSemuaPesanan);
                tampilkanDaftarPesanan(tempPesanan, totalSemuaPesanan);
                break;
            case 4:
                urutkanTotalHargaBubbleSort(tempPesanan, totalSemuaPesanan);
                tampilkanDaftarPesanan(tempPesanan, totalSemuaPesanan);
                break;
            case 5:
                return;
            deafult:
                tampilkanPesanError();
                continue;  
        } 
    } while (true);
}


// Prosedur untuk format tampilan daftar pesanan
void tampilkanDaftarPesanan(Pesanan* pesanan, int jumlah) {
    cout << "\n=======================================================================================\n";
    cout << left
         << setw(5) << "NO"
         << setw(20) << "NAMA PEMESAN"
         << setw(20) << "NAMA ITEM"
         << setw(10) << "UKURAN"
         << setw(10) << "JUMLAH"
         << right << setw(20) << "TOTAL HARGA" << endl;
    cout << "=======================================================================================\n";

    // Jika tidak ada pesanan
    if (jumlah == 0) {
        cout << "Tidak ada pesanan untuk ditampilkan\n";
        return;
    }

    // Tampilkan setiap pesanan
    for (int i = 0; i < jumlah; i++) {
        cout << left
             << setw(5)  << i + 1
             << setw(20) << pesanan[i].namaPemesan
             << setw(20) << pesanan[i].namaItem
             << setw(10) << pesanan[i].ukuranPesanan
             << setw(10) << pesanan[i].jumlah
             << right << setw(10) << "Rp "
             << fixed << setprecision(0) << pesanan[i].totalHarga << endl;
    }

    cout << "=======================================================================================\n";
}

int partitionNamaPemesan(Pesanan* pesanan, int low, int high) {
    string pivot = pesanan[high].namaPemesan;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (pesanan[j].namaPemesan < pivot) {
            i++;
            swap(pesanan[i], pesanan[j]);
        }
    }
    swap(pesanan[i + 1], pesanan[high]);
    return i + 1;
}

// Quick Sort untuk mengurutkan nama pemesan secara ascending
void urutkanNamaPemesanQuickSort(Pesanan* pesanan, int low, int high) {
    if (low < high) {
        int pi = partitionNamaPemesan(pesanan, low, high);
        urutkanNamaPemesanQuickSort(pesanan, low, pi - 1);
        urutkanNamaPemesanQuickSort(pesanan, pi + 1, high);
    }
}

// Selection Sort untuk mengurutkan nama item secara ascending
void urutkanNamaItemSelectionSort(Pesanan* pesanan, int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < jumlah; j++) {
            if (pesanan[j].namaItem < pesanan[min_idx].namaItem) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(pesanan[i], pesanan[min_idx]);
        }
    }
}

// Insertion Sort untuk mengurutkan jumlah pesanan secara descending
void urutkanJumlahInsertionSort(Pesanan* pesanan, int jumlah) {
    for (int i = 1; i < jumlah; i++) {
        Pesanan key = pesanan[i];
        int j = i - 1;
        while (j >= 0 && pesanan[j].jumlah < key.jumlah) {
            pesanan[j + 1] = pesanan[j];
            j = j - 1;
        }
        pesanan[j + 1] = key;
    }
}

// Bubble Sort untuk mengurutkan total harga secara descending
void urutkanTotalHargaBubbleSort(Pesanan* pesanan, int jumlahPesanan) {
    for (int i = 0; i < jumlahPesanan - 1; i++) {
        for (int j = 0; j < jumlahPesanan - i - 1; j++) {
            if (pesanan[j].totalHarga < pesanan[j + 1].totalHarga) {
                // Tukar jika yang sekarang lebih kecil dari yang berikutnya
                Pesanan temp = pesanan[j];
                pesanan[j] = pesanan[j + 1];
                pesanan[j + 1] = temp;
            }
        }
    }
}

// Menu Searching
void menuSearching(Pesanan* semuaPesanan, int totalSemuaPesanan) {
    if (semuaPesanan == nullptr || totalSemuaPesanan <= 0) {
        throw runtime_error("Tidak ada data pesanan untuk dicari.");
        return;
    }

    int pilihan;
    do {
        try{        
            cout << "\n========== MENU SEARCHING PESANAN ==========\n";
            cout << "1. Cari berdasarkan Nama Pemesan (Binary Search)\n";
            cout << "2. Cari berdasarkan Nama Item (Jump Search)\n";
            cout << "3. Cari berdasarkan Ukuran (Linear Search)\n";
            cout << "4. Kembali\n";

            pilihan = validasiInputPilihan(1, 4, "Masukkan pilihan [1-4]: ");

            // Membuat salinan untuk diurutkan
            Pesanan tempPesanan[maksimalPesanan];
            for (int i = 0; i < totalSemuaPesanan; i++) {
                tempPesanan[i] = semuaPesanan[i];
            }

            string keywordStr;
            Pesanan* hasil[100];
            int jumlahHasil = 0;

            // Validasi input string
            auto validasiKeyword = [](string& input, const string& promt) {
                while (true) {
                    cout << promt;
                    getline(cin, input);

                    // Hapus spasi depan dan belakang
                    input.erase(0, input.find_first_not_of(' '));
                    input.erase(input.find_last_not_of(' ') + 1);

                    if (input.empty()) {
                        cout << "Input tidak boleh kosong atau hanya spasi.\n";
                        continue;
                    }
                    break;
                }
            };

            switch (pilihan) {
                case 1:
                    urutkanNamaPemesanQuickSort(tempPesanan, 0, totalSemuaPesanan - 1);
                    validasiKeyword(keywordStr, "Masukkan nama pemesan: ");
                    jumlahHasil = binarySearchNamaPemesan(tempPesanan, totalSemuaPesanan, keywordStr, hasil);
                    tampilkanHasilSearching(hasil, jumlahHasil);
                    break;

                case 2:
                    urutkanNamaItemSelectionSort(tempPesanan, totalSemuaPesanan);
                    validasiKeyword(keywordStr, "Masukkan nama item: ");
                    jumlahHasil = jumpSearchNamaItem(tempPesanan, totalSemuaPesanan, keywordStr, hasil);
                    tampilkanHasilSearching(hasil, jumlahHasil);
                    break;

                case 3:
                    validasiKeyword(keywordStr, "Masukkan ukuran pesanan (S/M/L/XL): ");
                    jumlahHasil = linearSearchUkuran(tempPesanan, totalSemuaPesanan, keywordStr, hasil);
                    tampilkanHasilSearching(hasil, jumlahHasil);
                    break;

                case 4:
                    return;
                default:
                    tampilkanPesanError();
                    break;
            }
        } catch (const exception& e) {
            cerr << "Terjadi kesalahan: " << e.what() << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);
}

// Binary Search untuk nama pemesan
int binarySearchNamaPemesan(Pesanan* pesanan, int jumlah, string keyword, Pesanan** hasil) {
    int left = 0, right = jumlah - 1;
    int mid;
    int jumlahHasil = 0;

    while (left <= right) {
        mid = left + (right - left) / 2;

        if (pesanan[mid].namaPemesan == keyword) {
            // Telusuri ke kiri dari mid
            int i = mid;
            while (i >= 0 && pesanan[i].namaPemesan == keyword) {
                i--;
            }
            i++;
            while (i < jumlah && pesanan[i].namaPemesan == keyword) {
                hasil[jumlahHasil++] = &pesanan[i];
                i++;
            }
            return jumlahHasil;
        }
        else if (pesanan[mid].namaPemesan < keyword) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return 0;   // Tidak ditemukan
}

// Jump Search untuk nama item
int jumpSearchNamaItem(Pesanan* pesanan, int jumlah, string keyword, Pesanan** hasil) {
    int step = sqrt(jumlah);
    int prev = 0;
    int jumlahHasil = 0;
    
    // Lompat antar blok
    while (prev < jumlah && pesanan[min(step, jumlah) - 1].namaItem < keyword) {
        prev = step;
        step += sqrt(jumlah);
        if (prev >= jumlah) {
            return 0;
        }
    }

    // Linear search di blok ini
    int i = prev;
    while (i < min(step, jumlah) && pesanan[i].namaItem <= keyword) {
        if (pesanan[i].namaItem == keyword) {
            hasil[jumlahHasil++] = &pesanan[i];
        }
        i++;
    }

    return jumlahHasil;
}

// Linear Search berdasarkan ukuran
int linearSearchUkuran(Pesanan* pesanan, int jumlah, string keyword, Pesanan** hasil) {
    int jumlahHasil = 0;
    for (int i = 0; i < jumlah; i++) {
        if (pesanan[i].ukuranPesanan == keyword) {
            hasil[jumlahHasil++] = &pesanan[i];
        }
    }
     return jumlahHasil;
}

// Menampilkan hasil searching dalam bentuk tabel
void tampilkanHasilSearching(Pesanan* hasil[], int jumlah) {
    if (jumlah == 0) {
        cout << "Tidak ditemukan hasil pencarian!\n";
        return;
    }

    cout << "\n=======================================================================================\n";
    cout << left
         << setw(5) << "NO"
         << setw(20) << "NAMA PEMESAN"
         << setw(20) << "NAMA ITEM"
         << setw(10) << "UKURAN"
         << setw(10) << "JUMLAH"
         << right << setw(20) << "TOTAL HARGA" << endl;
    cout << "=======================================================================================\n";
 
    for (int i = 0; i < jumlah; i++) {
        cout << left
             << setw(5)  << i + 1
             << setw(20) << hasil[i]->namaPemesan
             << setw(20) << hasil[i]->namaItem
             << setw(10) << hasil[i]->ukuranPesanan
             << setw(10) << hasil[i]->jumlah
             << right << setw(10) << "Rp "
             << fixed << setprecision(0) << hasil[i]->totalHarga << endl;
    }

    cout << "=======================================================================================\n";
}

// Prosedur menampilkan pesan keluar
void tampilkanPesanKeluar() {
    cout << "\n=================================================" << endl;
    cout << "==  Terimakasih Telah Menggunakan Program ini  ==" << endl;
    cout << "==  Mohon maaf apabila terdapat kekurangan :)  ==" << endl;
    cout << "=================================================" << endl;
}

// Prosedur menampilkan pesan error
void tampilkanPesanError() {
    cout << "\n=======================================" << endl;
    cout << "==  Mohon Maaf Pilihan Tidak Ada :(  ==" << endl;
    cout << "=======================================" << endl;
}

// Fungsi rekursif menghitung total pesanan (menggunakan pointer)
int hitungTotalPesananRekursif(const Akun* akunPengguna, int indeks) {
    if (indeks >= akunPengguna->itemPesanan) {
        return 0;
    }
    return 1 + hitungTotalPesananRekursif(akunPengguna, indeks + 1);
}

// Fungsi untuk mengkonversi string harga ke integer
int konversiHarga(string hargaStr) {
    string angkaStr = "";
    for (char c : hargaStr) {
        if (isdigit(c)) {
            angkaStr += c;
        }
    }
    return angkaStr.empty() ? 0 : stoi(angkaStr);
}

// Fungsi overloading menampilkan pesanan (dereference pointer)
void tampilkanPesanan(const Pesanan* pesanan) {
    cout << setw(20) << pesanan->namaPemesan << setw(15) << pesanan->namaItem << setw(10) << pesanan->ukuranPesanan << "\n";
}

// Fungsi overloading menampilkan pesanan (dereference pointer dengan nomor)
void tampilkanPesanan(const Pesanan* pesanan, int nomor) {
    cout << setw(5) << nomor << setw(20) << pesanan->namaPemesan << setw(15) << pesanan->namaItem << setw(10) << pesanan->ukuranPesanan << "\n";
}

// Prosedur untuk admin melihat semua pesanan
void lihatSemuaPesanan(Akun* daftarAkun, int totalAkun) {
    try {
        // Hitung total semua pesanan
        int totalSemuaPesanan = 0;
        for (int i = 0; i < totalAkun; i++) {
            if (!daftarAkun[i].isAdmin) {
                totalSemuaPesanan += daftarAkun[i].itemPesanan;
            }
        }

        if (totalSemuaPesanan == 0) {
            cout << "\nBelum ada pesanan dari user manapun\n";
            return;
        }

        // Alokasi memori untuk semua pesanan
        Pesanan* semuaPesanan = new Pesanan[totalSemuaPesanan];
        if (!semuaPesanan) {
            throw runtime_error("Gagal mengalokasikan memori untuk pesanan.");
        }

        // Kumpulkan semua pesanan
        int index = 0;
        for (int i = 0; i < totalAkun; i++) {
            if (!daftarAkun[i].isAdmin) {
                for (int j = 0; j < daftarAkun[i].itemPesanan; j++) {
                    semuaPesanan[index++] = daftarAkun[i].daftarPesanan[j];
                }
            }
        }

        int pilihan;
        do {
            cout << "\n========== MENU LIHAT SEMUA PESANAN ==========\n";
            cout << "1. Sorting Pesanan\n";
            cout << "2. Searching Pesanan\n";
            cout << "3. Kembali\n";
            
            pilihan = validasiInputPilihan(1, 3, "Masukkan pilihan [1-3]: ");

            switch (pilihan) {
                case 1:
                    try {
                        MenuSorting(semuaPesanan, totalSemuaPesanan);
                    } catch (const exception& e) {
                        cerr << "\nError saat sorting: " << e.what() << endl;
                    }
                    break;
                case 2:
                    try {
                        menuSearching(semuaPesanan, totalSemuaPesanan);
                    } catch (const exception& e) {
                        cerr << "\nError saat searching: " << e.what() << endl;
                    }
                    break;
                case 3:
                    delete[] semuaPesanan;
                    return;
                default:
                    tampilkanPesanError();
            }
        } while (pilihan != 3);
        delete[] semuaPesanan;
    }
    catch (const bad_alloc& e) {
        cerr << "\nError alokasi memori: " << e.what() << endl;
    } 
    catch (exception& e) {
        cerr << "Terjadi kesalahan: " << e.what() << endl;
    } 
    catch (...) {
        cerr << "Terjadi kesalahan yang tidak diketahui.\n";
    }
}

int validasiInputPilihan(int min, int max, const string& pesan) {
    string input;
    int pilihan;

    while (true) {
        cout << pesan;
        getline(cin, input);

        // Trim spasi depan dan belakang
        input.erase(0, input.find_first_not_of(' '));
        input.erase(input.find_last_not_of(' ') + 1);

        // Cek jika input kosong
        if (input.empty()) {
            cout << "Input tidak boleh kosong atau hanya spasi.\n";
            continue;
        }

        // Cek jika mengandung spasi
        if (input.find(' ') != string::npos) {
            cout << "Input tidak boleh mengandung spasi.\n";
            continue;
        }

        // Cek apakah seluruh input adalah digit
        bool hanyaAngka = true;
        for (char c : input) {
            if (!isdigit(c)) {
                hanyaAngka = false;
                break;
            }
        }

        // Jika input bukan angka
        if (!hanyaAngka) {
            cout << "Input hanya boleh berupa angka tanpa karakter lain.\n";
            continue;
        }

        pilihan = stoi(input);
        if (pilihan < min || pilihan > max) {
            cout << "Pilihan hanya boleh antara " << min << " sampai " << max << ".\n";
            continue;
        }

        return pilihan; // Valid input
    }
}

//Prosedur Ubah Produk
void ubahProduk(Produk* daftarProduk, int jumlahProduk) {
    if (jumlahProduk == 0) {
        cout << "\n=====================================" << endl;
        cout << "==  Belum ada produk untuk diubah  ==" << endl;
        cout << "=====================================" << endl;
        return;
    }
    cout << "\n==   Ubah Produk   ==" << endl;
    cout << "\n===========================================" << endl;
    cout << "|              DAFTAR PRODUK              |" << endl;
    cout << "|=========================================|" << endl;
    cout << "|   No  |   Nama Produk    |     Harga    |" << endl;
    cout << "|=======|==================|==============|" << endl;
    
    for (int i = 0; i < jumlahProduk; i++) {
        cout << "\n|  " << setw(3) << left << i+1 << "  | " 
             << setw(16) << left << daftarProduk[i].nama << " | " 
             << setw(12) << left << daftarProduk[i].harga << " |";
    }
    cout << "\n===========================================" << endl;

    int pilihan;
    while (true) {
        cout << "\nPilih nomor produk yang ingin diubah : ";
        string input;
        getline(cin, input);

        try {
            pilihan = stoi(input);
            if (pilihan < 1 || pilihan > jumlahProduk){
                cout << "Pilihan tidak valid. Harap masukkan nomor yang sesuai.\n";
                continue;
            }
            break;
        } catch (...) {
            cout << "Input harus berupa angka!" << endl;
        }
    }
       
    string namaBaru;
    while (true) {
        cout << "\nMasukkan nama produk baru (tidak boleh kosong) : ";
        getline(cin, namaBaru);

        namaBaru.erase(0, namaBaru.find_first_not_of(" \t"));
        namaBaru.erase(namaBaru.find_last_not_of(" \t") + 1);

        if (namaBaru.empty()) {
            cout << "Nama produk tidak boleh kosong.\n";
            continue;
        }

        bool hanyaspasi = true;
        for (char c : namaBaru) {
            if (!isspace(c)) {
                hanyaspasi = false;
                break;
            }
        }
        if (hanyaspasi) {
            cout << "Nama produk tidak boleh hanya spasi!" << endl;
            continue;
        }

        if (namaBaru.length() > 50) {
            cout << "Nama produk terlalu panjang maksimal 50 karakter" << endl;
            continue;
        }

        bool valid = true;
        for (char c : namaBaru) {
            if (!isalpha(c) && !isspace(c)) {
                valid = false;
                break;
            }
        } 
        if (!valid) {
            cout << "Nama produk hanya boleh mengandung huruf dan spasi di antara kata!" << endl;
            continue;
        }
        
        bool spasiGanda = false;
        for (size_t i =0; i < namaBaru.length() -1; i++) {
            if (isspace(namaBaru[i]) && isspace(namaBaru[i+1])) {
                spasiGanda = true;
                break;
            }
        }

        if (spasiGanda) {
            cout << "Tidak boleh ada spasi ganda di nama produk!" << endl;
            continue;
        }
        break;
    } 

    string hargaBaru;
    while (true) {
        cout << "Masukkan harga produk baru : ";
        getline(cin, hargaBaru);

        hargaBaru.erase(0, hargaBaru.find_first_not_of(" \t"));
        hargaBaru.erase(hargaBaru.find_last_not_of(" \t") + 1);

        if (hargaBaru.empty()) {
            cout << "Harga produk tidak boleh kosong.\n";
            continue;
        }

        bool valid = true;
        for (char c : hargaBaru) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Harga hanya boleh mengandung angka!" << endl;
            continue;
        }

        try {
            long long nilai = stoll(hargaBaru);
            if (nilai <= 0) {
                cout << "Harga harus lebih besar dari 0!.\n";
                continue;    
            } 
            break;
        } catch (...) {
            cout << "Format harga tidak valid!.\n";
        }
    }

    char konfirmasi;
    while (true) {
        cout << "\nAnda akan mengubah produk :" << endl;
        cout << "Nama Lama : "  << daftarProduk[pilihan-1].nama << endl;
        cout << "Nama Baru : " << namaBaru << endl;
        cout << "Harga Lama : " << daftarProduk[pilihan-1].harga << endl;
        cout << "Harga Baru : " << hargaBaru << endl;
        cout << "Apakah Anda yakin? (y/n):";
        string  input;
        getline(cin, input);
        
        if (input.length() !=1) {
            cout << "Masukkan hanya 'y' atau 'n' !" << endl;
            continue;
        }
        konfirmasi = tolower(input[0]);

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            break;
        } else {
            cout << "Input tidak valid. Masukkan 'y' atau 'n'!" << endl;
        }
    }

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        daftarProduk[pilihan - 1].nama = namaBaru;
        daftarProduk[pilihan - 1].harga = hargaBaru;
        cout << "\n==================================" << endl;
        cout << "==    Produk berhasil diubah    ==" << endl;
        cout << "==================================" << endl;
    } else {
        cout << "\nPerubahan dibatalkan." << endl;
    }
}

//Prosedur hapus produk
void hapusProduk(Produk* daftarProduk, int* jumlahProduk) {
    if (*jumlahProduk == 0) {
        cout << "\n====================================" << endl;
        cout << "== Belum ada produk untuk dihapus ==" << endl;
        cout << "====================================" << endl;
        return;
    }
    cout << "\n==   Hapus Produk   ==" << endl;
    cout << "\n===========================================" << endl;
    cout << "|              DAFTAR PRODUK              |" << endl;
    cout << "|=========================================|" << endl;
    cout << "|   No  |   Nama Produk    |     Harga    |" << endl;
    cout << "|=======|==================|==============|" << endl;
    
    for (int i = 0; i < *jumlahProduk; i++) {
        cout << "\n|  " << setw(3) << left << i+1 << "  | " 
             << setw(16) << left << daftarProduk[i].nama << " | " 
             << setw(12) << left << daftarProduk[i].harga << " |";
    }
    cout << "\n===========================================" << endl;
    
    int pilihan;
    while (true) {
        cout << "\nPilih nomor produk yang ingin dihapus : ";
        string input;
        getline(cin, input);

        try {
            pilihan = stoi(input);
            if (pilihan < 1 || pilihan > *jumlahProduk) {
            cout << "Nomor produk tidak valid.\n";
            continue;
            }
            break;
        } catch (...) {
            cout << "Input harus berupa angka!" << endl;
        }
    }
    
    char konfirmasi;
    while (true) {
        cout << "\nAnda akan menghapus produk :" << endl;
        cout << "Nama Lama : "  << daftarProduk[pilihan-1].nama << endl;
        cout << "Harga Lama : " << daftarProduk[pilihan-1].harga << endl;
        cout << "Apakah Anda yakin? (y/n):";
        string input;
        getline(cin, input);
    
        if (input.length() !=1) {
            cout << "Masukkan hanya 'y' atau 'n' !" << endl;
            continue;
        }
        konfirmasi = tolower(input[0]);

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            break;
        } else {
            cout << "Input tidak valid. Masukkan 'y' atau 'n'!" << endl;
        }
    }

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        for (int i = pilihan -1 ; i < *jumlahProduk-1; i++) {
            daftarProduk[i] = daftarProduk[i+1];
        }
        (*jumlahProduk)--;
        cout << "\n==================================" << endl;
        cout << "==    Produk berhasil dihapus   ==" << endl;
        cout << "==================================" << endl;
    } else {
        cout << "\nPenghapusan dibatalkan" << endl;
    }
}

//Prosedur hapus akun users
void hapusAkunUser(Akun* daftarAkun, int* totalAkun) {
    // Tampilkan header
    cout << "\n==   Hapus Akun User   ==" << endl;
    cout << "\n=====================================" << endl;
    cout << "|          DAFTAR AKUN USER         |" << endl;
    cout << "=====================================" << endl;
    cout << "|  No.  |        Username           |" << endl;
    cout << "|=======|===========================|" << endl;
    
    // Tampilkan daftar akun user
    bool adaUser = false;
    for (int i = 0; i < *totalAkun; i++) {
        cout << "\n|  " << setw(3) << left << i+1 << "  | " 
             << setw(25) << left << daftarAkun[i].username << " |";
        adaUser = true;
    }
    cout << "\n=====================================" << endl;
    
    if (!adaUser) {
        cout << "\n====================================" << endl;
        cout << "==  Tidak ada user untuk dihapus  ==" << endl;
        cout << "====================================" << endl;
        return;
    }

    // Input pilihan user
    int pilihan;
    while (true) {
        cout << "\nPilih nomor akun user yang ingin dihapus: ";
        string input;
        getline(cin, input);

        try {
            pilihan = stoi(input);
            if (pilihan < 1 || pilihan > *totalAkun) {
                cout << "Nomor tidak valid. Harap masukkan antara 1-" << *totalAkun << endl;
                continue;
            }
            
            // Cek apakah akun admin
            if (daftarAkun[pilihan-1].isAdmin) {
                cout << "\n=======================================" << endl;
                cout << "==  Tidak bisa menghapus akun admin  ==" << endl;
                cout << "=======================================" << endl;
                continue;
            }
            break;
        } catch (...) {
            cout << "Input harus berupa angka!" << endl;
        }
    }

    // Konfirmasi penghapusan
    char konfirmasi;
    while (true) {
        cout << "\nAnda akan menghapus akun:" << endl;
        cout << "Username: " << daftarAkun[pilihan-1].username << endl;
        cout << "Role: User" << endl;
        cout << "Apakah Anda yakin? (y/n): ";
        
        string input;
        getline(cin, input);
        
        if (input.length() == 1) {
            konfirmasi = tolower(input[0]);
            if (konfirmasi == 'y' || konfirmasi == 'n') {
                break;
            }
        }
        cout << "Masukkan hanya 'y' atau 'n'!" << endl;
    }

    // Eksekusi penghapusan
    if (konfirmasi == 'y') {
        // Geser elemen array
        for (int i = pilihan-1; i < *totalAkun-1; i++) {
            daftarAkun[i] = daftarAkun[i+1];
        }
        (*totalAkun)--;
        
        cout << "\n==================================" << endl;
        cout << "==    Akun berhasil dihapus     ==" << endl;
        cout << "==================================" << endl;
    } else {
        cout << "\nPenghapusan dibatalkan." << endl;
    }
}


// Prosedur menampilkan menu user
void tampilkanMenuUser() {
    cout << "\n================================" << endl;
    cout << "==     MENU UTAMA USER     ==" << endl;
    cout << "==  1. Tambah ke Keranjang    ==" << endl;
    cout << "==  2. Lihat Keranjang        ==" << endl;
    cout << "==  3. Ubah Pesanan           ==" << endl;
    cout << "==  4. Hapus Item             ==" << endl;
    cout << "==  5. Checkout               ==" << endl;
    cout << "==  6. Logout                 ==" << endl;
    cout << "================================" << endl;
}

// Fungsi untuk menampilkan keranjang belanja
void tampilkanKeranjang(const Akun* akunPengguna) {
    if (akunPengguna->itemKeranjang == 0) {
        cout << "\n======================================" << endl;
        cout << "==  Keranjang Anda masih kosong :(  ==" << endl;
        cout << "======================================" << endl;
        return;
    }

    cout << "\n================== Keranjang Belanja ==================\n";
    cout << setw(5) << "No" << setw(20) << "Nama Item" 
         << setw(10) << "Ukuran" << setw(10) << "Jumlah" 
         << setw(15) << "Harga Satuan" << setw(15) << "Subtotal\n";
    
    int totalBelanja = 0;
    for (int i = 0; i < akunPengguna->itemKeranjang; i++) {
        const Pesanan& item = akunPengguna->keranjang[i];
        int hargaSatuan = item.totalHarga / item.jumlah;
        cout << setw(5) << i+1 
             << setw(20) << item.namaItem 
             << setw(10) << item.ukuranPesanan 
             << setw(10) << item.jumlah
             << "   Rp" << setw(13) << hargaSatuan
             << "   Rp" << setw(13) << item.totalHarga << "\n";
        totalBelanja += item.totalHarga;
    }
    
    cout << "\nTotal Belanja: Rp" << totalBelanja << endl;
}

// Fungsi untuk menambah item ke keranjang
void tambahKeKeranjang(Akun* akunPengguna, Produk* daftarProduk, int jumlahProduk) {
    if (akunPengguna->itemKeranjang >= maksimalPesanan) {
        cout << "\n=================================================" << endl;
        cout << "==  Keranjang sudah penuh, tidak bisa menambah ==" << endl;
        cout << "=================================================" << endl;
        return;
    }

    // Tampilkan daftar produk yang tersedia
    tampilkanInformasiMerchandise(daftarProduk, jumlahProduk);

    int pilihanProduk;
    bool produkValid = false;
    int indexProduk = -1;
    
    do {
        cout << "\nMasukkan Nomor Produk yang ingin dipesan (1-" << jumlahProduk << ") atau 0 untuk batal: ";
        string input;
        getline(cin, input);
        
        try {
            pilihanProduk = stoi(input);
            
            if (pilihanProduk == 0) {
                return; // Batal
            } else if (pilihanProduk < 1 || pilihanProduk > jumlahProduk) {
                cout << "Nomor produk tidak valid.\n";
            } else {
                indexProduk = pilihanProduk - 1;
                produkValid = true;
            }
        } catch (...) {
            cout << "Input tidak valid. Masukkan angka.\n";
        }
    } while (!produkValid);

    Produk& produk = daftarProduk[indexProduk];
    int hargaItem = konversiHarga(produk.harga);

    // Input ukuran
    string ukuran;
    bool ukuranValid = false;
    const string ukuranTersedia[] = {"S", "M", "L", "XL"};
    
    do {
        cout << "Masukkan Ukuran [S/M/L/XL]: ";
        getline(cin, ukuran);
        
        // Konversi ke uppercase untuk memudahkan validasi
        for (char &c : ukuran) {
            c = toupper(c);
        }
        
        for (const string& u : ukuranTersedia) {
            if (ukuran == u) {
                ukuranValid = true;
                break;
            }
        }
        
        if (!ukuranValid) {
            cout << "Ukuran tidak valid. Silakan masukkan S, M, L, atau XL.\n";
        }
    } while (!ukuranValid);

    // Input jumlah dan validasi
    int jumlah = 0;
    bool jumlahValid = false;
    
    do {
        cout << "Masukkan Jumlah Pesanan: ";
        string inputJumlah;
        getline(cin, inputJumlah);
        
        try {
            jumlah = stoi(inputJumlah);
            
            if (jumlah <= 0) {
                cout << "Jumlah harus lebih dari 0.\n";
            } else {
                jumlahValid = true;
            }
        } catch (...) {
            cout << "Input tidak valid. Masukkan angka.\n";
        }
    } while (!jumlahValid);

    // Tambahkan ke keranjang
    int indexKeranjang = akunPengguna->itemKeranjang;
    akunPengguna->keranjang[indexKeranjang].namaItem = produk.nama;
    akunPengguna->keranjang[indexKeranjang].ukuranPesanan = ukuran;
    akunPengguna->keranjang[indexKeranjang].jumlah = jumlah;
    akunPengguna->keranjang[indexKeranjang].totalHarga = jumlah * hargaItem;
    akunPengguna->keranjang[indexKeranjang].namaPemesan = akunPengguna->username;
    
    akunPengguna->itemKeranjang++;
    
    cout << "\n==============================================" << endl;
    cout << "==  Item berhasil ditambahkan ke keranjang  ==" << endl;
    cout << "==============================================" << endl;
}

// Fungsi untuk mengubah item dalam keranjang
void ubahItemKeranjang(Akun* akunPengguna, Produk* daftarProduk, int jumlahProduk) {
    if (akunPengguna->itemKeranjang == 0) {
        cout << "\n======================================" << endl;
        cout << "==  Keranjang Anda masih kosong :(  ==" << endl;
        cout << "======================================" << endl;
        return;
    }

    // Tampilkan keranjang terlebih dahulu
    tampilkanKeranjang(akunPengguna);

    int nomorItem;
    bool inputValid = false;
    
    do {
        cout << "\nMasukkan Nomor Item yang ingin diubah (1-" << akunPengguna->itemKeranjang 
             << ") atau 0 untuk batal: ";
        string input;
        getline(cin, input);
        
        try {
            nomorItem = stoi(input);
            
            if (nomorItem == 0) {
                return; // Batal
            } else if (nomorItem < 1 || nomorItem > akunPengguna->itemKeranjang) {
                cout << "Nomor item tidak valid.\n";
            } else {
                inputValid = true;
            }
        } catch (...) {
            cout << "Input tidak valid. Masukkan angka.\n";
        }
    } while (!inputValid);

    // Dapatkan item yang akan diubah
    int indexItem = nomorItem - 1;
    Pesanan& item = akunPengguna->keranjang[indexItem];
    
    // Cari produk terkait untuk mendapatkan harga
    int hargaItem = 0;
    
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].nama == item.namaItem) {
            hargaItem = konversiHarga(daftarProduk[i].harga);
            break;
        }
    }

    // Menu perubahan
    int pilihan;
    do {
        cout << "\nPilih yang ingin diubah:" << endl;
        cout << "1. Ukuran" << endl;
        cout << "2. Jumlah" << endl;
        cout << "3. Kembali" << endl;
        cout << "Pilihan [1-3]: ";
        string inputPilihan;
        getline(cin, inputPilihan);
        
        try {
            pilihan = stoi(inputPilihan);
            
            if (pilihan < 1 || pilihan > 3) {
                cout << "Pilihan tidak valid.\n";
            }
        } catch (...) {
            cout << "Input tidak valid. Masukkan angka.\n";
            continue;
        }

        switch (pilihan) {
            case 1: {
                // Ubah ukuran
                string ukuranBaru;
                bool ukuranValid = false;
                const string ukuranTersedia[] = {"S", "M", "L", "XL"};
                
                do {
                    cout << "Ukuran saat ini: " << item.ukuranPesanan << endl;
                    cout << "Masukkan Ukuran Baru [S/M/L/XL]: ";
                    getline(cin, ukuranBaru);
                    
                    // Konversi ke uppercase
                    for (char &c : ukuranBaru) {
                        c = toupper(c);
                    }
                    
                    for (const string& u : ukuranTersedia) {
                        if (ukuranBaru == u) {
                            ukuranValid = true;
                            break;
                        }
                    }
                    
                    if (!ukuranValid) {
                        cout << "Ukuran tidak valid. Silakan masukkan S, M, L, atau XL.\n";
                    }
                } while (!ukuranValid);
                
                item.ukuranPesanan = ukuranBaru;
                cout << "\nUkuran berhasil diubah.\n";
                break;
            }
            case 2: {
                // Ubah jumlah
                int jumlahBaru;
                bool jumlahValid = false;
                
                do {
                    cout << "Jumlah saat ini: " << item.jumlah << endl;
                    cout << "Masukkan Jumlah Baru: ";
                    string inputJumlah;
                    getline(cin, inputJumlah);
                    
                    try {
                        jumlahBaru = stoi(inputJumlah);
                        
                        if (jumlahBaru < 1) {
                            cout << "Jumlah harus lebih dari 0.\n";
                        } else {
                            jumlahValid = true;
                        }
                    } catch (...) {
                        cout << "Input tidak valid. Masukkan angka.\n";
                    }
                } while (!jumlahValid);
                
                // Update item di keranjang
                item.jumlah = jumlahBaru;
                item.totalHarga = jumlahBaru * hargaItem;
                
                cout << "\nJumlah berhasil diubah.\n";
                break;
            }
            case 3:
                return;
        }
    } while (pilihan != 3);
}

// Fungsi untuk menghapus item dari keranjang
void hapusItemKeranjang(Akun* akunPengguna, Produk* daftarProduk, int jumlahProduk) {
    if (akunPengguna->itemKeranjang == 0) {
        cout << "\n=======================================" << endl;
        cout << "==  Keranjang Anda masih kosong :(  ==" << endl;
        cout << "======================================" << endl;
        return;
    }

    // Tampilkan keranjang terlebih dahulu
    tampilkanKeranjang(akunPengguna);

    int nomorItem;
    bool inputValid = false;
    
    do {
        cout << "\nMasukkan Nomor Item yang ingin dihapus (1-" << akunPengguna->itemKeranjang 
             << ") atau 0 untuk batal: ";
        string input;
        getline(cin, input);
        
        try {
            nomorItem = stoi(input);
            
            if (nomorItem == 0) {
                return; // Batal
            } else if (nomorItem < 1 || nomorItem > akunPengguna->itemKeranjang) {
                cout << "Nomor item tidak valid.\n";
            } else {
                inputValid = true;
            }
        } catch (...) {
            cout << "Input tidak valid. Masukkan angka.\n";
        }
    } while (!inputValid);

    // Geser item-item setelahnya ke depan
    for (int i = nomorItem - 1; i < akunPengguna->itemKeranjang - 1; i++) {
        akunPengguna->keranjang[i] = akunPengguna->keranjang[i+1];
    }
    
    akunPengguna->itemKeranjang--;
    
    cout << "\n============================================" << endl;
    cout << "==  Item berhasil dihapus dari keranjang  ==" << endl;
    cout << "============================================" << endl;
}

// Fungsi untuk checkout (memindahkan dari keranjang ke daftar pesanan)
void checkout(Akun* akunPengguna) {
    if (akunPengguna->itemKeranjang == 0) {
        cout << "\n=======================================" << endl;
        cout << "==  Keranjang Anda masih kosong :(  ==" << endl;
        cout << "======================================" << endl;
        return;
    }

    // Tampilkan ringkasan pesanan
    cout << "\n================== Ringkasan Pesanan ==================\n";
    tampilkanKeranjang(akunPengguna);

    // Konfirmasi
    string konfirmasi;
    do {
        cout << "\nApakah Anda yakin ingin checkout? (ya/tidak): ";
        getline(cin, konfirmasi);
        
        if (konfirmasi != "ya" && konfirmasi != "tidak") {
            cout << "Masukkan 'ya' atau 'tidak'.\n";
        }
    } while (konfirmasi != "ya" && konfirmasi != "tidak");

    if (konfirmasi == "tidak") {
        cout << "\nCheckout dibatalkan.\n";
        return;
    }

    // Pindahkan semua item dari keranjang ke daftar pesanan
    for (int i = 0; i < akunPengguna->itemKeranjang; i++) {
        if (akunPengguna->itemPesanan >= maksimalPesanan) {
            cout << "\n================================================" << endl;
            cout << "==  Kuota pesanan penuh, tidak bisa checkout  ==" << endl;
            cout << "================================================" << endl;
            break;
        }
        
        akunPengguna->daftarPesanan[akunPengguna->itemPesanan] = akunPengguna->keranjang[i];
        akunPengguna->itemPesanan++;
    }

    // Kosongkan keranjang
    akunPengguna->itemKeranjang = 0;
    
    cout << "\n=========================================================" << endl;
    cout << "==  Checkout berhasil! Terima kasih telah berbelanja.  ==" << endl;
    cout << "=========================================================" << endl;
}

// ============
// Fungsi utama
// ============
int main() {
    Akun* daftarAkun = new Akun[maksimalPesanan];
    Produk* daftarProduk = new Produk[maksimalProduk];
    daftarProduk[0] = {"T-Shirt", "150000"};
    daftarProduk[1] = {"Hoodie", "300000"};
    daftarProduk[2] = {"Topi", "80000"};\
    int jumlahProduk = 3;
    int totalAkun = 0; 
    int kesempatanLogin = 0;
    int indeksPenggunaAktif = -1;
    bool isAdmin = false;

    // Membuat akun admin default
    daftarAkun[totalAkun].username = "admin";
    daftarAkun[totalAkun].password = "admin123";
    daftarAkun[totalAkun].isAdmin = true;
    totalAkun++;

    while (true) {
        tampilkanMenuAwal();
        int pilihanAwal = validasiInputPilihan(1, 3, "Masukkan pilihan [1-3]: ");

        if (pilihanAwal == 1) {
            prosesRegistrasi(daftarAkun, &totalAkun); // Menggunakan address-of
        } else if (pilihanAwal == 2) {
            if (prosesLogin(daftarAkun, totalAkun, &indeksPenggunaAktif, &kesempatanLogin, &isAdmin)) { // Menggunakan address-of
                // Menu utama setelah login
                int pilihan;
                while (true) {
                    if (isAdmin) {
                        tampilkanMenuAdmin();
                        pilihan = validasiInputPilihan(1, 7, "Masukkan pilihan [1-7]: ");

                        switch (pilihan) {
                            case 1:
                                tambahProduk(daftarProduk, &jumlahProduk);
                                break;
                            case 2:
                                tampilkanInformasiMerchandise(daftarProduk, jumlahProduk);
                                break;
                            case 3:
                                lihatSemuaPesanan(daftarAkun, totalAkun);
                                break;
                            case 4:
                                ubahProduk(daftarProduk, jumlahProduk);
                                break;
                            case 5:
                                hapusProduk(daftarProduk, &jumlahProduk);
                                break;
                            case 6:
                                hapusAkunUser(daftarAkun, &totalAkun);
                                break;  
                            case 7:
                                tampilkanPesanKeluar();
                                indeksPenggunaAktif = -1;
                                break;
                            default:
                                tampilkanPesanError();
                                break;
                        }
                        if (pilihan == 7) break;
                    } else {
                        tampilkanMenuUser();
                        pilihan = validasiInputPilihan(1, 6, "Masukkan pilihan [1-6]: ");

                        switch (pilihan) {
                            case 1:
                                tambahKeKeranjang(&daftarAkun[indeksPenggunaAktif], daftarProduk, jumlahProduk);
                                break;
                            case 2:
                                tampilkanKeranjang(&daftarAkun[indeksPenggunaAktif]);
                                break;
                            case 3:
                                ubahItemKeranjang(&daftarAkun[indeksPenggunaAktif], daftarProduk, jumlahProduk);
                                break;
                            case 4:
                                hapusItemKeranjang(&daftarAkun[indeksPenggunaAktif], daftarProduk, jumlahProduk);
                                break;
                            case 5:
                                checkout(&daftarAkun[indeksPenggunaAktif]);
                                break;
                            case 6:
                                tampilkanPesanKeluar();
                                indeksPenggunaAktif = -1;
                                break;
                            default:
                                tampilkanPesanError();
                                break;
                        }
                        if (pilihan == 6) break;
                    }
                }
            }
        } else if (pilihanAwal == 3) {
            tampilkanPesanKeluar();
            return 0;
        } else {
            tampilkanPesanError();
        }
    }

    delete[] daftarAkun;
    delete[] daftarProduk;
    return 0;
}