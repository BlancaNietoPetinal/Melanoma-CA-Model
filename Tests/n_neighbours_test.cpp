#include <iostream>
#include <fstream>
#include "../DestructionLib/destructionlib.h"


void test();

int main(){
    test();
    return 0;
}

void test(){
    std::vector<int> result;
    int x, y;
    int *testmat;
    testmat = new int[NODE_NUM];
    testmat = getMat("Resultados/T/090.txt", NODE_NUM);

    n_neighbours(2, testmat, 12, (2*NX-1), (2*NY-1));

    //n_neighbours(3, testmat, 12, (2*NX-1), (2*NY-1));


}
