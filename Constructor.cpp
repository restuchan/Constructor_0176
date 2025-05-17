#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Peminjam;
class Admin;

class Buku {
private:
    string judul;
    string penulis;
    bool dipinjam;

public:
    Buku(string j, string p) : judul(j), penulis(p), dipinjam(false) {}

    void tampilkanInfo() {
        cout << "Judul: " << judul << ", Penulis: " << penulis;
        cout << ", Status: " << (dipinjam ? "Dipinjam" : "Tersedia") << endl;
    }

    bool isDipinjam() const { return dipinjam; }
    void pinjam() { dipinjam = true; }
    void kembalikan() { dipinjam = false; }

    friend class Petugas;
    friend void lihatStatistik(Admin&, Buku&);
};

class Peminjam {
private:
    string nama;
    int id;
    int totalPinjaman;

public:
    Peminjam(string n, int i) : nama(n), id(i), totalPinjaman(0) {}

    void tampilkanData() {
        cout << "Peminjam: " << nama << " (ID: " << id << "), Total Pinjaman: " << totalPinjaman << endl;
    }

    void pinjamBuku() { totalPinjaman++; }
    void kembaliBuku() { if (totalPinjaman > 0) totalPinjaman--; }

    friend class Petugas;
    friend void lihatStatistik(Admin&, Peminjam&);
};

class Petugas {
private:
    string nama;
    int id;
    string levelAkses;

public:
    Petugas(string n, int i, string l) : nama(n), id(i), levelAkses(l) {}

    void prosesPinjam(Buku& b, Peminjam& p) {
        if (!b.dipinjam) {
            b.pinjam();
            p.pinjamBuku();
            cout << "Buku berhasil dipinjam.\n";
        } else {
            cout << "Buku sedang dipinjam.\n";
        }
    }

    void prosesKembali(Buku& b, Peminjam& p) {
        if (b.dipinjam) {
            b.kembalikan();
            p.kembaliBuku();
            cout << "Buku berhasil dikembalikan.\n";
        } else {
            cout << "Buku sudah tersedia.\n";
        }
    }

    friend class Admin;
};

class Admin {
public:
    void lihatInfoPetugas(const Petugas& ptg) {
        cout << "Petugas: " << ptg.nama << ", Level Akses: " << ptg.levelAkses << endl;
    }

    friend void lihatStatistik(Admin& adm, Buku& b);
    friend void lihatStatistik(Admin& adm, Peminjam& p);
};

void lihatStatistik(Admin& adm, Buku& b) {
    cout << "Statistik Buku: ";
    b.tampilkanInfo();
}

void lihatStatistik(Admin& adm, Peminjam& p) {
    cout << "Statistik Peminjam: ";
    p.tampilkanData();
}

int main() {
    vector<Buku> daftarBuku = {
        Buku("Struktur Data", "Pak Budi"),
        Buku("Algoritma", "Ibu Sari"),
        Buku("Basis Data", "Pak Anto")
    };

    vector<Peminjam> daftarPeminjam = {
        Peminjam("Andi", 101),
        Peminjam("Budi", 102),
        Peminjam("Cici", 103)
    };

    Petugas petugas1("Susi", 1, "Level1");
    Admin admin1;

    int pilihan;
    do {
        cout << "\n===== Sistem Perpustakaan =====\n";
        cout << "1. Pinjam Buku\n";
        cout << "2. Kembalikan Buku\n";
        cout << "3. Lihat Statistik Buku\n";
        cout << "4. Lihat Statistik Peminjam\n";
        cout << "5. Lihat Info Petugas\n";
        cout << "0. Keluar\n";
        cout << "\n===== Sistem Perpustakaan =====\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "Daftar Buku:\n";
            for (int i = 0; i < (int)daftarBuku.size(); i++) {
                cout << i << ". ";
                daftarBuku[i].tampilkanInfo();
            }
            cout << "Pilih nomor buku yang ingin dipinjam: ";
            int idxBuku; cin >> idxBuku;

            cout << "Daftar Peminjam:\n";
            for (int i = 0; i < (int)daftarPeminjam.size(); i++) {
                cout << i << ". ";
                daftarPeminjam[i].tampilkanData();
            }
            cout << "Pilih nomor peminjam: ";
            int idxPeminjam; cin >> idxPeminjam;

            if (idxBuku >= 0 && idxBuku < (int)daftarBuku.size() &&
                idxPeminjam >= 0 && idxPeminjam < (int)daftarPeminjam.size()) {
                petugas1.prosesPinjam(daftarBuku[idxBuku], daftarPeminjam[idxPeminjam]);
            } else {
                cout << "Input tidak valid.\n";
            }

        } 
