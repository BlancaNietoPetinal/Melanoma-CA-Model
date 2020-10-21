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

    get_coordinates(3,5,5,x,y);
    if((x!=0) || (y!=2)){
        result = false;
    };

    get_coordinates(13,5,5,x,y);
    if((x!=2) || (y!=2)){
        result = false;
    };

    std::cout<<"Test: "<<result<<std::endl;
}
