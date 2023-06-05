//
// Created by jakub on 5/3/2023.
//

#include "Prima.h"
#define L 100

namespace std {

    Prima::Prima() {
        testy();
    }

    void Prima::zprimujMacierz(int start) {
        int rozmiar = graf.rozmiar;
        int ik =0;
        kolejka = kopiec();
        odwiedzoned = new bool [rozmiar];
        for(int i=0;i<rozmiar;i++) odwiedzoned[i] = false;
        int wynik = 0;
        int m = start;
        while(ik<rozmiar-1){
            odwiedzoned[m] = true;
            for(int j=0;j<rozmiar;j++){
                if(graf.grafMacierz[m][j]!=-1 && !odwiedzoned[j]){
                    kolejka.dodaj(graf.grafMacierz[m][j],m,j);
                }
            }
            while(true){
                if(!odwiedzoned[kolejka.table[0].next]){
                    wynik+=kolejka.table[0].val;
                    m = kolejka.table[0].next;
                    kolejka.usunKorzen();
                    break;
                } else{
                    kolejka.usunKorzen();
                    if(kolejka.rozmiar==0) break;
                }
            }
            ik++;
        }
    }

    void Prima::zprimujListe(int start){
        int rozmiar = graf.rozmiar;
        kolejka = kopiec();
        odwiedzoned = new bool [rozmiar];
        int ik =0;
        for(int i=0;i<rozmiar;i++) odwiedzoned[i] = false;
        int wynik = 0;
        int m = start;
        node *tmp;
        while(ik<rozmiar-1){
            odwiedzoned[m] = true;
            tmp = graf.nLis[m].head;
                while(tmp!=NULL){
                    if(!odwiedzoned[tmp->next]){
                        kolejka.dodaj(tmp->val,m,tmp->next);
                    }
                    tmp = tmp->nextEl;
                }
            while(true){
                if(!odwiedzoned[kolejka.table[0].next]){
                    wynik+=kolejka.table[0].val;
                    m = kolejka.table[0].next;
                    kolejka.usunKorzen();
                    break;
                } else{
                    kolejka.usunKorzen();
                    if(kolejka.rozmiar==0) break;
                }
            }
            ik++;
        }
    }

    void Prima::wyswietl() {
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

    void Prima::testy(){
        ofstream dijFile ("Wyniki pomiarow Prima.txt",ios::out|ios::app);
        chrono::high_resolution_clock::time_point t1;
        chrono::high_resolution_clock::time_point t2;
        chrono::duration<double> time_span;
        double srednia = 0;
        double sredniaL = 0;
        int c = 0;
        timeFin = new double * [8];
        for(int i=0;i<8;i++) timeFin[i] = new double [5];
        timeFinL = new double * [8];
        for(int i=0;i<8;i++) timeFinL[i] = new double [5];
        float zagesz[] = {0.2,0.4,0.6,0.8,0.99};

        for(int k=5;c<8;k+=20){
            for(int j=0;j<5;j++){
                for(int i=0;i<L;i++){
                    gen = ranGen(k,10,zagesz[j]);

                    list = nList();
                    graf = Graf('n',"plik.txt");
                    t1 = chrono::high_resolution_clock::now();
                    zprimujListe(0);
                    t2 = chrono::high_resolution_clock::now();
                    time_span = std::chrono::duration_cast<chrono::duration<double>>(t2 - t1);
                    sredniaL += std::chrono::duration<double>(time_span).count();

                    graf = Graf('k',"plik.txt");
                    t1 = chrono::high_resolution_clock::now();
                    zprimujMacierz(0);
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
} // std