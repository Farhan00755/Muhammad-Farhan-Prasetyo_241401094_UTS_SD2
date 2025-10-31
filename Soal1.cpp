#include <iostream>
#include <cctype>
using namespace std;

int main () {
    system("cls");
    int jumlahPesanan = 0;
    string* NamaHewan;
    string* MenuPesanan;
    int* StatusVIP;
    
    cout << "=== KAFE IKLC PAWS & TREATS ===" << endl;
    cout << "Masukkan jumlah pesanan: ";
    cin >> jumlahPesanan;
    cin.ignore();
    
    NamaHewan = new string[jumlahPesanan];
    MenuPesanan = new string[jumlahPesanan];
    StatusVIP = new int[jumlahPesanan];

    for(int i = 0; i < jumlahPesanan; i++) {
        cout << "\nPesanan " << (i + 1) << ":" << endl;
        cout << "Nama hewan: ";
        getline(cin, NamaHewan[i]);
        cout << "Menu pesanan: ";
        getline(cin, MenuPesanan[i]);
        bool valid = false;
        while(!valid) {
            cout << "Status VIP (1=biasa, 2=VIP): ";
            cin >> StatusVIP[i];
            if(StatusVIP[i] == 1 || StatusVIP[i] == 2) {
                valid = true;
            } else {
                cout << "\nStatus VIP tidak valid! \n" << endl;
            }
        }
        cin.ignore();
    }

    cout << "\n=== Daftar Pesanan ===" << endl;
    int nomor = 1;
    for(int i = 0; i < jumlahPesanan; i++) {
        if(StatusVIP[i] == 2) {
            for (char &c : NamaHewan[i]) c = toupper(c);
            cout << nomor++ << ". " << NamaHewan[i] << " - " << MenuPesanan[i] << " [VIP]" << endl;
        }
    }
    for(int i = 0; i < jumlahPesanan; i++) {
        if(StatusVIP[i] == 1) {
            for (char &c : NamaHewan[i]) c = toupper(c);
            cout << nomor++ << ". " << NamaHewan[i] << " - " << MenuPesanan[i] << endl;
        }
    }
    
    return 0;
}