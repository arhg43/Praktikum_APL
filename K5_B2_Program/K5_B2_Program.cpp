#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>
#include <cstdlib>

using namespace std;

const int MAX_AKUN = 100;
const int MAX_PRODUK = 100;
const string FILE_PRODUK = "data_produk.csv";

// Struktur data untuk akun pengguna
struct Akun {
    string nama;
    string id;
    string peran;
};

// Struktur data untuk produk
struct Produk {
    string jenis;
    int harga;
    int unit_tersedia;
};

// Array untuk menyimpan daftar akun dan produk
Akun daftar_akun[MAX_AKUN];
Produk daftar_produk[MAX_PRODUK];
int jumlah_akun = 0;
int jumlah_produk = 0;

// Deklarasi fungsi
void tampilkanMenuAwal();
void tampilkanMenuPelanggan();
void tampilkanMenuAdmin();
void tambahAkun(Akun* akun);
string login(const string& input_nama, const string& input_id);
void tambahProduk();
void lihatProduk();
void pesanProduk();
void ubahProduk();
void hapusProduk();
void cariProduk();
void muatProdukDariFile();
void simpanProdukKeFile();

int main() {
    // Menambahkan akun admin awal
    daftar_akun[jumlah_akun++] = {"admin", "admin123", "admin"};

    // Memuat produk dari file CSV
    muatProdukDariFile();

   while (true) {
        system("cls");
        tampilkanMenuAwal();
        int pilihan;
        cout << "Pilih menu (1/2/3): ";
        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 3) {
            cout << "Input tidak valid. Silakan masukkan angka antara 1 dan 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (pilihan) {
            case 1: {
                Akun akun;
                tambahAkun(&akun);
                break;
            }
            case 2: {
                string input_nama, input_id;
                cout << "Masukkan Nama: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, input_nama);
                cout << "Masukkan password: ";
                cin >> input_id;
                string peran = (input_nama, input_id);
                // Tambahkan jeda setelah mencetak pesan login
                cout << "Tekan enter untuk melanjutkan..." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                if (peran == "admin") {
                    while (true) {
                        system("cls");
                        tampilkanMenuAdmin();
                        int pilihanAdmin;
                        cout << "Pilih menu (1/2/3/4/5/6): ";
                        while (!(cin >> pilihanAdmin) || pilihanAdmin < 1 || pilihanAdmin > 6) {
                            cout << "Input tidak valid. Silakan masukkan angka antara 1 dan 6: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        switch (pilihanAdmin) {
                            case 1:
                                system("cls");
                                tambahProduk();
                                cout << "Tekan enter untuk melanjutkan" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            case 2:
                                system("cls");
                                lihatProduk();
                                cout << "Tekan enter untuk melanjutkan" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            case 3:
                                system("cls");
                                ubahProduk();
                                cout << "Tekan enter untuk melanjutkan" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            case 4:
                                system("cls");
                                hapusProduk();
                                cout << "Tekan enter untuk melanjutkan" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            case 5:
                                system("cls");
                                lihatProduk();
                                cariProduk();
                                cout << "Tekan enter untuk melanjutkan" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            case 6:
                                system("cls");
                                cout << "Keluar dari menu admin." << endl;
                                cout << "Tekan enter untuk melanjutkan" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            default:
                                cout << "Menu tidak valid. Silakan pilih kembali." << endl;
                        }
                        if (pilihanAdmin == 6) break;
                    }
                } else if (peran == "pelanggan") {
                    while (true) {
                        system("cls");
                        tampilkanMenuPelanggan();
                        int pilihanPelanggan;
                        cout << "Pilih menu (1/2/3/4): ";
                        while (!(cin >> pilihanPelanggan) || pilihanPelanggan < 1 || pilihanPelanggan > 4) {
                            cout << "Input tidak valid. Silakan masukkan angka antara 1 dan 4: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        switch (pilihanPelanggan) {
                            case 1:
                                system("cls");
                                lihatProduk();
                                cout << "Tekan enter untuk melanjutkan" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            case 2:
                                system("cls");
                                pesanProduk();
                                cout << "Tekan enter untuk melanjutkan" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            case 3:
                                system("cls");
                                lihatProduk();
                                cariProduk();
                                cout << "Tekan enter untuk melanjutkan" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            case 4:
                                system("cls");
                                cout << "Keluar dari menu pelanggan." << endl;
                                cout << "Tekan enter untuk melanjutkan" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            default:
                                cout << "Menu tidak valid. Silakan pilih kembali." << endl;
                                cout << "Tekan enter untuk melanjutkan" << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        if (pilihanPelanggan == 4) break;
                    }
                } else {
                    cout << "Nama atau ID salah. Coba lagi." << endl;
                }
                break;
            }
            case 3:
                cout << "Keluar dari program." << endl;
                simpanProdukKeFile();
                return 0;
            default:
                cout << "Menu tidak valid. Silakan pilih kembali." << endl;
        }
    }
    return 0;
}

