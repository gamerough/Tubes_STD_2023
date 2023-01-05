#include "kampus.h"

void initKampus(kampus &x, string nama){
    namaKampus(x) = nama;
    startDosen(x) = NULL;
    startMatkul(x) = NULL;
}

adrDosen alokasiDosen(infotypeDosen x){
    adrDosen p;
    p = new dosen;
    infoDosen(p) = x;
    nextDosen(p) = NULL;
    child(p) = NULL;
    return p;
}

adrMatkul alokasiMatkul(infotypeMatkul x){
    adrMatkul p;
    p = new matkul;
    infoMatkul(p) = x;
    nextMatkul(p) = NULL;
    return p;
}

adrMengampu alokasiMengampu(kampus K, infotypeMatkul x){
    adrMengampu p;
    adrMatkul q;
    q = findMatkul(K, x);
    p = new mengampu;
    infoMengampu(p) = q;
    nextMengampu(p) = NULL;
    return p;
}

adrDosen findDosen(kampus K, infotypeDosen cari){
    adrDosen p = startDosen(K);
    while (p != NULL){
        if (infoDosen(p) == cari){
            return p;
        }
        p = nextDosen(p);
    }
    return NULL;
}

adrMatkul findMatkul(kampus K, infotypeMatkul cari){
    adrMatkul p = startMatkul(K);
    while (p != NULL){
        if (infoMatkul(p) == cari){
            return p;
        }
        p = nextMatkul(p);
    }
    return NULL;
}

void addDosen(kampus &K, adrDosen p){
    if (startDosen(K) == NULL){
        startDosen(K) = p;
    }else{
        nextDosen(p) = startDosen(K);
        startDosen(K) = p;
    }
}

void addMatkul(kampus &K, adrMatkul p){
    if (startMatkul(K) == NULL){
        startMatkul(K) = p;
    }else{
        nextMatkul(p) = startMatkul(K);
        startMatkul(K) = p;
    }
}

void addMengampu(kampus &K, infotypeDosen dataD, infotypeMatkul dataM){
    adrDosen pDosen;
    adrMengampu pMengampu, temp;

    pDosen = findDosen(K, dataD);
    pMengampu = alokasiMengampu(K, dataM);
    temp = child(pDosen);
    if (temp == NULL){
        child(pDosen) = pMengampu;
    }else{
        nextMengampu(pMengampu) = child(pDosen);
        child(pDosen) = pMengampu;
    }
}

void deleteMengampu(kampus &K, infotypeDosen dataD, infotypeMatkul dataM){
    adrDosen pDosen;
    adrMatkul pMatkul;
    pDosen = findDosen(K, dataD);
    pMatkul = findMatkul(K, dataM);
    if (pDosen != NULL && pMatkul != NULL){
        adrMengampu temp;
        temp = child(pDosen);
        while(temp != NULL){
            if(infoChild(temp) == dataM){
                adrMengampu beforeTemp;
                beforeTemp = child(pDosen);
                //proteksi beforetemp jika temp ada pada child pertama
                if (temp != child(pDosen)){
                    while (nextMengampu(beforeTemp) != temp || nextMengampu(beforeTemp) == NULL){
                        beforeTemp = nextMengampu(beforeTemp);
                    }
                }
                if(temp == child(pDosen)){ //delete first
                    child(pDosen) = nextMengampu(temp);
                    nextMengampu(temp) = NULL;
                }else if (nextMengampu(temp) == NULL){ //delete last
                    nextMengampu(beforeTemp) = NULL;
                }else{ //delete after
                    nextMengampu(beforeTemp) = nextMengampu(temp);
                    nextMengampu(temp) = NULL;
                }
            }
            temp = nextMengampu(temp);
        }
    }else{
        cout<<"\n\t\t  Dosen dan Mata Kuliah tersebut tidak terdaftar di Kampus\n";
    }
}

