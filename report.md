Nama: Nazwa Aiana Putri
Nim: 1313623016

# Laporan Analisis Segmentasi Jendela (3x3)

## Objektif

Analisis ini bertujuan mengidentifikasi **Pola Ideal Segmen** dengan menganalisis frekuensi kemunculan *window* $3 \times 3$ non-kosong yang dihasilkan dari gambar input.

---

## Metodologi (Goals 1 & 2)

### 1. Pengumpulan Data (`segmentDetection`)

* Kanvas dipindai menggunakan *sliding window* $3 \times 3$.
* Setiap *window* dikoversi menjadi **Matriks Biner** (`CustomMatrix`).
* Hanya *window* yang **Non-Kosong** (memiliki minimal 1 piksel segmen) yang dikumpulkan.
* Data mentah lengkap (Matriks dan Posisi) didokumentasikan dalam **`dump.txt`**.

### 2. Analisis Pola (`generateReport`)

* Setiap *CustomMatrix* diubah menjadi *string* biner unik (`matrixToString`).
* Frekuensi setiap pola unik dihitung (`pattern_counts`).
* Pola diurutkan untuk mengidentifikasi **pola yang paling sering muncul**, yang merupakan kandidat utama untuk "Pola Ideal Detektor."

---

## Hasil Analisis (Top 5 Pola Non-Kosong)

Berikut adalah 5 pola $3 \times 3$ yang paling sering muncul dari gambar input. Pola dengan frekuensi tertinggi dianggap sebagai kandidat terbaik untuk detektor di Milestone 2.

### Top 5 Pola Paling Sering Muncul:

#### Pola #1 (Frekuensi: [Nilai Frekuensi])
