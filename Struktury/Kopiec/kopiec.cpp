//
// Created by jakub on 3/12/2023.
//

#include "kopiec.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

    kopiec::kopiec(){
        table = new node[rozmiar];
        start = false;
    }

    void kopiec::pokaz() {
        cout<<table[0].val<<" : "<<table[0].id<<" : "<<table[0].next<<endl;
    }

    void kopiec::dodaj(int liczba, int id, int next) {
        temp = new node[++rozmiar];
        for(int i=0;i<rozmiar-1;i++) temp[i] = table[i];
        temp[rozmiar-1].val = liczba;
        temp[rozmiar-1].id = id;
        temp[rozmiar-1].next = next;
        relocate();
        sort(liczba, id, next);
    }

    void kopiec::usunKorzen() {
        if(rozmiar==0) {
            cout<<"Kopiec pusty"<<endl;
            return;
        }
        swap(table[0],table[rozmiar-1]);
        temp = new node[--rozmiar];
        for(int i=0;i<rozmiar;i++) temp[i] = table[i];
        relocate();
        int i=0;
        int j=1;
        while(j < rozmiar){
            if(j+1 < rozmiar && table[j+1].val < table[j].val) j++;
            if(table[i].val <= table[j].val) break;
            swap(table[i],table[j]);
            i = j;
            j = 2*j+1;
        }
    }

    void kopiec::sort(int v, int id, int next){
        int i=rozmiar-1;
        while(true){
            if(table[i].val<table[(int)floor((((double)i)-1)/2)].val && i!=0 && (int)floor((((double)i)-1)/2)>=0) {
                swap(table[i],table[(int)floor((((double)i)-1)/2)]);
                i = (int)floor((((double)i)-1)/2);
            } else break;
        }
    }

    void kopiec::relocate(){
        delete [] table;
        table = temp;
}

    bool kopiec::isCorrect(){
        int i=0;
        while(i<rozmiar){
            if(2*i+1>=rozmiar) break;
            if(table[i].val<table[2*i+1].val || table[i].val<table[2*i+2].val && 2*i+2<rozmiar){
                cout<<"BLAD KOPCA w "<<i<<endl;
                return false;
            } else i++;
        }
        cout<<"KOPIEC POPRAWNY"<<endl;
        return true;
    }

    void kopiec::wczytaj(string nazwa) {
        fstream file (nazwa,std::ios_base::in);
        if (!file.is_open()) {
            cout<<"ERROR"<<endl;
            return;
        }
        int number;
        while (file >> number){
            //dodaj(number);
        }
}

    void kopiec::zapisz(string nazwa) {
        if (table==NULL) cout<<"Brak utworzonej tablicy."<<endl;
        else {
            ofstream file (nazwa);
            if (!file.is_open()) {
                cout<<"ERROR"<<endl;
                return;
            }
            for (int i = 0; i < rozmiar; i++) {
               // file<<table[i]<<" ";
            }
        }
    }





