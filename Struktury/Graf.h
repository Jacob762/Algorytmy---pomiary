//
// Created by jakub on 5/5/2023.
//

#ifndef SDIZOPROJEKT2_GRAF_H
#define SDIZOPROJEKT2_GRAF_H
#include <string>
#include <iostream>
#include "Kopiec/kopiec.h"
#include "Lista/lista.h"
#include "Slist/nList.h"
#include "node.h"
// nie da sie includowac dwoch list roznych niewiadomo czemu XD

using namespace std;

    class Graf {
    public:
        kopiec Q;
        bool *S;
        int *koszt;
        int *poprzednik;
        int rozmiar;
        int **grafMacierz;
        int **temp;
        lista *list;
        lista *listp;
        nList *nLis;
        Graf();
        Graf(char struktura, string nazwa);
        void init_macierz();
        void init_lista();
        void dodajMacierz(string nazwa);

        void dodajMacierzFord(string nazwa);
        void pokaz();
        void poszerzMacierz(int wielkosc);
        void sciezkaMacierz(int start);

        void dodajLista(string nazwa);

        void dodajMacierzPrima(string nazwa);

        void dodajListaPrim(string nazwa);

        void getLista();
    };



#endif //SDIZOPROJEKT2_GRAF_H
