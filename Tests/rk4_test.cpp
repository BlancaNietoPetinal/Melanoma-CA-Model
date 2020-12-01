#include <iostream>
#include <typeinfo>
#include "../RK4/rk4lib.h"
#include "../constants.hpp"
#include "../Tools/toolslib.h"
# include "../DestructionLib/destructionlib.h"

using namespace constants;

int main(){
    int xsize = 2*NX-1, ysize = 2*NY-1;
    int *T, *H, *E, leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell;
    double *Tf, *Hf, *Ef, *Sol, *TSol, *HSol, *ESol, E0=3, H0=2, T0 = 1;
    T = new int[NODE_NUM];
    H = new int[NODE_NUM];
    E = new int[NODE_NUM];
    Tf = new double[NODE_NUM];
    Hf = new double[NODE_NUM];
    Ef = new double[NODE_NUM];
    Sol = new double[NODE_NUM];
    TSol = new double[NODE_NUM];
    HSol = new double[NODE_NUM];
    ESol = new double[NODE_NUM];

    get_tumor_limits(T, xsize, ysize, leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell);
    E = effectorCellPlacement(leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell, 2*NX-1, 2*NY-1, T);
    T = get_mat("Tests/Sample/Ttest_6x6_20.txt", NODE_NUM);
    H = get_mat("Tests/Sample/Htest_6x6_20.txt", NODE_NUM);
    
    for(int node=0;node<NODE_NUM;node++){
        Tf[node] = (double)T[node]; 
        Hf[node] = (double)H[node]; 
        Ef[node] = (double)E[node]; 
    }

    for( int node = 0; node<xsize*ysize; node++){
        Sol = RK4(Tf[node], Hf[node], Ef[node]);
        TSol[node] = Sol[0];
        HSol[node] = Sol[1];
        ESol[node] = Sol[2];
    }
    
    save_matd(NODE_NUM, TSol,"Tests/Sample/Trk4.txt");
    save_matd(NODE_NUM, HSol,"Tests/Sample/Hrk4.txt");
    save_matd(NODE_NUM, ESol,"Tests/Sample/Erk4.txt");
    return 0;
}
