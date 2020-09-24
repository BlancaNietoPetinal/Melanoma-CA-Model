#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <fstream>
#include "../MyFun/MyFun.h"
# define NODE_NUM ( 2 * NX - 1 ) * ( 2 * NY - 1 )

void create_nutrients(int nn, double mat[], int value);

int main() {
    int *T;
    int *H;
    int *D;
    double *N;
    double *M;
    T = new int[NODE_NUM];
    D = new int[NODE_NUM];
    H = new int[NODE_NUM];
    M = new double[NODE_NUM];
    N = new double[NODE_NUM];

    create_vec(NODE_NUM, T, 0);
    create_vec(NODE_NUM, D, 0);
    create_vec(NODE_NUM, H, 1);
    create_nutrients(NODE_NUM, N, 3);
    create_nutrients(NODE_NUM, M, 1);

    T[0] = 1; // iniciar con una celula tumoral

    H[0] = 0; // iniciar con una celula tumoral


    

    save_mat(NODE_NUM, T, "Tests/evolve_results/BTumormat.txt");
    save_mat(NODE_NUM, H, "Tests/evolve_results/BHealthmat.txt");
    save_mat(NODE_NUM, D, "Tests/evolve_results/BDeathmat.txt");

    evolve(NODE_NUM, M, N, T, D, H);

    save_mat(NODE_NUM, T, "Tests/evolve_results/ATumormat.txt");
    save_mat(NODE_NUM, H, "Tests/evolve_results/AHealthmat.txt");
    save_mat(NODE_NUM, D, "Tests/evolve_results/ADeathmat.txt");

    delete [] M;
    delete [] N;
    delete [] T;
    delete [] D;
    delete [] H;
    return 0;
};

void create_nutrients(int nn, double mat[], int value){
    for (int i = 0; i<nn; i++) 
    {  
        if (i%2 == 0){
            mat[i] = value;
        }
        else{
            mat[i] = 0;
        }

    }

};
