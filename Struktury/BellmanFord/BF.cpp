//
// Created by jakub on 5/20/2023.
//

#include <fstream>
#include "BF.h"
#define L 100

namespace std {
    BF::BF() {
        testy();
    }

    bool BF::zfordujMacierz(int start) {
        drogi = new int [graf.rozmiar];
        poprzednicy = new int [graf.rozmiar];
        bool res;
        for(int i=0;i<graf.rozmiar;i++){
            if(i!=start){
                drogi[i] = INT_MAX;
                poprzednicy[i] = -1;
            } else{
                drogi[i] = 0;
                poprzednicy[i] = -1;
            }
        }
        for(int i=1;i<graf.rozmiar;i++){
            res = true;
            for(int j=0;j<graf.rozmiar;j++){
                for(int k=0;k<graf.rozmiar;k++){
                    if(graf.grafMacierz[j][k]!=INT_MAX&&drogi[j]!=INT_MAX){
                        if(drogi[k]<=drogi[j]+graf.grafMacierz[j][k]) continue;
                        res = false;
                        drogi[k]=drogi[j]+graf.grafMacierz[j][k];
                        poprzednicy[k] = j;
                    }
                }
            }
            if(res) return true;
        }

        for(int i=0;i<graf.rozmiar;i++){
            for(int j=0;j<graf.rozmiar;j++){
                if(drogi[j]>drogi[i]+graf.grafMacierz[i][j]) return false;
            }
        }
        return true;
    }



    void BF::wyswietl(){
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
        cout<<endl;
    }

    void BF::poprawMacierz(){

    }

    void BF::zaladujListe(string nazwa) {
        int x,y,val;
        int s;
        fstream file(nazwa,std::ios_base::in);
        if (!file.is_open()) {
            cout<<"ERROR"<<endl;
            return;
        }
        file >> x >> y;
        node* temp;
        s = x;
        rozmiarL = x;
        lista = new nList [x];
        for(int i=0;i<s;i++) lista[i] = nList();
        while(file >> x >> y >> val){
            lista[x].dodajNaKoniec(new node(x,y,val));
        }
    }

    bool BF::zfordujListe(int start) {
        node *temp;
        drogi = new int [rozmiarL];
        poprzednicy = new int [rozmiarL];
        bool res;
        for(int i=0;i<rozmiarL;i++){
            if(i!=start){
                drogi[i] = INT_MAX;
                poprzednicy[i] = -1;
            } else{
                drogi[i] = 0;
                poprzednicy[i] = -1;
            }
        }

        for(int i=1;i<rozmiarL;i++){
            res = true;
            for(int j=0;j<rozmiarL;j++){
                temp = lista[j].head;
                while(temp!=NULL){
                    if(drogi[j]!=INT_MAX){
                        if(drogi[temp->next]<=drogi[j]+temp->val){
                            temp = temp->nextEl;
                            continue;
                        }
                        res = false;
                        drogi[temp->next] = drogi[j]+temp->val;
                        poprzednicy[temp->next] = j;
                    }
                    temp = temp->nextEl;
                }

            }
            if(res) return true;
        }
        for(int i=0;i<rozmiarL;i++){
            temp = lista[i].head;
            while(temp!=NULL){
                if(drogi[temp->next]<=drogi[i]+temp->val) return false;
                temp = temp->nextEl;
            }
        }
        return true;
    }

    void BF::getLista(){
        node* temp;
        for(int i=0;i<rozmiarL;i++){
            temp = lista[i].head;
            cout<<i<<"\t";
            while (temp!=NULL){
                cout<<temp->next<<" : "<<temp->val<<"  ";
                temp = temp->nextEl;
            }
            cout<<endl;
        }
    }

    void BF::testy(){
        ofstream dijFile ("Wyniki pomiarow BellmanFord.txt",ios::out|ios::app);
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
            for(int j=0;j<5;j++){
                for(int i=0;i<L;i++){
                    gen = ranGen(k,10,zagesz[j]);

                    zaladujListe("plik.txt");
                    t1 = chrono::high_resolution_clock::now();
                    zfordujListe(0);
                    t2 = chrono::high_resolution_clock::now();
                    time_span = std::chrono::duration_cast<chrono::duration<double>>(t2 - t1);
                    sredniaL += std::chrono::duration<double>(time_span).count();

                    graf = Graf('f',"plik.txt");
                    t1 = chrono::high_resolution_clock::now();
                    graf.init_macierz();
                    zfordujMacierz(0);
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