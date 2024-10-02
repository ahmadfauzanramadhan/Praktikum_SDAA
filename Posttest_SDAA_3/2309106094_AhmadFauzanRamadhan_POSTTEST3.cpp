#include <iostream>
#include <cstring>

using namespace std;

struct Album {
    char judul[100];
    char artis[100];
    int tahunRilis;
    int jumlahLagu;
    Album* next;
};

class AlbumList {
private:
    Album* head;

public:
    AlbumList() : head(nullptr) {}

    void tambahAlbum();
    void tampilkanAlbum();
    void ubahAlbum();
    void hapusAlbum();
    ~AlbumList();
};

void AlbumList::tambahAlbum() {
    Album* albumBaru = new Album;

    cout << "Masukkan judul album: ";
    cin.ignore();
    cin.getline(albumBaru->judul, 100);

    cout << "Masukkan nama artis: ";
    cin.getline(albumBaru->artis, 100);

    cout << "Masukkan tahun rilis: ";
    cin >> albumBaru->tahunRilis;

    cout << "Masukkan jumlah lagu: ";
    cin >> albumBaru->jumlahLagu;

    albumBaru->next = head;
    head = albumBaru;
    cout << "Album berhasil ditambahkan!\n";
}

void AlbumList::tampilkanAlbum() {
    if (!head) {
        cout << "Tidak ada album yang tersimpan.\n";
    } else {
        Album* current = head;
        int index = 1;
        while (current != nullptr) {
            cout << "Album " << index++ << ":\n";
            cout << "Judul: " << current->judul << "\n";
            cout << "Artis: " << current->artis << "\n";
            cout << "Tahun Rilis: " << current->tahunRilis << "\n";
            cout << "Jumlah Lagu: " << current->jumlahLagu << "\n";
            cout << "----------------------\n";
            current = current->next;
        }
    }
}

void AlbumList::ubahAlbum() {
    char judul[100];
    cout << "Masukkan judul album yang ingin diubah: ";
    cin.ignore();
    cin.getline(judul, 100);

    Album* current = head;
    bool ditemukan = false;

    while (current != nullptr) {
        if (strcmp(current->judul, judul) == 0) {
            ditemukan = true;
            cout << "Masukkan jumlah lagu baru: ";
            cin >> current->jumlahLagu;
            cout << "Data album berhasil diubah!\n";
            break;
        }
        current = current->next;
    }

    if (!ditemukan) {
        cout << "Album tidak ditemukan.\n";
    }
}

void AlbumList::hapusAlbum() {
    char judul[100];
    cout << "Masukkan judul album yang ingin dihapus: ";
    cin.ignore();
    cin.getline(judul, 100);

    Album* current = head;
    Album* previous = nullptr;
    bool ditemukan = false;

    while (current != nullptr) {
        if (strcmp(current->judul, judul) == 0) {
            ditemukan = true;
            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
            cout << "Album berhasil dihapus!\n";
            break;
        }
        previous = current;
        current = current->next;
    }

    if (!ditemukan) {
        cout << "Album tidak ditemukan.\n";
    }
}

AlbumList::~AlbumList() {
    Album* current = head;
    while (current != nullptr) {
        Album* next = current->next;
        delete current;
        current = next;
    }
}

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        cout << "\033[2J\033[1;1H";
    #endif
}

int main() {
    AlbumList albumList;
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
                albumList.tambahAlbum();
                break;
            case 2:
                albumList.tampilkanAlbum();
                break;
            case 3:
                albumList.ubahAlbum();
                break;
            case 4:
                albumList.hapusAlbum();
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
