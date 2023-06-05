//
// Created by jakub on 5/31/2023.
//

#include "node.h"

namespace std {

    node::node(int id, int next, int val){
        this->id = id;
        this->next = next;
        this->val = val;
    }

    int node::getVal(){
        return val;
    }

    int node::getId(){
        return id;
    }

    int node::getNext(){
        return next;
    }
} // std