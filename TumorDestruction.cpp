//Accion de las celulas citotoxicas T

# include <iostream>
# include "Libraries/DestructionLib/destructionlib.h"
# include "Libraries/Tools/toolslib.h"
# include "Libraries/RK4/rk4lib.h"
# include "constants.hpp"
using namespace constants;

int *T, *Ecount, *D, *H, leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell;
double *Td, *Hd, *Ed, *Dd, *Sol;
int xsize = 2*NX-1, ysize = 2*NY-1;
int main(){
    T = new int[NODE_NUM];
    Ecount = new int[NODE_NUM];
    D = new int[NODE_NUM];
    H = new int[NODE_NUM];

    Td = new double[NODE_NUM];
    Hd = new double[NODE_NUM];
    Ed = new double[NODE_NUM];
    Dd = new double[NODE_NUM];
    Sol = new double[NODE_NUM];

    create_vec(NODE_NUM, Ecount, 0);
    create_vec(NODE_NUM, D, 0);
    T = get_mat("Results/Generation/T/030.txt", NODE_NUM); 
    H = get_mat("Results/Generation/H/030.txt", NODE_NUM); 
    
    //suggestion usar std::tuple para obtener los valores
    Td = int_2_double(T, NODE_NUM);
    Hd = int_2_double(H, NODE_NUM);
    
    get_tumor_limits(Td, xsize, ysize, leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell);
   
    Ed = effectorCellPlacement(leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell, 2*NX-1, 2*NY-1, Td);

    for(int i=0; i<DESTRUCTION_IT; i++){
        tumor_lysis(Td, Ed, Ecount, Dd, Hd, xsize, ysize);
        for(int node=0; node<NODE_NUM; node++){
            Sol = RK4(Td[node], Hd[node], Ed[node]);
            Td[node] = Sol[0];
            Hd[node] = Sol[1];
            Ed[node] = Sol[2];
        }
        save_mat(NODE_NUM, Td, "Results/Destruction/T/"+std::to_string(i)+".txt");
        save_mat(NODE_NUM, Ed, "Results/Destruction/E/"+std::to_string(i)+".txt");
        save_mat(NODE_NUM, Ecount, "Results/Destruction/Ecount/"+std::to_string(i)+".txt");
        save_mat(NODE_NUM, Hd, "Results/Destruction/H/"+std::to_string(i)+".txt");

        if(noTumorCells(Td, NODE_NUM))break;
    }
    
    delete [] Ed;
    delete [] Ecount;
    delete [] D;
    delete [] Dd;
    delete [] H;
    delete [] Hd;
    delete [] T;
    delete [] Td;
    return 0;
}