#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <fstream>
#include "../MyFun/MyFun.h"


int main() {
    # define NODE_NUM ( 2 * NX - 1 ) * ( 2 * NY - 1 )
    int T[NODE_NUM];
    std::vector<int> neighbour_nodes;
    for(int i = 0; i<NX*NY; i++){
        T[i] = 0;
    }
    
    // esquinas
    //T[0] = 1;
    //T[NX*NY - 1] = 1;
    //T[NX*(NY-1)] = 1;
    //T[NX - 1] = 1;
    T[12] = 1;
    //laterales
    //T[1] = 1;
    //T[2*NX-1] = 1;
    //T[NX] = 1;
    //T[NX*(NY-1) + 1] = 1;

    // interno
    //T[NX + 1] = 1;

    for(int i = 0; i<NODE_NUM; i++){
        if(T[i] == 1){
            neighbours(i, T, neighbour_nodes);
            std::cout << "Los elementos vecinos vacios de "<<i<<" son: "<<std::endl;
            for(int j=0; j < neighbour_nodes.size(); j++){
                std::cout<< neighbour_nodes.at(j) << " ";
            }
            std::cout<<"\n";
            neighbour_nodes.clear();
        }
    }
    return 0;
}
