//Accion de las celulas citotoxicas T

# include <iostream>
# include "Libraries/DestructionLib/destructionlib.h"
# include "Libraries/Tools/toolslib.h"
# include "Libraries/RK4/rk4lib.h"
# include "constants.hpp"
using namespace constants;

int *T, *Ecount, *D, *H, *T_cells; 
double *Td, *Hd, *Ed, *Dd, *Sol, r;
int xsize = 2*NX-1, ysize = 2*NY-1, Tdi, Tdf;
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
    T_cells = new int[DESTRUCTION_IT];

    create_vec(NODE_NUM, Ecount, 0);
    create_vec(NODE_NUM, Ed, 0);
    create_vec(NODE_NUM, D, 0);
    T = get_mat("Results/DELETE/T/405.txt", NODE_NUM); 
    H = get_mat("Results/DELETE/H/405.txt", NODE_NUM); // SE PUEDE PRESCINDIR?
    
    //suggestion usar std::tuple para obtener los valores
    Td = int_2_double(T, NODE_NUM);
    Hd = int_2_double(H, NODE_NUM);

    effectorCellPlacement(2*NX-1, 2*NY-1, Td, Ed);
    save_mat(NODE_NUM, Ed, "Results/Destruction/Disconnected/E/initial.txt");
    for(int i=0; i<DESTRUCTION_IT; i++){
        tumor_lysis(Td, Ed, Ecount, Dd, Hd, xsize, ysize);
        for(int node=0; node<NODE_NUM; node++){
            Sol = RK4(Td[node], Hd[node], Ed[node]);
            Td[node] = Sol[0];
            Hd[node] = Sol[1];
            Ed[node] = Sol[2];
        }
        std::cout<<"ITERACION: "<<i<<std::endl;
        save_mat(NODE_NUM, Td, "Results/Destruction/Disconnected/T/"+std::to_string(i)+".txt");
        save_mat(NODE_NUM, Ed, "Results/Destruction/Disconnected/E/"+std::to_string(i)+".txt");
        //save_mat(NODE_NUM, Ecount, "Results/Destruction/Disconnected/Ecount/"+std::to_string(i)+".txt");
        save_mat(NODE_NUM, Hd, "Results/Destruction/Disconnected/H/"+std::to_string(i)+".txt");
        T_cells[i] = cell_counter(Td, NODE_NUM);
        if( (no_cells(Td, NODE_NUM)) || (no_cells(Ed, NODE_NUM)) )break;
    }
    save_mat(DESTRUCTION_IT, T_cells, "Results/Destruction/Disconnected/T/cell_count.txt");

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