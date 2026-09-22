#include <stdio.h>

// Deklarasi Fungsi Sub-masalah
void hitungBiayaLaundry(int X);
void penentuanHariPengambilan(int X);
void pengecekanKeterlambatan(int X);
void pemberianDiskonMember(int X);

int main() {
    long long npm;
    int X;

    printf("===================================================\n");
    printf("     PROGRAM UTAMA LAUNDRY-KU (SISTEM KILOAN)      \n");
    printf("===================================================\n");
    printf("Masukkan NPM Anda (contoh: 2311501234): ");
    scanf("%lld", &npm);

    // Menghitung konstanta X (1 digit terakhir NPM)
    X = npm % 10;
    if (X < 0) X = -X; // Mencegah nilai negatif jika input minus

    printf("\n--> Digit Terakhir NPM (X) = %d\n", X);
    printf("--> Sifat Digit X           = %s\n\n", (X % 2 == 0) ? "GENAP" : "GANJIL");

    int pilihan;
    do {
        printf("---------------------------------------------------\n");
        printf("MENU SUB-MASALAH LAUNDRY-KU:\n");
        printf("1. Perhitungan Biaya Laundry (Berdasarkan Berat)\n");
        printf("2. Penentuan Hari Pengambilan (5 Pelanggan)\n");
        printf("3. Pengecekan Keterlambatan Pengambilan (7 Pelanggan)\n");
        printf("4. Pemberian Diskon Member Bulanan (6 Pelanggan)\n");
        printf("5. Jalankan Semua Modul Berurutan\n");
        printf("0. Keluar\n");
        printf("---------------------------------------------------\n");
        printf("Pilih Sub-masalah (0-5): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: hitungBiayaLaundry(X); break;
            case 2: penentuanHariPengambilan(X); break;
            case 3: pengecekanKeterlambatan(X); break;
            case 4: pemberianDiskonMember(X); break;
            case 5:
                hitungBiayaLaundry(X);
                penentuanHariPengambilan(X);
                pengecekanKeterlambatan(X);
                pemberianDiskonMember(X);
                break;
            case 0: printf("\nProgram selesai. Terima kasih!\n"); break;
            default: printf("Pilihan tidak valid, silakan coba lagi.\n");
        }
    } while (pilihan != 0);

    return 0;
}

// 1. Perhitungan Biaya Laundry Berdasarkan Berat
void hitungBiayaLaundry(int X) {
    float berat;
    double tarif_per_kg, biaya_dasar, biaya_kantong = 0, total_biaya;

    printf("\n=== 1. PERHITUNGAN BIAYA LAUNDRY BERDASARKAN BERAT ===\n");
    printf("Masukkan berat cucian (kg): ");
    scanf("%f", &berat);

    // Menentukan tarif per kg berdasarkan kategori
    if (berat <= 3.0) {
        tarif_per_kg = 7000;
        printf("Kategori: Paket Ringan (Maks 3 kg) -> Rp 7.000 / kg\n");
    } else if (berat <= 6.0) {
        tarif_per_kg = 6500;
        printf("Kategori: Paket Sedang (3.1 - 6 kg) -> Rp 6.500 / kg\n");
    } else {
        tarif_per_kg = 6000;
        printf("Kategori: Paket Berat (> 6 kg) -> Rp 6.000 / kg\n");
    }

    biaya_dasar = berat * tarif_per_kg;

    // Modifikasi NPM (Aturan Kantong)
    if (X % 2 == 0) { // GENAP
        biaya_kantong = 2000;
        printf("Aturan Kantong (X=%d GENAP): Biaya tambahan kantong tebal = Rp 2.000\n", X);
    } else { // GANJIL
        biaya_kantong = 0;
        printf("Aturan Kantong (X=%d GANJIL): Gratis kantong plastik = Rp 0\n", X);
    }

    total_biaya = biaya_dasar + biaya_kantong;

    printf("--> Biaya Dasar   : Rp %.2f\n", biaya_dasar);
    printf("--> Biaya Kantong : Rp %.2f\n", biaya_kantong);
    printf("--> TOTAL BIAYA   : Rp %.2f\n", total_biaya);
}

