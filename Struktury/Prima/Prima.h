//
// Created by jakub on 5/3/2023.
//

#ifndef SDIZOPROJEKT2_PRIMA_H
#define SDIZOPROJEKT2_PRIMA_H
#include <iostream>
#include <chrono>
#include "../Tablica/tablica.h"
#include "../Kopiec/kopiec.h"
#include "../Lista/lista.h"
#include "../Graf.h"
#include "../node.h"
#include "../Slist/nList.h"
#include "../ranGen.h"
namespace std {

    class Prima {
    public:


        Graf graf;
        void zprimujMacierz(int start);
        int *drogi;
        bool *odwiedzoned;
        int *poprzednicy;
        void wyswietl();
        kopiec kolejka;
        nList list;
        Prima();
        void zprimujListe(int start);

        double **timeFin;
        double **timeFinL;
        ranGen gen;

        void testy();

        void zprimujMacierzI(int start);
    };

} // std

#endif //SDIZOPROJEKT2_PRIMA_H
