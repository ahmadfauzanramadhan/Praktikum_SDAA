#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <map>

using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

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

    // Pencarian
    int* toArrayJumlahLagu(int& size);  // Konversi linked list ke array untuk search
    int fibonacciSearch(int x);
    int jumpSearch(int x);
    int boyerMooreSearch(const char* text, const char* pattern);
    void cariJumlahLaguFibonacci();
    void cariJumlahLaguJump();
    void cariJudulAlbumBoyerMoore();

    ~AlbumList();
};

void AlbumList::tambahAlbum() {
    system(CLEAR);
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
    system(CLEAR);
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
    system(CLEAR);
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
    system(CLEAR);
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
    system(CLEAR);
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

// Method untuk merubah linked list ke array (untuk keperluan fibonacci dan jump search)
int* AlbumList::toArrayJumlahLagu(int& size) {
    size = 0;
    Album* temp = head;
    while (temp != nullptr) {
        size++;
        temp = temp->next;
    }

    int* arr = new int[size];
    temp = head;
    for (int i = 0; i < size; i++) {
        arr[i] = temp->jumlahLagu;
        temp = temp->next;
    }

    return arr;
}

// Fibonacci Search pada jumlah lagu
int AlbumList::fibonacciSearch(int x) {
    int size;
    int* arr = toArrayJumlahLagu(size);

    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < size) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;
    while (fibM > 1) {
        int i = std::min(offset + fibMMm2, size - 1);

        if (arr[i] < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (arr[i] > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            delete[] arr;
            return i;
        }
    }

    if (fibMMm1 && arr[offset + 1] == x) {
        delete[] arr;
        return offset + 1;
    }

    delete[] arr;
    return -1;
}

// Jump Search pada jumlah lagu
int AlbumList::jumpSearch(int x) {
    int size;
    int* arr = toArrayJumlahLagu(size);

    int step = sqrt(size);
    int prev = 0;

    while (arr[std::min(step, size) - 1] < x) {
        prev = step;
        step += sqrt(size);
        if (prev >= size) {
            delete[] arr;
            return -1;
        }
    }

    while (arr[prev] < x) {
        prev++;
        if (prev == std::min(step, size)) {
            delete[] arr;
            return -1;
        }
    }

    if (arr[prev] == x) {
        delete[] arr;
        return prev;
    }

    delete[] arr;
    return -1;
}

// Boyer-Moore Search untuk pencarian judul album
int AlbumList::boyerMooreSearch(const char* text, const char* pattern) {
    int m = strlen(pattern);
    int n = strlen(text);

    std::map<char, int> badChar;

    for (int i = 0; i < m; i++) {
        badChar[pattern[i]] = i;
    }

    int shift = 0;

    while (shift <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            return shift;
        } else {
            shift += std::max(1, j - badChar[text[shift + j]]);
        }
    }

    return -1;
}

void AlbumList::cariJumlahLaguFibonacci() {
    system(CLEAR);
    int x;
    cout << "Masukkan jumlah lagu yang ingin dicari: ";
    cin >> x;

    int result = fibonacciSearch(x);
    if (result == -1) {
        cout << "Jumlah lagu tidak ditemukan.\n";
    } else {
        cout << "Jumlah lagu ditemukan pada posisi: " << result + 1 << "\n";
    }
}

void AlbumList::cariJumlahLaguJump() {
    system(CLEAR);
    int x;
    cout << "Masukkan jumlah lagu yang ingin dicari: ";
    cin >> x;

    int result = jumpSearch(x);
    if (result == -1) {
        cout << "Jumlah lagu tidak ditemukan.\n";
    } else {
        cout << "Jumlah lagu ditemukan pada posisi: " << result + 1 << "\n";
    }
}

void AlbumList::cariJudulAlbumBoyerMoore() {
    system(CLEAR);
    char judul[100];
    cout << "Masukkan judul album yang ingin dicari: ";
    cin.ignore();
    cin.getline(judul, 100);

    Album* temp = head;
    bool found = false;

    while (temp != nullptr) {
        if (boyerMooreSearch(temp->judul, judul) != -1) {
            cout << "Album ditemukan: " << temp->judul << "\n";
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Album tidak ditemukan.\n";
    }
}

int main() {
    AlbumList albumList;
    int pilihan;

    do {
        system(CLEAR);
        cout << "Menu:\n";
        cout << "1. Tambah Album\n";
        cout << "2. Tampilkan Album\n";
        cout << "3. Urutkan Album (Merge Sort - Ascending)\n";
        cout << "4. Urutkan Album (Quick Sort - Descending)\n";
        cout << "5. Hapus Album\n";
        cout << "6. Cari Jumlah Lagu (Fibonacci Search)\n";
        cout << "7. Cari Jumlah Lagu (Jump Search)\n";
        cout << "8. Cari Judul Album (Boyer-Moore Search)\n";
        cout << "9. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                albumList.tambahAlbum();
                break;
            case 2:
                albumList.tampilkanAlbum();
                break;
            case 3:
                albumList.mergeSortAscending();
                break;
            case 4:
                albumList.quickSortDescending();
                break;
            case 5:
                albumList.hapusAlbum();
                break;
            case 6:
                albumList.cariJumlahLaguFibonacci();
                break;
            case 7:
                albumList.cariJumlahLaguJump();
                break;
            case 8:
                albumList.cariJudulAlbumBoyerMoore();
                break;
            case 9:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }

        if (pilihan != 9) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }

    } while (pilihan != 9);

    return 0;
}
