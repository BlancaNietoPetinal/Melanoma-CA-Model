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
    int *T, *E, *Ecount, *D, *H, node = 37, xsize = 11, ysize = 11;
    bool result;
    T = new int[NODE_NUM];
    E = new int[NODE_NUM];
    Ecount = new int[NODE_NUM];
    D = new int[NODE_NUM];
    H = new int[NODE_NUM];
    T = getMat("Tests/Sample/Ttest_6x6_15.txt", xsize*ysize);
    E = getMat("Tests/Sample/Etest_6x6_15.txt", xsize*ysize);
    for(int i = 0; i<xsize*ysize; i++){
        if( (T[i] == 0) && (E[i]==0) ){
            H[i] = 1;
        }
        else{
            H[i] = 0;
        }
    }
    create_vec(NODE_NUM, Ecount, 0);
    create_vec(NODE_NUM, D, 0);

    for(int iter = 0; iter<5; iter++){
        tumor_lysis(T, E, Ecount, D, H, xsize, ysize);
    }
    

    save_mat(NODE_NUM, T, "Tests/tumor_lysis/T.txt");
    save_mat(NODE_NUM, D, "Tests/tumor_lysis/D.txt");
    save_mat(NODE_NUM, Ecount, "Tests/tumor_lysis/Ecount.txt");
    save_mat(NODE_NUM, E, "Tests/tumor_lysis/E.txt");
    save_mat(NODE_NUM, H, "Tests/tumor_lysis/H.txt");

    delete []T;
    delete []E;
    delete []Ecount;
    delete []D;
    delete []H;
}