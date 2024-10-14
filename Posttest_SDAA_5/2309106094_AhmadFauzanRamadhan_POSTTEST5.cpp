#include <iostream>
#include <cstring>
#include <cstdlib>

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
    void mergeSortAscending();
    void quickSortDescending();
    void mergeSort(Album** headRef);
    Album* sortedMerge(Album* a, Album* b);
    void split(Album* source, Album** frontRef, Album** backRef);
    Album* partition(Album* low, Album* high, Album** newLow, Album** newHigh);
    void quickSort(Album** headRef, Album* low, Album* high);
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

void AlbumList::mergeSortAscending() {
    mergeSort(&head);
    cout << "Album diurutkan secara ascending berdasarkan jumlah lagu.\n";
}

void AlbumList::mergeSort(Album** headRef) {
    Album* head = *headRef;
    Album* a;
    Album* b;

    if ((head == nullptr) || (head->next == nullptr)) {
        return;
    }

    split(head, &a, &b);
    mergeSort(&a);
    mergeSort(&b);
    *headRef = sortedMerge(a, b);
}

Album* AlbumList::sortedMerge(Album* a, Album* b) {
    Album* result = nullptr;

    if (a == nullptr) {
        return b;
    } else if (b == nullptr) {
        return a;
    }

    if (a->jumlahLagu <= b->jumlahLagu) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }

    return result;
}

void AlbumList::split(Album* source, Album** frontRef, Album** backRef) {
    Album* fast;
    Album* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}


void AlbumList::quickSortDescending() {
    quickSort(&head, head, nullptr);
    cout << "Album diurutkan secara descending berdasarkan jumlah lagu.\n";
}

void AlbumList::quickSort(Album** headRef, Album* low, Album* high) {
    if (low != high && low != nullptr && low != high->next) {
        Album *newLow, *newHigh;
        Album* pivot = partition(low, high, &newLow, &newHigh);

        quickSort(headRef, newLow, pivot);
        quickSort(headRef, pivot->next, newHigh);
    }
}

Album* AlbumList::partition(Album* low, Album* high, Album** newLow, Album** newHigh) {
    Album* pivot = high;
    Album* prev = nullptr, *cur = low, *tail = pivot;

    while (cur != pivot) {
        if (cur->jumlahLagu > pivot->jumlahLagu) {
            if ((*newLow) == nullptr) *newLow = cur;

            prev = cur;
            cur = cur->next;
        } else {
            if (prev != nullptr) prev->next = cur->next;

            Album* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newLow) == nullptr) *newLow = pivot;

    *newHigh = tail;

    return pivot;
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
        system("clear");
    #endif
}

int main() {
    AlbumList albumList;
    int pilihan;

    do {
        clear();
        cout << "=== Menu Pendataan Album ===\n";
        cout << "1. Tambah Album\n";
        cout << "2. Tampilkan Album\n";
        cout << "3. Urutkan Album (Merge Sort - Ascending)\n";
        cout << "4. Urutkan Album (Quick Sort - Descending)\n";
        cout << "5. Hapus Album\n";
        cout << "6. Keluar\n";
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
                albumList.mergeSortAscending();
                albumList.tampilkanAlbum();
                break;
            case 4:
                albumList.quickSortDescending();
                albumList.tampilkanAlbum();
                break;
            case 5:
                albumList.hapusAlbum();
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
