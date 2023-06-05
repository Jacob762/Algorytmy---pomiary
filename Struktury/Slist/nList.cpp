//
// Created by jakub on 5/31/2023.
//

#include "nList.h"

namespace std {
    nList::nList(){
        head = NULL;
        tail = NULL;
        rozmiar=0;
    }

    bool nList::isEmpty() {
        if(!head) return true;
        else return false;
    }

    void nList::dodajNaKoniec(node * element) {
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

    void nList::dodajNaPoczatek(node * element){
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

    node* nList::wyszukajElement(int liczba) {
        node* temp = head;
        while(temp!=NULL){
            if(temp->next == liczba) return temp;
            temp = temp->nextEl;
        }
        return NULL;
    }

    void nList::usunZPoczatku(){
        if(rozmiar==0){
            cout<<"nList pusta"<<endl;
            return;
        }
        if(!safetyFirst()) {
            return;
        }
        head->nextEl->prevEl = NULL;
        head = head->nextEl;
        rozmiar--;
    }

    void nList::usunZKonca(){
        if(rozmiar==0){
            cout<<"nList pusta"<<endl;
            return;
        }
        if(!safetyFirst()) {
            return;
        }
        tail->prevEl->nextEl = NULL;
        tail = tail->prevEl;
        rozmiar--;
    }

    bool nList::safetyFirst(){
        if(isEmpty()) return false;
        else if(tail==head){
            head=NULL;
            tail=NULL;
            rozmiar=0;
            return false;
        }
        else return true;
    }
} // std