
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

// Oyuncu bilgilerini tutan yapi
struct OyuncuDurum {
    int saglik;
    int yemek;
    int su;
    int enerji;
    int gun;
    bool kacis;
};

void durumGoster(const OyuncuDurum& o) {
    // Oyuncunun mevcut durumunu ekrana yazdirir
    cout << "\nGun: " << o.gun << endl;
    cout << "Saglik: " << o.saglik << "  Yemek: " << o.yemek << "  Su: " << o.su << "  Enerji: " << o.enerji << endl;
    cout << "------------------------" << endl;
}

void kesfeCik(OyuncuDurum& o) {
    // Kesfe cikinca rastgele bir olay olur
    int olay = rand() % 5;
    if (olay == 0) {
        cout << "Bir cikis yolu buldun! Magaradan kurtuldun!\n";
        o.kacis = true;
    } else if (olay == 1) {
        cout << "Yarasa surusu saldirdi! Sagligin azaldi.\n";
        o.saglik -= 15;
        o.enerji -= 5;
    } else if (olay == 2) {
        cout << "Biraz mantar buldun, yemek artti.\n";
        o.yemek += 10;
        o.enerji -= 5;
    } else if (olay == 3) {
        cout << "Yer alti golu buldun, su artti.\n";
        o.su += 10;
        o.enerji -= 5;
    } else {
        cout << "Hicbir sey bulamadin, enerji kaybettin.\n";
        o.enerji -= 10;
    }
}

void dinlenFonksiyonu(OyuncuDurum& o) {
    // Dinlenince enerji artar, yemek ve su azalir
    cout << "Dinlendin, enerji kazandin.\n";
    o.enerji += 15;
    o.yemek -= 5;
    o.su -= 5;
}

void yemekBul(OyuncuDurum& o) {
    // Yemek ararken rastgele bir olay olur
    int olay = rand() % 3;
    if (olay == 0) {
        cout << "Yenebilir kokler buldun, yemek artti.\n";
        o.yemek += 15;
        o.enerji -= 5;
    } else if (olay == 1) {
        cout << "Zehirli bir bitki yedin, sagligin azaldi.\n";
        o.saglik -= 10;
        o.enerji -= 5;
    } else {
        cout << "Hicbir sey bulamadin, enerji kaybettin.\n";
        o.enerji -= 10;
    }
}

void suBul(OyuncuDurum& o) {
    // Su ararken rastgele bir olay olur
    int olay = rand() % 3;
    if (olay == 0) {
        cout << "Damlalardan su topladin, su artti.\n";
        o.su += 15;
        o.enerji -= 5;
    } else if (olay == 1) {
        cout << "Kirli su ictin, sagligin azaldi.\n";
        o.saglik -= 10;
        o.enerji -= 5;
    } else {
        cout << "Hicbir sey bulamadin, enerji kaybettin.\n";
        o.enerji -= 10;
    }
}

void yeniBirGun(OyuncuDurum& o) {
    // Yeni gun basinda kaynaklar azalir
    o.gun++;
    o.yemek -= 5;
    o.su -= 5;
    o.enerji -= 5;
    if (o.yemek < 0) {
        cout << "Aci kaldin! Sagligin azalacak.\n";
        o.saglik += o.yemek; // yemek negatifse saglik azalir
        o.yemek = 0;
    }
    if (o.su < 0) {
        cout << "Susuz kaldin! Sagligin azalacak.\n";
        o.saglik += o.su; // su negatifse saglik azalir
        o.su = 0;
    }
    if (o.enerji < 0) {
        cout << "Cok yoruldun! Sagligin azalacak.\n";
        o.saglik += o.enerji; // enerji negatifse saglik azalir
        o.enerji = 0;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Oyuncu baslangic degerleri
    OyuncuDurum oyuncu;
    oyuncu.saglik = 100;
    oyuncu.yemek = 30;
    oyuncu.su = 30;
    oyuncu.enerji = 30;
    oyuncu.gun = 1;
    oyuncu.kacis = false;

    cout << "Bir magarada mahsur kaldin. Hayatta kal ve cikisi bul!\n";

    while (oyuncu.saglik > 0 && !oyuncu.kacis) {
        durumGoster(oyuncu);

        cout << "Ne yapmak istersin?\n";
        cout << "1) Kesfe cik\n";
        cout << "2) Dinlen\n";
        cout << "3) Yemek ara\n";
        cout << "4) Su ara\n";
        cout << "Seciminiz (1-4): ";

        int secim = 0;
        cin >> secim;

        // Kullanici hatali girerse dongu basi
        if (secim < 1 || secim > 4) {
            cout << "Gecersiz secim! Bir daha dene.\n";
            continue;
        }

        // Secime gore fonksiyon cagir
        if (secim == 1) {
            kesfeCik(oyuncu);
        } else if (secim == 2) {
            dinlenFonksiyonu(oyuncu);
        } else if (secim == 3) {
            yemekBul(oyuncu);
        } else if (secim == 4) {
            suBul(oyuncu);
        }

        if (oyuncu.kacis) break;

        yeniBirGun(oyuncu);

        if (oyuncu.saglik <= 0) {
            cout << "Oludun. " << oyuncu.gun << " gun hayatta kalabildin.\n";
            break;
        }
    }

    if (oyuncu.kacis) {
        cout << "Tebrikler! " << oyuncu.gun << ". gunde magaradan kurtuldun!\n";
    }

    cout << "Oyun bitti.\n";
    return 0;
}