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
    int * mat1, * mat2;
    mat1 = new int[25];
    mat2 = new int[25];

    for(int node = 0; node<24; node++){
        mat1[node] = 1;
        mat2[node] = 0; 
    }

    mat2[13] = 1;
    mat2[22] = 1;

    match_matrices(mat2, mat1, 5, 5);

    if( (mat1[13] == 1) || (mat1[22] == 1) ){
        result = false;
    }

    std::cout<<"Test: "<<result<<std::endl;
}
