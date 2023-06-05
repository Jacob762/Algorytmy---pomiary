//
// Created by jakub on 5/20/2023.
//

#ifndef SDIZOPROJEKT2_BF_H
#define SDIZOPROJEKT2_BF_H
#include <iostream>
#include <chrono>
#include "../Kopiec/kopiec.h"
#include "../Graf.h"
#include "../Slist/nList.h"
#include "../node.h"
#include "../ranGen.h"

namespace std {

    class BF {
    public:
        BF();
        Graf graf;
        nList *lista;
        bool zfordujMacierz(int start);
        int *drogi;
        bool *odwiedzoned;
        int *poprzednicy;
        void wyswietl();
        void zaladujListe(string nazwa);
        void poprawMacierz();
        int rozmiarL;
        bool zfordujListe(int start);
        nList* pop;
        void getLista();

        double **timeFin;
        double **timeFinL;
        ranGen gen;

        void testy();
    };

} // std

#endif //SDIZOPROJEKT2_BF_H
