//
// Created by jakub on 5/3/2023.
//

#include "Dijkstra.h"
#define L 100
namespace std {

    Dijkstra::Dijkstra(){
        gen = ranGen();
        testy();
    }

    void Dijkstra::zdijkstrujMacierz(int start){
        bool dodaned[graf.rozmiar];
        for(int i=0;i<graf.rozmiar;i++) dodaned[i] = false;
        drogi = new int [graf.rozmiar];
        odwiedzoned = new bool [graf.rozmiar];
        poprzednicy = new int [graf.rozmiar];
        que = kopiec();
        int current;
        for(int i=0;i<graf.rozmiar;i++){
            if(i!=start){
                drogi[i] = INT_MAX;
                odwiedzoned[i] = false;
                poprzednicy[i] = -1;
            } else{
                drogi[i] = 0;
                odwiedzoned[i] = true;
                poprzednicy[i] = -1;
            }
        }
        que.dodaj(drogi[start],start,0);
        while(que.rozmiar!=0){
            current = que.table[0].id;
            que.usunKorzen();
            odwiedzoned[current] = true;
            for(int i=0;i<graf.rozmiar;i++) {
                if (drogi[i] > drogi[current] + graf.grafMacierz[current][i] && !odwiedzoned[i] && graf.grafMacierz[current][i]!=-1) {
                    poprzednicy[i] = current;
                    drogi[i] = drogi[current] + graf.grafMacierz[current][i];
                }
            }
            for(int i=0;i<graf.rozmiar;i++){
                if(drogi[i]!=INT_MAX && !odwiedzoned[i] && !dodaned[i]) {
                    que.dodaj(drogi[i],i,0);
                    dodaned[i] = true;
                }
            }
        }
        delete [] drogi;
        delete [] odwiedzoned;
        delete [] poprzednicy;
    }

    void Dijkstra::zdijkstrujListe(int start){
        bool dodaned[graf.rozmiar];
        for(int i=0;i<graf.rozmiar;i++) dodaned[i] = false;
        drogi = new int [graf.rozmiar];
        odwiedzoned = new bool [graf.rozmiar];
        poprzednicy = new int [graf.rozmiar];
        que = kopiec();
        node *temp;
        int current;
        for(int i=0;i<graf.rozmiar;i++){
            if(i!=start){
                drogi[i] = INT_MAX;
                odwiedzoned[i] = false;
                poprzednicy[i] = -1;
            } else{
                drogi[i] = 0;
                odwiedzoned[i] = true;
                poprzednicy[i] = -1;
            }
        }
        que.dodaj(drogi[start],start,0);
        while(que.rozmiar!=0){
            current = que.table[0].id;
            que.usunKorzen();
            odwiedzoned[current] = true;
            temp = graf.nLis[current].head;
            while(temp!=NULL) {
                if (drogi[temp->next] > drogi[current] + temp->val && !odwiedzoned[temp->next]) {
                    poprzednicy[temp->next] = current;
                    drogi[temp->next] = drogi[current] + temp->val;
                }
                temp = temp->nextEl;
            }
            for(int i=0;i<graf.rozmiar;i++){
                if(drogi[i]!=INT_MAX&&!odwiedzoned[i]&&!dodaned[i]) {
                    que.dodaj(drogi[i],i,0);
                    dodaned[i] = true;
                }
            }
        }
        delete [] drogi;
        delete [] odwiedzoned;
        delete [] poprzednicy;
    }


    void Dijkstra::wyswietl(){
        int* S = new int [graf.rozmiar];
        int sptr = 0;
        for( int i = 0; i < graf.rozmiar; i++ )
        {
            cout << i << ": ";

            // Ścieżkę przechodzimy od końca ku początkowi,
            // Zapisując na stosie kolejne wierzchołki

            for( int j = i; j > -1; j = poprzednicy [ j ] ) S [ sptr++ ] = j;

            // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

            while( sptr ) cout << S [ --sptr ] << " ";

            // Na końcu ścieżki wypisujemy jej koszt

            cout << "$" << drogi [ i ] << endl;
        }
    }

    void Dijkstra::testy(){
        ofstream dijFile ("Wyniki pomiarow Dijkstra.txt",ios::out|ios::app);
        chrono::high_resolution_clock::time_point t1;
        chrono::high_resolution_clock::time_point t2;
        chrono::duration<double> time_span;
        double srednia = 0;
        double sredniaL = 0;
        timeFin = new double * [8];
        for(int i=0;i<8;i++) timeFin[i] = new double [5];
        timeFinL = new double * [8];
        for(int i=0;i<8;i++) timeFinL[i] = new double [5];
        double zagesz[] = {0.2,0.4,0.6,0.8,0.99};
        int c = 0;
        for(int k=5;c<8;k+=20){
            for(int j=0;j<5;j++){
                for(int i=0;i<L;i++){
                    gen = ranGen(k,10,zagesz[j]);
                    graf = Graf('l',"plik.txt");
                    t1 = chrono::high_resolution_clock::now();
                    zdijkstrujListe(0);
                    t2 = chrono::high_resolution_clock::now();
                    time_span = std::chrono::duration_cast<chrono::duration<double>>(t2 - t1);
                    sredniaL += std::chrono::duration<double>(time_span).count();
                    graf = Graf('m',"plik.txt");
                    t1 = chrono::high_resolution_clock::now();
                    zdijkstrujMacierz(0);
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
            //if(c==15) break;
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