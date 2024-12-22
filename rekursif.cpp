#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <fstream>
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
    for (int i = 0; i < MAX_SESI; i++) {
        sesiPraktikum[i].jumlahMahasiswa = 0; // Reset jumlah mahasiswa setelah setiap iterasi
    }
}

// Rekursif: Fungsi untuk mencoba menempatkan mahasiswa pada sesi yang tepat
void jadwalRekursif(Mahasiswa mahasiswaList[], int jumlahMahasiswa, int index) {
    // Basis: Jika sudah memproses semua mahasiswa
    if (index == jumlahMahasiswa) {
        return;
    }

    bool terjadwal[3] = {false, false, false};

    // Coba untuk setiap mata kuliah yang dimiliki mahasiswa
    for (int j = 0; j < 3; j++) {
        if (mahasiswaList[index].mataKuliah[j].empty()) continue;

        // Temukan sesi yang cocok untuk mata kuliah mahasiswa
        for (int k = 0; k < MAX_SESI; k++) {
            if (sesiPraktikum[k].mataKuliah == mahasiswaList[index].mataKuliah[j] && sesiPraktikum[k].jumlahMahasiswa < MAX_CAPACITY && !terjadwal[j]) {
                sesiPraktikum[k].mahasiswa[sesiPraktikum[k].jumlahMahasiswa++] = stoi(mahasiswaList[index].nim);
                terjadwal[j] = true;
                break;
            }
        }
    }

    // Lanjutkan ke mahasiswa berikutnya
    jadwalRekursif(mahasiswaList, jumlahMahasiswa, index + 1);
}

int main() {
    Mahasiswa mahasiswaList[MAX_MAHASISWA];

    // Generate data dummy untuk MAX_MAHASISWA mahasiswa
    for (int i = 0; i < MAX_MAHASISWA; i++) {
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

   jadwalRekursif(mahasiswaList, MAX_MAHASISWA, 0);

    return 0;
}
