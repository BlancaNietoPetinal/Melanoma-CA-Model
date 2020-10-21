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
    int * mat;
    mat = new int[25];

    mat = get_squeare(1, 3, 1, 3, 5, 5);

    if((mat[0]!=0) || (mat[7]!=1) || (mat[24]!=0) || (mat[13]!=1)){
        result = false;
    };

    std::cout<<"Test: "<<result<<std::endl;
}