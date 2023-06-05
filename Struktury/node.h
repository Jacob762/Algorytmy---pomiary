//
// Created by jakub on 5/31/2023.
//

#ifndef SDIZOPROJEKT2_NODE_H
#define SDIZOPROJEKT2_NODE_H

namespace std {

    class node {
    public:
        node(int id, int next, int val);

        int id;
        int next;
        int val;

        node* nextEl;
        node* prevEl;

        int getVal();

        int getId();

        int getNext();
    };

} // std

#endif //SDIZOPROJEKT2_NODE_H
