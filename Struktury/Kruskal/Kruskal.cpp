//
// Created by jakub on 5/20/2023.
//

#include <fstream>
#include "Kruskal.h"
#define L 100
using namespace std;

    Kruskal::Kruskal() {
        testy();
    }

    void Kruskal::zkruskaluj(int start) {
        int wynik = 0;
        init_zbiory();
        int roz = kolejka.rozmiar;
        for(int krawedz = 0;krawedz<roz;krawedz++){
            if(znajdzDowodce(kolejka.table[0].id)!= znajdzDowodce(kolejka.table[0].next)){
                przypiszDowodce(kolejka.table[0].id,kolejka.table[0].next);
                wynik+=kolejka.table[0].val;
                list.dodajNaKoniec(new node(kolejka.table[0].id,kolejka.table[0].next, kolejka.table[0].val));
            }
            kolejka.usunKorzen();
        }
    }

    void Kruskal::init_zbiory(){
        poprzednicy = new int [size];
        stopien = new int [size];
        for(int i=0;i<size;i++){
            poprzednicy[i] = -1;
            stopien[i] = 0;
        }
    }

    int Kruskal::znajdzDowodce(int liczba){
        if(poprzednicy[liczba]==-1) return liczba;
        return znajdzDowodce(poprzednicy[liczba]);
    }

    void Kruskal::przypiszDowodce(int u, int v){
        int uno = znajdzDowodce(u);
        int vos = znajdzDowodce(v);
        if(uno==vos) return;
        else if(stopien[uno]<stopien[vos]) poprzednicy[uno] = vos;
        else if(stopien[vos]>stopien[uno]) poprzednicy[vos] = uno;
        else{
            poprzednicy[vos] = uno;
            stopien[uno] +=1;
        }
    }

    void Kruskal::init_kolejkaL(){
        kolejka = kopiec();
        listaElement *temp, *temp2;
        for(int i=0;i<graf.rozmiar;i++){
            temp = graf.list[i].head;
            temp2 = graf.listp[i].head;
            while(temp!=NULL){
                kolejka.dodaj(temp2->data,i,temp->data);
                temp = temp->nextEl;
                temp2 = temp2->nextEl;
            }
        }
    }

    void Kruskal::init_kolejkaM(){
        kolejka = kopiec();
        for(int i=0;i<graf.rozmiar;i++){
            for(int j=0;j<graf.rozmiar;j++){
                if(graf.grafMacierz[i][j]!=-1){
                    kolejka.dodaj(graf.grafMacierz[i][j],i,j);
                }
            }
        }
    }


void Kruskal::init_kolejkaMI(){
    int *odw = new int[graf.wierz];
    for(int i=0;i<graf.wierz;i++) odw[i] = false;
    kolejka = kopiec();
    for(int i=0;i<graf.rozmiar;i++){
        for(int j=0;j<graf.wierz;j++){
            if(graf.macInc[i][j]==1&&!odw[j]){
                odw[j]=true;
                for(int k=0;k<graf.rozmiar;k++) {
                    if(k==i) continue;
                    if (graf.macInc[k][j]==1){
                        kolejka.dodaj(graf.wart[j],i,k);
                        break;
                    }
                }
            }
        }
    }
}
void Kruskal::wyswietl() {
    node* temp;
    temp = list.head;
    cout<<endl;
    cout<<"id"<<"  "<<"next"<<"  "<<"val"<<endl;
    while (temp!=NULL){
        cout<<temp->id<<"    "<<temp->next<<"    "<<temp->val<<endl;
        temp = temp->nextEl;
    }
    while(list.head!=NULL) list.usunZPoczatku();
}

void Kruskal::testy(){
    ofstream dijFile ("Wyniki pomiarow Kruskal.txt",ios::out|ios::app);
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    chrono::duration<double> time_span;
    double srednia = 0;
    double sredniaL = 0;
    timeFin = new double * [8];
    for(int i=0;i<8;i++) timeFin[i] = new double [5];
    timeFinL = new double * [8];
    for(int i=0;i<8;i++) timeFinL[i] = new double [5];
    float zagesz[] = {0.2,0.4,0.6,0.8,0.99};
    int c = 0;
    for(int k=5;c<8;k+=20){
        size = k;
        for(int j=0;j<5;j++){
            for(int i=0;i<L;i++){
                gen = ranGen(k,10,zagesz[j]);

                graf = Graf('n',"plik.txt");
                t1 = chrono::high_resolution_clock::now();
                init_kolejkaL();
                zkruskaluj(0);
                t2 = chrono::high_resolution_clock::now();
                time_span = std::chrono::duration_cast<chrono::duration<double>>(t2 - t1);
                sredniaL += std::chrono::duration<double>(time_span).count();

                graf = Graf('k',"plik.txt");
                t1 = chrono::high_resolution_clock::now();
                init_kolejkaMI();
                zkruskaluj(0);
                t2 = chrono::high_resolution_clock::now();
                time_span = std::chrono::duration_cast<chrono::duration<double>>(t2 - t1);
                srednia += std::chrono::duration<double>(time_span).count();
            }
            timeFinL[c][j] = sredniaL/L;
            timeFin[c][j] = srednia/L;
            sredniaL=0;
            srednia=0;
        }
        c++;
    }
    dijFile<<"TABLICA"<<endl;
    for(int i=0;i<8;i++){
        for(int j=0;j<5;j++){
            dijFile<<timeFin[i][j]<<"  ";
        }
        dijFile<<endl;
    }
    dijFile<<endl;
    dijFile<<"LISTA"<<endl;
    for(int i=0;i<8;i++){
        for(int j=0;j<5;j++){
            dijFile<<timeFinL[i][j]<<"  ";
        }
        dijFile<<endl;
    }
    dijFile<<endl;
    dijFile.close();
}