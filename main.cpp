#include <iostream>
#include "kampus.h"
using namespace std;

//TESTING

int main()
{
    kampus K;
    string nama;
    adrDosen pDosen;
    adrMatkul pMatkul;
    adrMengampu pMengampu;

    cout<<"\n"
    "> > > > > > > > > > > > > TUGAS BESAR STRUKTUR DATA < < < < < < < < < < < < <\n"
    "\n"
    "                  =========================================\n"
    "                  =                                       =\n"
    "                  =          > KELOMPOK ROUTER <          =\n"
    "                  =                                       =\n"
    "                  =   > Abdul Wasiul Khair - 1301213278   =\n"
    "                  =   > Brilliant Jordan - 1301214328     =\n"
    "                  =                                       =\n"
    "                  =========================================\n"
    "\n";
    cout<<"\t\t  Masukkan Nama Kampus: ";
    getline(cin, nama);
    cout<<"\n                       TEKAN ENTER UNTUK MELANJUTKAN\n";
    initKampus(K, nama);
    getchar();

    int pilihan;
    pilihan = selectMenu();
    while (1){
        switch(pilihan){
        case 0:
            return 0;
            break;

        case 1:
            menuDosen(K);
            pilihan = selectMenu();
            break;

        case 2:
            menuMatkul(K);
            pilihan = selectMenu();
            break;

        default:
            cout<<"\t\t  Input tidak valid!"<<endl;
            cout<<"\t\t  Tekan Enter.......";
            getchar();
            getchar();
            pilihan = selectMenu();
            break;
        }
    }
}


