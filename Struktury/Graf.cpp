//
// Created by jakub on 5/5/2023.
//

#include "Graf.h"
#include <iostream>
#include <fstream>


using namespace std;

    Graf::Graf() {

    }

    Graf::Graf(char struktura, string nazwa){
        rozmiar = 1;
        switch(struktura){
            case 'm':
                dodajMacierzI(nazwa);
                break;
            case 'l':
                dodajLista(nazwa);
                break;
            case 'k':
                dodajMacierzPrimaI(nazwa);
                break;
            case 'n':
                dodajListaPrim(nazwa);
                break;
            case 'f':
                dodajMacierzFord(nazwa);
                break;
        }
    }

    void Graf::init_macierz() {
        cout<<endl<<endl;
        for(int i=0;i<rozmiar;i++){
            for(int j=0;j<rozmiar;j++){
                if(grafMacierz[i][j]!=-1){
                    Q.dodaj(grafMacierz[i][j],i,j);
                }
            }
        }
    }

    void Graf::dodajMacierz(string nazwa) {
        int x,y,val;
        fstream file(nazwa,std::ios_base::in);
        if (!file.is_open()) {
            cout<<"ERROR"<<endl;
            return;
        }
        file >> x >> y;
        rozmiar = x;
        grafMacierz = new int*[rozmiar];
        for(int i=0;i<rozmiar;i++){
            grafMacierz[i] = new int [rozmiar];
            for(int j=0;j<rozmiar;j++) grafMacierz[i][j] = -1;
        }
        while(file >> x >> y >> val){
            if(grafMacierz[x][y]==-1) grafMacierz[x][y] = val;
        }
    }
void Graf::dodajMacierzI(string nazwa) {
    int x,y,val;
    int ind = 0;

    fstream file(nazwa,std::ios_base::in);
    if (!file.is_open()) {
        cout<<"ERROR"<<endl;
        return;
    }
    file >> x >> y;
    rozmiar = x;
    wierz = y;
    wart = new int[wierz];
    macInc = new int*[rozmiar];
    for(int i=0;i<rozmiar;i++){
        macInc[i] = new int [y];
        for(int j=0;j<rozmiar;j++) macInc[i][j] = 0;
    }
    while(file >> x >> y >> val){
        macInc[x][ind] = 1;
        macInc[y][ind] = -1;
        wart[ind] = val;
        ind++;
    }
}
    void Graf::dodajMacierzFord(string nazwa){
        int x,y,val;
        fstream file(nazwa,std::ios_base::in);
        if (!file.is_open()) {
            cout<<"ERROR"<<endl;
            return;
        }
        file >> x >> y;
        rozmiar = x;
        grafMacierz = new int*[rozmiar];
        for(int i=0;i<rozmiar;i++){
            grafMacierz[i] = new int [rozmiar];
            for(int j=0;j<rozmiar;j++) grafMacierz[i][j] = INT_MAX;
        }
        while(file >> x >> y >> val){
            if(grafMacierz[x][y]==INT_MAX) grafMacierz[x][y] = val;
        }
    }

    void Graf::pokaz() {
        cout<<"   ";
        for(int i=0;i<rozmiar;i++) cout<<i<<"  ";
        cout<<endl;
        for(int i=0;i<rozmiar;i++){
            cout<<i<<"  ";
            for(int j=0;j<rozmiar;j++) cout<<grafMacierz[i][j]<<" ";
            cout<<endl;
        }

    }
    void Graf::init_lista() {
        cout<<endl<<endl;
        listaElement* temp;
        listaElement* temp2;
        for(int i=0;i<rozmiar;i++){
            temp = list[i].head;
            temp2 = listp[i].head;
            while(temp!=NULL){
                Q.dodaj(temp2->data,i,temp->data);
                temp = temp->nextEl;
                temp2 = temp2->nextEl;
            }
        }
    }

    void Graf::poszerzMacierz(int wielkosc) {
        temp = new int*[wielkosc];
        for(int i=0;i<wielkosc;i++) {
            temp[i] = new int[wielkosc];
            for(int j=0;j<wielkosc;j++) temp[i][j] = -1;
        }
        for(int i=0;i<rozmiar;i++) {
            for(int j=0;j<rozmiar;j++) {
                temp[i][j] = grafMacierz[i][j];
                if(i==j) temp[i][j] = 0;
            }
        }
        rozmiar = wielkosc;
        delete [] grafMacierz;
        grafMacierz = temp;
    }

