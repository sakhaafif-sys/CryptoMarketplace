#include "crypto.h"

using namespace std;

void initData(ListExchange &LE, ListCoin &LC, ListListing &LL) {
    insertExchange(LE, createNodeExchange("Binance"));
    insertExchange(LE, createNodeExchange("Indodax"));
    insertExchange(LE, createNodeExchange("Coinbase"));
    insertExchange(LE, createNodeExchange("Kraken"));
    insertExchange(LE, createNodeExchange("Bybit"));

    insertCoin(LC, createNodeCoin("BTC", "Bitcoin"));
    insertCoin(LC, createNodeCoin("ETH", "Ethereum"));
    insertCoin(LC, createNodeCoin("BNB", "BinanceCoin"));
    insertCoin(LC, createNodeCoin("SOL", "Solana"));
    insertCoin(LC, createNodeCoin("XRP", "Ripple"));

    adrExchange binance = findExchange(LE, "Binance");
    adrExchange indodax = findExchange(LE, "Indodax");
    adrExchange coinbase = findExchange(LE, "Coinbase");
    adrExchange bybit = findExchange(LE, "Bybit");

    adrCoin btc = findCoin(LC, "BTC");
    adrCoin eth = findCoin(LC, "ETH");
    adrCoin bnb = findCoin(LC, "BNB");
    adrCoin sol = findCoin(LC, "SOL");
    adrCoin xrp = findCoin(LC, "XRP");

    if (binance && btc){
        insertListing(LL, createNodeListing(binance, btc, "BTC/USDT"));
    }
    if (binance && eth){
        insertListing(LL, createNodeListing(binance, eth, "ETH/USDT"));
    }
    if (binance && bnb){
        insertListing(LL, createNodeListing(binance, bnb, "BNB/USDT"));
    }
    if (binance && sol){
        insertListing(LL, createNodeListing(binance, sol, "SOL/USDT"));
    }
    if (indodax && btc){
        insertListing(LL, createNodeListing(indodax, btc, "BTC/IDR"));
    }
    if (indodax && eth){
        insertListing(LL, createNodeListing(indodax, eth, "ETH/IDR"));
    }
    if (indodax && xrp){
        insertListing(LL, createNodeListing(indodax, xrp, "XRP/IDR"));
    }
    if (coinbase && btc){
        insertListing(LL, createNodeListing(coinbase, btc, "BTC/USD"));
    }
    if (coinbase && sol){
        insertListing(LL, createNodeListing(coinbase, sol, "SOL/USD"));
    }
    if (bybit && eth){
        insertListing(LL, createNodeListing(bybit, eth, "ETH/USDT"));
    }
    if (bybit && xrp){
        insertListing(LL, createNodeListing(bybit, xrp, "XRP/USDT"));
    }

}

void pause() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
    cout << endl;
}

void addExchange(ListExchange &LE) {
    string name;
    cout << ">> Masukkan Nama Bursa (Exchange): ";
    cin >> name;
    insertExchange(LE, createNodeExchange(name));
    cout << "[SUKSES] Bursa '" << name << "' berhasil didaftarkan ke sistem." << endl;
}

void addCoin(ListCoin &LC) {
    string code, name;
    cout << ">> Masukkan Simbol Koin (ex: BTC): ";
    cin >> code;
    cout << ">> Masukkan Nama Lengkap Koin (ex: Bitcoin): ";
    cin >> name;
    insertCoin(LC, createNodeCoin(code, name));
    cout << "[SUKSES] Aset '" << name << "' (" << code << ") berhasil didaftarkan." << endl;
}

void addListing(ListExchange LE, ListCoin LC, ListListing &LL) {
    string eName, cCode, pairName;
    cout << ">> Masukkan Nama Bursa Tujuan: ";
    cin >> eName;
    cout << ">> Masukkan Simbol Koin: ";
    cin >> cCode;
    cout << ">> Buat Nama Trading Pair (ex: BTC/USDT): ";
    cin >> pairName;

    adrExchange E = findExchange(LE, eName);
    adrCoin C = findCoin(LC, cCode);

    if (E != NULL && C != NULL) {
        insertListing(LL, createNodeListing(E, C, pairName));
        cout << "[SUKSES] Listing baru '" << pairName << "' berhasil dibuat di " << eName << "." << endl;
    } else {
        cout << "[GAGAL] Bursa atau Koin tidak ditemukan dalam database." << endl;
    }
}

void removeExchange(ListExchange &LE, ListListing &LL) {
    string name;
    cout << ">> Masukkan Nama Bursa yang akan di-delist: ";
    cin >> name;
    deleteExchange(LE, LL, name);
    cout << "[INFO] Proses penghapusan data bursa selesai." << endl;
}

