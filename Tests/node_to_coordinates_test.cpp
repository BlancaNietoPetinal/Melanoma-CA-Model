#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <fstream>
#include "../DestructionLib/destructionlib.h"

void test();

int main() {
    test();
    return 0;
}
void test(){
    int xsize = 5, ysize = 5, node = 6, x, y;
    bool result = true;

    node_to_coordinates(node, x, y, xsize, ysize);
    if( (x!=1) && (y!=1) ){
        result = false;
    }
    
    node_to_coordinates(14, x, y, xsize, ysize);
    if( (x!=2) && (y!=4) ){
        result = false;
    }
}

