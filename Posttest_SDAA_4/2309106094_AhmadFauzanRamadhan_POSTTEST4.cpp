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
protected:
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

class Stack : public AlbumList {
public:
    void push();
    void pop();
};

void Stack::push() {
    tambahAlbum();
}

void Stack::pop() {
    if (!head) {
        cout << "Stack kosong.\n";
    } else {
        Album* temp = head;
        head = head->next;
        cout << "Album " << temp->judul << " berhasil dihapus dari stack.\n";
        delete temp;
    }
}

class Queue : public AlbumList {
private:
    Album* tail;

public:
    Queue() : tail(nullptr) {}

    void enqueue();
    void dequeue();
};

void Queue::enqueue() {
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

    albumBaru->next = nullptr;

    if (head == nullptr) {
        head = tail = albumBaru;
    } else {
        tail->next = albumBaru;
        tail = albumBaru;
    }

    cout << "Album berhasil ditambahkan ke queue!\n";
}

void Queue::dequeue() {
    if (!head) {
        cout << "Queue kosong.\n";
    } else {
        Album* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        cout << "Album " << temp->judul << " berhasil dihapus dari queue.\n";
        delete temp;
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
    Stack stack;
    Queue queue;
    int pilihan;

    do {
        clear();
        cout << "=== Pendataan Album Hip-Hop (Stack & Queue) ===\n";
        cout << "1. Tambah Album (Stack)\n";
        cout << "2. Hapus Album (Stack)\n";
        cout << "3. Tambah Album (Queue)\n";
        cout << "4. Hapus Album (Queue)\n";
        cout << "5. Tampilkan Semua Album\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        clear();

        switch (pilihan) {
            case 1:
                stack.push();
                break;
            case 2:
                stack.pop();
                break;
            case 3:
                queue.enqueue();
                break;
            case 4:
                queue.dequeue();
                break;
            case 5:
                cout << "Album dalam Stack:\n";
                stack.tampilkanAlbum();
                cout << "\nAlbum dalam Queue:\n";
                queue.tampilkanAlbum();
                break;
            case 6:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }

        if (pilihan != 6) {
            cout << "Tekan Enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();
        }

    } while (pilihan != 6);

    return 0;
}
