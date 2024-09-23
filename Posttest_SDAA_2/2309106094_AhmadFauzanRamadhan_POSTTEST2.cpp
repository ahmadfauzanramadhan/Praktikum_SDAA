#include <iostream>
#include <cstring>
#ifdef _WIN32
    #include <cstdlib>
#else
    #include <unistd.h>
    #include <term.h>
#endif
using namespace std;

struct Album {
    char judul[100];
    char artis[100];
    int tahunRilis;
    int jumlahLagu;
};

const int MAX_ALBUM = 100;
Album albumList[MAX_ALBUM];
int jumlahAlbum = 0;

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        if (!cur_term) {
            int result;
            setupterm(NULL, STDOUT_FILENO, &result);
            if (result <= 0) return;
        }
        putp(tigetstr("clear"));
    #endif
}

void tambahalbum(Album* listAlbum, int* jumlah) {
    if (*jumlah < MAX_ALBUM) {
        Album albumBaru;
        
        cout << "Masukkan judul album: ";
        cin.ignore();
        cin.getline(albumBaru.judul, 100);
        
        cout << "Masukkan nama artis: ";
        cin.getline(albumBaru.artis, 100);
        
        cout << "Masukkan tahun rilis: ";
        cin >> albumBaru.tahunRilis;
        
        cout << "Masukkan jumlah lagu: ";
        cin >> albumBaru.jumlahLagu;
        
        listAlbum[*jumlah] = albumBaru;
        (*jumlah)++;
        cout << "Album berhasil ditambahkan!\n";
    } else {
        cout << "Database penuh, tidak dapat menambahkan album lagi.\n";
    }
}

void tampilkanalbum(Album* listAlbum, int jumlah) {
    if (jumlah == 0) {
        cout << "Tidak ada album yang tersimpan.\n";
    } else {
        for (int i = 0; i < jumlah; i++) {
            cout << "Album " << i + 1 << ":\n";
            cout << "Judul: " << listAlbum[i].judul << "\n";
            cout << "Artis: " << listAlbum[i].artis << "\n";
            cout << "Tahun Rilis: " << listAlbum[i].tahunRilis << "\n";
            cout << "Jumlah Lagu: " << listAlbum[i].jumlahLagu << "\n";
            cout << "----------------------\n";
        }
    }
}

void ubahalbum(Album* listAlbum, int jumlah) {
    char judul[100];
    cout << "Masukkan judul album yang ingin diubah: ";
    cin.ignore();
    cin.getline(judul, 100);

    bool ditemukan = false;
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(listAlbum[i].judul, judul) == 0) {
            ditemukan = true;
            cout << "Masukkan jumlah lagu baru: ";
            cin >> listAlbum[i].jumlahLagu;
            cout << "Data album berhasil diubah!\n";
            break;
        }
    }

    if (!ditemukan) {
        cout << "Album tidak ditemukan.\n";
    }
}

void hapusalbum(Album* listAlbum, int* jumlah) {
    char judul[100];
    cout << "Masukkan judul album yang ingin dihapus: ";
    cin.ignore();
    cin.getline(judul, 100);

    bool ditemukan = false;
    for (int i = 0; i < *jumlah; i++) {
        if (strcmp(listAlbum[i].judul, judul) == 0) {
            ditemukan = true;
            for (int j = i; j < *jumlah - 1; j++) {
                listAlbum[j] = listAlbum[j + 1];
            }
            (*jumlah)--;
            cout << "Album berhasil dihapus!\n";
            break;
        }
    }

    if (!ditemukan) {
        cout << "Album tidak ditemukan.\n";
    }
}

int main() {
    int pilihan;

    do {
        clear();
        cout << "=== Pendataan Album Hip-Hop ===\n";
        cout << "1. Tambah Album\n";
        cout << "2. Tampilkan Semua Album\n";
        cout << "3. Ubah Data Album\n";
        cout << "4. Hapus Album\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        clear();

        switch (pilihan) {
            case 1:
                tambahalbum(albumList, &jumlahAlbum);
                break;
            case 2:
                tampilkanalbum(albumList, jumlahAlbum);
                break;
            case 3:
                ubahalbum(albumList, jumlahAlbum);
                break;
            case 4:
                hapusalbum(albumList, &jumlahAlbum);
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
        
        if (pilihan != 5) {
            cout << "Tekan Enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();
        }

    } while (pilihan != 5);

    return 0;
}