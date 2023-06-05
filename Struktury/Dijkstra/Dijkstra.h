//
// Created by jakub on 5/3/2023.
//

#ifndef SDIZOPROJEKT2_DIJKSTRA_H
#define SDIZOPROJEKT2_DIJKSTRA_H
#include <iostream>
#include <chrono>
#include "../Tablica/tablica.h"
#include "../Kopiec/kopiec.h"
#include "../Lista/lista.h"
#include "../Graf.h"
#include "../Lista/listaElement.h"
#include "../ranGen.h"
#include "../node.h"
namespace std {

    class Dijkstra {
    public:

        Dijkstra();
        Graf graf;
        void zdijkstrujMacierz(int start);
        int *drogi;
        bool *odwiedzoned;
        int *poprzednicy;
        kopiec que;
        void wyswietl();
        double **timeFin;
        double **timeFinL;
        ranGen gen;
        void testy();

        void zdijkstrujListe(int start);
    };

} // std

#endif //SDIZOPROJEKT2_DIJKSTRA_H
