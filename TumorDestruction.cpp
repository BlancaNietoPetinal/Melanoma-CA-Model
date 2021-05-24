//Accion de las celulas citotoxicas T

# include <iostream>
# include "Libraries/DestructionLib/destructionlib.h"
# include "Libraries/Tools/toolslib.h"
# include "constants.hpp"
using namespace constants;

int *T, *Ecount, *D, *H, *T_cells, N_T_cells, d = 0; 
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
    std::vector<int> T_cells;
    std::string TUMOR_TYPE = "Disconnected";
    create_vec(NODE_NUM, Ecount, 0);
    create_vec(NODE_NUM, Ed, 0);
    create_vec(NODE_NUM, Dd, 0);
    T = get_mat("../Results/Generation/"+TUMOR_TYPE+"/T/0180.txt", NODE_NUM); 
    H = get_mat("../Results/Generation/"+TUMOR_TYPE+"/H/0180.txt", NODE_NUM); //prescindir?

    //suggestion usar std::tuple para obtener los valores
    Td = int_2_double(T, NODE_NUM);
    Hd = int_2_double(H, NODE_NUM);

    effectorCellPlacement(Td, Ed);
    save_mat(NODE_NUM, Ed, "../Results/Destruction/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/E/initial.txt");
        int diff = 0;
        for(int i=0; i<DESTRUCTION_IT; i++){
            if(i%5 == 0){
                save_mat(NODE_NUM, Td, "../Results/Destruction/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/T/"+std::to_string(i)+".txt");
            }
            
            tumor_lysis(Td, Ed, Ecount, Dd, Hd);

            std::cout<<"ITERACION: "<<i<<std::endl;
            if(i%5 == 0){
            save_mat(NODE_NUM, Ed, "../Results/Destruction/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/E/"+std::to_string(i)+".txt");
            save_mat(NODE_NUM, Dd, "../Results/Destruction/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/D/"+std::to_string(i)+".txt");
            save_mat(NODE_NUM, Ecount, "../Results/Destruction/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/Ecount/"+std::to_string(i)+".txt");
            save_mat(NODE_NUM, Hd, "../Results/Destruction/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/H/"+std::to_string(i)+".txt");
            }
            N_T_cells = cell_counter(Td);
            T_cells.push_back(N_T_cells);
            diff = N_T_cells-diff;
            if( no_cells(Td) || no_cells(Ed)){
                break;
            };
            if((diff == 0)){
                d++;
            }  
            if(diff != 0){
                d = 0;
            } 
            if(d>5){
                break;
            }
            diff = N_T_cells;
        }
        save_vec(T_cells, "../Results/Destruction/"+TUMOR_TYPE+"/T_cell_count-"+std::to_string(QUADRANT)+".txt");
    //delete [] Ed;
    //delete [] T_cells;
    //delete [] Ecount;
    //delete [] D;
    //delete [] Dd;
    //delete [] H;
    //delete [] Hd;
    //delete [] T;
    //delete [] Td;
    //delete [] Ed;
    //delete [] Sol;
    return 0;
}