void removeCoin(ListCoin &LC, ListListing &LL) {
    string code;
    cout << ">> Masukkan Simbol Koin yang akan dihapus: ";
    cin >> code;
    deleteCoin(LC, LL, code);
    cout << "[INFO] Proses penghapusan data aset selesai." << endl;
}

void removeListing(ListExchange LE, ListCoin LC, ListListing &LL) {
    string eName, cCode;
    cout << ">> Masukkan Nama Bursa: ";
    cin >> eName;
    cout << ">> Masukkan Simbol Koin yang akan di-delist: ";
    cin >> cCode;

    adrExchange E = findExchange(LE, eName);
    adrCoin C = findCoin(LC, cCode);

    if (E && C) {
        deleteListing(LL, E, C);
        cout << "[SUKSES] Trading pair telah dihapus dari bursa." << endl;
    } else {
        cout << "[GAGAL] Data tidak ditemukan." << endl;
    }
}

void searchExchange(ListExchange LE) {
    string name;
    cout << ">> Cari Nama Bursa: ";
    cin >> name;
    adrExchange E = findExchange(LE, name);
    if (E) cout << "[DITEMUKAN] Bursa terdaftar: " << E->info.name << endl;
    else cout << "[404] Bursa tidak ditemukan." << endl;
}

void searchCoin(ListCoin LC) {
    string code;
    cout << ">> Cari Simbol Koin: ";
    cin >> code;
    adrCoin C = findCoin(LC, code);
    if (C) cout << "[DITEMUKAN] Aset: " << C->info.name << " (" << C->info.code << ")" << endl;
    else cout << "[404] Aset tidak ditemukan." << endl;
}

void checkListingStatus(ListListing LL) {
    string eName, cCode;
    cout << ">> Nama Bursa: ";
    cin >> eName;
    cout << ">> Simbol Koin: ";
    cin >> cCode;
    adrListing L = findListing(LL, eName, cCode);
    if (L) cout << "[AKTIF] Trading Pair tersedia: " << L->pairName << endl;
    else cout << "[TIDAK AKTIF] Koin ini tidak diperdagangkan di bursa tersebut." << endl;
}

void viewAllExchanges(ListExchange LE) {
    cout << "\n--- DAFTAR BURSA TERDAFTAR ---" << endl;
    showAllExchange(LE);
}

void viewAllCoins(ListCoin LC) {
    cout << "\n--- DAFTAR ASET KRIPTO ---" << endl;
    showAllCoin(LC);
}

void viewCoinsInExchange(ListListing LL) {
    string name;
    cout << ">> Masukkan Nama Bursa: ";
    cin >> name;
    showCoinOfExchange(LL, name);
}

void viewExchangesForCoin(ListListing LL) {
    string code;
    cout << ">> Masukkan Simbol Koin: ";
    cin >> code;
    showExchangeOfCoin(LL, code);
}

void reportMarketOverview(ListExchange LE, ListListing LL) {
    cout << "\n--- LAPORAN LISTING PER BURSA ---" << endl;
    showExchangeWithCoin(LE, LL);
}

void reportAssetAvailability(ListCoin LC, ListListing LL) {
    cout << "\n--- LAPORAN KETERSEDIAAN ASET ---" << endl;
    showCoinWithExchange(LC, LL);
}

void statCoinCountInExchange(ListListing LL) {
    string name;
    cout << ">> Masukkan Nama Bursa: ";
    cin >> name;
    cout << "Total Aset diperdagangkan: " << countCoinOfExchange(LL, name) << " koin." << endl;
}

void statExchangeCountForCoin(ListListing LL) {
    string code;
    cout << ">> Masukkan Simbol Koin: ";
    cin >> code;
    cout << "Total Bursa yang melisting: " << countExchangeOfCoin(LL, code) << " bursa." << endl;
}

void statUnlistedCoins(ListCoin LC, ListListing LL) {
    cout << "Jumlah Koin yang belum listing dimanapun: " << countCoinNoExchange(LC, LL) << endl;
}

void statEmptyExchanges(ListExchange LE, ListListing LL) {
    cout << "Jumlah Bursa yang belum memiliki aset: " << countExchangeNoCoin(LE, LL) << endl;
}

