#include <stdio.h>

// Deklarasi Fungsi Sub-masalah
void hitungBiayaCetak(int X);
void estimasiWaktuCetak(int X);
void pengecekanKeterlambatanPrint(int X);
void diskonPelangganTetap(int X);

int main() {
    long long npm;
    int X;

    printf("===================================================\n");
    printf("    PROGRAM UTAMA PRINT-KU (PRINT & FOTOKOPI)      \n");
    printf("===================================================\n");
    printf("Masukkan NPM Anda (contoh: 2311501234): ");
    scanf("%lld", &npm);

    X = npm % 10;
    if (X < 0) X = -X;

    printf("\n--> Digit Terakhir NPM (X) = %d\n", X);
    printf("--> Sifat Digit X           = %s\n\n", (X % 2 == 0) ? "GENAP" : "GANJIL");

    int pilihan;
    do {
        printf("---------------------------------------------------\n");
        printf("MENU SUB-MASALAH PRINT-KU:\n");
        printf("1. Perhitungan Biaya Cetak (Berdasarkan Halaman)\n");
        printf("2. Estimasi Waktu Selesai (5 Pelanggan)\n");
        printf("3. Pengecekan Keterlambatan Pengambilan (7 Pelanggan)\n");
        printf("4. Pemberian Diskon Pelanggan Tetap (6 Pelanggan)\n");
        printf("5. Jalankan Semua Modul Berurutan\n");
        printf("0. Keluar\n");
        printf("---------------------------------------------------\n");
        printf("Pilih Sub-masalah (0-5): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: hitungBiayaCetak(X); break;
            case 2: estimasiWaktuCetak(X); break;
            case 3: pengecekanKeterlambatanPrint(X); break;
            case 4: diskonPelangganTetap(X); break;
            case 5:
                hitungBiayaCetak(X);
                estimasiWaktuCetak(X);
                pengecekanKeterlambatanPrint(X);
                diskonPelangganTetap(X);
                break;
            case 0: printf("\nProgram selesai. Terima kasih!\n"); break;
            default: printf("Pilihan tidak valid, silakan coba lagi.\n");
        }
    } while (pilihan != 0);

    return 0;
}

// 1. Perhitungan Biaya Cetak Berdasarkan Jumlah Halaman
void hitungBiayaCetak(int X) {
    int halaman;
    double tarif_per_lembar, biaya_dasar, biaya_jilid = 0, total_biaya;

    printf("\n=== 1. PERHITUNGAN BIAYA CETAK BERDASARKAN HALAMAN ===\n");
    printf("Masukkan jumlah halaman dokumen: ");
    scanf("%d", &halaman);

    if (halaman <= 20) {
        tarif_per_lembar = 500;
        printf("Kategori: Sedikit (Maks 20 lembar) -> Rp 500 / lembar\n");
    } else if (halaman <= 50) {
        tarif_per_lembar = 400;
        printf("Kategori: Sedang (21 - 50 lembar) -> Rp 400 / lembar\n");
    } else {
        tarif_per_lembar = 350;
        printf("Kategori: Banyak (> 50 lembar) -> Rp 350 / lembar\n");
    }

    biaya_dasar = halaman * tarif_per_lembar;

    // Modifikasi NPM (Biaya Jilid/Staples Rapi)
    if (X % 2 == 0) { // GENAP
        biaya_jilid = 1500;
        printf("Syarat Sistem (X=%d GENAP): Biaya jilid/staples rapi = Rp 1.500\n", X);
    } else { // GANJIL
        biaya_jilid = 0;
        printf("Syarat Sistem (X=%d GANJIL): Gratis / Tidak di-staples = Rp 0\n", X);
    }

    total_biaya = biaya_dasar + biaya_jilid;

    printf("--> Biaya Cetak Dasar : Rp %.2f\n", biaya_dasar);
    printf("--> Biaya Jilid/Staples: Rp %.2f\n", biaya_jilid);
    printf("--> TOTAL BIAYA       : Rp %.2f\n", total_biaya);
}

