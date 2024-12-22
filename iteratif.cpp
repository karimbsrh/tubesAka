#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#define MAX_MAHASISWA 10000
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
    cout << "\nJadwal Praktikum:\n";
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
    int jumlahMahasiswa = MAX_MAHASISWA;

    // Generate data dummy untuk 10.000 mahasiswa
    for (int i = 0; i < jumlahMahasiswa; i++) {
        mahasiswaList[i].nim = to_string(1000 + i);
        int pilihan = rand() % 3;
        if (pilihan == 0) {
            mahasiswaList[i].mataKuliah[0] = "StrukturData";
            mahasiswaList[i].mataKuliah[1] = "AlgoritmaPemrograman";
            mahasiswaList[i].mataKuliah[2] = "";
        } else if (pilihan == 1) {
            mahasiswaList[i].mataKuliah[0] = "SistemOperasi";
            mahasiswaList[i].mataKuliah[1] = "StrukturData";
            mahasiswaList[i].mataKuliah[2] = "";
        } else {
            mahasiswaList[i].mataKuliah[0] = "AlgoritmaPemrograman";
            mahasiswaList[i].mataKuliah[1] = "SistemOperasi";
            mahasiswaList[i].mataKuliah[2] = "StrukturData";
        }
    }

    jadwalIteratif(mahasiswaList, jumlahMahasiswa);

    return 0;
}