void manageListingMigration(ListExchange LE, ListCoin LC, ListListing &LL) {
    int subChoice;
    string eName, cCode, searchE, searchC;
    adrExchange E, newE;
    adrCoin C, newC;

    cout << "\n--- MIGRASI LISTING ---" << endl;
    cout << "1. Pindahkan Satu Koin ke Bursa Lain" << endl;
    cout << "2. Ganti Koin dalam sebuah Listing" << endl;
    cout << ">> Pilih Opsi: ";
    cin >> subChoice;

    if (subChoice == 1) {
        cout << ">> Simbol Koin yang akan dipindah: "; cin >> cCode;
        cout << ">> Nama Bursa ASAL: "; cin >> searchE;
        cout << ">> Nama Bursa TUJUAN: "; cin >> eName;

        C = findCoin(LC, cCode);
        E = findExchange(LE, searchE);
        newE = findExchange(LE, eName);

        if (C && E && newE) {
            editListingExchange(LL, E, newE, C);
            cout << "[SUKSES] Listing berhasil dipindahkan ke bursa baru." << endl;
        } else {
            cout << "[GAGAL] Data bursa atau koin tidak valid." << endl;
        }

    } else if (subChoice == 2) {
        cout << ">> Nama Bursa: "; cin >> eName;
        cout << ">> Simbol Koin LAMA yang akan diganti: "; cin >> searchC;
        cout << ">> Simbol Koin BARU pengganti: "; cin >> cCode;

        E = findExchange(LE, eName);
        C = findCoin(LC, searchC);
        newC = findCoin(LC, cCode);

        if (E && C && newC) {
            editListingCoin(LL, E, C, newC);
            cout << "[SUKSES] Aset dalam listing berhasil diperbarui." << endl;
        } else {
            cout << "[GAGAL] Data bursa atau koin tidak valid." << endl;
        }
    }
}

void showDashboardMenu() {
    cout << endl;
    cout << "===========================================================" << endl;
    cout << "             CRYPTO MARKETPLACE DASHBOARD                  " << endl;
    cout << "===========================================================" << endl;

    cout << " [INPUT DATA]" << endl;
    cout << "  1. Registrasi Exchange Baru" << endl;
    cout << "  2. Registrasi Koin Baru" << endl;
    cout << "  3. Tambah Listing Baru" << endl;

    cout << "\n [HAPUS DATA]" << endl;
    cout << "  4. Hapus Exchange" << endl;
    cout << "  5. Hapus Koin" << endl;
    cout << "  6. Hapus Listing" << endl;

    cout << "\n [PENCARIAN]" << endl;
    cout << "  7. Cari Data Exchange" << endl;
    cout << "  8. Cari Data Koin" << endl;
    cout << "  9. Cek Status Pair" << endl;

    cout << "\n [LAPORAN]" << endl;
    cout << " 10. Lihat Semua Exchange" << endl;
    cout << " 11. Lihat Semua Koin" << endl;
    cout << " 12. Lihat Koin di Exchange Tertentu" << endl;
    cout << " 13. Lihat Exchange Penyedia Koin Tertentu" << endl;
    cout << " 14. Laporan Global (By Exchange)" << endl;
    cout << " 15. Laporan Global (By Coin)" << endl;

    cout << "\n [STATISTIK & EDIT]" << endl;
    cout << " 16. Total Koin di Exchange Tertentu" << endl;
    cout << " 17. Total Market untuk Koin Tertentu" << endl;
    cout << " 18. Cek Koin Unlisted" << endl;
    cout << " 19. Cek Exchange Kosong" << endl;
    cout << " 20. Migrasi Listing (Edit Relasi)" << endl;

    cout << "===========================================================" << endl;
    cout << "  0. KELUAR APLIKASI" << endl;
    cout << "===========================================================" << endl;
}

int main() {
    ListExchange LE;
    ListCoin LC;
    ListListing LL;

    createListExchange(LE);
    createListCoin(LC);
    createListListing(LL);

    initData(LE, LC, LL);

    int choice;

    do {
        showDashboardMenu();
        cout << ">> Pilih Menu: ";
        cin >> choice;
        cout << endl;

        switch(choice) {
            case 1: addExchange(LE); break;
            case 2: addCoin(LC); break;
            case 3: addListing(LE, LC, LL); break;

            case 4: removeExchange(LE, LL); break;
            case 5: removeCoin(LC, LL); break;
            case 6: removeListing(LE, LC, LL); break;

            case 7: searchExchange(LE); break;
            case 8: searchCoin(LC); break;
            case 9: checkListingStatus(LL); break;

            case 10: viewAllExchanges(LE); break;
            case 11: viewAllCoins(LC); break;
            case 12: viewCoinsInExchange(LL); break;
            case 13: viewExchangesForCoin(LL); break;
            case 14: reportMarketOverview(LE, LL); break;
            case 15: reportAssetAvailability(LC, LL); break;

            case 16: statCoinCountInExchange(LL); break;
            case 17: statExchangeCountForCoin(LL); break;
            case 18: statUnlistedCoins(LC, LL); break;
            case 19: statEmptyExchanges(LE, LL); break;
            case 20: manageListingMigration(LE, LC, LL); break;

            case 0: cout << "Terima kasih telah menggunakan aplikasi." << endl; break;
            default: cout << "Pilihan tidak valid." << endl;
        }

        if (choice != 0) pause();

    } while (choice != 0);

    return 0;
}