void deleteMatkul(kampus &K, infotypeMatkul dataM){
    adrMatkul delMatkul;
    delMatkul = findMatkul(K, dataM);

    if (delMatkul == NULL){
        cout<<"\n\t\t  Mata Kuliat tersebut tidak terdaftar\n";
    }else{
        adrDosen pDosen = startDosen(K);
        while(pDosen != NULL){
            deleteMengampu(K, infoDosen(pDosen), dataM);
            pDosen = nextDosen(pDosen);
        }
        adrMatkul beforeDel;
        beforeDel = startMatkul(K);
        //proteksi beforeDel jika pMatkul ada pada node pertama
        if (delMatkul != startMatkul(K)){
            while (nextMatkul(beforeDel) != delMatkul || nextMatkul(beforeDel) == NULL){
                beforeDel = nextMatkul(beforeDel);
            }
        }
        if(delMatkul == startMatkul(K)){ //delete first
            startMatkul(K) = nextMatkul(delMatkul);
            nextMatkul(delMatkul) = NULL;
        }else if (nextMatkul(delMatkul) == NULL){ //delete last
            nextMatkul(beforeDel) = NULL;
        }else{ //delete after
            nextMatkul(beforeDel) = nextMatkul(delMatkul);
            nextMatkul(delMatkul) = NULL;
        }
    }
}

void deleteDosen(kampus &K, infotypeDosen dataD){
    adrDosen pDosen;
    adrMengampu pDel;
    pDosen = findDosen(K, dataD);
    //hapus edge pada node dosen
    if (pDosen != NULL){
        pDel = child(pDosen);
        while (child(pDosen) != NULL){
            child(pDosen) = nextMengampu(pDel);
            nextMengampu(pDel) = NULL;
            pDel = child(pDosen);
        }

        //hapus node dosen
        adrDosen beforeDel;
        beforeDel = startDosen(K);
        if (pDosen != startDosen(K)){
            while (nextDosen(beforeDel) != pDosen || nextDosen(beforeDel) == NULL){
                beforeDel = nextDosen(beforeDel);
            }
        }
        if(pDosen == startDosen(K)){ //delete first
            startDosen(K) = nextDosen(pDosen);
            nextDosen(pDosen) = NULL;
        }else if (nextDosen(pDosen) == NULL){ //delete last
            nextDosen(beforeDel) = NULL;
        }else{ //delete after
            nextDosen(beforeDel) = nextDosen(pDosen);
            nextDosen(pDosen) = NULL;
        }
    }else{
        cout<<"\n\t\t  Dosen tersebut tidak terdaftar\n";
    }
}

void printMengampu(kampus K, infotypeDosen dataD){
    adrDosen p;
    adrMengampu q;

    p = findDosen(K, dataD);
    if (p == NULL){
        cout<<"\t\t  Dosen tersebut belum terdaftar di Kampus\n";
    }else{
        q = child(p);
        cout<<"\t\t  "<<infoDosen(p)<<" mengampu mata kuliah:"<<endl;
        while(q != NULL){
            cout<<"\t\t  > "<<infoMatkul(infoMengampu(q))<<endl;
            q = nextMengampu(q);
        }
    }
}

void printListDosen(kampus K){
    if (startDosen(K) != NULL){
        cout<<"\n\t\t  Daftar Dosen pada Kampus "<<namaKampus(K)<<endl;
        adrDosen p = startDosen(K);
        while(p != NULL){
            cout<<"\t\t  > "<<infoDosen(p)<<endl;
            p = nextDosen(p);
        }
    }else{
        cout<<"\n\t\t  Belum ada Dosen\n";
    }
}

void printListMatkul(kampus K){
    cout<<"\t\t  Daftar Mata Kuliah pada Kampus "<<namaKampus(K)<<endl;
    adrMatkul q = startMatkul(K);
    while(q != NULL){
        cout<<"\n\t\t  > "<<infoMatkul(q);
        q = nextMatkul(q);
    }
}

