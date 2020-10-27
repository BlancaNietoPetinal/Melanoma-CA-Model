#include <iostream>
#include <fstream>
#include "../DestructionLib/destructionlib.h"


void test();

int main(){
    test();
    return 0;
}

void test(){
    bool result = true;
    int x, y;

    if(!are_neighbours_interior(12,1,5,5)){
        result = false;
    }

    if(are_neighbours_interior(12,3,5,5)){
        result = false;
    }

    if(!are_neighbours_interior(12,2,5,5)){
        result = false;
    }

    std::cout<<"Test: "<<result<<std::endl;
}