void Graf::dodajLista(string nazwa) {
    bool powtorka = false;
    int x,y,val;
    fstream file(nazwa,std::ios_base::in);
    if (!file.is_open()) {
        cout<<"ERROR"<<endl;
        return;
    }
    file >> x >> y;
    rozmiar = x;
    listaElement *tempp;
    node *temp2;

    nLis = new nList[rozmiar];
    for(int i=0;i<rozmiar;i++) nLis[i] = nList();
    while(file >> x >> y >> val){
        temp2 = nLis[x].head;
        while(temp2!=NULL){
            if(temp2->next==y) powtorka = true;
            temp2 = temp2->nextEl;
        }
        if(!powtorka){
            nLis[x].dodajNaKoniec(new node(x,y,val));
        }
        powtorka = false;
    }
}

    void Graf::dodajListaPrim(string nazwa) {
        bool powtorka = false;
        int x,y,val;
        fstream file(nazwa,std::ios_base::in);
        if (!file.is_open()) {
            cout<<"ERROR"<<endl;
            return;
        }
        file >> x >> y;
        rozmiar = x;
        list = new lista [rozmiar];
        listp = new lista [rozmiar];
        nLis = new nList[rozmiar];
        listaElement *tempp;
        node *temp2;
        for(int i=0;i<rozmiar;i++) list[i] = lista();
        for(int i=0;i<rozmiar;i++) nLis[i] = nList();
        for(int i=0;i<rozmiar;i++) listp[i] = lista();
        while(file >> x >> y >> val){
            tempp = list[x].head;
            temp2 = nLis[x].head;
            while(tempp!=NULL){
                if(tempp->data==y) powtorka = true;
                tempp = tempp->nextEl;
            }
            while(temp2!=NULL){
                if(temp2->next==y) powtorka = true;
                temp2 = temp2->nextEl;
            }
            if(!powtorka){
                list[x].dodajNaKoniec(new listaElement(y));
                listp[x].dodajNaKoniec(new listaElement(val));
                list[y].dodajNaKoniec(new listaElement(x));
                listp[y].dodajNaKoniec(new listaElement(val));
                nLis[x].dodajNaKoniec(new node(x,y,val));
                nLis[y].dodajNaKoniec(new node(y,x,val));
            }
            powtorka = false;
        }
    }

    void Graf::dodajMacierzPrima(string nazwa) {
        int x,y,val;
        fstream file(nazwa,std::ios_base::in);
        if (!file.is_open()) {
            cout<<"ERROR"<<endl;
            return;
        }
        file >> x >> y;
        rozmiar = x;
        grafMacierz = new int*[rozmiar];
        for(int i=0;i<rozmiar;i++){
            grafMacierz[i] = new int [rozmiar];
            for(int j=0;j<rozmiar;j++) grafMacierz[i][j] = -1;
        }
        while(file >> x >> y >> val){
            if(grafMacierz[x][y] == -1){
                grafMacierz[x][y] = val;
                grafMacierz[y][x] = val;
            }

        }
    }

void Graf::dodajMacierzPrimaI(string nazwa) {
    int x,y,val;
    int ind = 0;
    fstream file(nazwa,std::ios_base::in);
    if (!file.is_open()) {
        cout<<"ERROR"<<endl;
        return;
    }
    file >> x >> y;
    rozmiar = x;
    int *zab = new int [rozmiar];
    for(int i=0;i<rozmiar;i++) zab[i] = 1;
    wierz = y;
    wart = new int[wierz];
    for(int i=0;i<wierz;i++) wart[i] = 0;
    macInc = new int*[rozmiar];
    for(int i=0;i<rozmiar;i++){
        macInc[i] = new int [y];
        for(int j=0;j<wierz;j++) macInc[i][j] = 0;
    }
    while(file >> x >> y >> val){
        if(zab[x]<rozmiar&&zab[y]<rozmiar) {
            macInc[x][ind] = 1;
            macInc[y][ind] = 1;
            wart[ind] = val;
            ind++;
            zab[x]++;
            zab[y]++;
        }
    }
}
    void Graf::getLista(){
        listaElement *tmp;
        node *tm;
        for(int i=0;i<rozmiar;i++){
            tm = nLis[i].head;
            cout<<i<<"\t";
            while(tm!=NULL){
                cout<<tm->next<<" : "<<tm->val<<"  ";
                tm = tm->nextEl;
            }
            cout<<endl;
        }
    }
