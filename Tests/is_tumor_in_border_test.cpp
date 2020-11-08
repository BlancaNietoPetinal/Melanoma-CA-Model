#include <iostream>
#include <fstream>
#include "../Tools/toolslib.h"


void test();

int main(){
    test();
    return 0;
}

void test(){
    int xsize = 3, ysize = 3, *T;
    bool result;
    T = new int[xsize*ysize];
    create_vec(xsize*ysize, T, 0);
    T[4] = 1;
    result = is_tumor_in_border(T,3,3);
    std::cout<<"Resultado: "<<result<<std::endl;

}