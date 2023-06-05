//
// Created by jakub on 5/20/2023.
//

#ifndef SDIZOPROJEKT2_KRUSKAL_H
#define SDIZOPROJEKT2_KRUSKAL_H
#include <iostream>
#include "../Tablica/tablica.h"
#include "../Kopiec/kopiec.h"
#include "../Lista/lista.h"
#include "../Graf.h"
#include "../node.h"
#include "../Slist/nList.h"
#include "../ranGen.h"

class Kruskal {
public:

    Graf graf;
    void zkruskaluj(int start);
    int *stopien;
    int size;
    bool *odwiedzoned;
    int *poprzednicy;
    void wyswietl();
    kopiec kolejka;
    Kruskal();
    nList list;
    void init_zbiory();
    double **timeFin;
    double **timeFinL;
    ranGen gen;
    int znajdzDowodce(int liczba);

    void przypiszDowodce(int u, int v);

    void init_kolejkaM();
    void init_kolejkaL();

    void testy();
};


#endif //SDIZOPROJEKT2_KRUSKAL_H
