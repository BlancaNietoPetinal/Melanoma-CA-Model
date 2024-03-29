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
    int *T, *E, *Ecount, *D, *H, node = 37;
    bool result;
    T = new int[NODE_NUM];
    E = new int[NODE_NUM];
    Ecount = new int[NODE_NUM];
    D = new int[NODE_NUM];
    H = new int[NODE_NUM];
    T = getMat("Tests/Sample/Ttest_6x6_15.txt", 121);
    E = getMat("Tests/Sample/Etest_6x6_15.txt", 121);
    for(int i = 0; i<NODE_NUM; i++){
        if( (T[i] == 0) && (E[i]==0) ){
            H[i] = 1;
        }
    }
    create_vec(NODE_NUM, Ecount, 0);
    create_vec(NODE_NUM, D, 0);
    Ecount[node] = 2;
    lysis(T, E, Ecount, D, H, node, 11, 11);
    //E[node] = 10;
    save_mat(NODE_NUM, T, "Tests/lysis/T.txt");
    save_mat(NODE_NUM, D, "Tests/lysis/D.txt");
    save_mat(NODE_NUM, Ecount, "Tests/lysis/Ecount.txt");
    save_mat(NODE_NUM, E, "Tests/lysis/E.txt");
    save_mat(NODE_NUM, H, "Tests/lysis/H.txt");

    delete []T;
    delete []E;
    delete []Ecount;
    delete []D;
    delete []H;
}