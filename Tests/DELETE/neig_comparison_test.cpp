#include <iostream>
#include <fstream>
#include "../../GeneratorLib/generatorlib.h"
#include "../../Tools/toolslib.h"

#include <random>
#include <ctime>
#include <chrono>

int main(){
    std::default_random_engine generator2{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> dice_dist(1,50);

    int *T, node = 37, xsize = 11, ysize = 11, index;
    std::vector<int> nn1, nn2, fn1;
    bool result;
    T = new int[NODE_NUM];
    T = get_mat("Tests/Sample/Ttest_6x6_15.txt", xsize*ysize);
    /*
    neighbours(node, T, nn1);
    free_neighbours(T, nn1, fn1);
    for(int i = 0; i<fn1.size();i++){
        std::cout<<"Nodo: "<<fn1[i]<<std::endl;
        //T[fn1[i]] =10;
    }
    */
    nn2 = get_specific_neighbours(T, node, 1, 0, '=', xsize, ysize);
    std::cout<<"Algoritmo 2 tamano: "<<nn2.size()<<std::endl;
    for(int i = 0; i<nn2.size();i++){
        std::cout<<"Nodo: "<<nn2[i]<<std::endl;
        T[nn2[i]] =10;
    }
    
    for(int i = 0; i<10; i++){
        index = dice_dist(generator2) % nn2.size(); //CHEQUEAR ESTO
        std::cout<<"Indice: "<<index<<std::endl;
    }
    T[node]=20;
    save_mat(NODE_NUM, T, "Tests/DELETE/T.txt");
    return 0;
}