void printMatkulTerampuh(kampus K, infotypeMatkul dataM){
    adrMatkul cekMatkul;
    cekMatkul = findMatkul(K, dataM);
    if (cekMatkul != NULL){
        adrDosen pDosen;
        pDosen = startDosen(K);
        cout<<dataM<<" diampu oleh:\n";
        while(pDosen != NULL){
            adrMengampu pMengampu;
            pMengampu = child(pDosen);
            while (pMengampu!=NULL){
                if (infoChild(pMengampu) == dataM){
                    cout<<"> "<<infoDosen(pDosen)<<endl;
                }
                pMengampu = nextMengampu(pMengampu);
            }
            pDosen = nextDosen(pDosen);
        }
    }else{
        cout<<"\n\t\t Mata kuliah tersebut tidak terdaftar";
    }
}

int countDosenMengampu(kampus K, adrDosen p){
    int count = 0;
    adrMengampu q = child(p);
    while(q != NULL){
        count++;
        q = nextMengampu(q);
    }
    return count;
}

int countMatkulTerampu(kampus K, adrMatkul p){
    int count = 0;
    adrDosen pDosen = startDosen(K);
    while (pDosen != NULL){
        adrMengampu q = child(pDosen);
        while (q != NULL){
            if (infoMengampu(q) == p){
                count++;
            }
            q = nextMengampu(q);
        }
        pDosen = nextDosen(pDosen);
    }
    return count;
}

int countDosen(kampus K){
    int count = 0;
    adrDosen p = startDosen(K);
    while(p != NULL){
        count++;
        p = nextDosen(p);
    }
    return count;
}

int countMatkul(kampus K){
    int count = 0;
    adrMatkul p = startMatkul(K);
    while(p != NULL){
        count++;
        p = nextMatkul(p);
    }
    return count;
}

void mostDosen(kampus K){
    adrDosen pDosen, tempD;
    if (startDosen(K) == NULL){
        cout<<"\n\t\t  Belum ada dosen yang terdaftar";
    }else if (nextDosen(startDosen(K)) == NULL){
        cout<<"\n\t\t  Dosen yang mengampu mata kuliah terbanyak : "<<infoDosen(startDosen(K));
    }else{
        tempD = startDosen(K);
        pDosen = nextDosen(tempD);
        while (pDosen != NULL){
            if (countDosenMengampu(K, pDosen) > countDosenMengampu(K, tempD)){
                tempD = pDosen;
            }
            pDosen = nextDosen(pDosen);
        }
        cout<<"\n\t\t  Dosen yang mengampu mata kuliah terbanyak : "<<infoDosen(tempD);
    }
}

void leastDosen(kampus K){
    adrDosen pDosen, tempD;
    if (startDosen(K) == NULL){
        cout<<"\n\t\t  Belum ada dosen yang terdaftar";
    }else if (nextDosen(startDosen(K)) == NULL){
        cout<<"\n\t\t  Dosen yang mengampu mata kuliah tersedikit : "<<infoDosen(startDosen(K));
    }else{
        tempD = startDosen(K);
        pDosen = nextDosen(tempD);
        while (pDosen != NULL){
            if (countDosenMengampu(K, pDosen) < countDosenMengampu(K, tempD)){
                tempD = pDosen;
            }
            pDosen = nextDosen(pDosen);
        }
        cout<<"\n\t\t  Dosen yang mengampu mata kuliah tersedikit : "<<infoDosen(tempD);
    }
}

void mostMatkul(kampus K){
    adrMatkul pMatkul, tempM;
    adrDosen pDosen;
    adrMengampu pMengampu;
    int intMost, intTemp;
    if (startMatkul(K) == NULL){
        cout<<"\n\t\t  Belum ada mata kuliah yang terdaftar";
    }else if (nextMatkul(startMatkul(K)) == NULL){
        cout<<"\n\t\t  Mata kuliah yang diampu dosen terbanyak : "<<infoMatkul(startMatkul(K));
    }else{
        tempM = startMatkul(K);
        pDosen = startDosen(K);
        while(pDosen != NULL){
            pMengampu = child(pDosen);
            while(pMengampu != NULL){
                if (infoChild(pMengampu) == infoMatkul(tempM)){
                    intMost++;
                }
                pMengampu = nextMengampu(pMengampu);
            }
            pDosen = nextDosen(pDosen);
        }
        pMatkul = nextMatkul(tempM);
        while (pMatkul != NULL){
            intTemp = 0;
            pDosen = startDosen(K);
            while(pDosen != NULL){
                pMengampu = child(pDosen);
                while(pMengampu != NULL){
                    if (infoChild(pMengampu) == infoMatkul(pMatkul)){
                        intTemp++;
                    }
                    pMengampu = nextMengampu(pMengampu);
                }
                pDosen = nextDosen(pDosen);
            }
            if (intTemp > intMost){
                intMost = intTemp;
                tempM = pMatkul;
            }
            pMatkul = nextMatkul(pMatkul);
        }
        cout<<"\n\t\t  Mata kuliah yang diampu dosen terbanyak : "<<infoMatkul(tempM);
    }
}

