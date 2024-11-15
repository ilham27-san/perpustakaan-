#include <iostream>
#include <vector>
#include <string>
using namespace std;

// kelas buku atribut dan metode
class Buku {
	protected:
		string judul,pengarang,ISBN;
		int tahunTerbit;
	bool status;
	
public :
	Buku(string judul, string pengarang, int tahun, string ISBN)
	: judul(judul),pengarang(pengarang),tahunTerbit(tahun),ISBN(ISBN),status(true) {}
	
	void infoBuku () const {
	    cout << "Judul: " << judul << endl;
        cout << "Pengarang: " << pengarang << endl;
        cout << "Tahun Terbit: " << tahunTerbit << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Status: " << (status ? "Tersedia" : "Dipinjam") << endl;
	}
	
	bool isAvailable() const { return status; }
    void setstatus(bool s) { status = s; }
    string getISBN() const { return ISBN; }
};

// pewarisan kelas buku ke bukudigital
class bukuDigital : public Buku {
	private :
		string formatFile;
		
public :
	bukuDigital(string judul,string pengarang,int tahun,string ISBN,string format)
	: Buku(judul,pengarang,tahun,ISBN), formatFile(format) {}
	
void infoBuku() const {
	Buku :: infoBuku();
	cout << "Format File" << formatFile << endl;
	}
};

// kelas anggota atribut dan metode
class Anggota {
	string nama,nomorAnggota,alamat;
	vector<Buku*> daftarPinjaman;
	
public :
	Anggota(string nama,string nomorAnggota,string alamat)
	:nama (nama),nomorAnggota (nomorAnggota),alamat (alamat) {}
	
void infoAnggota() const {
    cout << "Nama: " << nama << endl;
        cout << "Nomor Anggota: " << nomorAnggota << endl;
        cout << "Alamat: " << alamat << endl;
        cout << "Buku yang Dipinjam:" << endl;
        for (size_t i = 0; i < daftarPinjaman.size(); ++i) {
            daftarPinjaman[i]->infoBuku();
        }
    }
    
    void pinjamBuku(Buku*buku){daftarPinjaman.push_back(buku);}
    void kembalikanBuku(Buku*buku) {
    	     for (size_t i = 0; i < daftarPinjaman.size(); ++i) {
            if (daftarPinjaman[i] == buku) {
                daftarPinjaman.erase(daftarPinjaman.begin() + i);
                break;
            }
        }
    }

    string getNomorAnggota() const { return nomorAnggota; }

};

//kelas perpustakaan atribut dan metode
class Perpustakaan {
private:
	vector<Buku*>daftarBuku;
	vector<Anggota*>daftarAnggota;
	
public :
	void tambahBuku (Buku*buku){daftarBuku.push_back(buku);}
	void tambahAnggota (Anggota*anggota){daftarAnggota.push_back(anggota);}
	
	void daftarBukuTersedia() const {
        cout << "Daftar Buku Tersedia:" << endl;
        for (size_t i = 0; i < daftarBuku.size(); ++i) {
            if (daftarBuku[i]->isAvailable()) {
                daftarBuku[i]->infoBuku();
                cout << endl;
            }
        }
    }
	
	void pinjamBuku (const string& nomorAnggota, const string& ISBN) {
		Anggota* anggota = cariAnggota(nomorAnggota);
		Buku* buku = cariBuku(ISBN);
		
		if(anggota && buku && buku->isAvailable()){
			anggota->kembalikanBuku(buku);
			buku->setstatus(true);
			cout << "Buku Berhasil Dipinjam"<< endl;
		}else {
				cout <<"Peminjaman Gagal, Cek Kembali"<< endl;
		}
	}
	void kembalikanBuku(const string& nomorAnggota, const string& ISBN) {
        Anggota* anggota = cariAnggota(nomorAnggota);
        Buku* buku = cariBuku(ISBN);

        if (anggota && buku && !buku->isAvailable()) {
            anggota->kembalikanBuku(buku);
            buku->setstatus(true);
            cout << "Buku berhasil dikembalikan!" << endl;
        } else {
            cout << "Pengembalian gagal, cek kembali data!" << endl;
        }
    }
	Anggota* cariAnggota(const string& nomorAnggota) const {
		for (size_t i =0; i < daftarAnggota.size(); ++i){
			if (daftarAnggota[i]->getNomorAnggota() == nomorAnggota)
			return daftarAnggota [i];
		}
		return NULL;
	}
	   Buku* cariBuku(const string& ISBN) const {
        for (size_t i = 0; i < daftarBuku.size(); ++i) {
            if (daftarBuku[i]->getISBN() == ISBN)
                return daftarBuku[i];
        }
        return NULL;
    }
};

