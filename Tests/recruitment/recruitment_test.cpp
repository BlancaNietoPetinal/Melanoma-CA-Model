#include <iostream>
#include <fstream>
#include "../../DestructionLib/destructionlib.h"
#include "../../GeneratorLib/generatorlib.h"


void test();

int main(){
    test(); //check results in matlab
    return 0;
}

void test(){
    int *T, *E, *Ecount, *D, *H, node = 13;
    bool result;
    T = new int[NODE_NUM];
    E = new int[NODE_NUM];
    D = new int[NODE_NUM];
    H = new int[NODE_NUM];
    T = getMat("Tests/Sample/Ttest_6x6_15.txt", 121);
    E = getMat("Tests/Sample/Etest_6x6_15.txt", 121);
    for(int n = 0; n<121; n++){
        if( (T[n] == 0) && (E[n] == 0) ){
            H[n] = 1;
        }
        else{
            H[n] = 0;
        }
    }
    create_vec(NODE_NUM, D, 0);
    recruitment(T, E, D, H, node, 11, 11);
    H[node] = 30;
    save_mat(NODE_NUM, T, "Tests/recruitment/T.txt");
    save_mat(NODE_NUM, D, "Tests/recruitment/D.txt");
    save_mat(NODE_NUM, H, "Tests/recruitment/H.txt");
    save_mat(NODE_NUM, E, "Tests/recruitment/E.txt");

    delete []T;
    delete []E;
    delete []D;
    delete []H;
}