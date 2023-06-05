//
// Created by Jakub Klawon on 08/03/2023.
//

#include "lista.h"
#include <iostream>
#include <fstream>

using namespace std;

lista::lista(){
    head = NULL;
    tail = NULL;
    rozmiar=0;
}

void lista::dodajNaKoniec(listaElement * element) {
    if (!head) {
        head = element;
        tail = element;
    }
    else {
        tail->nextEl = element;
        element->prevEl = tail;
        tail = element;
    }
    if (head == element) element->prevEl = NULL;
    if (tail == element) element->nextEl = NULL;
    rozmiar++;
}

void lista::dodajNaPoczatek(listaElement * element){
    if (!head) {
        head = element;
        tail = element;
    }
    else {
        head->prevEl = element;
        element->nextEl = head;
        head = element;
    }
    if (head == element) element->prevEl = NULL;
    if (tail == element) element->nextEl = NULL;
    rozmiar++;
}

void lista::dodajWDowolnymMiejscu(int index,listaElement * element){
    if(index<0||index>=rozmiar&&index!=0) {
        cout<<"Nie ma takiego indeksu"<<endl;
        return;
    }
    if (!head) {
        head = element;
        tail = element;
        rozmiar++;
    }
    else if(index==0){ //head
        dodajNaPoczatek(element);
    }
    else if(index==rozmiar-1){  //tail
        dodajNaKoniec(element);
    }
    else {
        listaElement* temp = wyszukajElement(index);
        temp->prevEl->nextEl = element;
        element->prevEl = temp->prevEl;
        element->nextEl = temp;
        temp->prevEl = element;
        rozmiar++;
    }
    if (head == element) element->prevEl = NULL;
    if (tail == element) element->nextEl = NULL;
}

void lista::pokaz() {
    if(isEmpty()) {
        cout<<"Lista pusta"<<endl;
        return;
    }
    listaElement* temp;
    temp = head;
    for(int i=0;i<rozmiar;i++){
        cout<<temp->data<<" ";
        temp = temp -> nextEl;
    }
    cout<<endl;
    delete temp;
}

listaElement* lista::wyszukajElement(int liczba) {
    listaElement* temp = head;
    for(int i=0;i<liczba;i++) {
        if(i==liczba-1) return temp;
        temp = temp->nextEl;
    }
    return NULL;
}

int lista::wyszukajElementIndex(int liczba) {
    if(isEmpty()){
        cout<<"Lista pusta"<<endl;
        return -8;
    }
    listaElement* temp = head;
    int indeks =  0;
    cout<<temp->data<<endl;
    while(temp!=tail) {
        if(temp->data == liczba) return indeks;
        temp = temp->nextEl;
        indeks++;
    }
    cout<<temp->data<<endl;
    if(temp->data==liczba) return indeks;
    return -9;
}
bool lista::isEmpty() {
    if(!head) return true;
    else return false;
}

bool lista::isEven(){
    if(rozmiar%2) return false;
    else return true;
}

void lista::usunZPoczatku(){
    if(rozmiar==0){
        cout<<"Lista pusta"<<endl;
        return;
    }
    if(!safetyFirst()) {
        return;
    }
    head->nextEl->prevEl = NULL;
    head = head->nextEl;
    rozmiar--;
}

void lista::usunZKonca(){
    if(rozmiar==0){
        cout<<"Lista pusta"<<endl;
        return;
    }
    if(!safetyFirst()) {
        return;
    }
    tail->prevEl->nextEl = NULL;
    tail = tail->prevEl;
    rozmiar--;
}

void lista::usunZDowolnegoMiejsca(int index){
    if(rozmiar==0){
        cout<<"Lista pusta"<<endl;
        return;
    }
    if(!safetyFirst()) {
        cout<<"Lista nie istnieje"<<endl;
        return;
    }
    if(index<0||index>=rozmiar&&index!=0) {
        cout<<"Nie ma takiego indeksu"<<endl;
        return;
    }
    else if(index==0){ //head
        usunZPoczatku();
    }
    else if(index==rozmiar-1){  //tail
        usunZKonca();
    }
    else {
        listaElement* temp = wyszukajElement(index);
        if(temp==NULL) return;
        temp->prevEl->nextEl = temp->nextEl;
        temp->nextEl->prevEl = temp->prevEl;
        delete temp;
        rozmiar--;
    }
}

bool lista::safetyFirst(){
    if(isEmpty()) return false;
    else if(tail==head){
        head=NULL;
        tail=NULL;
        rozmiar=0;
        return false;
    }
    else return true;
}


void lista::zapisz(string nazwa) {
    if (!safetyFirst()){
        cout<<"Brak utworzonej listy."<<endl;
        return;
    }
    ofstream file (nazwa);
    if (!file.is_open()) {
        cout<<"ERROR"<<endl;
        return;
    }
    listaElement* temp = head;
    for(int i=0;i<rozmiar;i++){
        file<< temp->data<< " ";
        temp = temp -> nextEl;
    }

}



