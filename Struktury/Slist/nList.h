//
// Created by jakub on 5/31/2023.
//

#ifndef SDIZOPROJEKT2_NLIST_H
#define SDIZOPROJEKT2_NLIST_H
#include <iostream>
#include "../node.h"

namespace std {

    class nList {
    public:
        node * head;
        node * tail;
        int rozmiar;
        nList();
        bool isEmpty();
        node* wyszukajElement(int liczba);
        void dodajNaKoniec(node *element);
        void dodajNaPoczatek(node *element);
        void usunZPoczatku();
        void usunZKonca();
        bool safetyFirst();
    };

} // std

#endif //SDIZOPROJEKT2_NLIST_H
