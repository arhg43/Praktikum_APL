#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Akun {
    string nama;
    string nim;
    string peran;
};

struct Produk {
    string nama;
    double harga;
};

vector<Akun> daftar_akun;
vector<Produk> daftar_produk;

void tampilkanMenuUtama();
void tampilkanMenuPelanggan();
void tampilkanMenuAdmin();
void tambahAkun();
string login();
void tambahProduk();
void lihatProduk();
void pesanProduk();
void ubahProduk();
void hapusProduk();

// Fungsi rekursif untuk mencari produk
int cariProdukRekursif(const string& nama_produk, int idx_produk = 0) {
    if (idx_produk >= daftar_produk.size())
        return -1; // Produk tidak ditemukan
    else if (daftar_produk[idx_produk].nama == nama_produk)
        return idx_produk; // Produk ditemukan
    else
        return cariProdukRekursif(nama_produk, idx_produk + 1); // Cari di indeks berikutnya
}

int main() {

    Akun admin;
    admin.nama = "ari";
    admin.nim = "2309106085";
    admin.peran = "admin";
    daftar_akun.push_back(admin);

    while (true) {
        tampilkanMenuUtama();
        int pilihan;
        cout << "Pilih menu (1/2/3): ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                tambahAkun();
                break;
            case 2: {
                string peran = login();
                if (peran == "admin") {
                    while (true) {
                        tampilkanMenuAdmin();
                        int pilihanAdmin;
                        cout << "Pilih menu (1/2/3/4/5): ";
                        cin >> pilihanAdmin;
                        switch (pilihanAdmin) {
                            case 1:
                                tambahProduk();
                                break;
                            case 2:
                                lihatProduk();
                                break;
                            case 3:
                                ubahProduk();
                                break;
                            case 4:
                                hapusProduk();
                                break;
                            case 5:
                                cout << "Keluar dari menu admin." << endl;
                                break;
                            default:
                                cout << "Menu tidak valid. Silakan pilih kembali." << endl;
                        }
                        if (pilihanAdmin == 5) {
                            break;
                        }
                    }
                } else if (peran == "pelanggan") {
                    while (true) {
                        tampilkanMenuPelanggan();
                        int pilihanPelanggan;
                        cout << "Pilih menu (1/2/3): ";
                        cin >> pilihanPelanggan;
                        switch (pilihanPelanggan) {
                            case 1:
                                lihatProduk();
                                break;
                            case 2:
                                pesanProduk();
                                break;
                            case 3:
                                cout << "Keluar dari menu pelanggan." << endl;
                                break;
                            default:
                                cout << "Menu tidak valid. Silakan pilih kembali." << endl;
                        }
                        if (pilihanPelanggan == 3) {
                            break;
                        }
                    }
                } else {
                    cout << "Nama atau Nim salah. Coba lagi." << endl;
                }
                break;
            }
            case 3:
                cout << "Keluar dari program." << endl;
                return 0;
            default:
                cout << "Menu tidak valid. Silakan pilih kembali." << endl;
        }
    }
    return 0;
}

void tampilkanMenuUtama() {
    cout << "\nMenu Utama:" << endl;
    cout << "1. Tambah akun" << endl;
    cout << "2. Login" << endl;
    cout << "3. Keluar" << endl;
}

void tampilkanMenuPelanggan() {
    cout << "\nMenu Pelanggan:" << endl;
    cout << "1. Lihat produk" << endl;
    cout << "2. Pesan produk" << endl;
    cout << "3. Keluar" << endl;
}

void tampilkanMenuAdmin() {
    cout << "\nMenu Admin:" << endl;
    cout << "1. Tambah produk" << endl;
    cout << "2. Lihat produk" << endl;
    cout << "3. Ubah produk" << endl;
    cout << "4. Hapus produk" << endl;
    cout << "5. Keluar" << endl;
}

void tambahAkun() {
    Akun akun;
    cout << "Masukkan Nama: ";
    cin >> akun.nama;
    cout << "Masukkan NIM: ";
    cin >> akun.nim;
    akun.peran = "pelanggan";
    daftar_akun.push_back(akun);
    cout << "Akun berhasil ditambahkan." << endl;
}

string login() {
    string input_nama, input_nim;
    cout << "Masukkan Nama: ";
    cin >> input_nama;
    cout << "Masukkan NIM: ";
    cin >> input_nim;
    for (int i = 0; i < daftar_akun.size(); ++i) {
        if (daftar_akun[i].nama == input_nama && daftar_akun[i].nim == input_nim)
{
            cout << "Login berhasil!" << endl;
            return daftar_akun[i].peran;
        }
    }
    cout << "Nama atau Nim salah. Coba lagi." << endl;
    return ""; // Jika login gagal, mengembalikan string kosong
}

void tambahProduk() {
    Produk produk;
    cout << "Masukkan nama produk: ";
    cin >> produk.nama;
    cout << "Masukkan harga produk: ";
    cin >> produk.harga;
    daftar_produk.push_back(produk);
    cout << "Produk berhasil ditambahkan." << endl;
}

void lihatProduk() {
    cout << "\nDaftar Produk:" << endl;
    if (daftar_produk.empty()) {
        cout << "Belum ada produk." << endl;
    } else {
        for (int i = 0; i < daftar_produk.size(); ++i) {
            cout << i + 1 << ". " << daftar_produk[i].nama << " - Rp " << daftar_produk[i].harga << endl;
        }
    }
}

void pesanProduk() {
    lihatProduk();
    if (daftar_produk.empty()) {
        return;
    }
    int idx_produk;
    cout << "Masukkan nama produk yang ingin dipesan: ";
    string nama_produk;
    cin >> nama_produk;
    idx_produk = cariProdukRekursif(nama_produk);
    if (idx_produk != -1) {
        int jumlah;
        cout << "Masukkan jumlah barang yang ingin dipesan: ";
        cin >> jumlah;
        double total_harga = daftar_produk[idx_produk].harga * jumlah;
        cout << "Total harga pesanan: Rp " << total_harga << endl;
        cout << "Pesanan berhasil!" << endl;
    } else {
        cout << "Produk tidak ditemukan." << endl;
    }
}

void ubahProduk() {
    lihatProduk();
    if (daftar_produk.empty()) {
        return;
    }
    string nama_produk;
    cout << "Masukkan nama produk yang ingin diubah: ";
    cin >> nama_produk;
    int idx_produk = cariProdukRekursif(nama_produk);
    if (idx_produk != -1) {
        cout << "Masukkan harga baru: ";
        cin >> daftar_produk[idx_produk].harga;
        cout << "Produk berhasil diubah." << endl;
    } else {
        cout << "Produk tidak ditemukan." << endl;
    }
}

void hapusProduk() {
    lihatProduk();
    if (daftar_produk.empty()) {
        return;
    }
    int idx_produk;
    cout << "Masukkan nomor produk yang ingin dihapus: ";
    cin >> idx_produk;
    if (idx_produk >= 1 && idx_produk <= daftar_produk.size()) {
        daftar_produk.erase(daftar_produk.begin() + idx_produk - 1);
        cout << "Produk berhasil dihapus." << endl;
    } else {
        cout << "Nomor produk tidak valid." << endl;
    }
    
}