// Fungsi untuk menampilkan menu awal
void tampilkanMenuAwal() {
    cout << "\n======<Selamat datang di toko buku >======" << endl;
    cout << "      |    [1] Registrasi               |" << endl;
    cout << "      |    [2] Login                    |" << endl;
    cout << "      |    [3] Keluar                   |" << endl;
    cout << "==========================================" << endl;
}

// Fungsi untuk menampilkan menu pelanggan
void tampilkanMenuPelanggan() {
    cout << "\n============================================" << endl;
    cout << "      |    [1] Lihat daftar buku    |" << endl;
    cout << "      |    [2] Beli buku            |" << endl;
    cout << "      |    [3] Cari buku            |" << endl;
    cout << "      |    [4] Keluar               |" << endl;
    cout << "============================================" << endl;
}

// Fungsi untuk menampilkan menu admin
void tampilkanMenuAdmin() {
    cout << "\n============================================" << endl;
    cout << "      |    [1] Tambah buku baru    |" << endl;
    cout << "      |    [2] Lihat Daftar buku   |" << endl;
    cout << "      |    [3] Ubah Data buku      |" << endl;
    cout << "      |    [4] Hapus buku          |" << endl;
    cout << "      |    [5] Cari buku           |" << endl;
    cout << "      |    [6] Keluar              |" << endl;
    cout << "============================================" << endl;
}

// Fungsi untuk menambah akun baru
void tambahAkun(Akun* akun) {
    cout << "Masukkan Nama: ";
    cin.ignore();
    getline(cin, akun->nama);

    // Cek apakah nama sudah terdaftar
    for (int i = 0; i < jumlah_akun; ++i) {
        if (daftar_akun[i].nama == akun->nama) {
            cout << "Nama tersebut sudah terdaftar. Tambah akun dibatalkan.tekan enter." << endl;
            cout << "Tekan enter untuk melanjutkan" << endl;
            cin.ignore();
            cin.get(); // tunggu user menekan enter
            return;
        }
    }

    // Cek apakah nama tidak kosong
    if (akun->nama.empty()) {
        cout << "Nama harus diisi dan tidak boleh kosong. Tambah akun dibatalkan." << endl;
        cout << "Tekan enter untuk melanjutkan" << endl;
        cin.ignore();
        cin.get(); // tunggu user menekan enter
        return;
    }

    cout << "Masukkan password: ";
    cin >> akun->id;

    akun->peran = "pelanggan";
    daftar_akun[jumlah_akun++] = *akun;

    cout << "Akun berhasil ditambahkan." << endl;
    cout << "Tekan enter untuk melanjutkan" << endl;
    cin.ignore();
    cin.get(); // tunggu user menekan enter
}

// Fungsi login dengan rekursif
string login(const string& input_nama, const string& input_id, int index = 0) {
    if (index >= jumlah_akun) {
        return "";
    } else if (daftar_akun[index].nama == input_nama && daftar_akun[index].id == input_id) {
        cout << "Login berhasil! Halo, " << input_nama << "!" << endl;
        return daftar_akun[index].peran;
    } else {
        return login(input_nama, input_id, index + 1);
    }
}

