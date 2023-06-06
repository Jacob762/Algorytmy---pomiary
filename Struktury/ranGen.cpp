//
// Created by jakub on 6/2/2023.
//

#include "ranGen.h"
#include <ctime>

namespace std {

    ranGen::ranGen() {

    }

    ranGen::ranGen(int nody, int krawedzie, float zageszczenie) {
        wygenerujGraf(nody,krawedzie,zageszczenie);
    }


    void ranGen::wygenerujGraf(int nody, int krawedzie, float zageszczenie){
        bool *tabOd = new bool [nody];
        int wyjscia = floor(zageszczenie*nody);
        for(int i=0;i<nody;i++) tabOd[i]= false;
        ofstream file("plik.txt", ios::out);
        if (!file.is_open()) {
            cout<<"ERROR"<<endl;
            return;
        }
        int x,y,z;
        file<<nody<<" "<<nody*wyjscia<<endl;
        for(int i=0;i<nody;i++){
            x = i;
            tabOd[x] = true;
            for(int j=0;j<wyjscia;j++) {
                y = rand()%nody;
                if(tabOd[y]){
                    while(true) {
                        if(tabOd[y]||y==x){
                            y = rand()%nody;
                        } else break;
                    }
                }
                tabOd[y] = true;
                z = rand()%20+1;
                file<<x<<" "<<y<<" "<<z<<endl;
            }
            for(int k=0;k<nody;k++) tabOd[k]= false;
        }
        file.close();

    }

} // std