// 2. Penentuan Hari Pengambilan Laundry (5 Pelanggan)
void penentuanHariPengambilan(int X) {
    printf("\n=== 2. PENENTUAN HARI PENGAMBILAN LAUNDRY (5 PELANGGAN) ===\n");
    int target_bonus = X % 5; // Modifikasi NPM X mod 5

    for (int i = 1; i <= 5; i++) {
        int jenis_layanan, lama_pengerjaan;

        printf("\nPelanggan Ke-%d:\n", i);
        printf("  Pilih Jenis Layanan (1: Reguler [2 hari], 2: Express [1 hari]): ");
        scanf("%d", &jenis_layanan);

        if (jenis_layanan == 2) {
            lama_pengerjaan = 1; // Express
        } else {
            lama_pengerjaan = 2; // Reguler
        }

        // Modifikasi NPM: Jika nomor urut pelanggan (1-5) sama dengan X mod 5
        // Catatan: Jika X % 5 == 0, maka berlaku untuk pelanggan ke-5
        int bonus = 0;
        if ((target_bonus == 0 && i == 5) || (target_bonus != 0 && i == target_bonus)) {
            bonus = 1;
            lama_pengerjaan += 1;
            printf("  [NPM MOD]: Pelanggan ke-%d bertepatan dengan (X mod 5), dapat +1 hari pengecekan kualitas.\n", i);
        }

        printf("  --> Estimasi Lama Pengerjaan: %d hari lagi\n", lama_pengerjaan);
    }
}

// 3. Pengecekan Keterlambatan Pengambilan Laundry (7 Pelanggan)
void pengecekanKeterlambatan(int X) {
    printf("\n=== 3. PENGECEKAN KETERLAMBATAN PENGAMBILAN (7 PELANGGAN) ===\n");

    int batas_toleransi = 3; // Batas normal

    // Modifikasi NPM (Member Senior: X = 0, 6, 7, 8, 9)
    if (X == 0 || X == 6 || X == 7 || X == 8 || X == 9) {
        batas_toleransi = 4;
        printf("Status Sistem: MEMBER SENIOR (Digit X=%d) -> Toleransi diperpanjang jadi 4 hari!\n", X);
    } else {
        printf("Status Sistem: MEMBER REGULER (Digit X=%d) -> Batas toleransi = 3 hari\n", X);
    }

    double total_denda_keseluruhan = 0;

    for (int i = 1; i <= 7; i++) {
        int hari_diambil, keterlambatan;
        double denda_pelanggan = 0;

        printf("\nPelanggan Ke-%d:\n", i);
        printf("  Masukkan jumlah hari sejak cucian selesai hingga diambil: ");
        scanf("%d", &hari_diambil);

        if (hari_diambil > batas_toleransi) {
            keterlambatan = hari_diambil - batas_toleransi;
            denda_pelanggan = keterlambatan * 1000.0; // Rp 1.000 / hari
        } else {
            keterlambatan = 0;
            denda_pelanggan = 0;
        }

        total_denda_keseluruhan += denda_pelanggan;

        printf("  --> Keterlambatan : %d hari\n", keterlambatan);
        printf("  --> Denda         : Rp %.0f\n", denda_pelanggan);
    }

    printf("\n===================================================\n");
    printf("TOTAL DENDA SELURUH PELANGGAN (7 Orang): Rp %.0f\n", total_denda_keseluruhan);
    printf("===================================================\n");
}

// 4. Pemberian Diskon Member Bulanan (6 Pelanggan)
void pemberianDiskonMember(int X) {
    printf("\n=== 4. PEMBERIAN DISKON MEMBER BULANAN (6 PELANGGAN) ===\n");

    double promo_kejutan = 0;
    if (X % 2 == 0) { // GENAP
        promo_kejutan = 3000.0;
        printf("Promo Kejutan (X=%d GENAP): Dapat tambahan ekstra potongan Rp 3.000\n", X);
    } else {
        promo_kejutan = 0.0;
        printf("Promo Kejutan (X=%d GANJIL): Tidak ada ekstra potongan tambahan\n", X);
    }

    for (int i = 1; i <= 6; i++) {
        int kunjungan;
        double total_biaya_awal, diskon_persen = 0, nominal_diskon, biaya_akhir;

        printf("\nPelanggan Ke-%d:\n", i);
        printf("  Masukkan jumlah kunjungan per bulan: ");
        scanf("%d", &kunjungan);
        printf("  Masukkan total biaya laundry awal (Rp): ");
        scanf("%lf", &total_biaya_awal);

        // Menentukan persentase diskon
        if (kunjungan >= 4 && kunjungan <= 6) {
            diskon_persen = 5.0;
        } else if (kunjungan > 6) {
            diskon_persen = 10.0;
        } else {
            diskon_persen = 0.0;
        }

        nominal_diskon = total_biaya_awal * (diskon_persen / 100.0);
        biaya_akhir = total_biaya_awal - nominal_diskon - promo_kejutan;

        if (biaya_akhir < 0) biaya_akhir = 0; // Mengantisipasi nilai minus

        printf("  --> Diskon Bulanan (%0.0f%%) : Rp %.2f\n", diskon_persen, nominal_diskon);
        printf("  --> Ekstra Potongan Promo : Rp %.2f\n", promo_kejutan);
        printf("  --> TOTAL BIAYA AKHIR     : Rp %.2f\n", biaya_akhir);
    }
}
