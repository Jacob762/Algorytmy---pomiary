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
        int rozmiar; // ilosc wierzcholkow
        int wierz; // ilosc krawedzi tak naprawde
        int **grafMacierz;
        int **temp;
        lista *list;
        lista *listp;
        nList *nLis;
        Graf();
        Graf(char struktura, string nazwa);
        void init_macierz();
        void init_lista();

        void pokaz();
        void poszerzMacierz(int wielkosc);
        void sciezkaMacierz(int start);

        int *wart;
        int **macInc;

        //Dijkstra
        void dodajMacierz(string nazwa);
        void dodajLista(string nazwa);
        void dodajMacierzI(string nazwa);

        //Ford (lista jest w klasie bf)
        void dodajMacierzFord(string nazwa);

        //prim + kruskal
        void dodajMacierzPrima(string nazwa); //macierz sasiedztwa
        void dodajListaPrim(string nazwa); //lista
        void dodajMacierzPrimaI(string nazwa); //macierz incydencji;

        void getLista();
    };



#endif //SDIZOPROJEKT2_GRAF_H