// Fungsi untuk menambah produk baru
void tambahProduk() {
    if (jumlah_produk >= MAX_PRODUK) {
        cout << "Kapasitas maksimum produk tercapai. Tidak bisa menambah produk baru." << endl;
        return;
    }
    Produk produk;
    cout << "Masukkan nama produk: ";
    cin.ignore();
    getline(cin, produk.jenis);
    if (produk.jenis.empty()) {
        cout << "Jenis produk harus diisi dan tidak boleh kosong. Tambah produk dibatalkan." << endl;
        return;
    }

    cout << "Masukkan harga produk: ";
    while (!(cin >> produk.harga) || produk.harga < 0) {
        cout << "Harga harus angka positif. Masukkan harga produk kembali: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Masukkan unit tersedia: ";
    while (!(cin >> produk.unit_tersedia) || produk.unit_tersedia < 0) {
        cout << "Unit tersedia harus angka positif. Masukkan unit tersedia kembali: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    daftar_produk[jumlah_produk++] = produk;
    simpanProdukKeFile();
    cout << "Produk berhasil ditambahkan." << endl;
}


// Fungsi untuk melakukan Bubble Sort pada daftar produk berdasarkan harga
void bubbleSortProduk() {
    for (int i = 0; i < jumlah_produk - 1; ++i) {
        for (int j = 0; j < jumlah_produk - i - 1; ++j) {
            if (daftar_produk[j].harga > daftar_produk[j + 1].harga) {
                // Tukar posisi produk
                Produk temp = daftar_produk[j];
                daftar_produk[j] = daftar_produk[j + 1];
                daftar_produk[j + 1] = temp;
            }
        }
    }
}

// Fungsi untuk melihat daftar produk
void lihatProduk() {
    bubbleSortProduk(); // Panggil fungsi Bubble Sort
    cout << "\n=============================================================================" << endl;
    cout << "| No.   |       Jenis Buku       |       Harga        |  Unit Tersedia     |" << endl;
    cout << "=============================================================================" << endl;
    if (jumlah_produk == 0) {
        cout << "|                                Belum ada produk                                |" << endl;
    } else {
        for (int i = 0; i < jumlah_produk; ++i) {
            cout << "| " << setw(5) << (i + 1) << " | " 
                 << setw(22) << left << daftar_produk[i].jenis << " | " 
                 << setw(18) << fixed << setprecision(2) << right << daftar_produk[i].harga << " | "
                 << setw(18) << right << daftar_produk[i].unit_tersedia << " |" << endl;
        }
    }
    cout << "=============================================================================" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Fungsi untuk mencari produk berdasarkan nama
void cariProduk() {
    cout << "Masukkan nama produk yang ingin dicari: ";
    string nama;
    cin.ignore();
    getline(cin, nama);

    bool ditemukan = false;
    cout << "\n=============================================================================" << endl;
    cout << "| No.   |       Jenis Buku       |       Harga        |  Unit Tersedia     |" << endl;
    cout << "=============================================================================" << endl;

    for (int i = 0; i < jumlah_produk; ++i) {
        if (daftar_produk[i].jenis.find(nama) != string::npos) {
            cout << "| " << setw(5) << (i + 1) << " | " 
                 << setw(22) << left << daftar_produk[i].jenis << " | " 
                 << setw(18) << fixed << setprecision(2) << right << daftar_produk[i].harga << " | "
                 << setw(18) << right << daftar_produk[i].unit_tersedia << " |" << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "|                          Produk tidak ditemukan                           |" << endl;
    }

    cout << "=============================================================================" << endl;
}

// Fungsi untuk memesan produk
void pesanProduk() {
    lihatProduk();
    if (jumlah_produk == 0) {
        return;
    }
    int idx_produk;
    cout << "Masukkan nomor produk yang ingin dipesan: ";
    if (!(cin >> idx_produk)) {
        cout << "Input harus berupa nomor. Pemesanan produk dibatalkan." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (idx_produk >= 1 && idx_produk <= jumlah_produk) {
        cout << "Masukkan jumlah produk yang ingin dipesan: ";
        int jumlah;
        while (!(cin >> jumlah)) {
            cout << "Jumlah harus berupa angka. Masukkan jumlah produk kembali: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (jumlah <= daftar_produk[idx_produk - 1].unit_tersedia) {
            daftar_produk[idx_produk - 1].unit_tersedia -= jumlah;
            double total_biaya = daftar_produk[idx_produk - 1].harga * jumlah;
            cout << "Pemesanan " << daftar_produk[idx_produk - 1].jenis << " sebanyak " << jumlah << " berhasil!" << endl;
            // Cetak struk
            cout << "\n=================================" << endl;
            cout << "          STRUK BELANJA          " << endl;
            cout << "=================================" << endl;
            cout << "Jenis Buku: " << daftar_produk[idx_produk - 1].jenis << endl;
            cout << "Harga per Unit: Rp " << daftar_produk[idx_produk - 1].harga << endl;
            cout << "Jumlah yang dibeli: " << jumlah << endl;
            cout << "Total Biaya: Rp " << total_biaya << endl;
            cout << "=================================" << endl;
            simpanProdukKeFile();
        } else {
            cout << "Stok tidak mencukupi. Pemesanan dibatalkan." << endl;
        }
    } else {
        cout << "Nomor produk tidak valid." << endl;
    }
}

// Fungsi untuk mengubah data produk
void ubahProduk() {
    int nomorProduk;
    lihatProduk();
    cout << "Masukkan nomor produk yang ingin diubah: ";
    cin >> nomorProduk;
    if (nomorProduk < 1 || nomorProduk > jumlah_produk) {
        cout << "Nomor produk tidak valid. Ubah produk dibatalkan." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    Produk& produk = daftar_produk[nomorProduk - 1];
    cout << "Masukkan harga baru untuk produk " << produk.jenis << ": ";
    while (!(cin >> produk.harga) || produk.harga < 0) {
        cout << "Harga harus angka positif. Masukkan harga produk kembali: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Masukkan jumlah unit baru yang tersedia untuk produk " << produk.jenis << ": ";
    while (!(cin >> produk.unit_tersedia) || produk.unit_tersedia < 0) {
        cout << "Unit tersedia harus angka positif. Masukkan unit tersedia kembali: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Produk berhasil diperbarui." << endl;
}



// Fungsi untuk menghapus produk
void hapusProduk() {
    lihatProduk();
    if (jumlah_produk == 0) {
        return;
    }
    int idx_produk;
    cout << "Masukkan nomor produk yang ingin dihapus: ";
    if (!(cin >> idx_produk)) {
        cout << "Input harus berupa nomor. Penghapusan produk dibatalkan." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (idx_produk >= 1 && idx_produk <= jumlah_produk) {
        for (int i = idx_produk - 1; i < jumlah_produk - 1; ++i) {
            daftar_produk[i] = daftar_produk[i + 1];
        }
        jumlah_produk--;
        cout << "Produk berhasil dihapus." << endl;
        simpanProdukKeFile();
    } else {
        cout << "Nomor produk tidak valid." << endl;
    }
}

// Fungsi untuk memuat data produk dari file CSV
void muatProdukDariFile() {
    ifstream file(FILE_PRODUK);
    if (!file.is_open()) {
        cout << "Gagal membuka file produk." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) continue;
        Produk produk;
        produk.jenis = line.substr(0, pos1);
        produk.harga = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
        produk.unit_tersedia = stoi(line.substr(pos2 + 1));
        daftar_produk[jumlah_produk++] = produk;
    }
    file.close();
}

// Fungsi untuk menyimpan data produk ke file CSV
void simpanProdukKeFile() {
    ofstream file(FILE_PRODUK);
    if (!file.is_open()) {
        cout << "Gagal membuka file produk untuk menulis." << endl;
        return;
    }
    for (int i = 0; i < jumlah_produk; ++i) {
        file << daftar_produk[i].jenis << "," << daftar_produk[i].harga << "," << daftar_produk[i].unit_tersedia << endl;
    }
   file.close();
}