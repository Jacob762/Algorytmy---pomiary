#include <iostream>
#include <fstream>
#include <random>
#include "Struktury/Prima/Prima.h"
#include "Struktury/Dijkstra/Dijkstra.h"
#include "Struktury/Kruskal/Kruskal.h"
#include "Struktury/BellmanFord/BF.h"
#include "Struktury/Slist/nList.h"



int main() {
    srand(time(NULL));
    //Prima pr = Prima();
    //Dijkstra dij = Dijkstra();
    Kruskal kru = Kruskal();
    BF bff = BF();

    return 0;
}


