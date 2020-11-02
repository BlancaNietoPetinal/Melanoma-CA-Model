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
    int *T, *E, *Ecount, *H, node = 37, xsize = 11, ysize = 11;
    bool result;
    T = new int[NODE_NUM];
    E = new int[NODE_NUM];
    Ecount = new int[NODE_NUM];
    H = new int[NODE_NUM];
    T = getMat("Tests/Sample/Ttest_6x6_15.txt", xsize*ysize);
    E = getMat("Tests/Sample/Etest_6x6_15.txt", xsize*ysize);
    for(int i = 0; i<NODE_NUM; i++){
        if( (T[i] == 0) && (E[i]==0) ){
            H[i] = 1;
        }
        else{
            H[i] = 0;
        }
    }
    create_vec(NODE_NUM, Ecount, 0);
    E[node] = 1;
    Ecount[node] = 2;
    T[node] = 10;
    inactivation(T, E, Ecount, H, node, xsize, ysize);

    save_mat(NODE_NUM, T, "Tests/inactivation/T.txt");
    save_mat(NODE_NUM, Ecount, "Tests/inactivation/Ecount.txt");
    save_mat(NODE_NUM, E, "Tests/inactivation/E.txt");
    save_mat(NODE_NUM, H, "Tests/inactivation/H.txt");

    delete []T;
    delete []E;
    delete []Ecount;
    delete []H;
}