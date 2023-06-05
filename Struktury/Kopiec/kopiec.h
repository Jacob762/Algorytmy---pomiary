//
// Created by jakub on 3/12/2023.
//

#ifndef SDIZO_KOPIEC_H
#define SDIZO_KOPIEC_H
#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

class kopiec {
private:
    bool start = true;
public:
    struct node{
        int id;
        int next;
        int val;
    };
    int n=0;
    kopiec();
    node * temp;
    int rozmiar = 0;
    node* table = NULL;
    void dodaj(int liczba, int id, int next);
    void usunKorzen();
    void pokaz();
    void relocate();
    void sort(int v,int id, int next);
    bool isCorrect();
    void wczytaj(string nazwa);
    void zapisz(string nazwa);
    int front();
};


#endif //SDIZO_KOPIEC_H
