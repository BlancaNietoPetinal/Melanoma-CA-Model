//Accion de las celulas citotoxicas T

# include <iostream>
# include "DestructionLib/destructionlib.h"
# include "Tools/toolslib.h"
# include "GeneratorLib/generatorlib.h"

# include "constants.hpp"
using namespace constants;

int *T, *E, *Ecount, *D, *H, leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell;
int xsize = 2*NX-1, ysize = 2*NY-1;
int main(){
    T = new int[NODE_NUM];
    E = new int[NODE_NUM];
    Ecount = new int[NODE_NUM];
    D = new int[NODE_NUM];
    H = new int[NODE_NUM];

    T = get_mat("Resultados/T/0"+std::to_string(ITERATIONS)+".txt", NODE_NUM);
    
    //suggestion usar std::tuple para obtener los valores
    get_tumor_limits(T, xsize, ysize, leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell);
   
    E = effectorCellPlacement(leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell, 2*NX-1, 2*NY-1, T);
    for(int i=0; i<20; i++){
        tumor_lysis(T, E, Ecount, D, H, xsize, ysize);
    }
    
    save_mat(NODE_NUM, E, "Resultados/T/effector"+std::to_string(ITERATIONS)+".txt");
    save_mat(NODE_NUM, Ecount, "Resultados/T/effectorcount"+std::to_string(ITERATIONS)+".txt");
    save_mat(NODE_NUM, T, "Resultados/T/destruction"+std::to_string(ITERATIONS)+".txt");
    delete [] E;
    delete [] T;
    return 0;
}