//fungsi utama mengakses aplikasi
int main() {
    Perpustakaan perpustakaan;

    // Tambah buku ke perpustakaan
    perpustakaan.tambahBuku(new Buku("Pemrograman C++", "Budi", 2020, "12345"));
    perpustakaan.tambahBuku(new bukuDigital("Algoritma Digital", "Ani", 2019, "67890", "PDF"));

    // Tambah anggota
    perpustakaan.tambahAnggota(new Anggota("Andi", "A001", "Jl. Sudirman No. 10"));

    // Pilihan menu
    int pilihan;
    do {
        cout << "\n=== Aplikasi Manajemen Perpustakaan ===\n";
        cout << "1. Tampilkan Daftar Buku Tersedia\n";
        cout << "2. Tampilkan Informasi Anggota\n";
        cout << "3. Tambah Buku\n";
        cout << "4. Tambah Anggota\n";
        cout << "5. Pinjam Buku\n";
        cout << "6. Kembalikan Buku\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            perpustakaan.daftarBukuTersedia();
            break;
        case 2: {
            string nomorAnggota;
            cout << "Masukkan Nomor Anggota: ";
            cin >> nomorAnggota;
            Anggota* anggota = perpustakaan.cariAnggota(nomorAnggota);
            if (anggota) {
                anggota->infoAnggota();
            } else {
                cout << "Anggota tidak ditemukan!" << endl;
            }
            break;
        }
        case 3: {
            string judul, pengarang, ISBN;
            int tahun;
            cout << "Masukkan Judul Buku: ";
            cin.ignore();
            getline(cin, judul);
            cout << "Masukkan Pengarang: ";
            getline(cin, pengarang);
            cout << "Masukkan Tahun Terbit: ";
            cin >> tahun;
            cout << "Masukkan ISBN: ";
            cin >> ISBN;
            perpustakaan.tambahBuku(new Buku(judul, pengarang, tahun, ISBN));
            cout << "Buku berhasil ditambahkan!" << endl;
            break;
        }
        case 4: {
            string nama, nomorAnggota, alamat;
            cout << "Masukkan Nama: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan Nomor Anggota: ";
            cin >> nomorAnggota;
            cout << "Masukkan Alamat: ";
            cin.ignore();
            getline(cin, alamat);
            perpustakaan.tambahAnggota(new Anggota(nama, nomorAnggota, alamat));
            cout << "Anggota berhasil ditambahkan!" << endl;
            break;
        }
        case 5: {
            string nomorAnggota, ISBN;
            cout << "Masukkan Nomor Anggota: ";
            cin >> nomorAnggota;
            cout << "Masukkan ISBN Buku: ";
            cin >> ISBN;
            perpustakaan.pinjamBuku(nomorAnggota, ISBN);
            break;
        }
        case 6: {
            string nomorAnggota, ISBN;
            cout << "Masukkan Nomor Anggota: ";
            cin >> nomorAnggota;
            cout << "Masukkan ISBN Buku: ";
            cin >> ISBN;
            perpustakaan.kembalikanBuku(nomorAnggota, ISBN);
            break;
        }
        case 0:
            cout << "Terima kasih telah menggunakan aplikasi!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);

    return 0;
}
