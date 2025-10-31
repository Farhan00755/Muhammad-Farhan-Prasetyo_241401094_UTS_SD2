#include <iostream>
using namespace std;

struct Node {
    string nama;
    int harga;
    int jumlah;
    Node *next;
};

Node *head = NULL;
Node *tail = NULL;

void insertFront(string nama, int harga, int jumlah) {
    Node *newNode = new Node{nama, harga, jumlah, NULL};
    if (head == NULL) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

void insertBack(string nama, int harga, int jumlah) {
    Node *newNode = new Node{nama, harga, jumlah, NULL};
    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void insertAfter(string targetNama, string nama, int harga, int jumlah) {
    Node *newNode = new Node{nama, harga, jumlah, NULL};
    Node *p = head;
    while (p != NULL && p->nama != targetNama) {
        p = p->next;
    }
    if (p != NULL) {
        newNode->next = p->next;
        p->next = newNode;
        if (p == tail) {
            tail = newNode;
        }
    }
}

void remove(string nama) {
    Node *p = head;
    Node *q = NULL;
    while (p != NULL && p->nama != nama) {
        q = p;
        p = p->next;
    }
    if (p != NULL) {
        if (q == NULL) {
            head = p->next;
            if (head == NULL) tail = NULL;
        } else {
            q->next = p->next;
            if (p == tail) tail = q;
        }
        delete p;
        cout << "Barang '" << nama << "' berhasil dihapus." << endl;
    } else {
        cout << "Barang '" << nama << "' tidak ditemukan." << endl;
    }
}

void printList() {
    Node *p = head;
    int totalBarang = 0;
    long totalHarga = 0;

    cout << "\n=== KERANJANG BELANJA ===" << endl;
    while (p != NULL) {
        cout << p->nama << " - Rp" << p->harga << " x" << p->jumlah << endl;
        totalBarang++;
        totalHarga += (p->harga) * p->jumlah;
        p = p->next;
    }

    cout << "\nTotal barang: " << totalBarang << endl;
    cout << "Total harga: Rp" << totalHarga << endl;
}

int main() {
    system("cls");
    int jumlahAwal;
    string nama;
    long harga;
    int jumlah;
    int pilihanPos;
    string targetNama;
    char hapus;
    
    cout << "==== KERANJANG BELANJA AJAIB ====" << endl;
    cout << "Masukkan jumlah barang awal: ";
    cin >> jumlahAwal;
    cin.ignore(); // untuk handle newline
    
    for (int i = 0; i < jumlahAwal; i++) {
        cout << "\nBarang " << (i + 1) << ":" << endl;
        cout << "Nama: ";
        getline(cin, nama);
        cout << "Harga: "; cin >> harga;
        cout << "Jumlah: "; cin >> jumlah;
        cin.ignore();
        insertBack(nama, harga, jumlah);
    }
    
    cout << "apakah anda ingin menghapus barang ? (y/n): ";
    cin >> hapus;
    cin.ignore();  // Membersihkan newline
    if (hapus == 'y' || hapus == 'Y') {
        string targetNama;
        cout << "\nNama barang yang ingin dihapus: ";
        getline(cin, targetNama);
        if (!targetNama.empty()) {
            remove(targetNama);
        } else {
            cout << "Nama barang tidak boleh kosong." << endl;
        }
    } 
    cout << "\napakah anda ingin menambah barang lagi? (y/n): ";
    char pilihan;
    cin >> pilihan;
    cin.ignore();  // Membersihkan newline

    while (pilihan == 'y') {
        cout << "\nBarang " << (++jumlahAwal) << ":" << endl;
        cout << "Nama: ";
        getline(cin, nama);
        cout << "Harga: ";
        cin >> harga;
        cout << "Jumlah: ";
        cin >> jumlah;
        cin.ignore();  // Membersihkan newline setelah cin >> jumlah
        cout << "tambah di awal, setelah, atau akhir? (1=awal, 2=setelah, 3=akhir): ";
        cin >> pilihanPos;
        cin.ignore();  // Membersihkan newline
        if (pilihanPos == 1) {
            insertFront(nama, harga, jumlah);
        } else if (pilihanPos == 2) {
            cout << "\nNama barang yang ingin ditambahkan setelah: ";
            getline(cin, targetNama);
            insertAfter(targetNama, nama, harga, jumlah);
        } else if (pilihanPos == 3) {
            insertBack(nama, harga, jumlah);
        }

        cout << "apakah anda ingin menghapus barang ? (y/n): ";
        cin >> hapus;
        cin.ignore();  // Membersihkan newline
        if (hapus == 'y' || hapus == 'Y') {
            string targetNama;
            cout << "\nNama barang yang ingin dihapus: ";
            getline(cin, targetNama);
            if (!targetNama.empty()) {
                remove(targetNama);
            } else {
                cout << "Nama barang tidak boleh kosong." << endl;
            }
        } 
        cout << "\napakah anda ingin menambah barang lagi? (y/n): ";
        cin >> pilihan;
        cin.ignore();  // Membersihkan newline
    }

    cout << "\nList Barang Awal:" << endl;
    printList();

    return 0;
}