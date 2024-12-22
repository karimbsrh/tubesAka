#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#define MAX_MAHASISWA 100
#define MAX_SESI 8
#define MAX_CAPACITY 40
using namespace std;

struct Praktikum {
    string hari;
    string mataKuliah;
    int mahasiswa[MAX_CAPACITY];
    int jumlahMahasiswa;
};

struct Mahasiswa {
    string nim;
    string mataKuliah[3];
};

// Data sesi praktikum
Praktikum sesiPraktikum[MAX_SESI] = {
    {"Senin", "StrukturData", {}, 0},
    {"Rabu", "StrukturData", {}, 0},
    {"Jumat", "StrukturData", {}, 0},
    {"Selasa", "AlgoritmaPemrograman", {}, 0},
    {"Kamis", "AlgoritmaPemrograman", {}, 0},
    {"Senin", "SistemOperasi", {}, 0},
    {"Rabu", "SistemOperasi", {}, 0},
    {"Sabtu", "SistemOperasi", {}, 0}
};

// Fungsi untuk mencetak jadwal
void cetakJadwal(Praktikum sesiPraktikum[], Mahasiswa mahasiswaList[], int jumlahMahasiswa) {
    cout << "Jadwal Praktikum:\n";
    for (int i = 0; i < MAX_SESI; i++) {
        cout << sesiPraktikum[i].mataKuliah << " - " << sesiPraktikum[i].hari << ": ";
        for (int j = 0; j < sesiPraktikum[i].jumlahMahasiswa; j++) {
            cout << sesiPraktikum[i].mahasiswa[j] << " ";
        }
        cout << endl;
    }

    cout << "\nMahasiswa yang tidak mendapatkan jadwal:\n";
    for (int i = 0; i < jumlahMahasiswa; i++) {
        bool mendapatkanJadwal = false;
        for (int j = 0; j < MAX_SESI; j++) {
            for (int k = 0; k < sesiPraktikum[j].jumlahMahasiswa; k++) {
                if (sesiPraktikum[j].mahasiswa[k] == stoi(mahasiswaList[i].nim)) {
                    mendapatkanJadwal = true;
                    break;
                }
            }
            if (mendapatkanJadwal) break;
        }
        if (!mendapatkanJadwal) {
            cout << mahasiswaList[i].nim << " ";
        }
    }
    cout << endl;
}

// Iteratif: Algoritma untuk penjadwalan
void jadwalIteratif(Mahasiswa mahasiswaList[], int jumlahMahasiswa) {
    for (int i = 0; i < jumlahMahasiswa; i++) {
        bool terjadwal[3] = {false, false, false};

        for (int j = 0; j < 3; j++) {
            if (mahasiswaList[i].mataKuliah[j].empty()) continue;
            for (int k = 0; k < MAX_SESI; k++) {
                if (sesiPraktikum[k].mataKuliah == mahasiswaList[i].mataKuliah[j] && sesiPraktikum[k].jumlahMahasiswa < MAX_CAPACITY && !terjadwal[j]) {
                    sesiPraktikum[k].mahasiswa[sesiPraktikum[k].jumlahMahasiswa++] = stoi(mahasiswaList[i].nim);
                    terjadwal[j] = true;
                    break;
                }
            }
        }
    }
    cetakJadwal(sesiPraktikum, mahasiswaList, jumlahMahasiswa);
}

int main() {
    Mahasiswa mahasiswaList[MAX_MAHASISWA];
    int jumlahMahasiswa;

    cout << "Masukkan jumlah mahasiswa: ";
    cin >> jumlahMahasiswa;
    cin.ignore(); // Membersihkan input buffer

    for (int i = 0; i < jumlahMahasiswa; i++) {
        cout << "Masukkan data mahasiswa ke-" << (i + 1) << " (format: NIM MataKuliah1 MataKuliah2 MataKuliah3): ";
        string line;
        getline(cin, line);

        stringstream ss(line);
        ss >> mahasiswaList[i].nim;
        for (int j = 0; j < 3; j++) {
            if (!(ss >> mahasiswaList[i].mataKuliah[j])) {
                mahasiswaList[i].mataKuliah[j] = "";
            }
        }
    }

    cout << "\nPenjadwalan Iteratif:\n";
    jadwalIteratif(mahasiswaList, jumlahMahasiswa);

    return 0;
}
