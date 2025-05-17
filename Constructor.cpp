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


