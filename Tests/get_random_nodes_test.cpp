#include <iostream>
#include <fstream>
#include "../Tools/toolslib.h"


void test();

int main(){
    test();
    return 0;
}

void test(){
    int xsize = 3, ysize = 3;
    int* random_nodes;
    random_nodes = get_random_nodes(xsize, ysize);
    for(int node = 0; node < xsize*ysize; node++){
        std::cout<<"node: "<<random_nodes[node]<<std::endl;
    }
}