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

    