// 2. Estimasi Waktu Selesai Cetak Dokumen (5 Pelanggan)
void estimasiWaktuCetak(int X) {
    printf("\n=== 2. ESTIMASI WAKTU SELESAI CETAK (5 PELANGGAN) ===\n");
    int target_maintenance = X % 5;

    for (int i = 1; i <= 5; i++) {
        int jenis_cetak, estimasi_menit;

        printf("\nPelanggan Ke-%d:\n", i);
        printf("  Pilih Jenis Cetakan (1: Draft [10 menit], 2: Final/Rapi [20 menit]): ");
        scanf("%d", &jenis_cetak);

        if (jenis_cetak == 2) {
            estimasi_menit = 20; // Final/Rapi
        } else {
            estimasi_menit = 10; // Draft
        }

        // Modifikasi NPM: tambahan 5 menit jika nomor urut == X mod 5
        if ((target_maintenance == 0 && i == 5) || (target_maintenance != 0 && i == target_maintenance)) {
            estimasi_menit += 5;
            printf("  [NPM MOD]: Pelanggan ke-%d terkena maintenance singkat mesin (+5 menit).\n", i);
        }

        printf("  --> Estimasi Waktu Selesai: %d menit lagi\n", estimasi_menit);
    }
}

// 3. Pengecekan Keterlambatan Pengambilan Dokumen (7 Pelanggan)
void pengecekanKeterlambatanPrint(int X) {
    printf("\n=== 3. PENGECEKAN KETERLAMBATAN PENGAMBILAN DOKUMEN (7 PELANGGAN) ===\n");

    int batas_toleransi = 2; // Normal 2 hari

    // Modifikasi NPM (Pelanggan VIP: X = 0, 6, 7, 8, 9)
    if (X == 0 || X == 6 || X == 7 || X == 8 || X == 9) {
        batas_toleransi = 3; // Denda baru dihitung pada hari ke-4 -> toleransi 3 hari
        printf("Status Sistem: PELANGGAN VIP (Digit X=%d) -> Toleransi diperpanjang hingga 3 hari (Denda mulai hari ke-4)!\n", X);
    } else {
        printf("Status Sistem: REGULER (Digit X=%d) -> Batas toleransi = 2 hari\n", X);
    }

    double total_penitipan_seluruh = 0;

    for (int i = 1; i <= 7; i++) {
        int hari_diambil, keterlambatan;
        double denda = 0;

        printf("\nPelanggan Ke-%d:\n", i);
        printf("  Masukkan jumlah hari sejak dokumen selesai hingga diambil: ");
        scanf("%d", &hari_diambil);

        if (hari_diambil > batas_toleransi) {
            keterlambatan = hari_diambil - batas_toleransi;
            denda = keterlambatan * 2000.0; // Rp 2.000 / hari
        } else {
            keterlambatan = 0;
            denda = 0;
        }

        total_penitipan_seluruh += denda;

        printf("  --> Hari Keterlambatan : %d hari\n", keterlambatan);
        printf("  --> Biaya Penitipan    : Rp %.0f\n", denda);
    }

    printf("\n===================================================\n");
    printf("TOTAL BIAYA PENITIPAN SELURUH PELANGGAN: Rp %.0f\n", total_penitipan_seluruh);
    printf("===================================================\n");
}

// 4. Pemberian Diskon Pelanggan Tetap Bulanan (6 Pelanggan)
void diskonPelangganTetap(int X) {
    printf("\n=== 4. PEMBERIAN DISKON PELANGGAN TETAP (6 PELANGGAN) ===\n");

    double promo_genap = 0;
    if (X % 2 == 0) { // GENAP
        promo_genap = 1000.0;
        printf("Promo Genap (X=%d GENAP): Ekstra potongan Rp 1.000\n", X);
    } else {
        promo_genap = 0.0;
        printf("Promo Genap (X=%d GANJIL): Tidak ada ekstra potongan tambahan\n", X);
    }

    for (int i = 1; i <= 6; i++) {
        int transaksi;
        double total_biaya_awal, diskon_persen = 0, nominal_diskon, biaya_akhir;

        printf("\nPelanggan Ke-%d:\n", i);
        printf("  Masukkan jumlah transaksi per bulan: ");
        scanf("%d", &transaksi);
        printf("  Masukkan total biaya sebelum diskon (Rp): ");
        scanf("%lf", &total_biaya_awal);

        if (transaksi >= 4 && transaksi <= 6) {
            diskon_persen = 5.0;
        } else if (transaksi > 6) {
            diskon_persen = 10.0;
        } else {
            diskon_persen = 0.0;
        }

        nominal_diskon = total_biaya_awal * (diskon_persen / 100.0);
        biaya_akhir = total_biaya_awal - nominal_diskon - promo_genap;

        if (biaya_akhir < 0) biaya_akhir = 0;

        printf("  --> Diskon Persentase (%0.0f%%) : Rp %.2f\n", diskon_persen, nominal_diskon);
        printf("  --> Ekstra Potongan Genap : Rp %.2f\n", promo_genap);
        printf("  --> BIAYA AKHIR           : Rp %.2f\n", biaya_akhir);
    }
}
