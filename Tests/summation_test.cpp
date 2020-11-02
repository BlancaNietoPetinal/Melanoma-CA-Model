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
    int *T, node = 48, xsize = 11, ysize = 11;
    std::vector<int> T_neigbours;
    int result;
    T = new int[xsize*ysize];
    T = getMat("Tests/Sample/Ttest_6x6_15.txt", 121);
    T_neigbours = get_neighbours(T,node,1, xsize, ysize);
    result = summation(T, T_neigbours);
    std::cout<<"Resultado: "<<result<<std::endl;
}