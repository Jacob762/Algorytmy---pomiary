//
// Created by jakub on 6/2/2023.
//

#ifndef SDIZOPROJEKT2TESTY_RANGEN_H
#define SDIZOPROJEKT2TESTY_RANGEN_H
#include <iostream>
#include <cmath>
#include <fstream>

namespace std {

    class ranGen {



    public:
        ranGen(int nody, int krawedzie, float zageszczenie);
        void wygenerujGraf(int nody, int krawedzie, float zageszczenie);
        ranGen();
    };

} // std

#endif //SDIZOPROJEKT2TESTY_RANGEN_H
