//Accion de las celulas citotoxicas T

# include <iostream>
# include "Libraries/DestructionLib/destructionlib.h"
# include "Libraries/Tools/toolslib.h"
# include "constants.hpp"
using namespace constants;

int *T, *Ecount, *D, *H, *E, *T_cells, N_T_cells, d = 0; 
int xsize = 2*NX-1, ysize = 2*NY-1, Tdi, Tdf;
int main(){
    T = new int[NODE_NUM];
    Ecount = new int[NODE_NUM];
    D = new int[NODE_NUM];
    E = new int[NODE_NUM];
    H = new int[NODE_NUM];
    std::vector<int> T_cells;
    std::string TUMOR_TYPE = "Spherical";
    create_vec(NODE_NUM, Ecount, 0);
    create_vec(NODE_NUM, E, 0);
    create_vec(NODE_NUM, D, 0);
    create_vec(NODE_NUM, H, 1);
    //T = get_mat("../Results/Generation/Mutated/"+TUMOR_TYPE+"/T/0930.txt", NODE_NUM); 
    //H = get_mat("../Results/Generation/Mutated/"+TUMOR_TYPE+"/H/0150.txt", NODE_NUM); //prescindir?
    T = get_mat("../Results/Generation/Mutated/"+TUMOR_TYPE+"/T/0195.txt", NODE_NUM); 
    
    
    for(int node = 0;node<NODE_NUM;node++){
        if(T[node]==1) H[node]=0;
    }
    effectorCellPlacement(T, E);
    save_mat(NODE_NUM, E, "../Results/Destruction/Mutated/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/E/initial.txt");
    //save_mat(NODE_NUM, E, "../Results/Destruction/NonMutated/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/E/initial.txt");
    
    int diff = 0, T0 = cell_counter(T), Tdead = 0;
        for(int i=0; i<DESTRUCTION_IT; i++){
            
            tumor_lysis(T, E, Ecount, D, H);

            std::cout<<"ITERACION: "<<i<<std::endl;
            if(i%5 == 0){
            save_mat(NODE_NUM, E, "../Results/Destruction/Mutated/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/E/"+std::to_string(i)+".txt");
            //save_mat(NODE_NUM, D, "../Results/Destruction/Mutated/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/D/"+std::to_string(i)+".txt");
            //save_mat(NODE_NUM, Ecount, "../Results/Destruction/Mutated/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/Ecount/"+std::to_string(i)+".txt");
            //save_mat(NODE_NUM, H, "../Results/Destruction/Mutated/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/H/"+std::to_string(i)+".txt");
            save_mat(NODE_NUM, T, "../Results/Destruction/Mutated/"+TUMOR_TYPE+"/"+std::to_string(QUADRANT)+"Q/T/"+std::to_string(i)+".txt");
            }
            N_T_cells = cell_counter(T);
            T_cells.push_back(N_T_cells);
            diff = N_T_cells-diff;
            if( no_cells(E)){
                break;
            };
            if((diff == 0)){
                d++;
            }  
            if(diff != 0){
                d = 0;
            } 
            if(d>10){
                break;
            }
            diff = N_T_cells;
            //get_lysis_ratio(T, T0);
        }
        save_vec(T_cells, "../Results/Destruction/Mutated/"+TUMOR_TYPE+"/T_cell_count-"+std::to_string(QUADRANT)+"Q.txt");
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