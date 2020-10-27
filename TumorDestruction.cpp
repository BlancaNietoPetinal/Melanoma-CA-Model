//Accion de las celulas citotoxicas T

# include <iostream>
# include "DestructionLib/destructionlib.h"

# include "GeneratorLib/generatorlib.h"

# include "constants.hpp"
using namespace constants;

int *T, *E, leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell;

int main(){
    T = new int[NODE_NUM];
    E = new int[NODE_NUM];

    T = getMat("Resultados/T/0"+std::to_string(ITERATIONS)+".txt", NODE_NUM);
    
    //suggestion usar std::tuple para obtener los valores
    get_limits(T, 2*NX-1, 2*NY-1, leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell);
   
    E = effectorCellPlacement(leftLimitCell, rightLimitCell, superiorLimitCell, inferiorLimitCell, 2*NX-1, 2*NY-1, T);
    
    save_mat(NODE_NUM, E, "Resultados/T/effector"+std::to_string(ITERATIONS)+".txt");

    delete [] E;
    delete [] T;
    return 0;
}