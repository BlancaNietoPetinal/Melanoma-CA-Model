#include <iostream>
#include <fstream>
#include "../../DestructionLib/destructionlib.h"

void showBorders(int * mat, int leftLim, int rightLim, int supLim, int infLim);

int main(){
    
    int * T;
    int leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell;
    T = new int[NODE_NUM];
    T = getMat("Resultados/T/015.txt", NODE_NUM);

    leftLimitCell = leftBorder(T, NODE_NUM);
    rightLimitCell = rightBorder(T, NODE_NUM);
    superiorLimitCell = superiorBorder(T, 2*NX-1, 2*NY-1);
    inferiorLimitCell = inferiorBorder(T, 2*NX-1, 2*NY-1);
    showBorders(T, leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell);

    return 0;
}

void showBorders(int * mat, int leftLim, int rightLim, int supLim, int infLim){
    std::ofstream file;
    file.open("Resultados/T/boarders.txt");
    for(int node = 0; node<NODE_NUM; node++){

        if( (node == leftLim) || (node == rightLim)  || (node == supLim) || (node == infLim) ){
            file<<20<<'\n';
        }
        else{
            file<<mat[node]<<'\n';
        }
    }
    file.close();
}