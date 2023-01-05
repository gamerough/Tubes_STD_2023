#ifndef KAMPUS_H_INCLUDED
#define KAMPUS_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define nextDosen(p) p->nextDosen
#define nextMengampu(p) p->nextMengampu
#define nextMatkul(p) p->nextMatkul
#define infoDosen(p) p->infoDosen
#define infoMengampu(p) p->infoMengampu
#define child(p) p->child
#define infoMatkul(p) p->infoMatkul
#define startDosen(K) K.startDosen
#define startMatkul(K) K.startMatkul
#define namaKampus(K) K.namaKampus
#define infoChild(p) infoMatkul(infoMengampu(p))

typedef string infotypeDosen;
typedef string infotypeMatkul;
typedef struct dosen *adrDosen;
typedef struct matkul *adrMatkul;
typedef struct mengampu *adrMengampu;

struct dosen{
    infotypeDosen infoDosen;
    adrMengampu child;
    adrDosen nextDosen;
};

struct mengampu{
    adrMatkul infoMengampu;
    adrMengampu nextMengampu;
};

struct matkul{
    infotypeMatkul infoMatkul;
    adrMatkul nextMatkul;
};

struct kampus{
    string namaKampus;
    adrDosen startDosen;
    adrMatkul startMatkul;
};

void initKampus(kampus &x, string nama); //DONE
adrDosen alokasiDosen(infotypeDosen x); //DONE
adrMatkul alokasiMatkul(infotypeMatkul x); //DONE
adrMengampu alokasiMengampu(kampus K, infotypeMatkul x); //DONE
adrDosen findDosen(kampus K, infotypeDosen cari); //DONE
adrMatkul findMatkul(kampus K, infotypeMatkul cari); //DONE
void addDosen(kampus &K, adrDosen p); //DONE
void addMatkul(kampus &K, adrMatkul p); //DONE
void addMengampu(kampus &K, infotypeDosen dataD, infotypeMatkul dataM); //DONE
void deleteMengampu(kampus &K, infotypeDosen dataD, infotypeMatkul dataM); //DONE
void deleteMatkul(kampus &K, infotypeMatkul dataM); //Done
void deleteDosen(kampus &K, infotypeDosen dataD); //Done
void printMengampu(kampus K, infotypeDosen dataD); //DONE
void printMatkulTerampuh(kampus K, infotypeDosen dataD); //DONE
void printListDosen(kampus K); //DONE
void printListMatkul(kampus K); //DONE
int countDosenMengampu(kampus K, adrDosen p); //DONE
int countMatkulTerampu(kampus K, adrMatkul p); //DONE
int countDosen(kampus K); //DONE
int countMatkul(kampus K); //DONE
void mostDosen(kampus K); //DONE
void leastDosen(kampus K); //DONE
void mostMatkul(kampus K); //DONE
void leastMatkul(kampus K); //DONE
void enterToContinue(); //DONE
int selectMenu(); // Done
int selectMenuDosen(); //DONE
void menuDosen(kampus &K); //DONE
int selectMenuMatkul(); //DONE
void menuMatkul(kampus &K); //DONE

#endif // KAMPUS_H_INCLUDED

//add procedure mostDosen
//add procedure leastDosen
//add procedure mostMatkul
//add procedure leastMatkul
//add function selectMenuMatkul
//add procedure menuMatkul