void leastMatkul(kampus K){
    adrMatkul pMatkul, tempM;
    adrDosen pDosen;
    adrMengampu pMengampu;
    int intLeast, intTemp;
    if (startMatkul(K) == NULL){
        cout<<"\n\t\t  Belum ada mata kuliah yang terdaftar";
    }else if (nextMatkul(startMatkul(K)) == NULL){
        cout<<"\n\t\t  Mata kuliah yang diampu dosen tersedikit : "<<infoMatkul(startMatkul(K));
    }else{
        tempM = startMatkul(K);
        pDosen = startDosen(K);
        while(pDosen != NULL){
            pMengampu = child(pDosen);
            while(pMengampu != NULL){
                if (infoChild(pMengampu) == infoMatkul(tempM)){
                    intLeast++;
                }
                pMengampu = nextMengampu(pMengampu);
            }
            pDosen = nextDosen(pDosen);
        }
        pMatkul = nextMatkul(tempM);
        while (pMatkul != NULL){
            intTemp = 0;
            pDosen = startDosen(K);
            while(pDosen != NULL){
                pMengampu = child(pDosen);
                while(pMengampu != NULL){
                    if (infoChild(pMengampu) == infoMatkul(pMatkul)){
                        intTemp++;
                    }
                    pMengampu = nextMengampu(pMengampu);
                }
                pDosen = nextDosen(pDosen);
            }
            if (intTemp < intLeast){
                intLeast = intTemp;
                tempM = pMatkul;
            }
            pMatkul = nextMatkul(pMatkul);
        }
        cout<<"\n\t\t  Mata kuliah yang diampu dosen tersedikit : "<<infoMatkul(tempM);
    }
}

int selectMenu(){
    system("cls");
    cout<<"\n"
    "> > > > > > > > > > > > >       > MAIN MENU <       < < < < < < < < < < < < <\n"
    "\n"
    "                  =========================================\n"
    "                  =                                       =\n"
    "                  =   > 1. Dosen                          =\n"
    "                  =   > 2. Mata Kuliah                    =\n"
    "                  =   > 0. Exit Program                   =\n"
    "                  =                                       =\n"
    "                  =========================================\n"
    "\n"
    "                  Masukkan pilihan: ";
    int input;
    cin >> input;
    cout << endl;
    return input;
}

int selectMenuDosen(){
    system("cls");
    cout<<"\n"
    "> > > > > > > > > > > > >         > DOSEN <         < < < < < < < < < < < < <\n"
    "\n"
    "                  =========================================\n"
    "                  =                                       =\n"
    "                  =   > 1. Tambah Dosen                   =\n"
    "                  =   > 2. Hapus Dosen                    =\n"
    "                  =   > 3. Tambah Mata Kuliah diampu      =\n"
    "                  =   > 4. Hapus Mata Kuliah diampu       =\n"
    "                  =   > 5. Print Dosen                    =\n"
    "                  =   > 6. Print Mata Kuliah diampu       =\n"
    "                  =   > 7. Terbanyak Mengampu             =\n"
    "                  =   > 8. Tersedikit Mengampu            =\n"
    "                  =   > 0. Kembali ke Main Menu           =\n"
    "                  =                                       =\n"
    "                  =========================================\n"
    "\n"
    "                  Masukkan pilihan: ";
    int input;
    cin >> input;
    return input;
}

