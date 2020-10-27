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
    int node;

    coordinates_to_node(node,2,0,5,5);
    if(node!=10){
        result = false;
    }

    coordinates_to_node(node,4,4,5,5);
    if(node!=24){
        result = false;
    }

    std::cout<<"Test: "<<result<<std::endl;
}