void enterToContinue(){
    cout<<"\n                       TEKAN ENTER UNTUK MELANJUTKAN\n";
    getchar();
}

void menuDosen(kampus &K){
    int pilihanDosen;
    infotypeDosen namaD;
    infotypeMatkul namaM;
    adrDosen pDosen;
    pilihanDosen = selectMenuDosen();
    getchar();
    switch(pilihanDosen){
    case 0:
        return;
    case 1:
        cout<<"\t\t  Masukkan nama dosen: ";
        getline(cin, namaD);
        pDosen = alokasiDosen(namaD);
        addDosen(K, pDosen);
        menuDosen(K);
        break;
    case 2:
        cout<<"\t\t  Masukkan nama dosen: ";
        getline(cin, namaD);
        deleteDosen(K, namaD);
        menuDosen(K);
        break;
    case 3:
        cout<<"\t\t  Masukkan nama dosen: ";
        getline(cin, namaD);
        cout<<"\t\t  Masukkan nama mata kuliah: ";
        getline(cin, namaM);
        addMengampu(K, namaD, namaM);
        menuDosen(K);
        break;

    case 4:
        cout<<"\t\t  Masukkan nama dosen: ";
        getline(cin, namaD);
        cout<<"\t\t  Masukkan nama mata kuliah: ";
        getline(cin, namaM);
        deleteMengampu(K, namaD, namaM);
        menuDosen(K);
        break;
    case 5:
        printListDosen(K);
        enterToContinue();
        menuDosen(K);
        break;
    case 6:
        cout<<"\t\t  Masukkan nama dosen: ";
        getline(cin, namaD);
        printMengampu(K, namaD);
        enterToContinue();
        menuDosen(K);
        break;
    case 7:
        mostDosen(K);
        enterToContinue();
        menuDosen(K);
        break;
    case 8:
        leastDosen(K);
        enterToContinue();
        menuDosen(K);
        break;
    }
}

int selectMenuMatkul(){
    system("cls");
    cout<<"\n"
    "> > > > > > > > > > > > >      > MATA KULIAH <      < < < < < < < < < < < < <\n"
    "\n"
    "                  =========================================\n"
    "                  =                                       =\n"
    "                  =   > 1. Tambah Mata Kuliah             =\n"
    "                  =   > 2. Hapus Mata Kuliah              =\n"
    "                  =   > 3. Print Mata Kuliah              =\n"
    "                  =   > 4. Print Dosen Mengampu           =\n"
    "                  =   > 5. Terbanyak Diampu               =\n"
    "                  =   > 6. Tersedikit Diampu              =\n"
    "                  =   > 0. Kembali ke Main Menu           =\n"
    "                  =                                       =\n"
    "                  =========================================\n"
    "\n"
    "                  Masukkan pilihan: ";
    int input;
    cin >> input;
    return input;
}

void menuMatkul(kampus &K){
    int pilihanMatkul;
    infotypeDosen namaD;
    infotypeMatkul namaM;
    adrMatkul pMatkul;
    pilihanMatkul = selectMenuMatkul();
    getchar();
    switch(pilihanMatkul){
    case 0:
        return;
    case 1:
        cout<<"\t\t  Masukkan nama mata kuliah: ";
        getline(cin, namaM);
        pMatkul = alokasiMatkul(namaM);
        addMatkul(K, pMatkul);
        menuMatkul(K);
        break;
    case 2:
        cout<<"\t\t  Masukkan nama mata kuliah: ";
        getline(cin, namaM);
        deleteMatkul(K, namaM);
        menuMatkul(K);
        break;
    case 3:
        printListMatkul(K);
        enterToContinue();
        menuMatkul(K);
        break;
    case 4:
        cout<<"\t\t  Masukkan nama mata kuliah: ";
        getline(cin, namaM);
        printMatkulTerampuh(K, namaM);
        enterToContinue();
        menuMatkul(K);
        break;
    case 5:
        mostMatkul(K);
        enterToContinue();
        menuMatkul(K);
        break;
    case 6:
        leastMatkul(K);
        enterToContinue();
        menuMatkul(K);
        break;
    }
}
